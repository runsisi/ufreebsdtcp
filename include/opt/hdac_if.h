/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   /usr/src/sys/dev/sound/pci/hda/hdac_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _hdac_if_h_
#define _hdac_if_h_

/** @brief Unique descriptor for the HDAC_GET_MTX() method */
extern struct kobjop_desc hdac_get_mtx_desc;
/** @brief A function implementing the HDAC_GET_MTX() method */
typedef struct mtx * hdac_get_mtx_t(device_t dev, device_t child);

static __inline struct mtx * HDAC_GET_MTX(device_t dev, device_t child)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_get_mtx);
	return ((hdac_get_mtx_t *) _m)(dev, child);
}

/** @brief Unique descriptor for the HDAC_CODEC_COMMAND() method */
extern struct kobjop_desc hdac_codec_command_desc;
/** @brief A function implementing the HDAC_CODEC_COMMAND() method */
typedef uint32_t hdac_codec_command_t(device_t dev, device_t child,
                                      uint32_t verb);

static __inline uint32_t HDAC_CODEC_COMMAND(device_t dev, device_t child,
                                            uint32_t verb)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_codec_command);
	return ((hdac_codec_command_t *) _m)(dev, child, verb);
}

/** @brief Unique descriptor for the HDAC_STREAM_ALLOC() method */
extern struct kobjop_desc hdac_stream_alloc_desc;
/** @brief A function implementing the HDAC_STREAM_ALLOC() method */
typedef int hdac_stream_alloc_t(device_t dev, device_t child, int dir,
                                int format, int stripe, uint32_t **dmapos);

static __inline int HDAC_STREAM_ALLOC(device_t dev, device_t child, int dir,
                                      int format, int stripe, uint32_t **dmapos)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_stream_alloc);
	return ((hdac_stream_alloc_t *) _m)(dev, child, dir, format, stripe, dmapos);
}

/** @brief Unique descriptor for the HDAC_STREAM_FREE() method */
extern struct kobjop_desc hdac_stream_free_desc;
/** @brief A function implementing the HDAC_STREAM_FREE() method */
typedef void hdac_stream_free_t(device_t dev, device_t child, int dir,
                                int stream);

static __inline void HDAC_STREAM_FREE(device_t dev, device_t child, int dir,
                                      int stream)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_stream_free);
	((hdac_stream_free_t *) _m)(dev, child, dir, stream);
}

/** @brief Unique descriptor for the HDAC_STREAM_START() method */
extern struct kobjop_desc hdac_stream_start_desc;
/** @brief A function implementing the HDAC_STREAM_START() method */
typedef int hdac_stream_start_t(device_t dev, device_t child, int dir,
                                int stream, bus_addr_t buf, int blksz,
                                int blkcnt);

static __inline int HDAC_STREAM_START(device_t dev, device_t child, int dir,
                                      int stream, bus_addr_t buf, int blksz,
                                      int blkcnt)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_stream_start);
	return ((hdac_stream_start_t *) _m)(dev, child, dir, stream, buf, blksz, blkcnt);
}

/** @brief Unique descriptor for the HDAC_STREAM_STOP() method */
extern struct kobjop_desc hdac_stream_stop_desc;
/** @brief A function implementing the HDAC_STREAM_STOP() method */
typedef void hdac_stream_stop_t(device_t dev, device_t child, int dir,
                                int stream);

static __inline void HDAC_STREAM_STOP(device_t dev, device_t child, int dir,
                                      int stream)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_stream_stop);
	((hdac_stream_stop_t *) _m)(dev, child, dir, stream);
}

/** @brief Unique descriptor for the HDAC_STREAM_RESET() method */
extern struct kobjop_desc hdac_stream_reset_desc;
/** @brief A function implementing the HDAC_STREAM_RESET() method */
typedef void hdac_stream_reset_t(device_t dev, device_t child, int dir,
                                 int stream);

static __inline void HDAC_STREAM_RESET(device_t dev, device_t child, int dir,
                                       int stream)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_stream_reset);
	((hdac_stream_reset_t *) _m)(dev, child, dir, stream);
}

/** @brief Unique descriptor for the HDAC_STREAM_GETPTR() method */
extern struct kobjop_desc hdac_stream_getptr_desc;
/** @brief A function implementing the HDAC_STREAM_GETPTR() method */
typedef uint32_t hdac_stream_getptr_t(device_t dev, device_t child, int dir,
                                      int stream);

static __inline uint32_t HDAC_STREAM_GETPTR(device_t dev, device_t child,
                                            int dir, int stream)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_stream_getptr);
	return ((hdac_stream_getptr_t *) _m)(dev, child, dir, stream);
}

/** @brief Unique descriptor for the HDAC_STREAM_INTR() method */
extern struct kobjop_desc hdac_stream_intr_desc;
/** @brief A function implementing the HDAC_STREAM_INTR() method */
typedef void hdac_stream_intr_t(device_t dev, int dir, int stream);

static __inline void HDAC_STREAM_INTR(device_t dev, int dir, int stream)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_stream_intr);
	((hdac_stream_intr_t *) _m)(dev, dir, stream);
}

/** @brief Unique descriptor for the HDAC_UNSOL_ALLOC() method */
extern struct kobjop_desc hdac_unsol_alloc_desc;
/** @brief A function implementing the HDAC_UNSOL_ALLOC() method */
typedef int hdac_unsol_alloc_t(device_t dev, device_t child, int wanted);

static __inline int HDAC_UNSOL_ALLOC(device_t dev, device_t child, int wanted)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_unsol_alloc);
	return ((hdac_unsol_alloc_t *) _m)(dev, child, wanted);
}

/** @brief Unique descriptor for the HDAC_UNSOL_FREE() method */
extern struct kobjop_desc hdac_unsol_free_desc;
/** @brief A function implementing the HDAC_UNSOL_FREE() method */
typedef void hdac_unsol_free_t(device_t dev, device_t child, int tag);

static __inline void HDAC_UNSOL_FREE(device_t dev, device_t child, int tag)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_unsol_free);
	((hdac_unsol_free_t *) _m)(dev, child, tag);
}

/** @brief Unique descriptor for the HDAC_UNSOL_INTR() method */
extern struct kobjop_desc hdac_unsol_intr_desc;
/** @brief A function implementing the HDAC_UNSOL_INTR() method */
typedef void hdac_unsol_intr_t(device_t dev, uint32_t resp);

static __inline void HDAC_UNSOL_INTR(device_t dev, uint32_t resp)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_unsol_intr);
	((hdac_unsol_intr_t *) _m)(dev, resp);
}

/** @brief Unique descriptor for the HDAC_PINDUMP() method */
extern struct kobjop_desc hdac_pindump_desc;
/** @brief A function implementing the HDAC_PINDUMP() method */
typedef void hdac_pindump_t(device_t dev);

static __inline void HDAC_PINDUMP(device_t dev)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,hdac_pindump);
	((hdac_pindump_t *) _m)(dev);
}

#endif /* _hdac_if_h_ */
