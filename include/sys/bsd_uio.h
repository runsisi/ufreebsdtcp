/*-
 * Copyright (c) 1982, 1986, 1993, 1994
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
 *	@(#)uio.h	8.5 (Berkeley) 2/22/94
 * $FreeBSD: release/9.2.0/sys/sys/uio.h 251874 2013-06-18 00:36:53Z scottl $
 */

#ifndef _SYS_UIO_H_
#define	_SYS_UIO_H_

#include <sys/bsd_cdefs.h>
#include <sys/_bsd_types.h>
#include <sys/_bsd_iovec.h>

#ifndef _BSD_SSIZE_T_DECLARED
typedef	__bsd_ssize_t	bsd_ssize_t;
#define	_BSD_SSIZE_T_DECLARED
#endif

#ifndef _BSD_OFF_T_DECLARED
typedef	__bsd_off_t	bsd_off_t;
#define	_BSD_OFF_T_DECLARED
#endif

#if __BSD_VISIBLE
enum	bsd_uio_rw { UIO_READ, UIO_WRITE };

/* Segment flag values. */
enum bsd_uio_seg {
	UIO_USERSPACE,		/* from user data space */
	UIO_SYSSPACE,		/* from system space */
	UIO_NOCOPY		/* don't copy, already in object */
};
#endif

#ifdef _KERNEL

struct uio {
	struct	bsd_iovec *uio_iov;		/* scatter/gather list */
	int	uio_iovcnt;		/* length of scatter/gather list */
	bsd_off_t	uio_offset;		/* offset in target object */
	bsd_ssize_t	uio_resid;		/* remaining bytes to process */
//	enum	bsd_uio_seg uio_segflg;	/* address space */
//	enum	bsd_uio_rw uio_rw;		/* operation */
	struct	thread *uio_td;		/* owner */
};

/*
 * Limits
 *
 * N.B.: UIO_MAXIOV must be no less than IOV_MAX from <sys/syslimits.h>
 * which in turn must be no less than _XOPEN_IOV_MAX from <limits.h>.  If
 * we ever make this tunable (probably pointless), then IOV_MAX should be
 * removed from <sys/syslimits.h> and applications would be expected to use
 * sysconf(3) to find out the correct value, or else assume the worst
 * (_XOPEN_IOV_MAX).  Perhaps UIO_MAXIOV should be simply defined as
 * IOV_MAX.
 */
#define UIO_MAXIOV	1024		/* max 1K of iov's */

struct vm_object;
struct vm_page;

struct uio *cloneuio(struct uio *uiop);
int	copyinfrom(const void * __restrict src, void * __restrict dst,
	    bsd_size_t len, int seg);
int	copyiniov(struct bsd_iovec *iovp, u_int iovcnt, struct bsd_iovec **iov,
	    int error);
int	copyinstrfrom(const void * __restrict src, void * __restrict dst,
	    bsd_size_t len, bsd_size_t * __restrict copied, int seg);
int	copyinuio(struct bsd_iovec *iovp, u_int iovcnt, struct uio **uiop);
int	copyout_map(struct thread *td, bsd_vm_offset_t *addr, bsd_size_t sz);
int	copyout_unmap(struct thread *td, bsd_vm_offset_t addr, bsd_size_t sz);
int	physcopyin(void *src, bsd_vm_paddr_t dst, bsd_size_t len);
int	physcopyout(bsd_vm_paddr_t src, void *dst, bsd_size_t len);
int	uiomove(void *cp, int n, struct uio *uio);
int	uiomove_frombuf(void *buf, int buflen, struct uio *uio);
int	uiomove_fromphys(struct vm_page *ma[], bsd_vm_offset_t offset, int n,
	    struct uio *uio);
int	uiomove_nofault(void *cp, int n, struct uio *uio);
int	uiomoveco(void *cp, int n, struct uio *uio, int disposable);

#else /* !_KERNEL */

__BEGIN_DECLS
bsd_ssize_t	readv(int, const struct bsd_iovec *, int);
bsd_ssize_t	writev(int, const struct bsd_iovec *, int);
#if __BSD_VISIBLE
bsd_ssize_t	preadv(int, const struct bsd_iovec *, int, bsd_off_t);
bsd_ssize_t	pwritev(int, const struct bsd_iovec *, int, bsd_off_t);
#endif
__END_DECLS

#endif /* _KERNEL */

#endif /* !_SYS_UIO_H_ */
