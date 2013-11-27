/*-
 * Copyright (c) 1982, 1986, 1988, 1990, 1993
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
 *	@(#)ip_output.c	8.3 (Berkeley) 1/21/94
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/netinet/ip_output.c 253281 2013-07-12 18:54:47Z trociny $");

#include "opt_ipfw.h"
#include "opt_ipsec.h"
#include "opt_route.h"
#include "opt_mbuf_stress_test.h"
#include "opt_mpath.h"
#include "opt_sctp.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_mbuf.h>
#include <sys/bsd_priv.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_protosw.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_socketvar.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_ucred.h>

#include <net/if.h>
#include <net/if_llatbl.h>
#include <net/netisr.h>
#include <net/pfil.h>
#include <net/route.h>
#include <net/flowtable.h>
#ifdef RADIX_MPATH
#include <net/radix_mpath.h>
#endif
#include <net/vnet.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/in_var.h>
#include <netinet/ip_var.h>
#include <netinet/ip_options.h>
#ifdef SCTP
#include <netinet/sctp.h>
#include <netinet/sctp_crc32.h>
#endif

#ifdef IPSEC
#include <netinet/ip_ipsec.h>
#include <netipsec/ipsec.h>
#endif /* IPSEC*/

#include <machine/bsd_in_cksum.h>

//#include <security/mac/mac_framework.h>

VNET_DEFINE(u_short, ip_id);
extern int brs_ip_output(struct mbuf *m, int vcid);

#ifdef MBUF_STRESS_TEST
static int mbuf_frag_size = 0;
SYSCTL_INT(_net_inet_ip, OID_AUTO, mbuf_frag_size, CTLFLAG_RW,
	&mbuf_frag_size, 0, "Fragment outgoing mbufs to this size");
#endif

static void	ip_mloopback
	(struct ifnet *, struct mbuf *, struct sockaddr_in *, int);


extern int in_mcast_loop;
extern	struct protosw inetsw[];

/*
 * IP output.  The packet in mbuf chain m contains a skeletal IP
 * header (with len, off, ttl, proto, tos, src, dst).
 * ip_len and ip_off are in host format.
 * The mbuf chain containing the packet will be freed.
 * The mbuf opt, if present, will not be freed.
 * If route ro is present and has ro_rt initialized, route lookup would be
 * skipped and ro->ro_rt would be used. If ro is present but ro->ro_rt is NULL,
 * then result of route lookup is stored in ro->ro_rt.
 *
 * In the IP forwarding case, the packet will arrive with options already
 * inserted, so must have a NULL opt pointer.
 */
int
ip_output(struct mbuf *m, struct mbuf *opt, struct route *ro, int flags,
    struct ip_moptions *imo, struct inpcb *inp)
{
    struct ip *ip;
    int hlen = sizeof (struct ip);
    int error = 0;
    int sw_csum;
    struct route iproute;

    M_ASSERTPKTHDR(m);

    if (inp != NULL) {
        INP_LOCK_ASSERT(inp);
        M_SETFIB(m, inp->inp_inc.inc_fibnum);
        if (inp->inp_flags & (INP_HW_FLOWID|INP_SW_FLOWID)) {
            m->m_pkthdr.flowid = inp->inp_flowid;
            m->m_flags |= M_FLOWID;
        }
    }

    if (ro == NULL) {
        ro = &iproute;
        bzero(ro, sizeof (*ro));
    }

#ifdef FLOWTABLE
    if (ro->ro_rt == NULL) {
        struct flentry *fle;

        /*
         * The flow table returns route entries valid for up to 30
         * seconds; we rely on the remainder of ip_output() taking no
         * longer than that long for the stability of ro_rt. The
         * flow ID assignment must have happened before this point.
         */
        fle = flowtable_lookup_mbuf(V_ip_ft, m, AF_INET);
        if (fle != NULL)
            flow_to_route(fle, ro);
    }
#endif

