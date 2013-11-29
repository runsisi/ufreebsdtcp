/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Karels at Berkeley Software Design, Inc.
 *
 * Quite extensively rewritten by Poul-Henning Kamp of the FreeBSD
 * project, to make these variables more userfriendly.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)kern_sysctl.c	8.4 (Berkeley) 4/14/94
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_sysctl.c 248034 2013-03-08 11:25:52Z marius $");

#include "opt_capsicum.h"
#include "opt_compat.h"
#include "opt_ktrace.h"

#include <sys/bsd_param.h>
#include <sys/bsd_fail.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_capability.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_priv.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_jail.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_sbuf.h>
#include <sys/bsd_sx.h>
#include <sys/bsd_sysproto.h>
#include <sys/bsd_uio.h>
#ifdef KTRACE
#include <sys/bsd_ktrace.h>
#endif

#include <net/vnet.h>

//#include <security/mac/mac_framework.h>

#include <vm/vm.h>
#include <vm/vm_extern.h>

static MALLOC_DEFINE(M_SYSCTL, "sysctl", "sysctl internal magic");
static MALLOC_DEFINE(M_SYSCTLOID, "sysctloid", "sysctl dynamic oids");
static MALLOC_DEFINE(M_SYSCTLTMP, "sysctltmp", "sysctl temp output buffer");

/*
 * The sysctllock protects the MIB tree.  It also protects sysctl
 * contexts used with dynamic sysctls.  The sysctl_register_oid() and
 * sysctl_unregister_oid() routines require the sysctllock to already
 * be held, so the sysctl_lock() and sysctl_unlock() routines are
 * provided for the few places in the kernel which need to use that
 * API rather than using the dynamic API.  Use of the dynamic API is
 * strongly encouraged for most code.
 *
 * The sysctlmemlock is used to limit the amount of user memory wired for
 * sysctl requests.  This is implemented by serializing any userland
 * sysctl requests larger than a single page via an exclusive lock.
 */
static struct sx sysctllock;
static struct sx sysctlmemlock;

#define	SYSCTL_XLOCK()		sx_xlock(&sysctllock)
#define	SYSCTL_XUNLOCK()	sx_xunlock(&sysctllock)
#define	SYSCTL_ASSERT_XLOCKED()	sx_assert(&sysctllock, SA_XLOCKED)
#define	SYSCTL_INIT()		sx_init(&sysctllock, "sysctl lock")
#define	SYSCTL_SLEEP(ch, wmesg, timo)					\
				sx_sleep(ch, &sysctllock, 0, wmesg, timo)

static int sysctl_root(SYSCTL_HANDLER_ARGS);

struct sysctl_oid_list sysctl__children; /* root list */

static int	sysctl_remove_oid_locked(struct sysctl_oid *oidp, int del,
		    int recurse);

static struct sysctl_oid *
sysctl_find_oidname(const char *name, struct sysctl_oid_list *list)
{
	struct sysctl_oid *oidp;

	SYSCTL_ASSERT_XLOCKED();
	BSD_SLIST_FOREACH(oidp, list, oid_link) {
		if (strcmp(oidp->oid_name, name) == 0) {
			return (oidp);
		}
	}
	return (NULL);
}

/*
 * Initialization of the MIB tree.
 *
 * Order by number in each list.
 */
void
sysctl_lock(void)
{

	SYSCTL_XLOCK();
}

void
sysctl_unlock(void)
{

	SYSCTL_XUNLOCK();
}

void
sysctl_register_oid(struct sysctl_oid *oidp)
{
	struct sysctl_oid_list *parent = oidp->oid_parent;
	struct sysctl_oid *p;
	struct sysctl_oid *q;

	/*
	 * First check if another oid with the same name already
	 * exists in the parent's list.
	 */
	SYSCTL_ASSERT_XLOCKED();
	p = sysctl_find_oidname(oidp->oid_name, parent);
	if (p != NULL) {
		if ((p->oid_kind & CTLTYPE) == CTLTYPE_NODE) {
			p->oid_refcnt++;
			return;
		} else {
			printf("can't re-use a leaf (%s)!\n", p->oid_name);
			return;
		}
	}
	/*
	 * If this oid has a number OID_AUTO, give it a number which
	 * is greater than any current oid.
	 * NOTE: DO NOT change the starting value here, change it in
	 * <sys/sysctl.h>, and make sure it is at least 256 to
	 * accomodate e.g. net.inet.raw as a static sysctl node.
	 */
	if (oidp->oid_number == OID_AUTO) {
		static int newoid = CTL_AUTO_START;

		oidp->oid_number = newoid++;
		if (newoid == 0x7fffffff)
			panic("out of oids");
	}
#if 0
	else if (oidp->oid_number >= CTL_AUTO_START) {
		/* do not panic; this happens when unregistering sysctl sets */
		printf("static sysctl oid too high: %d", oidp->oid_number);
	}
#endif

	/*
	 * Insert the oid into the parent's list in order.
	 */
	q = NULL;
	BSD_SLIST_FOREACH(p, parent, oid_link) {
		if (oidp->oid_number < p->oid_number)
			break;
		q = p;
	}
	if (q)
		BSD_SLIST_INSERT_AFTER(q, oidp, oid_link);
	else
		BSD_SLIST_INSERT_HEAD(parent, oidp, oid_link);
}

