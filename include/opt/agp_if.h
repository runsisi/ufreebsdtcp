/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/agp/agp_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _agp_if_h_
#define _agp_if_h_

/** @brief Unique descriptor for the AGP_GET_APERTURE() method */
extern struct kobjop_desc agp_get_aperture_desc;
/** @brief A function implementing the AGP_GET_APERTURE() method */
typedef bsd_uint32_t agp_get_aperture_t(bsd_device_t dev);

static __inline bsd_uint32_t AGP_GET_APERTURE(bsd_device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_get_aperture);
	return ((agp_get_aperture_t *) _m)(dev);
}

/** @brief Unique descriptor for the AGP_SET_APERTURE() method */
extern struct kobjop_desc agp_set_aperture_desc;
/** @brief A function implementing the AGP_SET_APERTURE() method */
typedef int agp_set_aperture_t(bsd_device_t dev, bsd_uint32_t aperture);

static __inline int AGP_SET_APERTURE(bsd_device_t dev, bsd_uint32_t aperture)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_set_aperture);
	return ((agp_set_aperture_t *) _m)(dev, aperture);
}

/** @brief Unique descriptor for the AGP_BIND_PAGE() method */
extern struct kobjop_desc agp_bind_page_desc;
/** @brief A function implementing the AGP_BIND_PAGE() method */
typedef int agp_bind_page_t(bsd_device_t dev, bsd_vm_offset_t offset,
                            bsd_vm_offset_t physical);

static __inline int AGP_BIND_PAGE(bsd_device_t dev, bsd_vm_offset_t offset,
                                  bsd_vm_offset_t physical)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_bind_page);
	return ((agp_bind_page_t *) _m)(dev, offset, physical);
}

/** @brief Unique descriptor for the AGP_UNBIND_PAGE() method */
extern struct kobjop_desc agp_unbind_page_desc;
/** @brief A function implementing the AGP_UNBIND_PAGE() method */
typedef int agp_unbind_page_t(bsd_device_t dev, bsd_vm_offset_t offset);

static __inline int AGP_UNBIND_PAGE(bsd_device_t dev, bsd_vm_offset_t offset)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_unbind_page);
	return ((agp_unbind_page_t *) _m)(dev, offset);
}

/** @brief Unique descriptor for the AGP_FLUSH_TLB() method */
extern struct kobjop_desc agp_flush_tlb_desc;
/** @brief A function implementing the AGP_FLUSH_TLB() method */
typedef void agp_flush_tlb_t(bsd_device_t dev);

static __inline void AGP_FLUSH_TLB(bsd_device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_flush_tlb);
	((agp_flush_tlb_t *) _m)(dev);
}

/** @brief Unique descriptor for the AGP_ENABLE() method */
extern struct kobjop_desc agp_enable_desc;
/** @brief A function implementing the AGP_ENABLE() method */
typedef int agp_enable_t(bsd_device_t dev, bsd_uint32_t mode);

static __inline int AGP_ENABLE(bsd_device_t dev, bsd_uint32_t mode)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_enable);
	return ((agp_enable_t *) _m)(dev, mode);
}

/** @brief Unique descriptor for the AGP_ALLOC_MEMORY() method */
extern struct kobjop_desc agp_alloc_memory_desc;
/** @brief A function implementing the AGP_ALLOC_MEMORY() method */
typedef struct agp_memory * agp_alloc_memory_t(bsd_device_t dev, int type,
                                               bsd_vm_size_t size);

static __inline struct agp_memory * AGP_ALLOC_MEMORY(bsd_device_t dev, int type,
                                                     bsd_vm_size_t size)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_alloc_memory);
	return ((agp_alloc_memory_t *) _m)(dev, type, size);
}

/** @brief Unique descriptor for the AGP_FREE_MEMORY() method */
extern struct kobjop_desc agp_free_memory_desc;
/** @brief A function implementing the AGP_FREE_MEMORY() method */
typedef int agp_free_memory_t(bsd_device_t dev, struct agp_memory *mem);

static __inline int AGP_FREE_MEMORY(bsd_device_t dev, struct agp_memory *mem)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_free_memory);
	return ((agp_free_memory_t *) _m)(dev, mem);
}

/** @brief Unique descriptor for the AGP_BIND_MEMORY() method */
extern struct kobjop_desc agp_bind_memory_desc;
/** @brief A function implementing the AGP_BIND_MEMORY() method */
typedef int agp_bind_memory_t(bsd_device_t dev, struct agp_memory *mem,
                              bsd_vm_offset_t offset);

static __inline int AGP_BIND_MEMORY(bsd_device_t dev, struct agp_memory *mem,
                                    bsd_vm_offset_t offset)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_bind_memory);
	return ((agp_bind_memory_t *) _m)(dev, mem, offset);
}

/** @brief Unique descriptor for the AGP_UNBIND_MEMORY() method */
extern struct kobjop_desc agp_unbind_memory_desc;
/** @brief A function implementing the AGP_UNBIND_MEMORY() method */
typedef int agp_unbind_memory_t(bsd_device_t dev, struct agp_memory *handle);

static __inline int AGP_UNBIND_MEMORY(bsd_device_t dev, struct agp_memory *handle)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_unbind_memory);
	return ((agp_unbind_memory_t *) _m)(dev, handle);
}

/** @brief Unique descriptor for the AGP_CHIPSET_FLUSH() method */
extern struct kobjop_desc agp_chipset_flush_desc;
/** @brief A function implementing the AGP_CHIPSET_FLUSH() method */
typedef int agp_chipset_flush_t(bsd_device_t dev);

static __inline int AGP_CHIPSET_FLUSH(bsd_device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,agp_chipset_flush);
	return ((agp_chipset_flush_t *) _m)(dev);
}

#endif /* _agp_if_h_ */