    if (opt) {
        int len = 0;
        m = ip_insertoptions(m, opt, &len);
        if (len != 0)
            hlen = len; /* ip->ip_hl is updated above */
    }
    ip = mtod(m, struct ip *);

    /*
     * Fill in IP header.  If we are not allowing fragmentation,
     * then the ip_id field is meaningless, but we don't set it
     * to zero.  Doing so causes various problems when devices along
     * the path (routers, load balancers, firewalls, etc.) illegally
     * disable DF on our packet.  Note that a 16-bit counter
     * will wrap around in less than 10 seconds at 100 Mbit/s on a
     * medium with MTU 1500.  See Steven M. Bellovin, "A Technique
     * for Counting NATted Hosts", Proc. IMW'02, available at
     * <http://www.cs.columbia.edu/~smb/papers/fnat.pdf>.
     */
    if ((flags & (IP_FORWARDING|IP_RAWOUTPUT)) == 0) {
        ip->ip_v = IPVERSION;
        ip->ip_hl = hlen >> 2;
        #if 0	// runsisi AT hust.edu.cn @2013/11/13
        ip->ip_id = ip_newid();
        IPSTAT_INC(ips_localout);
        #endif  // ---------------------- @2013/11/13
    } else {
        /* Header already set, fetch hlen from there */
        hlen = ip->ip_hl << 2;
    }

    /* 127/8 must not appear on wire - RFC1122. */
    if ((ntohl(ip->ip_dst.s_addr) >> IN_CLASSA_NSHIFT) == IN_LOOPBACKNET ||
        (ntohl(ip->ip_src.s_addr) >> IN_CLASSA_NSHIFT) == IN_LOOPBACKNET) {
        /*if ((ifp->if_flags & IFF_LOOPBACK) == 0)*/ {
            #if 0	// runsisi AT hust.edu.cn @2013/11/13
            IPSTAT_INC(ips_badaddr);
            #endif 	// ---------------------- @2013/11/13
            error = EADDRNOTAVAIL;
            goto bad;
        }
    }

    m->m_pkthdr.csum_flags |= CSUM_IP;
    sw_csum = m->m_pkthdr.csum_flags /*& ~ifp->if_hwassist*/;
    if (sw_csum & CSUM_DELAY_DATA) {
        in_delayed_cksum(m);
        sw_csum &= ~CSUM_DELAY_DATA;
    }
#ifdef SCTP
    if (sw_csum & CSUM_SCTP) {
        sctp_delayed_cksum(m, (uint32_t)(ip->ip_hl << 2));
        sw_csum &= ~CSUM_SCTP;
    }
#endif
    m->m_pkthdr.csum_flags &= 0/*ifp->if_hwassist*/;

    error = brs_ip_output(m, m->m_fibnum);

done:
    return (error);
bad:
    m_freem(m);
    goto done;
}

/*
 * Create a chain of fragments which fit the given mtu. m_frag points to the
 * mbuf to be fragmented; on return it points to the chain with the fragments.
 * Return 0 if no error. If error, m_frag may contain a partially built
 * chain of fragments that should be freed by the caller.
 *
 * if_hwassist_flags is the hw offload capabilities (see if_data.ifi_hwassist)
 * sw_csum contains the delayed checksums flags (e.g., CSUM_DELAY_IP).
 */
