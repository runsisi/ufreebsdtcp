/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/mii/miibus_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _miibus_if_h_
#define _miibus_if_h_

/** @brief Unique descriptor for the MIIBUS_READREG() method */
extern struct kobjop_desc miibus_readreg_desc;
/** @brief A function implementing the MIIBUS_READREG() method */
typedef int miibus_readreg_t(bsd_device_t dev, int phy, int reg);

static __inline int MIIBUS_READREG(bsd_device_t dev, int phy, int reg)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,miibus_readreg);
	return ((miibus_readreg_t *) _m)(dev, phy, reg);
}

/** @brief Unique descriptor for the MIIBUS_WRITEREG() method */
extern struct kobjop_desc miibus_writereg_desc;
/** @brief A function implementing the MIIBUS_WRITEREG() method */
typedef int miibus_writereg_t(bsd_device_t dev, int phy, int reg, int val);

static __inline int MIIBUS_WRITEREG(bsd_device_t dev, int phy, int reg, int val)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,miibus_writereg);
	return ((miibus_writereg_t *) _m)(dev, phy, reg, val);
}

/** @brief Unique descriptor for the MIIBUS_STATCHG() method */
extern struct kobjop_desc miibus_statchg_desc;
/** @brief A function implementing the MIIBUS_STATCHG() method */
typedef void miibus_statchg_t(bsd_device_t dev);

static __inline void MIIBUS_STATCHG(bsd_device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,miibus_statchg);
	((miibus_statchg_t *) _m)(dev);
}

/** @brief Unique descriptor for the MIIBUS_LINKCHG() method */
extern struct kobjop_desc miibus_linkchg_desc;
/** @brief A function implementing the MIIBUS_LINKCHG() method */
typedef void miibus_linkchg_t(bsd_device_t dev);

static __inline void MIIBUS_LINKCHG(bsd_device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,miibus_linkchg);
	((miibus_linkchg_t *) _m)(dev);
}

/** @brief Unique descriptor for the MIIBUS_MEDIAINIT() method */
extern struct kobjop_desc miibus_mediainit_desc;
/** @brief A function implementing the MIIBUS_MEDIAINIT() method */
typedef void miibus_mediainit_t(bsd_device_t dev);

static __inline void MIIBUS_MEDIAINIT(bsd_device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,miibus_mediainit);
	((miibus_mediainit_t *) _m)(dev);
}

#endif /* _miibus_if_h_ */
