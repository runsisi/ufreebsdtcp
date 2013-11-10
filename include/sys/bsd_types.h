/*-
 * Copyright (c) 1982, 1986, 1991, 1993, 1994
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
 *	@(#)types.h	8.6 (Berkeley) 2/19/95
 * $FreeBSD: release/9.2.0/sys/sys/types.h 229285 2012-01-02 16:14:52Z mdf $
 */

#ifndef _BSD_SYS_TYPES_H_
#define	_BSD_SYS_TYPES_H_

#include <sys/bsd_cdefs.h>

/* Machine type dependent parameters. */
#include <machine/bsd_endian.h>
#include <sys/_bsd_types.h>

#if 0 // runsisi AT hust.edu.cn @2013/10/18
#include <sys/_bsd_pthreadtypes.h>
#endif // -------

#if __BSD_VISIBLE
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
#ifndef _KERNEL
typedef	unsigned short	ushort;		/* Sys V compatibility */
typedef	unsigned int	uint;		/* Sys V compatibility */
#endif
#endif

/*
 * XXX POSIX sized integrals that should appear only in <sys/stdint.h>.
 */
#include <sys/_bsd_stdint.h>

#if 0	// runsisi AT hust.edu.cn @2013/11/06
typedef __bsd_uint8_t	bsd_uint8_t;	/* unsigned integrals (deprecated) */
typedef __bsd_uint16_t	bsd_uint16_t;
typedef __bsd_uint32_t	bsd_uint32_t;
typedef __bsd_uint64_t	bsd_uint64_t;
#endif 	// ---------------------- @2013/11/06

typedef	__bsd_uint64_t	bsd_uquad_t;	/* quads (deprecated) */
typedef	__bsd_int64_t	bsd_quad_t;
typedef	bsd_quad_t *	qaddr_t;

typedef	char *		caddr_t;	/* core address */
typedef	__const char *	c_caddr_t;	/* core address, pointer to const */
typedef	__volatile char *v_caddr_t;	/* core address, pointer to volatile */

#ifndef _BSD_BLKSIZE_T_DECLARED
typedef	__bsd_blksize_t	bsd_blksize_t;
#define	_BSD_BLKSIZE_T_DECLARED
#endif

typedef	__bsd_cpuwhich_t	bsd_cpuwhich_t;
typedef	__bsd_cpulevel_t	bsd_cpulevel_t;
typedef	__bsd_cpusetid_t	bsd_cpusetid_t;

#ifndef _BSD_BLKCNT_T_DECLARED
typedef	__bsd_blkcnt_t	blkcnt_t;
#define	_BSD_BLKCNT_T_DECLARED
#endif

typedef	__bsd_cap_rights_t	bsd_cap_rights_t;

#ifndef _BSD_CLOCK_T_DECLARED
typedef	__bsd_clock_t	bsd_clock_t;
#define	_BSD_CLOCK_T_DECLARED
#endif

#ifndef _BSD_CLOCKID_T_DECLARED
typedef	__bsd_clockid_t	bsd_clockid_t;
#define	_BSD_CLOCKID_T_DECLARED
#endif

typedef	__bsd_critical_t	bsd_critical_t;	/* Critical section value */
typedef	__bsd_int64_t	bsd_daddr_t;	/* disk address */

#ifndef _BSD_DEV_T_DECLARED
typedef	__bsd_dev_t		bsd_dev_t;		/* device number or struct cdev */
#define	_BSD_DEV_T_DECLARED
#endif

#ifndef _BSD_FFLAGS_T_DECLARED
typedef	__bsd_fflags_t	bsd_fflags_t;	/* file flags */
#define	_BSD_FFLAGS_T_DECLARED
#endif

typedef	__bsd_fixpt_t	bsd_fixpt_t;	/* fixed point number */

#ifndef _BSD_FSBLKCNT_T_DECLARED		/* for statvfs() */
typedef	__bsd_fsblkcnt_t	bsd_fsblkcnt_t;
typedef	__bsd_fsfilcnt_t	bsd_fsfilcnt_t;
#define	_BSD_FSBLKCNT_T_DECLARED
#endif

