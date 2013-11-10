/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)stat.h	8.12 (Berkeley) 6/16/95
 * $FreeBSD: release/9.2.0/sys/sys/stat.h 239901 2012-08-30 10:23:27Z kib $
 */

#ifndef _BSD_SYS_STAT_H_
#define	_BSD_SYS_STAT_H_

#include <sys/bsd_cdefs.h>
#include <sys/_bsd_timespec.h>
#include <sys/_bsd_types.h>

#ifndef _BSD_BLKSIZE_T_DECLARED
typedef	__bsd_blksize_t	bsd_blksize_t;
#define	_BSD_BLKSIZE_T_DECLARED
#endif

#ifndef _BSD_BLKCNT_T_DECLARED
typedef	__bsd_blkcnt_t	blkcnt_t;
#define	_BSD_BLKCNT_T_DECLARED
#endif

#ifndef _BSD_DEV_T_DECLARED
typedef	__bsd_dev_t		dev_t;
#define	_BSD_DEV_T_DECLARED
#endif

#ifndef _BSD_FFLAGS_T_DECLARED
typedef	__bsd_fflags_t	bsd_fflags_t;
#define	_BSD_FFLAGS_T_DECLARED
#endif

#ifndef _BSD_GID_T_DECLARED
typedef	__bsd_gid_t		bsd_gid_t;
#define	_BSD_GID_T_DECLARED
#endif

#ifndef _BSD_INO_T_DECLARED
typedef	__bsd_ino_t		bsd_ino_t;
#define	_BSD_INO_T_DECLARED
#endif

#ifndef _BSD_MODE_T_DECLARED
typedef	__bsd_mode_t	bsd_mode_t;
#define	_BSD_MODE_T_DECLARED
#endif

#ifndef _BSD_NLINK_T_DECLARED
typedef	__bsd_nlink_t	bsd_nlink_t;
#define	_BSD_NLINK_T_DECLARED
#endif

#ifndef _BSD_OFF_T_DECLARED
typedef	__bsd_off_t		bsd_off_t;
#define	_BSD_OFF_T_DECLARED
#endif

#ifndef _BSD_UID_T_DECLARED
typedef	__bsd_uid_t		bsd_uid_t;
#define	_BSD_UID_T_DECLARED
#endif

#if !defined(_KERNEL) && __BSD_VISIBLE
/*
 * XXX We get miscellaneous namespace pollution with this.
 */
#include <sys/bsd_time.h>
#endif

#ifdef _KERNEL
struct ostat {
	__bsd_uint16_t st_dev;		/* inode's device */
	bsd_ino_t	  st_ino;		/* inode's number */
	bsd_mode_t	  st_mode;		/* inode protection mode */
	bsd_nlink_t	  st_nlink;		/* number of hard links */
	__bsd_uint16_t st_uid;		/* user ID of the file's owner */
	__bsd_uint16_t st_gid;		/* group ID of the file's group */
	__bsd_uint16_t st_rdev;		/* device type */
	__bsd_int32_t st_size;		/* file size, in bytes */
	struct	bsd_timespec st_atim;	/* time of last access */
	struct	bsd_timespec st_mtim;	/* time of last data modification */
	struct	bsd_timespec st_ctim;	/* time of last file status change */
	__bsd_int32_t st_blksize;		/* optimal blocksize for I/O */
	__bsd_int32_t st_blocks;		/* blocks allocated for file */
	bsd_fflags_t  st_flags;		/* user defined flags for file */
	__bsd_uint32_t st_gen;		/* file generation number */
};
#endif

struct bsd_stat {
	__bsd_dev_t   st_dev;		/* inode's device */
	bsd_ino_t	  st_ino;		/* inode's number */
	bsd_mode_t	  st_mode;		/* inode protection mode */
	bsd_nlink_t	  st_nlink;		/* number of hard links */
	bsd_uid_t	  st_uid;		/* user ID of the file's owner */
	bsd_gid_t	  st_gid;		/* group ID of the file's group */
	__bsd_dev_t   st_rdev;		/* device type */
	struct	bsd_timespec st_atim;	/* time of last access */
	struct	bsd_timespec st_mtim;	/* time of last data modification */
	struct	bsd_timespec st_ctim;	/* time of last file status change */
	bsd_off_t	  st_size;		/* file size, in bytes */
	blkcnt_t st_blocks;		/* blocks allocated for file */
	bsd_blksize_t st_blksize;		/* optimal blocksize for I/O */
	bsd_fflags_t  st_flags;		/* user defined flags for file */
	__bsd_uint32_t st_gen;		/* file generation number */
	__bsd_int32_t st_lspare;
	struct bsd_timespec st_birthtim;	/* time of file creation */
	/*
	 * Explicitly pad st_birthtim to 16 bytes so that the size of
	 * struct stat is backwards compatible.  We use bitfields instead
	 * of an array of chars so that this doesn't require a C99 compiler
	 * to compile if the size of the padding is 0.  We use 2 bitfields
	 * to cover up to 64 bits on 32-bit machines.  We assume that
	 * CHAR_BIT is 8...
	 */
	unsigned int :(8 / 2) * (16 - (int)sizeof(struct bsd_timespec));
	unsigned int :(8 / 2) * (16 - (int)sizeof(struct bsd_timespec));
};

