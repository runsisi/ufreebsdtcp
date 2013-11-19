/*-
 * Copyright (c) 1982, 1986, 1991, 1993
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
 *	From: @(#)kern_clock.c	8.5 (Berkeley) 1/21/94
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_timeout.c 249132 2013-04-05 08:22:11Z mav $");

#include "opt_kdtrace.h"

#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_callout.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_ktr.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_mutex.h>

static int avg_depth;
static int avg_gcalls;
static int avg_lockcalls;
static int avg_mpcalls;

/*
 * TODO:
 *	allocate more timeout table slots when table overflows.
 */
int callwheelsize, callwheelbits, callwheelmask;


/*
 * There is one struct callout_cpu per cpu, holding all relevant
 * state for the callout processing thread on the individual CPU.
 * In particular:
 *	cc_ticks is incremented once per tick in callout_cpu().
 *	It tracks the global 'ticks' but in a way that the individual
 *	threads should not worry about races in the order in which
 *	hardclock() and hardclock_cpu() run on the various CPUs.
 *	cc_softclock is advanced in callout_cpu() to point to the
 *	first entry in cc_callwheel that may need handling. In turn,
 *	a softclock() is scheduled so it can serve the various entries i
 *	such that cc_softclock <= i <= cc_ticks .
 *	XXX maybe cc_softclock and cc_ticks should be volatile ?
 *
 *	cc_ticks is also used in callout_reset_cpu() to determine
 *	when the callout should be served.
 */
struct callout_cpu {
	struct mtx		cc_lock;
	struct callout		*cc_callout;
	struct callout_tailq	*cc_callwheel;
	struct callout_list	cc_callfree;
	struct callout		*cc_next;
	struct callout		*cc_curr;
	void			*cc_cookie;
	int 			cc_ticks;
	int 			cc_softticks;
	int			cc_cancel;
	int			cc_waiting;
	int 			cc_firsttick;
};

struct callout_cpu cc_cpu;
#define	CC_CPU(cpu)	&cc_cpu
#define	CC_SELF()	&cc_cpu

#define	CC_LOCK(cc)	mtx_lock_spin(&(cc)->cc_lock)
#define	CC_UNLOCK(cc)	mtx_unlock_spin(&(cc)->cc_lock)
#define	CC_LOCK_ASSERT(cc)	mtx_assert(&(cc)->cc_lock, MA_OWNED)

static int timeout_cpu;
void (*callout_new_inserted)(int cpu, int ticks) = NULL;

static void softclock(void *arg);

/**
 * Locked by cc_lock:
 *   cc_curr         - If a callout is in progress, it is curr_callout.
 *                     If curr_callout is non-NULL, threads waiting in
 *                     callout_drain() will be woken up as soon as the
 *                     relevant callout completes.
 *   cc_cancel       - Changing to 1 with both callout_lock and c_lock held
 *                     guarantees that the current callout will not run.
 *                     The softclock() function sets this to 0 before it
 *                     drops callout_lock to acquire c_lock, and it calls
 *                     the handler only if curr_cancelled is still 0 after
 *                     c_lock is successfully acquired.
 *   cc_waiting      - If a thread is waiting in callout_drain(), then
 *                     callout_wait is nonzero.  Set only when
 *                     curr_callout is non-NULL.
 */

/*
 * kern_timeout_callwheel_alloc() - kernel low level callwheel initialization 
 *
 *	This code is called very early in the kernel initialization sequence,
 *	and may be called more then once.
 */
caddr_t
kern_timeout_callwheel_alloc(caddr_t v)
{
	struct callout_cpu *cc;

	timeout_cpu = 0;
	cc = CC_CPU(timeout_cpu);
	/*
	 * Calculate callout wheel size
	 */
	for (callwheelsize = 1, callwheelbits = 0;
	     callwheelsize < ncallout;
	     callwheelsize <<= 1, ++callwheelbits)
		;
	callwheelmask = callwheelsize - 1;

	cc->cc_callwheel = (struct callout_tailq *)v;
	v = (caddr_t)(cc->cc_callwheel + callwheelsize);
	return(v);
}

