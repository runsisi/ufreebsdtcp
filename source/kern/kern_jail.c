/*-
 * Copyright (c) 1999 Poul-Henning Kamp.
 * Copyright (c) 2008 Bjoern A. Zeeb.
 * Copyright (c) 2009 James Gritton.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_jail.c 250915 2013-05-22 18:26:12Z jamie $");

#include "opt_compat.h"
#include "opt_ddb.h"
#include "opt_inet.h"
#include "opt_inet6.h"

#include <sys/bsd_param.h>
#include <sys/bsd_types.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_errno.h>
#include <sys/bsd_sysproto.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_osd.h>
#include <sys/bsd_priv.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_taskqueue.h>
#include <sys/bsd_fcntl.h>
#include <sys/bsd_jail.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_racct.h>
#include <sys/bsd_refcount.h>
#include <sys/bsd_sx.h>
#include <sys/bsd_sysent.h>
#include <sys/bsd_namei.h>
#include <sys/bsd_mount.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_syscallsubr.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_vnode.h>

#include <net/if.h>
#include <net/vnet.h>

#include <netinet/in.h>

#ifdef DDB
//#include <ddb/ddb.h>
#ifdef INET6
#include <netinet6/in6_var.h>
#endif /* INET6 */
#endif /* DDB */

//#include <security/mac/mac_framework.h>

/*
 * See if a prison has the specific flag set.
 */
int
prison_flag(struct ucred *cred, unsigned flag)
{

    /* This is an atomic read, so no locking is necessary. */
//    return (cred->cr_prison->pr_flags & flag);
    return 0;
}

#ifdef INET
/*
 * Pass back primary IPv4 address of this jail.
 *
 * If not restricted return success but do not alter the address.  Caller has
 * to make sure to initialize it correctly (e.g. INADDR_ANY).
 *
 * Returns 0 on success, EAFNOSUPPORT if the jail doesn't allow IPv4.
 * Address returned in NBO.
 */
int
prison_get_ip4(struct ucred *cred, struct in_addr *ia)
{
	struct prison *pr;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia != NULL, ("%s: ia is NULL", __func__));

	pr = cred->cr_prison;
	if (!(pr->pr_flags & PR_IP4))
		return (0);
	mtx_lock(&pr->pr_mtx);
	if (!(pr->pr_flags & PR_IP4)) {
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	if (pr->pr_ip4 == NULL) {
		mtx_unlock(&pr->pr_mtx);
		return (EAFNOSUPPORT);
	}

	ia->s_addr = pr->pr_ip4[0].s_addr;
	mtx_unlock(&pr->pr_mtx);
	return (0);
}

/*
 * Return 1 if we should do proper source address selection or are not jailed.
 * We will return 0 if we should bypass source address selection in favour
 * of the primary jail IPv4 address. Only in this case *ia will be updated and
 * returned in NBO.
 * Return EAFNOSUPPORT, in case this jail does not allow IPv4.
 */
int
prison_saddrsel_ip4(struct ucred *cred, struct in_addr *ia)
{
	return 1;
}

/*
 * Return true if pr1 and pr2 have the same IPv4 address restrictions.
 */
int
prison_equal_ip4(struct prison *pr1, struct prison *pr2)
{

    return 1;
}

/*
 * Make sure our (source) address is set to something meaningful to this
 * jail.
 *
 * Returns 0 if jail doesn't restrict IPv4 or if address belongs to jail,
 * EADDRNOTAVAIL if the address doesn't belong, or EAFNOSUPPORT if the jail
 * doesn't allow IPv4.  Address passed in in NBO and returned in NBO.
 */
int
prison_local_ip4(struct ucred *cred, struct in_addr *ia)
{
    #if 0	// runsisi AT hust.edu.cn @2013/11/28
    struct prison *pr;
    struct in_addr ia0;
    int error;

    KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
    KASSERT(ia != NULL, ("%s: ia is NULL", __func__));

    pr = cred->cr_prison;
    if (!(pr->pr_flags & PR_IP4))
        return (0);
    mtx_lock(&pr->pr_mtx);
    if (!(pr->pr_flags & PR_IP4)) {
        mtx_unlock(&pr->pr_mtx);
        return (0);
    }
    if (pr->pr_ip4 == NULL) {
        mtx_unlock(&pr->pr_mtx);
        return (EAFNOSUPPORT);
    }

    ia0.s_addr = ntohl(ia->s_addr);
    if (ia0.s_addr == INADDR_LOOPBACK) {
        ia->s_addr = pr->pr_ip4[0].s_addr;
        mtx_unlock(&pr->pr_mtx);
        return (0);
    }

    if (ia0.s_addr == INADDR_ANY) {
        /*
         * In case there is only 1 IPv4 address, bind directly.
         */
        if (pr->pr_ip4s == 1)
            ia->s_addr = pr->pr_ip4[0].s_addr;
        mtx_unlock(&pr->pr_mtx);
        return (0);
    }

    error = _prison_check_ip4(pr, ia);
    mtx_unlock(&pr->pr_mtx);
    return (error);
    #endif 	// ---------------------- @2013/11/28

    return 0;
}