void
sysctl_unregister_oid(struct sysctl_oid *oidp)
{
	struct sysctl_oid *p;
	int error;

	SYSCTL_ASSERT_XLOCKED();
	error = ENOENT;
	if (oidp->oid_number == OID_AUTO) {
		error = EINVAL;
	} else {
		BSD_SLIST_FOREACH(p, oidp->oid_parent, oid_link) {
			if (p == oidp) {
				BSD_SLIST_REMOVE(oidp->oid_parent, oidp,
				    sysctl_oid, oid_link);
				error = 0;
				break;
			}
		}
	}

	/* 
	 * This can happen when a module fails to register and is
	 * being unloaded afterwards.  It should not be a panic()
	 * for normal use.
	 */
	if (error)
		printf("%s: failed to unregister sysctl\n", __func__);
}

/*
 * Register the kernel's oids on startup.
 */
SET_DECLARE(sysctl_set, struct sysctl_oid);

static void
sysctl_register_all(void *arg)
{
	struct sysctl_oid **oidp;

	sx_init(&sysctlmemlock, "sysctl mem");
	SYSCTL_INIT();
	SYSCTL_XLOCK();
	SET_FOREACH(oidp, sysctl_set)
		sysctl_register_oid(*oidp);
	SYSCTL_XUNLOCK();
}
SYSINIT(sysctl, SI_SUB_KMEM, SI_ORDER_ANY, sysctl_register_all, 0);

/*
 * "Staff-functions"
 *
 * These functions implement a presently undocumented interface 
 * used by the sysctl program to walk the tree, and get the type
 * so it can print the value.
 * This interface is under work and consideration, and should probably
 * be killed with a big axe by the first person who can find the time.
 * (be aware though, that the proper interface isn't as obvious as it
 * may seem, there are various conflicting requirements.
 *
 * {0,0}	printf the entire MIB-tree.
 * {0,1,...}	return the name of the "..." OID.
 * {0,2,...}	return the next OID.
 * {0,3}	return the OID of the name in "new"
 * {0,4,...}	return the kind & format info for the "..." OID.
 * {0,5,...}	return the description the "..." OID.
 */

#ifdef SYSCTL_DEBUG
static void
sysctl_sysctl_debug_dump_node(struct sysctl_oid_list *l, int i)
{
	int k;
	struct sysctl_oid *oidp;

	SYSCTL_ASSERT_XLOCKED();
	BSD_SLIST_FOREACH(oidp, l, oid_link) {

		for (k=0; k<i; k++)
			printf(" ");

		printf("%d %s ", oidp->oid_number, oidp->oid_name);

		printf("%c%c",
			oidp->oid_kind & CTLFLAG_RD ? 'R':' ',
			oidp->oid_kind & CTLFLAG_WR ? 'W':' ');

		if (oidp->oid_handler)
			printf(" *Handler");

		switch (oidp->oid_kind & CTLTYPE) {
			case CTLTYPE_NODE:
				printf(" Node\n");
				if (!oidp->oid_handler) {
					sysctl_sysctl_debug_dump_node(
						oidp->oid_arg1, i+2);
				}
				break;
			case CTLTYPE_INT:    printf(" Int\n"); break;
			case CTLTYPE_UINT:   printf(" u_int\n"); break;
			case CTLTYPE_LONG:   printf(" Long\n"); break;
			case CTLTYPE_ULONG:  printf(" u_long\n"); break;
			case CTLTYPE_STRING: printf(" String\n"); break;
			case CTLTYPE_U64:    printf(" uint64_t\n"); break;
			case CTLTYPE_S64:    printf(" int64_t\n"); break;
			case CTLTYPE_OPAQUE: printf(" Opaque/struct\n"); break;
			default:	     printf("\n");
		}

	}
}

static int
sysctl_sysctl_debug(SYSCTL_HANDLER_ARGS)
{
	int error;

	error = priv_check(req->td, PRIV_SYSCTL_DEBUG);
	if (error)
		return (error);
	SYSCTL_XLOCK();
	sysctl_sysctl_debug_dump_node(&sysctl__children, 0);
	SYSCTL_XUNLOCK();
	return (ENOENT);
}

SYSCTL_PROC(_sysctl, 0, debug, CTLTYPE_STRING|CTLFLAG_RD,
	0, 0, sysctl_sysctl_debug, "-", "");
#endif

