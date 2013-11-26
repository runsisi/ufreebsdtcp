/*
 * opt_pre_global.h
 *
 *  Created on: 2013/11/26
 *      Author: runsisi AT hust.edu.cn
 */

#ifndef OPT_PRE_GLOBAL_H_
#define OPT_PRE_GLOBAL_H_

# undef  _ISOC95_SOURCE
# define _ISOC95_SOURCE 1
# undef  _ISOC99_SOURCE
# define _ISOC99_SOURCE 1
# undef  _POSIX_SOURCE
# define _POSIX_SOURCE  1
# undef  _POSIX_C_SOURCE
# define _POSIX_C_SOURCE    200809L
# undef  _XOPEN_SOURCE
# define _XOPEN_SOURCE  700
# undef  _XOPEN_SOURCE_EXTENDED
# define _XOPEN_SOURCE_EXTENDED 1
# undef  _LARGEFILE64_SOURCE
# define _LARGEFILE64_SOURCE    1
# undef  _BSD_SOURCE
//# define _BSD_SOURCE    1
# undef  _SVID_SOURCE
# define _SVID_SOURCE   1
# undef  _ATFILE_SOURCE
# define _ATFILE_SOURCE 1

#include <sys/bsd_select.h>

#endif /* OPT_PRE_GLOBAL_H_ */
