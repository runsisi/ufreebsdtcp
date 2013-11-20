/*-
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)time.h	8.5 (Berkeley) 5/4/95
 * $FreeBSD: release/9.2.0/sys/sys/time.h 247555 2013-03-01 17:10:43Z jhb $
 */

#ifndef _BSD_SYS_TIME_H_
#define _BSD_SYS_TIME_H_

#include <sys/_bsd_timeval.h>
#include <sys/bsd_types.h>
#include <sys/bsd_timespec.h>

struct bsd_timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};
#define	DST_NONE	0	/* not on dst */
#define	DST_USA		1	/* USA style dst */
#define	DST_AUST	2	/* Australian style dst */
#define	DST_WET		3	/* Western European dst */
#define	DST_MET		4	/* Middle European dst */
#define	DST_EET		5	/* Eastern European dst */
#define	DST_CAN		6	/* Canada */

#if __BSD_VISIBLE
struct bsd_bintime {
	bsd_time_t	sec;
	bsd_uint64_t frac;
};

static __inline void
bintime_addx(struct bsd_bintime *bt, bsd_uint64_t x)
{
	bsd_uint64_t u;

	u = bt->frac;
	bt->frac += x;
	if (u > bt->frac)
		bt->sec++;
}

static __inline void
bintime_add(struct bsd_bintime *bt, const struct bsd_bintime *bt2)
{
	bsd_uint64_t u;

	u = bt->frac;
	bt->frac += bt2->frac;
	if (u > bt->frac)
		bt->sec++;
	bt->sec += bt2->sec;
}

static __inline void
bintime_sub(struct bsd_bintime *bt, const struct bsd_bintime *bt2)
{
	bsd_uint64_t u;

	u = bt->frac;
	bt->frac -= bt2->frac;
	if (u < bt->frac)
		bt->sec--;
	bt->sec -= bt2->sec;
}

static __inline void
bintime_mul(struct bsd_bintime *bt, u_int x)
{
	bsd_uint64_t p1, p2;

	p1 = (bt->frac & 0xffffffffull) * x;
	p2 = (bt->frac >> 32) * x + (p1 >> 32);
	bt->sec *= x;
	bt->sec += (p2 >> 32);
	bt->frac = (p2 << 32) | (p1 & 0xffffffffull);
}

#define	bintime_clear(a)	((a)->sec = (a)->frac = 0)
#define	bintime_isset(a)	((a)->sec || (a)->frac)
#define	bintime_cmp(a, b, cmp)						\
	(((a)->sec == (b)->sec) ?					\
	    ((a)->frac cmp (b)->frac) :					\
	    ((a)->sec cmp (b)->sec))

/*-
 * Background information:
 *
 * When converting between timestamps on parallel timescales of differing
 * resolutions it is historical and scientific practice to round down rather
 * than doing 4/5 rounding.
 *
 *   The date changes at midnight, not at noon.
 *
 *   Even at 15:59:59.999999999 it's not four'o'clock.
 *
 *   time_second ticks after N.999999999 not after N.4999999999
 */

static __inline void
bintime2timespec(const struct bsd_bintime *bt, struct bsd_timespec *ts)
{

	ts->tv_sec = bt->sec;
	ts->tv_nsec = ((bsd_uint64_t)1000000000 * (bsd_uint32_t)(bt->frac >> 32)) >> 32;
}

static __inline void
timespec2bintime(const struct bsd_timespec *ts, struct bsd_bintime *bt)
{

	bt->sec = ts->tv_sec;
	/* 18446744073 = int(2^64 / 1000000000) */
	bt->frac = ts->tv_nsec * (bsd_uint64_t)18446744073LL; 
}

static __inline void
bintime2timeval(const struct bsd_bintime *bt, struct bsd_timeval *tv)
{

	tv->tv_sec = bt->sec;
	tv->tv_usec = ((bsd_uint64_t)1000000 * (bsd_uint32_t)(bt->frac >> 32)) >> 32;
}

