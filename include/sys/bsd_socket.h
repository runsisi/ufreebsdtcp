/*-
 * Copyright (c) 1982, 1985, 1986, 1988, 1993, 1994
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
 *	@(#)socket.h	8.4 (Berkeley) 2/21/94
 * $FreeBSD: release/9.2.0/sys/sys/socket.h 247525 2013-03-01 03:04:57Z jhb $
 */

#ifndef _BSD_SYS_SOCKET_H_
#define	_BSD_SYS_SOCKET_H_

#include <sys/bsd_cdefs.h>
#include <sys/_bsd_types.h>
#include <sys/_bsd_iovec.h>
#include <machine/_bsd_align.h>

/*
 * Definitions related to sockets: types, address families, options.
 */

/*
 * Data types.
 */
#if __BSD_VISIBLE
#ifndef _BSD_GID_T_DECLARED
typedef	__bsd_gid_t		bsd_gid_t;
#define	_BSD_GID_T_DECLARED
#endif

#ifndef _BSD_OFF_T_DECLARED
typedef	__bsd_off_t		bsd_off_t;
#define	_BSD_OFF_T_DECLARED
#endif

#ifndef _BSD_PID_T_DECLARED
typedef	__bsd_pid_t		bsd_pid_t;
#define	_BSD_PID_T_DECLARED
#endif
#endif

#ifndef _BSD_SA_FAMILY_T_DECLARED
typedef	__bsd_sa_family_t	bsd_sa_family_t;
#define	_BSD_SA_FAMILY_T_DECLARED
#endif

#ifndef _BSD_SOCKLEN_T_DECLARED
typedef	__bsd_socklen_t	bsd_socklen_t;
#define	_BSD_SOCKLEN_T_DECLARED
#endif
 
#ifndef _BSD_SSIZE_T_DECLARED
typedef	__bsd_ssize_t	bsd_ssize_t;
#define	_BSD_SSIZE_T_DECLARED
#endif

#if __BSD_VISIBLE 
#ifndef _BSD_UID_T_DECLARED
typedef	__bsd_uid_t		bsd_uid_t;
#define	_BSD_UID_T_DECLARED
#endif
#endif

/*
 * Types
 */
#define	BSD_SOCK_STREAM	1		/* stream socket */
#define	BSD_SOCK_DGRAM	2		/* datagram socket */
#define	BSD_SOCK_RAW	3		/* raw-protocol interface */
#if __BSD_VISIBLE
#define	BSD_SOCK_RDM	4		/* reliably-delivered message */
#endif
#define	BSD_SOCK_SEQPACKET	5		/* sequenced packet stream */

/*
 * Option flags per-socket.
 */
#define	BSD_SO_DEBUG	0x0001		/* turn on debugging info recording */
#define	BSD_SO_ACCEPTCONN	0x0002		/* socket has had listen() */
#define	BSD_SO_REUSEADDR	0x0004		/* allow local address reuse */
#define	BSD_SO_KEEPALIVE	0x0008		/* keep connections alive */
#define	BSD_SO_DONTROUTE	0x0010		/* just use interface addresses */
#define	BSD_SO_BROADCAST	0x0020		/* permit sending of broadcast msgs */
#if __BSD_VISIBLE
#define	BSD_SO_USELOOPBACK	0x0040		/* bypass hardware when possible */
#endif
#define	BSD_SO_LINGER	0x0080		/* linger on close if data present */
#define	BSD_SO_OOBINLINE	0x0100		/* leave received OOB data in line */
#if __BSD_VISIBLE
#define	BSD_SO_REUSEPORT	0x0200		/* allow local address & port reuse */
#define	BSD_SO_TIMESTAMP	0x0400		/* timestamp received dgram traffic */
#define	BSD_SO_NOSIGPIPE	0x0800		/* no SIGPIPE from EPIPE */
#define	BSD_SO_ACCEPTFILTER	0x1000		/* there is an accept filter */
#define	BSD_SO_BINTIME	0x2000		/* timestamp received dgram traffic */
#endif
#define	BSD_SO_NO_OFFLOAD	0x4000		/* socket cannot be offloaded */
#define	BSD_SO_NO_DDP	0x8000		/* disable direct data placement */

/*
 * Additional options, not kept in so_options.
 */
