/*-
 * Copyright (c) 1982, 1986, 1988, 1993
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
 *	@(#)ip_input.c	8.2 (Berkeley) 1/4/94
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/netinet/ip_input.c 243586 2012-11-27 01:59:51Z ae $");

#include "opt_bootp.h"
#include "opt_ipfw.h"
#include "opt_ipstealth.h"
#include "opt_ipsec.h"
#include "opt_route.h"

#include <stdio.h>
#include <string.h>
#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_mbuf.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_domain.h>
#include <sys/bsd_protosw.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_time.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_rwlock.h>
#include <sys/bsd_syslog.h>
#include <sys/bsd_sysctl.h>

#include <net/pfil.h>
#include <net/bsd_if.h>
#include <net/if_types.h>
#include <net/if_var.h>
#include <net/if_dl.h>
#include <net/bsd_route.h>
#include <net/netisr.h>
#include <net/vnet.h>
#include <net/flowtable.h>

#include <netinet/bsd_in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/bsd_ip.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
#include <netinet/ip_fw.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip_options.h>
#include <machine/bsd_in_cksum.h>
#include <netinet/ip_carp.h>
#ifdef IPSEC
#include <netinet/ip_ipsec.h>
#endif /* IPSEC */

#include <sys/bsd_socketvar.h>

//#include <security/mac/mac_framework.h>

u_char inetctlerrmap[PRC_NCMDS] = {
	0,		0,		0,		0,
	0,		BSD_EMSGSIZE,	BSD_EHOSTDOWN,	BSD_EHOSTUNREACH,
	BSD_EHOSTUNREACH,	BSD_EHOSTUNREACH,	BSD_ECONNREFUSED,	BSD_ECONNREFUSED,
	BSD_EMSGSIZE,	BSD_EHOSTUNREACH,	0,		0,
	0,		0,		BSD_EHOSTUNREACH,	0,
	BSD_ENOPROTOOPT,	BSD_ECONNREFUSED
};
