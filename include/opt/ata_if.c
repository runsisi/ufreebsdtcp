/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/ata/ata_if.m
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
#include <sys/bsd_kernel.h>
#include <sys/bsd_param.h>
#include <sys/bsd_types.h>
#include <sys/bsd_callout.h>
#include <sys/bsd_sema.h>
#include <sys/bsd_taskqueue.h>
#include <vm/uma.h>
#include <machine/bsd_bus.h>
#include <sys/bsd_ata.h>
#include <dev/ata/ata-all.h>
#include "ata_if.h"


static int ata_null_locking(device_t dev, int mode)
{
    struct ata_channel *ch = device_get_softc(dev);

    return ch->unit;
}

struct kobj_method ata_locking_method_default = {
	&ata_locking_desc, (kobjop_t) ata_null_locking
};

struct kobjop_desc ata_locking_desc = {
	0, &ata_locking_method_default
};


static int ata_null_setmode(device_t dev, int target, int mode)
{

	if (mode > ATA_PIO_MAX)
		return (ATA_PIO_MAX);
	return (mode);
}

struct kobj_method ata_setmode_method_default = {
	&ata_setmode_desc, (kobjop_t) ata_null_setmode
};

struct kobjop_desc ata_setmode_desc = {
	0, &ata_setmode_method_default
};


static int ata_null_getrev(device_t dev, int target)
{
	return (0);
}

struct kobj_method ata_getrev_method_default = {
	&ata_getrev_desc, (kobjop_t) ata_null_getrev
};

struct kobjop_desc ata_getrev_desc = {
	0, &ata_getrev_method_default
};

struct kobj_method ata_reset_method_default = {
	&ata_reset_desc, (kobjop_t) ata_generic_reset
};

struct kobjop_desc ata_reset_desc = {
	0, &ata_reset_method_default
};

struct kobj_method ata_reinit_method_default = {
	&ata_reinit_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc ata_reinit_desc = {
	0, &ata_reinit_method_default
};

