#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/stack_protector.c 198295 2009-10-20 16:36:51Z ru $");

#include <sys/bsd_types.h>
#include <sys/bsd_param.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_libkern.h>

long __stack_chk_guard[8] = {};
void __stack_chk_fail(void);

void
__stack_chk_fail(void)
{

	panic("stack overflow detected; backtrace may be corrupted");
}

#define __arraycount(__x)	(sizeof(__x) / sizeof(__x[0]))
static void
__stack_chk_init(void *dummy __unused)
{
	size_t i;
	long guard[__arraycount(__stack_chk_guard)];

	arc4rand(guard, sizeof(guard), 0);
	for (i = 0; i < __arraycount(guard); i++)
		__stack_chk_guard[i] = guard[i];
}
SYSINIT(stack_chk, SI_SUB_RANDOM, SI_ORDER_ANY, __stack_chk_init, NULL);