int
ip_fragment(struct ip *ip, struct mbuf **m_frag, int mtu,
    u_long if_hwassist_flags, int sw_csum)
{
	int error = 0;
	int hlen = ip->ip_hl << 2;
	int len = (mtu - hlen) & ~7;	/* size of payload in each fragment */
	int off;
	struct mbuf *m0 = *m_frag;	/* the original packet		*/
	int firstlen;
	struct mbuf **mnext;
	int nfrags;

	if (ip->ip_off & IP_DF) {	/* Fragmentation not allowed */
		IPSTAT_INC(ips_cantfrag);
		return EMSGSIZE;
	}

	/*
	 * Must be able to put at least 8 bytes per fragment.
	 */
	if (len < 8)
		return EMSGSIZE;

	/*
	 * If the interface will not calculate checksums on
	 * fragmented packets, then do it here.
	 */
	if (m0->m_pkthdr.csum_flags & CSUM_DELAY_DATA) {
		in_delayed_cksum(m0);
		m0->m_pkthdr.csum_flags &= ~CSUM_DELAY_DATA;
	}
#ifdef SCTP
	if (m0->m_pkthdr.csum_flags & CSUM_SCTP) {
		sctp_delayed_cksum(m0, hlen);
		m0->m_pkthdr.csum_flags &= ~CSUM_SCTP;
	}
#endif
	if (len > PAGE_SIZE) {
		/* 
		 * Fragment large datagrams such that each segment 
		 * contains a multiple of PAGE_SIZE amount of data, 
		 * plus headers. This enables a receiver to perform 
		 * page-flipping zero-copy optimizations.
		 *
		 * XXX When does this help given that sender and receiver
		 * could have different page sizes, and also mtu could
		 * be less than the receiver's page size ?
		 */
		int newlen;
		struct mbuf *m;

		for (m = m0, off = 0; m && (off+m->m_len) <= mtu; m = m->m_next)
			off += m->m_len;

		/*
		 * firstlen (off - hlen) must be aligned on an 
		 * 8-byte boundary
		 */
		if (off < hlen)
			goto smart_frag_failure;
		off = ((off - hlen) & ~7) + hlen;
		newlen = (~PAGE_MASK) & mtu;
		if ((newlen + sizeof (struct ip)) > mtu) {
			/* we failed, go back the default */
smart_frag_failure:
			newlen = len;
			off = hlen + len;
		}
		len = newlen;

	} else {
		off = hlen + len;
	}

	firstlen = off - hlen;
	mnext = &m0->m_nextpkt;		/* pointer to next packet */

	/*
	 * Loop through length of segment after first fragment,
	 * make new header and copy data of each part and link onto chain.
	 * Here, m0 is the original packet, m is the fragment being created.
	 * The fragments are linked off the m_nextpkt of the original
	 * packet, which after processing serves as the first fragment.
	 */
	for (nfrags = 1; off < ip->ip_len; off += len, nfrags++) {
		struct ip *mhip;	/* ip header on the fragment */
		struct mbuf *m;
		int mhlen = sizeof (struct ip);

		MGETHDR(m, M_DONTWAIT, MT_DATA);
		if (m == NULL) {
			error = ENOBUFS;
			IPSTAT_INC(ips_odropped);
			goto done;
		}
		m->m_flags |= (m0->m_flags & M_MCAST) | M_FRAG;
		/*
		 * In the first mbuf, leave room for the link header, then
		 * copy the original IP header including options. The payload
		 * goes into an additional mbuf chain returned by m_copym().
		 */
		m->m_data += max_linkhdr;
		mhip = mtod(m, struct ip *);
		*mhip = *ip;
		if (hlen > sizeof (struct ip)) {
			mhlen = ip_optcopy(ip, mhip) + sizeof (struct ip);
			mhip->ip_v = IPVERSION;
			mhip->ip_hl = mhlen >> 2;
		}
		m->m_len = mhlen;
		/* XXX do we need to add ip->ip_off below ? */
		mhip->ip_off = ((off - hlen) >> 3) + ip->ip_off;
		if (off + len >= ip->ip_len) {	/* last fragment */
			len = ip->ip_len - off;
			m->m_flags |= M_LASTFRAG;
		} else
			mhip->ip_off |= IP_MF;
		mhip->ip_len = htons((u_short)(len + mhlen));
		m->m_next = m_copym(m0, off, len, M_DONTWAIT);
		if (m->m_next == NULL) {	/* copy failed */
			m_free(m);
			error = ENOBUFS;	/* ??? */
			IPSTAT_INC(ips_odropped);
			goto done;
		}
		m->m_pkthdr.len = mhlen + len;
		m->m_pkthdr.rcvif = NULL;
#ifdef MAC
		mac_netinet_fragment(m0, m);
#endif
		m->m_pkthdr.csum_flags = m0->m_pkthdr.csum_flags;
		mhip->ip_off = htons(mhip->ip_off);
		mhip->ip_sum = 0;
		if (sw_csum & CSUM_DELAY_IP)
			mhip->ip_sum = in_cksum(m, mhlen);
		*mnext = m;
		mnext = &m->m_nextpkt;
	}
	IPSTAT_ADD(ips_ofragments, nfrags);

	/* set first marker for fragment chain */
	m0->m_flags |= M_FIRSTFRAG | M_FRAG;
	m0->m_pkthdr.csum_data = nfrags;

	/*
	 * Update first fragment by trimming what's been copied out
	 * and updating header.
	 */
	m_adj(m0, hlen + firstlen - ip->ip_len);
	m0->m_pkthdr.len = hlen + firstlen;
	ip->ip_len = htons((u_short)m0->m_pkthdr.len);
	ip->ip_off |= IP_MF;
	ip->ip_off = htons(ip->ip_off);
	ip->ip_sum = 0;
	if (sw_csum & CSUM_DELAY_IP)
		ip->ip_sum = in_cksum(m0, hlen);

done:
	*m_frag = m0;
	return error;
}

