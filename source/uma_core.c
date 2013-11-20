/*-
 * Copyright (c) 2002-2005, 2009 Jeffrey Roberson <jeff@FreeBSD.org>
 * Copyright (c) 2004, 2005 Bosko Milekic <bmilekic@FreeBSD.org>
 * Copyright (c) 2004-2006 Robert N. M. Watson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * uma_core.c  Implementation of the Universal Memory allocator
 *
 * This allocator is intended to replace the multitude of similar object caches
 * in the standard FreeBSD kernel.  The intent is to be flexible as well as
 * effecient.  A primary design goal is to return unused memory to the rest of
 * the system.  This will make the system as a whole more flexible due to the
 * ability to move memory to subsystems which most need it instead of leaving
 * pools of reserved memory unused.
 *
 * The basic ideas stem from similar slab/zone based allocators whose algorithms
 * are well known.
 *
 */

/*
 * TODO:
 *	- Improve memory usage for large allocations
 *	- Investigate cache size adjustments
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/vm/uma_core.c 242365 2012-10-30 17:05:12Z mdf $");

/* I should really use ktr.. */
/*
#define UMA_DEBUG 1
#define UMA_DEBUG_ALLOC 1
#define UMA_DEBUG_ALLOC_1 1
*/

#include "opt_ddb.h"
#include "opt_param.h"

#include <string.h>
#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_types.h>
#include <sys/bsd_queue.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_ktr.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_sysctl.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_sbuf.h>
#include <sys/bsd_smp.h>
#include <sys/bsd_vmmeter.h>

#include <vm/vm.h>
#include <vm/vm_object.h>
#include <vm/vm_page.h>
#include <vm/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_extern.h>
#include <vm/uma.h>
#include <vm/uma_int.h>
#include <vm/uma_dbg.h>

//#include <ddb/ddb.h>

/*
 * This is the zone and keg from which all zones are spawned.  The idea is that
 * even the zone & keg heads are allocated from the allocator, so we use the
 * bss section to bootstrap us.
 */
static struct uma_zone masterzone_z;
static uma_zone_t zones = &masterzone_z;

/*
 * This structure is passed as the zone ctor arg so that I don't have to create
 * a special allocation function just for zones.
 */
struct uma_zctor_args {
	const char *name;
	bsd_size_t size;
	uma_ctor ctor;
	uma_dtor dtor;
	uma_init uminit;
	uma_fini fini;
	uma_keg_t keg;
	int align;
	bsd_uint32_t flags;
};

/*
 * Flags and enumerations to be passed to internal functions.
 */
enum zfreeskip { SKIP_NONE, SKIP_DTOR, SKIP_FINI };

#define	ZFREE_STATFAIL	0x00000001	/* Update zone failure statistic. */
#define	ZFREE_STATFREE	0x00000002	/* Update zone free statistic. */

/* Prototypes.. */

static int zone_ctor(void *, int, void *, int);
static void zone_dtor(void *, int, void *);
static int zero_init(void *, int, int);

static void *zone_alloc_item(uma_zone_t, void *, int);
static void zone_free_item(uma_zone_t, void *, void *, enum zfreeskip, int);

/*
 * Zero fill initializer
 *
 * Arguments/Returns follow uma_init specifications
 */
static int
zero_init(void *mem, int size, int flags)
{
	bzero(mem, size);
	return (0);
}

/*
 * Zone header ctor.  This initializes all fields, locks, etc.
 *
 * Arguments/Returns follow uma_ctor specifications
 *	udata  Actually uma_zctor_args
 */
static int
zone_ctor(void *mem, int size, void *udata, int flags)
{
	struct uma_zctor_args *arg = udata;
	uma_zone_t zone = mem;

	bzero(zone, size);
	zone->uz_name = arg->name;
	zone->uz_ctor = arg->ctor;
	zone->uz_dtor = arg->dtor;
	zone->uz_slab = NULL;
	zone->uz_init = arg->uminit;
	zone->uz_fini = arg->fini;
	zone->uz_allocs = 0;
	zone->uz_frees = 0;
	zone->uz_fails = 0;
	zone->uz_sleeps = 0;
	zone->uz_fills = zone->uz_count = 0;
	zone->uz_flags = 0;
	zone->uz_size = arg->size;

	return (0);
}

/*
 * Zone header dtor.
 *
 * Arguments/Returns follow uma_dtor specifications
 *	udata  unused
 */
static void
zone_dtor(void *arg, int size, void *udata)
{
	uma_zone_t zone;

	zone = (uma_zone_t)arg;
}

/* Public functions */
/* See uma.h */
void
uma_startup(void *bootmem, int boot_pages)
{
	struct uma_zctor_args args;

#ifdef UMA_DEBUG
	printf("Creating uma zone headers zone and keg.\n");
#endif
	args.name = "UMA Zones";
	args.size = sizeof(struct uma_zone);
	args.ctor = zone_ctor;
	args.dtor = zone_dtor;
	args.uminit = zero_init;
	args.fini = NULL;
	args.keg = NULL;
	args.align = 32 - 1;
	args.flags = UMA_ZFLAG_INTERNAL;
	/* The initial zone has no Per cpu queues so it's smaller */
	zone_ctor(zones, sizeof(struct uma_zone), &args, M_WAITOK);

#ifdef UMA_DEBUG
	printf("UMA startup complete.\n");
#endif
}

/* See uma.h */
uma_zone_t
uma_zcreate(const char *name, bsd_size_t size, uma_ctor ctor, uma_dtor dtor,
		uma_init uminit, uma_fini fini, int align, bsd_uint32_t flags)

