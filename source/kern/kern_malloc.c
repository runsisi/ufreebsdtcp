/*-
 * Copyright (c) 1987, 1991, 1993
 *	The Regents of the University of California.
 * Copyright (c) 2005-2009 Robert N. M. Watson
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
 *	@(#)kern_malloc.c	8.3 (Berkeley) 1/4/94
 */

/*
 * Kernel malloc(9) implementation -- general purpose kernel memory allocator
 * based on memory types.  Back end is implemented using the UMA(9) zone
 * allocator.  A set of fixed-size buckets are used for smaller allocations,
 * and a special UMA allocation interface is used for larger allocations.
 * Callers declare memory types, and statistics are maintained independently
 * for each memory type.  Statistics are maintained per-CPU for performance
 * reasons.  See malloc(9) and comments in malloc.h for a detailed
 * description.
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_malloc.c 248085 2013-03-09 02:36:32Z marius $");

#include "opt_ddb.h"
#include "opt_kdtrace.h"
#include "opt_vm.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_kdb.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_mbuf.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_vmmeter.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_sbuf.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_time.h>

#include <vm/vm.h>
#include <vm/pmap.h>
#include <vm/vm_param.h>
#include <vm/vm_kern.h>
#include <vm/vm_extern.h>
#include <vm/vm_map.h>
#include <vm/vm_page.h>
#include <vm/uma.h>
#include <vm/uma_int.h>
#include <vm/uma_dbg.h>

#ifdef DEBUG_MEMGUARD
#include <vm/memguard.h>
#endif
#ifdef DEBUG_REDZONE
#include <vm/redzone.h>
#endif

#if defined(INVARIANTS) && defined(__i386__)
#include <machine/bsd_cpu.h>
#endif

//#include <ddb/ddb.h>

#ifdef KDTRACE_HOOKS
#include <sys/bsd_dtrace_bsd.h>

dtrace_malloc_probe_func_t	dtrace_malloc_probe;
#endif

/*
 * When realloc() is called, if the new size is sufficiently smaller than
 * the old size, realloc() will allocate a new, smaller block to avoid
 * wasting memory. 'Sufficiently smaller' is defined as: newsize <=
 * oldsize / 2^n, where REALLOC_FRACTION defines the value of 'n'.
 */
#ifndef REALLOC_FRACTION
#define	REALLOC_FRACTION	1	/* new block if <= half the size */
#endif

/*
 * Centrally define some common malloc types.
 */
MALLOC_DEFINE(M_CACHE, "cache", "Various Dynamically allocated caches");
MALLOC_DEFINE(M_DEVBUF, "devbuf", "device driver memory");
MALLOC_DEFINE(M_TEMP, "temp", "misc temporary data buffers");

MALLOC_DEFINE(M_IP6OPT, "ip6opt", "IPv6 options");
MALLOC_DEFINE(M_IP6NDP, "ip6ndp", "IPv6 Neighbor Discovery");

/*
 *	malloc:
 *
 *	Allocate a block of memory.
 *
 *	If M_NOWAIT is set, this routine will not block and return NULL if
 *	the allocation fails.
 */
void *
bsd_malloc(unsigned long size, struct malloc_type *mtp, int flags)
{
	caddr_t va;

	va = DPS_GetUUB("bsd malloc", size);

	return ((void *) va);
}

/*
 *	free:
 *
 *	Free a block of memory allocated by malloc.
 *
 *	This routine may not block.
 */
void
bsd_free(void *addr, struct malloc_type *mtp)
{
    if (addr)
    {
        DPS_RetUUB(addr);
    }
}

/*
 *	realloc: change the size of a memory block
 */
void *
bsd_realloc(void *addr, unsigned long size, struct malloc_type *mtp, int flags)
{
	unsigned long alloc;
	void *newaddr;

	/* realloc(NULL, ...) is equivalent to malloc(...) */
	if (addr == NULL)
		return (bsd_malloc(size, mtp, flags));

	// TODO: dps have to provide reaclloc interface, or alloc can not be known

	/* Allocate a new, bigger (or smaller) block */
	if ((newaddr = bsd_malloc(size, mtp, flags)) == NULL)
		return (NULL);

	/* Copy over original contents */
	bcopy(addr, newaddr, min(size, alloc));
	bsd_free(addr, mtp);
	return (newaddr);
}

/*
 *	reallocf: same as realloc() but free memory on failure.
 */
void *
reallocf(void *addr, unsigned long size, struct malloc_type *mtp, int flags)
{
	void *mem;

	if ((mem = bsd_realloc(addr, size, mtp, flags)) == NULL)
		bsd_free(addr, mtp);
	return (mem);
}
