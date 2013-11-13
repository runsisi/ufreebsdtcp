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

#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_malloc.h>

/*
 * Centrally define some common malloc types.
 */
MALLOC_DEFINE(M_TEMP, "temp", "misc temporary data buffers");

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

	// TODO: dps 是否提供了 reaclloc接口, 否则无法决定 alloc 大小

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