static __inline void
timeval2bintime(const struct bsd_timeval *tv, struct bsd_bintime *bt)
{

	bt->sec = tv->tv_sec;
	/* 18446744073709 = int(2^64 / 1000000) */
	bt->frac = tv->tv_usec * (bsd_uint64_t)18446744073709LL;
}
#endif /* __BSD_VISIBLE */

#ifdef _KERNEL

/* Operations on timespecs */
#define	timespecclear(tvp)	((tvp)->tv_sec = (tvp)->tv_nsec = 0)
#define	timespecisset(tvp)	((tvp)->tv_sec || (tvp)->tv_nsec)
#define	timespeccmp(tvp, uvp, cmp)					\
	(((tvp)->tv_sec == (uvp)->tv_sec) ?				\
	    ((tvp)->tv_nsec cmp (uvp)->tv_nsec) :			\
	    ((tvp)->tv_sec cmp (uvp)->tv_sec))
#define timespecadd(vvp, uvp)						\
	do {								\
		(vvp)->tv_sec += (uvp)->tv_sec;				\
		(vvp)->tv_nsec += (uvp)->tv_nsec;			\
		if ((vvp)->tv_nsec >= 1000000000) {			\
			(vvp)->tv_sec++;				\
			(vvp)->tv_nsec -= 1000000000;			\
		}							\
	} while (0)
#define timespecsub(vvp, uvp)						\
	do {								\
		(vvp)->tv_sec -= (uvp)->tv_sec;				\
		(vvp)->tv_nsec -= (uvp)->tv_nsec;			\
		if ((vvp)->tv_nsec < 0) {				\
			(vvp)->tv_sec--;				\
			(vvp)->tv_nsec += 1000000000;			\
		}							\
	} while (0)

/* Operations on timevals. */

#define	timevalclear(tvp)		((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define	timevalisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timevalcmp(tvp, uvp, cmp)					\
	(((tvp)->tv_sec == (uvp)->tv_sec) ?				\
	    ((tvp)->tv_usec cmp (uvp)->tv_usec) :			\
	    ((tvp)->tv_sec cmp (uvp)->tv_sec))

/* timevaladd and timevalsub are not inlined */

#endif /* _KERNEL */

#ifndef _KERNEL			/* NetBSD/OpenBSD compatible interfaces */

#define	timerclear(tvp)		((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp, uvp, cmp)					\
	(((tvp)->tv_sec == (uvp)->tv_sec) ?				\
	    ((tvp)->tv_usec cmp (uvp)->tv_usec) :			\
	    ((tvp)->tv_sec cmp (uvp)->tv_sec))
#define timeradd(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;	\
		if ((vvp)->tv_usec >= 1000000) {			\
			(vvp)->tv_sec++;				\
			(vvp)->tv_usec -= 1000000;			\
		}							\
	} while (0)
#define timersub(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;	\
		if ((vvp)->tv_usec < 0) {				\
			(vvp)->tv_sec--;				\
			(vvp)->tv_usec += 1000000;			\
		}							\
	} while (0)
#endif

/*
 * Names of the interval timers, and structure
 * defining a timer setting.
 */
#define	BSD_ITIMER_REAL	0
#define	BSD_ITIMER_VIRTUAL	1
#define	BSD_ITIMER_PROF	2

struct bsd_itimerval {
	struct	bsd_timeval it_interval;	/* timer interval */
	struct	bsd_timeval it_value;	/* current value */
};

/*
 * Getkerninfo clock information structure
 */
struct bsd_clockinfo {
	int	hz;		/* clock frequency */
	int	tick;		/* micro-seconds per hz tick */
	int	spare;
	int	stathz;		/* statistics clock frequency */
	int	profhz;		/* profiling clock frequency */
};

/* These macros are also in time.h. */
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME	0
#define CLOCK_VIRTUAL	1
#define CLOCK_PROF	2
#define CLOCK_MONOTONIC	4
#define CLOCK_UPTIME	5		/* FreeBSD-specific. */
#define CLOCK_UPTIME_PRECISE	7	/* FreeBSD-specific. */
#define CLOCK_UPTIME_FAST	8	/* FreeBSD-specific. */
#define CLOCK_REALTIME_PRECISE	9	/* FreeBSD-specific. */
#define CLOCK_REALTIME_FAST	10	/* FreeBSD-specific. */
#define CLOCK_MONOTONIC_PRECISE	11	/* FreeBSD-specific. */
#define CLOCK_MONOTONIC_FAST	12	/* FreeBSD-specific. */
#define CLOCK_SECOND	13		/* FreeBSD-specific. */
#define CLOCK_THREAD_CPUTIME_ID	14
#endif

