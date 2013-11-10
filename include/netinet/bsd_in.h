/*-
 * Copyright (c) 1982, 1986, 1990, 1993
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
 *	@(#)in.h	8.3 (Berkeley) 1/3/94
 * $FreeBSD: release/9.2.0/sys/netinet/in.h 250228 2013-05-04 00:31:41Z cperciva $
 */

#ifndef _BSD_NETINET_IN_H_
#define	_BSD_NETINET_IN_H_

#include <sys/bsd_cdefs.h>
#include <sys/_bsd_types.h>
#include <machine/bsd_endian.h>

/* Protocols common to RFC 1700, POSIX, and X/Open. */
#define	BSD_IPPROTO_IP		0		/* dummy for IP */
#define	BSD_IPPROTO_ICMP		1		/* control message protocol */
#define	BSD_IPPROTO_TCP		6		/* tcp */
#define	BSD_IPPROTO_UDP		17		/* user datagram protocol */

#define	BSD_INADDR_ANY		(bsd_uint32_t)0x00000000
#define	BSD_INADDR_BROADCAST	(bsd_uint32_t)0xffffffff	/* must be masked */

#ifndef _BSD_UINT8_T_DECLARED
typedef	__bsd_uint8_t		bsd_uint8_t;
#define	_BSD_UINT8_T_DECLARED
#endif

#ifndef _BSD_UINT16_T_DECLARED
typedef	__bsd_uint16_t		uint16_t;
#define	_BSD_UINT16_T_DECLARED
#endif

#ifndef _BSD_UINT32_T_DECLARED
typedef	__bsd_uint32_t		bsd_uint32_t;
#define	_BSD_UINT32_T_DECLARED
#endif

#ifndef _BSD_IN_ADDR_T_DECLARED
typedef	bsd_uint32_t		bsd_in_addr_t;
#define	_BSD_IN_ADDR_T_DECLARED
#endif

#ifndef _BSD_IN_PORT_T_DECLARED
typedef	bsd_uint16_t		bsd_in_port_t;
#define	_BSD_IN_PORT_T_DECLARED
#endif

#ifndef _BSD_SA_FAMILY_T_DECLARED
typedef	__bsd_sa_family_t		bsd_sa_family_t;
#define	_BSD_SA_FAMILY_T_DECLARED
#endif

/* Internet address (a structure for historical reasons). */
#ifndef	_BSD_STRUCT_IN_ADDR_DECLARED
struct bsd_in_addr {
	bsd_in_addr_t s_addr;
};
#define	_BSD_STRUCT_IN_ADDR_DECLARED
#endif

#ifndef	_BSD_SOCKLEN_T_DECLARED
typedef	__bsd_socklen_t	bsd_socklen_t;
#define	_BSD_SOCKLEN_T_DECLARED
#endif

#include <sys/_bsd_sockaddr_storage.h>

/* Socket address, internet style. */
struct bsd_sockaddr_in {
	bsd_uint8_t	sin_len;
	bsd_sa_family_t	sin_family;
	bsd_in_port_t	sin_port;
	struct	bsd_in_addr sin_addr;
	char	sin_zero[8];
};

#if !defined(_KERNEL) && __BSD_VISIBLE

#ifndef _BYTEORDER_PROTOTYPED
#define	_BYTEORDER_PROTOTYPED
__BEGIN_DECLS
bsd_uint32_t	bsd_htonl(bsd_uint32_t);
bsd_uint16_t	bsd_htons(uint16_t);
bsd_uint32_t	bsd_ntohl(bsd_uint32_t);
bsd_uint16_t	bsd_ntohs(uint16_t);
__END_DECLS
#endif

#ifndef _BYTEORDER_FUNC_DEFINED
#define	_BYTEORDER_FUNC_DEFINED
#define	bsd_htonl(x)	__htonl(x)
#define	bsd_htons(x)	__htons(x)
#define	bsd_ntohl(x)	__ntohl(x)
#define	bsd_ntohs(x)	__ntohs(x)
#endif

#endif /* !_KERNEL && __BSD_VISIBLE */

#if __POSIX_VISIBLE >= 200112
#define	BSD_IPPROTO_IPV6		41		/* IP6 header */
#define	BSD_IPPROTO_RAW		255		/* raw IP packet */
#define	BSD_INET_ADDRSTRLEN		16
#endif

#if __BSD_VISIBLE
/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981, and numerous additions.
 */

/*
 * Protocols (RFC 1700)
 */
