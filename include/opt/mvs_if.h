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


#ifndef _mvs_if_h_
#define _mvs_if_h_

/** @brief Unique descriptor for the MVS_EDMA() method */
extern struct kobjop_desc mvs_edma_desc;
/** @brief A function implementing the MVS_EDMA() method */
typedef void mvs_edma_t(device_t dev, device_t child, int mode);

static __inline void MVS_EDMA(device_t dev, device_t child, int mode)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,mvs_edma);
	((mvs_edma_t *) _m)(dev, child, mode);
}

#endif /* _mvs_if_h_ */
