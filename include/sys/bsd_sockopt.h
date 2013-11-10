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
 *	@(#)socketvar.h	8.3 (Berkeley) 2/19/95
 *
 * $FreeBSD: release/9.2.0/sys/sys/sockopt.h 180948 2008-07-29 07:45:05Z kmacy $
 */
#ifndef _SYS_SOCKOPT_H_
#define _SYS_SOCKOPT_H_

#ifndef _KERNEL
#error "no user-servicable parts inside"
#endif


struct thread;
struct bsd_socket;

/*
 * Argument structure for sosetopt et seq.  This is in the KERNEL
 * section because it will never be visible to user code.
 */
enum sopt_dir { SOPT_GET, SOPT_SET };

struct	bsd_sockopt {
	enum	sopt_dir sopt_dir; /* is this a get or a set? */
	int	sopt_level;	/* second arg of [gs]etsockopt */
	int	sopt_name;	/* third arg of [gs]etsockopt */
	void   *sopt_val;	/* fourth arg of [gs]etsockopt */
	bsd_size_t	sopt_valsize;	/* (almost) fifth arg of [gs]etsockopt */
	struct	thread *sopt_td; /* calling thread or null if kernel */
};

int	bsd_sosetopt(struct bsd_socket *so, struct bsd_sockopt *sopt);
int	bsd_sogetopt(struct bsd_socket *so, struct bsd_sockopt *sopt);
int	sooptcopyin(struct bsd_sockopt *sopt, void *buf, bsd_size_t len, bsd_size_t minlen);
int	sooptcopyout(struct bsd_sockopt *sopt, const void *buf, bsd_size_t len);
/* XXX; prepare mbuf for (__FreeBSD__ < 3) routines. */
int	soopt_getm(struct bsd_sockopt *sopt, struct mbuf **mp);
int	soopt_mcopyin(struct bsd_sockopt *sopt, struct mbuf *m);
int	soopt_mcopyout(struct bsd_sockopt *sopt, struct mbuf *m);
int	do_getopt_accept_filter(struct bsd_socket *so, struct bsd_sockopt *sopt);
int	do_setopt_accept_filter(struct bsd_socket *so, struct bsd_sockopt *sopt);
int	so_setsockopt(struct bsd_socket *so, int level, int optname,
	    void *optval, bsd_size_t optlen);

#endif /* _SYS_SOCKOPT_H_ */