#define	BSD_IPPROTO_HOPOPTS		0		/* IP6 hop-by-hop options */
#define	BSD_IPPROTO_IGMP		2		/* group mgmt protocol */
#define	BSD_IPPROTO_GGP		3		/* gateway^2 (deprecated) */
#define	BSD_IPPROTO_IPV4		4		/* IPv4 encapsulation */
#define	BSD_IPPROTO_IPIP		IPPROTO_IPV4	/* for compatibility */
#define	BSD_IPPROTO_ST		7		/* Stream protocol II */
#define	BSD_IPPROTO_EGP		8		/* exterior gateway protocol */
#define	BSD_IPPROTO_PIGP		9		/* private interior gateway */
#define	BSD_IPPROTO_RCCMON		10		/* BBN RCC Monitoring */
#define	BSD_IPPROTO_NVPII		11		/* network voice protocol*/
#define	BSD_IPPROTO_PUP		12		/* pup */
#define	BSD_IPPROTO_ARGUS		13		/* Argus */
#define	BSD_IPPROTO_EMCON		14		/* EMCON */
#define	BSD_IPPROTO_XNET		15		/* Cross Net Debugger */
#define	BSD_IPPROTO_CHAOS		16		/* Chaos*/
#define	BSD_IPPROTO_MUX		18		/* Multiplexing */
#define	BSD_IPPROTO_MEAS		19		/* DCN Measurement Subsystems */
#define	BSD_IPPROTO_HMP		20		/* Host Monitoring */
#define	BSD_IPPROTO_PRM		21		/* Packet Radio Measurement */
#define	BSD_IPPROTO_IDP		22		/* xns idp */
#define	BSD_IPPROTO_TRUNK1		23		/* Trunk-1 */
#define	BSD_IPPROTO_TRUNK2		24		/* Trunk-2 */
#define	BSD_IPPROTO_LEAF1		25		/* Leaf-1 */
#define	BSD_IPPROTO_LEAF2		26		/* Leaf-2 */
#define	BSD_IPPROTO_RDP		27		/* Reliable Data */
#define	BSD_IPPROTO_IRTP		28		/* Reliable Transaction */
#define	BSD_IPPROTO_TP		29		/* tp-4 w/ class negotiation */
#define	BSD_IPPROTO_BLT		30		/* Bulk Data Transfer */
#define	BSD_IPPROTO_NSP		31		/* Network Services */
#define	BSD_IPPROTO_INP		32		/* Merit Internodal */
#define	BSD_IPPROTO_SEP		33		/* Sequential Exchange */
#define	BSD_IPPROTO_3PC		34		/* Third Party Connect */
#define	BSD_IPPROTO_IDPR		35		/* InterDomain Policy Routing */
#define	BSD_IPPROTO_XTP		36		/* XTP */
#define	BSD_IPPROTO_DDP		37		/* Datagram Delivery */
#define	BSD_IPPROTO_CMTP		38		/* Control Message Transport */
#define	BSD_IPPROTO_TPXX		39		/* TP++ Transport */
#define	BSD_IPPROTO_IL		40		/* IL transport protocol */
#define	BSD_IPPROTO_SDRP		42		/* Source Demand Routing */
#define	BSD_IPPROTO_ROUTING		43		/* IP6 routing header */
#define	BSD_IPPROTO_FRAGMENT	44		/* IP6 fragmentation header */
#define	BSD_IPPROTO_IDRP		45		/* InterDomain Routing*/
#define	BSD_IPPROTO_RSVP		46		/* resource reservation */
#define	BSD_IPPROTO_GRE		47		/* General Routing Encap. */
#define	BSD_IPPROTO_MHRP		48		/* Mobile Host Routing */
#define	BSD_IPPROTO_BHA		49		/* BHA */
#define	BSD_IPPROTO_ESP		50		/* IP6 Encap Sec. Payload */
#define	BSD_IPPROTO_AH		51		/* IP6 Auth Header */
#define	BSD_IPPROTO_INLSP		52		/* Integ. Net Layer Security */
#define	BSD_IPPROTO_SWIPE		53		/* IP with encryption */
#define	BSD_IPPROTO_NHRP		54		/* Next Hop Resolution */
#define	BSD_IPPROTO_MOBILE		55		/* IP Mobility */
#define	BSD_IPPROTO_TLSP		56		/* Transport Layer Security */
#define	BSD_IPPROTO_SKIP		57		/* SKIP */
#define	BSD_IPPROTO_ICMPV6		58		/* ICMP6 */
#define	BSD_IPPROTO_NONE		59		/* IP6 no next header */
#define	BSD_IPPROTO_DSTOPTS		60		/* IP6 destination option */
#define	BSD_IPPROTO_AHIP		61		/* any host internal protocol */
#define	BSD_IPPROTO_CFTP		62		/* CFTP */
#define	BSD_IPPROTO_HELLO		63		/* "hello" routing protocol */
#define	BSD_IPPROTO_SATEXPAK	64		/* SATNET/Backroom EXPAK */
#define	BSD_IPPROTO_KRYPTOLAN	65		/* Kryptolan */
#define	BSD_IPPROTO_RVD		66		/* Remote Virtual Disk */
#define	BSD_IPPROTO_IPPC		67		/* Pluribus Packet Core */
#define	BSD_IPPROTO_ADFS		68		/* Any distributed FS */
#define	BSD_IPPROTO_SATMON		69		/* Satnet Monitoring */
#define	BSD_IPPROTO_VISA		70		/* VISA Protocol */
#define	BSD_IPPROTO_IPCV		71		/* Packet Core Utility */
#define	BSD_IPPROTO_CPNX		72		/* Comp. Prot. Net. Executive */
#define	BSD_IPPROTO_CPHB		73		/* Comp. Prot. HeartBeat */
#define	BSD_IPPROTO_WSN		74		/* Wang Span Network */
#define	BSD_IPPROTO_PVP		75		/* Packet Video Protocol */
#define	BSD_IPPROTO_BRSATMON	76		/* BackRoom SATNET Monitoring */
#define	BSD_IPPROTO_ND		77		/* Sun net disk proto (temp.) */
#define	BSD_IPPROTO_WBMON		78		/* WIDEBAND Monitoring */
#define	BSD_IPPROTO_WBEXPAK		79		/* WIDEBAND EXPAK */
#define	BSD_IPPROTO_EON		80		/* ISO cnlp */
#define	BSD_IPPROTO_VMTP		81		/* VMTP */
#define	BSD_IPPROTO_SVMTP		82		/* Secure VMTP */
#define	BSD_IPPROTO_VINES		83		/* Banyon VINES */
#define	BSD_IPPROTO_TTP		84		/* TTP */
#define	BSD_IPPROTO_IGP		85		/* NSFNET-IGP */
#define	BSD_IPPROTO_DGP		86		/* dissimilar gateway prot. */
#define	BSD_IPPROTO_TCF		87		/* TCF */
#define	BSD_IPPROTO_IGRP		88		/* Cisco/GXS IGRP */
#define	BSD_IPPROTO_OSPFIGP		89		/* OSPFIGP */
#define	BSD_IPPROTO_SRPC		90		/* Strite RPC protocol */
#define	BSD_IPPROTO_LARP		91		/* Locus Address Resoloution */
#define	BSD_IPPROTO_MTP		92		/* Multicast Transport */
#define	BSD_IPPROTO_AX25		93		/* AX.25 Frames */
#define	BSD_IPPROTO_IPEIP		94		/* IP encapsulated in IP */
#define	BSD_IPPROTO_MICP		95		/* Mobile Int.ing control */
#define	BSD_IPPROTO_SCCSP		96		/* Semaphore Comm. security */
#define	BSD_IPPROTO_ETHERIP		97		/* Ethernet IP encapsulation */
#define	BSD_IPPROTO_ENCAP		98		/* encapsulation header */
#define	BSD_IPPROTO_APES		99		/* any private encr. scheme */
#define	BSD_IPPROTO_GMTP		100		/* GMTP*/
#define	BSD_IPPROTO_IPCOMP		108		/* payload compression (IPComp) */
#define	BSD_IPPROTO_SCTP		132		/* SCTP */
#define	BSD_IPPROTO_MH		135		/* IPv6 Mobility Header */
/* 101-254: Partly Unassigned */
#define	BSD_IPPROTO_PIM		103		/* Protocol Independent Mcast */
#define	BSD_IPPROTO_CARP		112		/* CARP */
#define	BSD_IPPROTO_PGM		113		/* PGM */
#define	BSD_IPPROTO_MPLS		137		/* MPLS-in-IP */
#define	BSD_IPPROTO_PFSYNC		240		/* PFSYNC */
/* 255: Reserved */
/* BSD Private, local use, namespace incursion, no longer used */
#define	BSD_IPPROTO_OLD_DIVERT	254		/* OLD divert pseudo-proto */
#define	BSD_IPPROTO_MAX		256