#define	BSD_SO_SNDBUF	0x1001		/* send buffer size */
#define	BSD_SO_RCVBUF	0x1002		/* receive buffer size */
#define	BSD_SO_SNDLOWAT	0x1003		/* send low-water mark */
#define	BSD_SO_RCVLOWAT	0x1004		/* receive low-water mark */
#define	BSD_SO_SNDTIMEO	0x1005		/* send timeout */
#define	BSD_SO_RCVTIMEO	0x1006		/* receive timeout */
#define	BSD_SO_ERROR	0x1007		/* get error status and clear */
#define	BSD_SO_TYPE		0x1008		/* get socket type */
#if __BSD_VISIBLE
#define	BSD_SO_LABEL	0x1009		/* socket's MAC label */
#define	BSD_SO_PEERLABEL	0x1010		/* socket's peer's MAC label */
#define	BSD_SO_LISTENQLIMIT	0x1011		/* socket's backlog limit */
#define	BSD_SO_LISTENQLEN	0x1012		/* socket's complete queue length */
#define	BSD_SO_LISTENINCQLEN	0x1013	/* socket's incomplete queue length */
#define	BSD_SO_SETFIB	0x1014		/* use this FIB to route */
#define	BSD_SO_USER_COOKIE	0x1015		/* user cookie (dummynet etc.) */
#define	BSD_SO_PROTOCOL	0x1016		/* get socket protocol (Linux name) */
#define	BSD_SO_PROTOTYPE	BSD_SO_PROTOCOL	/* alias for SO_PROTOCOL (SunOS name) */
#endif

/*
 * Space reserved for new socket options added by third-party vendors.
 * This range applies to all socket option levels.  New socket options
 * in FreeBSD should always use an option value less than SO_VENDOR.
 */
#if __BSD_VISIBLE
#define	BSD_SO_VENDOR	0x80000000
#endif

/*
 * Structure used for manipulating linger option.
 */
struct bsd_linger {
	int	l_onoff;		/* option on/off */
	int	l_linger;		/* linger time */
};

#if __BSD_VISIBLE
struct bsd_accept_filter_arg {
	char	af_name[16];
	char	af_arg[256-16];
};
#endif

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define	BSD_SOL_SOCKET	0xffff		/* options for socket level */

/*
 * Address families.
 */
#define	BSD_AF_UNSPEC	0		/* unspecified */
#if __BSD_VISIBLE
#define	BSD_AF_LOCAL	BSD_AF_UNIX		/* local to host (pipes, portals) */
#endif
#define	BSD_AF_UNIX		1		/* standardized name for AF_LOCAL */
#define	BSD_AF_INET		2		/* internetwork: UDP, TCP, etc. */
#if __BSD_VISIBLE
#define	BSD_AF_IMPLINK	3		/* arpanet imp addresses */
#define	BSD_AF_PUP		4		/* pup protocols: e.g. BSP */
#define	BSD_AF_CHAOS	5		/* mit CHAOS protocols */
#define	BSD_AF_NETBIOS	6		/* SMB protocols */
#define	BSD_AF_ISO		7		/* ISO protocols */
#define	BSD_AF_OSI		BSD_AF_ISO
#define	BSD_AF_ECMA		8		/* European computer manufacturers */
#define	BSD_AF_DATAKIT	9		/* datakit protocols */
#define	BSD_AF_CCITT	10		/* CCITT protocols, X.25 etc */
#define	BSD_AF_SNA		11		/* IBM SNA */
#define BSD_AF_DECnet	12		/* DECnet */
#define BSD_AF_DLI		13		/* DEC Direct data link interface */
#define BSD_AF_LAT		14		/* LAT */
#define	BSD_AF_HYLINK	15		/* NSC Hyperchannel */
#define	BSD_AF_APPLETALK	16		/* Apple Talk */
#define	BSD_AF_ROUTE	17		/* Internal Routing Protocol */
#define	BSD_AF_LINK		18		/* Link layer interface */
#define	BSD_pseudo_AF_XTP	19		/* eXpress Transfer Protocol (no AF) */
#define	BSD_AF_COIP		20		/* connection-oriented IP, aka ST II */
#define	BSD_AF_CNT		21		/* Computer Network Technology */
#define BSD_pseudo_AF_RTIP	22		/* Help Identify RTIP packets */
#define	BSD_AF_IPX		23		/* Novell Internet Protocol */
#define	BSD_AF_SIP		24		/* Simple Internet Protocol */
#define	BSD_pseudo_AF_PIP	25		/* Help Identify PIP packets */
#define	BSD_AF_ISDN		26		/* Integrated Services Digital Network*/
#define	BSD_AF_E164		AF_ISDN		/* CCITT E.164 recommendation */
#define	BSD_pseudo_AF_KEY	27		/* Internal key-management function */
#endif
#define	BSD_AF_INET6	28		/* IPv6 */
#if __BSD_VISIBLE
#define	BSD_AF_NATM		29		/* native ATM access */
#define	BSD_AF_ATM		30		/* ATM */
#define BSD_pseudo_AF_HDRCMPLT 31		/* Used by BPF to not rewrite headers
					 * in interface output routine
					 */
