/*-
 * Copyright (c) 2007-2008 John Birrell (jb@freebsd.org)
 * All rights reserved.
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
 * $FreeBSD: release/9.2.0/sys/sys/dtrace_bsd.h 243989 2012-12-07 19:06:40Z gnn $
 *
 * This file contains BSD shims for Sun's DTrace code.
 */

#ifndef _SYS_DTRACE_BSD_H
#define	_SYS_DTRACE_BSD_H

/* Forward definitions: */
struct mbuf;
struct trapframe;
struct thread;
struct vattr;
struct vnode;
struct reg;
struct devstat;
struct bio;

/*
 * Cyclic clock function type definition used to hook the cyclic
 * subsystem into the appropriate timer interrupt.
 */
typedef	void (*cyclic_clock_func_t)(struct trapframe *);
extern cyclic_clock_func_t	cyclic_clock_func;

void clocksource_cyc_set(const struct bsd_bintime *t);

/*
 * The dtrace module handles traps that occur during a DTrace probe.
 * This type definition is used in the trap handler to provide a
 * hook for the dtrace module to register it's handler with.
 */
typedef int (*dtrace_trap_func_t)(struct trapframe *, u_int);

int	dtrace_trap(struct trapframe *, u_int);

extern dtrace_trap_func_t	dtrace_trap_func;

/* Used by the machine dependent trap() code. */
typedef	int (*dtrace_invop_func_t)(bsd_uintptr_t, bsd_uintptr_t *, bsd_uintptr_t);
typedef void (*dtrace_doubletrap_func_t)(void);

/* Global variables in trap.c */
extern	dtrace_invop_func_t	dtrace_invop_func;
extern	dtrace_doubletrap_func_t	dtrace_doubletrap_func;

/* Pid provider hooks */
typedef int (*dtrace_fasttrap_probe_ptr_t)(struct reg *);
extern	dtrace_fasttrap_probe_ptr_t	dtrace_fasttrap_probe_ptr;
typedef int (*dtrace_pid_probe_ptr_t)(struct reg *);
extern	dtrace_pid_probe_ptr_t	dtrace_pid_probe_ptr;
typedef int (*dtrace_return_probe_ptr_t)(struct reg *);
extern	dtrace_return_probe_ptr_t	dtrace_return_probe_ptr;

/* Virtual time hook function type. */
typedef	void (*dtrace_vtime_switch_func_t)(struct thread *);

extern int			dtrace_vtime_active;
extern dtrace_vtime_switch_func_t	dtrace_vtime_switch_func;

/* The fasttrap module hooks into the fork, exit and exit. */
typedef void (*dtrace_fork_func_t)(struct proc *, struct proc *);
typedef void (*dtrace_execexit_func_t)(struct proc *);

/* Global variable in kern_fork.c */
extern dtrace_fork_func_t	dtrace_fasttrap_fork;

/* Global variable in kern_exec.c */
extern dtrace_execexit_func_t	dtrace_fasttrap_exec;

/* Global variable in kern_exit.c */
extern dtrace_execexit_func_t	dtrace_fasttrap_exit;

/* The dtmalloc provider hooks into malloc. */
typedef	void (*dtrace_malloc_probe_func_t)(bsd_uint32_t, bsd_uintptr_t arg0,
    bsd_uintptr_t arg1, bsd_uintptr_t arg2, bsd_uintptr_t arg3, bsd_uintptr_t arg4);

extern dtrace_malloc_probe_func_t   dtrace_malloc_probe;

/* dtnfsclient NFSv[34] access cache provider hooks. */
typedef void (*dtrace_nfsclient_accesscache_flush_probe_func_t)(bsd_uint32_t,
    struct vnode *);
extern dtrace_nfsclient_accesscache_flush_probe_func_t
    dtrace_nfsclient_accesscache_flush_done_probe;
extern dtrace_nfsclient_accesscache_flush_probe_func_t
    dtrace_nfscl_accesscache_flush_done_probe;

typedef void (*dtrace_nfsclient_accesscache_get_probe_func_t)(bsd_uint32_t,
    struct vnode *, bsd_uid_t, bsd_uint32_t);
extern dtrace_nfsclient_accesscache_get_probe_func_t
    dtrace_nfsclient_accesscache_get_hit_probe,
    dtrace_nfsclient_accesscache_get_miss_probe;
extern dtrace_nfsclient_accesscache_get_probe_func_t
    dtrace_nfscl_accesscache_get_hit_probe,
    dtrace_nfscl_accesscache_get_miss_probe;