void
in_delayed_cksum(struct mbuf *m)
{
	struct ip *ip;
	u_short csum, offset;

	ip = mtod(m, struct ip *);
	offset = ip->ip_hl << 2 ;
	csum = in_cksum_skip(m, ip->ip_len, offset);
	if (m->m_pkthdr.csum_flags & CSUM_UDP && csum == 0)
		csum = 0xffff;
	offset += m->m_pkthdr.csum_data;	/* checksum offset */

	if (offset + sizeof(u_short) > m->m_len) {
		printf("delayed m_pullup, m->len: %d  off: %d  p: %d\n",
		    m->m_len, offset, ip->ip_p);
		/*
		 * XXX
		 * this shouldn't happen, but if it does, the
		 * correct behavior may be to insert the checksum
		 * in the appropriate next mbuf in the chain.
		 */
		return;
	}
	*(u_short *)(m->m_data + offset) = csum;
}

/*
 * IP socket option processing.
 */
int
ip_ctloutput(struct socket *so, struct sockopt *sopt)
{
	struct	inpcb *inp = sotoinpcb(so);
	int	error, optval;

	error = optval = 0;
	if (sopt->sopt_level != IPPROTO_IP) {
		error = EINVAL;

		if (sopt->sopt_level == SOL_SOCKET &&
		    sopt->sopt_dir == SOPT_SET) {
			switch (sopt->sopt_name) {
			case SO_REUSEADDR:
				INP_WLOCK(inp);
				if ((so->so_options & SO_REUSEADDR) != 0)
					inp->inp_flags2 |= INP_REUSEADDR;
				else
					inp->inp_flags2 &= ~INP_REUSEADDR;
				INP_WUNLOCK(inp);
				error = 0;
				break;
			case SO_REUSEPORT:
				INP_WLOCK(inp);
				if ((so->so_options & SO_REUSEPORT) != 0)
					inp->inp_flags2 |= INP_REUSEPORT;
				else
					inp->inp_flags2 &= ~INP_REUSEPORT;
				INP_WUNLOCK(inp);
				error = 0;
				break;
			case SO_SETFIB:
				INP_WLOCK(inp);
				inp->inp_inc.inc_fibnum = so->so_fibnum;
				INP_WUNLOCK(inp);
				error = 0;
				break;
			default:
				break;
			}
		}
		return (error);
	}

	switch (sopt->sopt_dir) {
	case SOPT_SET:
		switch (sopt->sopt_name) {
        #if 0	// runsisi AT hust.edu.cn @2013/11/07
		case IP_OPTIONS:
#ifdef notyet
		case IP_RETOPTS:
#endif
		{
			struct mbuf *m;
			if (sopt->sopt_valsize > MLEN) {
				error = EMSGSIZE;
				break;
			}
			MGET(m, sopt->sopt_td ? M_WAIT : M_DONTWAIT, MT_DATA);
			if (m == NULL) {
				error = ENOBUFS;
				break;
			}
			m->m_len = sopt->sopt_valsize;
			error = sooptcopyin(sopt, mtod(m, char *), m->m_len,
					    m->m_len);
			if (error) {
				m_free(m);
				break;
			}
			INP_WLOCK(inp);
			error = ip_pcbopts(inp, sopt->sopt_name, m);
			INP_WUNLOCK(inp);
			return (error);
		}
        #endif 	// ---------------------- @2013/11/07

		case IP_BINDANY:
			if (sopt->sopt_td != NULL) {
				error = priv_check(sopt->sopt_td,
				    PRIV_NETINET_BINDANY);
				if (error)
					break;
			}
			/* FALLTHROUGH */
		case IP_TOS:
		case IP_TTL:
		case IP_MINTTL:
		case IP_RECVOPTS:
		case IP_RECVRETOPTS:
		case IP_RECVDSTADDR:
		case IP_RECVTTL:
		case IP_RECVIF:
		case IP_FAITH:
		case IP_ONESBCAST:
		case IP_DONTFRAG:
		case IP_RECVTOS:
			error = sooptcopyin(sopt, &optval, sizeof optval,
					    sizeof optval);
			if (error)
				break;

			switch (sopt->sopt_name) {
			case IP_TOS:
				inp->inp_ip_tos = optval;
				break;

			case IP_TTL:
				inp->inp_ip_ttl = optval;
				break;

			case IP_MINTTL:
				if (optval >= 0 && optval <= MAXTTL)
					inp->inp_ip_minttl = optval;
				else
					error = EINVAL;
				break;

#define	OPTSET(bit) do {						\
	INP_WLOCK(inp);							\
	if (optval)							\
		inp->inp_flags |= bit;					\
	else								\
		inp->inp_flags &= ~bit;					\
	INP_WUNLOCK(inp);						\
} while (0)

			case IP_RECVOPTS:
				OPTSET(INP_RECVOPTS);
				break;

			case IP_RECVRETOPTS:
				OPTSET(INP_RECVRETOPTS);
				break;

			case IP_RECVDSTADDR:
				OPTSET(INP_RECVDSTADDR);
				break;

			case IP_RECVTTL:
				OPTSET(INP_RECVTTL);
				break;

			case IP_RECVIF:
				OPTSET(INP_RECVIF);
				break;

			case IP_FAITH:
				OPTSET(INP_FAITH);
				break;

			case IP_ONESBCAST:
				OPTSET(INP_ONESBCAST);
				break;
			case IP_DONTFRAG:
				OPTSET(INP_DONTFRAG);
				break;
			case IP_BINDANY:
				OPTSET(INP_BINDANY);
				break;
			case IP_RECVTOS:
				OPTSET(INP_RECVTOS);
				break;
			}
			break;
#undef OPTSET

        #if 0	// runsisi AT hust.edu.cn @2013/11/07
        /*
		 * Multicast socket options are processed by the in_mcast
		 * module.
		 */
		case IP_MULTICAST_IF:
		case IP_MULTICAST_VIF:
		case IP_MULTICAST_TTL:
		case IP_MULTICAST_LOOP:
		case IP_ADD_MEMBERSHIP:
		case IP_DROP_MEMBERSHIP:
		case IP_ADD_SOURCE_MEMBERSHIP:
		case IP_DROP_SOURCE_MEMBERSHIP:
		case IP_BLOCK_SOURCE:
		case IP_UNBLOCK_SOURCE:
		case IP_MSFILTER:
		case MCAST_JOIN_GROUP:
		case MCAST_LEAVE_GROUP:
		case MCAST_JOIN_SOURCE_GROUP:
		case MCAST_LEAVE_SOURCE_GROUP:
		case MCAST_BLOCK_SOURCE:
		case MCAST_UNBLOCK_SOURCE:
			error = inp_setmoptions(inp, sopt);
			break;
        #endif 	// ---------------------- @2013/11/07

		case IP_PORTRANGE:
			error = sooptcopyin(sopt, &optval, sizeof optval,
					    sizeof optval);
			if (error)
				break;

			INP_WLOCK(inp);
			switch (optval) {
			case IP_PORTRANGE_DEFAULT:
				inp->inp_flags &= ~(INP_LOWPORT);
				inp->inp_flags &= ~(INP_HIGHPORT);
				break;

			case IP_PORTRANGE_HIGH:
				inp->inp_flags &= ~(INP_LOWPORT);
				inp->inp_flags |= INP_HIGHPORT;
				break;

			case IP_PORTRANGE_LOW:
				inp->inp_flags &= ~(INP_HIGHPORT);
				inp->inp_flags |= INP_LOWPORT;
				break;

			default:
				error = EINVAL;
				break;
			}
			INP_WUNLOCK(inp);
			break;

#ifdef IPSEC
		case IP_IPSEC_POLICY:
		{
			caddr_t req;
			struct mbuf *m;

			if ((error = soopt_getm(sopt, &m)) != 0) /* XXX */
				break;
			if ((error = soopt_mcopyin(sopt, m)) != 0) /* XXX */
				break;
			req = mtod(m, caddr_t);
			error = ipsec_set_policy(inp, sopt->sopt_name, req,
			    m->m_len, (sopt->sopt_td != NULL) ?
			    sopt->sopt_td->td_ucred : NULL);
			m_freem(m);
			break;
		}
#endif /* IPSEC */

		default:
			error = ENOPROTOOPT;
			break;
		}
		break;

	case SOPT_GET:
		switch (sopt->sopt_name) {
		case IP_OPTIONS:
		case IP_RETOPTS:
			if (inp->inp_options)
				error = sooptcopyout(sopt, 
						     mtod(inp->inp_options,
							  char *),
						     inp->inp_options->m_len);
			else
				sopt->sopt_valsize = 0;
			break;

		case IP_TOS:
		case IP_TTL:
		case IP_MINTTL:
		case IP_RECVOPTS:
		case IP_RECVRETOPTS:
		case IP_RECVDSTADDR:
		case IP_RECVTTL:
		case IP_RECVIF:
		case IP_PORTRANGE:
		case IP_FAITH:
		case IP_ONESBCAST:
		case IP_DONTFRAG:
		case IP_BINDANY:
		case IP_RECVTOS:
			switch (sopt->sopt_name) {

			case IP_TOS:
				optval = inp->inp_ip_tos;
				break;

			case IP_TTL:
				optval = inp->inp_ip_ttl;
				break;

			case IP_MINTTL:
				optval = inp->inp_ip_minttl;
				break;

#define	OPTBIT(bit)	(inp->inp_flags & bit ? 1 : 0)

			case IP_RECVOPTS:
				optval = OPTBIT(INP_RECVOPTS);
				break;

			case IP_RECVRETOPTS:
				optval = OPTBIT(INP_RECVRETOPTS);
				break;

			case IP_RECVDSTADDR:
				optval = OPTBIT(INP_RECVDSTADDR);
				break;

			case IP_RECVTTL:
				optval = OPTBIT(INP_RECVTTL);
				break;

			case IP_RECVIF:
				optval = OPTBIT(INP_RECVIF);
				break;

			case IP_PORTRANGE:
				if (inp->inp_flags & INP_HIGHPORT)
					optval = IP_PORTRANGE_HIGH;
				else if (inp->inp_flags & INP_LOWPORT)
					optval = IP_PORTRANGE_LOW;
				else
					optval = 0;
				break;

			case IP_FAITH:
				optval = OPTBIT(INP_FAITH);
				break;

			case IP_ONESBCAST:
				optval = OPTBIT(INP_ONESBCAST);
				break;
			case IP_DONTFRAG:
				optval = OPTBIT(INP_DONTFRAG);
				break;
			case IP_BINDANY:
				optval = OPTBIT(INP_BINDANY);
				break;
			case IP_RECVTOS:
				optval = OPTBIT(INP_RECVTOS);
				break;
			}
			error = sooptcopyout(sopt, &optval, sizeof optval);
			break;

        #if 0	// runsisi AT hust.edu.cn @2013/11/07
        /*
		 * Multicast socket options are processed by the in_mcast
		 * module.
		 */
		case IP_MULTICAST_IF:
		case IP_MULTICAST_VIF:
		case IP_MULTICAST_TTL:
		case IP_MULTICAST_LOOP:
		case IP_MSFILTER:
			error = inp_getmoptions(inp, sopt);
			break;
        #endif 	// ---------------------- @2013/11/07

#ifdef IPSEC
		case IP_IPSEC_POLICY:
		{
			struct mbuf *m = NULL;
			caddr_t req = NULL;
			size_t len = 0;

			if (m != 0) {
				req = mtod(m, caddr_t);
				len = m->m_len;
			}
			error = ipsec_get_policy(sotoinpcb(so), req, len, &m);
			if (error == 0)
				error = soopt_mcopyout(sopt, m); /* XXX */
			if (error == 0)
				m_freem(m);
			break;
		}
#endif /* IPSEC */

		default:
			error = ENOPROTOOPT;
			break;
		}
		break;
	}
	return (error);
}

