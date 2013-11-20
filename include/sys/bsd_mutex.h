/*-
 * Copyright (c) 1997 Berkeley Software Design, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Berkeley Software Design Inc's name may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BERKELEY SOFTWARE DESIGN INC ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL BERKELEY SOFTWARE DESIGN INC BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from BSDI $Id: mutex.h,v 2.7.2.35 2000/04/27 03:10:26 cp Exp $
 * $FreeBSD: release/9.2.0/sys/sys/mutex.h 235404 2012-05-13 17:01:32Z avg $
 */

#ifndef _SYS_MUTEX_H_
#define _SYS_MUTEX_H_

#include <sys/bsd_queue.h>
#include <sys/_bsd_lock.h>
#include <sys/_bsd_mutex.h>

#ifdef _KERNEL
#include <sys/bsd_pcpu.h>
#include <sys/bsd_lock_profile.h>
#include <sys/bsd_lockstat.h>
#include <machine/bsd_atomic.h>
#include <machine/bsd_cpufunc.h>

/*
 * Mutex types and options passed to mtx_init().  MTX_QUIET and MTX_DUPOK
 * can also be passed in.
 */
#define	MTX_DEF		0x00000000	/* DEFAULT (sleep) lock */ 
#define MTX_SPIN	0x00000001	/* Spin lock (disables interrupts) */
#define MTX_RECURSE	0x00000004	/* Option: lock allowed to recurse */
#define	MTX_NOWITNESS	0x00000008	/* Don't do any witness checking. */
#define MTX_NOPROFILE   0x00000020	/* Don't profile this lock */

/*
 * Option flags passed to certain lock/unlock routines, through the use
 * of corresponding mtx_{lock,unlock}_flags() interface macros.
 */
#define	MTX_QUIET	LOP_QUIET	/* Don't log a mutex event */
#define	MTX_DUPOK	LOP_DUPOK	/* Don't log a duplicate acquire */

/*
 * State bits kept in mutex->mtx_lock, for the DEFAULT lock type. None of this,
 * with the exception of MTX_UNOWNED, applies to spin locks.
 */
#define	MTX_RECURSED	0x00000001	/* lock recursed (for MTX_DEF only) */
#define	MTX_CONTESTED	0x00000002	/* lock contested (for MTX_DEF only) */
#define MTX_UNOWNED	0x00000004	/* Cookie for free mutex */
#define	MTX_FLAGMASK	(MTX_RECURSED | MTX_CONTESTED | MTX_UNOWNED)

/*
 * Value stored in mutex->mtx_lock to denote a destroyed mutex.
 */
#define	MTX_DESTROYED	(MTX_CONTESTED | MTX_UNOWNED)

#define	mtx_trylock_flags_(m, opts, file, line)

#define	thread_lock_flags_(tdp, opts, file, line)
#define	thread_lock(tdp)
#define	thread_lock_flags(tdp, opt)
#define	thread_unlock(tdp)

#define	mtx_recurse	lock_object.lo_data

/* Very simple operations on mtx_lock. */

/* Try to obtain mtx_lock once. */
#define _mtx_obtain_lock(mp, tid)

/* Try to release mtx_lock if it is unrecursed and uncontested. */
#define _mtx_release_lock(mp, tid)

/* Release mtx_lock quickly, assuming we own it. */
#define _mtx_release_lock_quick(mp)

/*
 * Full lock operations that are suitable to be inlined in non-debug
 * kernels.  If the lock cannot be acquired or released trivially then
 * the work is deferred to another function.
 */

/* Lock a normal mutex. */
#define __mtx_lock(mp, tid, opts, file, line)

/*
 * Lock a spin mutex.  For spinlocks, we handle recursion inline (it
 * turns out that function calls can be significantly expensive on
 * some architectures).  Since spin locks are not _too_ common,
 * inlining this code is not too big a deal.
 */
#define __mtx_lock_spin(mp, tid, opts, file, line)

/* Unlock a normal mutex. */
#define __mtx_unlock(mp, tid, opts, file, line)

/*
 * Unlock a spin mutex.  For spinlocks, we can handle everything
 * inline, as it's pretty simple and a function call would be too
 * expensive (at least on some architectures).  Since spin locks are
 * not _too_ common, inlining this code is not too big a deal.
 *
 * Since we always perform a spinlock_enter() when attempting to acquire a
 * spin lock, we need to always perform a matching spinlock_exit() when
 * releasing a spin lock.  This includes the recursion cases.
 */

#define __mtx_unlock_spin(mp)

/*
 * Exported lock manipulation interface.
 *
 * mtx_lock(m) locks MTX_DEF mutex `m'
 *
 * mtx_lock_spin(m) locks MTX_SPIN mutex `m'
 *
 * mtx_unlock(m) unlocks MTX_DEF mutex `m'
 *
 * mtx_unlock_spin(m) unlocks MTX_SPIN mutex `m'
 *
 * mtx_lock_spin_flags(m, opts) and mtx_lock_flags(m, opts) locks mutex `m'
 *     and passes option flags `opts' to the "hard" function, if required.
 *     With these routines, it is possible to pass flags such as MTX_QUIET
 *     to the appropriate lock manipulation routines.
 *
 * mtx_trylock(m) attempts to acquire MTX_DEF mutex `m' but doesn't sleep if
 *     it cannot. Rather, it returns 0 on failure and non-zero on success.
 *     It does NOT handle recursion as we assume that if a caller is properly
 *     using this part of the interface, he will know that the lock in question
 *     is _not_ recursed.
 *
 * mtx_trylock_flags(m, opts) is used the same way as mtx_trylock() but accepts
 *     relevant option flags `opts.'
 *
 * mtx_initialized(m) returns non-zero if the lock `m' has been initialized.
 *
 * mtx_owned(m) returns non-zero if the current thread owns the lock `m'
 *
 * mtx_recursed(m) returns non-zero if the lock `m' is presently recursed.
 */ 
