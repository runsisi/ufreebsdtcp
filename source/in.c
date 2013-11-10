/*-
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (C) 2001 WIDE Project.  All rights reserved.
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
 *	@(#)in.c	8.4 (Berkeley) 1/9/95
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/netinet/in.c 252555 2013-07-03 09:25:29Z np $");

#include "opt_mpath.h"

#include <stdio.h>
#include <string.h>

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_sockio.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_priv.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_jail.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_syslog.h>

#include <net/bsd_if.h>
#include <net/if_var.h>
#include <net/if_arp.h>
#include <net/if_dl.h>
#include <net/if_llatbl.h>
#include <net/if_types.h>
#include <net/bsd_route.h>
#include <net/vnet.h>

#include <netinet/bsd_in.h>
#include <netinet/in_var.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
#include <netinet/igmp_var.h>
#include <netinet/bsd_udp.h>
#include <netinet/udp_var.h>

/*
 * Return 1 if an internet address is for a ``local'' host
 * (one to which we have a connection).
 */
int
in_localaddr(struct bsd_in_addr in)
{
    #if 0	// runsisi AT hust.edu.cn @2013/11/06
    register u_long i = bsd_ntohl(in.s_addr);
    register struct in_ifaddr *ia;

    IN_IFADDR_RLOCK();
    BSD_TAILQ_FOREACH(ia, &V_in_ifaddrhead, ia_link) {
        if ((i & ia->ia_subnetmask) == ia->ia_subnet) {
            IN_IFADDR_RUNLOCK();
            return (1);
        }
    }
    IN_IFADDR_RUNLOCK();
    #endif 	// ---------------------- @2013/11/06
	return (0);
}

/*
 * Return 1 if an internet address is for the local host and configured
 * on one of its interfaces.
 */
int
in_localip(struct bsd_in_addr in)
{
    #if 0	// runsisi AT hust.edu.cn @2013/11/06
    struct in_ifaddr *ia;

    IN_IFADDR_RLOCK();
    BSD_LIST_FOREACH(ia, INADDR_HASH(in.s_addr), ia_hash) {
        if (IA_SIN(ia)->sin_addr.s_addr == in.s_addr) {
            IN_IFADDR_RUNLOCK();
            return (1);
        }
    }
    IN_IFADDR_RUNLOCK();
    #endif 	// ---------------------- @2013/11/06
	return (0);
}

/*
 * Generic internet control operations (ioctl's).
 *
 * ifp is NULL if not an interface-specific ioctl.
 */
/* ARGSUSED */
int
in_control(struct bsd_socket *so, u_long cmd, caddr_t data, struct ifnet *ifp,
    struct thread *td)
{
    return 0;
}

/*
 * Determine whether an IP address is in a reserved set of addresses
 * that may not be forwarded, or whether datagrams to that destination
 * may be forwarded.
 */
int
in_canforward(struct bsd_in_addr in)
{
	register u_long i = bsd_ntohl(in.s_addr);
	register u_long net;

	if (BSD_IN_EXPERIMENTAL(i) || BSD_IN_MULTICAST(i) || BSD_IN_LINKLOCAL(i))
		return (0);
	if (BSD_IN_CLASSA(i)) {
		net = i & BSD_IN_CLASSA_NET;
		if (net == 0 || net == (BSD_IN_LOOPBACKNET << BSD_IN_CLASSA_NSHIFT))
			return (0);
	}
	return (1);
}

/*
 * Return 1 if the address might be a local broadcast address.
 */
int
in_broadcast(struct bsd_in_addr in, struct ifnet *ifp)
{
    #if 0	// runsisi AT hust.edu.cn @2013/11/06
    register struct ifaddr *ifa;
    u_long t;
    #endif 	// ---------------------- @2013/11/06

	if (in.s_addr == BSD_INADDR_BROADCAST ||
	    in.s_addr == BSD_INADDR_ANY)
		return (1);
	if ((ifp->if_flags & IFF_BROADCAST) == 0)
		return (0);
    #if 0	// runsisi AT hust.edu.cn @2013/11/06
    t = bsd_ntohl(in.s_addr);
    /*
     * Look through the list of addresses for a match
     * with a broadcast address.
     */
    #define ia ((struct in_ifaddr *)ifa)
    BSD_TAILQ_FOREACH(ifa, &ifp->if_addrhead, ifa_link)
        if (ifa->ifa_addr->sa_family == BSD_AF_INET &&
            (in.s_addr == ia->ia_broadaddr.sin_addr.s_addr ||
             /*
              * Check for old-style (host 0) broadcast, but
              * taking into account that RFC 3021 obsoletes it.
              */
            (ia->ia_subnetmask != BSD_IN_RFC3021_MASK &&
            t == ia->ia_subnet)) &&
             /*
              * Check for an all one subnetmask. These
              * only exist when an interface gets a secondary
              * address.
              */
            ia->ia_subnetmask != (u_long)0xffffffff)
                return (1);
    return (0);
    #undef ia
    #endif 	// ---------------------- @2013/11/06
    return 0;
}