/*
 * Routine called from ip_output() to loop back a copy of an IP multicast
 * packet to the input queue of a specified interface.  Note that this
 * calls the output routine of the loopback "driver", but with an interface
 * pointer that might NOT be a loopback interface -- evil, but easier than
 * replicating that code here.
 */
static void
ip_mloopback(struct ifnet *ifp, struct mbuf *m, struct sockaddr_in *dst,
    int hlen)
{
	register struct ip *ip;
	struct mbuf *copym;

	/*
	 * Make a deep copy of the packet because we're going to
	 * modify the pack in order to generate checksums.
	 */
	copym = m_dup(m, M_DONTWAIT);
	if (copym != NULL && (copym->m_flags & M_EXT || copym->m_len < hlen))
		copym = m_pullup(copym, hlen);
	if (copym != NULL) {
		/* If needed, compute the checksum and mark it as valid. */
		if (copym->m_pkthdr.csum_flags & CSUM_DELAY_DATA) {
			in_delayed_cksum(copym);
			copym->m_pkthdr.csum_flags &= ~CSUM_DELAY_DATA;
			copym->m_pkthdr.csum_flags |=
			    CSUM_DATA_VALID | CSUM_PSEUDO_HDR;
			copym->m_pkthdr.csum_data = 0xffff;
		}
		/*
		 * We don't bother to fragment if the IP length is greater
		 * than the interface's MTU.  Can this possibly matter?
		 */
		ip = mtod(copym, struct ip *);
		ip->ip_len = htons(ip->ip_len);
		ip->ip_off = htons(ip->ip_off);
		ip->ip_sum = 0;
		ip->ip_sum = in_cksum(copym, hlen);
#if 1 /* XXX */
		if (dst->sin_family != AF_INET) {
			printf("ip_mloopback: bad address family %d\n",
						dst->sin_family);
			dst->sin_family = AF_INET;
		}
#endif
		if_simloop(ifp, copym, dst->sin_family, 0);
	}
}