/*
 * Rewrite destination address in case we will connect to loopback address.
 *
 * Returns 0 on success, EAFNOSUPPORT if the jail doesn't allow IPv4.
 * Address passed in in NBO and returned in NBO.
 */
int
prison_remote_ip4(struct ucred *cred, struct in_addr *ia)
{
	struct prison *pr;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia != NULL, ("%s: ia is NULL", __func__));

	pr = cred->cr_prison;
	if (!(pr->pr_flags & PR_IP4))
		return (0);
	mtx_lock(&pr->pr_mtx);
	if (!(pr->pr_flags & PR_IP4)) {
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	if (pr->pr_ip4 == NULL) {
		mtx_unlock(&pr->pr_mtx);
		return (EAFNOSUPPORT);
	}

	if (ntohl(ia->s_addr) == INADDR_LOOPBACK) {
		ia->s_addr = pr->pr_ip4[0].s_addr;
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}

	/*
	 * Return success because nothing had to be changed.
	 */
	mtx_unlock(&pr->pr_mtx);
	return (0);
}

int
prison_check_ip4(struct ucred *cred, struct in_addr *ia)
{
    #if 0	// runsisi AT hust.edu.cn @2013/11/09
	struct prison *pr;
	int error;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia != NULL, ("%s: ia is NULL", __func__));

	pr = cred->cr_prison;
	if (!(pr->pr_flags & PR_IP4))
		return (0);
	mtx_lock(&pr->pr_mtx);
	if (!(pr->pr_flags & PR_IP4)) {
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	if (pr->pr_ip4 == NULL) {
		mtx_unlock(&pr->pr_mtx);
		return (EAFNOSUPPORT);
	}

	error = _prison_check_ip4(pr, ia);
	mtx_unlock(&pr->pr_mtx);
	return (error);
    #endif 	// ---------------------- @2013/11/09
    return 0;
}
#endif

#ifdef INET6
/*
 * Pass back primary IPv6 address for this jail.
 *
 * If not restricted return success but do not alter the address.  Caller has
 * to make sure to initialize it correctly (e.g. IN6ADDR_ANY_INIT).
 *
 * Returns 0 on success, EAFNOSUPPORT if the jail doesn't allow IPv6.
 */
int
prison_get_ip6(struct ucred *cred, struct in6_addr *ia6)
{
	struct prison *pr;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia6 != NULL, ("%s: ia6 is NULL", __func__));

	pr = cred->cr_prison;
	if (!(pr->pr_flags & PR_IP6))
		return (0);
	mtx_lock(&pr->pr_mtx);
	if (!(pr->pr_flags & PR_IP6)) {
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	if (pr->pr_ip6 == NULL) {
		mtx_unlock(&pr->pr_mtx);
		return (EAFNOSUPPORT);
	}

	bcopy(&pr->pr_ip6[0], ia6, sizeof(struct in6_addr));
	mtx_unlock(&pr->pr_mtx);
	return (0);
}

/*
 * Return 1 if we should do proper source address selection or are not jailed.
 * We will return 0 if we should bypass source address selection in favour
 * of the primary jail IPv6 address. Only in this case *ia will be updated and
 * returned in NBO.
 * Return EAFNOSUPPORT, in case this jail does not allow IPv6.
 */
int
prison_saddrsel_ip6(struct ucred *cred, struct in6_addr *ia6)
{
	struct prison *pr;
	struct in6_addr lia6;
	int error;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia6 != NULL, ("%s: ia6 is NULL", __func__));

	if (!jailed(cred))
		return (1);

	pr = cred->cr_prison;
	if (pr->pr_flags & PR_IP6_SADDRSEL)
		return (1);

	lia6 = in6addr_any;
	error = prison_get_ip6(cred, &lia6);
	if (error)
		return (error);
	if (IN6_IS_ADDR_UNSPECIFIED(&lia6))
		return (1);

	bcopy(&lia6, ia6, sizeof(struct in6_addr));
	return (0);
}

/*
 * Return true if pr1 and pr2 have the same IPv6 address restrictions.
 */
int
prison_equal_ip6(struct prison *pr1, struct prison *pr2)
{

    return 1;
}

/*
 * Make sure our (source) address is set to something meaningful to this jail.
 *
 * v6only should be set based on (inp->inp_flags & IN6P_IPV6_V6ONLY != 0)
 * when needed while binding.
 *
 * Returns 0 if jail doesn't restrict IPv6 or if address belongs to jail,
 * EADDRNOTAVAIL if the address doesn't belong, or EAFNOSUPPORT if the jail
 * doesn't allow IPv6.
 */
