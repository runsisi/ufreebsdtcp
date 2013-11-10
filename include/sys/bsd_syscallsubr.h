/*-
 * Copyright (c) 2002 Ian Dowse.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: release/9.2.0/sys/sys/syscallsubr.h 244172 2012-12-13 06:17:05Z kib $
 */

#ifndef _SYS_SYSCALLSUBR_H_
#define _SYS_SYSCALLSUBR_H_

#include <sys/bsd_signal.h>
#include <sys/bsd_uio.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_mac.h>
#include <sys/bsd_mount.h>

struct file;
enum idtype;
struct bsd_itimerval;
struct image_args;
struct jail;
struct kevent;
struct kevent_copyops;
struct kld_file_stat;
struct ksiginfo;
struct mbuf;
struct bsd_msghdr;
struct msqid_ds;
struct ogetdirentries_args;
struct rlimit;
struct rusage;
union semun;
struct sendfile_args;
struct bsd_sockaddr;
struct bsd_stat;
struct thr_param;
struct __wrusage;

int	kern___getcwd(struct thread *td, u_char *buf, enum bsd_uio_seg bufseg,
	    u_int buflen);
int	kern_accept(struct thread *td, int s, struct bsd_sockaddr **name,
	    bsd_socklen_t *namelen, struct file **fp);
int	kern_access(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    int flags);
int	kern_accessat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, int flags, int mode);
int	kern_adjtime(struct thread *td, struct bsd_timeval *delta,
	    struct bsd_timeval *olddelta);
int	kern_alternate_path(struct thread *td, const char *prefix, const char *path,
	    enum bsd_uio_seg pathseg, char **pathbuf, int create, int dirfd);
int	kern_bind(struct thread *td, int fd, struct bsd_sockaddr *sa);
int	kern_chdir(struct thread *td, char *path, enum bsd_uio_seg pathseg);
int	kern_chmod(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    int mode);
int	kern_chown(struct thread *td, char *path, enum bsd_uio_seg pathseg, int uid,
	    int gid);
int	kern_clock_getres(struct thread *td, bsd_clockid_t clock_id,
	    struct bsd_timespec *ts);
int	kern_clock_gettime(struct thread *td, bsd_clockid_t clock_id,
	    struct bsd_timespec *ats);
int	kern_clock_settime(struct thread *td, bsd_clockid_t clock_id,
	    struct bsd_timespec *ats);
int	kern_close(struct thread *td, int fd);
int	kern_connect(struct thread *td, int fd, struct bsd_sockaddr *sa);
int	kern_eaccess(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    int flags);
int	kern_execve(struct thread *td, struct image_args *args,
	    struct mac *mac_p);
int	kern_fchmodat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, bsd_mode_t mode, int flag);
int	kern_fchownat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, int uid, int gid, int flag);
int	kern_fcntl(struct thread *td, int fd, int cmd, bsd_intptr_t arg);
int	kern_fhstatfs(struct thread *td, fhandle_t fh, struct statfs *buf);
int	kern_fstat(struct thread *td, int fd, struct bsd_stat *sbp);
int	kern_fstatfs(struct thread *td, int fd, struct statfs *buf);
int	kern_ftruncate(struct thread *td, int fd, bsd_off_t length);
int	kern_futimes(struct thread *td, int fd, struct bsd_timeval *tptr,
	    enum bsd_uio_seg tptrseg);
int	kern_getdirentries(struct thread *td, int fd, char *buf, u_int count,
	    long *basep);
int	kern_getfsstat(struct thread *td, struct statfs **buf, bsd_size_t bufsize,
	    enum bsd_uio_seg bufseg, int flags);
int	kern_getgroups(struct thread *td, u_int *ngrp, bsd_gid_t *groups);
int	kern_getitimer(struct thread *, u_int, struct bsd_itimerval *);
int	kern_getpeername(struct thread *td, int fd, struct bsd_sockaddr **sa,
	    bsd_socklen_t *alen);
int	kern_getrusage(struct thread *td, int who, struct rusage *rup);
int	kern_getsockname(struct thread *td, int fd, struct bsd_sockaddr **sa,
	    bsd_socklen_t *alen);