#ifndef TIMER_ABSTIME
#define TIMER_RELTIME	0x0	/* relative timer */
#define TIMER_ABSTIME	0x1	/* absolute timer */
#endif

#ifdef _KERNEL

/*
 * Kernel to clock driver interface.
 */
void	inittodr(bsd_time_t base);
void	resettodr(void);

extern volatile bsd_time_t	time_second;
#if 0	// runsisi AT hust.edu.cn @2013/11/20
extern volatile bsd_time_t	time_uptime;
#endif 	// ---------------------- @2013/11/20
extern struct bsd_bintime boottimebin;
extern struct bsd_timeval boottime;

/*
 * Functions for looking at our clock: [get]{bin,nano,micro}[up]time()
 *
 * Functions without the "get" prefix returns the best timestamp
 * we can produce in the given format.
 *
 * "bin"   == struct bintime  == seconds + 64 bit fraction of seconds.
 * "nano"  == struct timespec == seconds + nanoseconds.
 * "micro" == struct timeval  == seconds + microseconds.
 *              
 * Functions containing "up" returns time relative to boot and
 * should be used for calculating time intervals.
 *
 * Functions without "up" returns GMT time.
 *
 * Functions with the "get" prefix returns a less precise result
 * much faster than the functions without "get" prefix and should
 * be used where a precision of 1/hz seconds is acceptable or where
 * performance is priority. (NB: "precision", _not_ "resolution" !) 
 * 
 */

void	binuptime(struct bsd_bintime *bt);
void	nanouptime(struct bsd_timespec *tsp);
void	microuptime(struct bsd_timeval *tvp);

void	bintime(struct bsd_bintime *bt);
void	nanotime(struct bsd_timespec *tsp);
void	microtime(struct bsd_timeval *tvp);

void	getbinuptime(struct bsd_bintime *bt);
void	getnanouptime(struct bsd_timespec *tsp);
void	getmicrouptime(struct bsd_timeval *tvp);

void	getbintime(struct bsd_bintime *bt);
void	getnanotime(struct bsd_timespec *tsp);
void	getmicrotime(struct bsd_timeval *tvp);

/* Other functions */
int	itimerdecr(struct bsd_itimerval *itp, int usec);
int	itimerfix(struct bsd_timeval *tv);
int	ppsratecheck(struct bsd_timeval *, int *, int);
int	ratecheck(struct bsd_timeval *, const struct bsd_timeval *);
void	timevaladd(struct bsd_timeval *t1, const struct bsd_timeval *t2);
void	timevalsub(struct bsd_timeval *t1, const struct bsd_timeval *t2);
int	tvtohz(struct bsd_timeval *tv);
#else /* !_KERNEL */
#include <time.h>

#include <sys/bsd_cdefs.h>
#include <sys/bsd_select.h>

__BEGIN_DECLS
int	setitimer(int, const struct bsd_itimerval *, struct bsd_itimerval *);
int	utimes(const char *, const struct bsd_timeval *);

#if __BSD_VISIBLE
int	adjtime(const struct bsd_timeval *, struct bsd_timeval *);
int	futimes(int, const struct bsd_timeval *);
int	futimesat(int, const char *, const struct bsd_timeval [2]);
int	lutimes(const char *, const struct bsd_timeval *);
int	settimeofday(const struct bsd_timeval *, const struct bsd_timezone *);
#endif

#if __XSI_VISIBLE
int	getitimer(int, struct bsd_itimerval *);
int	gettimeofday(struct bsd_timeval *, struct bsd_timezone *);
#endif

__END_DECLS

#endif /* !_KERNEL */

#endif /* !_SYS_TIME_H_ */
