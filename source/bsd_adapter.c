/*
 * bsd_adapter.c
 *
 *  Created on: 2013Äê10ÔÂ22ÈÕ
 *      Author: runsisi AT hust.edu.cn
 */

#include <string.h>
#include <stdlib.h>

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <netinet/bsd_in.h>
#include <netinet/bsd_ip.h>

#include <net/vnet.h>

VNET_DEFINE(int, ip_defttl) = IPDEFTTL;

extern int bsd_param_init();
extern int bsd_uma_init();
extern int bsd_mbuf_init();
extern int bsd_callout_init();
extern int bsd_domain_init();

bsd_uint32_t arc4random(void)
{
    return (bsd_uint32_t)random();
}

int
copyin(const void * udaddr, void * kaddr, bsd_size_t len)
{
    bcopy(udaddr, kaddr, len);
    return 0;
}

int
copyin_nofault(const void * udaddr, void * kaddr, bsd_size_t len)
{
    return copyin(udaddr, kaddr, len);
}

int
copyout(const void * kaddr, void * udaddr, bsd_size_t len)
{
    bcopy(kaddr, udaddr, len);
    return 0;
}

int
copyout_nofault(const void * kaddr, void * udaddr, bsd_size_t len)
{
    return copyout(kaddr, udaddr, len);
}

int
read_random(void *buf, int len)
{
    bsd_int32_t rnd = 0;
    int res = len % 4;
    len >>= 2;
    while (len)
    {
        rnd = random();
        bcopy(&rnd, buf, 4);
        buf += 4;
        len >>= 2;
    }
    if (res)
    {
        rnd = random();
        bcopy(&rnd, buf, res);
    }
    return 0;
}

int
bsd_init()
{
    bsd_param_init();
    bsd_uma_init();
    bsd_mbuf_init();
    bsd_callout_init();
    bsd_domain_init();
    return 0;
}
