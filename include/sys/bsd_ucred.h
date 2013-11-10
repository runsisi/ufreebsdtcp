/*-
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)ucred.h	8.4 (Berkeley) 1/9/95
 * $FreeBSD: release/9.2.0/sys/sys/ucred.h 219304 2011-03-05 12:40:35Z trasz $
 */

#ifndef _SYS_UCRED_H_
#define	_SYS_UCRED_H_

#include <bsm/audit.h>

struct loginclass;

/*
 * Credentials.
 *
 * Please do not inspect cr_uid directly to determine superuserness.  The
 * priv(9) interface should be used to check for privilege.
 */
#if defined(_KERNEL) || defined(_WANT_UCRED)
struct bsd_ucred {
	u_int	cr_ref;			/* reference count */
#define	cr_startcopy cr_uid
	bsd_uid_t	cr_uid;			/* effective user id */
	bsd_uid_t	cr_ruid;		/* real user id */
	bsd_uid_t	cr_svuid;		/* saved user id */
	int	cr_ngroups;		/* number of groups */
	bsd_gid_t	cr_rgid;		/* real group id */
	bsd_gid_t	cr_svgid;		/* saved group id */
	struct uidinfo	*cr_uidinfo;	/* per euid resource consumption */
	struct uidinfo	*cr_ruidinfo;	/* per ruid resource consumption */
	struct prison	*cr_prison;	/* jail(2) */
	struct loginclass	*cr_loginclass; /* login class */
	u_int		cr_flags;	/* credential flags */
	void 		*cr_pspare2[2];	/* general use 2 */
#define	cr_endcopy	cr_label
	struct label	*cr_label;	/* MAC label */
	struct auditinfo_addr	cr_audit;	/* Audit properties. */
	bsd_gid_t	*cr_groups;		/* groups */
	int	cr_agroups;		/* Available groups */
};
#define	NOCRED	((struct ucred *)0)	/* no credential available */
#define	FSCRED	((struct ucred *)-1)	/* filesystem credential */
#endif /* _KERNEL || _WANT_UCRED */

#define	XU_NGROUPS	16

/*
 * Flags for cr_flags.
 */
#define	CRED_FLAG_CAPMODE	0x00000001	/* In capability mode. */

/*
 * This is the external representation of struct ucred.
 */
struct xucred {
	u_int	cr_version;		/* structure layout version */
	bsd_uid_t	cr_uid;			/* effective user id */
	short	cr_ngroups;		/* number of groups */
	bsd_gid_t	cr_groups[XU_NGROUPS];	/* groups */
	void	*_cr_unused1;		/* compatibility with old ucred */
};
#define	XUCRED_VERSION	0

/* This can be used for both ucred and xucred structures. */
#define	cr_gid cr_groups[0]

#ifdef _KERNEL
struct proc;
struct thread;

void	change_egid(struct bsd_ucred *newcred, bsd_gid_t egid);
void	change_euid(struct bsd_ucred *newcred, struct uidinfo *euip);
void	change_rgid(struct bsd_ucred *newcred, bsd_gid_t rgid);
void	change_ruid(struct bsd_ucred *newcred, struct uidinfo *ruip);
void	change_svgid(struct bsd_ucred *newcred, bsd_gid_t svgid);
void	change_svuid(struct bsd_ucred *newcred, bsd_uid_t svuid);
void	crcopy(struct bsd_ucred *dest, struct bsd_ucred *src);
struct bsd_ucred	*crcopysafe(struct proc *p, struct bsd_ucred *cr);
struct bsd_ucred	*crdup(struct bsd_ucred *cr);
void	cred_update_thread(struct thread *td);
void	crfree(struct bsd_ucred *cr);
struct bsd_ucred	*crget(void);
struct bsd_ucred	*crhold(struct bsd_ucred *cr);
int	crshared(struct bsd_ucred *cr);
void	cru2x(struct bsd_ucred *cr, struct xucred *xcr);
void	crsetgroups(struct bsd_ucred *cr, int n, bsd_gid_t *groups);
int	groupmember(bsd_gid_t gid, struct bsd_ucred *cred);
#endif /* _KERNEL */

#endif /* !_SYS_UCRED_H_ */
