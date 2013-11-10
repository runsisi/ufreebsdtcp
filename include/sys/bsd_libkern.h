/*-
 * Copyright (c) 1992, 1993
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
 *	@(#)libkern.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: release/9.2.0/sys/sys/libkern.h 249915 2013-04-26 01:56:58Z ache $
 */

#ifndef _SYS_LIBKERN_H_
#define	_SYS_LIBKERN_H_

#include <sys/bsd_cdefs.h>
#include <sys/bsd_types.h>
#ifdef _KERNEL
#include <sys/bsd_systm.h>
#endif

#ifndef	LIBKERN_INLINE
#define	LIBKERN_INLINE  static __inline
#define	LIBKERN_BODY
#endif

/* BCD conversions. */
extern u_char const	bcd2bin_data[];
extern u_char const	bin2bcd_data[];
extern char const	hex2ascii_data[];

#define	bcd2bin(bcd)	(bcd2bin_data[bcd])
#define	bin2bcd(bin)	(bin2bcd_data[bin])
#define	hex2ascii(hex)	(hex2ascii_data[hex])

static __inline int imax(int a, int b) { return (a > b ? a : b); }
static __inline int imin(int a, int b) { return (a < b ? a : b); }
static __inline long lmax(long a, long b) { return (a > b ? a : b); }
static __inline long lmin(long a, long b) { return (a < b ? a : b); }
static __inline u_int max(u_int a, u_int b) { return (a > b ? a : b); }
static __inline u_int min(u_int a, u_int b) { return (a < b ? a : b); }
static __inline bsd_quad_t qmax(bsd_quad_t a, bsd_quad_t b) { return (a > b ? a : b); }
static __inline bsd_quad_t qmin(bsd_quad_t a, bsd_quad_t b) { return (a < b ? a : b); }
static __inline u_long ulmax(u_long a, u_long b) { return (a > b ? a : b); }
static __inline u_long ulmin(u_long a, u_long b) { return (a < b ? a : b); }
static __inline bsd_off_t omax(bsd_off_t a, bsd_off_t b) { return (a > b ? a : b); }
static __inline bsd_off_t omin(bsd_off_t a, bsd_off_t b) { return (a < b ? a : b); }

static __inline int bsd_abs(int a) { return (a < 0 ? -a : a); }
static __inline long bsd_labs(long a) { return (a < 0 ? -a : a); }
static __inline bsd_quad_t bsd_qabs(bsd_quad_t a) { return (a < 0 ? -a : a); }

#define	ARC4_ENTR_NONE	0	/* Don't have entropy yet. */
#define	ARC4_ENTR_HAVE	1	/* Have entropy. */
#define	ARC4_ENTR_SEED	2	/* Reseeding. */
extern int arc4rand_iniseed_state;

/* Prototypes for non-quad routines. */
struct malloc_type;
bsd_uint32_t arc4random(void);
void	 arc4rand(void *ptr, u_int len, int reseed);
//int	 bcmp(const void *, const void *, bsd_size_t);
//void	*bsearch(const void *, const void *, bsd_size_t,
//	    bsd_size_t, int (*)(const void *, const void *));
#ifndef	HAVE_INLINE_FFS
int	 ffs(int);
#endif
#ifndef	HAVE_INLINE_FFSL
int	 ffsl(long);
#endif
#ifndef	HAVE_INLINE_FLS
int	 fls(int);
#endif
#ifndef	HAVE_INLINE_FLSL
int	 flsl(long);
#endif
#if 0 // runsisi AT hust.edu.cn @2013/10/18
int	 fnmatch(const char *, const char *, int);
int	 locc(int, char *, u_int);
void	*memchr(const void *s, int c, bsd_size_t n);
int	 memcmp(const void *b1, const void *b2, bsd_size_t len);
void	 qsort(void *base, bsd_size_t nmemb, bsd_size_t size,
        int (*compar)(const void *, const void *));
void	 qsort_r(void *base, bsd_size_t nmemb, bsd_size_t size, void *thunk,
        int (*compar)(void *, const void *, const void *));
u_long	 random(void);
char	*index(const char *, int);
char	*rindex(const char *, int);
int	 scanc(u_int, const u_char *, const u_char *, int);
int	 skpc(int, int, char *);
void	 srandom(u_long);
int	 strcasecmp(const char *, const char *);
char	*strcat(char * __restrict, const char * __restrict);
int	 strcmp(const char *, const char *);
char	*strcpy(char * __restrict, const char * __restrict);
bsd_size_t	 strcspn(const char * __restrict, const char * __restrict) __pure;
char	*strdup(const char *__restrict, struct malloc_type *);
bsd_size_t	 strlcat(char *, const char *, bsd_size_t);
#endif
bsd_size_t	 bsd_strlcpy(char *, const char *, bsd_size_t);
#if 0
bsd_size_t	 strlen(const char *);
int	 strncasecmp(const char *, const char *, bsd_size_t);
int	 strncmp(const char *, const char *, bsd_size_t);
char	*strncpy(char * __restrict, const char * __restrict, bsd_size_t);
bsd_size_t	 strnlen(const char *, bsd_size_t);
char	*strsep(char **, const char *delim);
bsd_size_t	 strspn(const char *, const char *);
char	*strstr(const char *, const char *);
int	 strvalid(const char *, bsd_size_t);
#endif // -------

extern bsd_uint32_t crc32_tab[];

static __inline bsd_uint32_t
crc32_raw(const void *buf, bsd_size_t size, bsd_uint32_t crc)
{
	const bsd_uint8_t *p = (const bsd_uint8_t *)buf;

	while (size--)
		crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
	return (crc);
}

static __inline bsd_uint32_t
crc32(const void *buf, bsd_size_t size)
{
	bsd_uint32_t crc;

	crc = crc32_raw(buf, size, ~0U);
	return (crc ^ ~0U);
}

bsd_uint32_t
calculate_crc32c(bsd_uint32_t crc32c, const unsigned char *buffer, 
        unsigned int length);


#if 0 // runsisi AT hust.edu.cn @2013/10/18
LIBKERN_INLINE void *memset(void *, int, bsd_size_t);
#ifdef LIBKERN_BODY
LIBKERN_INLINE void *
memset(void *b, int c, bsd_size_t len)
{
    char *bb;

    if (c == 0)
        bzero(b, len);
    else
        for (bb = (char *)b; len--; )
            *bb++ = c;
    return (b);
}
#endif

static __inline char *
strchr(const char *p, int ch)
{
    return (index(p, ch));
}

static __inline char *
strrchr(const char *p, int ch)
{
    return (rindex(p, ch));
}
#endif // -------

/* fnmatch() return values. */
#define	FNM_NOMATCH	1	/* Match failed. */

/* fnmatch() flags. */
#define	FNM_NOESCAPE	0x01	/* Disable backslash escaping. */
#define	FNM_PATHNAME	0x02	/* Slash must be matched by slash. */
#define	FNM_PERIOD	0x04	/* Period must be matched by period. */
#define	FNM_LEADING_DIR	0x08	/* Ignore /<tail> after Imatch. */
#define	FNM_CASEFOLD	0x10	/* Case insensitive search. */
#define	FNM_IGNORECASE	FNM_CASEFOLD
#define	FNM_FILE_NAME	FNM_PATHNAME

#endif /* !_SYS_LIBKERN_H_ */
