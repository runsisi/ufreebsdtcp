/*-
 * Copyright (c) 1980, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 *	@(#)param.c	8.3 (Berkeley) 8/20/94
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/subr_param.c 253250 2013-07-12 05:45:09Z grehan $");

#include "opt_param.h"
#include "opt_msgbuf.h"
#include "opt_maxusers.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_limits.h>
#include <sys/bsd_msgbuf.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_proc.h>

#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/pmap.h>

/*
 * System parameter formulae.
 */

#ifndef HZ
#define	HZ 50 //1000
#endif
#define NPROC (20 + 16 * maxusers)
#ifndef NBUF
#define NBUF 0
#endif
#ifndef MAXFILES
#define MAXFILES (maxproc * 2)
#endif

int hz;
int tick;
int maxusers;           /* base tunable */
int maxproc;            /* maximum # of processes */
int maxprocperuid;          /* max # of procs per user */
int maxfiles;           /* sys. wide open files limit */
int maxfilesperproc;        /* per-proc open files limit */
int ncallout;           /* maximum # of timer events */

SYSCTL_INT(_kern, OID_AUTO, hz, CTLFLAG_RDTUN, &hz, 0,
    "Number of clock ticks per second");
SYSCTL_INT(_kern, OID_AUTO, ncallout, CTLFLAG_RDTUN, &ncallout, 0,
    "Number of pre-allocated timer events");
/*
 * Boot time overrides that are not scaled against main memory
 */
void
init_param1(void)
{
	hz = -1;
	TUNABLE_INT_FETCH("kern.hz", &hz);
	if (hz == -1)
		hz = HZ;
	tick = 1000000 / hz;

	ncallout = 4096;    // 4096 callout tailq
    TUNABLE_INT_FETCH("kern.ncallout", &ncallout);
}

/*
 * Boot time overrides that are scaled against main memory
 */
void
init_param2(long physpages)
{

	/* Base parameters */
	maxusers = MAXUSERS;
	TUNABLE_INT_FETCH("kern.maxusers", &maxusers);
	if (maxusers == 0) {
		maxusers = physpages / (2 * 1024 * 1024 / PAGE_SIZE);
		if (maxusers < 32)
			maxusers = 32;
		if (maxusers > 384)
			maxusers = 384;
	}

    /*
     * The following can be overridden after boot via sysctl.  Note:
     * unless overriden, these macros are ultimately based on maxusers.
     */
    maxproc = NPROC;
    TUNABLE_INT_FETCH("kern.maxproc", &maxproc);
    /*
     * Limit maxproc so that kmap entries cannot be exhausted by
     * processes.
     */
    #if 0	// runsisi AT hust.edu.cn @2013/11/29
    if (maxproc > (physpages / 12))
        maxproc = physpages / 12;
    #endif 	// ---------------------- @2013/11/29
    maxfiles = MAXFILES;
    TUNABLE_INT_FETCH("kern.maxfiles", &maxfiles);
    maxprocperuid = (maxproc * 9) / 10;
    maxfilesperproc = (maxfiles * 9) / 10;
}

// runsisi AT hust.edu.cn @2013/11/08
static void
bsd_param_init(void *dummy)
{
    init_param1();
    init_param2(0);
}

/*
 * be careful with the order
 */
SYSINIT(param_init, SI_SUB_TUNABLES, SI_ORDER_FIRST, bsd_param_init, NULL);
// ---------------------- @2013/11/08
