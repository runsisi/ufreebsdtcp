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
 * $FreeBSD: release/9.2.0/sys/sys/socketvar.h 215178 2010-11-12 13:02:26Z luigi $
 */

#ifndef _SYS_SOCKETVAR_H_
#define _SYS_SOCKETVAR_H_

#include <sys/bsd_queue.h>			/* for TAILQ macros */
#include <sys/bsd_selinfo.h>		/* for struct selinfo */
#include <sys/_bsd_lock.h>
#include <sys/_bsd_mutex.h>
#include <sys/_bsd_sx.h>
#include <sys/bsd_sockbuf.h>
#include <sys/bsd_sockstate.h>
#ifdef _KERNEL
#include <sys/bsd_sockopt.h>
#endif

struct vnet;

/*
 * Kernel structure per socket.
 * Contains send and receive buffer queues,
 * handle on protocol and pointer to protocol
 * private data and error information.
 */
typedef	bsd_uquad_t so_gen_t;

struct bsd_socket;

/*-
 * Locking key to struct socket:
 * (a) constant after allocation, no locking required.
 * (b) locked by SOCK_LOCK(so).
 * (c) locked by SOCKBUF_LOCK(&so->so_rcv).
 * (d) locked by SOCKBUF_LOCK(&so->so_snd).
 * (e) locked by ACCEPT_LOCK().
 * (f) not locked since integer reads/writes are atomic.
 * (g) used only as a sleep/wakeup address, no value.
 * (h) locked by global mutex so_global_mtx.
 */
struct bsd_socket {
	int	so_count;		/* (b) reference count */
	short	so_type;		/* (a) generic type, see socket.h */
	short	so_options;		/* from socket call, see socket.h */
	short	so_linger;		/* time to linger while closing */
	short	so_state;		/* (b) internal state flags SS_* */
	int	so_qstate;		/* (e) internal state flags SQ_* */
	void	*so_pcb;		/* protocol control block */
	struct	vnet *so_vnet;		/* network stack instance */
	struct	bsd_protosw *so_proto;	/* (a) protocol handle */
/*
 * Variables for connection queuing.
 * Socket where accepts occur is so_head in all subsidiary sockets.
 * If so_head is 0, socket is not related to an accept.
 * For head socket so_incomp queues partially completed connections,
 * while so_comp is a queue of connections ready to be accepted.
 * If a connection is aborted and it has so_head set, then
 * it has to be pulled out of either so_incomp or so_comp.
 * We allow connections to queue up based on current queue lengths
 * and limit on number of queued connections for this socket.
 */
	struct	bsd_socket *so_head;	/* (e) back pointer to listen socket */
	BSD_TAILQ_HEAD(, bsd_socket) so_incomp;	/* (e) queue of partial unaccepted connections */
	BSD_TAILQ_HEAD(, bsd_socket) so_comp;	/* (e) queue of complete unaccepted connections */
	BSD_TAILQ_ENTRY(bsd_socket) so_list;	/* (e) list of unaccepted connections */
	u_short	so_qlen;		/* (e) number of unaccepted connections */
	u_short	so_incqlen;		/* (e) number of unaccepted incomplete
					   connections */
	u_short	so_qlimit;		/* (e) max number queued connections */
	short	so_timeo;		/* (g) connection timeout */
	u_short	so_error;		/* (f) error affecting connection */
	struct	sigio *so_sigio;	/* [sg] information for async I/O or
					   out of band data (SIGURG) */
	u_long	so_oobmark;		/* (c) chars to oob mark */
	BSD_TAILQ_HEAD(, aiocblist) so_aiojobq; /* AIO ops waiting on socket */

	struct sockbuf so_rcv, so_snd;

	struct	bsd_ucred *so_cred;		/* (a) user credentials */
	struct	label *so_label;	/* (b) MAC label for socket */
	struct	label *so_peerlabel;	/* (b) cached MAC label for peer */
	/* NB: generation count must not be first. */
	so_gen_t so_gencnt;		/* (h) generation count */
	void	*so_emuldata;		/* (b) private data for emulators */
 	struct so_accf {
		struct	accept_filter *so_accept_filter;
		void	*so_accept_filter_arg;	/* saved filter args */
		char	*so_accept_filter_str;	/* saved user args */
	} *so_accf;
	/*
	 * so_fibnum, so_user_cookie and friends can be used to attach
	 * some user-specified metadata to a socket, which then can be
	 * used by the kernel for various actions.
	 * so_user_cookie is used by ipfw/dummynet.
	 */
	int so_fibnum;		/* routing domain for this socket */
	bsd_uint32_t so_user_cookie;

