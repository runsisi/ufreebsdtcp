/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/virtio/virtio_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <sys/bus.h>
#include "virtio_if.h"


static int
virtio_default_config_change(bsd_device_t dev)
{
	return (0);
}

struct kobj_method virtio_config_change_method_default = {
	&virtio_config_change_desc, (kobjop_t) virtio_default_config_change
};

struct kobjop_desc virtio_config_change_desc = {
	0, &virtio_config_change_method_default
};