#ifndef _BSD_GID_T_DECLARED
typedef	__bsd_gid_t		bsd_gid_t;		/* group id */
#define	_BSD_GID_T_DECLARED
#endif

#ifndef _BSD_IN_ADDR_T_DECLARED
typedef	__bsd_uint32_t	bsd_in_addr_t;	/* base type for internet address */
#define	_BSD_IN_ADDR_T_DECLARED
#endif

#ifndef _BSD_IN_PORT_T_DECLARED
typedef	__bsd_uint16_t	bsd_in_port_t;
#define	_BSD_IN_PORT_T_DECLARED
#endif

#ifndef _BSD_ID_T_DECLARED
typedef	__bsd_id_t		bsd_id_t;		/* can hold a uid_t or pid_t */
#define	_BSD_ID_T_DECLARED
#endif

#ifndef _BSD_INO_T_DECLARED
typedef	__bsd_ino_t		bsd_ino_t;		/* inode number */
#define	_BSD_INO_T_DECLARED
#endif

#ifndef _BSD_KEY_T_DECLARED
typedef	__bsd_key_t		bsd_key_t;		/* IPC key (for Sys V IPC) */
#define	_BSD_KEY_T_DECLARED
#endif

#ifndef _BSD_LWPID_T_DECLARED
typedef	__bsd_lwpid_t	bsd_lwpid_t;	/* Thread ID (a.k.a. LWP) */
#define	_BSD_LWPID_T_DECLARED
#endif

#ifndef _BSD_MODE_T_DECLARED
typedef	__bsd_mode_t	bsd_mode_t;		/* permissions */
#define	_BSD_MODE_T_DECLARED
#endif

#ifndef _BSD_ACCMODE_T_DECLARED
typedef	__bsd_accmode_t	bsd_accmode_t;	/* access permissions */
#define	_BSD_ACCMODE_T_DECLARED
#endif

#ifndef _BSD_NLINK_T_DECLARED
typedef	__bsd_nlink_t	bsd_nlink_t;	/* link count */
#define	_BSD_NLINK_T_DECLARED
#endif

#ifndef _BSD_OFF_T_DECLARED
typedef	__bsd_off_t		bsd_off_t;		/* file offset */
#define	_BSD_OFF_T_DECLARED
#endif

#ifndef _BSD_PID_T_DECLARED
typedef	__bsd_pid_t		bsd_pid_t;		/* process id */
#define	_BSD_PID_T_DECLARED
#endif

typedef	__bsd_register_t	bsd_register_t;

#ifndef _BSD_RLIM_T_DECLARED
typedef	__bsd_rlim_t	bsd_rlim_t;		/* resource limit */
#define	_BSD_RLIM_T_DECLARED
#endif

typedef	__bsd_segsz_t	bsd_segsz_t;	/* segment size (in pages) */

#ifndef _BSD_SIZE_T_DECLARED
typedef	__bsd_size_t	bsd_size_t;
#define	_BSD_SIZE_T_DECLARED
#endif

#ifndef _BSD_SSIZE_T_DECLARED
typedef	__bsd_ssize_t	bsd_ssize_t;
#define	_BSD_SSIZE_T_DECLARED
#endif

#ifndef _BSD_SUSECONDS_T_DECLARED
typedef	__bsd_suseconds_t	bsd_suseconds_t;	/* microseconds (signed) */
#define	_BSD_SUSECONDS_T_DECLARED
#endif

#ifndef _BSD_TIME_T_DECLARED
typedef	__bsd_time_t	bsd_time_t;
#define	_BSD_TIME_T_DECLARED
#endif

#ifndef _BSD_TIMER_T_DECLARED
typedef	__bsd_timer_t	bsd_timer_t;
#define	_BSD_TIMER_T_DECLARED
#endif

#ifndef _BSD_MQD_T_DECLARED
typedef	__bsd_mqd_t	bsd_mqd_t;
#define	_BSD_MQD_T_DECLARED
#endif

typedef	__bsd_u_register_t	bsd_u_register_t;