/* last return value of *_input(), meaning "all job for this pkt is done".  */
#define	BSD_IPPROTO_DONE		257

/* Only used internally, so can be outside the range of valid IP protocols. */
#define	BSD_IPPROTO_DIVERT		258		/* divert pseudo-protocol */
#define	BSD_IPPROTO_SEND		259		/* SeND pseudo-protocol */

/*
 * Defined to avoid confusion.  The master value is defined by
 * PROTO_SPACER in sys/protosw.h.
 */
#define	BSD_IPPROTO_SPACER		32767		/* spacer for loadable protos */

/*
 * Local port number conventions:
 *
 * When a user does a bind(2) or connect(2) with a port number of zero,
 * a non-conflicting local port address is chosen.
 * The default range is IPPORT_HIFIRSTAUTO through
 * IPPORT_HILASTAUTO, although that is settable by sysctl.
 *
 * A user may set the IPPROTO_IP option IP_PORTRANGE to change this
 * default assignment range.
 *
 * The value IP_PORTRANGE_DEFAULT causes the default behavior.
 *
 * The value IP_PORTRANGE_HIGH changes the range of candidate port numbers
 * into the "high" range.  These are reserved for client outbound connections
 * which do not want to be filtered by any firewalls.
 *
 * The value IP_PORTRANGE_LOW changes the range to the "low" are
 * that is (by convention) restricted to privileged processes.  This
 * convention is based on "vouchsafe" principles only.  It is only secure
 * if you trust the remote host to restrict these ports.
 *
 * The default range of ports and the high range can be changed by
 * sysctl(3).  (net.inet.ip.port{hi,low}{first,last}_auto)
 *
 * Changing those values has bad security implications if you are
 * using a stateless firewall that is allowing packets outside of that
 * range in order to allow transparent outgoing connections.
 *
 * Such a firewall configuration will generally depend on the use of these
 * default values.  If you change them, you may find your Security
 * Administrator looking for you with a heavy object.
 *
 * For a slightly more orthodox text view on this:
 *
 *            ftp://ftp.isi.edu/in-notes/iana/assignments/port-numbers
 *
 *    port numbers are divided into three ranges:
 *
 *                0 -  1023 Well Known Ports
 *             1024 - 49151 Registered Ports
 *            49152 - 65535 Dynamic and/or Private Ports
 *
 */