static int
sysctl_sysctl_name(SYSCTL_HANDLER_ARGS)
{
	int *name = (int *) arg1;
	u_int namelen = arg2;
	int error = 0;
	struct sysctl_oid *oid;
	struct sysctl_oid_list *lsp = &sysctl__children, *lsp2;
	char buf[10];

	SYSCTL_XLOCK();
	while (namelen) {
		if (!lsp) {
			snprintf(buf,sizeof(buf),"%d",*name);
			if (req->oldidx)
				error = SYSCTL_OUT(req, ".", 1);
			if (!error)
				error = SYSCTL_OUT(req, buf, strlen(buf));
			if (error)
				goto out;
			namelen--;
			name++;
			continue;
		}
		lsp2 = 0;
		BSD_SLIST_FOREACH(oid, lsp, oid_link) {
			if (oid->oid_number != *name)
				continue;

			if (req->oldidx)
				error = SYSCTL_OUT(req, ".", 1);
			if (!error)
				error = SYSCTL_OUT(req, oid->oid_name,
					strlen(oid->oid_name));
			if (error)
				goto out;

			namelen--;
			name++;

			if ((oid->oid_kind & CTLTYPE) != CTLTYPE_NODE) 
				break;

			if (oid->oid_handler)
				break;

			lsp2 = SYSCTL_CHILDREN(oid);
			break;
		}
		lsp = lsp2;
	}
	error = SYSCTL_OUT(req, "", 1);
 out:
	SYSCTL_XUNLOCK();
	return (error);
}

/*
 * XXXRW/JA: Shouldn't return name data for nodes that we don't permit in
 * capability mode.
 */
static SYSCTL_NODE(_sysctl, 1, name, CTLFLAG_RD | CTLFLAG_CAPRD,
    sysctl_sysctl_name, "");

static int
sysctl_sysctl_next_ls(struct sysctl_oid_list *lsp, int *name, u_int namelen, 
	int *next, int *len, int level, struct sysctl_oid **oidpp)
{
	struct sysctl_oid *oidp;

	SYSCTL_ASSERT_XLOCKED();
	*len = level;
	BSD_SLIST_FOREACH(oidp, lsp, oid_link) {
		*next = oidp->oid_number;
		*oidpp = oidp;

		if (oidp->oid_kind & CTLFLAG_SKIP)
			continue;

		if (!namelen) {
			if ((oidp->oid_kind & CTLTYPE) != CTLTYPE_NODE) 
				return (0);
			if (oidp->oid_handler) 
				/* We really should call the handler here...*/
				return (0);
			lsp = SYSCTL_CHILDREN(oidp);
			if (!sysctl_sysctl_next_ls(lsp, 0, 0, next+1, 
				len, level+1, oidpp))
				return (0);
			goto emptynode;
		}

		if (oidp->oid_number < *name)
			continue;

		if (oidp->oid_number > *name) {
			if ((oidp->oid_kind & CTLTYPE) != CTLTYPE_NODE)
				return (0);
			if (oidp->oid_handler)
				return (0);
			lsp = SYSCTL_CHILDREN(oidp);
			if (!sysctl_sysctl_next_ls(lsp, name+1, namelen-1, 
				next+1, len, level+1, oidpp))
				return (0);
			goto next;
		}
		if ((oidp->oid_kind & CTLTYPE) != CTLTYPE_NODE)
			continue;

		if (oidp->oid_handler)
			continue;

		lsp = SYSCTL_CHILDREN(oidp);
		if (!sysctl_sysctl_next_ls(lsp, name+1, namelen-1, next+1, 
			len, level+1, oidpp))
			return (0);
	next:
		namelen = 1;
	emptynode:
		*len = level;
	}
	return (1);
}

static int
sysctl_sysctl_next(SYSCTL_HANDLER_ARGS)
{
	int *name = (int *) arg1;
	u_int namelen = arg2;
	int i, j, error;
	struct sysctl_oid *oid;
	struct sysctl_oid_list *lsp = &sysctl__children;
	int newoid[CTL_MAXNAME];

	SYSCTL_XLOCK();
	i = sysctl_sysctl_next_ls(lsp, name, namelen, newoid, &j, 1, &oid);
	SYSCTL_XUNLOCK();
	if (i)
		return (ENOENT);
	error = SYSCTL_OUT(req, newoid, j * sizeof (int));
	return (error);
}

/*
 * XXXRW/JA: Shouldn't return next data for nodes that we don't permit in
 * capability mode.
 */
static SYSCTL_NODE(_sysctl, 2, next, CTLFLAG_RD | CTLFLAG_CAPRD,
    sysctl_sysctl_next, "");