	// runsisi AT hust.edu.cn @2013/11/13
	int so_fd;          /* this socket's corresponding fd */
	int so_otype;       /* original type, dps use the msb to identify sock for rpc */
	DPS_AO_ID so_aoid;      /* the ao we are live in */
	DPS_AO_ID so_appaoid;   /* the ao who created the so live in */
	bsd_uint32_t so_rcvq_id;    /* dps queue id for receive */
	bsd_uint32_t so_sndq_id;    /* dps queue id for send */
    // ---------------------- @2013/11/13
};

/*
 * Global accept mutex to serialize access to accept queues and
 * fields associated with multiple sockets.  This allows us to
 * avoid defining a lock order between listen and accept sockets
 * until such time as it proves to be a good idea.
 */
extern struct mtx accept_mtx;
#define	ACCEPT_LOCK_ASSERT()		mtx_assert(&accept_mtx, MA_OWNED)
#define	ACCEPT_UNLOCK_ASSERT()		mtx_assert(&accept_mtx, MA_NOTOWNED)
#define	ACCEPT_LOCK()			mtx_lock(&accept_mtx)
#define	ACCEPT_UNLOCK()			mtx_unlock(&accept_mtx)

/*
 * Per-socket mutex: we reuse the receive socket buffer mutex for space
 * efficiency.  This decision should probably be revisited as we optimize
 * locking for the socket code.
 */
#define	SOCK_MTX(_so)			SOCKBUF_MTX(&(_so)->so_rcv)
#define	SOCK_LOCK(_so)			SOCKBUF_LOCK(&(_so)->so_rcv)
#define	SOCK_OWNED(_so)			SOCKBUF_OWNED(&(_so)->so_rcv)
#define	SOCK_UNLOCK(_so)		SOCKBUF_UNLOCK(&(_so)->so_rcv)
#define	SOCK_LOCK_ASSERT(_so)		SOCKBUF_LOCK_ASSERT(&(_so)->so_rcv)

/*
 * Socket state bits stored in so_qstate.
 */
#define	SQ_INCOMP		0x0800	/* unaccepted, incomplete connection */
#define	SQ_COMP			0x1000	/* unaccepted, complete connection */

// runsisi AT hust.edu.cn @2013/11/14
#define SO_FOR_RPC(so)  ((so)->so_otype & 0x80000000)  /* if it's a sock created by rpc */
// ---------------------- @2013/11/14

/*
 * Externalized form of struct socket used by the sysctl(3) interface.
 */
struct xsocket {
	bsd_size_t	xso_len;	/* length of this structure */
	struct	bsd_socket *xso_so;	/* makes a convenient handle sometimes */
	short	so_type;
	short	so_options;
	short	so_linger;
	short	so_state;
	caddr_t	so_pcb;		/* another convenient handle */
	int	xso_protocol;
	int	xso_family;
	u_short	so_qlen;
	u_short	so_incqlen;
	u_short	so_qlimit;
	short	so_timeo;
	u_short	so_error;
	bsd_pid_t	so_pgid;
	u_long	so_oobmark;
	struct xsockbuf so_rcv, so_snd;
	bsd_uid_t	so_uid;		/* XXX */
};

#ifdef _KERNEL

/*
 * Macros for sockets and socket buffering.
 */

/*
 * Flags to sblock().
 */
#define	SBL_WAIT	0x00000001	/* Wait if not immediately available. */
#define	SBL_NOINTR	0x00000002	/* Force non-interruptible sleep. */
#define	SBL_VALID	(SBL_WAIT | SBL_NOINTR)

/*
 * Do we need to notify the other side when I/O is possible?
 */
#define	sb_notify(sb)	(((sb)->sb_flags & (SB_WAIT | SB_SEL | SB_ASYNC | \
    SB_UPCALL | SB_AIO | SB_KNOTE)) != 0)

/* do we have to send all at once on a socket? */
#define	sosendallatonce(so) \
    ((so)->so_proto->pr_flags & PR_ATOMIC)

