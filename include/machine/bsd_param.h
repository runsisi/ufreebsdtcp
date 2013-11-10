/*-
 * Copyright (c) 2002 David E. O'Brien.  All rights reserved.
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 *	@(#)param.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: release/9.2.0/sys/amd64/include/param.h 240097 2012-09-04 19:14:57Z des $
 */


#ifndef _AMD64_INCLUDE_PARAM_H_
#define	_AMD64_INCLUDE_PARAM_H_

#include <machine/_bsd_align.h>

/*
 * Machine dependent constants for AMD64.
 */


#define __HAVE_ACPI
#define __PCI_REROUTE_INTERRUPT

#ifndef MACHINE
#define	MACHINE		"amd64"
#endif
#ifndef MACHINE_ARCH
#define	MACHINE_ARCH	"amd64"
#endif
#ifndef MACHINE_ARCH32
#define	MACHINE_ARCH32	"i386"
#endif

#if defined(SMP) || defined(KLD_MODULE)
#ifndef MAXCPU
#define MAXCPU		64
#endif
#else
#define MAXCPU		1
#endif

#define	ALIGNBYTES		_BSD_ALIGNBYTES
#define	ALIGN(p)		_BSD_ALIGN(p)
/*
 * ALIGNED_POINTER is a boolean macro that checks whether an address
 * is valid to fetch data elements of type t from on this architecture.
 * This does not reflect the optimal alignment, just the possibility
 * (within reasonable limits). 
 */
#define	ALIGNED_POINTER(p, t)	1

/*
 * CACHE_LINE_SIZE is the compile-time maximum cache line size for an
 * architecture.  It should be used with appropriate caution.
 */
#define	BSD_CACHE_LINE_SHIFT	7
#define	BSD_CACHE_LINE_SIZE		(1 << BSD_CACHE_LINE_SHIFT)

/* Size of the level 1 page table units */
#define BSD_NPTEPG		(BSD_PAGE_SIZE/(sizeof (pt_entry_t)))
#define	BSD_NPTEPGSHIFT	9		/* LOG2(NPTEPG) */
#define BSD_PAGE_SHIFT	12		/* LOG2(PAGE_SIZE) */
#define BSD_PAGE_SIZE	(1<<BSD_PAGE_SHIFT)	/* bytes/page */
#define BSD_PAGE_MASK	(BSD_PAGE_SIZE-1)
/* Size of the level 2 page directory units */
#define	BSD_NPDEPG		(BSD_PAGE_SIZE/(sizeof (pd_entry_t)))
#define	BSD_NPDEPGSHIFT	9		/* LOG2(NPDEPG) */
#define	BSD_PDRSHIFT	21              /* LOG2(NBPDR) */
#define	BSD_NBPDR		(1<<BSD_PDRSHIFT)   /* bytes/page dir */
#define	BSD_PDRMASK		(BSD_NBPDR-1)
/* Size of the level 3 page directory pointer table units */
#define	BSD_NPDPEPG		(BSD_PAGE_SIZE/(sizeof (pdp_entry_t)))
#define	BSD_NPDPEPGSHIFT	9		/* LOG2(NPDPEPG) */
#define	BSD_PDPSHIFT	30		/* LOG2(NBPDP) */
#define	BSD_NBPDP		(1<<BSD_PDPSHIFT)	/* bytes/page dir ptr table */
#define	BSD_PDPMASK		(BSD_NBPDP-1)
/* Size of the level 4 page-map level-4 table units */
#define	BSD_NPML4EPG	(BSD_PAGE_SIZE/(sizeof (pml4_entry_t)))
#define	BSD_NPML4EPGSHIFT	9		/* LOG2(NPML4EPG) */
#define	BSD_PML4SHIFT	39		/* LOG2(NBPML4) */
#define	BSD_NBPML4		(1UL<<BSD_PML4SHIFT)/* bytes/page map lev4 table */
#define	BSD_PML4MASK	(BSD_NBPML4-1)

#define	BSD_MAXPAGESIZES	3	/* maximum number of supported page sizes */

#define BSD_IOPAGES	2		/* pages of i/o permission bitmap */

#ifndef	BSD_KSTACK_PAGES
#define	BSD_KSTACK_PAGES	4	/* pages of kstack (with pcb) */
#endif
#define	BSD_KSTACK_GUARD_PAGES 1	/* pages of kstack guard; 0 disables */

/*
 * Mach derived conversion macros
 */
#define	round_page(x)	((((unsigned long)(x)) + BSD_PAGE_MASK) & ~(BSD_PAGE_MASK))
#define	trunc_page(x)	((unsigned long)(x) & ~(BSD_PAGE_MASK))
#define trunc_2mpage(x)	((unsigned long)(x) & ~BSD_PDRMASK)
#define round_2mpage(x)	((((unsigned long)(x)) + BSD_PDRMASK) & ~BSD_PDRMASK)
#define trunc_1gpage(x)	((unsigned long)(x) & ~BSD_PDPMASK)

#define	atop(x)		((unsigned long)(x) >> BSD_PAGE_SHIFT)
#define	ptoa(x)		((unsigned long)(x) << BSD_PAGE_SHIFT)

#define	amd64_btop(x)	((unsigned long)(x) >> BSD_PAGE_SHIFT)
#define	amd64_ptob(x)	((unsigned long)(x) << BSD_PAGE_SHIFT)

#define	pgtok(x)	((unsigned long)(x) * (BSD_PAGE_SIZE / 1024)) 

#endif /* !_AMD64_INCLUDE_PARAM_H_ */