int	kern_getsockopt(struct thread *td, int s, int level, int name,
	    void *optval, enum bsd_uio_seg valseg, bsd_socklen_t *valsize);
int	kern_ioctl(struct thread *td, int fd, u_long com, caddr_t data);
int	kern_jail(struct thread *td, struct jail *j);
int	kern_jail_get(struct thread *td, struct uio *options, int flags);
int	kern_jail_set(struct thread *td, struct uio *options, int flags);
int	kern_kevent(struct thread *td, int fd, int nchanges, int nevents,
	    struct kevent_copyops *k_ops, const struct bsd_timespec *timeout);
int	kern_kldload(struct thread *td, const char *file, int *fileid);
int	kern_kldstat(struct thread *td, int fileid, struct kld_file_stat *stat);
int	kern_kldunload(struct thread *td, int fileid, int flags);
int	kern_lchown(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    int uid, int gid);
int	kern_link(struct thread *td, char *path, char *link,
	    enum bsd_uio_seg segflg);
int	kern_linkat(struct thread *td, int fd1, int fd2, char *path1,
	    char *path2, enum bsd_uio_seg segflg, int follow);
int	kern_lstat(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    struct bsd_stat *sbp);
int	kern_lutimes(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    struct bsd_timeval *tptr, enum bsd_uio_seg tptrseg);
int	kern_mkdir(struct thread *td, char *path, enum bsd_uio_seg segflg,
	    int mode);
int	kern_mkdirat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg segflg, int mode);
int	kern_mkfifo(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    int mode);
int	kern_mkfifoat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, int mode);
int	kern_mknod(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    int mode, int dev);
int	kern_mknodat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, int mode, int dev);
int	kern_msgctl(struct thread *, int, int, struct msqid_ds *);
int	kern_msgsnd(struct thread *, int, const void *, bsd_size_t, int, long);
int	kern_msgrcv(struct thread *, int, void *, bsd_size_t, long, int, long *);
int     kern_nanosleep(struct thread *td, struct bsd_timespec *rqt,
	    struct bsd_timespec *rmt);
int	kern_ogetdirentries(struct thread *td, struct ogetdirentries_args *uap,
	    long *ploff);
int	kern_open(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    int flags, int mode);
int	kern_openat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, int flags, int mode);
int	kern_pathconf(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    int name, u_long flags);
int	kern_pipe(struct thread *td, int fildes[2]);
int	kern_posix_fadvise(struct thread *td, int fd, bsd_off_t offset, bsd_off_t len,
	    int advice);
int	kern_posix_fallocate(struct thread *td, int fd, bsd_off_t offset,
	    bsd_off_t len);
int	kern_preadv(struct thread *td, int fd, struct uio *auio, bsd_off_t offset);
int	kern_pselect(struct thread *td, int nd, bsd_fd_set *in, bsd_fd_set *ou,
	    bsd_fd_set *ex, struct bsd_timeval *tvp, bsd_sigset_t *uset, int abi_nfdbits);
int	kern_ptrace(struct thread *td, int req, bsd_pid_t pid, void *addr,
	    int data);
int	kern_pwritev(struct thread *td, int fd, struct uio *auio, bsd_off_t offset);
int	kern_readlink(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    char *buf, enum bsd_uio_seg bufseg, bsd_size_t count);
int	kern_readlinkat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, char *buf, enum bsd_uio_seg bufseg, bsd_size_t count);
int	kern_readv(struct thread *td, int fd, struct uio *auio);
int	kern_recvit(struct thread *td, int s, struct bsd_msghdr *mp,
	    enum bsd_uio_seg fromseg, struct mbuf **controlp);
int	kern_rename(struct thread *td, char *from, char *to,
	    enum bsd_uio_seg pathseg);
int	kern_renameat(struct thread *td, int oldfd, char *old, int newfd,
	    char *new, enum bsd_uio_seg pathseg);
int	kern_rmdir(struct thread *td, char *path, enum bsd_uio_seg pathseg);
int	kern_rmdirat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg);
int	kern_sched_rr_get_interval(struct thread *td, bsd_pid_t pid,
	    struct bsd_timespec *ts);
int	kern_semctl(struct thread *td, int semid, int semnum, int cmd,
	    union semun *arg, bsd_register_t *rval);
