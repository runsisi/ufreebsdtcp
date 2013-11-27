/*
 * opt_pre_global.h
 *
 *  Created on: 2013/11/26
 *      Author: runsisi AT hust.edu.cn
 */

#ifndef OPT_PRE_GLOBAL_H_
#define OPT_PRE_GLOBAL_H_

#define _KERNEL

#include <sys/bsd_errno.h>
#include <sys/_bsd_sigset.h>

#undef _KERNEL

#define _ASM_GENERIC_ERRNO_H
#define _SIGSET_H_types

#define _ISOC95_SOURCE          1
#define _ISOC99_SOURCE          1
#define _POSIX_SOURCE           1
#define _POSIX_C_SOURCE         200809L
#define _XOPEN_SOURCE           700
#define _XOPEN_SOURCE_EXTENDED  1
#define _LARGEFILE64_SOURCE     1
#define _BSD_SOURCE             1
#define _SVID_SOURCE            1
#define _ATFILE_SOURCE          1

#endif /* OPT_PRE_GLOBAL_H_ */