static int
name2oid(char *name, int *oid, int *len, struct sysctl_oid **oidpp)
{
	struct sysctl_oid *oidp;
	struct sysctl_oid_list *lsp = &sysctl__children;
	char *p;

	SYSCTL_ASSERT_XLOCKED();

	for (*len = 0; *len < CTL_MAXNAME;) {
		p = strsep(&name, ".");

		oidp = BSD_SLIST_FIRST(lsp);
		for (;; oidp = BSD_SLIST_NEXT(oidp, oid_link)) {
			if (oidp == NULL)
				return (ENOENT);
			if (strcmp(p, oidp->oid_name) == 0)
				break;
		}
		*oid++ = oidp->oid_number;
		(*len)++;

		if (name == NULL || *name == '\0') {
			if (oidpp)
				*oidpp = oidp;
			return (0);
		}

		if ((oidp->oid_kind & CTLTYPE) != CTLTYPE_NODE)
			break;

		if (oidp->oid_handler)
			break;

		lsp = SYSCTL_CHILDREN(oidp);
	}
	return (ENOENT);
}

static int
sysctl_sysctl_name2oid(SYSCTL_HANDLER_ARGS)
{
	char *p;
	int error, oid[CTL_MAXNAME], len = 0;
	struct sysctl_oid *op = 0;

	if (!req->newlen) 
		return (ENOENT);
	if (req->newlen >= MAXPATHLEN)	/* XXX arbitrary, undocumented */
		return (ENAMETOOLONG);

	p = bsd_malloc(req->newlen+1, M_SYSCTL, M_WAITOK);

	error = SYSCTL_IN(req, p, req->newlen);
	if (error) {
		bsd_free(p, M_SYSCTL);
		return (error);
	}

	p [req->newlen] = '\0';

	SYSCTL_XLOCK();
	error = name2oid(p, oid, &len, &op);
	SYSCTL_XUNLOCK();

	bsd_free(p, M_SYSCTL);

	if (error)
		return (error);

	error = SYSCTL_OUT(req, oid, len * sizeof *oid);
	return (error);
}

/*
 * XXXRW/JA: Shouldn't return name2oid data for nodes that we don't permit in
 * capability mode.
 */
SYSCTL_PROC(_sysctl, 3, name2oid,
    CTLTYPE_INT | CTLFLAG_RW | CTLFLAG_ANYBODY | CTLFLAG_MPSAFE
    | CTLFLAG_CAPRW, 0, 0, sysctl_sysctl_name2oid, "I", "");

static int
sysctl_sysctl_oidfmt(SYSCTL_HANDLER_ARGS)
{
	struct sysctl_oid *oid;
	int error;

	SYSCTL_XLOCK();
	error = sysctl_find_oid(arg1, arg2, &oid, NULL, req);
	if (error)
		goto out;

	if (oid->oid_fmt == NULL) {
		error = ENOENT;
		goto out;
	}
	error = SYSCTL_OUT(req, &oid->oid_kind, sizeof(oid->oid_kind));
	if (error)
		goto out;
	error = SYSCTL_OUT(req, oid->oid_fmt, strlen(oid->oid_fmt) + 1);
 out:
	SYSCTL_XUNLOCK();
	return (error);
}


static SYSCTL_NODE(_sysctl, 4, oidfmt, CTLFLAG_RD|CTLFLAG_MPSAFE|CTLFLAG_CAPRD,
    sysctl_sysctl_oidfmt, "");

static int
sysctl_sysctl_oiddescr(SYSCTL_HANDLER_ARGS)
{
	struct sysctl_oid *oid;
	int error;

	SYSCTL_XLOCK();
	error = sysctl_find_oid(arg1, arg2, &oid, NULL, req);
	if (error)
		goto out;

	if (oid->oid_descr == NULL) {
		error = ENOENT;
		goto out;
	}
	error = SYSCTL_OUT(req, oid->oid_descr, strlen(oid->oid_descr) + 1);
 out:
	SYSCTL_XUNLOCK();
	return (error);
}

static SYSCTL_NODE(_sysctl, 5, oiddescr, CTLFLAG_RD|CTLFLAG_CAPRD,
    sysctl_sysctl_oiddescr, "");

/*
 * Default "handler" functions.
 */

/*
 * Handle an int, signed or unsigned.
 * Two cases:
 *     a variable:  point arg1 at it.
 *     a constant:  pass it in arg2.
 */

int
sysctl_handle_int(SYSCTL_HANDLER_ARGS)
{
	int tmpout, error = 0;

	/*
	 * Attempt to get a coherent snapshot by making a copy of the data.
	 */
	if (arg1)
		tmpout = *(int *)arg1;
	else
		tmpout = arg2;
	error = SYSCTL_OUT(req, &tmpout, sizeof(int));

	if (error || !req->newptr)
		return (error);

	if (!arg1)
		error = EPERM;
	else
		error = SYSCTL_IN(req, arg1, sizeof(int));
	return (error);
}

/*
 * Based on on sysctl_handle_int() convert milliseconds into ticks.
 * Note: this is used by TCP.
 */

int
sysctl_msec_to_ticks(SYSCTL_HANDLER_ARGS)
{
	int error, s, tt;

	tt = *(int *)arg1;
	s = (int)((int64_t)tt * 1000 / hz);

	error = sysctl_handle_int(oidp, &s, 0, req);
	if (error || !req->newptr)
		return (error);

	tt = (int)((int64_t)s * hz / 1000);
	if (tt < 1)
		return (EINVAL);

	*(int *)arg1 = tt;
	return (0);
}


