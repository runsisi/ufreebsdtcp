/*
 * bsd_adapter.c
 *
 *  Created on: 2013/10/22
 *      Author: runsisi AT hust.edu.cn
 */

#include <string.h>
#include <stdlib.h>

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <net/vnet.h>

VNET_DEFINE(int, ip_defttl) = IPDEFTTL;

uint32_t arc4random(void)
{
    return (uint32_t)random();
}

int
copystr(const void * kfaddr, void * kdaddr, size_t len, size_t * lencopied)
{
    strncpy(kdaddr, kfaddr, len);
    if (lencopied != NULL)
        *lencopied = len;
    return 0;
}

int
bsd_copyinstr(const void * udaddr, void * kaddr, size_t len, size_t * lencopied)
{
    strncpy(kaddr, udaddr, len);
    if (lencopied != NULL)
        *lencopied = len;
    return 0;
}

int
copyin(const void * udaddr, void * kaddr, size_t len)
{
    bcopy(udaddr, kaddr, len);
    return 0;
}

int
copyin_nofault(const void * udaddr, void * kaddr, size_t len)
{
    return copyin(udaddr, kaddr, len);
}

int
copyout(const void * kaddr, void * udaddr, size_t len)
{
    bcopy(kaddr, udaddr, len);
    return 0;
}

int
copyout_nofault(const void * kaddr, void * udaddr, size_t len)
{
    return copyout(kaddr, udaddr, len);
}

int
read_random(void *buf, int len)
{
    int32_t rnd = 0;
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
