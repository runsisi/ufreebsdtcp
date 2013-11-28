/*
 * Copyright (c) 1982, 1986, 1988, 1993
 *      The Regents of the University of California.
 * Copyright (c) 2005 Andre Oppermann, Internet Business Solutions AG.
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
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/netinet/ip_options.c 213832 2010-10-14 12:32:49Z bz $");

#include "opt_ipstealth.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_mbuf.h>
#include <sys/bsd_domain.h>
#include <sys/bsd_protosw.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_time.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_syslog.h>
#include <sys/bsd_sysctl.h>

#include <net/if.h>
#include <net/if_types.h>
#include <net/if_var.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <net/netisr.h>
#include <net/vnet.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
#include <netinet/ip_options.h>
#include <netinet/ip_icmp.h>
#include <machine/bsd_in_cksum.h>

#include <sys/bsd_socketvar.h>

/*
 * Retrieve incoming source route for use in replies, in the same form used
 * by setsockopt.  The first hop is placed before the options, will be
 * removed later.
 */
struct mbuf *
ip_srcroute(struct mbuf *m0)
{
    #if 0	// runsisi AT hust.edu.cn @2013/11/05
	struct in_addr *p, *q;
	struct mbuf *m;
	struct ipopt_tag *opts;

	opts = (struct ipopt_tag *)m_tag_find(m0, PACKET_TAG_IPOPTIONS, NULL);
	if (opts == NULL)
		return (NULL);

	if (opts->ip_nhops == 0)
		return (NULL);
	m = m_get(M_DONTWAIT, MT_DATA);
	if (m == NULL)
		return (NULL);

#define OPTSIZ	(sizeof(opts->ip_srcrt.nop) + sizeof(opts->ip_srcrt.srcopt))

	/* length is (nhops+1)*sizeof(addr) + sizeof(nop + srcrt header) */
	m->m_len = opts->ip_nhops * sizeof(struct in_addr) +
	    sizeof(struct in_addr) + OPTSIZ;

	/*
	 * First, save first hop for return route.
	 */
	p = &(opts->ip_srcrt.route[opts->ip_nhops - 1]);
	*(mtod(m, struct in_addr *)) = *p--;

	/*
	 * Copy option fields and padding (nop) to mbuf.
	 */
	opts->ip_srcrt.nop = IPOPT_NOP;
	opts->ip_srcrt.srcopt[IPOPT_OFFSET] = IPOPT_MINOFF;
	(void)memcpy(mtod(m, caddr_t) + sizeof(struct in_addr),
	    &(opts->ip_srcrt.nop), OPTSIZ);
	q = (struct in_addr *)(mtod(m, caddr_t) +
	    sizeof(struct in_addr) + OPTSIZ);
#undef OPTSIZ
	/*
	 * Record return path as an IP source route, reversing the path
	 * (pointers are now aligned).
	 */
	while (p >= opts->ip_srcrt.route) {
		*q++ = *p--;
	}
	/*
	 * Last hop goes to final destination.
	 */
	*q = opts->ip_srcrt.dst;
	m_tag_delete(m0, (struct m_tag *)opts);
	return (m);
    #endif 	// ---------------------- @2013/11/05

    return NULL;
}

/*
 * Strip out IP options, at higher level protocol in the kernel.  Second
 * argument is buffer to which options will be moved, and return value is
 * their length.
 *
 * XXX should be deleted; last arg currently ignored.
 */
void
ip_stripoptions(struct mbuf *m, struct mbuf *mopt)
{
	int i;
	struct ip *ip = mtod(m, struct ip *);
	caddr_t opts;
	int olen;

	olen = (ip->ip_hl << 2) - sizeof (struct ip);
	opts = (caddr_t)(ip + 1);
	i = m->m_len - (sizeof (struct ip) + olen);
	bcopy(opts + olen, opts, (unsigned)i);
	m->m_len -= olen;
	if (m->m_flags & M_PKTHDR)
		m->m_pkthdr.len -= olen;
	ip->ip_v = IPVERSION;
	ip->ip_hl = sizeof(struct ip) >> 2;
}

/*
 * Insert IP options into preformed packet.  Adjust IP destination as
 * required for IP source routing, as indicated by a non-zero in_addr at the
 * start of the options.
 *
 * XXX This routine assumes that the packet has no options in place.
 */
struct mbuf *
ip_insertoptions(struct mbuf *m, struct mbuf *opt, int *phlen)
{
	struct ipoption *p = mtod(opt, struct ipoption *);
	struct mbuf *n;
	struct ip *ip = mtod(m, struct ip *);
	unsigned optlen;

	optlen = opt->m_len - sizeof(p->ipopt_dst);
	if (optlen + ip->ip_len > IP_MAXPACKET) {
		*phlen = 0;
		return (m);		/* XXX should fail */
	}
	if (p->ipopt_dst.s_addr)
		ip->ip_dst = p->ipopt_dst;
	if (m->m_flags & M_EXT || m->m_data - optlen < m->m_pktdat) {
		MGETHDR(n, M_DONTWAIT, MT_DATA);
		if (n == NULL) {
			*phlen = 0;
			return (m);
		}
		M_MOVE_PKTHDR(n, m);
		n->m_pkthdr.rcvif = NULL;
		n->m_pkthdr.len += optlen;
		m->m_len -= sizeof(struct ip);
		m->m_data += sizeof(struct ip);
		n->m_next = m;
		m = n;
		m->m_len = optlen + sizeof(struct ip);
		m->m_data += max_linkhdr;
		bcopy(ip, mtod(m, void *), sizeof(struct ip));
	} else {
		m->m_data -= optlen;
		m->m_len += optlen;
		m->m_pkthdr.len += optlen;
		bcopy(ip, mtod(m, void *), sizeof(struct ip));
	}
	ip = mtod(m, struct ip *);
	bcopy(p->ipopt_list, ip + 1, optlen);
	*phlen = sizeof(struct ip) + optlen;
	ip->ip_v = IPVERSION;
	ip->ip_hl = *phlen >> 2;
	ip->ip_len += optlen;
	return (m);
}