static void
callout_cpu_init(struct callout_cpu *cc)
{
	int i;

//	mtx_init(&cc->cc_lock, "callout", NULL, MTX_SPIN | MTX_RECURSE);
	BSD_SLIST_INIT(&cc->cc_callfree);
	for (i = 0; i < callwheelsize; i++) {
	    BSD_TAILQ_INIT(&cc->cc_callwheel[i]);
	}
}

/*
 * kern_timeout_callwheel_init() - initialize previously reserved callwheel
 *				   space.
 *
 *	This code is called just once, after the space reserved for the
 *	callout wheel has been finalized.
 */
void
kern_timeout_callwheel_init(void)
{
	callout_cpu_init(CC_CPU(timeout_cpu));
}

void
callout_tick(void)
{
	struct callout_cpu *cc;
	int need_softclock;
	int bucket;

	/*
	 * Process callouts at a very low cpu priority, so we don't keep the
	 * relatively high clock interrupt priority any longer than necessary.
	 */
	need_softclock = 0;
	cc = CC_SELF();
	mtx_lock_spin_flags(&cc->cc_lock, MTX_QUIET);
	cc->cc_firsttick = cc->cc_ticks = ticks;
	for (; (cc->cc_softticks - cc->cc_ticks) <= 0; cc->cc_softticks++) {
		bucket = cc->cc_softticks & callwheelmask;
		if (!BSD_TAILQ_EMPTY(&cc->cc_callwheel[bucket])) {
			need_softclock = 1;
			break;
		}
	}
	mtx_unlock_spin_flags(&cc->cc_lock, MTX_QUIET);
	/*
	 * swi_sched acquires the thread lock, so we don't want to call it
	 * with cc_lock held; incorrect locking order.
	 */
    if (need_softclock)
        softclock(cc);
}

static struct callout_cpu *
callout_lock(struct callout *c)
{
	struct callout_cpu *cc;
	int cpu;

	for (;;) {
		cpu = c->c_cpu;
		cc = CC_CPU(cpu);
		CC_LOCK(cc);
		if (cpu == c->c_cpu)
			break;
		CC_UNLOCK(cc);
	}
	return (cc);
}

static void
callout_cc_add(struct callout *c, struct callout_cpu *cc, int to_ticks,
    void (*func)(void *), void *arg, int cpu)
{

	CC_LOCK_ASSERT(cc);

	if (to_ticks <= 0)
		to_ticks = 1;
	c->c_arg = arg;
	c->c_flags |= (CALLOUT_ACTIVE | CALLOUT_PENDING);
	c->c_func = func;
	c->c_time = ticks + to_ticks;
	BSD_TAILQ_INSERT_TAIL(&cc->cc_callwheel[c->c_time & callwheelmask],
	    c, c_links.tqe);
	if ((c->c_time - cc->cc_firsttick) < 0 &&
	    callout_new_inserted != NULL) {
		cc->cc_firsttick = c->c_time;
		(*callout_new_inserted)(cpu,
		    to_ticks + (ticks - cc->cc_ticks));
	}
}

static void
callout_cc_del(struct callout *c, struct callout_cpu *cc)
{

	if ((c->c_flags & CALLOUT_LOCAL_ALLOC) == 0)
		return;
	c->c_func = NULL;
	BSD_SLIST_INSERT_HEAD(&cc->cc_callfree, c, c_links.sle);
}