#ifdef _KERNEL
struct nstat {
	__bsd_dev_t   st_dev;		/* inode's device */
	bsd_ino_t	  st_ino;		/* inode's number */
	__bsd_uint32_t st_mode;		/* inode protection mode */
	__bsd_uint32_t st_nlink;		/* number of hard links */
	bsd_uid_t	  st_uid;		/* user ID of the file's owner */
	bsd_gid_t	  st_gid;		/* group ID of the file's group */
	__bsd_dev_t   st_rdev;		/* device type */
	struct	bsd_timespec st_atim;	/* time of last access */
	struct	bsd_timespec st_mtim;	/* time of last data modification */
	struct	bsd_timespec st_ctim;	/* time of last file status change */
	bsd_off_t	  st_size;		/* file size, in bytes */
	blkcnt_t st_blocks;		/* blocks allocated for file */
	bsd_blksize_t st_blksize;		/* optimal blocksize for I/O */
	bsd_fflags_t  st_flags;		/* user defined flags for file */
	__bsd_uint32_t st_gen;		/* file generation number */
	struct bsd_timespec st_birthtim;	/* time of file creation */
	/*
	 * See above about the following padding.
	 */
	unsigned int :(8 / 2) * (16 - (int)sizeof(struct bsd_timespec));
	unsigned int :(8 / 2) * (16 - (int)sizeof(struct bsd_timespec));
};
#endif

#ifndef _KERNEL
#define	st_atime		st_atim.tv_sec
#define	st_mtime		st_mtim.tv_sec
#define	st_ctime		st_ctim.tv_sec
#if __BSD_VISIBLE
#define	st_birthtime		st_birthtim.tv_sec
#endif

/* For compatibility. */
#if __BSD_VISIBLE
#define	st_atimespec		st_atim
#define	st_mtimespec		st_mtim
#define	st_ctimespec		st_ctim
#define	st_birthtimespec	st_birthtim
#endif
#endif /* !_KERNEL */

#define	BSD_S_ISUID	0004000			/* set user id on execution */
#define	BSD_S_ISGID	0002000			/* set group id on execution */
#if __BSD_VISIBLE
#define	BSD_S_ISTXT	0001000			/* sticky bit */
#endif

#define	BSD_S_IRWXU	0000700			/* RWX mask for owner */
#define	BSD_S_IRUSR	0000400			/* R for owner */
#define	BSD_S_IWUSR	0000200			/* W for owner */
#define	BSD_S_IXUSR	0000100			/* X for owner */

#if __BSD_VISIBLE
#define	BSD_S_IREAD		BSD_S_IRUSR
#define	BSD_S_IWRITE	BSD_S_IWUSR
#define	BSD_S_IEXEC		BSD_S_IXUSR
#endif

#define	BSD_S_IRWXG	0000070			/* RWX mask for group */
#define	BSD_S_IRGRP	0000040			/* R for group */
#define	BSD_S_IWGRP	0000020			/* W for group */
#define	BSD_S_IXGRP	0000010			/* X for group */

#define	BSD_S_IRWXO	0000007			/* RWX mask for other */
#define	BSD_S_IROTH	0000004			/* R for other */
#define	BSD_S_IWOTH	0000002			/* W for other */
#define	BSD_S_IXOTH	0000001			/* X for other */

#if __XSI_VISIBLE
#define	BSD_S_IFMT	 0170000		/* type of file mask */
#define	BSD_S_IFIFO	 0010000		/* named pipe (fifo) */
#define	BSD_S_IFCHR	 0020000		/* character special */
#define	BSD_S_IFDIR	 0040000		/* directory */
#define	BSD_S_IFBLK	 0060000		/* block special */
#define	BSD_S_IFREG	 0100000		/* regular */
#define	BSD_S_IFLNK	 0120000		/* symbolic link */
#define	BSD_S_IFSOCK 0140000		/* socket */
#define	BSD_S_ISVTX	 0001000		/* save swapped text even after use */
#endif
#if __BSD_VISIBLE
#define	BSD_S_IFWHT  0160000		/* whiteout */
#endif