#define	BSD_AF_NETGRAPH	32		/* Netgraph sockets */
#define	BSD_AF_SLOW		33		/* 802.3ad slow protocol */
#define	BSD_AF_SCLUSTER	34		/* Sitara cluster protocol */
#define	BSD_AF_ARP		35
#define	BSD_AF_BLUETOOTH	36		/* Bluetooth sockets */
#define	BSD_AF_IEEE80211	37		/* IEEE 802.11 protocol */
#define	BSD_AF_MAX		38
/*
 * When allocating a new AF_ constant, please only allocate
 * even numbered constants for FreeBSD until 134 as odd numbered AF_
 * constants 39-133 are now reserved for vendors.
 */
#define AF_VENDOR00 39
#define AF_VENDOR01 41
#define AF_VENDOR02 43
#define AF_VENDOR03 45
#define AF_VENDOR04 47
#define AF_VENDOR05 49
#define AF_VENDOR06 51
#define AF_VENDOR07 53
#define AF_VENDOR08 55
#define AF_VENDOR09 57
#define AF_VENDOR10 59
#define AF_VENDOR11 61
#define AF_VENDOR12 63
#define AF_VENDOR13 65
#define AF_VENDOR14 67
#define AF_VENDOR15 69
#define AF_VENDOR16 71
#define AF_VENDOR17 73
#define AF_VENDOR18 75
#define AF_VENDOR19 77
#define AF_VENDOR20 79
#define AF_VENDOR21 81
#define AF_VENDOR22 83
#define AF_VENDOR23 85
#define AF_VENDOR24 87
#define AF_VENDOR25 89
#define AF_VENDOR26 91
#define AF_VENDOR27 93
#define AF_VENDOR28 95
#define AF_VENDOR29 97
#define AF_VENDOR30 99
#define AF_VENDOR31 101
#define AF_VENDOR32 103
#define AF_VENDOR33 105
#define AF_VENDOR34 107
#define AF_VENDOR35 109
#define AF_VENDOR36 111
#define AF_VENDOR37 113
#define AF_VENDOR38 115
#define AF_VENDOR39 117
#define AF_VENDOR40 119
#define AF_VENDOR41 121
#define AF_VENDOR42 123
#define AF_VENDOR43 125
#define AF_VENDOR44 127
#define AF_VENDOR45 129
#define AF_VENDOR46 131
#define AF_VENDOR47 133
#endif

/*
 * Structure used by kernel to store most
 * addresses.
 */
struct bsd_sockaddr {
	unsigned char	sa_len;		/* total length */
	bsd_sa_family_t	sa_family;	/* address family */
	char		sa_data[14];	/* actually longer; address value */
};
#if __BSD_VISIBLE
#define	BSD_SOCK_MAXADDRLEN	255		/* longest possible addresses */

/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct bsd_sockproto {
	unsigned short	sp_family;		/* address family */
	unsigned short	sp_protocol;		/* protocol */
};
#endif

#include <sys/_bsd_sockaddr_storage.h>

#if __BSD_VISIBLE
/*
 * Protocol families, same as address families for now.
 */
