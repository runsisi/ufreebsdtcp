/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/mii/miibus_if.m
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
#include "miibus_if.h"

struct kobj_method miibus_readreg_method_default = {
	&miibus_readreg_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc miibus_readreg_desc = {
	0, &miibus_readreg_method_default
};

struct kobj_method miibus_writereg_method_default = {
	&miibus_writereg_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc miibus_writereg_desc = {
	0, &miibus_writereg_method_default
};

struct kobj_method miibus_statchg_method_default = {
	&miibus_statchg_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc miibus_statchg_desc = {
	0, &miibus_statchg_method_default
};

struct kobj_method miibus_linkchg_method_default = {
	&miibus_linkchg_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc miibus_linkchg_desc = {
	0, &miibus_linkchg_method_default
};

struct kobj_method miibus_mediainit_method_default = {
	&miibus_mediainit_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc miibus_mediainit_desc = {
	0, &miibus_mediainit_method_default
};

