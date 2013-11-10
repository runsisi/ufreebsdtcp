/*-
 * Copyright (c) 2004 Doug Rabson
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
 *
 *	$FreeBSD: release/9.2.0/sys/net/firewire.h 194581 2009-06-21 10:29:31Z rdivacky $
 */

#ifndef _NET_FIREWIRE_H_
#define _NET_FIREWIRE_H_

#define FW_ENCAP_UNFRAG		0
#define FW_ENCAP_FIRST		1
#define FW_ENCAP_LAST		2
#define FW_ENCAP_NEXT		3

union fw_encap {
		bsd_uint32_t ul[2];
		struct {
#if BYTE_ORDER == BIG_ENDIAN
			bsd_uint32_t lf		:2;
			bsd_uint32_t reserved	:14;
			bsd_uint32_t ether_type	:16;
#else
			bsd_uint32_t ether_type	:16;
			bsd_uint32_t reserved	:14;
			bsd_uint32_t lf		:2;
#endif
		} unfrag;
		struct {
#if BYTE_ORDER == BIG_ENDIAN
			bsd_uint32_t lf		:2;
			bsd_uint32_t reserved1	:2;
			bsd_uint32_t datagram_size	:12;
			bsd_uint32_t ether_type	:16;
			bsd_uint32_t dgl		:16;
			bsd_uint32_t reserved2	:16;
#else
			bsd_uint32_t ether_type	:16;
			bsd_uint32_t datagram_size	:12;
			bsd_uint32_t reserved1	:2;
			bsd_uint32_t lf		:2;
			bsd_uint32_t reserved2	:16;
			bsd_uint32_t dgl		:16;
#endif
		} firstfrag;
		struct {
#if BYTE_ORDER == BIG_ENDIAN
			bsd_uint32_t lf		:2;
			bsd_uint32_t reserved1	:2;
			bsd_uint32_t datagram_size	:12;
			bsd_uint32_t reserved2	:4;
			bsd_uint32_t fragment_offset :12;
			bsd_uint32_t dgl		:16;
			bsd_uint32_t reserved3	:16;
#else
			bsd_uint32_t fragment_offset :12;
			bsd_uint32_t reserved2	:4;
			bsd_uint32_t datagram_size	:12;
			bsd_uint32_t reserved1	:2;
			bsd_uint32_t lf		:2;
			bsd_uint32_t reserved3	:16;
			bsd_uint32_t dgl		:16;
#endif
		} nextfrag;
};

#define MTAG_FIREWIRE			1394
#define MTAG_FIREWIRE_HWADDR		0
#define MTAG_FIREWIRE_SENDER_EUID	1

struct fw_hwaddr {
	bsd_uint32_t		sender_unique_ID_hi;
	bsd_uint32_t		sender_unique_ID_lo;
	bsd_uint8_t			sender_max_rec;
	bsd_uint8_t			sspd;
	bsd_uint16_t		sender_unicast_FIFO_hi;
	bsd_uint32_t		sender_unicast_FIFO_lo;
};

/*
 * BPF wants to see one of these.
 */
struct fw_bpfhdr {
	bsd_uint8_t			firewire_dhost[8];
	bsd_uint8_t			firewire_shost[8];
	bsd_uint16_t		firewire_type;
};

#ifdef _KERNEL

/*
 * A structure to track the reassembly of a link-level fragmented
 * datagram.
 */
struct fw_reass {
	STAILQ_ENTRY(fw_reass)	fr_link;
	bsd_uint32_t		fr_id;		/* host+dgl */
	struct mbuf		*fr_frags;	/* chain of frags */
};
STAILQ_HEAD(fw_reass_list, fw_reass);

struct fw_com {
	struct ifnet		*fc_ifp;
	struct fw_hwaddr	fc_hwaddr;
	struct firewire_comm	*fc_fc;
	bsd_uint8_t			fc_broadcast_channel;
	bsd_uint8_t			fc_speed;	/* our speed */
	bsd_uint16_t		fc_node;	/* our nodeid */
	struct fw_reass_list	fc_frags;	/* partial datagrams */
};
#define	IFP2FWC(ifp)	((struct fw_com *)(ifp)->if_l2com)

extern	void	firewire_input(struct ifnet *ifp, struct mbuf *m, bsd_uint16_t src);
extern	void	firewire_ifattach(struct ifnet *, struct fw_hwaddr *);
extern	void	firewire_ifdetach(struct ifnet *);
extern	void	firewire_busreset(struct ifnet *);
extern	int	firewire_ioctl(struct ifnet *, u_long, caddr_t);

#endif /* !_KERNEL */

#endif /* !_NET_FIREWIRE_H_ */
