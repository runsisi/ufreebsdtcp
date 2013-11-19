/*-
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <phk@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_tc.c 248085 2013-03-09 02:36:32Z marius $");

#include "opt_compat.h"
#include "opt_ntp.h"

#include <sys/bsd_param.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_syslog.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_timepps.h>
#include <sys/bsd_timetc.h>
#include <sys/bsd_timex.h>
#include <sys/bsd_vdso.h>

volatile bsd_time_t time_uptime = 1;

static void tc_windup(void);

/*
 * Initialize the next struct timehands in the ring and make
 * it the active timehands.  Along the way we might switch to a different
 * timecounter and/or do seconds processing in NTP.  Slightly magic.
 */
static void
tc_windup(void)
{
    /*
     * TODO: what if ticks overflows? we will always lose a second
     * fortunately in brs we always use time_uptime to calculate
     * relative time, and it ok if it not precise
     */
    if ((unsigned int)ticks % hz == 0)
    {
        time_uptime++;
    }
}

void
tc_ticktock(int cnt)
{
	tc_windup();
}
