/*-
 * Copyright (c) 1997-2000 Doug Rabson
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
 */

#include <sys/bsd_cdefs.h>
__FBSDID("$FreeBSD: release/9.2.0/sys/kern/kern_linker.c 235620 2012-05-18 18:51:13Z jhb $");

#include "opt_ddb.h"
#include "opt_hwpmc_hooks.h"

#include <sys/bsd_param.h>
#include <sys/bsd_kernel.h>
#include <sys/bsd_systm.h>
#include <sys/bsd_malloc.h>
#include <sys/bsd_sysproto.h>
#include <sys/bsd_sysent.h>
#include <sys/bsd_priv.h>
#include <sys/bsd_proc.h>
#include <sys/bsd_lock.h>
#include <sys/bsd_mutex.h>
#include <sys/bsd_sx.h>
#include <sys/bsd_module.h>
#include <sys/bsd_mount.h>
#include <sys/bsd_linker.h>
#include <sys/bsd_fcntl.h>
#include <sys/bsd_jail.h>
#include <sys/bsd_libkern.h>
#include <sys/bsd_namei.h>
#include <sys/bsd_vnode.h>
#include <sys/bsd_syscallsubr.h>
#include <sys/bsd_sysctl.h>

#include <net/vnet.h>

//#include <security/mac/mac_framework.h>

#include "linker_if.h"

#ifdef HWPMC_HOOKS
#include <sys/bsd_pmckern.h>
#endif

/* Metadata from the static kernel */
SET_DECLARE(modmetadata_set, struct mod_metadata);

static int
linker_file_register_modules(linker_file_t lf)
{
	struct mod_metadata **start, **stop, **mdp;
	const moduledata_t *moddata;
	int first_error, error;

	KLD_DPF(FILE, ("linker_file_register_modules: registering modules"
	    " in %s\n", lf->filename));

	start = SET_BEGIN(modmetadata_set);
	stop = SET_LIMIT(modmetadata_set);

	first_error = 0;
	for (mdp = start; mdp < stop; mdp++) {
		if ((*mdp)->md_type != MDT_MODULE)
			continue;
		moddata = (*mdp)->md_data;
		KLD_DPF(FILE, ("Registering module %s in %s\n",
		    moddata->name, lf->filename));
		error = module_register(moddata, lf);
		if (error) {
			printf("Module %s failed to register: %d\n",
			    moddata->name, error);
			if (first_error == 0)
				first_error = error;
		}
	}
	return (first_error);
}

static void
linker_init_kernel_modules(void)
{

	linker_file_register_modules(NULL);
}

#if 0	// runsisi AT hust.edu.cn @2013/12/01
SYSINIT(linker_kernel, SI_SUB_KLD, SI_ORDER_ANY, linker_init_kernel_modules,
    0);
#endif 	// ---------------------- @2013/12/01
// runsisi AT hust.edu.cn @2013/12/01
SYSINIT(linker_kernel, SI_SUB_KLD, SI_ORDER_SECOND, linker_init_kernel_modules,
    0);
// ---------------------- @2013/12/01
