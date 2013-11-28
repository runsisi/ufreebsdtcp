/*-
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 *	@(#)kern_resource.c	8.5 (Berkeley) 1/21/94
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_resource.c 230754 2012-01-29 21:08:24Z trociny $");

#include "opt_compat.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_sysproto.h>
#include <sys/bsd_file.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_priv.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_refcount.h>
#include <sys/bsd_racct.h>
#include <sys/bsd_resourcevar.h>
#include <sys/bsd_rwlock.h>
#include <sys/bsd_sched.h>
#include <sys/bsd_sx.h>
#include <sys/bsd_syscallsubr.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_sysent.h>
#include <sys/bsd_time.h>
#include <sys/bsd_umtx.h>

#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>

/*
 * Return the current (soft) limit for a particular system resource.
 * The which parameter which specifies the index into the rlimit array
 */
rlim_t
lim_cur(struct proc *p, int which)
{
	struct rlimit rl;

	lim_rlimit(p, which, &rl);
	return (rl.rlim_cur);
}

/*
 * Return a copy of the entire rlimit structure for the system limit
 * specified by 'which' in the rlimit structure pointed to by 'rlp'.
 */
void
lim_rlimit(struct proc *p, int which, struct rlimit *rlp)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);
	KASSERT(which >= 0 && which < RLIM_NLIMITS,
	    ("request for invalid resource limit"));
	*rlp = p->p_limit->pl_rlimit[which];
	if (p->p_sysent->sv_fixlimit != NULL)
		p->p_sysent->sv_fixlimit(rlp, which);
}

/*
 * Change the total socket buffer size a user has used.
 */
int
chgsbsize(uip, hiwat, to, max)
	struct	uidinfo	*uip;
	u_int  *hiwat;
	u_int	to;
	rlim_t	max;
{
    #if 0 // runsisi AT hust.edu.cn @2013/10/25
	int diff;

	diff = to - *hiwat;
	if (diff > 0) {
		if (atomic_fetchadd_long(&uip->ui_sbsize, (long)diff) + diff > max) {
			atomic_subtract_long(&uip->ui_sbsize, (long)diff);
			return (0);
		}
	} else {
		atomic_add_long(&uip->ui_sbsize, (long)diff);
		if (uip->ui_sbsize < 0)
			printf("negative sbsize for uid = %d\n", uip->ui_uid);
	}
    #endif // ------- @2013/10/25
	*hiwat = to;
	return (1);
}
