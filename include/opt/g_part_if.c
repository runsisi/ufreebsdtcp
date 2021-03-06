/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/geom/part/g_part_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/bsd_param.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_kobj.h>
#include <sys/bsd_param.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_sbuf.h>
#include <sys/bsd_bus.h>
#include <machine/bsd_bus.h>
#include <sys/bsd_systm.h>
#include <geom/geom.h>
#include <geom/part/g_part.h>
#include "g_part_if.h"


static void
default_fullname(struct g_part_table *table,
    struct g_part_entry *entry, struct sbuf *sb, const char *pfx)
{
	char buf[32];

	sbuf_printf(sb, "%s%s", pfx,
	    G_PART_NAME(table, entry, buf, sizeof(buf)));
}

static int
default_precheck(struct g_part_table *t __unused,
    enum g_part_ctl r __unused, struct g_part_parms *p __unused)
{
	return (0);
}

static int
default_resize(struct g_part_table *t __unused,
    struct g_part_entry *e __unused, struct g_part_parms *p __unused)
{
	return (ENOSYS);
}

static int
default_recover(struct g_part_table *t __unused)
{
	return (ENOSYS);
}

struct kobj_method g_part_add_method_default = {
	&g_part_add_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_add_desc = {
	0, &g_part_add_method_default
};

struct kobj_method g_part_bootcode_method_default = {
	&g_part_bootcode_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_bootcode_desc = {
	0, &g_part_bootcode_method_default
};

struct kobj_method g_part_create_method_default = {
	&g_part_create_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_create_desc = {
	0, &g_part_create_method_default
};

struct kobj_method g_part_destroy_method_default = {
	&g_part_destroy_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_destroy_desc = {
	0, &g_part_destroy_method_default
};

struct kobj_method g_part_dumpconf_method_default = {
	&g_part_dumpconf_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_dumpconf_desc = {
	0, &g_part_dumpconf_method_default
};

struct kobj_method g_part_dumpto_method_default = {
	&g_part_dumpto_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_dumpto_desc = {
	0, &g_part_dumpto_method_default
};

struct kobj_method g_part_fullname_method_default = {
	&g_part_fullname_desc, (kobjop_t) default_fullname
};

struct kobjop_desc g_part_fullname_desc = {
	0, &g_part_fullname_method_default
};

struct kobj_method g_part_modify_method_default = {
	&g_part_modify_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_modify_desc = {
	0, &g_part_modify_method_default
};

struct kobj_method g_part_resize_method_default = {
	&g_part_resize_desc, (kobjop_t) default_resize
};

struct kobjop_desc g_part_resize_desc = {
	0, &g_part_resize_method_default
};

struct kobj_method g_part_name_method_default = {
	&g_part_name_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_name_desc = {
	0, &g_part_name_method_default
};

struct kobj_method g_part_precheck_method_default = {
	&g_part_precheck_desc, (kobjop_t) default_precheck
};

struct kobjop_desc g_part_precheck_desc = {
	0, &g_part_precheck_method_default
};

struct kobj_method g_part_probe_method_default = {
	&g_part_probe_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_probe_desc = {
	0, &g_part_probe_method_default
};

struct kobj_method g_part_read_method_default = {
	&g_part_read_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_read_desc = {
	0, &g_part_read_method_default
};

struct kobj_method g_part_recover_method_default = {
	&g_part_recover_desc, (kobjop_t) default_recover
};

struct kobjop_desc g_part_recover_desc = {
	0, &g_part_recover_method_default
};

struct kobj_method g_part_setunset_method_default = {
	&g_part_setunset_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_setunset_desc = {
	0, &g_part_setunset_method_default
};

struct kobj_method g_part_type_method_default = {
	&g_part_type_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_type_desc = {
	0, &g_part_type_method_default
};

struct kobj_method g_part_write_method_default = {
	&g_part_write_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_part_write_desc = {
	0, &g_part_write_method_default
};