#define	BSD_S_ISDIR(m)	(((m) & 0170000) == 0040000)	/* directory */
#define	BSD_S_ISCHR(m)	(((m) & 0170000) == 0020000)	/* char special */
#define	BSD_S_ISBLK(m)	(((m) & 0170000) == 0060000)	/* block special */
#define	BSD_S_ISREG(m)	(((m) & 0170000) == 0100000)	/* regular file */
#define	BSD_S_ISFIFO(m)	(((m) & 0170000) == 0010000)	/* fifo or socket */
#if __POSIX_VISIBLE >= 200112
#define	BSD_S_ISLNK(m)	(((m) & 0170000) == 0120000)	/* symbolic link */
#define	BSD_S_ISSOCK(m)	(((m) & 0170000) == 0140000)	/* socket */
#endif
#if __BSD_VISIBLE
#define	BSD_S_ISWHT(m)	(((m) & 0170000) == 0160000)	/* whiteout */
#endif

#if __BSD_VISIBLE
#define	BSD_ACCESSPERMS	(BSD_S_IRWXU|BSD_S_IRWXG|BSD_S_IRWXO)	/* 0777 */
							/* 7777 */
#define	BSD_ALLPERMS	(BSD_S_ISUID|BSD_S_ISGID|BSD_S_ISTXT|BSD_S_IRWXU|BSD_S_IRWXG|BSD_S_IRWXO)
							/* 0666 */
#define	BSD_DEFFILEMODE	(BSD_S_IRUSR|BSD_S_IWUSR|BSD_S_IRGRP|BSD_S_IWGRP|BSD_S_IROTH|BSD_S_IWOTH)

#define BSD_S_BLKSIZE	512		/* block size used in the stat struct */

/*
 * Definitions of flags stored in file flags word.
 *
 * Super-user and owner changeable flags.
 */
#define	BSD_UF_SETTABLE	0x0000ffff	/* mask of owner changeable flags */
#define	BSD_UF_NODUMP	0x00000001	/* do not dump file */
#define	BSD_UF_IMMUTABLE	0x00000002	/* file may not be changed */
#define	BSD_UF_APPEND	0x00000004	/* writes to file may only append */
#define BSD_UF_OPAQUE	0x00000008	/* directory is opaque wrt. union */
#define BSD_UF_NOUNLINK	0x00000010	/* file may not be removed or renamed */
/*
 * Super-user changeable flags.
 */
#define	BSD_SF_SETTABLE	0xffff0000	/* mask of superuser changeable flags */
#define	BSD_SF_ARCHIVED	0x00010000	/* file is archived */
#define	BSD_SF_IMMUTABLE	0x00020000	/* file may not be changed */
#define	BSD_SF_APPEND	0x00040000	/* writes to file may only append */
#define	BSD_SF_NOUNLINK	0x00100000	/* file may not be removed or renamed */
#define	BSD_SF_SNAPSHOT	0x00200000	/* snapshot inode */

#ifdef _KERNEL
/*
 * Shorthand abbreviations of above.
 */
#define	BSD_OPAQUE		(BSD_UF_OPAQUE)
#define	BSD_APPEND		(BSD_UF_APPEND | BSD_SF_APPEND)
#define	BSD_IMMUTABLE	(BSD_UF_IMMUTABLE | BSD_SF_IMMUTABLE)
#define	BSD_NOUNLINK	(BSD_UF_NOUNLINK | BSD_SF_NOUNLINK)
#endif

#endif /* __BSD_VISIBLE */

#ifndef _KERNEL
__BEGIN_DECLS
#if __BSD_VISIBLE
int	chflags(const char *, unsigned long);
#endif
int	chmod(const char *, bsd_mode_t);
#if __BSD_VISIBLE
int	fchflags(int, unsigned long);
#endif
#if __POSIX_VISIBLE >= 200112
int	fchmod(int, bsd_mode_t);
#endif
#if __POSIX_VISIBLE >= 200809
int	fchmodat(int, const char *, bsd_mode_t, int);
#endif
int	fstat(int, struct bsd_stat *);
#if __BSD_VISIBLE
int	lchflags(const char *, int);
int	lchmod(const char *, bsd_mode_t);
#endif
#if __POSIX_VISIBLE >= 200112
int	lstat(const char * __restrict, struct bsd_stat * __restrict);
#endif
int	mkdir(const char *, bsd_mode_t);
int	mkfifo(const char *, bsd_mode_t);
#if !defined(_MKNOD_DECLARED) && __XSI_VISIBLE
int	mknod(const char *, bsd_mode_t, dev_t);
#define	_MKNOD_DECLARED
#endif
int	stat(const char * __restrict, struct bsd_stat * __restrict);
bsd_mode_t	umask(bsd_mode_t);
#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200809
int	fstatat(int, const char *, struct bsd_stat *, int);
int	mkdirat(int, const char *, bsd_mode_t);
int	mkfifoat(int, const char *, bsd_mode_t);
#endif
#if __BSD_VISIBLE || __XSI_VISIBLE >= 700
int	mknodat(int, const char *, bsd_mode_t, dev_t);
#endif
__END_DECLS
#endif /* !_KERNEL */

#endif /* !_SYS_STAT_H_ */
