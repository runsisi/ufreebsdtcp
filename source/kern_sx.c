/*-
 * Copyright (c) 2007 Attilio Rao <attilio@freebsd.org>
 * Copyright (c) 2001 Jason Evans <jasone@freebsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice(s), this list of conditions and the following disclaimer as
 *    the first lines of this file unmodified other than the possible
 *    addition of one or more copyright notices.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice(s), this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/*
 * Shared/exclusive locks.  This implementation attempts to ensure
 * deterministic lock granting behavior, so that slocks and xlocks are
 * interleaved.
 *
 * Priority propagation will not generally raise the priority of lock holders,
 * so should not be relied upon in combination with sx locks.
 */

#include "opt_ddb.h"
#include "opt_hwpmc_hooks.h"
#include "opt_kdtrace.h"
#include "opt_no_adaptive_sx.h"

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_sx.c 250581 2013-05-12 22:01:22Z hiren $");

#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_sx.h>

int
_sx_try_xlock(struct sx *sx, const char *file, int line)
{

    return (0);
}

/*
 * This function represents the so-called 'hard case' for sx_xlock
 * operation.  All 'easy case' failures are redirected to this.  Note
 * that ideally this would be a static function, but it needs to be
 * accessible from at least sx.h.
 */
int
_sx_xlock_hard(struct sx *sx, bsd_uintptr_t tid, int opts, const char *file,
    int line)
{

	return (0);
}

/*
 * This function represents the so-called 'hard case' for sx_xunlock
 * operation.  All 'easy case' failures are redirected to this.  Note
 * that ideally this would be a static function, but it needs to be
 * accessible from at least sx.h.
 */
void
_sx_xunlock_hard(struct sx *sx, bsd_uintptr_t tid, const char *file, int line)
{

}

/*
 * This function represents the so-called 'hard case' for sx_slock
 * operation.  All 'easy case' failures are redirected to this.  Note
 * that ideally this would be a static function, but it needs to be
 * accessible from at least sx.h.
 */
int
_sx_slock_hard(struct sx *sx, int opts, const char *file, int line)
{

	return (0);
}

/*
 * This function represents the so-called 'hard case' for sx_sunlock
 * operation.  All 'easy case' failures are redirected to this.  Note
 * that ideally this would be a static function, but it needs to be
 * accessible from at least sx.h.
 */
void
_sx_sunlock_hard(struct sx *sx, const char *file, int line)
{

}