/*
 * Handle a long, signed or unsigned.
 * Two cases:
 *     a variable:  point arg1 at it.
 *     a constant:  pass it in arg2.
 */

int
sysctl_handle_long(SYSCTL_HANDLER_ARGS)
{
	int error = 0;
	long tmplong;
#ifdef SCTL_MASK32
	int tmpint;
#endif

	/*
	 * Attempt to get a coherent snapshot by making a copy of the data.
	 */
	if (arg1)
		tmplong = *(long *)arg1;
	else
		tmplong = arg2;
#ifdef SCTL_MASK32
	if (req->flags & SCTL_MASK32) {
		tmpint = tmplong;
		error = SYSCTL_OUT(req, &tmpint, sizeof(int));
	} else
#endif
		error = SYSCTL_OUT(req, &tmplong, sizeof(long));

	if (error || !req->newptr)
		return (error);

	if (!arg1)
		error = EPERM;
#ifdef SCTL_MASK32
	else if (req->flags & SCTL_MASK32) {
		error = SYSCTL_IN(req, &tmpint, sizeof(int));
		*(long *)arg1 = (long)tmpint;
	}
#endif
	else
		error = SYSCTL_IN(req, arg1, sizeof(long));
	return (error);
}

/*
 * Handle a 64 bit int, signed or unsigned.
 * Two cases:
 *     a variable:  point arg1 at it.
 *     a constant:  pass it in arg2.
 */
int
sysctl_handle_64(SYSCTL_HANDLER_ARGS)
{
	int error = 0;
	uint64_t tmpout;

	/*
	 * Attempt to get a coherent snapshot by making a copy of the data.
	 */
	if (arg1)
		tmpout = *(uint64_t *)arg1;
	else
		tmpout = arg2;
	error = SYSCTL_OUT(req, &tmpout, sizeof(uint64_t));

	if (error || !req->newptr)
		return (error);

	if (!arg1)
		error = EPERM;
	else
		error = SYSCTL_IN(req, arg1, sizeof(uint64_t));
	return (error);
}

/*
 * Handle our generic '\0' terminated 'C' string.
 * Two cases:
 * 	a variable string:  point arg1 at it, arg2 is max length.
 * 	a constant string:  point arg1 at it, arg2 is zero.
 */

int
sysctl_handle_string(SYSCTL_HANDLER_ARGS)
{
	int error=0;
	char *tmparg;
	size_t outlen;

	/*
	 * Attempt to get a coherent snapshot by copying to a
	 * temporary kernel buffer.
	 */
retry:
	outlen = strlen((char *)arg1)+1;
	tmparg = bsd_malloc(outlen, M_SYSCTLTMP, M_WAITOK);

	if (strlcpy(tmparg, (char *)arg1, outlen) >= outlen) {
		bsd_free(tmparg, M_SYSCTLTMP);
		goto retry;
	}

	error = SYSCTL_OUT(req, tmparg, outlen);
	bsd_free(tmparg, M_SYSCTLTMP);

	if (error || !req->newptr)
		return (error);

	if ((req->newlen - req->newidx) >= arg2) {
		error = EINVAL;
	} else {
		arg2 = (req->newlen - req->newidx);
		error = SYSCTL_IN(req, arg1, arg2);
		((char *)arg1)[arg2] = '\0';
	}

	return (error);
}

/*
 * Handle any kind of opaque data.
 * arg1 points to it, arg2 is the size.
 */

int
sysctl_handle_opaque(SYSCTL_HANDLER_ARGS)
{
	int error, tries;
	u_int generation;
	struct sysctl_req req2;

	/*
	 * Attempt to get a coherent snapshot, by using the thread
	 * pre-emption counter updated from within mi_switch() to
	 * determine if we were pre-empted during a bcopy() or
	 * copyout(). Make 3 attempts at doing this before giving up.
	 * If we encounter an error, stop immediately.
	 */
	tries = 0;
	req2 = *req;
retry:
	generation = curthread->td_generation;
	error = SYSCTL_OUT(req, arg1, arg2);
	if (error)
		return (error);
	tries++;
	if (generation != curthread->td_generation && tries < 3) {
		*req = req2;
		goto retry;
	}

	error = SYSCTL_IN(req, arg1, arg2);

	return (error);
}

/*
 * Transfer functions to/from kernel space.
 * XXX: rather untested at this point
 */
static int
sysctl_old_kernel(struct sysctl_req *req, const void *p, size_t l)
{
	size_t i = 0;

	if (req->oldptr) {
		i = l;
		if (req->oldlen <= req->oldidx)
			i = 0;
		else
			if (i > req->oldlen - req->oldidx)
				i = req->oldlen - req->oldidx;
		if (i > 0)
			bcopy(p, (char *)req->oldptr + req->oldidx, i);
	}
	req->oldidx += l;
	if (req->oldptr && i != l)
		return (ENOMEM);
	return (0);
}

