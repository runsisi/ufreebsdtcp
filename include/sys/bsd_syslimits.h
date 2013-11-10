/*-
 * Copyright (c) 1988, 1993
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
 *	@(#)syslimits.h	8.1 (Berkeley) 6/2/93
 * $FreeBSD: release/9.2.0/sys/sys/syslimits.h 194498 2009-06-19 17:10:35Z brooks $
 */

#ifndef _BSD_SYS_SYSLIMITS_H_
#define _BSD_SYS_SYSLIMITS_H_

#if !defined(_KERNEL) && !defined(_LIMITS_H_) && !defined(_BSD_SYS_PARAM_H_)
#ifndef _SYS_CDEFS_H_
#error this file needs sys/cdefs.h as a prerequisite
#endif
#ifdef __CC_SUPPORTS_WARNING
#warning "No user-serviceable parts inside."
#endif
#endif

/*
 * Do not add any new variables here.  (See the comment at the end of
 * the file for why.)
 */
#define	BSD_ARG_MAX			262144	/* max bytes for an exec function */
#ifndef BSD_CHILD_MAX
#define	BSD_CHILD_MAX		   40	/* max simultaneous processes */
#endif
#define	BSD_LINK_MAX		32767	/* max file link count */
#define	BSD_MAX_CANON		  255	/* max bytes in term canon input line */
#define	BSD_MAX_INPUT		  255	/* max bytes in terminal input */
#define	BSD_NAME_MAX		  255	/* max bytes in a file name */
#ifndef BSD_NGROUPS_MAX
#define	BSD_NGROUPS_MAX	 	 1023	/* max supplemental group id's */
#endif
#ifndef BSD_OPEN_MAX
#define	BSD_OPEN_MAX		   64	/* max open files per process */
#endif
#define	BSD_PATH_MAX		 1024	/* max bytes in pathname */
#define	BSD_PIPE_BUF		  512	/* max bytes for atomic pipe writes */
#define	BSD_IOV_MAX			 1024	/* max elements in i/o vector */

/*
 * We leave the following values undefined to force applications to either
 * assume conservative values or call sysconf() to get the current value.
 *
 * HOST_NAME_MAX
 *
 * (We should do this for most of the values currently defined here,
 * but many programs are not prepared to deal with this yet.)
 */
#endif
