/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/mmc/mmcbus_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/bsd_param.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_kobj.h>
#include <dev/mmc/mmcreg.h>
#include <dev/mmc/bridge.h>
#include "mmcbus_if.h"

struct kobj_method mmcbus_wait_for_request_method_default = {
	&mmcbus_wait_for_request_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mmcbus_wait_for_request_desc = {
	0, &mmcbus_wait_for_request_method_default
};

struct kobj_method mmcbus_acquire_bus_method_default = {
	&mmcbus_acquire_bus_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mmcbus_acquire_bus_desc = {
	0, &mmcbus_acquire_bus_method_default
};

struct kobj_method mmcbus_release_bus_method_default = {
	&mmcbus_release_bus_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mmcbus_release_bus_desc = {
	0, &mmcbus_release_bus_method_default
};