static int
sysctl_new_kernel(struct sysctl_req *req, void *p, size_t l)
{
	if (!req->newptr)
		return (0);
	if (req->newlen - req->newidx < l)
		return (EINVAL);
	bcopy((char *)req->newptr + req->newidx, p, l);
	req->newidx += l;
	return (0);
}

int
kernel_sysctl(struct thread *td, int *name, u_int namelen, void *old,
    size_t *oldlenp, void *new, size_t newlen, size_t *retval, int flags)
{
	int error = 0;
	struct sysctl_req req;

	bzero(&req, sizeof req);

	req.td = td;
	req.flags = flags;

	if (oldlenp) {
		req.oldlen = *oldlenp;
	}
	req.validlen = req.oldlen;

	if (old) {
		req.oldptr= old;
	}

	if (new != NULL) {
		req.newlen = newlen;
		req.newptr = new;
	}

	req.oldfunc = sysctl_old_kernel;
	req.newfunc = sysctl_new_kernel;
	req.lock = REQ_UNWIRED;

	SYSCTL_XLOCK();
	error = sysctl_root(0, name, namelen, &req);
	SYSCTL_XUNLOCK();

	if (req.lock == REQ_WIRED && req.validlen > 0)
        #if 0	// runsisi AT hust.edu.cn @2013/11/29
        vsunlock(req.oldptr, req.validlen);
        #endif 	// ---------------------- @2013/11/29

	if (error && error != ENOMEM)
		return (error);

	if (retval) {
		if (req.oldptr && req.oldidx > req.validlen)
			*retval = req.validlen;
		else
			*retval = req.oldidx;
	}
	return (error);
}

int
kernel_sysctlbyname(struct thread *td, char *name, void *old, size_t *oldlenp,
    void *new, size_t newlen, size_t *retval, int flags)
{
        int oid[CTL_MAXNAME];
        size_t oidlen, plen;
	int error;

	oid[0] = 0;		/* sysctl internal magic */
	oid[1] = 3;		/* name2oid */
	oidlen = sizeof(oid);

	error = kernel_sysctl(td, oid, 2, oid, &oidlen,
	    (void *)name, strlen(name), &plen, flags);
	if (error)
		return (error);

	error = kernel_sysctl(td, oid, plen / sizeof(int), old, oldlenp,
	    new, newlen, retval, flags);
	return (error);
}

/*
 * Transfer function to/from user space.
 */
static int
sysctl_old_user(struct sysctl_req *req, const void *p, size_t l)
{
	size_t i, len, origidx;
	int error;

	origidx = req->oldidx;
	req->oldidx += l;
	if (req->oldptr == NULL)
		return (0);
	/*
	 * If we have not wired the user supplied buffer and we are currently
	 * holding locks, drop a witness warning, as it's possible that
	 * write operations to the user page can sleep.
	 */
	if (req->lock != REQ_WIRED)
		WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
		    "sysctl_old_user()");
	i = l;
	len = req->validlen;
	if (len <= origidx)
		i = 0;
	else {
		if (i > len - origidx)
			i = len - origidx;
		if (req->lock == REQ_WIRED) {
			error = copyout_nofault(p, (char *)req->oldptr +
			    origidx, i);
		} else
			error = copyout(p, (char *)req->oldptr + origidx, i);
		if (error != 0)
			return (error);
	}
	if (i < l)
		return (ENOMEM);
	return (0);
}

static int
sysctl_new_user(struct sysctl_req *req, void *p, size_t l)
{
	int error;

	if (!req->newptr)
		return (0);
	if (req->newlen - req->newidx < l)
		return (EINVAL);
	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "sysctl_new_user()");
	error = copyin((char *)req->newptr + req->newidx, p, l);
	req->newidx += l;
	return (error);
}

/*
 * Wire the user space destination buffer.  If set to a value greater than
 * zero, the len parameter limits the maximum amount of wired memory.
 */
int
sysctl_wire_old_buffer(struct sysctl_req *req, size_t len)
{
    #if 0	// runsisi AT hust.edu.cn @2013/11/29
    int ret;
    size_t wiredlen;

    wiredlen = (len > 0 && len < req->oldlen) ? len : req->oldlen;
    ret = 0;
    if (req->lock != REQ_WIRED && req->oldptr &&
        req->oldfunc == sysctl_old_user) {
        if (wiredlen != 0) {
            ret = vslock(req->oldptr, wiredlen);
            if (ret != 0) {
                if (ret != ENOMEM)
                    return (ret);
                wiredlen = 0;
            }
        }
        req->lock = REQ_WIRED;
        req->validlen = wiredlen;
    }
    #endif 	// ---------------------- @2013/11/29
	return (0);
}