#define	BSD_PF_UNSPEC	BSD_AF_UNSPEC
#define	BSD_PF_LOCAL	BSD_AF_LOCAL
#define	BSD_PF_UNIX		BSD_PF_LOCAL	/* backward compatibility */
#define	BSD_PF_INET		BSD_AF_INET
#define	BSD_PF_IMPLINK	BSD_AF_IMPLINK
#define	BSD_PF_PUP		BSD_AF_PUP
#define	BSD_PF_CHAOS	BSD_AF_CHAOS
#define	BSD_PF_NETBIOS	BSD_AF_NETBIOS
#define	BSD_PF_ISO		BSD_AF_ISO
#define	BSD_PF_OSI		BSD_AF_ISO
#define	BSD_PF_ECMA		BSD_AF_ECMA
#define	BSD_PF_DATAKIT	BSD_AF_DATAKIT
#define	BSD_PF_CCITT	BSD_AF_CCITT
#define	BSD_PF_SNA		BSD_AF_SNA
#define BSD_PF_DECnet	BSD_AF_DECnet
#define BSD_PF_DLI		BSD_AF_DLI
#define BSD_PF_LAT		BSD_AF_LAT
#define	BSD_PF_HYLINK	BSD_AF_HYLINK
#define	BSD_PF_APPLETALK	BSD_AF_APPLETALK
#define	BSD_PF_ROUTE	BSD_AF_ROUTE
#define	BSD_PF_LINK		BSD_AF_LINK
#define	BSD_PF_XTP		BSD_pseudo_AF_XTP	/* really just proto family, no AF */
#define	BSD_PF_COIP		BSD_AF_COIP
#define	BSD_PF_CNT		BSD_AF_CNT
#define	BSD_PF_SIP		BSD_AF_SIP
#define	BSD_PF_IPX		BSD_AF_IPX
#define BSD_PF_RTIP		BSD_pseudo_AF_RTIP	/* same format as AF_INET */
#define BSD_PF_PIP		BSD_pseudo_AF_PIP
#define	BSD_PF_ISDN		BSD_AF_ISDN
#define	BSD_PF_KEY		BSD_pseudo_AF_KEY
#define	BSD_PF_INET6	BSD_AF_INET6
#define	BSD_PF_NATM		BSD_AF_NATM
#define	BSD_PF_ATM		BSD_AF_ATM
#define	BSD_PF_NETGRAPH	BSD_AF_NETGRAPH
#define	BSD_PF_SLOW		BSD_AF_SLOW
#define BSD_PF_SCLUSTER	BSD_AF_SCLUSTER
#define	BSD_PF_ARP		BSD_AF_ARP
#define	BSD_PF_BLUETOOTH	BSD_AF_BLUETOOTH

#define	BSD_PF_MAX		BSD_AF_MAX

/*
 * Definitions for network related sysctl, CTL_NET.
 *
 * Second level is protocol family.
 * Third level is protocol number.
 *
 * Further levels are defined by the individual families below.
 */
#define BSD_NET_MAXID	BSD_AF_MAX

#define BSD_CTL_NET_NAMES { \
	{ 0, 0 }, \
	{ "unix", CTLTYPE_NODE }, \
	{ "inet", CTLTYPE_NODE }, \
	{ "implink", CTLTYPE_NODE }, \
	{ "pup", CTLTYPE_NODE }, \
	{ "chaos", CTLTYPE_NODE }, \
	{ "xerox_ns", CTLTYPE_NODE }, \
	{ "iso", CTLTYPE_NODE }, \
	{ "emca", CTLTYPE_NODE }, \
	{ "datakit", CTLTYPE_NODE }, \
	{ "ccitt", CTLTYPE_NODE }, \
	{ "ibm_sna", CTLTYPE_NODE }, \
	{ "decnet", CTLTYPE_NODE }, \
	{ "dec_dli", CTLTYPE_NODE }, \
	{ "lat", CTLTYPE_NODE }, \
	{ "hylink", CTLTYPE_NODE }, \
	{ "appletalk", CTLTYPE_NODE }, \
	{ "route", CTLTYPE_NODE }, \
	{ "link_layer", CTLTYPE_NODE }, \
	{ "xtp", CTLTYPE_NODE }, \
	{ "coip", CTLTYPE_NODE }, \
	{ "cnt", CTLTYPE_NODE }, \
	{ "rtip", CTLTYPE_NODE }, \
	{ "ipx", CTLTYPE_NODE }, \
	{ "sip", CTLTYPE_NODE }, \
	{ "pip", CTLTYPE_NODE }, \
	{ "isdn", CTLTYPE_NODE }, \
	{ "key", CTLTYPE_NODE }, \
	{ "inet6", CTLTYPE_NODE }, \
	{ "natm", CTLTYPE_NODE }, \
	{ "atm", CTLTYPE_NODE }, \
	{ "hdrcomplete", CTLTYPE_NODE }, \
	{ "netgraph", CTLTYPE_NODE }, \
	{ "snp", CTLTYPE_NODE }, \
	{ "scp", CTLTYPE_NODE }, \
}

