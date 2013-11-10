/*-
 * Copyright (c) 1983, 1990, 1993
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
 *	@(#)fcntl.h	8.3 (Berkeley) 1/21/94
 * $FreeBSD: release/9.2.0/sys/sys/fcntl.h 239899 2012-08-30 10:12:40Z kib $
 */

#ifndef _BSD_SYS_FCNTL_H_
#define	_BSD_SYS_FCNTL_H_

/*
 * This file includes the definitions for open and fcntl
 * described by POSIX for <fcntl.h>; it also includes
 * related kernel definitions.
 */

#include <sys/bsd_cdefs.h>
#include <sys/_bsd_types.h>

#ifndef _BSD_MODE_T_DECLARED
typedef	__bsd_mode_t	bsd_mode_t;
#define	_BSD_MODE_T_DECLARED
#endif

#ifndef _BSD_OFF_T_DECLARED
typedef	__bsd_off_t		bsd_off_t;
#define	_BSD_OFF_T_DECLARED
#endif

#ifndef _BSD_PID_T_DECLARED
typedef	__bsd_pid_t		bsd_pid_t;
#define	_BSD_PID_T_DECLARED
#endif

/*
 * File status flags: these are used by open(2), fcntl(2).
 * They are also used (indirectly) in the kernel file structure f_flags,
 * which is a superset of the open/fcntl flags.  Open flags and f_flags
 * are inter-convertible using OFLAGS(fflags) and FFLAGS(oflags).
 * Open/fcntl flags begin with O_; kernel-internal flags begin with F.
 */
/* open-only flags */
#define	BSD_O_RDONLY	0x0000		/* open for reading only */
#define	BSD_O_WRONLY	0x0001		/* open for writing only */
#define	BSD_O_RDWR		0x0002		/* open for reading and writing */
#define	BSD_O_ACCMODE	0x0003		/* mask for above modes */

/*
 * Kernel encoding of open mode; separate read and write bits that are
 * independently testable: 1 greater than the above.
 *
 * XXX
 * FREAD and FWRITE are excluded from the #ifdef _KERNEL so that TIOCFLUSH,
 * which was documented to use FREAD/FWRITE, continues to work.
 */
#if __BSD_VISIBLE
#define	BSD_FREAD		0x0001
#define	BSD_FWRITE		0x0002
#endif
#define	BSD_O_NONBLOCK	0x0004		/* no delay */
#define	BSD_O_APPEND	0x0008		/* set append mode */
#if __BSD_VISIBLE
#define	BSD_O_SHLOCK	0x0010		/* open with shared file lock */
#define	BSD_O_EXLOCK	0x0020		/* open with exclusive file lock */
#define	BSD_O_ASYNC		0x0040		/* signal pgrp when data ready */
#define	BSD_O_FSYNC		0x0080		/* synchronous writes */
#endif
#define	BSD_O_SYNC		0x0080		/* POSIX synonym for O_FSYNC */
#if __BSD_VISIBLE
#define	BSD_O_NOFOLLOW	0x0100		/* don't follow symlinks */
#endif
#define	BSD_O_CREAT		0x0200		/* create if nonexistent */
#define	BSD_O_TRUNC		0x0400		/* truncate to zero length */
#define	BSD_O_EXCL		0x0800		/* error if already exists */
#ifdef _KERNEL
#define	BSD_FHASLOCK	0x4000		/* descriptor holds advisory lock */
#endif

/* Defined by POSIX 1003.1; BSD default, but must be distinct from O_RDONLY. */
#define	BSD_O_NOCTTY	0x8000		/* don't assign controlling terminal */

#if __BSD_VISIBLE
/* Attempt to bypass buffer cache */
#define	BSD_O_DIRECT	0x00010000
#endif

/* Defined by POSIX Extended API Set Part 2 */
#if __BSD_VISIBLE
#define	BSD_O_DIRECTORY	0x00020000	/* Fail if not directory */
#define	BSD_O_EXEC		0x00040000	/* Open for execute only */
#endif
#ifdef	_KERNEL
#define	BSD_FEXEC		BSD_O_EXEC
#endif

#if __POSIX_VISIBLE >= 200809
/* Defined by POSIX 1003.1-2008; BSD default, but reserve for future use. */
#define	BSD_O_TTY_INIT	0x00080000	/* Restore default termios attributes */

#define	BSD_O_CLOEXEC	0x00100000
#endif

/*
 * XXX missing O_DSYNC, O_RSYNC.
 */