/* can we read something from so? */
#define	soreadabledata(so) \
    ((so)->so_rcv.sb_cc >= (so)->so_rcv.sb_lowat || \
	!BSD_TAILQ_EMPTY(&(so)->so_comp) || (so)->so_error)
#define	soreadable(so) \
	(soreadabledata(so) || ((so)->so_rcv.sb_state & SBS_CANTRCVMORE))

/* can we write something to so? */
#define	sowriteable(so) \
    ((sbspace(&(so)->so_snd) >= (so)->so_snd.sb_lowat && \
	(((so)->so_state&SS_ISCONNECTED) || \
	  ((so)->so_proto->pr_flags&PR_CONNREQUIRED)==0)) || \
     ((so)->so_snd.sb_state & SBS_CANTSENDMORE) || \
     (so)->so_error)

/*
 * soref()/sorele() ref-count the socket structure.  Note that you must
 * still explicitly close the socket, but the last ref count will free
 * the structure.
 */
#define	soref(so) do {							\
	SOCK_LOCK_ASSERT(so);						\
	++(so)->so_count;						\
} while (0)

#define	sorele(so) do {							\
	ACCEPT_LOCK_ASSERT();						\
	SOCK_LOCK_ASSERT(so);						\
	if ((so)->so_count <= 0)					\
		panic("sorele");					\
	if (--(so)->so_count == 0)					\
		sofree(so);						\
	else {								\
		SOCK_UNLOCK(so);					\
		ACCEPT_UNLOCK();					\
	}								\
} while (0)

/*
 * In sorwakeup() and sowwakeup(), acquire the socket buffer lock to
 * avoid a non-atomic test-and-wakeup.  However, sowakeup is
 * responsible for releasing the lock if it is called.  We unlock only
 * if we don't call into sowakeup.  If any code is introduced that
 * directly invokes the underlying sowakeup() primitives, it must
 * maintain the same semantics.
 */
#define	sorwakeup_locked(so) do {					\
	SOCKBUF_LOCK_ASSERT(&(so)->so_rcv);				\
	if (sb_notify(&(so)->so_rcv))					\
		sowakeup((so), &(so)->so_rcv);	 			\
	else								\
		SOCKBUF_UNLOCK(&(so)->so_rcv);				\
} while (0)

#define	sorwakeup(so) do {						\
	SOCKBUF_LOCK(&(so)->so_rcv);					\
	sorwakeup_locked(so);						\
} while (0)

#define	sowwakeup_locked(so) do {					\
	SOCKBUF_LOCK_ASSERT(&(so)->so_snd);				\
	if (sb_notify(&(so)->so_snd))					\
		sowakeup((so), &(so)->so_snd); 				\
	else								\
		SOCKBUF_UNLOCK(&(so)->so_snd);				\
} while (0)

#define	sowwakeup(so) do {						\
	SOCKBUF_LOCK(&(so)->so_snd);					\
	sowwakeup_locked(so);						\
} while (0)

struct accept_filter {
	char	accf_name[16];
	int	(*accf_callback)
		(struct bsd_socket *so, void *arg, int waitflag);
	void *	(*accf_create)
		(struct bsd_socket *so, char *arg);
	void	(*accf_destroy)
		(struct bsd_socket *so);
	BSD_SLIST_ENTRY(accept_filter) accf_next;
};

#ifdef MALLOC_DECLARE
MALLOC_DECLARE(M_ACCF);
MALLOC_DECLARE(M_PCB);
MALLOC_DECLARE(M_SONAME);
#endif

extern int	maxsockets;
extern u_long	sb_max;
extern struct uma_zone *socket_zone;
extern so_gen_t so_gencnt;

struct mbuf;
struct bsd_sockaddr;
struct bsd_ucred;
struct uio;

/* 'which' values for socket upcalls. */
#define	SO_RCV		1
#define	SO_SND		2

/* Return values for socket upcalls. */
#define	SU_OK		0
#define	SU_ISCONNECTED	1

/*
 * From uipc_socket and friends
 */