/*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).         (IP_PORTRANGE_LOW)
 */
#define	BSD_IPPORT_RESERVED		1024

/*
 * Default local port range, used by IP_PORTRANGE_DEFAULT
 */
#define BSD_IPPORT_EPHEMERALFIRST	10000
#define BSD_IPPORT_EPHEMERALLAST	65535
 
/*
 * Dynamic port range, used by IP_PORTRANGE_HIGH.
 */
#define	BSD_IPPORT_HIFIRSTAUTO	49152
#define	BSD_IPPORT_HILASTAUTO	65535

/*
 * Scanning for a free reserved port return a value below IPPORT_RESERVED,
 * but higher than IPPORT_RESERVEDSTART.  Traditionally the start value was
 * 512, but that conflicts with some well-known-services that firewalls may
 * have a fit if we use.
 */
#define	BSD_IPPORT_RESERVEDSTART	600

#define	BSD_IPPORT_MAX		65535

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define	BSD_IN_CLASSA(i)		(((bsd_uint32_t)(i) & 0x80000000) == 0)
#define	BSD_IN_CLASSA_NET		0xff000000
#define	BSD_IN_CLASSA_NSHIFT	24
#define	BSD_IN_CLASSA_HOST		0x00ffffff
#define	BSD_IN_CLASSA_MAX		128

#define	BSD_IN_CLASSB(i)		(((bsd_uint32_t)(i) & 0xc0000000) == 0x80000000)
#define	BSD_IN_CLASSB_NET		0xffff0000
#define	BSD_IN_CLASSB_NSHIFT	16
#define	BSD_IN_CLASSB_HOST		0x0000ffff
#define	BSD_IN_CLASSB_MAX		65536

#define	BSD_IN_CLASSC(i)		(((bsd_uint32_t)(i) & 0xe0000000) == 0xc0000000)
#define	BSD_IN_CLASSC_NET		0xffffff00
#define	BSD_IN_CLASSC_NSHIFT	8
#define	BSD_IN_CLASSC_HOST		0x000000ff

#define	BSD_IN_CLASSD(i)		(((bsd_uint32_t)(i) & 0xf0000000) == 0xe0000000)
#define	BSD_IN_CLASSD_NET		0xf0000000	/* These ones aren't really */
#define	BSD_IN_CLASSD_NSHIFT	28		/* net and host fields, but */
#define	BSD_IN_CLASSD_HOST		0x0fffffff	/* routing needn't know.    */
#define	BSD_IN_MULTICAST(i)		BSD_IN_CLASSD(i)

#define	BSD_IN_EXPERIMENTAL(i)	(((bsd_uint32_t)(i) & 0xf0000000) == 0xf0000000)
#define	BSD_IN_BADCLASS(i)		(((bsd_uint32_t)(i) & 0xf0000000) == 0xf0000000)

#define BSD_IN_LINKLOCAL(i)		(((bsd_uint32_t)(i) & 0xffff0000) == 0xa9fe0000)
#define BSD_IN_LOOPBACK(i)		(((bsd_uint32_t)(i) & 0xff000000) == 0x7f000000)
#define BSD_IN_ZERONET(i)		(((bsd_uint32_t)(i) & 0xff000000) == 0)

#define	BSD_IN_PRIVATE(i)	((((bsd_uint32_t)(i) & 0xff000000) == 0x0a000000) || \
			 (((bsd_uint32_t)(i) & 0xfff00000) == 0xac100000) || \
			 (((bsd_uint32_t)(i) & 0xffff0000) == 0xc0a80000))

#define	BSD_IN_LOCAL_GROUP(i)	(((bsd_uint32_t)(i) & 0xffffff00) == 0xe0000000)
 
