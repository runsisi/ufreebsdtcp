/*-
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)in_proto.c	8.2 (Berkeley) 2/9/95
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/netinet/in_proto.c 230868 2012-02-01 15:57:49Z glebius $");

#include "opt_ipx.h"
#include "opt_mrouting.h"
#include "opt_ipsec.h"
#include "opt_inet.h"
#include "opt_inet6.h"
#include "opt_sctp.h"
#include "opt_mpath.h"

#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_domain.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_protosw.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_sysctl.h>

/*
 * While this file provides the domain and protocol switch tables for IPv4, it
 * also provides the sysctl node declarations for net.inet.* often shared with
 * IPv6 for common features or by upper layer protocols.  In case of no IPv4
 * support compile out everything but these sysctl nodes.
 */
#ifdef INET
#include <net/bsd_if.h>
#include <net/bsd_route.h>
#ifdef RADIX_MPATH
#include <net/radix_mpath.h>
#endif
#include <net/vnet.h>
#endif /* INET */

#if defined(INET) || defined(INET6)
#include <netinet/bsd_in.h>
#endif

#ifdef INET
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/bsd_ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/igmp_var.h>
#include <netinet/bsd_tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/bsd_udp.h>
#include <netinet/udp_var.h>
#include <netinet/ip_encap.h>

/*
 * TCP/IP protocol family: IP, ICMP, UDP, TCP.
 */

#if 0	// runsisi AT hust.edu.cn @2013/11/04
static struct pr_usrreqs nousrreqs;
#endif 	// ---------------------- @2013/11/04

#ifdef IPSEC
#include <netipsec/ipsec.h>
#endif /* IPSEC */

#ifdef SCTP
#include <netinet/in_pcb.h>
#include <netinet/sctp_pcb.h>
#include <netinet/sctp.h>
#include <netinet/sctp_var.h>
#endif /* SCTP */

FEATURE(inet, "Internet Protocol version 4");

extern	struct bsd_domain inetdomain;

/* Spacer for loadable protocols. */
#define IPPROTOSPACER   			\
{						\
	.pr_domain =		&inetdomain,	\
	.pr_protocol =		PROTO_SPACER,	\
	.pr_usrreqs =		&nousrreqs	\
}

