/*-
 * Copyright (c) 2009 Konstantin Belousov <kib@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: release/9.2.0/sys/sys/rangelock.h 239835 2012-08-29 15:13:13Z kib $
 */

#ifndef	_SYS_RANGELOCK_H
#define	_SYS_RANGELOCK_H

#include <sys/bsd_queue.h>

#define	RL_LOCK_READ		0x0001
#define	RL_LOCK_WRITE		0x0002
#define	RL_LOCK_TYPE_MASK	0x0003
#define	RL_LOCK_GRANTED		0x0004

struct rl_q_entry;

/*
 * The structure representing the range lock.  Caller may request
 * read or write access to the range of bytes. Access is granted if
 * all existing lock owners are compatible with the request. Two lock
 * owners are compatible if their ranges do not overlap, or both
 * owners are for read.
 *
 * Access to the structure itself is synchronized with the externally
 * supplied mutex.
 *
 * rl_waiters is the queue of lock requests in the order of arrival.
 * rl_currdep is the first lock request that cannot be granted now due
 * to the preceding requests conflicting with it.
 */
struct rangelock {
	BSD_TAILQ_HEAD(, rl_q_entry) rl_waiters;
	struct rl_q_entry	*rl_currdep;
};

#ifdef _KERNEL

struct mtx;

void	 rangelock_init(struct rangelock *lock);
void	 rangelock_destroy(struct rangelock *lock);
void	 rangelock_unlock(struct rangelock *lock, void *cookie,
	    struct mtx *ilk);
void	*rangelock_unlock_range(struct rangelock *lock, void *cookie,
	    off_t start, off_t end, struct mtx *ilk);
void	*rangelock_rlock(struct rangelock *lock, off_t start, off_t end,
	    struct mtx *ilk);
void	*rangelock_wlock(struct rangelock *lock, off_t start, off_t end,
	    struct mtx *ilk);
void	 rlqentry_free(struct rl_q_entry *rlqe);

#endif	/* _KERNEL */

#endif	/* _SYS_RANGELOCK_H */
