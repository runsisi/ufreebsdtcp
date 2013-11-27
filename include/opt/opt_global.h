#if 0	// runsisi AT hust.edu.cn @2013/11/18
#define KDB 1
#define MAC 1
#define SMP 1
#define NEW_PCIB 1
#define AUDIT 1
#endif 	// ---------------------- @2013/11/18

// runsisi AT hust.edu.cn @2013/11/26
//#undef _ASM_GENERIC_ERRNO_H

#undef __size_t
#undef errno

#undef _ANSI_SOURCE
#undef _C99_SOURCE
#undef _POSIX_SOURCE
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#define __FreeBSD__

#define _KERNEL     1
#define VIMAGE      1
// ---------------------- @2013/11/26