int	kern_select(struct thread *td, int nd, bsd_fd_set *fd_in, bsd_fd_set *fd_ou,
	    bsd_fd_set *fd_ex, struct bsd_timeval *tvp, int abi_nfdbits);
int	kern_sendfile(struct thread *td, struct sendfile_args *uap,
	    struct uio *hdr_uio, struct uio *trl_uio, int compat);
int	kern_sendit(struct thread *td, int s, struct bsd_msghdr *mp, int flags,
	    struct mbuf *control, enum bsd_uio_seg segflg);
int	kern_setgroups(struct thread *td, u_int ngrp, bsd_gid_t *groups);
int	kern_setitimer(struct thread *, u_int, struct bsd_itimerval *,
	    struct bsd_itimerval *);
int	kern_setrlimit(struct thread *, u_int, struct rlimit *);
int	kern_setsockopt(struct thread *td, int s, int level, int name,
	    void *optval, enum bsd_uio_seg valseg, bsd_socklen_t valsize);
int	kern_settimeofday(struct thread *td, struct bsd_timeval *tv,
	    struct bsd_timezone *tzp);
int	kern_shmat(struct thread *td, int shmid, const void *shmaddr,
	    int shmflg);
int	kern_shmctl(struct thread *td, int shmid, int cmd, void *buf,
	    bsd_size_t *bufsz);
int	kern_sigaction(struct thread *td, int sig, struct sigaction *act,
	    struct sigaction *oact, int flags);
int	kern_sigaltstack(struct thread *td, bsd_stack_t *ss, bsd_stack_t *oss);
int	kern_sigprocmask(struct thread *td, int how,
	    bsd_sigset_t *set, bsd_sigset_t *oset, int flags);
int	kern_sigsuspend(struct thread *td, bsd_sigset_t mask);
int	kern_sigtimedwait(struct thread *td, bsd_sigset_t waitset,
	    struct ksiginfo *ksi, struct bsd_timespec *timeout);
int	kern_stat(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    struct bsd_stat *sbp);
int	kern_statat(struct thread *td, int flag, int fd, char *path,
	    enum bsd_uio_seg pathseg, struct bsd_stat *sbp);
int	kern_statat_vnhook(struct thread *td, int flag, int fd, char *path,
	    enum bsd_uio_seg pathseg, struct bsd_stat *sbp,
	    void (*hook)(struct vnode *vp, struct bsd_stat *sbp));
int	kern_statfs(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    struct statfs *buf);
int	kern_symlink(struct thread *td, char *path, char *link,
	    enum bsd_uio_seg segflg);
int	kern_symlinkat(struct thread *td, char *path1, int fd, char *path2,
	    enum bsd_uio_seg segflg);
int	kern_thr_new(struct thread *td, struct thr_param *param);
int	kern_thr_suspend(struct thread *td, struct bsd_timespec *tsp);
int	kern_truncate(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    bsd_off_t length);
int	kern_unlink(struct thread *td, char *path, enum bsd_uio_seg pathseg);
int	kern_unlinkat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, bsd_ino_t oldinum);
int	kern_utimes(struct thread *td, char *path, enum bsd_uio_seg pathseg,
	    struct bsd_timeval *tptr, enum bsd_uio_seg tptrseg);
int	kern_utimesat(struct thread *td, int fd, char *path,
	    enum bsd_uio_seg pathseg, struct bsd_timeval *tptr, enum bsd_uio_seg tptrseg);
int	kern_wait(struct thread *td, bsd_pid_t pid, int *status, int options,
	    struct rusage *rup);
int	kern_wait6(struct thread *td, enum idtype idtype, bsd_id_t id, int *status,
	    int options, struct __wrusage *wrup, bsd_siginfo_t *sip);
int	kern_writev(struct thread *td, int fd, struct uio *auio);
int	kern_socketpair(struct thread *td, int domain, int type, int protocol,
	    int *rsv);

/* flags for kern_sigaction */
#define	KSA_OSIGSET	0x0001	/* uses osigact_t */
#define	KSA_FREEBSD4	0x0002	/* uses ucontext4 */

#endif /* !_SYS_SYSCALLSUBR_H_ */
