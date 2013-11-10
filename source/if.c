/*-
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)if.c	8.5 (Berkeley) 1/9/95
 * $FreeBSD: release/9.2.0/sys/net/if.c 255444 2013-09-10 10:08:20Z des $
 */

#include "opt_compat.h"
#include "opt_inet6.h"
#include "opt_inet.h"

#include <string.h>
#include <stdio.h>

#include <sys/bsd_param.h>
#include <sys/bsd_types.h>
#include <sys/bsd_conf.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_sbuf.h>
#include <sys/bsd_bus.h>
#include <sys/bsd_mbuf.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_priv.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_socketvar.h>
#include <sys/bsd_protosw.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_refcount.h>
#include <sys/bsd_module.h>
#include <sys/bsd_rwlock.h>
#include <sys/bsd_sockio.h>
#include <sys/bsd_syslog.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_taskqueue.h>
#include <sys/bsd_domain.h>
#include <sys/bsd_jail.h>
#include <sys/bsd_priv.h>

#include <machine/bsd_stdarg.h>
#include <vm/uma.h>

#include <net/bsd_if.h>
#include <net/if_arp.h>
#include <net/if_clone.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <net/if_var.h>
#include <net/radix.h>
#include <net/bsd_route.h>
#include <net/vnet.h>

#if defined(INET) || defined(INET6)
#include <netinet/bsd_in.h>
#include <netinet/in_var.h>
#include <netinet/bsd_ip.h>
#include <netinet/ip_carp.h>
#ifdef INET
#include <netinet/if_ether.h>
#endif /* INET */
#ifdef INET6
#include <netinet6/in6_var.h>
#include <netinet6/in6_ifattach.h>
#endif /* INET6 */
#endif /* INET || INET6 */

//#include <security/mac/mac_framework.h>

#ifdef COMPAT_FREEBSD32
#include <sys/mount.h>
#include <compat/freebsd32/freebsd32.h>
#endif

/*
 * Locate an interface based on a complete address.
 */

struct ifaddr *
ifa_ifwithaddr(struct bsd_sockaddr *addr)
{

	return NULL;
}

int
ifa_ifwithaddr_check(struct bsd_sockaddr *addr)
{

	return 1;
}
