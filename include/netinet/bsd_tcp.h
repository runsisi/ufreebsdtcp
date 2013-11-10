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
 *	@(#)tcp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: release/9.2.0/sys/netinet/tcp.h 247525 2013-03-01 03:04:57Z jhb $
 */

#ifndef _BSD_NETINET_TCP_H_
#define _BSD_NETINET_TCP_H_

#include <sys/bsd_cdefs.h>
#include <sys/bsd_types.h>

#if __BSD_VISIBLE

typedef	bsd_uint32_t tcp_seq;

#define tcp6_seq	tcp_seq	/* for KAME src sync over BSD*'s */
#define tcp6hdr		bsd_tcphdr	/* for KAME src sync over BSD*'s */

/*
 * TCP header.
 * Per RFC 793, September, 1981.
 */
struct bsd_tcphdr {
	u_short	th_sport;		/* source port */
	u_short	th_dport;		/* destination port */
	tcp_seq	th_seq;			/* sequence number */
	tcp_seq	th_ack;			/* acknowledgement number */
#if BSD_BYTE_ORDER == BSD_LITTLE_ENDIAN
	u_char	th_x2:4,		/* (unused) */
		th_off:4;		/* data offset */
#endif
#if BSD_BYTE_ORDER == BSD_BIG_ENDIAN
	u_char	th_off:4,		/* data offset */
		th_x2:4;		/* (unused) */
#endif
	u_char	th_flags;
#define	BSD_TH_FIN	0x01
#define	BSD_TH_SYN	0x02
#define	BSD_TH_RST	0x04
#define	BSD_TH_PUSH	0x08
#define	BSD_TH_ACK	0x10
#define	BSD_TH_URG	0x20
#define	BSD_TH_ECE	0x40
#define	BSD_TH_CWR	0x80
#define	BSD_TH_FLAGS	(BSD_TH_FIN|BSD_TH_SYN|BSD_TH_RST|BSD_TH_PUSH|BSD_TH_ACK|BSD_TH_URG|BSD_TH_ECE|BSD_TH_CWR)
#define	PRINT_TH_FLAGS	"\20\1FIN\2SYN\3RST\4PUSH\5ACK\6URG\7ECE\10CWR"

	u_short	th_win;			/* window */
	u_short	th_sum;			/* checksum */
	u_short	th_urp;			/* urgent pointer */
};

#define	BSD_TCPOPT_EOL		0
#define	   BSD_TCPOLEN_EOL			1
#define	BSD_TCPOPT_PAD		0		/* padding after EOL */
#define	   BSD_TCPOLEN_PAD			1
#define	BSD_TCPOPT_NOP		1
#define	   BSD_TCPOLEN_NOP			1
#define	BSD_TCPOPT_MAXSEG		2
#define    BSD_TCPOLEN_MAXSEG		4
#define BSD_TCPOPT_WINDOW		3
#define    BSD_TCPOLEN_WINDOW		3
#define BSD_TCPOPT_SACK_PERMITTED	4
#define    BSD_TCPOLEN_SACK_PERMITTED	2
#define BSD_TCPOPT_SACK		5
#define	   BSD_TCPOLEN_SACKHDR		2
#define    BSD_TCPOLEN_SACK			8	/* 2*sizeof(tcp_seq) */
#define BSD_TCPOPT_TIMESTAMP	8
#define    BSD_TCPOLEN_TIMESTAMP		10
#define    BSD_TCPOLEN_TSTAMP_APPA		(BSD_TCPOLEN_TIMESTAMP+2) /* appendix A */
#define	BSD_TCPOPT_SIGNATURE	19		/* Keyed MD5: RFC 2385 */
#define	   BSD_TCPOLEN_SIGNATURE		18

/* Miscellaneous constants */
#define	BSD_MAX_SACK_BLKS	6	/* Max # SACK blocks stored at receiver side */
#define	BSD_TCP_MAX_SACK	4	/* MAX # SACKs sent in any segment */


/*
 * The default maximum segment size (MSS) to be used for new TCP connections
 * when path MTU discovery is not enabled.
 *
 * RFC879 derives the default MSS from the largest datagram size hosts are
 * minimally required to handle directly or through IP reassembly minus the
 * size of the IP and TCP header.  With IPv6 the minimum MTU is specified
 * in RFC2460.
 *
 * For IPv4 the MSS is 576 - sizeof(struct tcpiphdr)
 * For IPv6 the MSS is IPV6_MMTU - sizeof(struct ip6_hdr) - sizeof(struct tcphdr)
 *
 * We use explicit numerical definition here to avoid header pollution.
 */
#define	BSD_TCP_MSS		536
#define	BSD_TCP6_MSS	1220

/*
 * Limit the lowest MSS we accept for path MTU discovery and the TCP SYN MSS
 * option.  Allowing low values of MSS can consume significant resources and
 * be used to mount a resource exhaustion attack.
 * Connections requesting lower MSS values will be rounded up to this value
 * and the IP_DF flag will be cleared to allow fragmentation along the path.
 *
 * See tcp_subr.c tcp_minmss SYSCTL declaration for more comments.  Setting
 * it to "0" disables the minmss check.
 *
 * The default value is fine for TCP across the Internet's smallest official
 * link MTU (256 bytes for AX.25 packet radio).  However, a connection is very
 * unlikely to come across such low MTU interfaces these days (anno domini 2003).
 */
#define	BSD_TCP_MINMSS 216

#define	BSD_TCP_MAXWIN	65535	/* largest value for (unscaled) window */
#define	BSD_TTCP_CLIENT_SND_WND	4096	/* dflt send window for T/TCP client */

#define BSD_TCP_MAX_WINSHIFT	14	/* maximum window shift */

#define BSD_TCP_MAXBURST		4	/* maximum segments in a burst */

#define BSD_TCP_MAXHLEN	(0xf<<2)	/* max length of header in bytes */
#define BSD_TCP_MAXOLEN	(BSD_TCP_MAXHLEN - sizeof(struct bsd_tcphdr))
					/* max space left for options */
#endif /* __BSD_VISIBLE */

/*
 * User-settable options (used with setsockopt).  These are discrete
 * values and are not masked together.  Some values appear to be
 * bitmasks for historical reasons.
 */
#define	BSD_TCP_NODELAY	1	/* don't delay send to coalesce packets */
#if __BSD_VISIBLE
#define	BSD_TCP_MAXSEG	2	/* set maximum segment size */
#define BSD_TCP_NOPUSH	4	/* don't push last block of write */
#define BSD_TCP_NOOPT	8	/* don't use TCP options */
#define BSD_TCP_MD5SIG	16	/* use MD5 digests (RFC2385) */
#define	BSD_TCP_INFO	32	/* retrieve tcp_info structure */
#define	BSD_TCP_CONGESTION	64	/* get/set congestion control algorithm */
#define	BSD_TCP_KEEPINIT	128	/* N, time to establish connection */
#define	BSD_TCP_KEEPIDLE	256	/* L,N,X start keeplives after this period */
#define	BSD_TCP_KEEPINTVL	512	/* L,N interval between keepalives */
#define	BSD_TCP_KEEPCNT	1024	/* L,N number of keepalives before close */

/* Start of reserved space for third-party user-settable options. */
#define	BSD_TCP_VENDOR	BSD_SO_VENDOR

#define	BSD_TCP_CA_NAME_MAX	16	/* max congestion control name length */

#define	BSD_TCPI_OPT_TIMESTAMPS	0x01
#define	BSD_TCPI_OPT_SACK		0x02
#define	BSD_TCPI_OPT_WSCALE		0x04
#define	BSD_TCPI_OPT_ECN		0x08
#define	BSD_TCPI_OPT_TOE		0x10

/*
 * The TCP_INFO socket option comes from the Linux 2.6 TCP API, and permits
 * the caller to query certain information about the state of a TCP
 * connection.  We provide an overlapping set of fields with the Linux
 * implementation, but since this is a fixed size structure, room has been
 * left for growth.  In order to maximize potential future compatibility with
 * the Linux API, the same variable names and order have been adopted, and
 * padding left to make room for omitted fields in case they are added later.
 *
 * XXX: This is currently an unstable ABI/API, in that it is expected to
 * change.
 */
struct tcp_info {
	bsd_uint8_t	tcpi_state;		/* TCP FSM state. */
	bsd_uint8_t	__tcpi_ca_state;
	bsd_uint8_t	__tcpi_retransmits;
	bsd_uint8_t	__tcpi_probes;
	bsd_uint8_t	__tcpi_backoff;
	bsd_uint8_t	tcpi_options;		/* Options enabled on conn. */
	bsd_uint8_t	tcpi_snd_wscale:4,	/* RFC1323 send shift value. */
			tcpi_rcv_wscale:4;	/* RFC1323 recv shift value. */

	bsd_uint32_t	tcpi_rto;		/* Retransmission timeout (usec). */
	bsd_uint32_t	__tcpi_ato;
	bsd_uint32_t	tcpi_snd_mss;		/* Max segment size for send. */
	bsd_uint32_t	tcpi_rcv_mss;		/* Max segment size for receive. */

	bsd_uint32_t	__tcpi_unacked;
	bsd_uint32_t	__tcpi_sacked;
	bsd_uint32_t	__tcpi_lost;
	bsd_uint32_t	__tcpi_retrans;
	bsd_uint32_t	__tcpi_fackets;

	/* Times; measurements in usecs. */
	bsd_uint32_t	__tcpi_last_data_sent;
	bsd_uint32_t	__tcpi_last_ack_sent;	/* Also unimpl. on Linux? */
	bsd_uint32_t	tcpi_last_data_recv;	/* Time since last recv data. */
	bsd_uint32_t	__tcpi_last_ack_recv;

	/* Metrics; variable units. */
	bsd_uint32_t	__tcpi_pmtu;
	bsd_uint32_t	__tcpi_rcv_ssthresh;
	bsd_uint32_t	tcpi_rtt;		/* Smoothed RTT in usecs. */
	bsd_uint32_t	tcpi_rttvar;		/* RTT variance in usecs. */
	bsd_uint32_t	tcpi_snd_ssthresh;	/* Slow start threshold. */
	bsd_uint32_t	tcpi_snd_cwnd;		/* Send congestion window. */
	bsd_uint32_t	__tcpi_advmss;
	bsd_uint32_t	__tcpi_reordering;

	bsd_uint32_t	__tcpi_rcv_rtt;
	bsd_uint32_t	tcpi_rcv_space;		/* Advertised recv window. */

	/* FreeBSD extensions to tcp_info. */
	bsd_uint32_t	tcpi_snd_wnd;		/* Advertised send window. */
	bsd_uint32_t	tcpi_snd_bwnd;		/* No longer used. */
	bsd_uint32_t	tcpi_snd_nxt;		/* Next egress seqno */
	bsd_uint32_t	tcpi_rcv_nxt;		/* Next ingress seqno */
	bsd_uint32_t	tcpi_toe_tid;		/* HWTID for TOE endpoints */
	bsd_uint32_t	tcpi_snd_rexmitpack;	/* Retransmitted packets */
	bsd_uint32_t	tcpi_rcv_ooopack;	/* Out-of-order packets */
	bsd_uint32_t	tcpi_snd_zerowin;	/* Zero-sized windows sent */

	/* Padding to grow without breaking ABI. */
	bsd_uint32_t	__tcpi_pad[26];		/* Padding. */
};
#endif

#endif /* !_NETINET_TCP_H_ */
