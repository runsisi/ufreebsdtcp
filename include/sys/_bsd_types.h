/*-
 * Copyright (c) 2002 Mike Barcroft <mike@FreeBSD.org>
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
 * $FreeBSD: release/9.2.0/sys/sys/_types.h 223710 2011-07-01 12:13:48Z jonathan $
 */

#ifndef _BSD_SYS__TYPES_H_
#define _BSD_SYS__TYPES_H_

#include <sys/bsd_cdefs.h>
#include <machine/_bsd_types.h>

/*
 * Standard type definitions.
 */
typedef	__bsd_uint32_t	__bsd_blksize_t;	/* file block size */
typedef	__bsd_int64_t	__bsd_blkcnt_t;	/* file block count */
typedef	__bsd_int32_t	__bsd_clockid_t;	/* clock_gettime()... */
typedef	__bsd_uint64_t	__bsd_cap_rights_t;	/* capability rights */
typedef	__bsd_uint32_t	__bsd_fflags_t;	/* file flags */
typedef	__bsd_uint64_t	__bsd_fsblkcnt_t;
typedef	__bsd_uint64_t	__bsd_fsfilcnt_t;
typedef	__bsd_uint32_t	__bsd_gid_t;
typedef	__bsd_int64_t	__bsd_id_t;		/* can hold a gid_t, pid_t, or uid_t */
typedef	__bsd_uint32_t	__bsd_ino_t;	/* inode number */
typedef	long		__bsd_key_t;	/* IPC key (for Sys V IPC) */
typedef	__bsd_int32_t	__bsd_lwpid_t;	/* Thread ID (a.k.a. LWP) */
typedef	__bsd_uint16_t	__bsd_mode_t;	/* permissions */
typedef	int		__bsd_accmode_t;	/* access permissions */
typedef	int		__bsd_nl_item;
typedef	__bsd_uint16_t	__bsd_nlink_t;	/* link count */
typedef	__bsd_int64_t	__bsd_off_t;	/* file offset */
typedef	__bsd_int32_t	__bsd_pid_t;	/* process [group] */
typedef	__bsd_int64_t	__bsd_rlim_t;	/* resource limit - intentionally */
					/* signed, because of legacy code */
					/* that uses -1 for RLIM_INFINITY */
typedef	__bsd_uint8_t	__bsd_sa_family_t;
typedef	__bsd_uint32_t	__bsd_socklen_t;
typedef	long		__bsd_suseconds_t;	/* microseconds (signed) */
typedef	struct __timer	*__bsd_timer_t;	/* timer_gettime()... */
typedef	struct __mq	*__bsd_mqd_t;	/* mq_open()... */
typedef	__bsd_uint32_t	__bsd_uid_t;
typedef	unsigned int	__bsd_useconds_t;	/* microseconds (unsigned) */
typedef	int		__bsd_cpuwhich_t;	/* which parameter for cpuset. */
typedef	int		__bsd_cpulevel_t;	/* level parameter for cpuset. */
typedef int		__bsd_cpusetid_t;	/* cpuset identifier. */

/*
 * Unusual type definitions.
 */
/*
 * rune_t is declared to be an ``int'' instead of the more natural
 * ``unsigned long'' or ``long''.  Two things are happening here.  It is not
 * unsigned so that EOF (-1) can be naturally assigned to it and used.  Also,
 * it looks like 10646 will be a 31 bit standard.  This means that if your
 * ints cannot hold 32 bits, you will be in trouble.  The reason an int was
 * chosen over a long is that the is*() and to*() routines take ints (says
 * ANSI C), but they use __ct_rune_t instead of int.
 *
 * NOTE: rune_t is not covered by ANSI nor other standards, and should not
 * be instantiated outside of lib/libc/locale.  Use wchar_t.  wchar_t and
 * rune_t must be the same type.  Also, wint_t must be no narrower than
 * wchar_t, and should be able to hold all members of the largest
 * character set plus one extra value (WEOF), and must be at least 16 bits.
 */
typedef	int		__bsd_ct_rune_t;	/* arg type for ctype funcs */
typedef	__bsd_ct_rune_t	__bsd_rune_t;	/* rune_t (see above) */
typedef	__bsd_ct_rune_t	__bsd_wchar_t;	/* wchar_t (see above) */
typedef	__bsd_ct_rune_t	__bsd_wint_t;	/* wint_t (see above) */

typedef	__bsd_uint32_t	__bsd_dev_t;	/* device number */

typedef	__bsd_uint32_t	__bsd_fixpt_t;	/* fixed point number */

/*
 * mbstate_t is an opaque object to keep conversion state during multibyte
 * stream conversions.
 */
typedef union {
	char		__mbstate8[128];
	__bsd_int64_t	_mbstateL;	/* for alignment */
} __bsd_mbstate_t;

#endif /* !_SYS__TYPES_H_ */
