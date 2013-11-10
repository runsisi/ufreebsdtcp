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
 *	@(#)errno.h	8.5 (Berkeley) 1/21/94
 * $FreeBSD: release/9.2.0/sys/sys/errno.h 220335 2011-04-04 17:39:30Z avg $
 */

#ifndef _BSD_SYS_ERRNO_H_
#define _BSD_SYS_ERRNO_H_

#define	BSD_EPERM		1		/* Operation not permitted */
#define	BSD_ENOENT		2		/* No such file or directory */
#define	BSD_ESRCH		3		/* No such process */
#define	BSD_EINTR		4		/* Interrupted system call */
#define	BSD_EIO		5		/* Input/output error */
#define	BSD_ENXIO		6		/* Device not configured */
#define	BSD_E2BIG		7		/* Argument list too long */
#define	BSD_ENOEXEC		8		/* Exec format error */
#define	BSD_EBADF		9		/* Bad file descriptor */
#define	BSD_ECHILD		10		/* No child processes */
#define	BSD_EDEADLK		11		/* Resource deadlock avoided */
                    /* 11 was EAGAIN */
#define	BSD_ENOMEM		12		/* Cannot allocate memory */
#define	BSD_EACCES		13		/* Permission denied */
#define	BSD_EFAULT		14		/* Bad address */
#ifndef _POSIX_SOURCE
#define	BSD_ENOTBLK		15		/* Block device required */
#endif
#define	BSD_EBUSY		16		/* Device busy */
#define	BSD_EEXIST		17		/* File exists */
#define	BSD_EXDEV		18		/* Cross-device link */
#define	BSD_ENODEV		19		/* Operation not supported by device */
#define	BSD_ENOTDIR		20		/* Not a directory */
#define	BSD_EISDIR		21		/* Is a directory */
#define	BSD_EINVAL		22		/* Invalid argument */
#define	BSD_ENFILE		23		/* Too many open files in system */
#define	BSD_EMFILE		24		/* Too many open files */
#define	BSD_ENOTTY		25		/* Inappropriate ioctl for device */
#ifndef _POSIX_SOURCE
#define	BSD_ETXTBSY		26		/* Text file busy */
#endif
#define	BSD_EFBIG		27		/* File too large */
#define	BSD_ENOSPC		28		/* No space left on device */
#define	BSD_ESPIPE		29		/* Illegal seek */
#define	BSD_EROFS		30		/* Read-only filesystem */
#define	BSD_EMLINK		31		/* Too many links */
#define	BSD_EPIPE		32		/* Broken pipe */

/* math software */
#define	BSD_EDOM		33		/* Numerical argument out of domain */
#define	BSD_ERANGE		34		/* Result too large */

/* non-blocking and interrupt i/o */
#define	BSD_EAGAIN		35		/* Resource temporarily unavailable */
#ifndef _POSIX_SOURCE
#define	BSD_EWOULDBLOCK	BSD_EAGAIN		/* Operation would block */
#define	BSD_EINPROGRESS	36		/* Operation now in progress */
#define	BSD_EALREADY	37		/* Operation already in progress */

/* ipc/network software -- argument errors */
#define	BSD_ENOTSOCK	38		/* Socket operation on non-socket */
#define	BSD_EDESTADDRREQ	39		/* Destination address required */
#define	BSD_EMSGSIZE	40		/* Message too long */
#define	BSD_EPROTOTYPE	41		/* Protocol wrong type for socket */
#define	BSD_ENOPROTOOPT	42		/* Protocol not available */
#define	BSD_EPROTONOSUPPORT	43		/* Protocol not supported */
#define	BSD_ESOCKTNOSUPPORT	44		/* Socket type not supported */
#define	BSD_EOPNOTSUPP	45		/* Operation not supported */
#define	BSD_ENOTSUP		BSD_EOPNOTSUPP	/* Operation not supported */
#define	BSD_EPFNOSUPPORT	46		/* Protocol family not supported */
#define	BSD_EAFNOSUPPORT	47		/* Address family not supported by protocol family */
#define	BSD_EADDRINUSE	48		/* Address already in use */
#define	BSD_EADDRNOTAVAIL	49		/* Can't assign requested address */

/* ipc/network software -- operational errors */
#define	BSD_ENETDOWN	50		/* Network is down */
#define	BSD_ENETUNREACH	51		/* Network is unreachable */
#define	BSD_ENETRESET	52		/* Network dropped connection on reset */
#define	BSD_ECONNABORTED	53		/* Software caused connection abort */
#define	BSD_ECONNRESET	54		/* Connection reset by peer */
#define	BSD_ENOBUFS		55		/* No buffer space available */
#define	BSD_EISCONN		56		/* Socket is already connected */
#define	BSD_ENOTCONN	57		/* Socket is not connected */
#define	BSD_ESHUTDOWN	58		/* Can't send after socket shutdown */
#define	BSD_ETOOMANYREFS	59		/* Too many references: can't splice */
#define	BSD_ETIMEDOUT	60		/* Operation timed out */
#define	BSD_ECONNREFUSED	61		/* Connection refused */

#define	BSD_ELOOP		62		/* Too many levels of symbolic links */
#endif /* _POSIX_SOURCE */
#define	BSD_ENAMETOOLONG	63		/* File name too long */

/* should be rearranged */
#ifndef _POSIX_SOURCE
#define	BSD_EHOSTDOWN	64		/* Host is down */
#define	BSD_EHOSTUNREACH	65		/* No route to host */
#endif /* _POSIX_SOURCE */
#define	BSD_ENOTEMPTY	66		/* Directory not empty */

/* quotas & mush */
#ifndef _POSIX_SOURCE
#define	BSD_EPROCLIM	67		/* Too many processes */
#define	BSD_EUSERS		68		/* Too many users */
#define	BSD_EDQUOT		69		/* Disc quota exceeded */

/* Network File System */
#define	BSD_ESTALE		70		/* Stale NFS file handle */
#define	BSD_EREMOTE		71		/* Too many levels of remote in path */
#define	BSD_EBADRPC		72		/* RPC struct is bad */
#define	BSD_ERPCMISMATCH	73		/* RPC version wrong */
#define	BSD_EPROGUNAVAIL	74		/* RPC prog. not avail */
#define	BSD_EPROGMISMATCH	75		/* Program version wrong */
#define	BSD_EPROCUNAVAIL	76		/* Bad procedure for program */
#endif /* _POSIX_SOURCE */

#define	BSD_ENOLCK		77		/* No locks available */
#define	BSD_ENOSYS		78		/* Function not implemented */

#ifndef _POSIX_SOURCE
#define	BSD_EFTYPE		79		/* Inappropriate file type or format */
#define	BSD_EAUTH		80		/* Authentication error */
#define	BSD_ENEEDAUTH	81		/* Need authenticator */
#define	BSD_EIDRM		82		/* Identifier removed */
#define	BSD_ENOMSG		83		/* No message of desired type */
#define	BSD_EOVERFLOW	84		/* Value too large to be stored in data type */
#define	BSD_ECANCELED	85		/* Operation canceled */
#define	BSD_EILSEQ		86		/* Illegal byte sequence */
#define	BSD_ENOATTR		87		/* Attribute not found */

#define	BSD_EDOOFUS		88		/* Programming error */
#endif /* _POSIX_SOURCE */

#define	BSD_EBADMSG		89		/* Bad message */
#define	BSD_EMULTIHOP	90		/* Multihop attempted */
#define	BSD_ENOLINK		91		/* Link has been severed */
#define	BSD_EPROTO		92		/* Protocol error */

#ifndef _POSIX_SOURCE
#define	BSD_ENOTCAPABLE	93		/* Capabilities insufficient */
#define	BSD_ECAPMODE	94		/* Not permitted in capability mode */
#endif /* _POSIX_SOURCE */

#ifndef _POSIX_SOURCE
#define	BSD_ELAST		94		/* Must be equal largest errno */
#endif /* _POSIX_SOURCE */

#ifdef _KERNEL
/* pseudo-errors returned inside kernel to modify return to process */
#define	BSD_ERESTART	(-1)		/* restart syscall */
#define	BSD_EJUSTRETURN	(-2)		/* don't modify regs, just return */
#define	BSD_ENOIOCTL	(-3)		/* ioctl not handled by this layer */
#define	BSD_EDIRIOCTL	(-4)		/* do direct ioctl in GEOM */
#endif

#endif
