/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/acpi_support/acpi_wmi_if.m
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
#include <contrib/dev/acpica/include/acpi.h>
#include "acpi_wmi_if.h"


static int
acpi_wmi_generic_provides_guid_string(device_t dev, const char* guid_string)
{
	return 0;
}

struct kobj_method acpi_wmi_provides_guid_string_method_default = {
	&acpi_wmi_provides_guid_string_desc, (kobjop_t) acpi_wmi_generic_provides_guid_string
};

struct kobjop_desc acpi_wmi_provides_guid_string_desc = {
	0, &acpi_wmi_provides_guid_string_method_default
};

struct kobj_method acpi_wmi_evaluate_call_method_default = {
	&acpi_wmi_evaluate_call_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_evaluate_call_desc = {
	0, &acpi_wmi_evaluate_call_method_default
};

struct kobj_method acpi_wmi_get_block_method_default = {
	&acpi_wmi_get_block_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_get_block_desc = {
	0, &acpi_wmi_get_block_method_default
};

struct kobj_method acpi_wmi_set_block_method_default = {
	&acpi_wmi_set_block_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_set_block_desc = {
	0, &acpi_wmi_set_block_method_default
};

struct kobj_method acpi_wmi_install_event_handler_method_default = {
	&acpi_wmi_install_event_handler_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_install_event_handler_desc = {
	0, &acpi_wmi_install_event_handler_method_default
};

struct kobj_method acpi_wmi_remove_event_handler_method_default = {
	&acpi_wmi_remove_event_handler_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_remove_event_handler_desc = {
	0, &acpi_wmi_remove_event_handler_method_default
};

struct kobj_method acpi_wmi_get_event_data_method_default = {
	&acpi_wmi_get_event_data_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_get_event_data_desc = {
	0, &acpi_wmi_get_event_data_method_default
};

