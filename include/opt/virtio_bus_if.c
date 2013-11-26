/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/virtio/virtio_bus_if.m
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
#include <machine/bsd_bus.h>
#include "virtio_bus_if.h"

struct kobj_method virtio_bus_negotiate_features_method_default = {
	&virtio_bus_negotiate_features_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_negotiate_features_desc = {
	0, &virtio_bus_negotiate_features_method_default
};

struct kobj_method virtio_bus_with_feature_method_default = {
	&virtio_bus_with_feature_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_with_feature_desc = {
	0, &virtio_bus_with_feature_method_default
};

struct kobj_method virtio_bus_alloc_virtqueues_method_default = {
	&virtio_bus_alloc_virtqueues_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_alloc_virtqueues_desc = {
	0, &virtio_bus_alloc_virtqueues_method_default
};

struct kobj_method virtio_bus_setup_intr_method_default = {
	&virtio_bus_setup_intr_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_setup_intr_desc = {
	0, &virtio_bus_setup_intr_method_default
};

struct kobj_method virtio_bus_stop_method_default = {
	&virtio_bus_stop_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_stop_desc = {
	0, &virtio_bus_stop_method_default
};

struct kobj_method virtio_bus_reinit_method_default = {
	&virtio_bus_reinit_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_reinit_desc = {
	0, &virtio_bus_reinit_method_default
};

struct kobj_method virtio_bus_reinit_complete_method_default = {
	&virtio_bus_reinit_complete_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_reinit_complete_desc = {
	0, &virtio_bus_reinit_complete_method_default
};

struct kobj_method virtio_bus_notify_vq_method_default = {
	&virtio_bus_notify_vq_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_notify_vq_desc = {
	0, &virtio_bus_notify_vq_method_default
};

struct kobj_method virtio_bus_read_device_config_method_default = {
	&virtio_bus_read_device_config_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_read_device_config_desc = {
	0, &virtio_bus_read_device_config_method_default
};

struct kobj_method virtio_bus_write_device_config_method_default = {
	&virtio_bus_write_device_config_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc virtio_bus_write_device_config_desc = {
	0, &virtio_bus_write_device_config_method_default
};

