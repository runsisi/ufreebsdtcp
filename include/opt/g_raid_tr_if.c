/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/geom/raid/g_raid_tr_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <sys/param.h>
#include <sys/lock.h>
#include <sys/malloc.h>
#include <sys/mutex.h>
#include <sys/sbuf.h>
#include <sys/bus.h>
#include <machine/bus.h>
#include <sys/systm.h>
#include <geom/geom.h>
#include <geom/raid/g_raid.h>
#include "g_raid_tr_if.h"


static int
g_raid_tr_locked_default(struct g_raid_tr_object *tr, void *argp)
{

	return (0);
}

struct kobj_method g_raid_tr_taste_method_default = {
	&g_raid_tr_taste_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_tr_taste_desc = {
	0, &g_raid_tr_taste_method_default
};

struct kobj_method g_raid_tr_event_method_default = {
	&g_raid_tr_event_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_tr_event_desc = {
	0, &g_raid_tr_event_method_default
};

struct kobj_method g_raid_tr_start_method_default = {
	&g_raid_tr_start_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_tr_start_desc = {
	0, &g_raid_tr_start_method_default
};

struct kobj_method g_raid_tr_stop_method_default = {
	&g_raid_tr_stop_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_tr_stop_desc = {
	0, &g_raid_tr_stop_method_default
};

struct kobj_method g_raid_tr_iostart_method_default = {
	&g_raid_tr_iostart_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_tr_iostart_desc = {
	0, &g_raid_tr_iostart_method_default
};

struct kobj_method g_raid_tr_iodone_method_default = {
	&g_raid_tr_iodone_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_tr_iodone_desc = {
	0, &g_raid_tr_iodone_method_default
};

struct kobj_method g_raid_tr_kerneldump_method_default = {
	&g_raid_tr_kerneldump_desc, (kobjop_t) g_raid_tr_kerneldump_common
};

struct kobjop_desc g_raid_tr_kerneldump_desc = {
	0, &g_raid_tr_kerneldump_method_default
};

struct kobj_method g_raid_tr_locked_method_default = {
	&g_raid_tr_locked_desc, (kobjop_t) g_raid_tr_locked_default
};

struct kobjop_desc g_raid_tr_locked_desc = {
	0, &g_raid_tr_locked_method_default
};

struct kobj_method g_raid_tr_free_method_default = {
	&g_raid_tr_free_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_tr_free_desc = {
	0, &g_raid_tr_free_method_default
};

struct kobj_method g_raid_tr_idle_method_default = {
	&g_raid_tr_idle_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_tr_idle_desc = {
	0, &g_raid_tr_idle_method_default
};

