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

#include <sys/bsd_param.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_kobj.h>
#include <sys/bsd_bus.h>
#include "virtio_if.h"


static int
virtio_default_config_change(device_t dev)
{
	return (0);
}

struct kobj_method virtio_config_change_method_default = {
	&virtio_config_change_desc, (kobjop_t) virtio_default_config_change
};

struct kobjop_desc virtio_config_change_desc = {
	0, &virtio_config_change_method_default
};

