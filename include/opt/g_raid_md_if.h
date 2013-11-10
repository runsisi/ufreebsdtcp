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


#ifndef _g_raid_md_if_h_
#define _g_raid_md_if_h_


#define G_RAID_MD_TASTE_FAIL		-1
#define G_RAID_MD_TASTE_EXISTING	 0
#define G_RAID_MD_TASTE_NEW		 1

/** @brief Unique descriptor for the G_RAID_MD_CREATE() method */
extern struct kobjop_desc g_raid_md_create_desc;
/** @brief A function implementing the G_RAID_MD_CREATE() method */
typedef int g_raid_md_create_t(struct g_raid_md_object *md, struct g_class *mp,
                               struct g_geom **gp);

static __inline int G_RAID_MD_CREATE(struct g_raid_md_object *md,
                                     struct g_class *mp, struct g_geom **gp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_create);
	return ((g_raid_md_create_t *) _m)(md, mp, gp);
}

/** @brief Unique descriptor for the G_RAID_MD_CREATE_REQ() method */
extern struct kobjop_desc g_raid_md_create_req_desc;
/** @brief A function implementing the G_RAID_MD_CREATE_REQ() method */
typedef int g_raid_md_create_req_t(struct g_raid_md_object *md,
                                   struct g_class *mp, struct gctl_req *req,
                                   struct g_geom **gp);

static __inline int G_RAID_MD_CREATE_REQ(struct g_raid_md_object *md,
                                         struct g_class *mp,
                                         struct gctl_req *req,
                                         struct g_geom **gp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_create_req);
	return ((g_raid_md_create_req_t *) _m)(md, mp, req, gp);
}

/** @brief Unique descriptor for the G_RAID_MD_TASTE() method */
extern struct kobjop_desc g_raid_md_taste_desc;
/** @brief A function implementing the G_RAID_MD_TASTE() method */
typedef int g_raid_md_taste_t(struct g_raid_md_object *md, struct g_class *mp,
                              struct g_consumer *cp, struct g_geom **gp);

static __inline int G_RAID_MD_TASTE(struct g_raid_md_object *md,
                                    struct g_class *mp, struct g_consumer *cp,
                                    struct g_geom **gp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_taste);
	return ((g_raid_md_taste_t *) _m)(md, mp, cp, gp);
}

/** @brief Unique descriptor for the G_RAID_MD_CTL() method */
extern struct kobjop_desc g_raid_md_ctl_desc;
/** @brief A function implementing the G_RAID_MD_CTL() method */
typedef int g_raid_md_ctl_t(struct g_raid_md_object *md, struct gctl_req *req);

static __inline int G_RAID_MD_CTL(struct g_raid_md_object *md,
                                  struct gctl_req *req)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_ctl);
	return ((g_raid_md_ctl_t *) _m)(md, req);
}

/** @brief Unique descriptor for the G_RAID_MD_EVENT() method */
extern struct kobjop_desc g_raid_md_event_desc;
/** @brief A function implementing the G_RAID_MD_EVENT() method */
typedef int g_raid_md_event_t(struct g_raid_md_object *md,
                              struct g_raid_disk *disk, u_int event);

static __inline int G_RAID_MD_EVENT(struct g_raid_md_object *md,
                                    struct g_raid_disk *disk, u_int event)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_event);
	return ((g_raid_md_event_t *) _m)(md, disk, event);
}

/** @brief Unique descriptor for the G_RAID_MD_VOLUME_EVENT() method */
extern struct kobjop_desc g_raid_md_volume_event_desc;
/** @brief A function implementing the G_RAID_MD_VOLUME_EVENT() method */
typedef int g_raid_md_volume_event_t(struct g_raid_md_object *md,
                                     struct g_raid_volume *vol, u_int event);

static __inline int G_RAID_MD_VOLUME_EVENT(struct g_raid_md_object *md,
                                           struct g_raid_volume *vol,
                                           u_int event)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_volume_event);
	return ((g_raid_md_volume_event_t *) _m)(md, vol, event);
}

/** @brief Unique descriptor for the G_RAID_MD_WRITE() method */
extern struct kobjop_desc g_raid_md_write_desc;
/** @brief A function implementing the G_RAID_MD_WRITE() method */
typedef int g_raid_md_write_t(struct g_raid_md_object *md,
                              struct g_raid_volume *vol,
                              struct g_raid_subdisk *sd,
                              struct g_raid_disk *disk);

static __inline int G_RAID_MD_WRITE(struct g_raid_md_object *md,
                                    struct g_raid_volume *vol,
                                    struct g_raid_subdisk *sd,
                                    struct g_raid_disk *disk)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_write);
	return ((g_raid_md_write_t *) _m)(md, vol, sd, disk);
}

/** @brief Unique descriptor for the G_RAID_MD_FAIL_DISK() method */
extern struct kobjop_desc g_raid_md_fail_disk_desc;
/** @brief A function implementing the G_RAID_MD_FAIL_DISK() method */
typedef int g_raid_md_fail_disk_t(struct g_raid_md_object *md,
                                  struct g_raid_subdisk *sd,
                                  struct g_raid_disk *disk);

static __inline int G_RAID_MD_FAIL_DISK(struct g_raid_md_object *md,
                                        struct g_raid_subdisk *sd,
                                        struct g_raid_disk *disk)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_fail_disk);
	return ((g_raid_md_fail_disk_t *) _m)(md, sd, disk);
}

/** @brief Unique descriptor for the G_RAID_MD_FREE_DISK() method */
extern struct kobjop_desc g_raid_md_free_disk_desc;
/** @brief A function implementing the G_RAID_MD_FREE_DISK() method */
typedef int g_raid_md_free_disk_t(struct g_raid_md_object *md,
                                  struct g_raid_disk *disk);

static __inline int G_RAID_MD_FREE_DISK(struct g_raid_md_object *md,
                                        struct g_raid_disk *disk)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_free_disk);
	return ((g_raid_md_free_disk_t *) _m)(md, disk);
}

/** @brief Unique descriptor for the G_RAID_MD_FREE_VOLUME() method */
extern struct kobjop_desc g_raid_md_free_volume_desc;
/** @brief A function implementing the G_RAID_MD_FREE_VOLUME() method */
typedef int g_raid_md_free_volume_t(struct g_raid_md_object *md,
                                    struct g_raid_volume *vol);

static __inline int G_RAID_MD_FREE_VOLUME(struct g_raid_md_object *md,
                                          struct g_raid_volume *vol)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_free_volume);
	return ((g_raid_md_free_volume_t *) _m)(md, vol);
}

/** @brief Unique descriptor for the G_RAID_MD_FREE() method */
extern struct kobjop_desc g_raid_md_free_desc;
/** @brief A function implementing the G_RAID_MD_FREE() method */
typedef int g_raid_md_free_t(struct g_raid_md_object *md);

static __inline int G_RAID_MD_FREE(struct g_raid_md_object *md)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)md)->ops,g_raid_md_free);
	return ((g_raid_md_free_t *) _m)(md);
}

#endif /* _g_raid_md_if_h_ */
