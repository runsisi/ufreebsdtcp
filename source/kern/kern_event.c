/*-
 * Copyright (c) 1999,2000,2001 Jonathan Lemon <jlemon@FreeBSD.org>
 * Copyright 2004 John-Mark Gurney <jmg@FreeBSD.org>
 * Copyright (c) 2009 Apple, Inc.
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
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_event.c 239915 2012-08-30 18:29:49Z jhb $");

#include "opt_ktrace.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_capability.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_unistd.h>
#include <sys/bsd_file.h>
#include <sys/bsd_filedesc.h>
#include <sys/bsd_filio.h>
#include <sys/bsd_fcntl.h>
#include <sys/bsd_kthread.h>
#include <sys/bsd_selinfo.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_event.h>
#include <sys/bsd_eventvar.h>
#include <sys/bsd_poll.h>
#include <sys/bsd_protosw.h>
#include <sys/bsd_sigio.h>
#include <sys/bsd_signalvar.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_socketvar.h>
#include <sys/bsd_stat.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_sysproto.h>
#include <sys/bsd_syscallsubr.h>
#include <sys/bsd_taskqueue.h>
#include <sys/bsd_uio.h>
#ifdef KTRACE
#include <sys/bsd_ktrace.h>
#endif

#include <vm/uma.h>

/*
 * Walk down a list of knotes, activating them if their event has triggered.
 *
 * There is a possibility to optimize in the case of one kq watching another.
 * Instead of scheduling a task to wake it up, you could pass enough state
 * down the chain to make up the parent kqueue.  Make this code functional
 * first.
 */
void
knote(struct knlist *list, long hint, int lockflags)
{
	struct knote *kn;

	if (list == NULL)
		return;

	/*
	 * If we unlock the list lock (and set KN_INFLUX), we can eliminate
	 * the kqueue scheduling, but this will introduce four
	 * lock/unlock's for each knote to test.  If we do, continue to use
	 * BSD_SLIST_FOREACH, BSD_SLIST_FOREACH_SAFE is not safe in our case, it is
	 * only safe if you want to remove the current item, which we are
	 * not doing.
	 */
	BSD_SLIST_FOREACH(kn, &list->kl_list, kn_selnext) {
	}
}

void
knlist_init(struct knlist *knl, void *lock, void (*kl_lock)(void *),
    void (*kl_unlock)(void *),
    void (*kl_assert_locked)(void *), void (*kl_assert_unlocked)(void *))
{

	BSD_SLIST_INIT(&knl->kl_list);
}

void
knlist_init_mtx(struct knlist *knl, struct mtx *lock)
{

	knlist_init(knl, lock, NULL, NULL, NULL, NULL);
}

void
knlist_destroy(struct knlist *knl)
{

#ifdef INVARIANTS
	/*
	 * if we run across this error, we need to find the offending
	 * driver and have it call knlist_clear.
	 */
	if (!BSD_SLIST_EMPTY(&knl->kl_list))
		printf("WARNING: destroying knlist w/ knotes on it!\n");
#endif

	knl->kl_lockarg = knl->kl_lock = knl->kl_unlock = NULL;
	BSD_SLIST_INIT(&knl->kl_list);
}