typedef void (*dtrace_nfsclient_accesscache_load_probe_func_t)(bsd_uint32_t,
    struct vnode *, bsd_uid_t, bsd_uint32_t, int);
extern dtrace_nfsclient_accesscache_load_probe_func_t
    dtrace_nfsclient_accesscache_load_done_probe;
extern dtrace_nfsclient_accesscache_load_probe_func_t
    dtrace_nfscl_accesscache_load_done_probe;

/* dtnfsclient NFSv[234] attribute cache provider hooks. */
typedef void (*dtrace_nfsclient_attrcache_flush_probe_func_t)(bsd_uint32_t,
    struct vnode *);
extern dtrace_nfsclient_attrcache_flush_probe_func_t
    dtrace_nfsclient_attrcache_flush_done_probe;
extern dtrace_nfsclient_attrcache_flush_probe_func_t
    dtrace_nfscl_attrcache_flush_done_probe;

typedef void (*dtrace_nfsclient_attrcache_get_hit_probe_func_t)(bsd_uint32_t,
    struct vnode *, struct vattr *);
extern dtrace_nfsclient_attrcache_get_hit_probe_func_t
    dtrace_nfsclient_attrcache_get_hit_probe;
extern dtrace_nfsclient_attrcache_get_hit_probe_func_t
    dtrace_nfscl_attrcache_get_hit_probe;

typedef void (*dtrace_nfsclient_attrcache_get_miss_probe_func_t)(bsd_uint32_t,
    struct vnode *);
extern dtrace_nfsclient_attrcache_get_miss_probe_func_t
    dtrace_nfsclient_attrcache_get_miss_probe;
extern dtrace_nfsclient_attrcache_get_miss_probe_func_t
    dtrace_nfscl_attrcache_get_miss_probe;

typedef void (*dtrace_nfsclient_attrcache_load_probe_func_t)(bsd_uint32_t,
    struct vnode *, struct vattr *, int);
extern dtrace_nfsclient_attrcache_load_probe_func_t
    dtrace_nfsclient_attrcache_load_done_probe;
extern dtrace_nfsclient_attrcache_load_probe_func_t
    dtrace_nfscl_attrcache_load_done_probe;

/* dtnfsclient NFSv[234] RPC provider hooks. */
typedef void (*dtrace_nfsclient_nfs23_start_probe_func_t)(bsd_uint32_t,
    struct vnode *, struct mbuf *, struct bsd_ucred *, int);
extern dtrace_nfsclient_nfs23_start_probe_func_t
    dtrace_nfsclient_nfs23_start_probe;
extern dtrace_nfsclient_nfs23_start_probe_func_t
    dtrace_nfscl_nfs234_start_probe;

typedef void (*dtrace_nfsclient_nfs23_done_probe_func_t)(bsd_uint32_t,
    struct vnode *, struct mbuf *, struct bsd_ucred *, int, int);
extern dtrace_nfsclient_nfs23_done_probe_func_t
    dtrace_nfsclient_nfs23_done_probe;
extern dtrace_nfsclient_nfs23_done_probe_func_t
    dtrace_nfscl_nfs234_done_probe;

/* IO Provider hooks, really hook into devstat */
typedef void (*dtrace_io_start_probe_func_t)(bsd_uint32_t, struct bio *,
					     struct devstat *);
extern dtrace_io_start_probe_func_t dtrace_io_start_probe;

typedef void (*dtrace_io_done_probe_func_t)(bsd_uint32_t, struct bio *,
					    struct devstat *);
extern dtrace_io_done_probe_func_t dtrace_io_done_probe;

typedef void (*dtrace_io_wait_start_probe_func_t)(bsd_uint32_t, bsd_uintptr_t *, 
						  struct devstat *);
extern dtrace_io_wait_start_probe_func_t dtrace_io_wait_start_probe;

typedef void (*dtrace_io_wait_done_probe_func_t)(bsd_uint32_t, bsd_uintptr_t *, 
						 struct devstat *);
extern dtrace_io_wait_done_probe_func_t dtrace_io_wait_done_probe;

/*
 * Functions which allow the dtrace module to check that the kernel 
 * hooks have been compiled with sufficient space for it's private
 * structures.
 */
bsd_size_t	kdtrace_proc_size(void);
bsd_size_t	kdtrace_thread_size(void);

/*
 * OpenSolaris compatible time functions returning nanoseconds.
 * On OpenSolaris these return hrtime_t which we define as uint64_t.
 */
bsd_uint64_t	dtrace_gethrtime(void);
bsd_uint64_t	dtrace_gethrestime(void);

#endif /* _SYS_DTRACE_BSD_H */
