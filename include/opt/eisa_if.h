/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/eisa/eisa_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _eisa_if_h_
#define _eisa_if_h_

/** @brief Unique descriptor for the EISA_ADD_INTR() method */
extern struct kobjop_desc eisa_add_intr_desc;
/** @brief A function implementing the EISA_ADD_INTR() method */
typedef int eisa_add_intr_t(bsd_device_t dev, bsd_device_t child, int irq, int trigger);

static __inline int EISA_ADD_INTR(bsd_device_t dev, bsd_device_t child, int irq,
                                  int trigger)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,eisa_add_intr);
	return ((eisa_add_intr_t *) _m)(dev, child, irq, trigger);
}

/** @brief Unique descriptor for the EISA_ADD_IOSPACE() method */
extern struct kobjop_desc eisa_add_iospace_desc;
/** @brief A function implementing the EISA_ADD_IOSPACE() method */
typedef int eisa_add_iospace_t(bsd_device_t dev, bsd_device_t child, u_long iobase,
                               u_long iosize, int flags);

static __inline int EISA_ADD_IOSPACE(bsd_device_t dev, bsd_device_t child,
                                     u_long iobase, u_long iosize, int flags)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,eisa_add_iospace);
	return ((eisa_add_iospace_t *) _m)(dev, child, iobase, iosize, flags);
}

/** @brief Unique descriptor for the EISA_ADD_MSPACE() method */
extern struct kobjop_desc eisa_add_mspace_desc;
/** @brief A function implementing the EISA_ADD_MSPACE() method */
typedef int eisa_add_mspace_t(bsd_device_t dev, bsd_device_t child, u_long mbase,
                              u_long msize, int flags);

static __inline int EISA_ADD_MSPACE(bsd_device_t dev, bsd_device_t child, u_long mbase,
                                    u_long msize, int flags)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,eisa_add_mspace);
	return ((eisa_add_mspace_t *) _m)(dev, child, mbase, msize, flags);
}

#endif /* _eisa_if_h_ */