#ifdef _KERNEL
/* convert from open() flags to/from fflags; convert O_RD/WR to FREAD/FWRITE */
#define	BSD_FFLAGS(oflags)	((oflags) + 1)
#define	BSD_OFLAGS(fflags)	((fflags) - 1)

/* bits to save after open */
#define	BSD_FMASK	(BSD_FREAD|BSD_FWRITE|BSD_FAPPEND|BSD_FASYNC|BSD_FFSYNC|BSD_FNONBLOCK|BSD_O_DIRECT|BSD_FEXEC)
/* bits settable by fcntl(F_SETFL, ...) */
#define	BSD_FCNTLFLAGS	(BSD_FAPPEND|BSD_FASYNC|BSD_FFSYNC|BSD_FNONBLOCK|BSD_FRDAHEAD|BSD_O_DIRECT)

#if defined(COMPAT_FREEBSD7) || defined(COMPAT_FREEBSD6) || \
    defined(COMPAT_FREEBSD5) || defined(COMPAT_FREEBSD4)
/*
 * Set by shm_open(3) in older libc's to get automatic MAP_ASYNC
 * behavior for POSIX shared memory objects (which are otherwise
 * implemented as plain files).
 */
#define	BSD_FPOSIXSHM	BSD_O_NOFOLLOW
#undef BSD_FCNTLFLAGS
#define	BSD_FCNTLFLAGS	(BSD_FAPPEND|BSD_FASYNC|BSD_FFSYNC|BSD_FNONBLOCK|BSD_FPOSIXSHM|BSD_FRDAHEAD| \
        BSD_O_DIRECT)
#endif
#endif

/*
 * The O_* flags used to have only F* names, which were used in the kernel
 * and by fcntl.  We retain the F* names for the kernel f_flag field
 * and for backward compatibility for fcntl.  These flags are deprecated.
 */
#if __BSD_VISIBLE
#define	BSD_FAPPEND		BSD_O_APPEND	/* kernel/compat */
#define	BSD_FASYNC		BSD_O_ASYNC		/* kernel/compat */
#define	BSD_FFSYNC		BSD_O_FSYNC		/* kernel */
#define	BSD_FNONBLOCK	BSD_O_NONBLOCK	/* kernel */
#define	BSD_FNDELAY		BSD_O_NONBLOCK	/* compat */
#define	BSD_O_NDELAY	BSD_O_NONBLOCK	/* compat */
#endif

/*
 * We are out of bits in f_flag (which is a short).  However,
 * the flag bits not set in FMASK are only meaningful in the
 * initial open syscall.  Those bits can thus be given a
 * different meaning for fcntl(2).
 */
#if __BSD_VISIBLE
/* Read ahead */
#define	BSD_FRDAHEAD	BSD_O_CREAT
#endif

/* Defined by POSIX Extended API Set Part 2 */
#if __BSD_VISIBLE
/*
 * Magic value that specify the use of the current working directory
 * to determine the target of relative file paths in the openat() and
 * similar syscalls.
 */
#define	BSD_AT_FDCWD		-100

/*
 * Miscellaneous flags for the *at() syscalls.
 */
#define	BSD_AT_EACCESS		0x100	/* Check access using effective user and group ID */
#define	BSD_AT_SYMLINK_NOFOLLOW	0x200   /* Do not follow symbolic links */
#define	BSD_AT_SYMLINK_FOLLOW	0x400	/* Follow symbolic link */
#define	BSD_AT_REMOVEDIR		0x800	/* Remove directory instead of file */
#endif

/*
 * Constants used for fcntl(2)
 */

/* command values */
#define	BSD_F_DUPFD		0		/* duplicate file descriptor */
#define	BSD_F_GETFD		1		/* get file descriptor flags */
#define	BSD_F_SETFD		2		/* set file descriptor flags */
#define	BSD_F_GETFL		3		/* get file status flags */
#define	BSD_F_SETFL		4		/* set file status flags */
#if __BSD_VISIBLE || __XSI_VISIBLE || __POSIX_VISIBLE >= 200112
#define	BSD_F_GETOWN	5		/* get SIGIO/SIGURG proc/pgrp */
#define	BSD_F_SETOWN	6		/* set SIGIO/SIGURG proc/pgrp */
#endif
#if __BSD_VISIBLE
#define	BSD_F_OGETLK	7		/* get record locking information */
#define	BSD_F_OSETLK	8		/* set record locking information */
#define	BSD_F_OSETLKW	9		/* F_SETLK; wait if blocked */
#define	BSD_F_DUP2FD	10		/* duplicate file descriptor to arg */
#endif
#define	BSD_F_GETLK		11		/* get record locking information */
#define	BSD_F_SETLK		12		/* set record locking information */
#define	BSD_F_SETLKW	13		/* F_SETLK; wait if blocked */
#if __BSD_VISIBLE
#define	BSD_F_SETLK_REMOTE	14		/* debugging support for remote locks */
#define	BSD_F_READAHEAD	15		/* read ahead */
#define	BSD_F_RDAHEAD	16		/* Darwin compatible read ahead */
#endif
#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200809
#define	BSD_F_DUPFD_CLOEXEC	17		/* Like F_DUPFD, but FD_CLOEXEC is set */
#endif
#if __BSD_VISIBLE
#define	BSD_F_DUP2FD_CLOEXEC 18		/* Like F_DUP2FD, but FD_CLOEXEC is set */
#endif