static void
softclock_call_cc(struct callout *c, struct callout_cpu *cc, int *mpcalls,
    int *lockcalls, int *gcalls)
{
	void (*c_func)(void *);
	void *c_arg;
	int c_flags;
#ifdef DIAGNOSTIC
	struct bintime bt1, bt2;
	struct timespec ts2;
	static uint64_t maxdt = 36893488147419102LL;	/* 2 msec */
	static timeout_t *lastfunc;
#endif

	KASSERT((c->c_flags & (CALLOUT_PENDING | CALLOUT_ACTIVE)) ==
	    (CALLOUT_PENDING | CALLOUT_ACTIVE),
	    ("softclock_call_cc: pend|act %p %x", c, c->c_flags));
	c_func = c->c_func;
	c_arg = c->c_arg;
	c_flags = c->c_flags;
	if (c->c_flags & CALLOUT_LOCAL_ALLOC)
		c->c_flags = CALLOUT_LOCAL_ALLOC;
	else
		c->c_flags &= ~CALLOUT_PENDING;
	cc->cc_curr = c;
	cc->cc_cancel = 0;
	CC_UNLOCK(cc);
	{
		(*mpcalls)++;
		CTR3(KTR_CALLOUT, "callout mpsafe %p func %p arg %p",
		    c, c_func, c_arg);
	}
#ifdef DIAGNOSTIC
	binuptime(&bt1);
#endif
	c_func(c_arg);
#ifdef DIAGNOSTIC
	binuptime(&bt2);
	bintime_sub(&bt2, &bt1);
	if (bt2.frac > maxdt) {
		if (lastfunc != c_func || bt2.frac > maxdt * 2) {
			bintime2timespec(&bt2, &ts2);
			printf(
		"Expensive timeout(9) function: %p(%p) %jd.%09ld s\n",
			    c_func, c_arg, (intmax_t)ts2.tv_sec, ts2.tv_nsec);
		}
		maxdt = bt2.frac;
		lastfunc = c_func;
	}
#endif
	CTR1(KTR_CALLOUT, "callout %p finished", c);

	CC_LOCK(cc);
	KASSERT(cc->cc_curr == c, ("mishandled cc_curr"));
	cc->cc_curr = NULL;

	/*
	 * If the current callout is locally allocated (from
	 * timeout(9)) then put it on the freelist.
	 *
	 * Note: we need to check the cached copy of c_flags because
	 * if it was not local, then it's not safe to deref the
	 * callout pointer.
	 */
	KASSERT((c_flags & CALLOUT_LOCAL_ALLOC) == 0 ||
	    c->c_flags == CALLOUT_LOCAL_ALLOC,
	    ("corrupted callout"));
	if (c_flags & CALLOUT_LOCAL_ALLOC)
		callout_cc_del(c, cc);
}

/*
 * The callout mechanism is based on the work of Adam M. Costello and 
 * George Varghese, published in a technical report entitled "Redesigning
 * the BSD Callout and Timer Facilities" and modified slightly for inclusion
 * in FreeBSD by Justin T. Gibbs.  The original work on the data structures
 * used in this implementation was published by G. Varghese and T. Lauck in
 * the paper "Hashed and Hierarchical Timing Wheels: Data Structures for
 * the Efficient Implementation of a Timer Facility" in the Proceedings of
 * the 11th ACM Annual Symposium on Operating Systems Principles,
 * Austin, Texas Nov 1987.
 */

/*
 * Software (low priority) clock interrupt.
 * Run periodic events from timeout queue.
 */