#define	BSD_IN_ANY_LOCAL(i)		(IN_LINKLOCAL(i) || IN_LOCAL_GROUP(i))

#define	BSD_INADDR_LOOPBACK		(bsd_uint32_t)0x7f000001
#ifndef _KERNEL
#define	BSD_INADDR_NONE		0xffffffff		/* -1 return */
#endif

#define	BSD_INADDR_UNSPEC_GROUP	(bsd_uint32_t)0xe0000000	/* 224.0.0.0 */
#define	BSD_INADDR_ALLHOSTS_GROUP	(bsd_uint32_t)0xe0000001	/* 224.0.0.1 */
#define	BSD_INADDR_ALLRTRS_GROUP	(bsd_uint32_t)0xe0000002	/* 224.0.0.2 */
#define	BSD_INADDR_ALLRPTS_GROUP	(bsd_uint32_t)0xe0000016	/* 224.0.0.22, IGMPv3 */
#define	BSD_INADDR_CARP_GROUP	(bsd_uint32_t)0xe0000012	/* 224.0.0.18 */
#define	BSD_INADDR_PFSYNC_GROUP	(bsd_uint32_t)0xe00000f0	/* 224.0.0.240 */
#define	BSD_INADDR_ALLMDNS_GROUP	(bsd_uint32_t)0xe00000fb	/* 224.0.0.251 */
#define	BSD_INADDR_MAX_LOCAL_GROUP	(bsd_uint32_t)0xe00000ff	/* 224.0.0.255 */

#define	BSD_IN_LOOPBACKNET		127			/* official! */

#define	BSD_IN_RFC3021_MASK		(bsd_uint32_t)0xfffffffe

/*
 * Options for use with [gs]etsockopt at the IP level.
 * First word of comment is data type; bool is stored in int.
 */
#define	BSD_IP_OPTIONS		1    /* buf/ip_opts; set/get IP options */
#define	BSD_IP_HDRINCL		2    /* int; header is included with data */
#define	BSD_IP_TOS			3    /* int; IP type of service and preced. */
#define	BSD_IP_TTL			4    /* int; IP time to live */
#define	BSD_IP_RECVOPTS		5    /* bool; receive all IP opts w/dgram */
#define	BSD_IP_RECVRETOPTS		6    /* bool; receive IP opts for response */
#define	BSD_IP_RECVDSTADDR		7    /* bool; receive IP dst addr w/dgram */
#define	BSD_IP_SENDSRCADDR		IP_RECVDSTADDR /* cmsg_type to set src addr */
#define	BSD_IP_RETOPTS		8    /* ip_opts; set/get IP options */
#define	BSD_IP_MULTICAST_IF		9    /* struct in_addr *or* struct ip_mreqn;
				      * set/get IP multicast i/f  */
#define	BSD_IP_MULTICAST_TTL	10   /* u_char; set/get IP multicast ttl */
#define	BSD_IP_MULTICAST_LOOP	11   /* u_char; set/get IP multicast loopback */
#define	BSD_IP_ADD_MEMBERSHIP	12   /* ip_mreq; add an IP group membership */
#define	BSD_IP_DROP_MEMBERSHIP	13   /* ip_mreq; drop an IP group membership */
#define	BSD_IP_MULTICAST_VIF	14   /* set/get IP mcast virt. iface */
#define	BSD_IP_RSVP_ON		15   /* enable RSVP in kernel */
#define	BSD_IP_RSVP_OFF		16   /* disable RSVP in kernel */
#define	BSD_IP_RSVP_VIF_ON		17   /* set RSVP per-vif socket */
#define	BSD_IP_RSVP_VIF_OFF		18   /* unset RSVP per-vif socket */
#define	BSD_IP_PORTRANGE		19   /* int; range to choose for unspec port */
#define	BSD_IP_RECVIF		20   /* bool; receive reception if w/dgram */
/* for IPSEC */
#define	BSD_IP_IPSEC_POLICY		21   /* int; set/get security policy */
#define	BSD_IP_FAITH		22   /* bool; accept FAITH'ed connections */

#define	BSD_IP_ONESBCAST		23   /* bool: send all-ones broadcast */
#define	BSD_IP_BINDANY		24   /* bool: allow bind to any address */

/*
 * Options for controlling the firewall and dummynet.
 * Historical options (from 40 to 64) will eventually be
 * replaced by only two options, IP_FW3 and IP_DUMMYNET3.
 */
#define	BSD_IP_FW_TABLE_ADD		40   /* add entry */
#define	BSD_IP_FW_TABLE_DEL		41   /* delete entry */
#define	BSD_IP_FW_TABLE_FLUSH	42   /* flush table */
#define	BSD_IP_FW_TABLE_GETSIZE	43   /* get table size */
#define	BSD_IP_FW_TABLE_LIST	44   /* list table contents */