/* file descriptor flags (F_GETFD, F_SETFD) */
#define	BSD_FD_CLOEXEC	1		/* close-on-exec flag */

/* record locking flags (F_GETLK, F_SETLK, F_SETLKW) */
#define	BSD_F_RDLCK		1		/* shared or read lock */
#define	BSD_F_UNLCK		2		/* unlock */
#define	BSD_F_WRLCK		3		/* exclusive or write lock */
#if __BSD_VISIBLE
#define	BSD_F_UNLCKSYS	4		/* purge locks for a given system ID */
#define	BSD_F_CANCEL	5		/* cancel an async lock request */
#endif
#ifdef _KERNEL
#define	BSD_F_WAIT		0x010		/* Wait until lock is granted */
#define	BSD_F_FLOCK		0x020	 	/* Use flock(2) semantics for lock */
#define	BSD_F_POSIX		0x040	 	/* Use POSIX semantics for lock */
#define	BSD_F_REMOTE	0x080		/* Lock owner is remote NFS client */
#define	BSD_F_NOINTR	0x100		/* Ignore signals when waiting */
#endif

/*
 * Advisory file segment locking data type -
 * information passed to system by user
 */
struct bsd_flock {
	bsd_off_t	l_start;	/* starting offset */
	bsd_off_t	l_len;		/* len = 0 means until end of file */
	bsd_pid_t	l_pid;		/* lock owner */
	short	l_type;		/* lock type: read/write, etc. */
	short	l_whence;	/* type of l_start */
	int	l_sysid;	/* remote system id or zero for local */
};

#if __BSD_VISIBLE
/*
 * Old advisory file segment locking data type,
 * before adding l_sysid.
 */
struct __bsd_oflock {
	bsd_off_t	l_start;	/* starting offset */
	bsd_off_t	l_len;		/* len = 0 means until end of file */
	bsd_pid_t	l_pid;		/* lock owner */
	short	l_type;		/* lock type: read/write, etc. */
	short	l_whence;	/* type of l_start */
};
#endif

#if __BSD_VISIBLE
/* lock operations for flock(2) */
#define	BSD_LOCK_SH		0x01		/* shared file lock */
#define	BSD_LOCK_EX		0x02		/* exclusive file lock */
#define	BSD_LOCK_NB		0x04		/* don't block when locking */
#define	BSD_LOCK_UN		0x08		/* unlock file */
#endif

#if __POSIX_VISIBLE >= 200112
/*
 * Advice to posix_fadvise
 */
#define	BSD_POSIX_FADV_NORMAL	0	/* no special treatment */
#define	BSD_POSIX_FADV_RANDOM	1	/* expect random page references */
#define	BSD_POSIX_FADV_SEQUENTIAL	2	/* expect sequential page references */
#define	BSD_POSIX_FADV_WILLNEED	3	/* will need these pages */
#define	BSD_POSIX_FADV_DONTNEED	4	/* dont need these pages */
#define	BSD_POSIX_FADV_NOREUSE	5	/* access data only once */
#endif

#ifndef _KERNEL
__BEGIN_DECLS
int	open(const char *, int, ...);
int	creat(const char *, bsd_mode_t);
int	fcntl(int, int, ...);
#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200809
int	openat(int, const char *, int, ...);
#endif
#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200112
int	posix_fadvise(int, bsd_off_t, bsd_off_t, int);
int	posix_fallocate(int, bsd_off_t, bsd_off_t);
#endif
#if __BSD_VISIBLE
int	bsd_flock(int, int);
#endif
__END_DECLS
#endif

#endif /* !_SYS_FCNTL_H_ */
