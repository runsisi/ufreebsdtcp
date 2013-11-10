/*-
 * Fowler / Noll / Vo Hash (FNV Hash)
 * http://www.isthe.com/chongo/tech/comp/fnv/
 *
 * This is an implementation of the algorithms posted above.
 * This file is placed in the public domain by Peter Wemm.
 *
 * $FreeBSD: release/9.2.0/sys/sys/fnv_hash.h 248235 2013-03-13 10:45:36Z ae $
 */
#ifndef _SYS_FNV_HASH_H_
#define	_SYS_FNV_HASH_H_

typedef bsd_uint32_t Fnv32_t;
typedef bsd_uint64_t Fnv64_t;

#define FNV1_32_INIT ((Fnv32_t) 33554467UL)
#define FNV1_64_INIT ((Fnv64_t) 0xcbf29ce484222325ULL)

#define FNV_32_PRIME ((Fnv32_t) 0x01000193UL)
#define FNV_64_PRIME ((Fnv64_t) 0x100000001b3ULL)

static __inline Fnv32_t
fnv_32_buf(const void *buf, bsd_size_t len, Fnv32_t hval)
{
	const bsd_uint8_t *s = (const bsd_uint8_t *)buf;

	while (len-- != 0) {
		hval *= FNV_32_PRIME;
		hval ^= *s++;
	}
	return hval;
}

static __inline Fnv32_t
fnv_32_str(const char *str, Fnv32_t hval)
{
	const bsd_uint8_t *s = (const bsd_uint8_t *)str;
	Fnv32_t c;

	while ((c = *s++) != 0) {
		hval *= FNV_32_PRIME;
		hval ^= c;
	}
	return hval;
}

static __inline Fnv64_t
fnv_64_buf(const void *buf, bsd_size_t len, Fnv64_t hval)
{
	const bsd_uint8_t *s = (const bsd_uint8_t *)buf;

	while (len-- != 0) {
		hval *= FNV_64_PRIME;
		hval ^= *s++;
	}
	return hval;
}

static __inline Fnv64_t
fnv_64_str(const char *str, Fnv64_t hval)
{
	const bsd_uint8_t *s = (const bsd_uint8_t *)str;
	bsd_u_register_t c;		 /* 32 bit on i386, 64 bit on alpha,ia64 */

	while ((c = *s++) != 0) {
		hval *= FNV_64_PRIME;
		hval ^= c;
	}
	return hval;
}
#endif /* _SYS_FNV_HASH_H_ */
