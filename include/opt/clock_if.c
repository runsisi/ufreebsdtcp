/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/kern/clock_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/bsd_param.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_kobj.h>
#include <sys/bsd_bus.h>
#include <sys/bsd_time.h>
#include "clock_if.h"

struct kobj_method clock_gettime_method_default = {
	&clock_gettime_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc clock_gettime_desc = {
	0, &clock_gettime_method_default
};

struct kobj_method clock_settime_method_default = {
	&clock_settime_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc clock_settime_desc = {
	0, &clock_settime_method_default
};

