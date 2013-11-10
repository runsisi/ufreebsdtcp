/*-
 * Copyright (c) 2011 David E. O'Brien <obrien@FreeBSD.org>
 * Copyright (c) 2001 Mike Barcroft <mike@FreeBSD.org>
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
 * $FreeBSD: release/9.2.0/sys/sys/_stdint.h 222813 2011-06-07 08:46:13Z attilio $
 */

#ifndef _BSD_SYS__STDINT_H_
#define _BSD_SYS__STDINT_H_

#ifndef _BSD_INT8_T_DECLARED
typedef	__bsd_int8_t		bsd_int8_t;
#define	_BSD_INT8_T_DECLARED
#endif

#ifndef _BSD_INT16_T_DECLARED
typedef	__bsd_int16_t		bsd_int16_t;
#define	_BSD_INT16_T_DECLARED
#endif

#ifndef _BSD_INT32_T_DECLARED
typedef	__bsd_int32_t		bsd_int32_t;
#define	_BSD_INT32_T_DECLARED
#endif

#ifndef _BSD_INT64_T_DECLARED
typedef	__bsd_int64_t		bsd_int64_t;
#define	_BSD_INT64_T_DECLARED
#endif

#ifndef _BSD_UINT8_T_DECLARED
typedef	__bsd_uint8_t		bsd_uint8_t;
#define	_BSD_UINT8_T_DECLARED
#endif

#ifndef _BSD_UINT16_T_DECLARED
typedef	__bsd_uint16_t		bsd_uint16_t;
#define	_BSD_UINT16_T_DECLARED
#endif

#ifndef _BSD_UINT32_T_DECLARED
typedef	__bsd_uint32_t		bsd_uint32_t;
#define	_BSD_UINT32_T_DECLARED
#endif

#ifndef _BSD_UINT64_T_DECLARED
typedef	__bsd_uint64_t		bsd_uint64_t;
#define	_BSD_UINT64_T_DECLARED
#endif

#ifndef _BSD_INTPTR_T_DECLARED
typedef	__bsd_intptr_t		bsd_intptr_t;
#define	_BSD_INTPTR_T_DECLARED
#endif
#ifndef _BSD_UINTPTR_T_DECLARED
typedef	__bsd_uintptr_t		bsd_uintptr_t;
#define	_BSD_UINTPTR_T_DECLARED
#endif

#endif /* !_SYS__STDINT_H_ */
