/*-
 * Copyright (c) 1982, 1986, 1991, 1993
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
 *	@(#)kern_clock.c	8.5 (Berkeley) 1/21/94
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_clock.c 250600 2013-05-13 15:18:36Z fabient $");

#include "opt_kdb.h"
#include "opt_device_polling.h"
#include "opt_hwpmc_hooks.h"
#include "opt_kdtrace.h"
#include "opt_ntp.h"
#include "opt_watchdog.h"

#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_callout.h>
#include <sys/bsd_kdb.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_kthread.h>
#include <sys/bsd_ktr.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_resource.h>
#include <sys/bsd_resourcevar.h>
#include <sys/bsd_sched.h>
#include <sys/bsd_sdt.h>
#include <sys/bsd_signalvar.h>
#include <sys/bsd_sleepqueue.h>
#include <sys/bsd_smp.h>
#include <vm/vm.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_bus.h>
#include <sys/bsd_interrupt.h>
#include <sys/bsd_limits.h>
#include <sys/bsd_timetc.h>

// runsisi AT hust.edu.cn @2013/11/20
#include <net/vnet.h>
// ---------------------- @2013/11/20

/*
 * Clock handling routines.
 *
 * This code is written to operate with two timers that run independently of
 * each other.
 *
 * The main timer, running hz times per second, is used to trigger interval
 * timers, timeouts and rescheduling as needed.
 *
 * The second timer handles kernel and user profiling,
 * and does resource use estimation.  If the second timer is programmable,
 * it is randomized to avoid aliasing between the two clocks.  For example,
 * the randomization prevents an adversary from always giving up the cpu
 * just before its quantum expires.  Otherwise, it would never accumulate
 * cpu ticks.  The mean frequency of the second timer is stathz.
 *
 * If no second timer exists, stathz will be zero; in this case we drive
 * profiling and statistics off the main clock.  This WILL NOT be accurate;
 * do not do it unless absolutely necessary.
 *
 * The statistics clock may (or may not) be run at a higher rate while
 * profiling.  This profile clock runs at profhz.  We require that profhz
 * be an integral multiple of stathz.
 *
 * If the statistics clock is running fast, it must be divided by the ratio
 * profhz/stathz for statistics.  (For profiling, every tick counts.)
 *
 * Time-of-day is maintained using a "timecounter", which may or may
 * not be related to the hardware generating the above mentioned
 * interrupts.
 */

#if 0	// runsisi AT hust.edu.cn @2013/11/20
volatile int	ticks;
#endif 	// ---------------------- @2013/11/20
// runsisi AT hust.edu.cn @2013/11/20
VNET_DEFINE(volatile int, ticks);
#define V_ticks     VNET(ticks)
// ---------------------- @2013/11/20

/*
 * Each time the real-time timer fires, this function is called on all CPUs.
 * Note that hardclock() calls hardclock_cpu() for the boot CPU, so only
 * the other CPUs in the system need to call this function.
 */
void
hardclock_cpu(int usermode)
{
	callout_tick();
}

/*
 * The real-time timer, interrupting hz times per second.
 */
void
hardclock(int usermode, bsd_uintfptr_t pc)
{
    atomic_add_int(&V_ticks, 1);
	hardclock_cpu(usermode);
	tc_ticktock(1);
}
