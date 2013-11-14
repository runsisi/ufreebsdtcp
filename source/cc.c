/*-
 * Copyright (c) 2007-2008
 *	Swinburne University of Technology, Melbourne, Australia.
 * Copyright (c) 2009-2010 Lawrence Stewart <lstewart@freebsd.org>
 * Copyright (c) 2010 The FreeBSD Foundation
 * All rights reserved.
 *
 * This software was developed at the Centre for Advanced Internet
 * Architectures, Swinburne University of Technology, by Lawrence Stewart and
 * James Healy, made possible in part by a grant from the Cisco University
 * Research Program Fund at Community Foundation Silicon Valley.
 *
 * Portions of this software were developed at the Centre for Advanced
 * Internet Architectures, Swinburne University of Technology, Melbourne,
 * Australia by David Hayes under sponsorship from the FreeBSD Foundation.
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
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * This software was first released in 2007 by James Healy and Lawrence Stewart
 * whilst working on the NewTCP research project at Swinburne University of
 * Technology's Centre for Advanced Internet Architectures, Melbourne,
 * Australia, which was made possible in part by a grant from the Cisco
 * University Research Program Fund at Community Foundation Silicon Valley.
 * More details are available at:
 *   http://caia.swin.edu.au/urp/newtcp/
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/netinet/cc/cc.c 220560 2011-04-12 08:13:18Z lstewart $");

#include <stdio.h>
#include <string.h>
#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_libkern.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_module.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_rwlock.h>
#include <sys/bsd_sbuf.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_socketvar.h>
#include <sys/bsd_sysctl.h>

#include <net/bsd_if.h>
#include <net/if_var.h>

#include <netinet/cc.h>
#include <netinet/bsd_in.h>
#include <netinet/in_pcb.h>
#include <netinet/tcp_var.h>

#include <netinet/cc/cc_module.h>

/*
 * List of available cc algorithms on the current system. First element
 * is used as the system default CC algorithm.
 */
struct cc_head cc_list = BSD_STAILQ_HEAD_INITIALIZER(cc_list);

/* Protects the cc_list TAILQ. */
struct rwlock cc_list_lock;

VNET_DEFINE(struct cc_algo *, default_cc_ptr) = &newreno_cc_algo;

/*
 * Reset the default CC algo to NewReno for any netstack which is using the algo
 * that is about to go away as its default.
 */
static void
cc_checkreset_default(struct cc_algo *remove_cc)
{
	VNET_ITERATOR_DECL(vnet_iter);

	CC_LIST_LOCK_ASSERT();

	VNET_LIST_RLOCK_NOSLEEP();
	VNET_FOREACH(vnet_iter) {
		CURVNET_SET(vnet_iter);
		if (strncmp(CC_DEFAULT()->name, remove_cc->name,
		    BSD_TCP_CA_NAME_MAX) == 0)
			V_default_cc_ptr = &newreno_cc_algo;
		CURVNET_RESTORE();
	}
	VNET_LIST_RUNLOCK_NOSLEEP();
}

/*
 * Initialise CC subsystem on system boot.
 */
static void
cc_init(void)
{
	CC_LIST_LOCK_INIT();
	BSD_STAILQ_INIT(&cc_list);
}

/*
 * Returns non-zero on success, 0 on failure.
 */
int
cc_deregister_algo(struct cc_algo *remove_cc)
{
	struct cc_algo *funcs, *tmpfuncs;
	int err;

	err = BSD_ENOENT;

	/* Never allow newreno to be deregistered. */
	if (&newreno_cc_algo == remove_cc)
		return (BSD_EPERM);

	/* Remove algo from cc_list so that new connections can't use it. */
	CC_LIST_WLOCK();
	BSD_STAILQ_FOREACH_SAFE(funcs, &cc_list, entries, tmpfuncs) {
		if (funcs == remove_cc) {
			cc_checkreset_default(remove_cc);
			BSD_STAILQ_REMOVE(&cc_list, funcs, cc_algo, entries);
			err = 0;
			break;
		}
	}
	CC_LIST_WUNLOCK();

	if (!err)
		/*
		 * XXXLAS:
		 * - We may need to handle non-zero return values in future.
		 * - If we add CC framework support for protocols other than
		 *   TCP, we may want a more generic way to handle this step.
		 */
		tcp_ccalgounload(remove_cc);

	return (err);
}

/*
 * Returns 0 on success, non-zero on failure.
 */
int
cc_register_algo(struct cc_algo *add_cc)
{
	struct cc_algo *funcs;
	int err;

	err = 0;

	/*
	 * Iterate over list of registered CC algorithms and make sure
	 * we're not trying to add a duplicate.
	 */
	CC_LIST_WLOCK();
	BSD_STAILQ_FOREACH(funcs, &cc_list, entries) {
		if (funcs == add_cc || strncmp(funcs->name, add_cc->name,
		    BSD_TCP_CA_NAME_MAX) == 0)
			err = BSD_EEXIST;
	}

	if (!err)
		BSD_STAILQ_INSERT_TAIL(&cc_list, add_cc, entries);

	CC_LIST_WUNLOCK();

	return (err);
}

/*
 * Handles kld related events. Returns 0 on success, non-zero on failure.
 */
int
cc_modevent(module_t mod, int event_type, void *data)
{
	struct cc_algo *algo;
	int err;

	err = 0;
	algo = (struct cc_algo *)data;

	switch(event_type) {
	case MOD_LOAD:
		if (algo->mod_init != NULL)
			err = algo->mod_init();
		if (!err)
			err = cc_register_algo(algo);
		break;

	case MOD_QUIESCE:
	case MOD_SHUTDOWN:
	case MOD_UNLOAD:
		err = cc_deregister_algo(algo);
		if (!err && algo->mod_destroy != NULL)
			algo->mod_destroy();
		if (err == BSD_ENOENT)
			err = 0;
		break;

	default:
		err = BSD_EINVAL;
		break;
	}

	return (err);
}

// runsisi AT hust.edu.cn @2013/11/07
int
bsd_cc_init(void)
{
    cc_init();
    return 0;
}
// ---------------------- @2013/11/07