#define	BSD_IP_FW3			48   /* generic ipfw v.3 sockopts */
#define	BSD_IP_DUMMYNET3		49   /* generic dummynet v.3 sockopts */

#define	BSD_IP_FW_ADD		50   /* add a firewall rule to chain */
#define	BSD_IP_FW_DEL		51   /* delete a firewall rule from chain */
#define	BSD_IP_FW_FLUSH		52   /* flush firewall rule chain */
#define	BSD_IP_FW_ZERO		53   /* clear single/all firewall counter(s) */
#define	BSD_IP_FW_GET		54   /* get entire firewall rule chain */
#define	BSD_IP_FW_RESETLOG		55   /* reset logging counters */

#define BSD_IP_FW_NAT_CFG           56   /* add/config a nat rule */
#define BSD_IP_FW_NAT_DEL           57   /* delete a nat rule */
#define BSD_IP_FW_NAT_GET_CONFIG    58   /* get configuration of a nat rule */
#define BSD_IP_FW_NAT_GET_LOG       59   /* get log of a nat rule */

#define	BSD_IP_DUMMYNET_CONFIGURE	60   /* add/configure a dummynet pipe */
#define	BSD_IP_DUMMYNET_DEL		61   /* delete a dummynet pipe from chain */
#define	BSD_IP_DUMMYNET_FLUSH	62   /* flush dummynet */
#define	BSD_IP_DUMMYNET_GET		64   /* get entire dummynet pipes */

#define	BSD_IP_RECVTTL		65   /* bool; receive IP TTL w/dgram */
#define	BSD_IP_MINTTL		66   /* minimum TTL for packet or drop */
#define	BSD_IP_DONTFRAG		67   /* don't fragment packet */
#define	BSD_IP_RECVTOS		68   /* bool; receive IP TOS w/dgram */

/* IPv4 Source Filter Multicast API [RFC3678] */
#define	BSD_IP_ADD_SOURCE_MEMBERSHIP	70   /* join a source-specific group */
#define	BSD_IP_DROP_SOURCE_MEMBERSHIP	71   /* drop a single source */
#define	BSD_IP_BLOCK_SOURCE			72   /* block a source */
#define	BSD_IP_UNBLOCK_SOURCE		73   /* unblock a source */

/* The following option is private; do not use it from user applications. */
#define	BSD_IP_MSFILTER			74   /* set/get filter list */

/* Protocol Independent Multicast API [RFC3678] */
#define	BSD_MCAST_JOIN_GROUP		80   /* join an any-source group */
#define	BSD_MCAST_LEAVE_GROUP		81   /* leave all sources for group */
#define	BSD_MCAST_JOIN_SOURCE_GROUP		82   /* join a source-specific group */
#define	BSD_MCAST_LEAVE_SOURCE_GROUP	83   /* leave a single source */
#define	BSD_MCAST_BLOCK_SOURCE		84   /* block a source */
#define	BSD_MCAST_UNBLOCK_SOURCE		85   /* unblock a source */

/*
 * Defaults and limits for options
 */
#define	BSD_IP_DEFAULT_MULTICAST_TTL  1	/* normally limit m'casts to 1 hop  */
#define	BSD_IP_DEFAULT_MULTICAST_LOOP 1	/* normally hear sends if a member  */

/*
 * The imo_membership vector for each socket is now dynamically allocated at
 * run-time, bounded by USHRT_MAX, and is reallocated when needed, sized
 * according to a power-of-two increment.
 */
#define	BSD_IP_MIN_MEMBERSHIPS	31
#define	BSD_IP_MAX_MEMBERSHIPS	4095
#define	BSD_IP_MAX_SOURCE_FILTER	1024	/* XXX to be unused */

/*
 * Default resource limits for IPv4 multicast source filtering.
 * These may be modified by sysctl.
 */
#define	BSD_IP_MAX_GROUP_SRC_FILTER		512	/* sources per group */
#define	BSD_IP_MAX_SOCK_SRC_FILTER		128	/* sources per socket/group */
#define	BSD_IP_MAX_SOCK_MUTE_FILTER		128	/* XXX no longer used */

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
struct bsd_ip_mreq {
	struct	bsd_in_addr imr_multiaddr;	/* IP multicast address of group */
	struct	bsd_in_addr imr_interface;	/* local IP address of interface */
};

/*
 * Modified argument structure for IP_MULTICAST_IF, obtained from Linux.
 * This is used to specify an interface index for multicast sends, as
 * the IPv4 legacy APIs do not support this (unless IP_SENDIF is available).
 */
struct bsd_ip_mreqn {
	struct	bsd_in_addr imr_multiaddr;	/* IP multicast address of group */
	struct	bsd_in_addr imr_address;	/* local IP address of interface */
	int		imr_ifindex;	/* Interface index; cast to uint32_t */
};

/*
 * Argument structure for IPv4 Multicast Source Filter APIs. [RFC3678]
 */