struct bsd_protosw bsd_inetsw[] = {
#if 0	// runsisi AT hust.edu.cn @2013/11/04
{
    .pr_type =		0,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_IP,
    .pr_init =		ip_init,
#ifdef VIMAGE
    .pr_destroy =		ip_destroy,
#endif
    .pr_slowtimo =		ip_slowtimo,
    .pr_drain =		ip_drain,
    .pr_usrreqs =		&nousrreqs
},
{
    .pr_type =		BSD_SOCK_DGRAM,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_UDP,
    .pr_flags =		PR_ATOMIC|PR_ADDR,
    .pr_input =		udp_input,
    .pr_ctlinput =		udp_ctlinput,
    .pr_ctloutput =		udp_ctloutput,
    .pr_init =		udp_init,
#ifdef VIMAGE
    .pr_destroy =		udp_destroy,
#endif
    .pr_usrreqs =		&udp_usrreqs
},
#endif 	// ---------------------- @2013/11/04
{
	.pr_type =		BSD_SOCK_STREAM,
	.pr_domain =		&inetdomain,
	.pr_protocol =		BSD_IPPROTO_TCP,
	.pr_flags =		PR_CONNREQUIRED|PR_IMPLOPCL|PR_WANTRCVD,
	.pr_input =		tcp_input,
	.pr_ctlinput =		tcp_ctlinput,
	.pr_ctloutput =		tcp_ctloutput,
	.pr_init =		tcp_init,
#ifdef VIMAGE
	.pr_destroy =		tcp_destroy,
#endif
	.pr_slowtimo =		tcp_slowtimo,
	.pr_drain =		tcp_drain,
	.pr_usrreqs =		&tcp_usrreqs
},
#if 0	// runsisi AT hust.edu.cn @2013/11/04
#ifdef SCTP
{ 
    .pr_type =		SOCK_SEQPACKET,
    .pr_domain =		&inetdomain,
    .pr_protocol =		IPPROTO_SCTP,
    .pr_flags =		PR_WANTRCVD,
    .pr_input =		sctp_input,
    .pr_ctlinput =		sctp_ctlinput,
    .pr_ctloutput =		sctp_ctloutput,
    .pr_init =		sctp_init,
#ifdef VIMAGE
    .pr_destroy =		sctp_finish,
#endif
    .pr_drain =		sctp_drain,
    .pr_usrreqs =		&sctp_usrreqs
},
{ 
    .pr_type =		SOCK_STREAM,
    .pr_domain =		&inetdomain,
    .pr_protocol =		IPPROTO_SCTP,
    .pr_flags =		PR_WANTRCVD,
    .pr_input =		sctp_input,
    .pr_ctlinput =		sctp_ctlinput,
    .pr_ctloutput =		sctp_ctloutput,
    .pr_drain =		sctp_drain,
    .pr_usrreqs =		&sctp_usrreqs
},
#endif /* SCTP */
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_RAW,
    .pr_flags =		PR_ATOMIC|PR_ADDR,
    .pr_input =		rip_input,
    .pr_ctlinput =		rip_ctlinput,
    .pr_ctloutput =		rip_ctloutput,
    .pr_usrreqs =		&rip_usrreqs
},
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_ICMP,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		icmp_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_usrreqs =		&rip_usrreqs
},
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_IGMP,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		igmp_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_fasttimo =		igmp_fasttimo,
    .pr_slowtimo =		igmp_slowtimo,
    .pr_usrreqs =		&rip_usrreqs
},
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_RSVP,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		rsvp_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_usrreqs =		&rip_usrreqs
},
#ifdef IPSEC
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		IPPROTO_AH,
    .pr_flags =		PR_ATOMIC|PR_ADDR,
    .pr_input =		ah4_input,
    .pr_ctlinput =		ah4_ctlinput,
    .pr_usrreqs =		&nousrreqs
},
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		IPPROTO_ESP,
    .pr_flags =		PR_ATOMIC|PR_ADDR,
    .pr_input =		esp4_input,
    .pr_ctlinput =		esp4_ctlinput,
    .pr_usrreqs =		&nousrreqs
},
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		IPPROTO_IPCOMP,
    .pr_flags =		PR_ATOMIC|PR_ADDR,
    .pr_input =		ipcomp4_input,
    .pr_usrreqs =		&nousrreqs
},
#endif /* IPSEC */
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_IPV4,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		encap4_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_init =		encap_init,
    .pr_usrreqs =		&rip_usrreqs
},
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_MOBILE,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		encap4_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_init =		encap_init,
    .pr_usrreqs =		&rip_usrreqs
},
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_ETHERIP,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		encap4_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_init =		encap_init,
    .pr_usrreqs =		&rip_usrreqs
},
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_GRE,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		encap4_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_init =		encap_init,
    .pr_usrreqs =		&rip_usrreqs
},
# ifdef INET6
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_IPV6,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		encap4_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_init =		encap_init,
    .pr_usrreqs =		&rip_usrreqs
},
#endif
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_protocol =		BSD_IPPROTO_PIM,
    .pr_flags =		PR_ATOMIC|PR_ADDR|PR_LASTHDR,
    .pr_input =		encap4_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_usrreqs =		&rip_usrreqs
},
/* Spacer n-times for loadable protocols. */
IPPROTOSPACER,
IPPROTOSPACER,
IPPROTOSPACER,
IPPROTOSPACER,
IPPROTOSPACER,
IPPROTOSPACER,
IPPROTOSPACER,
IPPROTOSPACER,
/* raw wildcard */
{
    .pr_type =		BSD_SOCK_RAW,
    .pr_domain =		&inetdomain,
    .pr_flags =		PR_ATOMIC|PR_ADDR,
    .pr_input =		rip_input,
    .pr_ctloutput =		rip_ctloutput,
    .pr_init =		rip_init,
#ifdef VIMAGE
    .pr_destroy =		rip_destroy,
#endif
    .pr_usrreqs =		&rip_usrreqs
},
#endif 	// ---------------------- @2013/11/04
};