#ifndef _BSD_UID_T_DECLARED
typedef	__bsd_uid_t		bsd_uid_t;		/* user id */
#define	_BSD_UID_T_DECLARED
#endif

#ifndef _BSD_USECONDS_T_DECLARED
typedef	__bsd_useconds_t	bsd_useconds_t;	/* microseconds (unsigned) */
#define	_BSD_USECONDS_T_DECLARED
#endif

typedef	__bsd_vm_offset_t	bsd_vm_offset_t;
typedef	__bsd_vm_ooffset_t	bsd_vm_ooffset_t;
typedef	__bsd_vm_paddr_t	bsd_vm_paddr_t;
typedef	__bsd_vm_pindex_t	bsd_vm_pindex_t;
typedef	__bsd_vm_size_t	bsd_vm_size_t;

#ifdef _KERNEL
typedef	int		bsd_boolean_t;
typedef	struct device	*bsd_device_t;
typedef	__bsd_intfptr_t	bsd_intfptr_t;

/*
 * XXX this is fixed width for historical reasons.  It should have had type
 * __int_fast32_t.  Fixed-width types should not be used unless binary
 * compatibility is essential.  Least-width types should be used even less
 * since they provide smaller benefits.
 *
 * XXX should be MD.
 *
 * XXX this is bogus in -current, but still used for spl*().
 */
typedef	__bsd_uint32_t	bsd_intrmask_t;	/* Interrupt mask (spl, xxx_imask...) */

typedef	__bsd_uintfptr_t	bsd_uintfptr_t;
typedef	__bsd_uint64_t	bsd_uoff_t;
typedef	char		bsd_vm_memattr_t;	/* memory attribute codes */
typedef	struct vm_page	*bsd_vm_page_t;

#if !defined(__bool_true_false_are_defined) && !defined(__cplusplus)
#define	__bool_true_false_are_defined	1
#define	false	0
#define	true	1
#if __STDC_VERSION__ < 199901L && __GNUC__ < 3 && !defined(__INTEL_COMPILER)
typedef	int	_Bool;
#endif
typedef	_Bool	bool;
#endif /* !__bool_true_false_are_defined && !__cplusplus */

#define bsd_offsetof(type, field) __bsd_offsetof(type, field)

#endif /* !_KERNEL */

/*
 * The following are all things that really shouldn't exist in this header,
 * since its purpose is to provide typedefs, not miscellaneous doodads.
 */
#if __BSD_VISIBLE

#include <sys/bsd_select.h>

/*
 * minor() gives a cookie instead of an index since we don't want to
 * change the meanings of bits 0-15 or waste time and space shifting
 * bits 16-31 for devices that don't use them.
 */
#define	bsd_major(x)	((int)(((u_int)(x) >> 8)&0xff))	/* major number */
#define	bsd_minor(x)	((int)((x)&0xffff00ff))		/* minor number */
#define	bsd_makedev(x,y)	((bsd_dev_t)(((x) << 8) | (y)))	/* create dev_t */

/*
 * These declarations belong elsewhere, but are repeated here and in
 * <stdio.h> to give broken programs a better chance of working with
 * 64-bit off_t's.
 */
#ifndef _KERNEL
__BEGIN_DECLS
#ifndef _FTRUNCATE_DECLARED
#define	_FTRUNCATE_DECLARED
int	 ftruncate(int, bsd_off_t);
#endif
#ifndef _LSEEK_DECLARED
#define	_LSEEK_DECLARED
bsd_off_t	 lseek(int, bsd_off_t, int);
#endif
#ifndef _MMAP_DECLARED
#define	_MMAP_DECLARED
void *	 mmap(void *, bsd_size_t, int, int, int, bsd_off_t);
#endif
#ifndef _TRUNCATE_DECLARED
#define	_TRUNCATE_DECLARED
int	 truncate(const char *, bsd_off_t);
#endif
__END_DECLS
#endif /* !_KERNEL */

#endif /* __BSD_VISIBLE */

#endif /* !_SYS_TYPES_H_ */