/*
 * PF_ROUTE - Routing table
 *
 * Three additional levels are defined:
 *	Fourth: address family, 0 is wildcard
 *	Fifth: type of info, defined below
 *	Sixth: flag(s) to mask with for NET_RT_FLAGS
 */
#define BSD_NET_RT_DUMP	1		/* dump; may limit to a.f. */
#define BSD_NET_RT_FLAGS	2		/* by flags, e.g. RESOLVING */
#define BSD_NET_RT_IFLIST	3		/* survey interface list */
#define	BSD_NET_RT_IFMALIST	4		/* return multicast address list */
#define	BSD_NET_RT_IFLISTL	5		/* Survey interface list, using 'l'en
					 * versions of msghdr structs. */
#define	BSD_NET_RT_MAXID	6

#define BSD_CTL_NET_RT_NAMES { \
	{ 0, 0 }, \
	{ "dump", CTLTYPE_STRUCT }, \
	{ "flags", CTLTYPE_STRUCT }, \
	{ "iflist", CTLTYPE_STRUCT }, \
	{ "ifmalist", CTLTYPE_STRUCT }, \
	{ "iflistl", CTLTYPE_STRUCT }, \
}
#endif /* __BSD_VISIBLE */

/*
 * Maximum queue length specifiable by listen.
 */
#define	BSD_SOMAXCONN	128

/*
 * Message header for recvmsg and sendmsg calls.
 * Used value-result for recvmsg, value only for sendmsg.
 */
struct bsd_msghdr {
	void		*msg_name;		/* optional address */
	bsd_socklen_t	 msg_namelen;		/* size of address */
	struct bsd_iovec	*msg_iov;		/* scatter/gather array */
	int		 msg_iovlen;		/* # elements in msg_iov */
	void		*msg_control;		/* ancillary data, see below */
	bsd_socklen_t	 msg_controllen;	/* ancillary data buffer len */
	int		 msg_flags;		/* flags on received message */
};

#define	BSD_MSG_OOB		0x1		/* process out-of-band data */
#define	BSD_MSG_PEEK	0x2		/* peek at incoming message */
#define	BSD_MSG_DONTROUTE	0x4		/* send without using routing tables */
#define	BSD_MSG_EOR		0x8		/* data completes record */
#define	BSD_MSG_TRUNC	0x10		/* data discarded before delivery */
#define	BSD_MSG_CTRUNC	0x20		/* control data lost before delivery */
#define	BSD_MSG_WAITALL	0x40		/* wait for full request or error */
#define BSD_MSG_NOTIFICATION 0x2000         /* SCTP notification */
#if __BSD_VISIBLE
#define	BSD_MSG_DONTWAIT	0x80		/* this message should be nonblocking */
#define	BSD_MSG_EOF		0x100		/* data completes connection */
#define	BSD_MSG_NBIO	0x4000		/* FIONBIO mode, used by fifofs */
#define	BSD_MSG_COMPAT      0x8000		/* used in sendit() */
#endif
#ifdef _KERNEL
#define	BSD_MSG_SOCALLBCK   0x10000		/* for use by socket callbacks - soreceive (TCP) */
#endif
#if __BSD_VISIBLE
#define	BSD_MSG_NOSIGNAL	0x20000		/* do not generate SIGPIPE on EOF */
#endif

/*
 * Header for ancillary data objects in msg_control buffer.
 * Used for additional information with/about a datagram
 * not expressible by flags.  The format is a sequence
 * of message elements headed by cmsghdr structures.
 */
struct bsd_cmsghdr {
	bsd_socklen_t	cmsg_len;		/* data byte count, including hdr */
	int		cmsg_level;		/* originating protocol */
	int		cmsg_type;		/* protocol-specific type */
/* followed by	u_char  cmsg_data[]; */
};

#if __BSD_VISIBLE
/*
 * While we may have more groups than this, the cmsgcred struct must
 * be able to fit in an mbuf and we have historically supported a
 * maximum of 16 groups.
*/
#define BSD_CMGROUP_MAX 16

/*
 * Credentials structure, used to verify the identity of a peer
 * process that has sent us a message. This is allocated by the
 * peer process but filled in by the kernel. This prevents the
 * peer from lying about its identity. (Note that cmcred_groups[0]
 * is the effective GID.)
 */