int
sysctl_find_oid(int *name, u_int namelen, struct sysctl_oid **noid,
    int *nindx, struct sysctl_req *req)
{
	struct sysctl_oid_list *lsp;
	struct sysctl_oid *oid;
	int indx;

	SYSCTL_ASSERT_XLOCKED();
	lsp = &sysctl__children;
	indx = 0;
	while (indx < CTL_MAXNAME) {
		BSD_SLIST_FOREACH(oid, lsp, oid_link) {
			if (oid->oid_number == name[indx])
				break;
		}
		if (oid == NULL)
			return (ENOENT);

		indx++;
		if ((oid->oid_kind & CTLTYPE) == CTLTYPE_NODE) {
			if (oid->oid_handler != NULL || indx == namelen) {
				*noid = oid;
				if (nindx != NULL)
					*nindx = indx;
				KASSERT((oid->oid_kind & CTLFLAG_DYING) == 0,
				    ("%s found DYING node %p", __func__, oid));
				return (0);
			}
			lsp = SYSCTL_CHILDREN(oid);
		} else if (indx == namelen) {
			*noid = oid;
			if (nindx != NULL)
				*nindx = indx;
			KASSERT((oid->oid_kind & CTLFLAG_DYING) == 0,
			    ("%s found DYING node %p", __func__, oid));
			return (0);
		} else {
			return (ENOTDIR);
		}
	}
	return (ENOENT);
}

/*
 * Traverse our tree, and find the right node, execute whatever it points
 * to, and return the resulting error code.
 */

static int
sysctl_root(SYSCTL_HANDLER_ARGS)
{
	struct sysctl_oid *oid;
	int error, indx, lvl;

	SYSCTL_ASSERT_XLOCKED();

	error = sysctl_find_oid(arg1, arg2, &oid, &indx, req);
	if (error)
		return (error);

	if ((oid->oid_kind & CTLTYPE) == CTLTYPE_NODE) {
		/*
		 * You can't call a sysctl when it's a node, but has
		 * no handler.  Inform the user that it's a node.
		 * The indx may or may not be the same as namelen.
		 */
		if (oid->oid_handler == NULL)
			return (EISDIR);
	}

	/* Is this sysctl writable? */
	if (req->newptr && !(oid->oid_kind & CTLFLAG_WR))
		return (EPERM);

    #if 0	// runsisi AT hust.edu.cn @2013/11/29
    KASSERT(req->td != NULL, ("sysctl_root(): req->td == NULL"));

    #ifdef CAPABILITY_MODE
    /*
     * If the process is in capability mode, then don't permit reading or
     * writing unless specifically granted for the node.
     */
    if (IN_CAPABILITY_MODE(req->td)) {
        if (req->oldptr && !(oid->oid_kind & CTLFLAG_CAPRD))
            return (EPERM);
        if (req->newptr && !(oid->oid_kind & CTLFLAG_CAPWR))
            return (EPERM);
    }
    #endif

    /* Is this sysctl sensitive to securelevels? */
    if (req->newptr && (oid->oid_kind & CTLFLAG_SECURE)) {
        lvl = (oid->oid_kind & CTLMASK_SECURE) >> CTLSHIFT_SECURE;
        error = securelevel_gt(req->td->td_ucred, lvl);
        if (error)
            return (error);
    }

    /* Is this sysctl writable by only privileged users? */
    if (req->newptr && !(oid->oid_kind & CTLFLAG_ANYBODY)) {
        int priv;

        if (oid->oid_kind & CTLFLAG_PRISON)
            priv = PRIV_SYSCTL_WRITEJAIL;
    #ifdef VIMAGE
        else if ((oid->oid_kind & CTLFLAG_VNET) &&
             prison_owns_vnet(req->td->td_ucred))
            priv = PRIV_SYSCTL_WRITEJAIL;
    #endif
        else
            priv = PRIV_SYSCTL_WRITE;
        error = priv_check(req->td, priv);
        if (error)
            return (error);
    }
    #endif 	// ---------------------- @2013/11/29

	if (!oid->oid_handler)
		return (EINVAL);

	if ((oid->oid_kind & CTLTYPE) == CTLTYPE_NODE) {
		arg1 = (int *)arg1 + indx;
		arg2 -= indx;
	} else {
		arg1 = oid->oid_arg1;
		arg2 = oid->oid_arg2;
	}
#ifdef MAC
	error = mac_system_check_sysctl(req->td->td_ucred, oid, arg1, arg2,
	    req);
	if (error != 0)
		return (error);
#endif
	oid->oid_running++;
	SYSCTL_XUNLOCK();

	if (!(oid->oid_kind & CTLFLAG_MPSAFE))
		mtx_lock(&Giant);
	error = oid->oid_handler(oid, arg1, arg2, req);
	if (!(oid->oid_kind & CTLFLAG_MPSAFE))
		mtx_unlock(&Giant);

    #if 0	// runsisi AT hust.edu.cn @2013/11/29
    KFAIL_POINT_ERROR(_debug_fail_point, sysctl_running, error);
    #endif 	// ---------------------- @2013/11/29

	SYSCTL_XLOCK();
	oid->oid_running--;
    #if 0	// runsisi AT hust.edu.cn @2013/11/29
    if (oid->oid_running == 0 && (oid->oid_kind & CTLFLAG_DYING) != 0)
        wakeup(&oid->oid_running);
    #endif 	// ---------------------- @2013/11/29
	return (error);
}

