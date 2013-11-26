#if 0	// runsisi AT hust.edu.cn @2013/11/18
#define KDB 1
#define MAC 1
#define SMP 1
#define NEW_PCIB 1
#define AUDIT 1
#endif 	// ---------------------- @2013/11/18

// runsisi AT hust.edu.cn @2013/11/26
#undef _ISOC95_SOURCE
#undef _ISOC99_SOURCE
#undef _POSIX_SOURCE
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE
#undef _XOPEN_SOURCE_EXTENDED
#undef _LARGEFILE64_SOURCE
#undef _BSD_SOURCE
#undef _SVID_SOURCE
#undef _ATFILE_SOURCE

#undef _SYS_CDEFS_H_
//#undef _SYS_ERRNO_H_

#undef _ASM_GENERIC_ERRNO_H
#undef _TIME_H
#undef _SIGSET_H_types

#undef __unused
#undef __nonnull

#define _KERNEL 1
#define VIMAGE  1
// ---------------------- @2013/11/26