{
	struct uma_zctor_args args;

	/* This stuff is essential for the zone ctor */
	args.name = name;
	args.size = size;
	args.ctor = ctor;
	args.dtor = dtor;
	args.uminit = uminit;
	args.fini = fini;
	args.align = align;
	args.flags = flags;
	args.keg = NULL;

	return (zone_alloc_item(zones, &args, M_WAITOK));
}

/* See uma.h */
uma_zone_t
uma_zsecond_create(char *name, uma_ctor ctor, uma_dtor dtor,
		    uma_init zinit, uma_fini zfini, uma_zone_t master)
{
	struct uma_zctor_args args;

	args.name = name;
	args.size = master->uz_size;
	args.ctor = ctor;
	args.dtor = dtor;
	args.uminit = zinit;
	args.fini = zfini;

	/* XXX Attaches only one keg of potentially many. */
	return (zone_alloc_item(zones, &args, M_WAITOK));
}

/* See uma.h */
void
uma_zdestroy(uma_zone_t zone)
{

	zone_free_item(zones, zone, NULL, SKIP_NONE, ZFREE_STATFREE);
}

/* See uma.h */
void *
uma_zalloc_arg(uma_zone_t zone, void *udata, int flags)
{
	void *item;

	item = zone_alloc_item(zone, udata, flags);
	return (item);
}

/*
 * Allocates an item for an internal zone
 *
 * Arguments
 *	zone   The zone to alloc for.
 *	udata  The data to be passed to the constructor.
 *	flags  M_WAITOK, M_NOWAIT, M_ZERO.
 *
 * Returns
 *	NULL if there is no memory and M_NOWAIT is set
 *	An item if successful
 */

static void *
zone_alloc_item(uma_zone_t zone, void *udata, int flags)
{
	void *item;

	item = NULL;

#ifdef UMA_DEBUG_ALLOC
	printf("INTERNAL: Allocating one item from %s(%p)\n", zone->uz_name, zone);
#endif

	item = DPS_GetUUB("zone alloc", zone->uz_size);
	if (NULL == item)
	{
	    zone->uz_fails++;
	    return NULL;
	}

	zone->uz_allocs++;

	/*
	 * We have to call both the zone's init (not the keg's init)
	 * and the zone's ctor.  This is because the item is going from
	 * a keg slab directly to the user, and the user is expecting it
	 * to be both zone-init'd as well as zone-ctor'd.
	 */
	if (zone->uz_init != NULL) {
		if (zone->uz_init(item, zone->uz_size, flags) != 0) {
			zone_free_item(zone, item, udata, SKIP_FINI,
			    ZFREE_STATFAIL | ZFREE_STATFREE);
			return (NULL);
		}
	}
	if (zone->uz_ctor != NULL) {
		if (zone->uz_ctor(item, zone->uz_size, udata, flags) != 0) {
			zone_free_item(zone, item, udata, SKIP_DTOR,
			    ZFREE_STATFAIL | ZFREE_STATFREE);
			return (NULL);
		}
	}
	if (flags & M_ZERO)
		bzero(item, zone->uz_size);

	return (item);
}

/* See uma.h */
void
uma_zfree_arg(uma_zone_t zone, void *item, void *udata)
{
    /* uma_zfree(..., NULL) does nothing, to match free(9). */
    if (item == NULL)
            return;

	if (zone->uz_dtor)
		zone->uz_dtor(item, zone->uz_size, udata);

	/*
	 * If nothing else caught this, we'll just do an internal free.
	 */
	zone_free_item(zone, item, udata, SKIP_DTOR, ZFREE_STATFREE);

	return;
}

/*
 * Frees an item to an INTERNAL zone or allocates a free bucket
 *
 * Arguments:
 *	zone   The zone to free to
 *	item   The item we're freeing
 *	udata  User supplied data for the dtor
 *	skip   Skip dtors and finis
 */
static void
zone_free_item(uma_zone_t zone, void *item, void *udata,
    enum zfreeskip skip, int flags)
{
    if (skip < SKIP_DTOR && zone->uz_dtor)
        zone->uz_dtor(item, zone->uz_size, udata);

    if (skip < SKIP_FINI && zone->uz_fini)
        zone->uz_fini(item, zone->uz_size);

    if (flags & ZFREE_STATFAIL)
        zone->uz_fails++;
    if (flags & ZFREE_STATFREE)
        zone->uz_frees++;

    DPS_RetUUB(item);
}

/* See uma.h */
int
uma_zone_set_max(uma_zone_t zone, int nitems)
{

	return (nitems);
}

/* See uma.h */
int
uma_zone_get_max(uma_zone_t zone)
{

	return (0);
}

/* See uma.h */
int
uma_zone_get_cur(uma_zone_t zone)
{

	return (0);
}

/* See uma.h */
/* XXX uk_freef is not actually used with the zone locked */
void
uma_zone_set_freef(uma_zone_t zone, uma_free freef)
{

}

/* See uma.h */
/* XXX uk_allocf is not actually used with the zone locked */
void
uma_zone_set_allocf(uma_zone_t zone, uma_alloc allocf)
{

}

/* See uma.h */
bsd_uint32_t *
uma_find_refcnt(uma_zone_t zone, void *item)
{

	return 0;
}

// runsisi AT hust.edu.cn @2013/11/08
static void
uma_statup_init(void *dummy)
{
    uma_startup(NULL, 0);
}

SYSINIT(vm_mem, SI_SUB_VM, SI_ORDER_FIRST, uma_statup_init, NULL);
// ---------------------- @2013/11/08