static void
softclock(void *arg)
{
	struct callout_cpu *cc;
	struct callout *c;
	struct callout_tailq *bucket;
	int curticks;
	int steps;	/* #steps since we last allowed interrupts */
	int depth;
	int mpcalls;
	int lockcalls;
	int gcalls;

#ifndef MAX_SOFTCLOCK_STEPS
#define MAX_SOFTCLOCK_STEPS 100 /* Maximum allowed value of steps. */
#endif /* MAX_SOFTCLOCK_STEPS */

	mpcalls = 0;
	lockcalls = 0;
	gcalls = 0;
	depth = 0;
	steps = 0;
	cc = (struct callout_cpu *)arg;
	CC_LOCK(cc);
	while (cc->cc_softticks - 1 != cc->cc_ticks) {
		/*
		 * cc_softticks may be modified by hard clock, so cache
		 * it while we work on a given bucket.
		 */
		curticks = cc->cc_softticks;
		cc->cc_softticks++;
		bucket = &cc->cc_callwheel[curticks & callwheelmask];
		c = BSD_TAILQ_FIRST(bucket);
		while (c != NULL) {
			depth++;
			if (c->c_time != curticks) {
				c = BSD_TAILQ_NEXT(c, c_links.tqe);
				++steps;
				if (steps >= MAX_SOFTCLOCK_STEPS) {
					cc->cc_next = c;
					/* Give interrupts a chance. */
					CC_UNLOCK(cc);
					;	/* nothing */
					CC_LOCK(cc);
					c = cc->cc_next;
					steps = 0;
				}
			} else {
				cc->cc_next = BSD_TAILQ_NEXT(c, c_links.tqe);
				BSD_TAILQ_REMOVE(bucket, c, c_links.tqe);
				softclock_call_cc(c, cc, &mpcalls,
				    &lockcalls, &gcalls);
				steps = 0;
				c = cc->cc_next;
			}
		}
	}
	avg_depth += (depth * 1000 - avg_depth) >> 8;
	avg_mpcalls += (mpcalls * 1000 - avg_mpcalls) >> 8;
	avg_lockcalls += (lockcalls * 1000 - avg_lockcalls) >> 8;
	avg_gcalls += (gcalls * 1000 - avg_gcalls) >> 8;
	cc->cc_next = NULL;
	CC_UNLOCK(cc);
}

/*
 * New interface; clients allocate their own callout structures.
 *
 * callout_reset() - establish or change a timeout
 * callout_stop() - disestablish a timeout
 * callout_init() - initialize a callout structure so that it can
 *	safely be passed to callout_reset() and callout_stop()
 *
 * <sys/callout.h> defines three convenience macros:
 *
 * callout_active() - returns truth if callout has not been stopped,
 *	drained, or deactivated since the last time the callout was
 *	reset.
 * callout_pending() - returns truth if callout is still waiting for timeout
 * callout_deactivate() - marks the callout as having been serviced
 */
int
callout_reset_on(struct callout *c, int to_ticks, void (*ftn)(void *),
    void *arg, int cpu)
{
	struct callout_cpu *cc;
	int cancelled = 0;

	/*
	 * Don't allow migration of pre-allocated callouts lest they
	 * become unbalanced.
	 */
	if (c->c_flags & CALLOUT_LOCAL_ALLOC)
		cpu = c->c_cpu;
	cc = callout_lock(c);
	if (cc->cc_curr == c) {
		/*
		 * We're being asked to reschedule a callout which is
		 * currently in progress.  If there is a lock then we
		 * can cancel the callout if it has not really started.
		 */
		if (c->c_lock != NULL && !cc->cc_cancel)
			cancelled = cc->cc_cancel = 1;
	}
	if (c->c_flags & CALLOUT_PENDING) {
		if (cc->cc_next == c) {
			cc->cc_next = BSD_TAILQ_NEXT(c, c_links.tqe);
		}
		BSD_TAILQ_REMOVE(&cc->cc_callwheel[c->c_time & callwheelmask], c,
		    c_links.tqe);

		cancelled = 1;
		c->c_flags &= ~(CALLOUT_ACTIVE | CALLOUT_PENDING);
	}

	callout_cc_add(c, cc, to_ticks, ftn, arg, cpu);
	CTR5(KTR_CALLOUT, "%sscheduled %p func %p arg %p in %d",
	    cancelled ? "re" : "", c, c->c_func, c->c_arg, to_ticks);
	CC_UNLOCK(cc);

	return (cancelled);
}

/*
 * Common idioms that can be optimized in the future.
 */
int
callout_schedule_on(struct callout *c, int to_ticks, int cpu)
{
	return callout_reset_on(c, to_ticks, c->c_func, c->c_arg, cpu);
}

