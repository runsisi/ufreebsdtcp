/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/eisa/eisa_if.m
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
#include <sys/bsd_types.h>
#include "eisa_if.h"

struct kobj_method eisa_add_intr_method_default = {
	&eisa_add_intr_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc eisa_add_intr_desc = {
	0, &eisa_add_intr_method_default
};

struct kobj_method eisa_add_iospace_method_default = {
	&eisa_add_iospace_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc eisa_add_iospace_desc = {
	0, &eisa_add_iospace_method_default
};

struct kobj_method eisa_add_mspace_method_default = {
	&eisa_add_mspace_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc eisa_add_mspace_desc = {
	0, &eisa_add_mspace_method_default
};