int	sockargs(struct mbuf **mp, caddr_t buf, int buflen, int type);
int	getsockaddr(struct bsd_sockaddr **namp, caddr_t uaddr, bsd_size_t len);
void	soabort(struct bsd_socket *so);
int	bsd_soaccept(struct bsd_socket *so, struct bsd_sockaddr **nam);
int	socheckuid(struct bsd_socket *so, bsd_uid_t uid);
int	bsd_sobind(struct bsd_socket *so, struct bsd_sockaddr *nam, struct thread *td);
int	bsd_soclose(struct bsd_socket *so);
int	bsd_soconnect(struct bsd_socket *so, struct bsd_sockaddr *nam, struct thread *td);
int	soconnect2(struct bsd_socket *so1, struct bsd_socket *so2);
int	socow_setup(struct mbuf *m0, struct uio *uio);
int	bsd_socreate(int dom, struct bsd_socket **aso, int type, int proto,
	    struct bsd_ucred *cred, struct thread *td);
int	sodisconnect(struct bsd_socket *so);
struct	bsd_sockaddr *sodupsockaddr(const struct bsd_sockaddr *sa, int mflags);
void	sofree(struct bsd_socket *so);
void	sohasoutofband(struct bsd_socket *so);
int	bsd_solisten(struct bsd_socket *so, int backlog, struct thread *td);
void	solisten_proto(struct bsd_socket *so, int backlog);
int	solisten_proto_check(struct bsd_socket *so);
struct bsd_socket *
	sonewconn(struct bsd_socket *head, int connstatus);


int	sopoll(struct bsd_socket *so, int events, struct bsd_ucred *active_cred,
	    struct thread *td);
int	sopoll_generic(struct bsd_socket *so, int events,
	    struct bsd_ucred *active_cred, struct thread *td);
int	soreceive(struct bsd_socket *so, struct bsd_sockaddr **paddr, struct uio *uio,
	    struct mbuf **mp0, struct mbuf **controlp, int *flagsp);
int	soreceive_stream(struct bsd_socket *so, struct bsd_sockaddr **paddr,
	    struct uio *uio, struct mbuf **mp0, struct mbuf **controlp,
	    int *flagsp);
int	soreceive_dgram(struct bsd_socket *so, struct bsd_sockaddr **paddr,
	    struct uio *uio, struct mbuf **mp0, struct mbuf **controlp,
	    int *flagsp);
int	soreceive_generic(struct bsd_socket *so, struct bsd_sockaddr **paddr,
	    struct uio *uio, struct mbuf **mp0, struct mbuf **controlp,
	    int *flagsp);
int	soreserve(struct bsd_socket *so, u_long sndcc, u_long rcvcc);
void	sorflush(struct bsd_socket *so);
int	bsd_sosend(struct bsd_socket *so, struct bsd_sockaddr *addr, struct uio *uio,
	    struct mbuf *top, struct mbuf *control, int flags,
	    struct thread *td);
int	sosend_dgram(struct bsd_socket *so, struct bsd_sockaddr *addr,
	    struct uio *uio, struct mbuf *top, struct mbuf *control,
	    int flags, struct thread *td);
int	sosend_generic(struct bsd_socket *so, struct bsd_sockaddr *addr,
	    struct uio *uio, struct mbuf *top, struct mbuf *control,
	    int flags, struct thread *td);
int	bsd_soshutdown(struct bsd_socket *so, int how);
void	sotoxsocket(struct bsd_socket *so, struct xsocket *xso);
void	soupcall_clear(struct bsd_socket *so, int which);
void	soupcall_set(struct bsd_socket *so, int which,
	    int (*func)(struct bsd_socket *, void *, int), void *arg);
// runsisi AT hust.edu.cn @2013/11/13
/*
 * these functions are implemented in socket_kernel.c
 */
int     sogetqsize(int qtype);
int     socreateq(struct bsd_socket *so);
int     sodelq(struct bsd_socket *so);
int     soasyncnotify(struct bsd_socket *so, int ev);
// ---------------------- @2013/11/13
void	sowakeup(struct bsd_socket *so, struct sockbuf *sb);
int	selsocket(struct bsd_socket *so, int events, struct bsd_timeval *tv,
	    struct thread *td);

/*
 * Accept filter functions (duh).
 */
int	accept_filt_add(struct accept_filter *filt);
int	accept_filt_del(char *name);
struct	accept_filter *accept_filt_get(char *name);
#ifdef ACCEPT_FILTER_MOD
#ifdef SYSCTL_DECL
SYSCTL_DECL(_net_inet_accf);
#endif
int	accept_filt_generic_mod_event(module_t mod, int event, void *data);
#endif

#endif /* _KERNEL */

#endif /* !_SYS_SOCKETVAR_H_ */
