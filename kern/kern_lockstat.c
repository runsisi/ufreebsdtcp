/*-
 * Copyright 2008-2009 Stacey Son <sson@FreeBSD.org>
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
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: release/9.2.0/sys/kern/kern_lockstat.c 192853 2009-05-26 20:28:22Z sson $
 */

/*
 * Backend for the lock tracing (lockstat) kernel support. This is required 
 * to allow a module to load even though DTrace kernel support may not be 
 * present. 
 *
 */

#include "opt_kdtrace.h"

#ifdef KDTRACE_HOOKS

#include <sys/time.h>
#include <sys/types.h>
#include <sys/lockstat.h>

/*
 * The following must match the type definition of dtrace_probe.  It is  
 * defined this way to avoid having to rely on CDDL code.
 */
bsd_uint32_t lockstat_probemap[LS_NPROBES];
void (*lockstat_probe_func)(bsd_uint32_t, bsd_uintptr_t, bsd_uintptr_t,
    bsd_uintptr_t, bsd_uintptr_t, bsd_uintptr_t);


bsd_uint64_t 
lockstat_nsecs(void)
{
	struct bsd_bintime bt;
	bsd_uint64_t ns;

	binuptime(&bt);
	ns = bt.sec * (bsd_uint64_t)1000000000;
	ns += ((bsd_uint64_t)1000000000 * (bsd_uint32_t)(bt.frac >> 32)) >> 32;
	return (ns);
}

#endif /* KDTRACE_HOOKS */