#if 0	// runsisi AT hust.edu.cn @2013/11/04
extern int in_inithead(void **, int);
extern int in_detachhead(void **, int);
#endif 	// ---------------------- @2013/11/04

struct bsd_domain inetdomain = {
	.dom_family =		BSD_AF_INET,
	.dom_name =		"internet",
	.dom_protosw =		bsd_inetsw,
	.dom_protoswNPROTOSW =	&bsd_inetsw[sizeof(bsd_inetsw)/sizeof(bsd_inetsw[0])],
#if 0	// runsisi AT hust.edu.cn @2013/11/04
#ifdef RADIX_MPATH
    .dom_rtattach =		rn4_mpath_inithead,
#else
    .dom_rtattach =		in_inithead,
#endif
#ifdef VIMAGE
    .dom_rtdetach =		in_detachhead,
#endif
    .dom_rtoffset =		32,
    .dom_maxrtkey =		sizeof(struct bsd_sockaddr_in),
    .dom_ifattach =		in_domifattach,
    .dom_ifdetach =		in_domifdetach
#endif 	// ---------------------- @2013/11/04
};

VNET_DOMAIN_SET(inet);
#endif /* INET */

#if 0	// runsisi AT hust.edu.cn @2013/11/04
SYSCTL_NODE(_net,      BSD_PF_INET,		inet,	CTLFLAG_RW, 0,
    "Internet Family");

SYSCTL_NODE(_net_inet, BSD_IPPROTO_IP,	ip,	CTLFLAG_RW, 0,	"IP");
SYSCTL_NODE(_net_inet, BSD_IPPROTO_ICMP,	icmp,	CTLFLAG_RW, 0,	"ICMP");
SYSCTL_NODE(_net_inet, BSD_IPPROTO_UDP,	udp,	CTLFLAG_RW, 0,	"UDP");
SYSCTL_NODE(_net_inet, BSD_IPPROTO_TCP,	tcp,	CTLFLAG_RW, 0,	"TCP");
#ifdef SCTP
SYSCTL_NODE(_net_inet, BSD_IPPROTO_SCTP,	sctp,	CTLFLAG_RW, 0,	"SCTP");
#endif
SYSCTL_NODE(_net_inet, BSD_IPPROTO_IGMP,	igmp,	CTLFLAG_RW, 0,	"IGMP");
#ifdef IPSEC
/* XXX no protocol # to use, pick something "reserved" */
SYSCTL_NODE(_net_inet, 253,		ipsec,	CTLFLAG_RW, 0,	"IPSEC");
SYSCTL_NODE(_net_inet, BSD_IPPROTO_AH,	ah,	CTLFLAG_RW, 0,	"AH");
SYSCTL_NODE(_net_inet, BSD_IPPROTO_ESP,	esp,	CTLFLAG_RW, 0,	"ESP");
SYSCTL_NODE(_net_inet, BSD_IPPROTO_IPCOMP,	ipcomp,	CTLFLAG_RW, 0,	"IPCOMP");
SYSCTL_NODE(_net_inet, BSD_IPPROTO_IPIP,	ipip,	CTLFLAG_RW, 0,	"IPIP");
#endif /* IPSEC */
SYSCTL_NODE(_net_inet, BSD_IPPROTO_RAW,	raw,	CTLFLAG_RW, 0,	"RAW");
#endif 	// ---------------------- @2013/11/04
