/*-
 * Copyright (c) 1982, 1986, 1989, 1990, 1991, 1993
 *	The Regents of the University of California.
 * (c) UNIX System Laboratories, Inc.
 * Copyright (c) 2000-2001 Robert N. M. Watson.
 * All rights reserved.
 *
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
 *	@(#)kern_prot.c	8.6 (Berkeley) 1/21/94
 */

/*
 * System calls related to processes and protection
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_prot.c 244204 2012-12-14 08:52:08Z bapt $");

#include "opt_compat.h"
#include "opt_inet.h"
#include "opt_inet6.h"

#include "dps_frame.h"

#include <sys/bsd_param.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_acct.h>
#include <sys/bsd_kdb.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_loginclass.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_refcount.h>
#include <sys/bsd_sx.h>
#include <sys/bsd_priv.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_sysproto.h>
#include <sys/bsd_jail.h>
#include <sys/bsd_pioctl.h>
#include <sys/bsd_racct.h>
#include <sys/bsd_resourcevar.h>
#include <sys/bsd_socket.h>
#include <sys/bsd_socketvar.h>
#include <sys/bsd_syscallsubr.h>
#include <sys/bsd_sysctl.h>

#ifdef REGRESSION
FEATURE(regression,
    "Kernel support for interfaces nessesary for regression testing (SECURITY RISK!)");
#endif

#if defined(INET) || defined(INET6)
#include <netinet/bsd_in.h>
#include <netinet/in_pcb.h>
#endif

/*
 * Claim another reference to a ucred structure.
 */
struct bsd_ucred *
crhold(struct bsd_ucred *cr)
{
	return (cr);
}

/*
 * Free a cred structure.  Throws away space when ref count gets to 0.
 */
void
crfree(struct bsd_ucred *cr)
{

}
