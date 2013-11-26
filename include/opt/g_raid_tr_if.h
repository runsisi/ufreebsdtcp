/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/geom/raid/g_raid_tr_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _g_raid_tr_if_h_
#define _g_raid_tr_if_h_


#define G_RAID_TR_TASTE_FAIL		-1
#define G_RAID_TR_TASTE_SUCCEED		 0

/** @brief Unique descriptor for the G_RAID_TR_TASTE() method */
extern struct kobjop_desc g_raid_tr_taste_desc;
/** @brief A function implementing the G_RAID_TR_TASTE() method */
typedef int g_raid_tr_taste_t(struct g_raid_tr_object *tr,
                              struct g_raid_volume *volume);

static __inline int G_RAID_TR_TASTE(struct g_raid_tr_object *tr,
                                    struct g_raid_volume *volume)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_taste);
	return ((g_raid_tr_taste_t *) _m)(tr, volume);
}

/** @brief Unique descriptor for the G_RAID_TR_EVENT() method */
extern struct kobjop_desc g_raid_tr_event_desc;
/** @brief A function implementing the G_RAID_TR_EVENT() method */
typedef int g_raid_tr_event_t(struct g_raid_tr_object *tr,
                              struct g_raid_subdisk *sd, u_int event);

static __inline int G_RAID_TR_EVENT(struct g_raid_tr_object *tr,
                                    struct g_raid_subdisk *sd, u_int event)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_event);
	return ((g_raid_tr_event_t *) _m)(tr, sd, event);
}

/** @brief Unique descriptor for the G_RAID_TR_START() method */
extern struct kobjop_desc g_raid_tr_start_desc;
/** @brief A function implementing the G_RAID_TR_START() method */
typedef int g_raid_tr_start_t(struct g_raid_tr_object *tr);

static __inline int G_RAID_TR_START(struct g_raid_tr_object *tr)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_start);
	return ((g_raid_tr_start_t *) _m)(tr);
}

/** @brief Unique descriptor for the G_RAID_TR_STOP() method */
extern struct kobjop_desc g_raid_tr_stop_desc;
/** @brief A function implementing the G_RAID_TR_STOP() method */
typedef int g_raid_tr_stop_t(struct g_raid_tr_object *tr);

static __inline int G_RAID_TR_STOP(struct g_raid_tr_object *tr)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_stop);
	return ((g_raid_tr_stop_t *) _m)(tr);
}

/** @brief Unique descriptor for the G_RAID_TR_IOSTART() method */
extern struct kobjop_desc g_raid_tr_iostart_desc;
/** @brief A function implementing the G_RAID_TR_IOSTART() method */
typedef void g_raid_tr_iostart_t(struct g_raid_tr_object *tr, struct bio *bp);

static __inline void G_RAID_TR_IOSTART(struct g_raid_tr_object *tr,
                                       struct bio *bp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_iostart);
	((g_raid_tr_iostart_t *) _m)(tr, bp);
}

/** @brief Unique descriptor for the G_RAID_TR_IODONE() method */
extern struct kobjop_desc g_raid_tr_iodone_desc;
/** @brief A function implementing the G_RAID_TR_IODONE() method */
typedef void g_raid_tr_iodone_t(struct g_raid_tr_object *tr,
                                struct g_raid_subdisk *sd, struct bio *bp);

static __inline void G_RAID_TR_IODONE(struct g_raid_tr_object *tr,
                                      struct g_raid_subdisk *sd, struct bio *bp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_iodone);
	((g_raid_tr_iodone_t *) _m)(tr, sd, bp);
}

/** @brief Unique descriptor for the G_RAID_TR_KERNELDUMP() method */
extern struct kobjop_desc g_raid_tr_kerneldump_desc;
/** @brief A function implementing the G_RAID_TR_KERNELDUMP() method */
typedef int g_raid_tr_kerneldump_t(struct g_raid_tr_object *tr, void *virtual,
                                   vm_offset_t physical, off_t offset,
                                   size_t length);

static __inline int G_RAID_TR_KERNELDUMP(struct g_raid_tr_object *tr,
                                         void *virtual, vm_offset_t physical,
                                         off_t offset, size_t length)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_kerneldump);
	return ((g_raid_tr_kerneldump_t *) _m)(tr, virtual, physical, offset, length);
}

/** @brief Unique descriptor for the G_RAID_TR_LOCKED() method */
extern struct kobjop_desc g_raid_tr_locked_desc;
/** @brief A function implementing the G_RAID_TR_LOCKED() method */
typedef int g_raid_tr_locked_t(struct g_raid_tr_object *tr, void *argp);

static __inline int G_RAID_TR_LOCKED(struct g_raid_tr_object *tr, void *argp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_locked);
	return ((g_raid_tr_locked_t *) _m)(tr, argp);
}

/** @brief Unique descriptor for the G_RAID_TR_FREE() method */
extern struct kobjop_desc g_raid_tr_free_desc;
/** @brief A function implementing the G_RAID_TR_FREE() method */
typedef int g_raid_tr_free_t(struct g_raid_tr_object *tr);

static __inline int G_RAID_TR_FREE(struct g_raid_tr_object *tr)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_free);
	return ((g_raid_tr_free_t *) _m)(tr);
}

/** @brief Unique descriptor for the G_RAID_TR_IDLE() method */
extern struct kobjop_desc g_raid_tr_idle_desc;
/** @brief A function implementing the G_RAID_TR_IDLE() method */
typedef int g_raid_tr_idle_t(struct g_raid_tr_object *tr);

static __inline int G_RAID_TR_IDLE(struct g_raid_tr_object *tr)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)tr)->ops,g_raid_tr_idle);
	return ((g_raid_tr_idle_t *) _m)(tr);
}

#endif /* _g_raid_tr_if_h_ */
