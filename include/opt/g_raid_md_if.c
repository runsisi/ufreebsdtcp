/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/geom/raid/g_raid_md_if.m
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
#include <geom/raid/g_raid.h>
#include "g_raid_md_if.h"


static int
g_raid_md_create_default(struct g_raid_md_object *md,
    struct g_class *mp, struct g_geom **gp)
{

	return (G_RAID_MD_TASTE_FAIL);
}

static int
g_raid_md_create_req_default(struct g_raid_md_object *md,
    struct g_class *mp, struct gctl_req *req, struct g_geom **gp)
{

	return (G_RAID_MD_CREATE(md, mp, gp));
}

static int
g_raid_md_ctl_default(struct g_raid_md_object *md,
    struct gctl_req *req)
{

	return (-1);
}

static int
g_raid_md_volume_event_default(struct g_raid_md_object *md,
    struct g_raid_volume *vol, u_int event)
{

	return (-1);
}

static int
g_raid_md_free_disk_default(struct g_raid_md_object *md,
    struct g_raid_volume *vol)
{

	return (0);
}

static int
g_raid_md_free_volume_default(struct g_raid_md_object *md,
    struct g_raid_volume *vol)
{

	return (0);
}

struct kobj_method g_raid_md_create_method_default = {
	&g_raid_md_create_desc, (kobjop_t) g_raid_md_create_default
};

struct kobjop_desc g_raid_md_create_desc = {
	0, &g_raid_md_create_method_default
};

struct kobj_method g_raid_md_create_req_method_default = {
	&g_raid_md_create_req_desc, (kobjop_t) g_raid_md_create_req_default
};

struct kobjop_desc g_raid_md_create_req_desc = {
	0, &g_raid_md_create_req_method_default
};

struct kobj_method g_raid_md_taste_method_default = {
	&g_raid_md_taste_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_md_taste_desc = {
	0, &g_raid_md_taste_method_default
};

struct kobj_method g_raid_md_ctl_method_default = {
	&g_raid_md_ctl_desc, (kobjop_t) g_raid_md_ctl_default
};

struct kobjop_desc g_raid_md_ctl_desc = {
	0, &g_raid_md_ctl_method_default
};

struct kobj_method g_raid_md_event_method_default = {
	&g_raid_md_event_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_md_event_desc = {
	0, &g_raid_md_event_method_default
};

struct kobj_method g_raid_md_volume_event_method_default = {
	&g_raid_md_volume_event_desc, (kobjop_t) g_raid_md_volume_event_default
};

struct kobjop_desc g_raid_md_volume_event_desc = {
	0, &g_raid_md_volume_event_method_default
};

struct kobj_method g_raid_md_write_method_default = {
	&g_raid_md_write_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_md_write_desc = {
	0, &g_raid_md_write_method_default
};

struct kobj_method g_raid_md_fail_disk_method_default = {
	&g_raid_md_fail_disk_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_md_fail_disk_desc = {
	0, &g_raid_md_fail_disk_method_default
};

struct kobj_method g_raid_md_free_disk_method_default = {
	&g_raid_md_free_disk_desc, (kobjop_t) g_raid_md_free_disk_default
};

struct kobjop_desc g_raid_md_free_disk_desc = {
	0, &g_raid_md_free_disk_method_default
};

struct kobj_method g_raid_md_free_volume_method_default = {
	&g_raid_md_free_volume_desc, (kobjop_t) g_raid_md_free_volume_default
};

struct kobjop_desc g_raid_md_free_volume_desc = {
	0, &g_raid_md_free_volume_method_default
};

struct kobj_method g_raid_md_free_method_default = {
	&g_raid_md_free_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc g_raid_md_free_desc = {
	0, &g_raid_md_free_method_default
};

