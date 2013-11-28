/*-
 * Copyright (c) 1998 Berkeley Software Design, Inc. All rights reserved.
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
 *	from BSDI $Id: mutex_witness.c,v 1.1.2.20 2000/04/27 03:10:27 cp Exp $
 *	and BSDI $Id: synch_machdep.c,v 2.3.2.39 2000/04/27 03:10:25 cp Exp $
 */

/*
 * Machine independent bits of mutex implementation.
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_mutex.c 250581 2013-05-12 22:01:22Z hiren $");

#include "opt_adaptive_mutexes.h"
#include "opt_ddb.h"
#include "opt_global.h"
#include "opt_hwpmc_hooks.h"
#include "opt_kdtrace.h"
#include "opt_sched.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_bus.h>
#include <sys/bsd_conf.h>
#include <sys/bsd_kdb.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_ktr.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_resourcevar.h>
#include <sys/bsd_sched.h>
#include <sys/bsd_sbuf.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_turnstile.h>
#include <sys/bsd_vmmeter.h>
#include <sys/bsd_lock_profile.h>

#include <machine/bsd_atomic.h>
#include <machine/bsd_bus.h>
#include <machine/bsd_cpu.h>

//#include <ddb/ddb.h>

//#include <fs/devfs/devfs_int.h>

#include <vm/vm.h>
#include <vm/vm_extern.h>

#if defined(SMP) && !defined(NO_ADAPTIVE_MUTEXES)
#define	ADAPTIVE_MUTEXES
#endif

#ifdef HWPMC_HOOKS
#include <sys/bsd_pmckern.h>
PMC_SOFT_DEFINE( , , lock, failed);
#endif

/*
 * Internal utility macros.
 */
#define mtx_unowned(m)	((m)->mtx_lock == MTX_UNOWNED)

#define	mtx_destroyed(m) ((m)->mtx_lock == MTX_DESTROYED)

#define	mtx_owner(m)	((struct thread *)((m)->mtx_lock & ~MTX_FLAGMASK))

static void	assert_mtx(struct lock_object *lock, int what);
#ifdef DDB
static void	db_show_mtx(struct lock_object *lock);
#endif
static void	lock_mtx(struct lock_object *lock, int how);
static void	lock_spin(struct lock_object *lock, int how);
#ifdef KDTRACE_HOOKS
static int	owner_mtx(struct lock_object *lock, struct thread **owner);
#endif
static int	unlock_mtx(struct lock_object *lock);
static int	unlock_spin(struct lock_object *lock);

/*
 * Lock classes for sleep and spin mutexes.
 */
struct lock_class lock_class_mtx_sleep = {
	.lc_name = "sleep mutex",
	.lc_flags = LC_SLEEPLOCK | LC_RECURSABLE,
	.lc_assert = assert_mtx,
#ifdef DDB
	.lc_ddb_show = db_show_mtx,
#endif
	.lc_lock = lock_mtx,
	.lc_unlock = unlock_mtx,
#ifdef KDTRACE_HOOKS
	.lc_owner = owner_mtx,
#endif
};
struct lock_class lock_class_mtx_spin = {
	.lc_name = "spin mutex",
	.lc_flags = LC_SPINLOCK | LC_RECURSABLE,
	.lc_assert = assert_mtx,
#ifdef DDB
	.lc_ddb_show = db_show_mtx,
#endif
	.lc_lock = lock_spin,
	.lc_unlock = unlock_spin,
#ifdef KDTRACE_HOOKS
	.lc_owner = owner_mtx,
#endif
};

/*
 * System-wide mutexes
 */
struct mtx blocked_lock;
struct mtx Giant;

void
assert_mtx(struct lock_object *lock, int what)
{

	mtx_assert((struct mtx *)lock, what);
}

void
lock_mtx(struct lock_object *lock, int how)
{

	mtx_lock((struct mtx *)lock);
}

void
lock_spin(struct lock_object *lock, int how)
{

	panic("spin locks can only use msleep_spin");
}