struct bsd_ip_mreq_source {
	struct	bsd_in_addr imr_multiaddr;	/* IP multicast address of group */
	struct	bsd_in_addr imr_sourceaddr;	/* IP address of source */
	struct	bsd_in_addr imr_interface;	/* local IP address of interface */
};

/*
 * Argument structures for Protocol-Independent Multicast Source
 * Filter APIs. [RFC3678]
 */
struct bsd_group_req {
	bsd_uint32_t		gr_interface;	/* interface index */
	struct bsd_sockaddr_storage	gr_group;	/* group address */
};

struct bsd_group_source_req {
	bsd_uint32_t		gsr_interface;	/* interface index */
	struct bsd_sockaddr_storage	gsr_group;	/* group address */
	struct bsd_sockaddr_storage	gsr_source;	/* source address */
};

#ifndef __MSFILTERREQ_DEFINED
#define __MSFILTERREQ_DEFINED
/*
 * The following structure is private; do not use it from user applications.
 * It is used to communicate IP_MSFILTER/IPV6_MSFILTER information between
 * the RFC 3678 libc functions and the kernel.
 */
struct __bsd_msfilterreq {
	bsd_uint32_t		 msfr_ifindex;	/* interface index */
	bsd_uint32_t		 msfr_fmode;	/* filter mode for group */
	bsd_uint32_t		 msfr_nsrcs;	/* # of sources in msfr_srcs */
	struct bsd_sockaddr_storage	 msfr_group;	/* group address */
	struct bsd_sockaddr_storage	*msfr_srcs;	/* pointer to the first member
						 * of a contiguous array of
						 * sources to filter in full.
						 */
};
#endif

struct bsd_sockaddr;

/*
 * Advanced (Full-state) APIs [RFC3678]
 * The RFC specifies uint_t for the 6th argument to [sg]etsourcefilter().
 * We use uint32_t here to be consistent.
 */
int	setipv4sourcefilter(int, struct bsd_in_addr, struct bsd_in_addr, bsd_uint32_t,
	    bsd_uint32_t, struct bsd_in_addr *);
int	getipv4sourcefilter(int, struct bsd_in_addr, struct bsd_in_addr, bsd_uint32_t *,
	    bsd_uint32_t *, struct bsd_in_addr *);
int	setsourcefilter(int, bsd_uint32_t, struct bsd_sockaddr *, bsd_socklen_t,
	    bsd_uint32_t, bsd_uint32_t, struct bsd_sockaddr_storage *);
int	getsourcefilter(int, bsd_uint32_t, struct bsd_sockaddr *, bsd_socklen_t,
	    bsd_uint32_t *, bsd_uint32_t *, struct bsd_sockaddr_storage *);

/*
 * Filter modes; also used to represent per-socket filter mode internally.
 */
#define	BSD_MCAST_UNDEFINED	0	/* fmode: not yet defined */
#define	BSD_MCAST_INCLUDE	1	/* fmode: include these source(s) */
#define	BSD_MCAST_EXCLUDE	2	/* fmode: exclude these source(s) */

/*
 * Argument for IP_PORTRANGE:
 * - which range to search when port is unspecified at bind() or connect()
 */
#define	BSD_IP_PORTRANGE_DEFAULT	0	/* default range */
#define	BSD_IP_PORTRANGE_HIGH	1	/* "high" - request firewall bypass */
#define	BSD_IP_PORTRANGE_LOW	2	/* "low" - vouchsafe security */

/*
 * Definitions for inet sysctl operations.
 *
 * Third level is protocol number.
 * Fourth level is desired variable within that protocol.
 */
#define	BSD_IPPROTO_MAXID	(BSD_IPPROTO_AH + 1)	/* don't list to IPPROTO_MAX */

#define	BSD_CTL_IPPROTO_NAMES { \
	{ "ip", CTLTYPE_NODE }, \
	{ "icmp", CTLTYPE_NODE }, \
	{ "igmp", CTLTYPE_NODE }, \
	{ "ggp", CTLTYPE_NODE }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "tcp", CTLTYPE_NODE }, \
	{ 0, 0 }, \
	{ "egp", CTLTYPE_NODE }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "pup", CTLTYPE_NODE }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "udp", CTLTYPE_NODE }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "idp", CTLTYPE_NODE }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "ipsec", CTLTYPE_NODE }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "pim", CTLTYPE_NODE }, \
}

/*
 * Names for IP sysctl objects
 */