int
callout_schedule(struct callout *c, int to_ticks)
{
	return callout_reset_on(c, to_ticks, c->c_func, c->c_arg, c->c_cpu);
}

int
_callout_stop_safe(c, safe)
	struct	callout *c;
	int	safe;
{
	struct callout_cpu *cc;

	cc = callout_lock(c);

	/*
	 * If the callout isn't pending, it's not on the queue, so
	 * don't attempt to remove it from the queue.  We can try to
	 * stop it by other means however.
	 */
	if (!(c->c_flags & CALLOUT_PENDING)) {
		c->c_flags &= ~CALLOUT_ACTIVE;

		return (0);
	}

	c->c_flags &= ~(CALLOUT_ACTIVE | CALLOUT_PENDING);

	CTR3(KTR_CALLOUT, "cancelled %p func %p arg %p",
	    c, c->c_func, c->c_arg);
	if (cc->cc_next == c)
		cc->cc_next = BSD_TAILQ_NEXT(c, c_links.tqe);
	BSD_TAILQ_REMOVE(&cc->cc_callwheel[c->c_time & callwheelmask], c,
	    c_links.tqe);
	callout_cc_del(c, cc);

	CC_UNLOCK(cc);
	return (1);
}

void
callout_init(c, mpsafe)
	struct	callout *c;
	int mpsafe;
{
	bzero(c, sizeof *c);

    c->c_lock = NULL;
    c->c_flags = CALLOUT_RETURNUNLOCKED;
	c->c_cpu = timeout_cpu;
}

void
_callout_init_lock(c, lock, flags)
	struct	callout *c;
	struct	lock_object *lock;
	int flags;
{
	bzero(c, sizeof *c);
	c->c_lock = lock;
	KASSERT((flags & ~(CALLOUT_RETURNUNLOCKED | CALLOUT_SHAREDLOCK)) == 0,
	    ("callout_init_lock: bad flags %d", flags));
	KASSERT(lock != NULL || (flags & CALLOUT_RETURNUNLOCKED) == 0,
	    ("callout_init_lock: CALLOUT_RETURNUNLOCKED with no lock"));
	KASSERT(lock == NULL || !(LOCK_CLASS(lock)->lc_flags &
	    (LC_SPINLOCK | LC_SLEEPABLE)), ("%s: invalid lock class",
	    __func__));
	c->c_flags = flags & (CALLOUT_RETURNUNLOCKED | CALLOUT_SHAREDLOCK);
	c->c_cpu = timeout_cpu;
}


// runsisi AT hust.edu.cn @2013/11/01
extern void hardclock(int usermode, bsd_uintfptr_t pc);
extern void tcp_hc_callout_init(void);
/*
 * out callout system is driven by this timer
 */
static DPS_Timer dps_drive_timer;
static void
clock_drive(DPS_Timer *timer, void *arg)
{
    hardclock(0, 0);
}

int
bsd_callout_init()
{
    void *firstaddr;
    caddr_t v;
    bsd_vm_size_t size = 0;
    SWORD32 ret = 0;

    firstaddr = 0;
again:
    v = (caddr_t)firstaddr;

    v = kern_timeout_callwheel_alloc(v);

    if (firstaddr == 0) {
        size = (bsd_vm_size_t)v;
        firstaddr = DPS_Malloc("brs callout", (WORD32)size);
        if (firstaddr == 0)
        {
            bsd_log(BSD_LOG_ERROR, "startup: no room for tables");
            return BSD_ENOMEM;
        }
        goto again;
    }

    kern_timeout_callwheel_init();

    /* hz = 100, reference to subr_param.c */
    ret = DPS_ResetAoTimer(&dps_drive_timer, PERIODICAL, 10,
            (DPS_TIMER_CBK)clock_drive, (void*)0,
            (DPS_GetAoByID(DPS_GetSelfAoID()))->dwLcoreId);

    tcp_hc_callout_init();

    return 0;
}
// ---------------------- @2013/11/01