int
unlock_mtx(struct lock_object *lock)
{
	return (0);
}

int
unlock_spin(struct lock_object *lock)
{

	panic("spin locks can only use msleep_spin");
}

#ifdef KDTRACE_HOOKS
int
owner_mtx(struct lock_object *lock, struct thread **owner)
{
	struct mtx *m = (struct mtx *)lock;

	*owner = mtx_owner(m);
	return (mtx_unowned(m) == 0);
}
#endif

/*
 * Function versions of the inlined __mtx_* macros.  These are used by
 * modules and can also be called from assembly language if needed.
 */
void
_mtx_lock_flags(struct mtx *m, int opts, const char *file, int line)
{

}

void
_mtx_unlock_flags(struct mtx *m, int opts, const char *file, int line)
{

}

void
_mtx_lock_spin_flags(struct mtx *m, int opts, const char *file, int line)
{

}

void
_mtx_unlock_spin_flags(struct mtx *m, int opts, const char *file, int line)
{

}

/*
 * The important part of mtx_trylock{,_flags}()
 * Tries to acquire lock `m.'  If this function is called on a mutex that
 * is already owned, it will recursively acquire the lock.
 */
int
_mtx_trylock(struct mtx *m, int opts, const char *file, int line)
{

	return (1);
}

/*
 * _mtx_lock_sleep: the tougher part of acquiring an MTX_DEF lock.
 *
 * We call this if the lock is either contested (i.e. we need to go to
 * sleep waiting for it), or if we need to recurse on it.
 */
void
_mtx_lock_sleep(struct mtx *m, uintptr_t tid, int opts, const char *file,
    int line)
{

}

void
_thread_lock_flags(struct thread *td, int opts, const char *file, int line)
{

}

struct mtx *
thread_lock_block(struct thread *td)
{
	struct mtx *lock;

	return (lock);
}

void
thread_lock_unblock(struct thread *td, struct mtx *new)
{

}

void
thread_lock_set(struct thread *td, struct mtx *new)
{

}

/*
 * _mtx_unlock_sleep: the tougher part of releasing an MTX_DEF lock.
 *
 * We are only called here if the lock is recursed or contested (i.e. we
 * need to wake up a blocked thread).
 */
void
_mtx_unlock_sleep(struct mtx *m, int opts, const char *file, int line)
{

}

/*
 * All the unlocking of MTX_SPIN locks is done inline.
 * See the __mtx_unlock_spin() macro for the details.
 */

/*
 * The backing function for the INVARIANTS-enabled mtx_assert()
 */
#ifdef INVARIANT_SUPPORT
void
_mtx_assert(struct mtx *m, int what, const char *file, int line)
{

}
#endif

/*
 * The MUTEX_DEBUG-enabled mtx_validate()
 *
 * Most of these checks have been moved off into the LO_INITIALIZED flag
 * maintained by the witness code.
 */
#ifdef MUTEX_DEBUG

void	mtx_validate(struct mtx *);

void
mtx_validate(struct mtx *m)
{

}
#endif

/*
 * General init routine used by the MTX_SYSINIT() macro.
 */
void
mtx_sysinit(void *arg)
{

}

/*
 * Mutex initialization routine; initialize lock `m' of type contained in
 * `opts' with options contained in `opts' and name `name.'  The optional
 * lock type `type' is used as a general lock category name for use with
 * witness.
 */
void
mtx_init(struct mtx *m, const char *name, const char *type, int opts)
{

}

/*
 * Remove lock `m' from all_mtx queue.  We don't allow MTX_QUIET to be
 * passed in as a flag here because if the corresponding mtx_init() was
 * called with MTX_QUIET set, then it will already be set in the mutex's
 * flags.
 */
void
mtx_destroy(struct mtx *m)
{

}

/*
 * Intialize the mutex code and system mutexes.  This is called from the MD
 * startup code prior to mi_startup().  The per-CPU data space needs to be
 * setup before this is called.
 */
void
mutex_init(void)
{

}
