/*-
 * Copyright (c) 2001, 2002 Mike Barcroft <mike@FreeBSD.org>
 * Copyright (c) 2001 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Klaus Klein.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: release/9.2.0/sys/amd64/include/_stdint.h 217147 2011-01-08 12:43:05Z tijl $
 */

#ifndef _MACHINE__STDINT_H_
#define	_MACHINE__STDINT_H_

#if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS)

#define	BSD_INT8_C(c)		(c)
#define	BSD_INT16_C(c)		(c)
#define	BSD_INT32_C(c)		(c)
#define	BSD_INT64_C(c)		(c ## L)

#define	BSD_UINT8_C(c)		(c)
#define	BSD_UINT16_C(c)		(c)
#define	BSD_UINT32_C(c)		(c ## U)
#define	BSD_UINT64_C(c)		(c ## UL)

#define	BSD_INTMAX_C(c)		BSD_INT64_C(c)
#define	BSD_UINTMAX_C(c)		BSD_UINT64_C(c)

#endif /* !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) */

#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)

/*
 * ISO/IEC 9899:1999
 * 7.18.2.1 Limits of exact-width integer types
 */
/* Minimum values of exact-width signed integer types. */
#define	BSD_INT8_MIN	(-0x7f-1)
#define	BSD_INT16_MIN	(-0x7fff-1)
#define	BSD_INT32_MIN	(-0x7fffffff-1)
#define	BSD_INT64_MIN	(-0x7fffffffffffffffL-1)

/* Maximum values of exact-width signed integer types. */
#define	BSD_INT8_MAX	0x7f
#define	BSD_INT16_MAX	0x7fff
#define	BSD_INT32_MAX	0x7fffffff
#define	BSD_INT64_MAX	0x7fffffffffffffffL

/* Maximum values of exact-width unsigned integer types. */
#define	BSD_UINT8_MAX	0xff
#define	BSD_UINT16_MAX	0xffff
#define	BSD_UINT32_MAX	0xffffffffU
#define	BSD_UINT64_MAX	0xffffffffffffffffUL

/*
 * ISO/IEC 9899:1999
 * 7.18.2.2  Limits of minimum-width integer types
 */
/* Minimum values of minimum-width signed integer types. */
#define	BSD_INT_LEAST8_MIN	BSD_INT8_MIN
#define	BSD_INT_LEAST16_MIN	BSD_INT16_MIN
#define	BSD_INT_LEAST32_MIN	BSD_INT32_MIN
#define	BSD_INT_LEAST64_MIN	BSD_INT64_MIN

/* Maximum values of minimum-width signed integer types. */
#define	BSD_INT_LEAST8_MAX	BSD_INT8_MAX
#define	BSD_INT_LEAST16_MAX	BSD_INT16_MAX
#define	BSD_INT_LEAST32_MAX	BSD_INT32_MAX
#define	BSD_INT_LEAST64_MAX	BSD_INT64_MAX

/* Maximum values of minimum-width unsigned integer types. */
#define	BSD_UINT_LEAST8_MAX	 BSD_UINT8_MAX
#define	BSD_UINT_LEAST16_MAX BSD_UINT16_MAX
#define	BSD_UINT_LEAST32_MAX BSD_UINT32_MAX
#define	BSD_UINT_LEAST64_MAX BSD_UINT64_MAX

/*
 * ISO/IEC 9899:1999
 * 7.18.2.3  Limits of fastest minimum-width integer types
 */
/* Minimum values of fastest minimum-width signed integer types. */
#define	BSD_INT_FAST8_MIN	BSD_INT32_MIN
#define	BSD_INT_FAST16_MIN	BSD_INT32_MIN
#define	BSD_INT_FAST32_MIN	BSD_INT32_MIN
#define	BSD_INT_FAST64_MIN	BSD_INT64_MIN

/* Maximum values of fastest minimum-width signed integer types. */
#define	BSD_INT_FAST8_MAX	BSD_INT32_MAX
#define	BSD_INT_FAST16_MAX	BSD_INT32_MAX
#define	BSD_INT_FAST32_MAX	BSD_INT32_MAX
#define	BSD_INT_FAST64_MAX	BSD_INT64_MAX

/* Maximum values of fastest minimum-width unsigned integer types. */
#define	BSD_UINT_FAST8_MAX	BSD_UINT32_MAX
#define	BSD_UINT_FAST16_MAX	BSD_UINT32_MAX
#define	BSD_UINT_FAST32_MAX	BSD_UINT32_MAX
#define	BSD_UINT_FAST64_MAX	BSD_UINT64_MAX

/*
 * ISO/IEC 9899:1999
 * 7.18.2.4  Limits of integer types capable of holding object pointers
 */
#define	BSD_INTPTR_MIN	BSD_INT64_MIN
#define	BSD_INTPTR_MAX	BSD_INT64_MAX
#define	BSD_UINTPTR_MAX	BSD_UINT64_MAX

/*
 * ISO/IEC 9899:1999
 * 7.18.2.5  Limits of greatest-width integer types
 */
#define	BSD_INTMAX_MIN	BSD_INT64_MIN
#define	BSD_INTMAX_MAX	BSD_INT64_MAX
#define	BSD_UINTMAX_MAX	BSD_UINT64_MAX

/*
 * ISO/IEC 9899:1999
 * 7.18.3  Limits of other integer types
 */
/* Limits of ptrdiff_t. */
#define	BSD_PTRDIFF_MIN	BSD_INT64_MIN	
#define	BSD_PTRDIFF_MAX	BSD_INT64_MAX

/* Limits of sig_atomic_t. */
#define	BSD_SIG_ATOMIC_MIN	BSD_INT32_MIN
#define	BSD_SIG_ATOMIC_MAX	BSD_INT32_MAX

/* Limit of size_t. */
#define	BSD_SIZE_MAX	BSD_UINT64_MAX

#ifndef WCHAR_MIN /* Also possibly defined in <wchar.h> */
/* Limits of wchar_t. */
#define	BSD_WCHAR_MIN	BSD_INT32_MIN
#define	BSD_WCHAR_MAX	BSD_INT32_MAX
#endif

/* Limits of wint_t. */
#define	BSD_WINT_MIN	BSD_INT32_MIN
#define	BSD_WINT_MAX	BSD_INT32_MAX

#endif /* !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) */

#endif /* !_MACHINE__STDINT_H_ */
