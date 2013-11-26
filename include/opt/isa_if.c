/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/isa/isa_if.m
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
#include <isa/isavar.h>
#include "isa_if.h"

struct kobj_method isa_add_config_method_default = {
	&isa_add_config_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc isa_add_config_desc = {
	0, &isa_add_config_method_default
};

struct kobj_method isa_set_config_callback_method_default = {
	&isa_set_config_callback_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc isa_set_config_callback_desc = {
	0, &isa_set_config_callback_method_default
};

struct kobj_method isa_pnp_probe_method_default = {
	&isa_pnp_probe_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc isa_pnp_probe_desc = {
	0, &isa_pnp_probe_method_default
};