#define mtx_lock(m)
#define mtx_lock_spin(m)
#define mtx_trylock(m)
#define mtx_unlock(m)
#define mtx_unlock_spin(m)

struct mtx_pool;

struct mtx_pool *mtx_pool_create(const char *mtx_name, int pool_size, int opts);
void mtx_pool_destroy(struct mtx_pool **poolp);
struct mtx *mtx_pool_find(struct mtx_pool *pool, void *ptr);
struct mtx *mtx_pool_alloc(struct mtx_pool *pool);
#define mtx_pool_lock(pool, ptr)					\
	mtx_lock(mtx_pool_find((pool), (ptr)))
#define mtx_pool_lock_spin(pool, ptr)					\
	mtx_lock_spin(mtx_pool_find((pool), (ptr)))
#define mtx_pool_unlock(pool, ptr)					\
	mtx_unlock(mtx_pool_find((pool), (ptr)))
#define mtx_pool_unlock_spin(pool, ptr)					\
	mtx_unlock_spin(mtx_pool_find((pool), (ptr)))

/*
 * mtxpool_lockbuilder is a pool of sleep locks that is not witness
 * checked and should only be used for building higher level locks.
 *
 * mtxpool_sleep is a general purpose pool of sleep mutexes.
 */
extern struct mtx_pool *mtxpool_lockbuilder;
extern struct mtx_pool *mtxpool_sleep;

#ifndef LOCK_DEBUG
#error LOCK_DEBUG not defined, include <sys/lock.h> before <sys/mutex.h>
#endif
#if LOCK_DEBUG > 0 || defined(MUTEX_NOINLINE)
#define	mtx_lock_flags_(m, opts, file, line)
#define	mtx_unlock_flags_(m, opts, file, line)
#define	mtx_lock_spin_flags_(m, opts, file, line)
#define	mtx_unlock_spin_flags_(m, opts, file, line)
#else	/* LOCK_DEBUG == 0 && !MUTEX_NOINLINE */
#define	mtx_lock_flags_(m, opts, file, line)
#define	mtx_unlock_flags_(m, opts, file, line)
#define	mtx_lock_spin_flags_(m, opts, file, line)
#define	mtx_unlock_spin_flags_(m, opts, file, line)
#endif	/* LOCK_DEBUG > 0 || MUTEX_NOINLINE */

#ifdef INVARIANTS
#define	mtx_assert_(m, what, file, line)

#define GIANT_REQUIRED

#else	/* INVARIANTS */
#define mtx_assert_(m, what, file, line)	(void)0
#define GIANT_REQUIRED
#endif	/* INVARIANTS */

#define	mtx_lock_flags(m, opts)
#define	mtx_unlock_flags(m, opts)
#define	mtx_lock_spin_flags(m, opts)
#define	mtx_unlock_spin_flags(m, opts)
#define mtx_trylock_flags(m, opts)
#define	mtx_assert(m, what)

#define	mtx_sleep(chan, mtx, pri, wmesg, timo)

#define	mtx_initialized(m)

#define mtx_owned(m)	(1)

#define mtx_recursed(m)	(0)

#define mtx_name(m)

/*
 * Global locks.
 */
extern struct mtx Giant;
extern struct mtx blocked_lock;

/*
 * Giant lock manipulation and clean exit macros.
 * Used to replace return with an exit Giant and return.
 *
 * Note that DROP_GIANT*() needs to be paired with PICKUP_GIANT() 
 * The #ifndef is to allow lint-like tools to redefine DROP_GIANT.
 */
#ifndef DROP_GIANT
#define DROP_GIANT()

#define PICKUP_GIANT()

#define PARTIAL_PICKUP_GIANT()
#endif

#define	UGAR(rval)

struct mtx_args {
	struct mtx	*ma_mtx;
	const char 	*ma_desc;
	int		 ma_opts;
};

#define	MTX_SYSINIT(name, mtx, desc, opts)

/*
 * The INVARIANTS-enabled mtx_assert() functionality.
 *
 * The constants need to be defined for INVARIANT_SUPPORT infrastructure
 * support as _mtx_assert() itself uses them and the latter implies that
 * _mtx_assert() must build.
 */
#if defined(INVARIANTS) || defined(INVARIANT_SUPPORT)
#define MA_OWNED	LA_XLOCKED
#define MA_NOTOWNED	LA_UNLOCKED
#define MA_RECURSED	LA_RECURSED
#define MA_NOTRECURSED	LA_NOTRECURSED
#endif

/*
 * Common lock type names.
 */
#define	MTX_NETWORK_LOCK	"network driver"

// runsisi AT hust.edu.cn @2013/11/20
void mtx_init(struct mtx *m, const char *name, const char *type, int opts);
void mtx_destroy(struct mtx *m);
// ---------------------- @2013/11/20

#endif	/* _KERNEL */
#endif	/* _SYS_MUTEX_H_ */