#define	BSD_IPCTL_FORWARDING	1	/* act as router */
#define	BSD_IPCTL_SENDREDIRECTS	2	/* may send redirects when forwarding */
#define	BSD_IPCTL_DEFTTL		3	/* default TTL */
#ifdef notyet
#define	BSD_IPCTL_DEFMTU		4	/* default MTU */
#endif
#define	BSD_IPCTL_RTEXPIRE		5	/* cloned route expiration time */
#define	BSD_IPCTL_RTMINEXPIRE	6	/* min value for expiration time */
#define	BSD_IPCTL_RTMAXCACHE	7	/* trigger level for dynamic expire */
#define	BSD_IPCTL_SOURCEROUTE	8	/* may perform source routes */
#define	BSD_IPCTL_DIRECTEDBROADCAST	9	/* may re-broadcast received packets */
#define	BSD_IPCTL_INTRQMAXLEN	10	/* max length of netisr queue */
#define	BSD_IPCTL_INTRQDROPS	11	/* number of netisr q drops */
#define	BSD_IPCTL_STATS		12	/* ipstat structure */
#define	BSD_IPCTL_ACCEPTSOURCEROUTE	13	/* may accept source routed packets */
#define	BSD_IPCTL_FASTFORWARDING	14	/* use fast IP forwarding code */
#define	BSD_IPCTL_KEEPFAITH		15	/* FAITH IPv4->IPv6 translater ctl */
#define	BSD_IPCTL_GIF_TTL		16	/* default TTL for gif encap packet */
#define	BSD_IPCTL_MAXID		17

#define	BSD_IPCTL_NAMES { \
	{ 0, 0 }, \
	{ "forwarding", CTLTYPE_INT }, \
	{ "redirect", CTLTYPE_INT }, \
	{ "ttl", CTLTYPE_INT }, \
	{ "mtu", CTLTYPE_INT }, \
	{ "rtexpire", CTLTYPE_INT }, \
	{ "rtminexpire", CTLTYPE_INT }, \
	{ "rtmaxcache", CTLTYPE_INT }, \
	{ "sourceroute", CTLTYPE_INT }, \
	{ "directed-broadcast", CTLTYPE_INT }, \
	{ "intr-queue-maxlen", CTLTYPE_INT }, \
	{ "intr-queue-drops", CTLTYPE_INT }, \
	{ "stats", CTLTYPE_STRUCT }, \
	{ "accept_sourceroute", CTLTYPE_INT }, \
	{ "fastforwarding", CTLTYPE_INT }, \
}

#endif /* __BSD_VISIBLE */

#ifdef _KERNEL

struct ifnet; struct mbuf;	/* forward declarations for Standard C */

int	 in_broadcast(struct bsd_in_addr, struct ifnet *);
int	 in_canforward(struct bsd_in_addr);
int	 in_localaddr(struct bsd_in_addr);
int	 in_localip(struct bsd_in_addr);
int	 inet_aton(const char *, struct bsd_in_addr *); /* in libkern */
char	*bsd_inet_ntoa(struct bsd_in_addr); /* in libkern */
char	*bsd_inet_ntoa_r(struct bsd_in_addr ina, char *buf); /* in libkern */
char	*bsd_inet_ntop(int, const void *, char *, bsd_socklen_t); /* in libkern */
int	 bsd_inet_pton(int af, const char *, void *); /* in libkern */
void	 in_ifdetach(struct ifnet *);

#define	in_hosteq(s, t)	((s).s_addr == (t).s_addr)
#define	in_nullhost(x)	((x).s_addr == INADDR_ANY)
#define	in_allhosts(x)	((x).s_addr == htonl(INADDR_ALLHOSTS_GROUP))

#define	satosin(sa)	((struct sockaddr_in *)(sa))
#define	sintosa(sin)	((struct sockaddr *)(sin))
#define	ifatoia(ifa)	((struct in_ifaddr *)(ifa))

/*
 * Historically, BSD keeps ip_len and ip_off in host format
 * when doing layer 3 processing, and this often requires
 * to translate the format back and forth.
 * To make the process explicit, we define a couple of macros
 * that also take into account the fact that at some point
 * we may want to keep those fields always in net format.
 */

#if (BSD_BYTE_ORDER == BSD_BIG_ENDIAN) || defined(HAVE_NET_IPLEN)
#define SET_NET_IPLEN(p)	do {} while (0)
#define SET_HOST_IPLEN(p)	do {} while (0)
#else
#define SET_NET_IPLEN(p)	do {		\
	struct ip *h_ip = (p);			\
	h_ip->ip_len = htons(h_ip->ip_len);	\
	h_ip->ip_off = htons(h_ip->ip_off);	\
	} while (0)

#define SET_HOST_IPLEN(p)	do {		\
	struct ip *h_ip = (p);			\
	h_ip->ip_len = ntohs(h_ip->ip_len);	\
	h_ip->ip_off = ntohs(h_ip->ip_off);	\
	} while (0)
#endif /* !HAVE_NET_IPLEN */

#endif /* _KERNEL */

/* INET6 stuff */
#if __POSIX_VISIBLE >= 200112
#define	__KAME_NETINET_IN_H_INCLUDED_
#include <netinet6/in6.h>
#undef __KAME_NETINET_IN_H_INCLUDED_
#endif

#endif /* !_NETINET_IN_H_*/