int
prison_local_ip6(struct ucred *cred, struct in6_addr *ia6, int v6only)
{
	struct prison *pr;
	int error;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia6 != NULL, ("%s: ia6 is NULL", __func__));

	pr = cred->cr_prison;
	if (!(pr->pr_flags & PR_IP6))
		return (0);
	mtx_lock(&pr->pr_mtx);
	if (!(pr->pr_flags & PR_IP6)) {
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	if (pr->pr_ip6 == NULL) {
		mtx_unlock(&pr->pr_mtx);
		return (EAFNOSUPPORT);
	}

	if (IN6_IS_ADDR_LOOPBACK(ia6)) {
		bcopy(&pr->pr_ip6[0], ia6, sizeof(struct in6_addr));
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}

	if (IN6_IS_ADDR_UNSPECIFIED(ia6)) {
		/*
		 * In case there is only 1 IPv6 address, and v6only is true,
		 * then bind directly.
		 */
		if (v6only != 0 && pr->pr_ip6s == 1)
			bcopy(&pr->pr_ip6[0], ia6, sizeof(struct in6_addr));
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}

	error = _prison_check_ip6(pr, ia6);
	mtx_unlock(&pr->pr_mtx);
	return (error);
}

/*
 * Rewrite destination address in case we will connect to loopback address.
 *
 * Returns 0 on success, EAFNOSUPPORT if the jail doesn't allow IPv6.
 */
int
prison_remote_ip6(struct ucred *cred, struct in6_addr *ia6)
{
	struct prison *pr;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia6 != NULL, ("%s: ia6 is NULL", __func__));

	pr = cred->cr_prison;
	if (!(pr->pr_flags & PR_IP6))
		return (0);
	mtx_lock(&pr->pr_mtx);
	if (!(pr->pr_flags & PR_IP6)) {
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	if (pr->pr_ip6 == NULL) {
		mtx_unlock(&pr->pr_mtx);
		return (EAFNOSUPPORT);
	}

	if (IN6_IS_ADDR_LOOPBACK(ia6)) {
		bcopy(&pr->pr_ip6[0], ia6, sizeof(struct in6_addr));
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}

	/*
	 * Return success because nothing had to be changed.
	 */
	mtx_unlock(&pr->pr_mtx);
	return (0);
}

int
prison_check_ip6(struct ucred *cred, struct in6_addr *ia6)
{
	struct prison *pr;
	int error;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia6 != NULL, ("%s: ia6 is NULL", __func__));

	pr = cred->cr_prison;
	if (!(pr->pr_flags & PR_IP6))
		return (0);
	mtx_lock(&pr->pr_mtx);
	if (!(pr->pr_flags & PR_IP6)) {
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	if (pr->pr_ip6 == NULL) {
		mtx_unlock(&pr->pr_mtx);
		return (EAFNOSUPPORT);
	}

	error = _prison_check_ip6(pr, ia6);
	mtx_unlock(&pr->pr_mtx);
	return (error);
}
#endif

/*
 * Check if a jail supports the given address family.
 *
 * Returns 0 if not jailed or the address family is supported, EAFNOSUPPORT
 * if not.
 */
int
prison_check_af(struct ucred *cred, int af)
{
	return 0;
}

/*
 * Check if given address belongs to the jail referenced by cred (wrapper to
 * prison_check_ip[46]).
 *
 * Returns 0 if jail doesn't restrict the address family or if address belongs
 * to jail, EADDRNOTAVAIL if the address doesn't belong, or EAFNOSUPPORT if
 * the jail doesn't allow the address family.  IPv4 Address passed in in NBO.
 */
int
prison_if(struct ucred *cred, struct sockaddr *sa)
{
#if 0	// runsisi AT hust.edu.cn @2013/11/28
#ifdef INET
    struct sockaddr_in *sai;
#endif
#ifdef INET6
    struct sockaddr_in6 *sai6;
#endif
    int error;

    KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
    KASSERT(sa != NULL, ("%s: sa is NULL", __func__));

#ifdef VIMAGE
    if (prison_owns_vnet(cred))
        return (0);
#endif

    error = 0;
    switch (sa->sa_family)
    {
#ifdef INET
    case AF_INET:
        sai = (struct sockaddr_in *)sa;
        error = prison_check_ip4(cred, &sai->sin_addr);
        break;
#endif
#ifdef INET6
    case AF_INET6:
        sai6 = (struct sockaddr_in6 *)sa;
        error = prison_check_ip6(cred, &sai6->sin6_addr);
        break;
#endif
    default:
        if (!(cred->cr_prison->pr_allow & PR_ALLOW_SOCKET_AF))
            error = EAFNOSUPPORT;
    }
    return (error);
#endif 	// ---------------------- @2013/11/28

    return 0;
}
