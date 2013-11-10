/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 *	@(#)param.h	8.3 (Berkeley) 4/4/95
 * $FreeBSD: release/9.2.0/sys/sys/param.h 253912 2013-08-03 12:41:21Z gjb $
 */

#ifndef _BSD_SYS_PARAM_H_
#define _BSD_SYS_PARAM_H_

// runsisi AT hust.edu.cn @2013/11/01
#ifndef _KERNEL
#define _KERNEL
#endif

#ifdef _POSIX_SOURCE
#undef _POSIX_SOURCE
#endif

#define BSD_LOG_DEBUG       1
#define BSD_LOG_WARNING     2
#define BSD_LOG_ERROR       3

// ---------------------- @2013/11/01

#include <sys/_bsd_null.h>

#define	BSD	199506		/* System version (year & month). */
#define BSD4_3	1
#define BSD4_4	1

/* 
 * __FreeBSD_version numbers are documented in the Porter's Handbook.
 * If you bump the version for any reason, you should update the documentation
 * there.
 * Currently this lives here in the doc/ repository:
 *
 *	head/en_US.ISO8859-1/books/porters-handbook/book.xml
 *
 * scheme is:  <major><two digit minor>Rxx
 *		'R' is in the range 0 to 4 if this is a release branch or
 *		x.0-CURRENT before RELENG_*_0 is created, otherwise 'R' is
 *		in the range 5 to 9.
 */
#undef __FreeBSD_version
#define __FreeBSD_version 902001	/* Master, propagated to newvers */

/*
 * __FreeBSD_kernel__ indicates that this system uses the kernel of FreeBSD,
 * which by definition is always true on FreeBSD. This macro is also defined
 * on other systems that use the kernel of FreeBSD, such as GNU/kFreeBSD.
 *
 * It is tempting to use this macro in userland code when we want to enable
 * kernel-specific routines, and in fact it's fine to do this in code that
 * is part of FreeBSD itself.  However, be aware that as presence of this
 * macro is still not widespread (e.g. older FreeBSD versions, 3rd party
 * compilers, etc), it is STRONGLY DISCOURAGED to check for this macro in
 * external applications without also checking for __FreeBSD__ as an
 * alternative.
 */
#undef __FreeBSD_kernel__
#define __FreeBSD_kernel__

#ifdef _KERNEL
#define	P_OSREL_SIGWAIT		700000
#define	P_OSREL_SIGSEGV		700004
#define	P_OSREL_MAP_ANON	800104
#endif

#ifndef LOCORE
#include <sys/bsd_types.h>
#endif

/*
 * Machine-independent constants (some used in following include files).
 * Redefined constants are from POSIX 1003.1 limits file.
 *
 * MAXCOMLEN should be >= sizeof(ac_comm) (see <acct.h>)
 */
#include <sys/bsd_syslimits.h>

#define	BSD_MAXCOMLEN	19		/* max command name remembered */
#define	BSD_MAXINTERP	BSD_PATH_MAX	/* max interpreter file name length */
#define	BSD_MAXLOGNAME	17		/* max login name length (incl. NUL) */
#define	BSD_MAXUPRC		BSD_CHILD_MAX	/* max simultaneous processes */
#define	BSD_NCARGS		BSD_ARG_MAX		/* max bytes for an exec function */
#define	BSD_NGROUPS		(NGROUPS_MAX+1)	/* max number groups */
#define	BSD_NOFILE		BSD_OPEN_MAX	/* max open files per process */
#define	BSD_NOGROUP		65535		/* marker for empty group set member */
#define BSD_MAXHOSTNAMELEN	256		/* max hostname size */
#define BSD_SPECNAMELEN	63		/* max length of devicename */

/* More types and definitions used throughout the kernel. */
#ifdef _KERNEL
#include <sys/bsd_cdefs.h>
#include <sys/bsd_errno.h>
#ifndef LOCORE
#include <sys/bsd_time.h>
#include <sys/bsd_priority.h>
#endif

#ifndef FALSE
#define	FALSE	0
#endif
#ifndef TRUE
#define	TRUE	1
#endif
#endif

#ifndef _KERNEL
/* Signals. */
#include <sys/bsd_signal.h>
#endif

/* Machine type dependent parameters. */
#include <machine/bsd_param.h>
#ifndef _KERNEL
#include <sys/bsd_limits.h>
#endif

#ifndef BSD_DEV_BSHIFT
#define	BSD_DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
#endif
#define	BSD_DEV_BSIZE	(1<<BSD_DEV_BSHIFT)

#ifndef BSD_BLKDEV_IOSIZE
#define BSD_BLKDEV_IOSIZE  BSD_PAGE_SIZE	/* default block device I/O size */
#endif
#ifndef BSD_DFLTPHYS
#define BSD_DFLTPHYS	(64 * 1024)	/* default max raw I/O transfer size */
#endif
#ifndef BSD_MAXPHYS
#define BSD_MAXPHYS		(128 * 1024)	/* max raw I/O transfer size */
#endif
#ifndef BSD_MAXDUMPPGS
#define BSD_MAXDUMPPGS	(BSD_DFLTPHYS/BSD_PAGE_SIZE)
#endif

/*
 * Constants related to network buffer management.
 * MCLBYTES must be no larger than PAGE_SIZE.
 */
#if 0	// runsisi AT hust.edu.cn @2013/11/04
#ifndef	MSIZE
#define MSIZE		256		/* size of an mbuf */
#endif	/* MSIZE */
#endif 	// ---------------------- @2013/11/04

// runsisi AT hust.edu.cn @2013/11/04
#ifndef MSIZE
#define MSIZE       2048     /* size of an mbuf */
#endif  /* MSIZE */
// ---------------------- @2013/11/04

#ifndef	MCLSHIFT
#define MCLSHIFT	11		/* convert bytes to mbuf clusters */
#endif	/* MCLSHIFT */

#if 0	// runsisi AT hust.edu.cn @2013/11/04
#define MCLBYTES	(1 << MCLSHIFT)	/* size of an mbuf cluster */
#endif 	// ---------------------- @2013/11/04

// runsisi AT hust.edu.cn @2013/11/04
#define MCLBYTES    ((1 << MCLSHIFT) + 4) /* do not conflict with MSIZE */
// ---------------------- @2013/11/04

#if BSD_PAGE_SIZE < 2048
#define	MJUMPAGESIZE	MCLBYTES
#elif BSD_PAGE_SIZE <= 8192
#define	MJUMPAGESIZE	BSD_PAGE_SIZE
#else
#define	BSD_MJUMPAGESIZE	(8 * 1024)
#endif

#define	MJUM9BYTES	(9 * 1024)	/* jumbo cluster 9k */
#define	MJUM16BYTES	(16 * 1024)	/* jumbo cluster 16k */

/*
 * Some macros for units conversion
 */

/* clicks to bytes */
#ifndef ctob
#define ctob(x)	((x)<<PAGE_SHIFT)
#endif

/* bytes to clicks */
#ifndef btoc
#define btoc(x)	(((vm_offset_t)(x)+PAGE_MASK)>>PAGE_SHIFT)
#endif

/*
 * btodb() is messy and perhaps slow because `bytes' may be an off_t.  We
 * want to shift an unsigned type to avoid sign extension and we don't
 * want to widen `bytes' unnecessarily.  Assume that the result fits in
 * a daddr_t.
 */
#ifndef btodb
#define btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
	(sizeof (bytes) > sizeof(long) \
	 ? (daddr_t)((unsigned long long)(bytes) >> BSD_DEV_BSHIFT) \
	 : (daddr_t)((unsigned long)(bytes) >> BSD_DEV_BSHIFT))
#endif

#ifndef dbtob
#define dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
	((off_t)(db) << BSD_DEV_BSHIFT)
#endif

#define	BSD_PRIMASK	0x0ff
#define	BSD_PCATCH	0x100		/* OR'd with pri for tsleep to check signals */
#define	BSD_PDROP	0x200	/* OR'd with pri to stop re-entry of interlock mutex */
#define	BSD_PBDRY	0x400	/* for PCATCH stop is done on the user boundary */

#define	BSD_NZERO	0		/* default "nice" */

#define	BSD_NBBY	8		/* number of bits in a byte */
#define	BSD_NBPW	sizeof(int)	/* number of bytes per word (integer) */

#define	BSD_CMASK	022		/* default file mask: S_IWGRP|S_IWOTH */

#define	BSD_NODEV	(bsd_dev_t)(-1)	/* non-existent device */

/*
 * File system parameters and macros.
 *
 * MAXBSIZE -	Filesystems are made out of blocks of at most MAXBSIZE bytes
 *		per block.  MAXBSIZE may be made larger without effecting
 *		any existing filesystems as long as it does not exceed MAXPHYS,
 *		and may be made smaller at the risk of not being able to use
 *		filesystems which require a block size exceeding MAXBSIZE.
 *
 * BKVASIZE -	Nominal buffer space per buffer, in bytes.  BKVASIZE is the
 *		minimum KVM memory reservation the kernel is willing to make.
 *		Filesystems can of course request smaller chunks.  Actual 
 *		backing memory uses a chunk size of a page (PAGE_SIZE).
 *
 *		If you make BKVASIZE too small you risk seriously fragmenting
 *		the buffer KVM map which may slow things down a bit.  If you
 *		make it too big the kernel will not be able to optimally use 
 *		the KVM memory reserved for the buffer cache and will wind 
 *		up with too-few buffers.
 *
 *		The default is 16384, roughly 2x the block size used by a
 *		normal UFS filesystem.
 */
#define BSD_MAXBSIZE	65536	/* must be power of 2 */
#define BSD_BKVASIZE	16384	/* must be power of 2 */
#define BSD_BKVAMASK	(BSD_BKVASIZE-1)

/*
 * MAXPATHLEN defines the longest permissible path length after expanding
 * symbolic links. It is used to allocate a temporary buffer from the buffer
 * pool in which to do the name expansion, hence should be a power of two,
 * and must be less than or equal to MAXBSIZE.  MAXSYMLINKS defines the
 * maximum number of symbolic links that may be expanded in a path name.
 * It should be set high enough to allow all legitimate uses, but halt
 * infinite loops reasonably quickly.
 */
#define	BSD_MAXPATHLEN	BSD_PATH_MAX
#define BSD_MAXSYMLINKS	32

/* Bit map related macros. */
#define	bsd_setbit(a,i)	(((unsigned char *)(a))[(i)/BSD_NBBY] |= 1<<((i)%BSD_NBBY))
#define	bsd_clrbit(a,i)	(((unsigned char *)(a))[(i)/BSD_NBBY] &= ~(1<<((i)%BSD_NBBY)))
#define	bsd_isset(a,i)							\
	(((const unsigned char *)(a))[(i)/BSD_NBBY] & (1<<((i)%BSD_NBBY)))
#define	bsd_isclr(a,i)							\
	((((const unsigned char *)(a))[(i)/BSD_NBBY] & (1<<((i)%BSD_NBBY))) == 0)

/* Macros for counting and rounding. */
#ifndef bsd_howmany
#define	bsd_howmany(x, y)	(((x)+((y)-1))/(y))
#endif
#define	bsd_nitems(x)	(sizeof((x)) / sizeof((x)[0]))
#define	bsd_rounddown(x, y)	(((x)/(y))*(y))
#define	bsd_roundup(x, y)	((((x)+((y)-1))/(y))*(y))  /* to any y */
#define	bsd_roundup2(x, y)	(((x)+((y)-1))&(~((y)-1))) /* if y is powers of two */
#define bsd_powerof2(x)	((((x)-1)&(x))==0)

/* Macros for min/max. */
#define	BSD_MIN(a,b) (((a)<(b))?(a):(b))
#define	BSD_MAX(a,b) (((a)>(b))?(a):(b))

#ifdef _KERNEL
/*
 * Basic byte order function prototypes for non-inline functions.
 */
#ifndef LOCORE
#ifndef _BYTEORDER_PROTOTYPED
#define	_BYTEORDER_PROTOTYPED
__BEGIN_DECLS
__bsd_uint32_t	 bsd_htonl(__bsd_uint32_t);
__bsd_uint16_t	 bsd_htons(__bsd_uint16_t);
__bsd_uint32_t	 bsd_ntohl(__bsd_uint32_t);
__bsd_uint16_t	 bsd_ntohs(__bsd_uint16_t);
__END_DECLS
#endif
#endif

#ifndef lint
#ifndef _BYTEORDER_FUNC_DEFINED
#define	_BYTEORDER_FUNC_DEFINED
#define	bsd_htonl(x)	__htonl(x)
#define	bsd_htons(x)	__htons(x)
#define	bsd_ntohl(x)	__ntohl(x)
#define	bsd_ntohs(x)	__ntohs(x)
#endif /* !_BYTEORDER_FUNC_DEFINED */
#endif /* lint */
#endif /* _KERNEL */

/*
 * Scale factor for scaled integers used to count %cpu time and load avgs.
 *
 * The number of CPU `tick's that map to a unique `%age' can be expressed
 * by the formula (1 / (2 ^ (FSHIFT - 11))).  The maximum load average that
 * can be calculated (assuming 32 bits) can be closely approximated using
 * the formula (2 ^ (2 * (16 - FSHIFT))) for (FSHIFT < 15).
 *
 * For the scheduler to maintain a 1:1 mapping of CPU `tick' to `%age',
 * FSHIFT must be at least 11; this gives us a maximum load avg of ~1024.
 */
#define	BSD_FSHIFT	11		/* bits to right of fixed binary point */
#define BSD_FSCALE	(1<<BSD_FSHIFT)

#define dbtoc(db)			/* calculates devblks to pages */ \
	((db + (ctodb(1) - 1)) >> (PAGE_SHIFT - BSD_DEV_BSHIFT))
 
#define ctodb(db)			/* calculates pages to devblks */ \
	((db) << (PAGE_SHIFT - BSD_DEV_BSHIFT))

/*
 * Old spelling of __containerof().
 */
#define	member2struct(s, m, x)						\
	((struct s *)(void *)((char *)(x) - offsetof(struct s, m)))

/*
 * Access a variable length array that has been declared as a fixed
 * length array.
 */
#define __PAST_END(array, offset) (((__typeof__(*(array)) *)(array))[offset])

#endif	/* _SYS_PARAM_H_ */