struct bsd_cmsgcred {
	bsd_pid_t	cmcred_pid;		/* PID of sending process */
	bsd_uid_t	cmcred_uid;		/* real UID of sending process */
	bsd_uid_t	cmcred_euid;		/* effective UID of sending process */
	bsd_gid_t	cmcred_gid;		/* real GID of sending process */
	short	cmcred_ngroups;		/* number or groups */
	bsd_gid_t	cmcred_groups[BSD_CMGROUP_MAX];	/* groups */
};

/*
 * Socket credentials.
 */
struct bsd_sockcred {
	bsd_uid_t	sc_uid;			/* real user id */
	bsd_uid_t	sc_euid;		/* effective user id */
	bsd_gid_t	sc_gid;			/* real group id */
	bsd_gid_t	sc_egid;		/* effective group id */
	int	sc_ngroups;		/* number of supplemental groups */
	bsd_gid_t	sc_groups[1];		/* variable length */
};

/*
 * Compute size of a sockcred structure with groups.
 */
#define	BSD_SOCKCREDSIZE(ngrps) \
	(sizeof(struct sockcred) + (sizeof(bsd_gid_t) * ((ngrps) - 1)))

#endif /* __BSD_VISIBLE */

/* given pointer to struct cmsghdr, return pointer to data */
#define	BSD_CMSG_DATA(cmsg)		((unsigned char *)(cmsg) + \
				 _BSD_ALIGN(sizeof(struct bsd_cmsghdr)))

