/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/mvs/mvs_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include "mvs_if.h"

struct kobj_method mvs_edma_method_default = {
	&mvs_edma_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc mvs_edma_desc = {
	0, &mvs_edma_method_default
};

