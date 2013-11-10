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


#ifndef _virtio_bus_if_h_
#define _virtio_bus_if_h_


struct vq_alloc_info;

/** @brief Unique descriptor for the VIRTIO_BUS_NEGOTIATE_FEATURES() method */
extern struct kobjop_desc virtio_bus_negotiate_features_desc;
/** @brief A function implementing the VIRTIO_BUS_NEGOTIATE_FEATURES() method */
typedef bsd_uint64_t virtio_bus_negotiate_features_t(bsd_device_t dev,
                                                 bsd_uint64_t child_features);

static __inline bsd_uint64_t VIRTIO_BUS_NEGOTIATE_FEATURES(bsd_device_t dev,
                                                       bsd_uint64_t child_features)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_negotiate_features);
	return ((virtio_bus_negotiate_features_t *) _m)(dev, child_features);
}

/** @brief Unique descriptor for the VIRTIO_BUS_WITH_FEATURE() method */
extern struct kobjop_desc virtio_bus_with_feature_desc;
/** @brief A function implementing the VIRTIO_BUS_WITH_FEATURE() method */
typedef int virtio_bus_with_feature_t(bsd_device_t dev, bsd_uint64_t feature);

static __inline int VIRTIO_BUS_WITH_FEATURE(bsd_device_t dev, bsd_uint64_t feature)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_with_feature);
	return ((virtio_bus_with_feature_t *) _m)(dev, feature);
}

/** @brief Unique descriptor for the VIRTIO_BUS_ALLOC_VIRTQUEUES() method */
extern struct kobjop_desc virtio_bus_alloc_virtqueues_desc;
/** @brief A function implementing the VIRTIO_BUS_ALLOC_VIRTQUEUES() method */
typedef int virtio_bus_alloc_virtqueues_t(bsd_device_t dev, int flags, int nvqs,
                                          struct vq_alloc_info *info);

static __inline int VIRTIO_BUS_ALLOC_VIRTQUEUES(bsd_device_t dev, int flags,
                                                int nvqs,
                                                struct vq_alloc_info *info)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_alloc_virtqueues);
	return ((virtio_bus_alloc_virtqueues_t *) _m)(dev, flags, nvqs, info);
}

/** @brief Unique descriptor for the VIRTIO_BUS_SETUP_INTR() method */
extern struct kobjop_desc virtio_bus_setup_intr_desc;
/** @brief A function implementing the VIRTIO_BUS_SETUP_INTR() method */
typedef int virtio_bus_setup_intr_t(bsd_device_t dev, enum intr_type type);

static __inline int VIRTIO_BUS_SETUP_INTR(bsd_device_t dev, enum intr_type type)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_setup_intr);
	return ((virtio_bus_setup_intr_t *) _m)(dev, type);
}

/** @brief Unique descriptor for the VIRTIO_BUS_STOP() method */
extern struct kobjop_desc virtio_bus_stop_desc;
/** @brief A function implementing the VIRTIO_BUS_STOP() method */
typedef void virtio_bus_stop_t(bsd_device_t dev);

static __inline void VIRTIO_BUS_STOP(bsd_device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_stop);
	((virtio_bus_stop_t *) _m)(dev);
}

/** @brief Unique descriptor for the VIRTIO_BUS_REINIT() method */
extern struct kobjop_desc virtio_bus_reinit_desc;
/** @brief A function implementing the VIRTIO_BUS_REINIT() method */
typedef int virtio_bus_reinit_t(bsd_device_t dev, bsd_uint64_t features);

static __inline int VIRTIO_BUS_REINIT(bsd_device_t dev, bsd_uint64_t features)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_reinit);
	return ((virtio_bus_reinit_t *) _m)(dev, features);
}

/** @brief Unique descriptor for the VIRTIO_BUS_REINIT_COMPLETE() method */
extern struct kobjop_desc virtio_bus_reinit_complete_desc;
/** @brief A function implementing the VIRTIO_BUS_REINIT_COMPLETE() method */
typedef void virtio_bus_reinit_complete_t(bsd_device_t dev);

static __inline void VIRTIO_BUS_REINIT_COMPLETE(bsd_device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_reinit_complete);
	((virtio_bus_reinit_complete_t *) _m)(dev);
}

/** @brief Unique descriptor for the VIRTIO_BUS_NOTIFY_VQ() method */
extern struct kobjop_desc virtio_bus_notify_vq_desc;
/** @brief A function implementing the VIRTIO_BUS_NOTIFY_VQ() method */
typedef void virtio_bus_notify_vq_t(bsd_device_t dev, bsd_uint16_t queue);

static __inline void VIRTIO_BUS_NOTIFY_VQ(bsd_device_t dev, bsd_uint16_t queue)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_notify_vq);
	((virtio_bus_notify_vq_t *) _m)(dev, queue);
}

/** @brief Unique descriptor for the VIRTIO_BUS_READ_DEVICE_CONFIG() method */
extern struct kobjop_desc virtio_bus_read_device_config_desc;
/** @brief A function implementing the VIRTIO_BUS_READ_DEVICE_CONFIG() method */
typedef void virtio_bus_read_device_config_t(bsd_device_t dev, bus_size_t offset,
                                             void *dst, int len);

static __inline void VIRTIO_BUS_READ_DEVICE_CONFIG(bsd_device_t dev,
                                                   bus_size_t offset, void *dst,
                                                   int len)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_read_device_config);
	((virtio_bus_read_device_config_t *) _m)(dev, offset, dst, len);
}

/** @brief Unique descriptor for the VIRTIO_BUS_WRITE_DEVICE_CONFIG() method */
extern struct kobjop_desc virtio_bus_write_device_config_desc;
/** @brief A function implementing the VIRTIO_BUS_WRITE_DEVICE_CONFIG() method */
typedef void virtio_bus_write_device_config_t(bsd_device_t dev, bus_size_t offset,
                                              void *src, int len);

static __inline void VIRTIO_BUS_WRITE_DEVICE_CONFIG(bsd_device_t dev,
                                                    bus_size_t offset,
                                                    void *src, int len)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,virtio_bus_write_device_config);
	((virtio_bus_write_device_config_t *) _m)(dev, offset, src, len);
}

#endif /* _virtio_bus_if_h_ */