/* given pointer to struct cmsghdr, return pointer to next cmsghdr */
#define	BSD_CMSG_NXTHDR(mhdr, cmsg)	\
	((char *)(cmsg) == NULL ? BSD_CMSG_FIRSTHDR(mhdr) : \
	    ((char *)(cmsg) + _BSD_ALIGN(((struct bsd_cmsghdr *)(cmsg))->cmsg_len) + \
	  _BSD_ALIGN(sizeof(struct bsd_cmsghdr)) > \
	    (char *)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
	    (struct bsd_cmsghdr *)0 : \
	    (struct bsd_cmsghdr *)(void *)((char *)(cmsg) + \
	    _BSD_ALIGN(((struct cmsghdr *)(cmsg))->cmsg_len)))

/*
 * RFC 2292 requires to check msg_controllen, in case that the kernel returns
 * an empty list for some reasons.
 */
#define	BSD_CMSG_FIRSTHDR(mhdr) \
	((mhdr)->msg_controllen >= sizeof(struct bsd_cmsghdr) ? \
	 (struct bsd_cmsghdr *)(mhdr)->msg_control : \
	 (struct bsd_cmsghdr *)NULL)

#if __BSD_VISIBLE
/* RFC 2292 additions */
#define	BSD_CMSG_SPACE(l)		(_BSD_ALIGN(sizeof(struct bsd_cmsghdr)) + _BSD_ALIGN(l))
#define	BSD_CMSG_LEN(l)		(_BSD_ALIGN(sizeof(struct bsd_cmsghdr)) + (l))
#endif

#ifdef _KERNEL
#define	BSD_CMSG_ALIGN(n)	_BSD_ALIGN(n)
#endif

/* "Socket"-level control message types: */
#define	BSD_SCM_RIGHTS	0x01		/* access rights (array of int) */
#if __BSD_VISIBLE
#define	BSD_SCM_TIMESTAMP	0x02		/* timestamp (struct timeval) */
#define	BSD_SCM_CREDS	0x03		/* process creds (struct cmsgcred) */
#define	BSD_SCM_BINTIME	0x04		/* timestamp (struct bintime) */
#endif

#if __BSD_VISIBLE
/*
 * 4.3 compat sockaddr, move to compat file later
 */
struct bsd_osockaddr {
	unsigned short sa_family;	/* address family */
	char	sa_data[14];		/* up to 14 bytes of direct address */
};

/*
 * 4.3-compat message header (move to compat file later).
 */
struct bsd_omsghdr {
	char	*msg_name;		/* optional address */
	int	msg_namelen;		/* size of address */
	struct	bsd_iovec *msg_iov;		/* scatter/gather array */
	int	msg_iovlen;		/* # elements in msg_iov */
	char	*msg_accrights;		/* access rights sent/received */
	int	msg_accrightslen;
};
#endif

/*
 * howto arguments for shutdown(2), specified by Posix.1g.
 */
#define	BSD_SHUT_RD		0		/* shut down the reading side */
#define	BSD_SHUT_WR		1		/* shut down the writing side */
#define	BSD_SHUT_RDWR	2		/* shut down both sides */

/* we cheat and use the SHUT_XX defines for these */
#define BSD_PRU_FLUSH_RD     BSD_SHUT_RD
#define BSD_PRU_FLUSH_WR     BSD_SHUT_WR
#define BSD_PRU_FLUSH_RDWR   BSD_SHUT_RDWR


#if __BSD_VISIBLE
/*
 * sendfile(2) header/trailer struct
 */
struct bsd_sf_hdtr {
	struct bsd_iovec *headers;	/* pointer to an array of header struct iovec's */
	int hdr_cnt;		/* number of header iovec's */
	struct bsd_iovec *trailers;	/* pointer to an array of trailer struct iovec's */
	int trl_cnt;		/* number of trailer iovec's */
};

/*
 * Sendfile-specific flag(s)
 */
#define	BSD_SF_NODISKIO     0x00000001
#define	BSD_SF_MNOWAIT	0x00000002
#define	BSD_SF_SYNC		0x00000004
#endif

#ifndef	_KERNEL

#include <sys/bsd_cdefs.h>

__BEGIN_DECLS
int	accept(int, struct bsd_sockaddr * __restrict, bsd_socklen_t * __restrict);
int	bind(int, const struct bsd_sockaddr *, bsd_socklen_t);
int	connect(int, const struct bsd_sockaddr *, bsd_socklen_t);
int	getpeername(int, struct bsd_sockaddr * __restrict, bsd_socklen_t * __restrict);
int	getsockname(int, struct bsd_sockaddr * __restrict, bsd_socklen_t * __restrict);
int	getsockopt(int, int, int, void * __restrict, bsd_socklen_t * __restrict);
int	listen(int, int);
bsd_ssize_t	recv(int, void *, bsd_size_t, int);
bsd_ssize_t	recvfrom(int, void *, bsd_size_t, int, struct bsd_sockaddr * __restrict, bsd_socklen_t * __restrict);
bsd_ssize_t	recvmsg(int, struct bsd_msghdr *, int);
bsd_ssize_t	send(int, const void *, bsd_size_t, int);
bsd_ssize_t	sendto(int, const void *,
	    bsd_size_t, int, const struct bsd_sockaddr *, bsd_socklen_t);
bsd_ssize_t	sendmsg(int, const struct bsd_msghdr *, int);
#if __BSD_VISIBLE
int	sendfile(int, int, bsd_off_t, bsd_size_t, struct bsd_sf_hdtr *, bsd_off_t *, int);
int	setfib(int);
#endif
int	setsockopt(int, int, int, const void *, bsd_socklen_t);
int	shutdown(int, int);
int	sockatmark(int);
int	bsd_socket(int, int, int);
int	socketpair(int, int, int, int *);
__END_DECLS

#endif /* !_KERNEL */

#ifdef _KERNEL
struct bsd_socket;

struct tcpcb *so_sototcpcb(struct bsd_socket *so);
struct inpcb *so_sotoinpcb(struct bsd_socket *so);
struct sockbuf *so_sockbuf_snd(struct bsd_socket *);
struct sockbuf *so_sockbuf_rcv(struct bsd_socket *);

int so_state_get(const struct bsd_socket *);
void so_state_set(struct bsd_socket *, int);

int so_options_get(const struct bsd_socket *);
void so_options_set(struct bsd_socket *, int);

int so_error_get(const struct bsd_socket *);
void so_error_set(struct bsd_socket *, int);

int so_linger_get(const struct bsd_socket *);
void so_linger_set(struct bsd_socket *, int);

struct bsd_protosw *so_protosw_get(const struct bsd_socket *);
void so_protosw_set(struct bsd_socket *, struct bsd_protosw *);

void so_sorwakeup_locked(struct bsd_socket *so);
void so_sowwakeup_locked(struct bsd_socket *so);

void so_sorwakeup(struct bsd_socket *so);
void so_sowwakeup(struct bsd_socket *so);

void so_lock(struct bsd_socket *so);
void so_unlock(struct bsd_socket *so);

void so_listeners_apply_all(struct bsd_socket *so, void (*func)(struct bsd_socket *, void *), void *arg);

#endif


#endif /* !_SYS_SOCKET_H_ */