#ifndef _SYS_SYSPROTO_H_
struct sysctl_args {
	int	*name;
	u_int	namelen;
	void	*old;
	size_t	*oldlenp;
	void	*new;
	size_t	newlen;
};
#endif
int
sys___sysctl(struct thread *td, struct sysctl_args *uap)
{
	int error, i, name[CTL_MAXNAME];
	size_t j;

	if (uap->namelen > CTL_MAXNAME || uap->namelen < 2)
		return (EINVAL);

 	error = copyin(uap->name, &name, uap->namelen * sizeof(int));
 	if (error)
		return (error);

	error = userland_sysctl(td, name, uap->namelen,
		uap->old, uap->oldlenp, 0,
		uap->new, uap->newlen, &j, 0);
	if (error && error != ENOMEM)
		return (error);
	if (uap->oldlenp) {
		i = copyout(&j, uap->oldlenp, sizeof(j));
		if (i)
			return (i);
	}
	return (error);
}

/*
 * This is used from various compatibility syscalls too.  That's why name
 * must be in kernel space.
 */
int
userland_sysctl(struct thread *td, int *name, u_int namelen, void *old,
    size_t *oldlenp, int inkernel, void *new, size_t newlen, size_t *retval,
    int flags)
{
	int error = 0, memlocked;
	struct sysctl_req req;

	bzero(&req, sizeof req);

	req.td = td;
	req.flags = flags;

	if (oldlenp) {
		if (inkernel) {
			req.oldlen = *oldlenp;
		} else {
			error = copyin(oldlenp, &req.oldlen, sizeof(*oldlenp));
			if (error)
				return (error);
		}
	}
	req.validlen = req.oldlen;

    #if 0	// runsisi AT hust.edu.cn @2013/11/29
    if (old) {
        if (!useracc(old, req.oldlen, VM_PROT_WRITE))
            return (EFAULT);
        req.oldptr= old;
    }

    if (new != NULL) {
        if (!useracc(new, newlen, VM_PROT_READ))
            return (EFAULT);
        req.newlen = newlen;
        req.newptr = new;
    }
    #endif 	// ---------------------- @2013/11/29

	req.oldfunc = sysctl_old_user;
	req.newfunc = sysctl_new_user;
	req.lock = REQ_UNWIRED;

#ifdef KTRACE
	if (KTRPOINT(curthread, KTR_SYSCTL))
		ktrsysctl(name, namelen);
#endif

	if (req.oldlen > PAGE_SIZE) {
		memlocked = 1;
		sx_xlock(&sysctlmemlock);
	} else
		memlocked = 0;
	CURVNET_SET(TD_TO_VNET(td));

	for (;;) {
		req.oldidx = 0;
		req.newidx = 0;
		SYSCTL_XLOCK();
		error = sysctl_root(0, name, namelen, &req);
		SYSCTL_XUNLOCK();
		if (error != EAGAIN)
			break;
        #if 0	// runsisi AT hust.edu.cn @2013/11/29
        kern_yield(PRI_USER);
        #endif 	// ---------------------- @2013/11/29
	}

	CURVNET_RESTORE();

	if (req.lock == REQ_WIRED && req.validlen > 0)
        #if 0	// runsisi AT hust.edu.cn @2013/11/29
        vsunlock(req.oldptr, req.validlen);
        #endif 	// ---------------------- @2013/11/29
	if (memlocked)
		sx_xunlock(&sysctlmemlock);

	if (error && error != ENOMEM)
		return (error);

	if (retval) {
		if (req.oldptr && req.oldidx > req.validlen)
			*retval = req.validlen;
		else
			*retval = req.oldidx;
	}
	return (error);
}

/*
 * Drain into a sysctl struct.  The user buffer should be wired if a page
 * fault would cause issue.
 */
static int
sbuf_sysctl_drain(void *arg, const char *data, int len)
{
	struct sysctl_req *req = arg;
	int error;

	error = SYSCTL_OUT(req, data, len);
	KASSERT(error >= 0, ("Got unexpected negative value %d", error));
	return (error == 0 ? len : -error);
}

struct sbuf *
sbuf_new_for_sysctl(struct sbuf *s, char *buf, int length,
    struct sysctl_req *req)
{

	s = sbuf_new(s, buf, length, SBUF_FIXEDLEN);
	sbuf_set_drain(s, sbuf_sysctl_drain, req);
	return (s);
}
