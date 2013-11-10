KERN_IDENT=GENERIC
MACHINE=amd64
MACHINE_ARCH=amd64
WITH_CTF=1
DEBUG=-g
S=/usr/src/sys
# Makefile.amd64 -- with config changes.
# Copyright 1990 W. Jolitz
#	from: @(#)Makefile.i386	7.1 5/10/91
#	from FreeBSD: src/sys/conf/Makefile.i386,v 1.255 2002/02/20 23:35:49
# $FreeBSD: release/9.2.0/sys/conf/Makefile.amd64 232930 2012-03-13 18:39:57Z dim $
#
# Makefile for FreeBSD
#
# This makefile is constructed from a machine description:
#	config machineid
# Most changes should be made in the machine description
#	/sys/amd64/conf/``machineid''
# after which you should do
#	 config machineid
# Generic makefile changes should be made in
#	/sys/conf/Makefile.amd64
# after which config should be rerun for all machines.
#

# Which version of config(8) is required.

STD8X16FONT?=	iso

.if !defined(S)
.if exists(./@/.)
S=	./@
.else
S=	../../..
.endif
.endif
.include "$S/conf/kern.pre.mk"

DDB_ENABLED!=	grep DDB opt_ddb.h || true
DTR_ENABLED!=	grep KDTRACE_FRAME opt_kdtrace.h || true
HWPMC_ENABLED!=	grep HWPMC opt_hwpmc_hooks.h || true
.if !empty(DDB_ENABLED) || !empty(DTR_ENABLED) || !empty(HWPMC_ENABLED)
CFLAGS+=	-fno-omit-frame-pointer
.endif

MKMODULESENV+= MACHINE=amd64

# XXX: clang integrated-as doesn't grok .codeNN directives yet
ASM_CFLAGS.acpi_wakecode.S=	${CLANG_NO_IAS}
ASM_CFLAGS.ia32_sigtramp.S=	${CLANG_NO_IAS}
ASM_CFLAGS.linux32_locore.s=	${CLANG_NO_IAS}
ASM_CFLAGS.mpboot.S=		${CLANG_NO_IAS}
ASM_CFLAGS+=			${ASM_CFLAGS.${.IMPSRC:T}}

BEFORE_DEPEND=acpi_quirks.h aic7xxx_seq.h aic7xxx_reg.h \
	aic79xx_seq.h aic79xx_reg.h feeder_eq_gen.h \
	feeder_rate_gen.h snd_fxdiv_gen.h miidevs.h \
	pccarddevs.h teken_state.h usbdevs.h usbdevs_data.h \
	ia32_assym.h acpi_wakecode.o acpi_wakecode.bin \
	acpi_wakecode.h acpi_wakedata.h 

OBJS=aic7xxx_reg_print.o aic79xx_reg_print.o cam.o cam_compat.o \
	cam_periph.o cam_queue.o cam_sim.o cam_xpt.o ata_all.o ata_xpt.o \
	ata_pmp.o scsi_xpt.o scsi_all.o scsi_cd.o scsi_ch.o ata_da.o \
	scsi_da.o scsi_pass.o scsi_sa.o scsi_enc.o scsi_enc_ses.o \
	scsi_enc_safte.o smp_all.o dsargs.o dscontrol.o dsfield.o \
	dsinit.o dsmethod.o dsmthdat.o dsobject.o dsopcode.o dsutils.o \
	dswexec.o dswload.o dswload2.o dswscope.o dswstate.o evevent.o \
	evglock.o evgpe.o evgpeblk.o evgpeinit.o evgpeutil.o evmisc.o \
	evregion.o evrgnini.o evsci.o evxface.o evxfevnt.o evxfgpe.o \
	evxfregn.o exconfig.o exconvrt.o excreate.o exdebug.o exdump.o \
	exfield.o exfldio.o exmisc.o exmutex.o exnames.o exoparg1.o \
	exoparg2.o exoparg3.o exoparg6.o exprep.o exregion.o exresnte.o \
	exresolv.o exresop.o exstore.o exstoren.o exstorob.o exsystem.o \
	exutils.o hwacpi.o hwgpe.o hwpci.o hwregs.o hwsleep.o hwtimer.o \
	hwvalid.o hwxface.o nsaccess.o nsalloc.o nsdump.o nseval.o \
	nsinit.o nsload.o nsnames.o nsobject.o nsparse.o nspredef.o \
	nsrepair.o nsrepair2.o nssearch.o nsutils.o nswalk.o nsxfeval.o \
	nsxfname.o nsxfobj.o psargs.o psloop.o psopcode.o psparse.o \
	psscope.o pstree.o psutils.o pswalk.o psxface.o rsaddr.o \
	rscalc.o rscreate.o rsdump.o rsinfo.o rsio.o rsirq.o rslist.o \
	rsmemory.o rsmisc.o rsutils.o rsxface.o tbfadt.o tbfind.o \
	tbinstal.o tbutils.o tbxface.o tbxfroot.o utalloc.o utcache.o \
	utcopy.o utdebug.o utdecode.o utdelete.o uteval.o utglobal.o \
	utids.o utinit.o utlock.o utmath.o utmisc.o utmutex.o utobject.o \
	utosi.o utresrc.o utstate.o utxface.o utxferror.o \
	rijndael-alg-fst.o rijndael-api-fst.o rijndael-api.o sha1.o \
	sha2.o aac.o aac_cam.o aac_debug.o aac_disk.o aac_pci.o \
	aacraid.o aacraid_cam.o aacraid_debug.o aacraid_pci.o OsdDebug.o \
	OsdHardware.o OsdInterrupt.o OsdMemory.o OsdSchedule.o \
	OsdStream.o OsdSynch.o OsdTable.o acpi.o acpi_acad.o \
	acpi_battery.o acpi_button.o acpi_cmbat.o acpi_cpu.o acpi_ec.o \
	acpi_hpet.o acpi_isab.o acpi_lid.o acpi_package.o acpi_pci.o \
	acpi_pci_link.o acpi_pcib.o acpi_pcib_acpi.o acpi_pcib_pci.o \
	acpi_perf.o acpi_powerres.o acpi_quirk.o acpi_resource.o \
	acpi_smbat.o acpi_thermal.o acpi_throttle.o acpi_timer.o \
	adv_pci.o advansys.o advlib.o advmcode.o adw_pci.o adwcam.o \
	adwlib.o adwmcode.o if_ae.o if_age.o agp.o agp_if.o ahci.o aic.o \
	aic_pccard.o ahc_isa.o ahc_pci.o ahd_pci.o aic7770.o aic79xx.o \
	aic79xx_osm.o aic79xx_pci.o aic7xxx.o aic7xxx_93cx6.o \
	aic7xxx_osm.o aic7xxx_pci.o if_alc.o if_ale.o amr.o amr_disk.o \
	amr_pci.o if_an.o if_an_isa.o if_an_pccard.o if_an_pci.o \
	ata_if.o ata-all.o ata-dma.o ata-lowlevel.o ata-queue.o \
	ata-sata.o ata-card.o ata-isa.o ata-pci.o ata-ahci.o ata-acard.o \
	ata-acerlabs.o ata-adaptec.o ata-amd.o ata-ati.o ata-cenatek.o \
	ata-cypress.o ata-cyrix.o ata-highpoint.o ata-intel.o ata-ite.o \
	ata-jmicron.o ata-marvell.o ata-micron.o ata-national.o \
	ata-netcell.o ata-nvidia.o ata-promise.o ata-serverworks.o \
	ata-siliconimage.o ata-sis.o ata-via.o if_ath_pci.o if_ath.o \
	if_ath_debug.o if_ath_keycache.o if_ath_tx.o if_ath_tx_ht.o \
	if_ath_sysctl.o ah_osdep.o ah.o ah_eeprom_v1.o ah_eeprom_v3.o \
	ah_eeprom_v14.o ah_eeprom_v4k.o ah_eeprom_9287.o ah_regdomain.o \
	ar5210_attach.o ar5210_beacon.o ar5210_interrupts.o \
	ar5210_keycache.o ar5210_misc.o ar5210_phy.o ar5210_power.o \
	ar5210_recv.o ar5210_reset.o ar5210_xmit.o ar5211_attach.o \
	ar5211_beacon.o ar5211_interrupts.o ar5211_keycache.o \
	ar5211_misc.o ar5211_phy.o ar5211_power.o ar5211_recv.o \
	ar5211_reset.o ar5211_xmit.o ar5212_ani.o ar5212_attach.o \
	ar5212_beacon.o ar5212_eeprom.o ar5212_gpio.o \
	ar5212_interrupts.o ar5212_keycache.o ar5212_misc.o ar5212_phy.o \
	ar5212_power.o ar5212_recv.o ar5212_reset.o ar5212_rfgain.o \
	ar5212_xmit.o ar5416_ani.o ar5416_attach.o ar5416_beacon.o \
	ar5416_cal.o ar5416_cal_iq.o ar5416_cal_adcgain.o \
	ar5416_cal_adcdc.o ar5416_eeprom.o ar5416_gpio.o \
	ar5416_interrupts.o ar5416_keycache.o ar5416_misc.o ar5416_phy.o \
	ar5416_power.o ar5416_recv.o ar5416_reset.o ar5416_xmit.o \
	ar9130_attach.o ar9130_phy.o ar9130_eeprom.o ar9160_attach.o \
	ar9280_attach.o ar9280_olc.o ar9285_attach.o ar9285_reset.o \
	ar9285_cal.o ar9285_phy.o ar9285_diversity.o ar9287_attach.o \
	ar9287_reset.o ar9287_cal.o ar9287_olc.o ar2413.o ar2425.o \
	ar5111.o ar5112.o ar5413.o ar2133.o ar9280.o ar9285.o ar9287.o \
	sample.o dfs_null.o if_bce.o if_bfe.o if_bge.o bt.o bt_isa.o \
	bt_pci.o if_bxe.o bxe_link.o cardbus.o cardbus_cis.o \
	cardbus_device.o if_cas.o ciss.o ichss.o if_cs.o if_cs_isa.o \
	if_cs_pccard.o if_dc.o dcphy.o pnphy.o if_de.o dpt_pci.o \
	dpt_scsi.o if_ed.o if_ed_novell.o if_ed_rtl80x9.o if_ed_pccard.o \
	if_ed_pci.o eisa_if.o if_em.o if_lem.o if_igb.o \
	e1000_80003es2lan.o e1000_82540.o e1000_82541.o e1000_82542.o \
	e1000_82543.o e1000_82571.o e1000_82575.o e1000_ich8lan.o \
	e1000_i210.o e1000_api.o e1000_mac.o e1000_manage.o e1000_nvm.o \
	e1000_phy.o e1000_vf.o e1000_mbx.o e1000_osdep.o if_et.o if_ep.o \
	if_ep_isa.o if_ep_pccard.o esp_pci.o ncr53c9x.o if_ex.o \
	if_ex_isa.o if_ex_pccard.o exca.o splash.o if_fe.o \
	if_fe_pccard.o if_fxp.o inphy.o if_gem.o if_gem_pci.o if_hme.o \
	if_hme_pci.o hptiop.o ida.o ida_disk.o ida_pci.o iir.o \
	iir_ctrl.o iir_pci.o ips.o ips_commands.o ips_disk.o ips_ioctl.o \
	ips_pci.o if_ipw.o isp.o isp_freebsd.o isp_library.o isp_pci.o \
	isp_target.o if_iwi.o if_iwn.o ixgbe.o ixv.o ixgbe_phy.o \
	ixgbe_api.o ixgbe_common.o ixgbe_mbx.o ixgbe_vf.o ixgbe_82598.o \
	ixgbe_82599.o ixgbe_x540.o ixgbe_dcb.o ixgbe_dcb_82598.o \
	ixgbe_dcb_82599.o if_jme.o kbdmux.o am7990.o am79900.o \
	if_le_pci.o lance.o led.o if_lge.o if_malo.o if_malohal.o \
	if_malo_pci.o md.o memdev.o memutil.o mfi.o mfi_debug.o \
	mfi_pci.o mfi_disk.o mfi_syspd.o mfi_tbolt.o acphy.o amphy.o \
	atphy.o axphy.o bmtphy.o brgphy.o ciphy.o e1000phy.o gentbi.o \
	icsphy.o ip1000phy.o jmphy.o lxtphy.o mii.o mii_bitbang.o \
	mii_physubr.o miibus_if.o mlphy.o nsgphy.o nsphy.o nsphyter.o \
	pnaphy.o qsphy.o rdcphy.o rgephy.o rlphy.o smcphy.o tdkphy.o \
	tlphy.o truephy.o ukphy.o ukphy_subr.o xmphy.o mlx.o mlx_disk.o \
	mlx_pci.o mly.o mmcbr_if.o mmcbus_if.o mps.o mps_config.o \
	mps_mapping.o mps_pci.o mps_sas.o mps_sas_lsi.o mps_table.o \
	mps_user.o mpt.o mpt_cam.o mpt_debug.o mpt_pci.o mpt_raid.o \
	mpt_user.o if_msk.o mvs.o mvs_if.o mvs_pci.o if_mwl.o \
	if_mwl_pci.o mwlhal.o if_nge.o null.o card_if.o pccard.o \
	pccard_cis.o pccard_cis_quirks.o pccard_device.o power_if.o \
	pccbb.o pccbb_isa.o pccbb_pci.o fixup_pci.o hostb_pci.o \
	ignore_pci.o isa_pci.o pci.o pci_if.o pci_pci.o pci_subr.o \
	pci_user.o pcib_if.o vga_pci.o if_pcn.o if_plip.o lpt.o \
	ppb_1284.o ppb_base.o ppb_msq.o ppbconf.o ppbus_if.o ppi.o ppc.o \
	ppc_acpi.o ppc_isa.o ppc_pci.o ppc_puc.o pty.o puc.o puc_cfg.o \
	puc_pccard.o puc_pci.o pucdata.o rt2560.o rt2661.o rt2860.o \
	if_ral_pci.o harvest.o hash.o probe.o randomdev.o \
	randomdev_soft.o yarrow.o if_re.o if_sf.o if_sge.o siis.o \
	if_sis.o if_sk.o if_sn.o if_sn_isa.o if_sn_pccard.o clone.o \
	unit.o sndbuf_dma.o cmi.o csa.o csapcm.o emu10kx.o emu10kx-pcm.o \
	emu10kx-midi.o es137x.o ich.o via8233.o hdaa.o hdaa_patches.o \
	hdac.o hdac_if.o hdacc.o ac97.o ac97_if.o ac97_patch.o buffer.o \
	channel.o channel_if.o dsp.o feeder.o feeder_chain.o feeder_eq.o \
	feeder_if.o feeder_format.o feeder_matrix.o feeder_mixer.o \
	feeder_rate.o feeder_volume.o mixer.o mixer_if.o sndstat.o \
	sound.o vchan.o uaudio.o uaudio_pcm.o midi.o mpu401.o mpu_if.o \
	mpufoi_if.o sequencer.o synth_if.o if_ste.o if_stge.o sym_hipd.o \
	schistory.o scmouse.o scterm.o scvidctl.o syscons.o sysmouse.o \
	if_ti.o if_tl.o trm.o tw_cl_init.o tw_cl_intr.o tw_cl_io.o \
	tw_cl_misc.o tw_osl_cam.o tw_osl_freebsd.o twe.o twe_freebsd.o \
	tws.o tws_cam.o tws_hdm.o tws_services.o tws_user.o if_tx.o \
	if_txp.o uart_bus_acpi.o uart_bus_isa.o uart_bus_pccard.o \
	uart_bus_pci.o uart_bus_puc.o uart_core.o uart_dev_ns8250.o \
	uart_if.o uart_subr.o uart_tty.o ehci.o ehci_pci.o ohci.o \
	ohci_pci.o uhci.o uhci_pci.o xhci.o xhci_pci.o usb_controller.o \
	umass.o urio.o usb_busdma.o usb_compat_linux.o usb_core.o \
	usb_debug.o usb_dev.o usb_device.o usb_dynamic.o usb_error.o \
	usb_generic.o usb_handle_request.o usb_hid.o usb_hub.o usb_if.o \
	usb_lookup.o usb_mbuf.o usb_msctest.o usb_parse.o usb_pf.o \
	usb_process.o usb_request.o usb_transfer.o usb_util.o if_aue.o \
	if_axe.o if_cdce.o if_cue.o if_kue.o if_rue.o if_udav.o ruephy.o \
	usb_ethernet.o if_rum.o if_run.o if_uath.o if_upgt.o if_ural.o \
	if_urtw.o if_zyd.o u3g.o uark.o ubsa.o uftdi.o uipaq.o ulpt.o \
	uplcom.o uslcom.o uvisor.o uvscom.o usb_serial.o uhid.o ukbd.o \
	ums.o usb_quirk.o if_vge.o if_vr.o if_vx.o if_vx_pci.o \
	watchdog.o if_wb.o if_wi.o if_wi_pccard.o if_wi_pci.o if_wpi.o \
	if_xe.o if_xe_pccard.o if_xl.o xlphy.o dead_vnops.o devfs_devs.o \
	devfs_dir.o devfs_rule.o devfs_vfsops.o devfs_vnops.o \
	fifo_vnops.o msdosfs_conv.o msdosfs_denode.o msdosfs_fat.o \
	msdosfs_fileno.o msdosfs_lookup.o msdosfs_vfsops.o \
	msdosfs_vnops.o nfs_commonkrpc.o nfs_commonsubs.o \
	nfs_commonport.o nfs_commonacl.o nfs_clcomsubs.o nfs_clsubs.o \
	nfs_clstate.o nfs_clkrpc.o nfs_clrpcops.o nfs_clvnops.o \
	nfs_clnode.o nfs_clvfsops.o nfs_clport.o nfs_clbio.o \
	nfs_clnfsiod.o nfs_fha_new.o nfs_nfsdsocket.o nfs_nfsdsubs.o \
	nfs_nfsdstate.o nfs_nfsdkrpc.o nfs_nfsdserv.o nfs_nfsdport.o \
	nfs_nfsdcache.o procfs.o procfs_ctl.o procfs_dbregs.o \
	procfs_fpregs.o procfs_ioctl.o procfs_map.o procfs_mem.o \
	procfs_note.o procfs_osrel.o procfs_regs.o procfs_rlimit.o \
	procfs_status.o procfs_type.o pseudofs.o pseudofs_fileno.o \
	pseudofs_vncache.o pseudofs_vnops.o geom_ctl.o geom_dev.o \
	geom_disk.o geom_dump.o geom_event.o geom_io.o geom_kern.o \
	geom_slice.o geom_subr.o geom_vfs.o g_label.o g_label_ext2fs.o \
	g_label_iso9660.o g_label_msdosfs.o g_label_ntfs.o \
	g_label_reiserfs.o g_label_ufs.o g_label_gpt.o g_part.o \
	g_part_if.o g_part_bsd.o g_part_ebr.o g_part_gpt.o g_part_mbr.o \
	g_raid.o g_raid_ctl.o g_raid_md_if.o g_raid_tr_if.o md_ddf.o \
	md_intel.o md_jmicron.o md_nvidia.o md_promise.o md_sii.o \
	tr_concat.o tr_raid0.o tr_raid1.o tr_raid1e.o tr_raid5.o \
	isa_if.o isa_common.o isahint.o cd9660_bmap.o cd9660_lookup.o \
	cd9660_node.o cd9660_rrip.o cd9660_util.o cd9660_vfsops.o \
	cd9660_vnops.o bus_if.o clock_if.o cpufreq_if.o device_if.o \
	imgact_elf.o imgact_shell.o init_main.o init_sysent.o ksched.o \
	kern_acct.o kern_clock.o kern_condvar.o kern_conf.o kern_cons.o \
	kern_cpu.o kern_cpuset.o kern_context.o kern_descrip.o \
	kern_dtrace.o kern_environment.o kern_et.o kern_event.o \
	kern_exec.o kern_exit.o kern_fail.o kern_fork.o kern_hhook.o \
	kern_idle.o kern_intr.o kern_jail.o kern_khelp.o kern_kthread.o \
	kern_ktrace.o kern_linker.o kern_lock.o kern_lockf.o \
	kern_lockstat.o kern_loginclass.o kern_malloc.o kern_mbuf.o \
	kern_mib.o kern_module.o kern_mtxpool.o kern_mutex.o \
	kern_ntptime.o kern_osd.o kern_physio.o kern_pmc.o kern_priv.o \
	kern_proc.o kern_prot.o kern_racct.o kern_rangelock.o \
	kern_rctl.o kern_resource.o kern_rmlock.o kern_rwlock.o \
	kern_sdt.o kern_sema.o kern_sharedpage.o kern_shutdown.o \
	kern_sig.o kern_switch.o kern_sx.o kern_synch.o kern_syscalls.o \
	kern_sysctl.o kern_tc.o kern_thr.o kern_thread.o kern_time.o \
	kern_timeout.o kern_umtx.o kern_uuid.o kern_xxx.o link_elf.o \
	linker_if.o md5c.o p1003_1b.o posix4_mib.o sched_ule.o \
	serdev_if.o stack_protector.o subr_acl_nfs4.o subr_acl_posix1e.o \
	subr_autoconf.o subr_blist.o subr_bus.o subr_bus_dma.o \
	subr_bufring.o subr_clock.o subr_devstat.o subr_disk.o \
	subr_eventhandler.o subr_fattime.o subr_firmware.o subr_hash.o \
	subr_hints.o subr_kdb.o subr_kobj.o subr_lock.o subr_log.o \
	subr_module.o subr_msgbuf.o subr_param.o subr_pcpu.o \
	subr_power.o subr_prf.o subr_prof.o subr_rman.o subr_rtc.o \
	subr_sbuf.o subr_scanf.o subr_sglist.o subr_sleepqueue.o \
	subr_smp.o subr_stack.o subr_taskqueue.o subr_trap.o \
	subr_turnstile.o subr_uio.o subr_unit.o sys_capability.o \
	sys_generic.o sys_pipe.o sys_procdesc.o sys_process.o \
	sys_socket.o syscalls.o sysv_ipc.o sysv_msg.o sysv_sem.o \
	sysv_shm.o tty.o tty_info.o tty_inq.o tty_outq.o tty_pts.o \
	tty_tty.o tty_ttydisc.o uipc_accf.o uipc_domain.o uipc_mbuf.o \
	uipc_mbuf2.o uipc_shm.o uipc_sockbuf.o uipc_socket.o \
	uipc_syscalls.o uipc_usrreq.o vfs_acl.o vfs_bio.o vfs_cache.o \
	vfs_cluster.o vfs_default.o vfs_export.o vfs_extattr.o \
	vfs_hash.o vfs_init.o vfs_lookup.o vfs_mount.o vfs_mountroot.o \
	vfs_subr.o vfs_syscalls.o vfs_vnops.o arc4random.o bcd.o \
	bsearch.o crc32.o fnmatch.o index.o inet_aton.o inet_ntoa.o \
	inet_ntop.o inet_pton.o memcmp.o qsort.o qsort_r.o random.o \
	rindex.o scanc.o skpc.o strcasecmp.o strcat.o strcmp.o strcpy.o \
	strcspn.o strdup.o strlcat.o strlcpy.o strlen.o strncmp.o \
	strncpy.o strnlen.o strsep.o strspn.o strstr.o strtol.o strtoq.o \
	strtoul.o strtouq.o strvalid.o bpf.o bpf_buffer.o bpf_filter.o \
	bpf_zerocopy.o if.o if_clone.o if_dead.o if_ethersubr.o \
	if_faith.o if_gif.o if_loop.o if_llatbl.o if_media.o if_mib.o \
	if_tun.o if_vlan.o netisr.o pfil.o radix.o radix_mpath.o \
	raw_cb.o raw_usrreq.o route.o rtsock.o zlib.o ieee80211.o \
	ieee80211_action.o ieee80211_ageq.o ieee80211_adhoc.o \
	ieee80211_amrr.o ieee80211_crypto.o ieee80211_crypto_ccmp.o \
	ieee80211_crypto_none.o ieee80211_crypto_tkip.o \
	ieee80211_crypto_wep.o ieee80211_dfs.o ieee80211_freebsd.o \
	ieee80211_hostap.o ieee80211_ht.o ieee80211_hwmp.o \
	ieee80211_input.o ieee80211_ioctl.o ieee80211_mesh.o \
	ieee80211_monitor.o ieee80211_node.o ieee80211_output.o \
	ieee80211_phy.o ieee80211_power.o ieee80211_proto.o \
	ieee80211_radiotap.o ieee80211_ratectl.o \
	ieee80211_ratectl_none.o ieee80211_regdomain.o ieee80211_scan.o \
	ieee80211_scan_sta.o ieee80211_sta.o ieee80211_wds.o if_ether.o \
	igmp.o in.o in_gif.o ip_id.o in_mcast.o in_pcb.o in_proto.o \
	in_rmx.o ip_ecn.o ip_encap.o ip_fastfwd.o ip_icmp.o ip_input.o \
	ip_options.o ip_output.o raw_ip.o cc.o cc_newreno.o \
	sctp_asconf.o sctp_auth.o sctp_bsd_addr.o sctp_cc_functions.o \
	sctp_crc32.o sctp_indata.o sctp_input.o sctp_output.o sctp_pcb.o \
	sctp_peeloff.o sctp_ss_functions.o sctp_sysctl.o sctp_timer.o \
	sctp_usrreq.o sctputil.o tcp_hostcache.o tcp_input.o tcp_lro.o \
	tcp_output.o tcp_offload.o tcp_reass.o tcp_sack.o tcp_subr.o \
	tcp_syncache.o tcp_timer.o tcp_timewait.o tcp_usrreq.o \
	udp_usrreq.o dest6.o frag6.o icmp6.o in6.o in6_cksum.o in6_gif.o \
	in6_ifattach.o in6_mcast.o in6_pcb.o in6_proto.o in6_rmx.o \
	in6_src.o ip6_forward.o ip6_id.o ip6_input.o ip6_output.o mld6.o \
	nd6.o nd6_nbr.o nd6_rtr.o raw_ip6.o route6.o scope6.o \
	sctp6_usrreq.o udp6_usrreq.o nfs_diskless.o nfs_fha.o nfs_lock.o \
	nfs_nfssvc.o nlm_advlock.o nlm_prot_clnt.o nlm_prot_impl.o \
	nlm_prot_server.o nlm_prot_svc.o nlm_prot_xdr.o sm_inter_xdr.o \
	if_rl.o auth_none.o auth_unix.o authunix_prot.o clnt_dg.o \
	clnt_rc.o clnt_vc.o getnetconfig.o replay.o rpc_callmsg.o \
	rpc_generic.o rpc_prot.o rpcb_clnt.o rpcb_prot.o svc.o \
	svc_auth.o svc_auth_unix.o svc_dg.o svc_generic.o svc_vc.o \
	audit.o audit_arg.o audit_bsm.o audit_bsm_domain.o \
	audit_bsm_errno.o audit_bsm_fcntl.o audit_bsm_klib.o \
	audit_bsm_socket_type.o audit_bsm_token.o audit_pipe.o \
	audit_syscalls.o audit_trigger.o audit_worker.o mac_audit.o \
	mac_cred.o mac_framework.o mac_inet.o mac_inet6.o mac_label.o \
	mac_net.o mac_pipe.o mac_posix_sem.o mac_posix_shm.o mac_priv.o \
	mac_process.o mac_socket.o mac_syscalls.o mac_system.o \
	mac_sysv_msg.o mac_sysv_sem.o mac_sysv_shm.o mac_vfs.o teken.o \
	ffs_alloc.o ffs_balloc.o ffs_inode.o ffs_snapshot.o \
	ffs_softdep.o ffs_subr.o ffs_tables.o ffs_vfsops.o ffs_vnops.o \
	ffs_suspend.o ufs_acl.o ufs_bmap.o ufs_dirhash.o ufs_extattr.o \
	ufs_gjournal.o ufs_inode.o ufs_lookup.o ufs_quota.o ufs_vfsops.o \
	ufs_vnops.o default_pager.o device_pager.o phys_pager.o \
	sg_pager.o swap_pager.o uma_core.o uma_dbg.o vm_contig.o \
	vm_fault.o vm_glue.o vm_init.o vm_kern.o vm_map.o vm_meter.o \
	vm_mmap.o vm_object.o vm_page.o vm_pageout.o vm_pager.o \
	vm_phys.o vm_reserv.o vm_unix.o vm_zeroidle.o vnode_pager.o \
	xdr.o xdr_array.o xdr_mbuf.o xdr_mem.o xdr_reference.o \
	xdr_sizeof.o hpt27xx_lib.o hptmvraid.o hptnr_lib.o hptrr_lib.o \
	acpi_machdep.o acpi_switch.o acpi_wakeup.o amd64_mem.o atomic.o \
	autoconf.o bios.o cpu_switch.o elf_machdep.o exception.o fpu.o \
	identcpu.o in_cksum.o initcpu.o io.o legacy.o machdep.o mem.o \
	minidump_machdep.o mp_machdep.o mpboot.o pmap.o ptrace_machdep.o \
	sigtramp.o stack_machdep.o support.o sys_machdep.o trap.o \
	uio_machdep.o uma_machdep.o vm_machdep.o pci_cfgreg.o acpi_if.o \
	acpi_wmi_if.o agp_amd64.o agp_i810.o agp_intel.o agp_via.o \
	arcmsr.o atkbd.o atkbd_atkbdc.o atkbdc.o atkbdc_isa.o \
	atkbdc_subr.o psm.o if_ed_isa.o if_ed_wd80x3.o fb.o vesa.o vga.o \
	iodev.o fdc.o fdc_acpi.o fdc_isa.o fdc_pccard.o hpt27xx_os_bsd.o \
	hpt27xx_osm_bsd.o hpt27xx_config.o entry.o mv.o gui_lib.o \
	hptproc.o ioctl.o hptnr_os_bsd.o hptnr_osm_bsd.o hptnr_config.o \
	hptrr_os_bsd.o hptrr_osm_bsd.o hptrr_config.o kbd.o if_nfe.o \
	ivy.o nehemiah.o scterm-teken.o scvesactl.o scvgarndr.o scvtb.o \
	uart_cpu_amd64.o isci.o isci_controller.o isci_domain.o \
	isci_interrupt.o isci_io_request.o isci_logger.o \
	isci_oem_parameters.o isci_remote_device.o isci_sysctl.o \
	isci_task_request.o isci_timer.o sati.o sati_abort_task_set.o \
	sati_atapi.o sati_device.o sati_inquiry.o sati_log_sense.o \
	sati_lun_reset.o sati_mode_pages.o sati_mode_select.o \
	sati_mode_sense.o sati_mode_sense_10.o sati_mode_sense_6.o \
	sati_move.o sati_passthrough.o sati_read.o sati_read_buffer.o \
	sati_read_capacity.o sati_reassign_blocks.o sati_report_luns.o \
	sati_request_sense.o sati_start_stop_unit.o \
	sati_synchronize_cache.o sati_test_unit_ready.o sati_unmap.o \
	sati_util.o sati_verify.o sati_write.o sati_write_and_verify.o \
	sati_write_buffer.o sati_write_long.o sci_abstract_list.o \
	sci_base_controller.o sci_base_domain.o sci_base_iterator.o \
	sci_base_library.o sci_base_logger.o \
	sci_base_memory_descriptor_list.o \
	sci_base_memory_descriptor_list_decorator.o sci_base_object.o \
	sci_base_observer.o sci_base_phy.o sci_base_port.o \
	sci_base_remote_device.o sci_base_request.o \
	sci_base_state_machine.o sci_base_state_machine_logger.o \
	sci_base_state_machine_observer.o sci_base_subject.o sci_util.o \
	scic_sds_controller.o scic_sds_library.o scic_sds_pci.o \
	scic_sds_phy.o scic_sds_port.o \
	scic_sds_port_configuration_agent.o scic_sds_remote_device.o \
	scic_sds_remote_node_context.o scic_sds_remote_node_table.o \
	scic_sds_request.o scic_sds_sgpio.o scic_sds_smp_remote_device.o \
	scic_sds_smp_request.o scic_sds_ssp_request.o \
	scic_sds_stp_packet_request.o scic_sds_stp_remote_device.o \
	scic_sds_stp_request.o scic_sds_unsolicited_frame_control.o \
	scif_sas_controller.o scif_sas_controller_state_handlers.o \
	scif_sas_controller_states.o scif_sas_domain.o \
	scif_sas_domain_state_handlers.o scif_sas_domain_states.o \
	scif_sas_high_priority_request_queue.o \
	scif_sas_internal_io_request.o scif_sas_io_request.o \
	scif_sas_io_request_state_handlers.o \
	scif_sas_io_request_states.o scif_sas_library.o \
	scif_sas_remote_device.o \
	scif_sas_remote_device_ready_substate_handlers.o \
	scif_sas_remote_device_ready_substates.o \
	scif_sas_remote_device_starting_substate_handlers.o \
	scif_sas_remote_device_starting_substates.o \
	scif_sas_remote_device_state_handlers.o \
	scif_sas_remote_device_states.o scif_sas_request.o \
	scif_sas_smp_activity_clear_affiliation.o \
	scif_sas_smp_io_request.o scif_sas_smp_phy.o \
	scif_sas_smp_remote_device.o scif_sas_stp_io_request.o \
	scif_sas_stp_remote_device.o scif_sas_stp_task_request.o \
	scif_sas_task_request.o scif_sas_task_request_state_handlers.o \
	scif_sas_task_request_states.o scif_sas_timer.o virtio.o \
	virtqueue.o virtio_bus_if.o virtio_if.o virtio_pci.o if_vtnet.o \
	virtio_blk.o virtio_balloon.o virtio_scsi.o syscons_isa.o \
	vga_isa.o kern_clocksource.o link_elf_obj.o ia32_reg.o \
	ia32_signal.o ia32_sigtramp.o ia32_syscall.o ia32_misc.o \
	freebsd32_ioctl.o freebsd32_misc.o freebsd32_syscalls.o \
	freebsd32_sysent.o ia32_sysvec.o imgact_elf32.o memmove.o \
	memset.o x86bios.o x86emu.o OsdEnvironment.o acpi_apm.o madt.o \
	srat.o powernow.o est.o hwpstate.o p4tcc.o atrtc.o clock.o isa.o \
	isa_dma.o nmi.o orm.o pci_bus.o qpi.o busdma_machdep.o \
	dump_machdep.o intr_machdep.o io_apic.o local_apic.o mca.o msi.o \
	nexus.o tsc.o 

CFILES=aic7xxx_reg_print.c aic79xx_reg_print.c $S/cam/cam.c \
	$S/cam/cam_compat.c $S/cam/cam_periph.c $S/cam/cam_queue.c \
	$S/cam/cam_sim.c $S/cam/cam_xpt.c $S/cam/ata/ata_all.c \
	$S/cam/ata/ata_xpt.c $S/cam/ata/ata_pmp.c $S/cam/scsi/scsi_xpt.c \
	$S/cam/scsi/scsi_all.c $S/cam/scsi/scsi_cd.c \
	$S/cam/scsi/scsi_ch.c $S/cam/ata/ata_da.c $S/cam/scsi/scsi_da.c \
	$S/cam/scsi/scsi_pass.c $S/cam/scsi/scsi_sa.c \
	$S/cam/scsi/scsi_enc.c $S/cam/scsi/scsi_enc_ses.c \
	$S/cam/scsi/scsi_enc_safte.c $S/cam/scsi/smp_all.c \
	$S/contrib/dev/acpica/dispatcher/dsargs.c \
	$S/contrib/dev/acpica/dispatcher/dscontrol.c \
	$S/contrib/dev/acpica/dispatcher/dsfield.c \
	$S/contrib/dev/acpica/dispatcher/dsinit.c \
	$S/contrib/dev/acpica/dispatcher/dsmethod.c \
	$S/contrib/dev/acpica/dispatcher/dsmthdat.c \
	$S/contrib/dev/acpica/dispatcher/dsobject.c \
	$S/contrib/dev/acpica/dispatcher/dsopcode.c \
	$S/contrib/dev/acpica/dispatcher/dsutils.c \
	$S/contrib/dev/acpica/dispatcher/dswexec.c \
	$S/contrib/dev/acpica/dispatcher/dswload.c \
	$S/contrib/dev/acpica/dispatcher/dswload2.c \
	$S/contrib/dev/acpica/dispatcher/dswscope.c \
	$S/contrib/dev/acpica/dispatcher/dswstate.c \
	$S/contrib/dev/acpica/events/evevent.c \
	$S/contrib/dev/acpica/events/evglock.c \
	$S/contrib/dev/acpica/events/evgpe.c \
	$S/contrib/dev/acpica/events/evgpeblk.c \
	$S/contrib/dev/acpica/events/evgpeinit.c \
	$S/contrib/dev/acpica/events/evgpeutil.c \
	$S/contrib/dev/acpica/events/evmisc.c \
	$S/contrib/dev/acpica/events/evregion.c \
	$S/contrib/dev/acpica/events/evrgnini.c \
	$S/contrib/dev/acpica/events/evsci.c \
	$S/contrib/dev/acpica/events/evxface.c \
	$S/contrib/dev/acpica/events/evxfevnt.c \
	$S/contrib/dev/acpica/events/evxfgpe.c \
	$S/contrib/dev/acpica/events/evxfregn.c \
	$S/contrib/dev/acpica/executer/exconfig.c \
	$S/contrib/dev/acpica/executer/exconvrt.c \
	$S/contrib/dev/acpica/executer/excreate.c \
	$S/contrib/dev/acpica/executer/exdebug.c \
	$S/contrib/dev/acpica/executer/exdump.c \
	$S/contrib/dev/acpica/executer/exfield.c \
	$S/contrib/dev/acpica/executer/exfldio.c \
	$S/contrib/dev/acpica/executer/exmisc.c \
	$S/contrib/dev/acpica/executer/exmutex.c \
	$S/contrib/dev/acpica/executer/exnames.c \
	$S/contrib/dev/acpica/executer/exoparg1.c \
	$S/contrib/dev/acpica/executer/exoparg2.c \
	$S/contrib/dev/acpica/executer/exoparg3.c \
	$S/contrib/dev/acpica/executer/exoparg6.c \
	$S/contrib/dev/acpica/executer/exprep.c \
	$S/contrib/dev/acpica/executer/exregion.c \
	$S/contrib/dev/acpica/executer/exresnte.c \
	$S/contrib/dev/acpica/executer/exresolv.c \
	$S/contrib/dev/acpica/executer/exresop.c \
	$S/contrib/dev/acpica/executer/exstore.c \
	$S/contrib/dev/acpica/executer/exstoren.c \
	$S/contrib/dev/acpica/executer/exstorob.c \
	$S/contrib/dev/acpica/executer/exsystem.c \
	$S/contrib/dev/acpica/executer/exutils.c \
	$S/contrib/dev/acpica/hardware/hwacpi.c \
	$S/contrib/dev/acpica/hardware/hwgpe.c \
	$S/contrib/dev/acpica/hardware/hwpci.c \
	$S/contrib/dev/acpica/hardware/hwregs.c \
	$S/contrib/dev/acpica/hardware/hwsleep.c \
	$S/contrib/dev/acpica/hardware/hwtimer.c \
	$S/contrib/dev/acpica/hardware/hwvalid.c \
	$S/contrib/dev/acpica/hardware/hwxface.c \
	$S/contrib/dev/acpica/namespace/nsaccess.c \
	$S/contrib/dev/acpica/namespace/nsalloc.c \
	$S/contrib/dev/acpica/namespace/nsdump.c \
	$S/contrib/dev/acpica/namespace/nseval.c \
	$S/contrib/dev/acpica/namespace/nsinit.c \
	$S/contrib/dev/acpica/namespace/nsload.c \
	$S/contrib/dev/acpica/namespace/nsnames.c \
	$S/contrib/dev/acpica/namespace/nsobject.c \
	$S/contrib/dev/acpica/namespace/nsparse.c \
	$S/contrib/dev/acpica/namespace/nspredef.c \
	$S/contrib/dev/acpica/namespace/nsrepair.c \
	$S/contrib/dev/acpica/namespace/nsrepair2.c \
	$S/contrib/dev/acpica/namespace/nssearch.c \
	$S/contrib/dev/acpica/namespace/nsutils.c \
	$S/contrib/dev/acpica/namespace/nswalk.c \
	$S/contrib/dev/acpica/namespace/nsxfeval.c \
	$S/contrib/dev/acpica/namespace/nsxfname.c \
	$S/contrib/dev/acpica/namespace/nsxfobj.c \
	$S/contrib/dev/acpica/parser/psargs.c \
	$S/contrib/dev/acpica/parser/psloop.c \
	$S/contrib/dev/acpica/parser/psopcode.c \
	$S/contrib/dev/acpica/parser/psparse.c \
	$S/contrib/dev/acpica/parser/psscope.c \
	$S/contrib/dev/acpica/parser/pstree.c \
	$S/contrib/dev/acpica/parser/psutils.c \
	$S/contrib/dev/acpica/parser/pswalk.c \
	$S/contrib/dev/acpica/parser/psxface.c \
	$S/contrib/dev/acpica/resources/rsaddr.c \
	$S/contrib/dev/acpica/resources/rscalc.c \
	$S/contrib/dev/acpica/resources/rscreate.c \
	$S/contrib/dev/acpica/resources/rsdump.c \
	$S/contrib/dev/acpica/resources/rsinfo.c \
	$S/contrib/dev/acpica/resources/rsio.c \
	$S/contrib/dev/acpica/resources/rsirq.c \
	$S/contrib/dev/acpica/resources/rslist.c \
	$S/contrib/dev/acpica/resources/rsmemory.c \
	$S/contrib/dev/acpica/resources/rsmisc.c \
	$S/contrib/dev/acpica/resources/rsutils.c \
	$S/contrib/dev/acpica/resources/rsxface.c \
	$S/contrib/dev/acpica/tables/tbfadt.c \
	$S/contrib/dev/acpica/tables/tbfind.c \
	$S/contrib/dev/acpica/tables/tbinstal.c \
	$S/contrib/dev/acpica/tables/tbutils.c \
	$S/contrib/dev/acpica/tables/tbxface.c \
	$S/contrib/dev/acpica/tables/tbxfroot.c \
	$S/contrib/dev/acpica/utilities/utalloc.c \
	$S/contrib/dev/acpica/utilities/utcache.c \
	$S/contrib/dev/acpica/utilities/utcopy.c \
	$S/contrib/dev/acpica/utilities/utdebug.c \
	$S/contrib/dev/acpica/utilities/utdecode.c \
	$S/contrib/dev/acpica/utilities/utdelete.c \
	$S/contrib/dev/acpica/utilities/uteval.c \
	$S/contrib/dev/acpica/utilities/utglobal.c \
	$S/contrib/dev/acpica/utilities/utids.c \
	$S/contrib/dev/acpica/utilities/utinit.c \
	$S/contrib/dev/acpica/utilities/utlock.c \
	$S/contrib/dev/acpica/utilities/utmath.c \
	$S/contrib/dev/acpica/utilities/utmisc.c \
	$S/contrib/dev/acpica/utilities/utmutex.c \
	$S/contrib/dev/acpica/utilities/utobject.c \
	$S/contrib/dev/acpica/utilities/utosi.c \
	$S/contrib/dev/acpica/utilities/utresrc.c \
	$S/contrib/dev/acpica/utilities/utstate.c \
	$S/contrib/dev/acpica/utilities/utxface.c \
	$S/contrib/dev/acpica/utilities/utxferror.c \
	$S/crypto/rijndael/rijndael-alg-fst.c \
	$S/crypto/rijndael/rijndael-api-fst.c \
	$S/crypto/rijndael/rijndael-api.c $S/crypto/sha1.c \
	$S/crypto/sha2/sha2.c $S/dev/aac/aac.c $S/dev/aac/aac_cam.c \
	$S/dev/aac/aac_debug.c $S/dev/aac/aac_disk.c \
	$S/dev/aac/aac_pci.c $S/dev/aacraid/aacraid.c \
	$S/dev/aacraid/aacraid_cam.c $S/dev/aacraid/aacraid_debug.c \
	$S/dev/aacraid/aacraid_pci.c $S/dev/acpica/Osd/OsdDebug.c \
	$S/dev/acpica/Osd/OsdHardware.c $S/dev/acpica/Osd/OsdInterrupt.c \
	$S/dev/acpica/Osd/OsdMemory.c $S/dev/acpica/Osd/OsdSchedule.c \
	$S/dev/acpica/Osd/OsdStream.c $S/dev/acpica/Osd/OsdSynch.c \
	$S/dev/acpica/Osd/OsdTable.c $S/dev/acpica/acpi.c \
	$S/dev/acpica/acpi_acad.c $S/dev/acpica/acpi_battery.c \
	$S/dev/acpica/acpi_button.c $S/dev/acpica/acpi_cmbat.c \
	$S/dev/acpica/acpi_cpu.c $S/dev/acpica/acpi_ec.c \
	$S/dev/acpica/acpi_hpet.c $S/dev/acpica/acpi_isab.c \
	$S/dev/acpica/acpi_lid.c $S/dev/acpica/acpi_package.c \
	$S/dev/acpica/acpi_pci.c $S/dev/acpica/acpi_pci_link.c \
	$S/dev/acpica/acpi_pcib.c $S/dev/acpica/acpi_pcib_acpi.c \
	$S/dev/acpica/acpi_pcib_pci.c $S/dev/acpica/acpi_perf.c \
	$S/dev/acpica/acpi_powerres.c $S/dev/acpica/acpi_quirk.c \
	$S/dev/acpica/acpi_resource.c $S/dev/acpica/acpi_smbat.c \
	$S/dev/acpica/acpi_thermal.c $S/dev/acpica/acpi_throttle.c \
	$S/dev/acpica/acpi_timer.c $S/dev/advansys/adv_pci.c \
	$S/dev/advansys/advansys.c $S/dev/advansys/advlib.c \
	$S/dev/advansys/advmcode.c $S/dev/advansys/adw_pci.c \
	$S/dev/advansys/adwcam.c $S/dev/advansys/adwlib.c \
	$S/dev/advansys/adwmcode.c $S/dev/ae/if_ae.c $S/dev/age/if_age.c \
	$S/dev/agp/agp.c $S/dev/ahci/ahci.c $S/dev/aic/aic.c \
	$S/dev/aic/aic_pccard.c $S/dev/aic7xxx/ahc_isa.c \
	$S/dev/aic7xxx/ahc_pci.c $S/dev/aic7xxx/ahd_pci.c \
	$S/dev/aic7xxx/aic7770.c $S/dev/aic7xxx/aic79xx.c \
	$S/dev/aic7xxx/aic79xx_osm.c $S/dev/aic7xxx/aic79xx_pci.c \
	$S/dev/aic7xxx/aic7xxx.c $S/dev/aic7xxx/aic7xxx_93cx6.c \
	$S/dev/aic7xxx/aic7xxx_osm.c $S/dev/aic7xxx/aic7xxx_pci.c \
	$S/dev/alc/if_alc.c $S/dev/ale/if_ale.c $S/dev/amr/amr.c \
	$S/dev/amr/amr_disk.c $S/dev/amr/amr_pci.c $S/dev/an/if_an.c \
	$S/dev/an/if_an_isa.c $S/dev/an/if_an_pccard.c \
	$S/dev/an/if_an_pci.c $S/dev/ata/ata-all.c $S/dev/ata/ata-dma.c \
	$S/dev/ata/ata-lowlevel.c $S/dev/ata/ata-queue.c \
	$S/dev/ata/ata-sata.c $S/dev/ata/ata-card.c $S/dev/ata/ata-isa.c \
	$S/dev/ata/ata-pci.c $S/dev/ata/chipsets/ata-ahci.c \
	$S/dev/ata/chipsets/ata-acard.c \
	$S/dev/ata/chipsets/ata-acerlabs.c \
	$S/dev/ata/chipsets/ata-adaptec.c $S/dev/ata/chipsets/ata-amd.c \
	$S/dev/ata/chipsets/ata-ati.c $S/dev/ata/chipsets/ata-cenatek.c \
	$S/dev/ata/chipsets/ata-cypress.c \
	$S/dev/ata/chipsets/ata-cyrix.c \
	$S/dev/ata/chipsets/ata-highpoint.c \
	$S/dev/ata/chipsets/ata-intel.c $S/dev/ata/chipsets/ata-ite.c \
	$S/dev/ata/chipsets/ata-jmicron.c \
	$S/dev/ata/chipsets/ata-marvell.c \
	$S/dev/ata/chipsets/ata-micron.c \
	$S/dev/ata/chipsets/ata-national.c \
	$S/dev/ata/chipsets/ata-netcell.c \
	$S/dev/ata/chipsets/ata-nvidia.c \
	$S/dev/ata/chipsets/ata-promise.c \
	$S/dev/ata/chipsets/ata-serverworks.c \
	$S/dev/ata/chipsets/ata-siliconimage.c \
	$S/dev/ata/chipsets/ata-sis.c $S/dev/ata/chipsets/ata-via.c \
	$S/dev/ath/if_ath_pci.c $S/dev/ath/if_ath.c \
	$S/dev/ath/if_ath_debug.c $S/dev/ath/if_ath_keycache.c \
	$S/dev/ath/if_ath_tx.c $S/dev/ath/if_ath_tx_ht.c \
	$S/dev/ath/if_ath_sysctl.c $S/dev/ath/ah_osdep.c \
	$S/dev/ath/ath_hal/ah.c $S/dev/ath/ath_hal/ah_eeprom_v1.c \
	$S/dev/ath/ath_hal/ah_eeprom_v3.c \
	$S/dev/ath/ath_hal/ah_eeprom_v14.c \
	$S/dev/ath/ath_hal/ah_eeprom_v4k.c \
	$S/dev/ath/ath_hal/ah_eeprom_9287.c \
	$S/dev/ath/ath_hal/ah_regdomain.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_attach.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_beacon.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_interrupts.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_keycache.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_misc.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_phy.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_power.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_recv.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_reset.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_xmit.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_attach.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_beacon.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_interrupts.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_keycache.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_misc.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_phy.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_power.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_recv.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_reset.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_xmit.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_ani.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_attach.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_beacon.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_eeprom.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_gpio.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_interrupts.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_keycache.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_misc.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_phy.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_power.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_recv.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_reset.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_rfgain.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_xmit.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_ani.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_attach.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_beacon.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_cal.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_cal_iq.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_cal_adcgain.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_cal_adcdc.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_eeprom.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_gpio.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_interrupts.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_keycache.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_misc.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_phy.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_power.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_recv.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_reset.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_xmit.c \
	$S/dev/ath/ath_hal/ar9001/ar9130_attach.c \
	$S/dev/ath/ath_hal/ar9001/ar9130_phy.c \
	$S/dev/ath/ath_hal/ar9001/ar9130_eeprom.c \
	$S/dev/ath/ath_hal/ar9001/ar9160_attach.c \
	$S/dev/ath/ath_hal/ar9002/ar9280_attach.c \
	$S/dev/ath/ath_hal/ar9002/ar9280_olc.c \
	$S/dev/ath/ath_hal/ar9002/ar9285_attach.c \
	$S/dev/ath/ath_hal/ar9002/ar9285_reset.c \
	$S/dev/ath/ath_hal/ar9002/ar9285_cal.c \
	$S/dev/ath/ath_hal/ar9002/ar9285_phy.c \
	$S/dev/ath/ath_hal/ar9002/ar9285_diversity.c \
	$S/dev/ath/ath_hal/ar9002/ar9287_attach.c \
	$S/dev/ath/ath_hal/ar9002/ar9287_reset.c \
	$S/dev/ath/ath_hal/ar9002/ar9287_cal.c \
	$S/dev/ath/ath_hal/ar9002/ar9287_olc.c \
	$S/dev/ath/ath_hal/ar5212/ar2413.c \
	$S/dev/ath/ath_hal/ar5212/ar2425.c \
	$S/dev/ath/ath_hal/ar5212/ar5111.c \
	$S/dev/ath/ath_hal/ar5212/ar5112.c \
	$S/dev/ath/ath_hal/ar5212/ar5413.c \
	$S/dev/ath/ath_hal/ar5416/ar2133.c \
	$S/dev/ath/ath_hal/ar9002/ar9280.c \
	$S/dev/ath/ath_hal/ar9002/ar9285.c \
	$S/dev/ath/ath_hal/ar9002/ar9287.c \
	$S/dev/ath/ath_rate/sample/sample.c \
	$S/dev/ath/ath_dfs/null/dfs_null.c $S/dev/bce/if_bce.c \
	$S/dev/bfe/if_bfe.c $S/dev/bge/if_bge.c $S/dev/buslogic/bt.c \
	$S/dev/buslogic/bt_isa.c $S/dev/buslogic/bt_pci.c \
	$S/dev/bxe/if_bxe.c $S/dev/bxe/bxe_link.c \
	$S/dev/cardbus/cardbus.c $S/dev/cardbus/cardbus_cis.c \
	$S/dev/cardbus/cardbus_device.c $S/dev/cas/if_cas.c \
	$S/dev/ciss/ciss.c $S/dev/cpufreq/ichss.c $S/dev/cs/if_cs.c \
	$S/dev/cs/if_cs_isa.c $S/dev/cs/if_cs_pccard.c $S/dev/dc/if_dc.c \
	$S/dev/dc/dcphy.c $S/dev/dc/pnphy.c $S/dev/de/if_de.c \
	$S/dev/dpt/dpt_pci.c $S/dev/dpt/dpt_scsi.c $S/dev/ed/if_ed.c \
	$S/dev/ed/if_ed_novell.c $S/dev/ed/if_ed_rtl80x9.c \
	$S/dev/ed/if_ed_pccard.c $S/dev/ed/if_ed_pci.c \
	$S/dev/e1000/if_em.c $S/dev/e1000/if_lem.c $S/dev/e1000/if_igb.c \
	$S/dev/e1000/e1000_80003es2lan.c $S/dev/e1000/e1000_82540.c \
	$S/dev/e1000/e1000_82541.c $S/dev/e1000/e1000_82542.c \
	$S/dev/e1000/e1000_82543.c $S/dev/e1000/e1000_82571.c \
	$S/dev/e1000/e1000_82575.c $S/dev/e1000/e1000_ich8lan.c \
	$S/dev/e1000/e1000_i210.c $S/dev/e1000/e1000_api.c \
	$S/dev/e1000/e1000_mac.c $S/dev/e1000/e1000_manage.c \
	$S/dev/e1000/e1000_nvm.c $S/dev/e1000/e1000_phy.c \
	$S/dev/e1000/e1000_vf.c $S/dev/e1000/e1000_mbx.c \
	$S/dev/e1000/e1000_osdep.c $S/dev/et/if_et.c $S/dev/ep/if_ep.c \
	$S/dev/ep/if_ep_isa.c $S/dev/ep/if_ep_pccard.c \
	$S/dev/esp/esp_pci.c $S/dev/esp/ncr53c9x.c $S/dev/ex/if_ex.c \
	$S/dev/ex/if_ex_isa.c $S/dev/ex/if_ex_pccard.c \
	$S/dev/exca/exca.c $S/dev/fb/splash.c $S/dev/fe/if_fe.c \
	$S/dev/fe/if_fe_pccard.c $S/dev/fxp/if_fxp.c $S/dev/fxp/inphy.c \
	$S/dev/gem/if_gem.c $S/dev/gem/if_gem_pci.c $S/dev/hme/if_hme.c \
	$S/dev/hme/if_hme_pci.c $S/dev/hptiop/hptiop.c $S/dev/ida/ida.c \
	$S/dev/ida/ida_disk.c $S/dev/ida/ida_pci.c $S/dev/iir/iir.c \
	$S/dev/iir/iir_ctrl.c $S/dev/iir/iir_pci.c $S/dev/ips/ips.c \
	$S/dev/ips/ips_commands.c $S/dev/ips/ips_disk.c \
	$S/dev/ips/ips_ioctl.c $S/dev/ips/ips_pci.c $S/dev/ipw/if_ipw.c \
	$S/dev/isp/isp.c $S/dev/isp/isp_freebsd.c \
	$S/dev/isp/isp_library.c $S/dev/isp/isp_pci.c \
	$S/dev/isp/isp_target.c $S/dev/iwi/if_iwi.c $S/dev/iwn/if_iwn.c \
	$S/dev/ixgbe/ixgbe.c $S/dev/ixgbe/ixv.c $S/dev/ixgbe/ixgbe_phy.c \
	$S/dev/ixgbe/ixgbe_api.c $S/dev/ixgbe/ixgbe_common.c \
	$S/dev/ixgbe/ixgbe_mbx.c $S/dev/ixgbe/ixgbe_vf.c \
	$S/dev/ixgbe/ixgbe_82598.c $S/dev/ixgbe/ixgbe_82599.c \
	$S/dev/ixgbe/ixgbe_x540.c $S/dev/ixgbe/ixgbe_dcb.c \
	$S/dev/ixgbe/ixgbe_dcb_82598.c $S/dev/ixgbe/ixgbe_dcb_82599.c \
	$S/dev/jme/if_jme.c $S/dev/kbdmux/kbdmux.c $S/dev/le/am7990.c \
	$S/dev/le/am79900.c $S/dev/le/if_le_pci.c $S/dev/le/lance.c \
	$S/dev/led/led.c $S/dev/lge/if_lge.c $S/dev/malo/if_malo.c \
	$S/dev/malo/if_malohal.c $S/dev/malo/if_malo_pci.c \
	$S/dev/md/md.c $S/dev/mem/memdev.c $S/dev/mem/memutil.c \
	$S/dev/mfi/mfi.c $S/dev/mfi/mfi_debug.c $S/dev/mfi/mfi_pci.c \
	$S/dev/mfi/mfi_disk.c $S/dev/mfi/mfi_syspd.c \
	$S/dev/mfi/mfi_tbolt.c $S/dev/mii/acphy.c $S/dev/mii/amphy.c \
	$S/dev/mii/atphy.c $S/dev/mii/axphy.c $S/dev/mii/bmtphy.c \
	$S/dev/mii/brgphy.c $S/dev/mii/ciphy.c $S/dev/mii/e1000phy.c \
	$S/dev/mii/gentbi.c $S/dev/mii/icsphy.c $S/dev/mii/ip1000phy.c \
	$S/dev/mii/jmphy.c $S/dev/mii/lxtphy.c $S/dev/mii/mii.c \
	$S/dev/mii/mii_bitbang.c $S/dev/mii/mii_physubr.c \
	$S/dev/mii/mlphy.c $S/dev/mii/nsgphy.c $S/dev/mii/nsphy.c \
	$S/dev/mii/nsphyter.c $S/dev/mii/pnaphy.c $S/dev/mii/qsphy.c \
	$S/dev/mii/rdcphy.c $S/dev/mii/rgephy.c $S/dev/mii/rlphy.c \
	$S/dev/mii/smcphy.c $S/dev/mii/tdkphy.c $S/dev/mii/tlphy.c \
	$S/dev/mii/truephy.c $S/dev/mii/ukphy.c $S/dev/mii/ukphy_subr.c \
	$S/dev/mii/xmphy.c $S/dev/mlx/mlx.c $S/dev/mlx/mlx_disk.c \
	$S/dev/mlx/mlx_pci.c $S/dev/mly/mly.c $S/dev/mps/mps.c \
	$S/dev/mps/mps_config.c $S/dev/mps/mps_mapping.c \
	$S/dev/mps/mps_pci.c $S/dev/mps/mps_sas.c \
	$S/dev/mps/mps_sas_lsi.c $S/dev/mps/mps_table.c \
	$S/dev/mps/mps_user.c $S/dev/mpt/mpt.c $S/dev/mpt/mpt_cam.c \
	$S/dev/mpt/mpt_debug.c $S/dev/mpt/mpt_pci.c \
	$S/dev/mpt/mpt_raid.c $S/dev/mpt/mpt_user.c $S/dev/msk/if_msk.c \
	$S/dev/mvs/mvs.c $S/dev/mvs/mvs_pci.c $S/dev/mwl/if_mwl.c \
	$S/dev/mwl/if_mwl_pci.c $S/dev/mwl/mwlhal.c $S/dev/nge/if_nge.c \
	$S/dev/null/null.c $S/dev/pccard/pccard.c \
	$S/dev/pccard/pccard_cis.c $S/dev/pccard/pccard_cis_quirks.c \
	$S/dev/pccard/pccard_device.c $S/dev/pccbb/pccbb.c \
	$S/dev/pccbb/pccbb_isa.c $S/dev/pccbb/pccbb_pci.c \
	$S/dev/pci/fixup_pci.c $S/dev/pci/hostb_pci.c \
	$S/dev/pci/ignore_pci.c $S/dev/pci/isa_pci.c $S/dev/pci/pci.c \
	$S/dev/pci/pci_pci.c $S/dev/pci/pci_subr.c $S/dev/pci/pci_user.c \
	$S/dev/pci/vga_pci.c $S/dev/pcn/if_pcn.c $S/dev/ppbus/if_plip.c \
	$S/dev/ppbus/lpt.c $S/dev/ppbus/ppb_1284.c \
	$S/dev/ppbus/ppb_base.c $S/dev/ppbus/ppb_msq.c \
	$S/dev/ppbus/ppbconf.c $S/dev/ppbus/ppi.c $S/dev/ppc/ppc.c \
	$S/dev/ppc/ppc_acpi.c $S/dev/ppc/ppc_isa.c $S/dev/ppc/ppc_pci.c \
	$S/dev/ppc/ppc_puc.c $S/dev/pty/pty.c $S/dev/puc/puc.c \
	$S/dev/puc/puc_cfg.c $S/dev/puc/puc_pccard.c \
	$S/dev/puc/puc_pci.c $S/dev/puc/pucdata.c $S/dev/ral/rt2560.c \
	$S/dev/ral/rt2661.c $S/dev/ral/rt2860.c $S/dev/ral/if_ral_pci.c \
	$S/dev/random/harvest.c $S/dev/random/hash.c \
	$S/dev/random/probe.c $S/dev/random/randomdev.c \
	$S/dev/random/randomdev_soft.c $S/dev/random/yarrow.c \
	$S/dev/re/if_re.c $S/dev/sf/if_sf.c $S/dev/sge/if_sge.c \
	$S/dev/siis/siis.c $S/dev/sis/if_sis.c $S/dev/sk/if_sk.c \
	$S/dev/sn/if_sn.c $S/dev/sn/if_sn_isa.c $S/dev/sn/if_sn_pccard.c \
	$S/dev/sound/clone.c $S/dev/sound/unit.c \
	$S/dev/sound/isa/sndbuf_dma.c $S/dev/sound/pci/cmi.c \
	$S/dev/sound/pci/csa.c $S/dev/sound/pci/csapcm.c \
	$S/dev/sound/pci/emu10kx.c $S/dev/sound/pci/emu10kx-pcm.c \
	$S/dev/sound/pci/emu10kx-midi.c $S/dev/sound/pci/es137x.c \
	$S/dev/sound/pci/ich.c $S/dev/sound/pci/via8233.c \
	$S/dev/sound/pci/hda/hdaa.c $S/dev/sound/pci/hda/hdaa_patches.c \
	$S/dev/sound/pci/hda/hdac.c $S/dev/sound/pci/hda/hdacc.c \
	$S/dev/sound/pcm/ac97.c $S/dev/sound/pcm/ac97_patch.c \
	$S/dev/sound/pcm/buffer.c $S/dev/sound/pcm/channel.c \
	$S/dev/sound/pcm/dsp.c $S/dev/sound/pcm/feeder.c \
	$S/dev/sound/pcm/feeder_chain.c $S/dev/sound/pcm/feeder_eq.c \
	$S/dev/sound/pcm/feeder_format.c \
	$S/dev/sound/pcm/feeder_matrix.c $S/dev/sound/pcm/feeder_mixer.c \
	$S/dev/sound/pcm/feeder_rate.c $S/dev/sound/pcm/feeder_volume.c \
	$S/dev/sound/pcm/mixer.c $S/dev/sound/pcm/sndstat.c \
	$S/dev/sound/pcm/sound.c $S/dev/sound/pcm/vchan.c \
	$S/dev/sound/usb/uaudio.c $S/dev/sound/usb/uaudio_pcm.c \
	$S/dev/sound/midi/midi.c $S/dev/sound/midi/mpu401.c \
	$S/dev/sound/midi/sequencer.c $S/dev/ste/if_ste.c \
	$S/dev/stge/if_stge.c $S/dev/sym/sym_hipd.c \
	$S/dev/syscons/schistory.c $S/dev/syscons/scmouse.c \
	$S/dev/syscons/scterm.c $S/dev/syscons/scvidctl.c \
	$S/dev/syscons/syscons.c $S/dev/syscons/sysmouse.c \
	$S/dev/ti/if_ti.c $S/dev/tl/if_tl.c $S/dev/trm/trm.c \
	$S/dev/twa/tw_cl_init.c $S/dev/twa/tw_cl_intr.c \
	$S/dev/twa/tw_cl_io.c $S/dev/twa/tw_cl_misc.c \
	$S/dev/twa/tw_osl_cam.c $S/dev/twa/tw_osl_freebsd.c \
	$S/dev/twe/twe.c $S/dev/twe/twe_freebsd.c $S/dev/tws/tws.c \
	$S/dev/tws/tws_cam.c $S/dev/tws/tws_hdm.c \
	$S/dev/tws/tws_services.c $S/dev/tws/tws_user.c \
	$S/dev/tx/if_tx.c $S/dev/txp/if_txp.c \
	$S/dev/uart/uart_bus_acpi.c $S/dev/uart/uart_bus_isa.c \
	$S/dev/uart/uart_bus_pccard.c $S/dev/uart/uart_bus_pci.c \
	$S/dev/uart/uart_bus_puc.c $S/dev/uart/uart_core.c \
	$S/dev/uart/uart_dev_ns8250.c $S/dev/uart/uart_subr.c \
	$S/dev/uart/uart_tty.c $S/dev/usb/controller/ehci.c \
	$S/dev/usb/controller/ehci_pci.c $S/dev/usb/controller/ohci.c \
	$S/dev/usb/controller/ohci_pci.c $S/dev/usb/controller/uhci.c \
	$S/dev/usb/controller/uhci_pci.c $S/dev/usb/controller/xhci.c \
	$S/dev/usb/controller/xhci_pci.c \
	$S/dev/usb/controller/usb_controller.c \
	$S/dev/usb/storage/umass.c $S/dev/usb/storage/urio.c \
	$S/dev/usb/usb_busdma.c $S/dev/usb/usb_compat_linux.c \
	$S/dev/usb/usb_core.c $S/dev/usb/usb_debug.c \
	$S/dev/usb/usb_dev.c $S/dev/usb/usb_device.c \
	$S/dev/usb/usb_dynamic.c $S/dev/usb/usb_error.c \
	$S/dev/usb/usb_generic.c $S/dev/usb/usb_handle_request.c \
	$S/dev/usb/usb_hid.c $S/dev/usb/usb_hub.c \
	$S/dev/usb/usb_lookup.c $S/dev/usb/usb_mbuf.c \
	$S/dev/usb/usb_msctest.c $S/dev/usb/usb_parse.c \
	$S/dev/usb/usb_pf.c $S/dev/usb/usb_process.c \
	$S/dev/usb/usb_request.c $S/dev/usb/usb_transfer.c \
	$S/dev/usb/usb_util.c $S/dev/usb/net/if_aue.c \
	$S/dev/usb/net/if_axe.c $S/dev/usb/net/if_cdce.c \
	$S/dev/usb/net/if_cue.c $S/dev/usb/net/if_kue.c \
	$S/dev/usb/net/if_rue.c $S/dev/usb/net/if_udav.c \
	$S/dev/usb/net/ruephy.c $S/dev/usb/net/usb_ethernet.c \
	$S/dev/usb/wlan/if_rum.c $S/dev/usb/wlan/if_run.c \
	$S/dev/usb/wlan/if_uath.c $S/dev/usb/wlan/if_upgt.c \
	$S/dev/usb/wlan/if_ural.c $S/dev/usb/wlan/if_urtw.c \
	$S/dev/usb/wlan/if_zyd.c $S/dev/usb/serial/u3g.c \
	$S/dev/usb/serial/uark.c $S/dev/usb/serial/ubsa.c \
	$S/dev/usb/serial/uftdi.c $S/dev/usb/serial/uipaq.c \
	$S/dev/usb/serial/ulpt.c $S/dev/usb/serial/uplcom.c \
	$S/dev/usb/serial/uslcom.c $S/dev/usb/serial/uvisor.c \
	$S/dev/usb/serial/uvscom.c $S/dev/usb/serial/usb_serial.c \
	$S/dev/usb/input/uhid.c $S/dev/usb/input/ukbd.c \
	$S/dev/usb/input/ums.c $S/dev/usb/quirk/usb_quirk.c \
	$S/dev/vge/if_vge.c $S/dev/vr/if_vr.c $S/dev/vx/if_vx.c \
	$S/dev/vx/if_vx_pci.c $S/dev/watchdog/watchdog.c \
	$S/dev/wb/if_wb.c $S/dev/wi/if_wi.c $S/dev/wi/if_wi_pccard.c \
	$S/dev/wi/if_wi_pci.c $S/dev/wpi/if_wpi.c $S/dev/xe/if_xe.c \
	$S/dev/xe/if_xe_pccard.c $S/dev/xl/if_xl.c $S/dev/xl/xlphy.c \
	$S/fs/deadfs/dead_vnops.c $S/fs/devfs/devfs_devs.c \
	$S/fs/devfs/devfs_dir.c $S/fs/devfs/devfs_rule.c \
	$S/fs/devfs/devfs_vfsops.c $S/fs/devfs/devfs_vnops.c \
	$S/fs/fifofs/fifo_vnops.c $S/fs/msdosfs/msdosfs_conv.c \
	$S/fs/msdosfs/msdosfs_denode.c $S/fs/msdosfs/msdosfs_fat.c \
	$S/fs/msdosfs/msdosfs_fileno.c $S/fs/msdosfs/msdosfs_lookup.c \
	$S/fs/msdosfs/msdosfs_vfsops.c $S/fs/msdosfs/msdosfs_vnops.c \
	$S/fs/nfs/nfs_commonkrpc.c $S/fs/nfs/nfs_commonsubs.c \
	$S/fs/nfs/nfs_commonport.c $S/fs/nfs/nfs_commonacl.c \
	$S/fs/nfsclient/nfs_clcomsubs.c $S/fs/nfsclient/nfs_clsubs.c \
	$S/fs/nfsclient/nfs_clstate.c $S/fs/nfsclient/nfs_clkrpc.c \
	$S/fs/nfsclient/nfs_clrpcops.c $S/fs/nfsclient/nfs_clvnops.c \
	$S/fs/nfsclient/nfs_clnode.c $S/fs/nfsclient/nfs_clvfsops.c \
	$S/fs/nfsclient/nfs_clport.c $S/fs/nfsclient/nfs_clbio.c \
	$S/fs/nfsclient/nfs_clnfsiod.c $S/fs/nfsserver/nfs_fha_new.c \
	$S/fs/nfsserver/nfs_nfsdsocket.c $S/fs/nfsserver/nfs_nfsdsubs.c \
	$S/fs/nfsserver/nfs_nfsdstate.c $S/fs/nfsserver/nfs_nfsdkrpc.c \
	$S/fs/nfsserver/nfs_nfsdserv.c $S/fs/nfsserver/nfs_nfsdport.c \
	$S/fs/nfsserver/nfs_nfsdcache.c $S/fs/procfs/procfs.c \
	$S/fs/procfs/procfs_ctl.c $S/fs/procfs/procfs_dbregs.c \
	$S/fs/procfs/procfs_fpregs.c $S/fs/procfs/procfs_ioctl.c \
	$S/fs/procfs/procfs_map.c $S/fs/procfs/procfs_mem.c \
	$S/fs/procfs/procfs_note.c $S/fs/procfs/procfs_osrel.c \
	$S/fs/procfs/procfs_regs.c $S/fs/procfs/procfs_rlimit.c \
	$S/fs/procfs/procfs_status.c $S/fs/procfs/procfs_type.c \
	$S/fs/pseudofs/pseudofs.c $S/fs/pseudofs/pseudofs_fileno.c \
	$S/fs/pseudofs/pseudofs_vncache.c \
	$S/fs/pseudofs/pseudofs_vnops.c $S/geom/geom_ctl.c \
	$S/geom/geom_dev.c $S/geom/geom_disk.c $S/geom/geom_dump.c \
	$S/geom/geom_event.c $S/geom/geom_io.c $S/geom/geom_kern.c \
	$S/geom/geom_slice.c $S/geom/geom_subr.c $S/geom/geom_vfs.c \
	$S/geom/label/g_label.c $S/geom/label/g_label_ext2fs.c \
	$S/geom/label/g_label_iso9660.c $S/geom/label/g_label_msdosfs.c \
	$S/geom/label/g_label_ntfs.c $S/geom/label/g_label_reiserfs.c \
	$S/geom/label/g_label_ufs.c $S/geom/label/g_label_gpt.c \
	$S/geom/part/g_part.c $S/geom/part/g_part_bsd.c \
	$S/geom/part/g_part_ebr.c $S/geom/part/g_part_gpt.c \
	$S/geom/part/g_part_mbr.c $S/geom/raid/g_raid.c \
	$S/geom/raid/g_raid_ctl.c $S/geom/raid/md_ddf.c \
	$S/geom/raid/md_intel.c $S/geom/raid/md_jmicron.c \
	$S/geom/raid/md_nvidia.c $S/geom/raid/md_promise.c \
	$S/geom/raid/md_sii.c $S/geom/raid/tr_concat.c \
	$S/geom/raid/tr_raid0.c $S/geom/raid/tr_raid1.c \
	$S/geom/raid/tr_raid1e.c $S/geom/raid/tr_raid5.c \
	$S/isa/isa_common.c $S/isa/isahint.c $S/fs/cd9660/cd9660_bmap.c \
	$S/fs/cd9660/cd9660_lookup.c $S/fs/cd9660/cd9660_node.c \
	$S/fs/cd9660/cd9660_rrip.c $S/fs/cd9660/cd9660_util.c \
	$S/fs/cd9660/cd9660_vfsops.c $S/fs/cd9660/cd9660_vnops.c \
	$S/kern/imgact_elf.c $S/kern/imgact_shell.c $S/kern/init_main.c \
	$S/kern/init_sysent.c $S/kern/ksched.c $S/kern/kern_acct.c \
	$S/kern/kern_clock.c $S/kern/kern_condvar.c $S/kern/kern_conf.c \
	$S/kern/kern_cons.c $S/kern/kern_cpu.c $S/kern/kern_cpuset.c \
	$S/kern/kern_context.c $S/kern/kern_descrip.c \
	$S/kern/kern_dtrace.c $S/kern/kern_environment.c \
	$S/kern/kern_et.c $S/kern/kern_event.c $S/kern/kern_exec.c \
	$S/kern/kern_exit.c $S/kern/kern_fail.c $S/kern/kern_fork.c \
	$S/kern/kern_hhook.c $S/kern/kern_idle.c $S/kern/kern_intr.c \
	$S/kern/kern_jail.c $S/kern/kern_khelp.c $S/kern/kern_kthread.c \
	$S/kern/kern_ktrace.c $S/kern/kern_linker.c $S/kern/kern_lock.c \
	$S/kern/kern_lockf.c $S/kern/kern_lockstat.c \
	$S/kern/kern_loginclass.c $S/kern/kern_malloc.c \
	$S/kern/kern_mbuf.c $S/kern/kern_mib.c $S/kern/kern_module.c \
	$S/kern/kern_mtxpool.c $S/kern/kern_mutex.c \
	$S/kern/kern_ntptime.c $S/kern/kern_osd.c $S/kern/kern_physio.c \
	$S/kern/kern_pmc.c $S/kern/kern_priv.c $S/kern/kern_proc.c \
	$S/kern/kern_prot.c $S/kern/kern_racct.c \
	$S/kern/kern_rangelock.c $S/kern/kern_rctl.c \
	$S/kern/kern_resource.c $S/kern/kern_rmlock.c \
	$S/kern/kern_rwlock.c $S/kern/kern_sdt.c $S/kern/kern_sema.c \
	$S/kern/kern_sharedpage.c $S/kern/kern_shutdown.c \
	$S/kern/kern_sig.c $S/kern/kern_switch.c $S/kern/kern_sx.c \
	$S/kern/kern_synch.c $S/kern/kern_syscalls.c \
	$S/kern/kern_sysctl.c $S/kern/kern_tc.c $S/kern/kern_thr.c \
	$S/kern/kern_thread.c $S/kern/kern_time.c $S/kern/kern_timeout.c \
	$S/kern/kern_umtx.c $S/kern/kern_uuid.c $S/kern/kern_xxx.c \
	$S/kern/link_elf.c $S/kern/md5c.c $S/kern/p1003_1b.c \
	$S/kern/posix4_mib.c $S/kern/sched_ule.c \
	$S/kern/stack_protector.c $S/kern/subr_acl_nfs4.c \
	$S/kern/subr_acl_posix1e.c $S/kern/subr_autoconf.c \
	$S/kern/subr_blist.c $S/kern/subr_bus.c $S/kern/subr_bus_dma.c \
	$S/kern/subr_bufring.c $S/kern/subr_clock.c \
	$S/kern/subr_devstat.c $S/kern/subr_disk.c \
	$S/kern/subr_eventhandler.c $S/kern/subr_fattime.c \
	$S/kern/subr_firmware.c $S/kern/subr_hash.c $S/kern/subr_hints.c \
	$S/kern/subr_kdb.c $S/kern/subr_kobj.c $S/kern/subr_lock.c \
	$S/kern/subr_log.c $S/kern/subr_module.c $S/kern/subr_msgbuf.c \
	$S/kern/subr_param.c $S/kern/subr_pcpu.c $S/kern/subr_power.c \
	$S/kern/subr_prf.c $S/kern/subr_prof.c $S/kern/subr_rman.c \
	$S/kern/subr_rtc.c $S/kern/subr_sbuf.c $S/kern/subr_scanf.c \
	$S/kern/subr_sglist.c $S/kern/subr_sleepqueue.c \
	$S/kern/subr_smp.c $S/kern/subr_stack.c $S/kern/subr_taskqueue.c \
	$S/kern/subr_trap.c $S/kern/subr_turnstile.c $S/kern/subr_uio.c \
	$S/kern/subr_unit.c $S/kern/sys_capability.c \
	$S/kern/sys_generic.c $S/kern/sys_pipe.c $S/kern/sys_procdesc.c \
	$S/kern/sys_process.c $S/kern/sys_socket.c $S/kern/syscalls.c \
	$S/kern/sysv_ipc.c $S/kern/sysv_msg.c $S/kern/sysv_sem.c \
	$S/kern/sysv_shm.c $S/kern/tty.c $S/kern/tty_info.c \
	$S/kern/tty_inq.c $S/kern/tty_outq.c $S/kern/tty_pts.c \
	$S/kern/tty_tty.c $S/kern/tty_ttydisc.c $S/kern/uipc_accf.c \
	$S/kern/uipc_domain.c $S/kern/uipc_mbuf.c $S/kern/uipc_mbuf2.c \
	$S/kern/uipc_shm.c $S/kern/uipc_sockbuf.c $S/kern/uipc_socket.c \
	$S/kern/uipc_syscalls.c $S/kern/uipc_usrreq.c $S/kern/vfs_acl.c \
	$S/kern/vfs_bio.c $S/kern/vfs_cache.c $S/kern/vfs_cluster.c \
	$S/kern/vfs_default.c $S/kern/vfs_export.c $S/kern/vfs_extattr.c \
	$S/kern/vfs_hash.c $S/kern/vfs_init.c $S/kern/vfs_lookup.c \
	$S/kern/vfs_mount.c $S/kern/vfs_mountroot.c $S/kern/vfs_subr.c \
	$S/kern/vfs_syscalls.c $S/kern/vfs_vnops.c \
	$S/libkern/arc4random.c $S/libkern/bcd.c $S/libkern/bsearch.c \
	$S/libkern/crc32.c $S/libkern/fnmatch.c $S/libkern/index.c \
	$S/libkern/inet_aton.c $S/libkern/inet_ntoa.c \
	$S/libkern/inet_ntop.c $S/libkern/inet_pton.c \
	$S/libkern/memcmp.c $S/libkern/qsort.c $S/libkern/qsort_r.c \
	$S/libkern/random.c $S/libkern/rindex.c $S/libkern/scanc.c \
	$S/libkern/skpc.c $S/libkern/strcasecmp.c $S/libkern/strcat.c \
	$S/libkern/strcmp.c $S/libkern/strcpy.c $S/libkern/strcspn.c \
	$S/libkern/strdup.c $S/libkern/strlcat.c $S/libkern/strlcpy.c \
	$S/libkern/strlen.c $S/libkern/strncmp.c $S/libkern/strncpy.c \
	$S/libkern/strnlen.c $S/libkern/strsep.c $S/libkern/strspn.c \
	$S/libkern/strstr.c $S/libkern/strtol.c $S/libkern/strtoq.c \
	$S/libkern/strtoul.c $S/libkern/strtouq.c $S/libkern/strvalid.c \
	$S/net/bpf.c $S/net/bpf_buffer.c $S/net/bpf_filter.c \
	$S/net/bpf_zerocopy.c $S/net/if.c $S/net/if_clone.c \
	$S/net/if_dead.c $S/net/if_ethersubr.c $S/net/if_faith.c \
	$S/net/if_gif.c $S/net/if_loop.c $S/net/if_llatbl.c \
	$S/net/if_media.c $S/net/if_mib.c $S/net/if_tun.c \
	$S/net/if_vlan.c $S/net/netisr.c $S/net/pfil.c $S/net/radix.c \
	$S/net/radix_mpath.c $S/net/raw_cb.c $S/net/raw_usrreq.c \
	$S/net/route.c $S/net/rtsock.c $S/net/zlib.c \
	$S/net80211/ieee80211.c $S/net80211/ieee80211_action.c \
	$S/net80211/ieee80211_ageq.c $S/net80211/ieee80211_adhoc.c \
	$S/net80211/ieee80211_amrr.c $S/net80211/ieee80211_crypto.c \
	$S/net80211/ieee80211_crypto_ccmp.c \
	$S/net80211/ieee80211_crypto_none.c \
	$S/net80211/ieee80211_crypto_tkip.c \
	$S/net80211/ieee80211_crypto_wep.c $S/net80211/ieee80211_dfs.c \
	$S/net80211/ieee80211_freebsd.c $S/net80211/ieee80211_hostap.c \
	$S/net80211/ieee80211_ht.c $S/net80211/ieee80211_hwmp.c \
	$S/net80211/ieee80211_input.c $S/net80211/ieee80211_ioctl.c \
	$S/net80211/ieee80211_mesh.c $S/net80211/ieee80211_monitor.c \
	$S/net80211/ieee80211_node.c $S/net80211/ieee80211_output.c \
	$S/net80211/ieee80211_phy.c $S/net80211/ieee80211_power.c \
	$S/net80211/ieee80211_proto.c $S/net80211/ieee80211_radiotap.c \
	$S/net80211/ieee80211_ratectl.c \
	$S/net80211/ieee80211_ratectl_none.c \
	$S/net80211/ieee80211_regdomain.c $S/net80211/ieee80211_scan.c \
	$S/net80211/ieee80211_scan_sta.c $S/net80211/ieee80211_sta.c \
	$S/net80211/ieee80211_wds.c $S/netinet/if_ether.c \
	$S/netinet/igmp.c $S/netinet/in.c $S/netinet/in_gif.c \
	$S/netinet/ip_id.c $S/netinet/in_mcast.c $S/netinet/in_pcb.c \
	$S/netinet/in_proto.c $S/netinet/in_rmx.c $S/netinet/ip_ecn.c \
	$S/netinet/ip_encap.c $S/netinet/ip_fastfwd.c \
	$S/netinet/ip_icmp.c $S/netinet/ip_input.c \
	$S/netinet/ip_options.c $S/netinet/ip_output.c \
	$S/netinet/raw_ip.c $S/netinet/cc/cc.c \
	$S/netinet/cc/cc_newreno.c $S/netinet/sctp_asconf.c \
	$S/netinet/sctp_auth.c $S/netinet/sctp_bsd_addr.c \
	$S/netinet/sctp_cc_functions.c $S/netinet/sctp_crc32.c \
	$S/netinet/sctp_indata.c $S/netinet/sctp_input.c \
	$S/netinet/sctp_output.c $S/netinet/sctp_pcb.c \
	$S/netinet/sctp_peeloff.c $S/netinet/sctp_ss_functions.c \
	$S/netinet/sctp_sysctl.c $S/netinet/sctp_timer.c \
	$S/netinet/sctp_usrreq.c $S/netinet/sctputil.c \
	$S/netinet/tcp_hostcache.c $S/netinet/tcp_input.c \
	$S/netinet/tcp_lro.c $S/netinet/tcp_output.c \
	$S/netinet/tcp_offload.c $S/netinet/tcp_reass.c \
	$S/netinet/tcp_sack.c $S/netinet/tcp_subr.c \
	$S/netinet/tcp_syncache.c $S/netinet/tcp_timer.c \
	$S/netinet/tcp_timewait.c $S/netinet/tcp_usrreq.c \
	$S/netinet/udp_usrreq.c $S/netinet6/dest6.c $S/netinet6/frag6.c \
	$S/netinet6/icmp6.c $S/netinet6/in6.c $S/netinet6/in6_cksum.c \
	$S/netinet6/in6_gif.c $S/netinet6/in6_ifattach.c \
	$S/netinet6/in6_mcast.c $S/netinet6/in6_pcb.c \
	$S/netinet6/in6_proto.c $S/netinet6/in6_rmx.c \
	$S/netinet6/in6_src.c $S/netinet6/ip6_forward.c \
	$S/netinet6/ip6_id.c $S/netinet6/ip6_input.c \
	$S/netinet6/ip6_output.c $S/netinet6/mld6.c $S/netinet6/nd6.c \
	$S/netinet6/nd6_nbr.c $S/netinet6/nd6_rtr.c \
	$S/netinet6/raw_ip6.c $S/netinet6/route6.c $S/netinet6/scope6.c \
	$S/netinet6/sctp6_usrreq.c $S/netinet6/udp6_usrreq.c \
	$S/nfs/nfs_diskless.c $S/nfs/nfs_fha.c $S/nfs/nfs_lock.c \
	$S/nfs/nfs_nfssvc.c $S/nlm/nlm_advlock.c $S/nlm/nlm_prot_clnt.c \
	$S/nlm/nlm_prot_impl.c $S/nlm/nlm_prot_server.c \
	$S/nlm/nlm_prot_svc.c $S/nlm/nlm_prot_xdr.c \
	$S/nlm/sm_inter_xdr.c $S/pci/if_rl.c $S/rpc/auth_none.c \
	$S/rpc/auth_unix.c $S/rpc/authunix_prot.c $S/rpc/clnt_dg.c \
	$S/rpc/clnt_rc.c $S/rpc/clnt_vc.c $S/rpc/getnetconfig.c \
	$S/rpc/replay.c $S/rpc/rpc_callmsg.c $S/rpc/rpc_generic.c \
	$S/rpc/rpc_prot.c $S/rpc/rpcb_clnt.c $S/rpc/rpcb_prot.c \
	$S/rpc/svc.c $S/rpc/svc_auth.c $S/rpc/svc_auth_unix.c \
	$S/rpc/svc_dg.c $S/rpc/svc_generic.c $S/rpc/svc_vc.c \
	$S/security/audit/audit.c $S/security/audit/audit_arg.c \
	$S/security/audit/audit_bsm.c \
	$S/security/audit/audit_bsm_domain.c \
	$S/security/audit/audit_bsm_errno.c \
	$S/security/audit/audit_bsm_fcntl.c \
	$S/security/audit/audit_bsm_klib.c \
	$S/security/audit/audit_bsm_socket_type.c \
	$S/security/audit/audit_bsm_token.c \
	$S/security/audit/audit_pipe.c \
	$S/security/audit/audit_syscalls.c \
	$S/security/audit/audit_trigger.c \
	$S/security/audit/audit_worker.c $S/security/mac/mac_audit.c \
	$S/security/mac/mac_cred.c $S/security/mac/mac_framework.c \
	$S/security/mac/mac_inet.c $S/security/mac/mac_inet6.c \
	$S/security/mac/mac_label.c $S/security/mac/mac_net.c \
	$S/security/mac/mac_pipe.c $S/security/mac/mac_posix_sem.c \
	$S/security/mac/mac_posix_shm.c $S/security/mac/mac_priv.c \
	$S/security/mac/mac_process.c $S/security/mac/mac_socket.c \
	$S/security/mac/mac_syscalls.c $S/security/mac/mac_system.c \
	$S/security/mac/mac_sysv_msg.c $S/security/mac/mac_sysv_sem.c \
	$S/security/mac/mac_sysv_shm.c $S/security/mac/mac_vfs.c \
	$S/teken/teken.c $S/ufs/ffs/ffs_alloc.c $S/ufs/ffs/ffs_balloc.c \
	$S/ufs/ffs/ffs_inode.c $S/ufs/ffs/ffs_snapshot.c \
	$S/ufs/ffs/ffs_softdep.c $S/ufs/ffs/ffs_subr.c \
	$S/ufs/ffs/ffs_tables.c $S/ufs/ffs/ffs_vfsops.c \
	$S/ufs/ffs/ffs_vnops.c $S/ufs/ffs/ffs_suspend.c \
	$S/ufs/ufs/ufs_acl.c $S/ufs/ufs/ufs_bmap.c \
	$S/ufs/ufs/ufs_dirhash.c $S/ufs/ufs/ufs_extattr.c \
	$S/ufs/ufs/ufs_gjournal.c $S/ufs/ufs/ufs_inode.c \
	$S/ufs/ufs/ufs_lookup.c $S/ufs/ufs/ufs_quota.c \
	$S/ufs/ufs/ufs_vfsops.c $S/ufs/ufs/ufs_vnops.c \
	$S/vm/default_pager.c $S/vm/device_pager.c $S/vm/phys_pager.c \
	$S/vm/sg_pager.c $S/vm/swap_pager.c $S/vm/uma_core.c \
	$S/vm/uma_dbg.c $S/vm/vm_contig.c $S/vm/vm_fault.c \
	$S/vm/vm_glue.c $S/vm/vm_init.c $S/vm/vm_kern.c $S/vm/vm_map.c \
	$S/vm/vm_meter.c $S/vm/vm_mmap.c $S/vm/vm_object.c \
	$S/vm/vm_page.c $S/vm/vm_pageout.c $S/vm/vm_pager.c \
	$S/vm/vm_phys.c $S/vm/vm_reserv.c $S/vm/vm_unix.c \
	$S/vm/vm_zeroidle.c $S/vm/vnode_pager.c $S/xdr/xdr.c \
	$S/xdr/xdr_array.c $S/xdr/xdr_mbuf.c $S/xdr/xdr_mem.c \
	$S/xdr/xdr_reference.c $S/xdr/xdr_sizeof.c \
	$S/amd64/acpica/acpi_machdep.c $S/amd64/acpica/acpi_wakeup.c \
	$S/amd64/amd64/amd64_mem.c $S/amd64/amd64/atomic.c \
	$S/amd64/amd64/autoconf.c $S/amd64/amd64/bios.c \
	$S/amd64/amd64/elf_machdep.c $S/amd64/amd64/fpu.c \
	$S/amd64/amd64/identcpu.c $S/amd64/amd64/in_cksum.c \
	$S/amd64/amd64/initcpu.c $S/amd64/amd64/io.c \
	$S/amd64/amd64/legacy.c $S/amd64/amd64/machdep.c \
	$S/amd64/amd64/mem.c $S/amd64/amd64/minidump_machdep.c \
	$S/amd64/amd64/mp_machdep.c $S/amd64/amd64/pmap.c \
	$S/amd64/amd64/ptrace_machdep.c $S/amd64/amd64/stack_machdep.c \
	$S/amd64/amd64/sys_machdep.c $S/amd64/amd64/trap.c \
	$S/amd64/amd64/uio_machdep.c $S/amd64/amd64/uma_machdep.c \
	$S/amd64/amd64/vm_machdep.c $S/amd64/pci/pci_cfgreg.c \
	$S/dev/agp/agp_amd64.c $S/dev/agp/agp_i810.c \
	$S/dev/agp/agp_intel.c $S/dev/agp/agp_via.c \
	$S/dev/arcmsr/arcmsr.c $S/dev/atkbdc/atkbd.c \
	$S/dev/atkbdc/atkbd_atkbdc.c $S/dev/atkbdc/atkbdc.c \
	$S/dev/atkbdc/atkbdc_isa.c $S/dev/atkbdc/atkbdc_subr.c \
	$S/dev/atkbdc/psm.c $S/dev/ed/if_ed_isa.c \
	$S/dev/ed/if_ed_wd80x3.c $S/dev/fb/fb.c $S/dev/fb/vesa.c \
	$S/dev/fb/vga.c $S/dev/io/iodev.c $S/dev/fdc/fdc.c \
	$S/dev/fdc/fdc_acpi.c $S/dev/fdc/fdc_isa.c \
	$S/dev/fdc/fdc_pccard.c $S/dev/hpt27xx/hpt27xx_os_bsd.c \
	$S/dev/hpt27xx/hpt27xx_osm_bsd.c $S/dev/hpt27xx/hpt27xx_config.c \
	$S/dev/hptmv/entry.c $S/dev/hptmv/mv.c $S/dev/hptmv/gui_lib.c \
	$S/dev/hptmv/hptproc.c $S/dev/hptmv/ioctl.c \
	$S/dev/hptnr/hptnr_os_bsd.c $S/dev/hptnr/hptnr_osm_bsd.c \
	$S/dev/hptnr/hptnr_config.c $S/dev/hptrr/hptrr_os_bsd.c \
	$S/dev/hptrr/hptrr_osm_bsd.c $S/dev/hptrr/hptrr_config.c \
	$S/dev/kbd/kbd.c $S/dev/nfe/if_nfe.c $S/dev/random/ivy.c \
	$S/dev/random/nehemiah.c $S/dev/syscons/scterm-teken.c \
	$S/dev/syscons/scvesactl.c $S/dev/syscons/scvgarndr.c \
	$S/dev/syscons/scvtb.c $S/dev/uart/uart_cpu_amd64.c \
	$S/dev/isci/isci.c $S/dev/isci/isci_controller.c \
	$S/dev/isci/isci_domain.c $S/dev/isci/isci_interrupt.c \
	$S/dev/isci/isci_io_request.c $S/dev/isci/isci_logger.c \
	$S/dev/isci/isci_oem_parameters.c \
	$S/dev/isci/isci_remote_device.c $S/dev/isci/isci_sysctl.c \
	$S/dev/isci/isci_task_request.c $S/dev/isci/isci_timer.c \
	$S/dev/isci/scil/sati.c $S/dev/isci/scil/sati_abort_task_set.c \
	$S/dev/isci/scil/sati_atapi.c $S/dev/isci/scil/sati_device.c \
	$S/dev/isci/scil/sati_inquiry.c \
	$S/dev/isci/scil/sati_log_sense.c \
	$S/dev/isci/scil/sati_lun_reset.c \
	$S/dev/isci/scil/sati_mode_pages.c \
	$S/dev/isci/scil/sati_mode_select.c \
	$S/dev/isci/scil/sati_mode_sense.c \
	$S/dev/isci/scil/sati_mode_sense_10.c \
	$S/dev/isci/scil/sati_mode_sense_6.c \
	$S/dev/isci/scil/sati_move.c $S/dev/isci/scil/sati_passthrough.c \
	$S/dev/isci/scil/sati_read.c $S/dev/isci/scil/sati_read_buffer.c \
	$S/dev/isci/scil/sati_read_capacity.c \
	$S/dev/isci/scil/sati_reassign_blocks.c \
	$S/dev/isci/scil/sati_report_luns.c \
	$S/dev/isci/scil/sati_request_sense.c \
	$S/dev/isci/scil/sati_start_stop_unit.c \
	$S/dev/isci/scil/sati_synchronize_cache.c \
	$S/dev/isci/scil/sati_test_unit_ready.c \
	$S/dev/isci/scil/sati_unmap.c $S/dev/isci/scil/sati_util.c \
	$S/dev/isci/scil/sati_verify.c $S/dev/isci/scil/sati_write.c \
	$S/dev/isci/scil/sati_write_and_verify.c \
	$S/dev/isci/scil/sati_write_buffer.c \
	$S/dev/isci/scil/sati_write_long.c \
	$S/dev/isci/scil/sci_abstract_list.c \
	$S/dev/isci/scil/sci_base_controller.c \
	$S/dev/isci/scil/sci_base_domain.c \
	$S/dev/isci/scil/sci_base_iterator.c \
	$S/dev/isci/scil/sci_base_library.c \
	$S/dev/isci/scil/sci_base_logger.c \
	$S/dev/isci/scil/sci_base_memory_descriptor_list.c \
	$S/dev/isci/scil/sci_base_memory_descriptor_list_decorator.c \
	$S/dev/isci/scil/sci_base_object.c \
	$S/dev/isci/scil/sci_base_observer.c \
	$S/dev/isci/scil/sci_base_phy.c $S/dev/isci/scil/sci_base_port.c \
	$S/dev/isci/scil/sci_base_remote_device.c \
	$S/dev/isci/scil/sci_base_request.c \
	$S/dev/isci/scil/sci_base_state_machine.c \
	$S/dev/isci/scil/sci_base_state_machine_logger.c \
	$S/dev/isci/scil/sci_base_state_machine_observer.c \
	$S/dev/isci/scil/sci_base_subject.c $S/dev/isci/scil/sci_util.c \
	$S/dev/isci/scil/scic_sds_controller.c \
	$S/dev/isci/scil/scic_sds_library.c \
	$S/dev/isci/scil/scic_sds_pci.c $S/dev/isci/scil/scic_sds_phy.c \
	$S/dev/isci/scil/scic_sds_port.c \
	$S/dev/isci/scil/scic_sds_port_configuration_agent.c \
	$S/dev/isci/scil/scic_sds_remote_device.c \
	$S/dev/isci/scil/scic_sds_remote_node_context.c \
	$S/dev/isci/scil/scic_sds_remote_node_table.c \
	$S/dev/isci/scil/scic_sds_request.c \
	$S/dev/isci/scil/scic_sds_sgpio.c \
	$S/dev/isci/scil/scic_sds_smp_remote_device.c \
	$S/dev/isci/scil/scic_sds_smp_request.c \
	$S/dev/isci/scil/scic_sds_ssp_request.c \
	$S/dev/isci/scil/scic_sds_stp_packet_request.c \
	$S/dev/isci/scil/scic_sds_stp_remote_device.c \
	$S/dev/isci/scil/scic_sds_stp_request.c \
	$S/dev/isci/scil/scic_sds_unsolicited_frame_control.c \
	$S/dev/isci/scil/scif_sas_controller.c \
	$S/dev/isci/scil/scif_sas_controller_state_handlers.c \
	$S/dev/isci/scil/scif_sas_controller_states.c \
	$S/dev/isci/scil/scif_sas_domain.c \
	$S/dev/isci/scil/scif_sas_domain_state_handlers.c \
	$S/dev/isci/scil/scif_sas_domain_states.c \
	$S/dev/isci/scil/scif_sas_high_priority_request_queue.c \
	$S/dev/isci/scil/scif_sas_internal_io_request.c \
	$S/dev/isci/scil/scif_sas_io_request.c \
	$S/dev/isci/scil/scif_sas_io_request_state_handlers.c \
	$S/dev/isci/scil/scif_sas_io_request_states.c \
	$S/dev/isci/scil/scif_sas_library.c \
	$S/dev/isci/scil/scif_sas_remote_device.c \
	$S/dev/isci/scil/scif_sas_remote_device_ready_substate_handlers.c \
	$S/dev/isci/scil/scif_sas_remote_device_ready_substates.c \
	$S/dev/isci/scil/scif_sas_remote_device_starting_substate_handlers.c \
	$S/dev/isci/scil/scif_sas_remote_device_starting_substates.c \
	$S/dev/isci/scil/scif_sas_remote_device_state_handlers.c \
	$S/dev/isci/scil/scif_sas_remote_device_states.c \
	$S/dev/isci/scil/scif_sas_request.c \
	$S/dev/isci/scil/scif_sas_smp_activity_clear_affiliation.c \
	$S/dev/isci/scil/scif_sas_smp_io_request.c \
	$S/dev/isci/scil/scif_sas_smp_phy.c \
	$S/dev/isci/scil/scif_sas_smp_remote_device.c \
	$S/dev/isci/scil/scif_sas_stp_io_request.c \
	$S/dev/isci/scil/scif_sas_stp_remote_device.c \
	$S/dev/isci/scil/scif_sas_stp_task_request.c \
	$S/dev/isci/scil/scif_sas_task_request.c \
	$S/dev/isci/scil/scif_sas_task_request_state_handlers.c \
	$S/dev/isci/scil/scif_sas_task_request_states.c \
	$S/dev/isci/scil/scif_sas_timer.c $S/dev/virtio/virtio.c \
	$S/dev/virtio/virtqueue.c $S/dev/virtio/pci/virtio_pci.c \
	$S/dev/virtio/network/if_vtnet.c \
	$S/dev/virtio/block/virtio_blk.c \
	$S/dev/virtio/balloon/virtio_balloon.c \
	$S/dev/virtio/scsi/virtio_scsi.c $S/isa/syscons_isa.c \
	$S/isa/vga_isa.c $S/kern/kern_clocksource.c \
	$S/kern/link_elf_obj.c $S/amd64/ia32/ia32_reg.c \
	$S/amd64/ia32/ia32_signal.c $S/amd64/ia32/ia32_syscall.c \
	$S/amd64/ia32/ia32_misc.c $S/compat/freebsd32/freebsd32_ioctl.c \
	$S/compat/freebsd32/freebsd32_misc.c \
	$S/compat/freebsd32/freebsd32_syscalls.c \
	$S/compat/freebsd32/freebsd32_sysent.c \
	$S/compat/ia32/ia32_sysvec.c $S/kern/imgact_elf32.c \
	$S/libkern/memmove.c $S/libkern/memset.c \
	$S/compat/x86bios/x86bios.c $S/contrib/x86emu/x86emu.c \
	$S/x86/acpica/OsdEnvironment.c $S/x86/acpica/acpi_apm.c \
	$S/x86/acpica/madt.c $S/x86/acpica/srat.c \
	$S/x86/cpufreq/powernow.c $S/x86/cpufreq/est.c \
	$S/x86/cpufreq/hwpstate.c $S/x86/cpufreq/p4tcc.c \
	$S/x86/isa/atrtc.c $S/x86/isa/clock.c $S/x86/isa/isa.c \
	$S/x86/isa/isa_dma.c $S/x86/isa/nmi.c $S/x86/isa/orm.c \
	$S/x86/pci/pci_bus.c $S/x86/pci/qpi.c \
	$S/x86/x86/busdma_machdep.c $S/x86/x86/dump_machdep.c \
	$S/x86/x86/intr_machdep.c $S/x86/x86/io_apic.c \
	$S/x86/x86/local_apic.c $S/x86/x86/mca.c $S/x86/x86/msi.c \
	$S/x86/x86/nexus.c $S/x86/x86/tsc.c 

SFILES=$S/amd64/acpica/acpi_switch.S $S/amd64/amd64/cpu_switch.S \
	$S/amd64/amd64/exception.S $S/amd64/amd64/locore.S \
	$S/amd64/amd64/mpboot.S $S/amd64/amd64/sigtramp.S \
	$S/amd64/amd64/support.S $S/amd64/ia32/ia32_sigtramp.S 

MFILES=$S/dev/agp/agp_if.m $S/dev/ata/ata_if.m $S/dev/eisa/eisa_if.m \
	$S/dev/mii/miibus_if.m $S/dev/mmc/mmcbr_if.m \
	$S/dev/mmc/mmcbus_if.m $S/dev/mvs/mvs_if.m \
	$S/dev/pccard/card_if.m $S/dev/pccard/power_if.m \
	$S/dev/pci/pci_if.m $S/dev/pci/pcib_if.m $S/dev/ppbus/ppbus_if.m \
	$S/dev/sound/pci/hda/hdac_if.m $S/dev/sound/pcm/ac97_if.m \
	$S/dev/sound/pcm/channel_if.m $S/dev/sound/pcm/feeder_if.m \
	$S/dev/sound/pcm/mixer_if.m $S/dev/sound/midi/mpu_if.m \
	$S/dev/sound/midi/mpufoi_if.m $S/dev/sound/midi/synth_if.m \
	$S/dev/uart/uart_if.m $S/dev/usb/usb_if.m \
	$S/geom/part/g_part_if.m $S/geom/raid/g_raid_md_if.m \
	$S/geom/raid/g_raid_tr_if.m $S/isa/isa_if.m $S/kern/bus_if.m \
	$S/kern/clock_if.m $S/kern/cpufreq_if.m $S/kern/device_if.m \
	$S/kern/linker_if.m $S/kern/serdev_if.m $S/dev/acpica/acpi_if.m \
	$S/dev/acpi_support/acpi_wmi_if.m $S/dev/virtio/virtio_bus_if.m \
	$S/dev/virtio/virtio_if.m 

CLEAN=acpi_quirks.h aicasm* y.tab.h aic7xxx_seq.h aic7xxx_reg.h \
	aic7xxx_reg_print.c aic79xx_seq.h aic79xx_reg.h \
	aic79xx_reg_print.c feeder_eq_gen.h feeder_rate_gen.h \
	snd_fxdiv_gen.h miidevs.h pccarddevs.h teken_state.h usbdevs.h \
	usbdevs_data.h ia32_genassym.o ia32_assym.h acpi_wakecode.o \
	acpi_wakecode.bin acpi_wakecode.h acpi_wakedata.h 

acpi_quirks.h: $S/tools/acpi_quirks2h.awk $S/dev/acpica/acpi_quirks
	${AWK} -f $S/tools/acpi_quirks2h.awk $S/dev/acpica/acpi_quirks

aicasm: $S/dev/aic7xxx/aicasm/*.[chyl]
	CC='${CC}' ${MAKE} -f $S/dev/aic7xxx/aicasm/Makefile MAKESRCPATH=$S/dev/aic7xxx/aicasm

aic7xxx_seq.h: $S/dev/aic7xxx/aic7xxx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic7xxx_seq.h -r aic7xxx_reg.h -p aic7xxx_reg_print.c -i $S/dev/aic7xxx/aic7xxx_osm.h $S/dev/aic7xxx/aic7xxx.seq

aic7xxx_reg.h: $S/dev/aic7xxx/aic7xxx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic7xxx_seq.h -r aic7xxx_reg.h -p aic7xxx_reg_print.c -i $S/dev/aic7xxx/aic7xxx_osm.h $S/dev/aic7xxx/aic7xxx.seq

aic7xxx_reg_print.c: $S/dev/aic7xxx/aic7xxx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic7xxx_seq.h -r aic7xxx_reg.h -p aic7xxx_reg_print.c -i $S/dev/aic7xxx/aic7xxx_osm.h $S/dev/aic7xxx/aic7xxx.seq

aic7xxx_reg_print.o: 
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic79xx_seq.h: $S/dev/aic7xxx/aic79xx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic79xx_seq.h -r aic79xx_reg.h -p aic79xx_reg_print.c -i $S/dev/aic7xxx/aic79xx_osm.h $S/dev/aic7xxx/aic79xx.seq

aic79xx_reg.h: $S/dev/aic7xxx/aic79xx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic79xx_seq.h -r aic79xx_reg.h -p aic79xx_reg_print.c -i $S/dev/aic7xxx/aic79xx_osm.h $S/dev/aic7xxx/aic79xx.seq

aic79xx_reg_print.c: $S/dev/aic7xxx/aic79xx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic79xx_seq.h -r aic79xx_reg.h -p aic79xx_reg_print.c -i $S/dev/aic7xxx/aic79xx_osm.h $S/dev/aic7xxx/aic79xx.seq

aic79xx_reg_print.o: 
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder_eq_gen.h: $S/tools/sound/feeder_eq_mkfilter.awk
	${AWK} -f $S/tools/sound/feeder_eq_mkfilter.awk -- ${FEEDER_EQ_PRESETS} > feeder_eq_gen.h

feeder_rate_gen.h: $S/tools/sound/feeder_rate_mkfilter.awk
	${AWK} -f $S/tools/sound/feeder_rate_mkfilter.awk -- ${FEEDER_RATE_PRESETS} > feeder_rate_gen.h

snd_fxdiv_gen.h: $S/tools/sound/snd_fxdiv_gen.awk
	${AWK} -f $S/tools/sound/snd_fxdiv_gen.awk -- > snd_fxdiv_gen.h

miidevs.h: $S/tools/miidevs2h.awk $S/dev/mii/miidevs
	${AWK} -f $S/tools/miidevs2h.awk $S/dev/mii/miidevs

pccarddevs.h: $S/tools/pccarddevs2h.awk $S/dev/pccard/pccarddevs
	${AWK} -f $S/tools/pccarddevs2h.awk $S/dev/pccard/pccarddevs

teken_state.h: $S/teken/gensequences $S/teken/sequences
	${AWK} -f $S/teken/gensequences $S/teken/sequences > teken_state.h

usbdevs.h: $S/tools/usbdevs2h.awk $S/dev/usb/usbdevs
	${AWK} -f $S/tools/usbdevs2h.awk $S/dev/usb/usbdevs -h

usbdevs_data.h: $S/tools/usbdevs2h.awk $S/dev/usb/usbdevs
	${AWK} -f $S/tools/usbdevs2h.awk $S/dev/usb/usbdevs -d

cam.ln: $S/cam/cam.c
	${NORMAL_LINT}

cam.o: $S/cam/cam.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cam_compat.ln: $S/cam/cam_compat.c
	${NORMAL_LINT}

cam_compat.o: $S/cam/cam_compat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cam_periph.ln: $S/cam/cam_periph.c
	${NORMAL_LINT}

cam_periph.o: $S/cam/cam_periph.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cam_queue.ln: $S/cam/cam_queue.c
	${NORMAL_LINT}

cam_queue.o: $S/cam/cam_queue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cam_sim.ln: $S/cam/cam_sim.c
	${NORMAL_LINT}

cam_sim.o: $S/cam/cam_sim.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cam_xpt.ln: $S/cam/cam_xpt.c
	${NORMAL_LINT}

cam_xpt.o: $S/cam/cam_xpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata_all.ln: $S/cam/ata/ata_all.c
	${NORMAL_LINT}

ata_all.o: $S/cam/ata/ata_all.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata_xpt.ln: $S/cam/ata/ata_xpt.c
	${NORMAL_LINT}

ata_xpt.o: $S/cam/ata/ata_xpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata_pmp.ln: $S/cam/ata/ata_pmp.c
	${NORMAL_LINT}

ata_pmp.o: $S/cam/ata/ata_pmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_xpt.ln: $S/cam/scsi/scsi_xpt.c
	${NORMAL_LINT}

scsi_xpt.o: $S/cam/scsi/scsi_xpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_all.ln: $S/cam/scsi/scsi_all.c
	${NORMAL_LINT}

scsi_all.o: $S/cam/scsi/scsi_all.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_cd.ln: $S/cam/scsi/scsi_cd.c
	${NORMAL_LINT}

scsi_cd.o: $S/cam/scsi/scsi_cd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_ch.ln: $S/cam/scsi/scsi_ch.c
	${NORMAL_LINT}

scsi_ch.o: $S/cam/scsi/scsi_ch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata_da.ln: $S/cam/ata/ata_da.c
	${NORMAL_LINT}

ata_da.o: $S/cam/ata/ata_da.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_da.ln: $S/cam/scsi/scsi_da.c
	${NORMAL_LINT}

scsi_da.o: $S/cam/scsi/scsi_da.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_pass.ln: $S/cam/scsi/scsi_pass.c
	${NORMAL_LINT}

scsi_pass.o: $S/cam/scsi/scsi_pass.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_sa.ln: $S/cam/scsi/scsi_sa.c
	${NORMAL_LINT}

scsi_sa.o: $S/cam/scsi/scsi_sa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_enc.ln: $S/cam/scsi/scsi_enc.c
	${NORMAL_LINT}

scsi_enc.o: $S/cam/scsi/scsi_enc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_enc_ses.ln: $S/cam/scsi/scsi_enc_ses.c
	${NORMAL_LINT}

scsi_enc_ses.o: $S/cam/scsi/scsi_enc_ses.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scsi_enc_safte.ln: $S/cam/scsi/scsi_enc_safte.c
	${NORMAL_LINT}

scsi_enc_safte.o: $S/cam/scsi/scsi_enc_safte.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

smp_all.ln: $S/cam/scsi/smp_all.c
	${NORMAL_LINT}

smp_all.o: $S/cam/scsi/smp_all.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dsargs.ln: $S/contrib/dev/acpica/dispatcher/dsargs.c
	${NORMAL_LINT}

dsargs.o: $S/contrib/dev/acpica/dispatcher/dsargs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dscontrol.ln: $S/contrib/dev/acpica/dispatcher/dscontrol.c
	${NORMAL_LINT}

dscontrol.o: $S/contrib/dev/acpica/dispatcher/dscontrol.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dsfield.ln: $S/contrib/dev/acpica/dispatcher/dsfield.c
	${NORMAL_LINT}

dsfield.o: $S/contrib/dev/acpica/dispatcher/dsfield.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dsinit.ln: $S/contrib/dev/acpica/dispatcher/dsinit.c
	${NORMAL_LINT}

dsinit.o: $S/contrib/dev/acpica/dispatcher/dsinit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dsmethod.ln: $S/contrib/dev/acpica/dispatcher/dsmethod.c
	${NORMAL_LINT}

dsmethod.o: $S/contrib/dev/acpica/dispatcher/dsmethod.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dsmthdat.ln: $S/contrib/dev/acpica/dispatcher/dsmthdat.c
	${NORMAL_LINT}

dsmthdat.o: $S/contrib/dev/acpica/dispatcher/dsmthdat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dsobject.ln: $S/contrib/dev/acpica/dispatcher/dsobject.c
	${NORMAL_LINT}

dsobject.o: $S/contrib/dev/acpica/dispatcher/dsobject.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dsopcode.ln: $S/contrib/dev/acpica/dispatcher/dsopcode.c
	${NORMAL_LINT}

dsopcode.o: $S/contrib/dev/acpica/dispatcher/dsopcode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dsutils.ln: $S/contrib/dev/acpica/dispatcher/dsutils.c
	${NORMAL_LINT}

dsutils.o: $S/contrib/dev/acpica/dispatcher/dsutils.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dswexec.ln: $S/contrib/dev/acpica/dispatcher/dswexec.c
	${NORMAL_LINT}

dswexec.o: $S/contrib/dev/acpica/dispatcher/dswexec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dswload.ln: $S/contrib/dev/acpica/dispatcher/dswload.c
	${NORMAL_LINT}

dswload.o: $S/contrib/dev/acpica/dispatcher/dswload.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dswload2.ln: $S/contrib/dev/acpica/dispatcher/dswload2.c
	${NORMAL_LINT}

dswload2.o: $S/contrib/dev/acpica/dispatcher/dswload2.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dswscope.ln: $S/contrib/dev/acpica/dispatcher/dswscope.c
	${NORMAL_LINT}

dswscope.o: $S/contrib/dev/acpica/dispatcher/dswscope.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dswstate.ln: $S/contrib/dev/acpica/dispatcher/dswstate.c
	${NORMAL_LINT}

dswstate.o: $S/contrib/dev/acpica/dispatcher/dswstate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evevent.ln: $S/contrib/dev/acpica/events/evevent.c
	${NORMAL_LINT}

evevent.o: $S/contrib/dev/acpica/events/evevent.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evglock.ln: $S/contrib/dev/acpica/events/evglock.c
	${NORMAL_LINT}

evglock.o: $S/contrib/dev/acpica/events/evglock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evgpe.ln: $S/contrib/dev/acpica/events/evgpe.c
	${NORMAL_LINT}

evgpe.o: $S/contrib/dev/acpica/events/evgpe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evgpeblk.ln: $S/contrib/dev/acpica/events/evgpeblk.c
	${NORMAL_LINT}

evgpeblk.o: $S/contrib/dev/acpica/events/evgpeblk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evgpeinit.ln: $S/contrib/dev/acpica/events/evgpeinit.c
	${NORMAL_LINT}

evgpeinit.o: $S/contrib/dev/acpica/events/evgpeinit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evgpeutil.ln: $S/contrib/dev/acpica/events/evgpeutil.c
	${NORMAL_LINT}

evgpeutil.o: $S/contrib/dev/acpica/events/evgpeutil.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evmisc.ln: $S/contrib/dev/acpica/events/evmisc.c
	${NORMAL_LINT}

evmisc.o: $S/contrib/dev/acpica/events/evmisc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evregion.ln: $S/contrib/dev/acpica/events/evregion.c
	${NORMAL_LINT}

evregion.o: $S/contrib/dev/acpica/events/evregion.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evrgnini.ln: $S/contrib/dev/acpica/events/evrgnini.c
	${NORMAL_LINT}

evrgnini.o: $S/contrib/dev/acpica/events/evrgnini.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evsci.ln: $S/contrib/dev/acpica/events/evsci.c
	${NORMAL_LINT}

evsci.o: $S/contrib/dev/acpica/events/evsci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evxface.ln: $S/contrib/dev/acpica/events/evxface.c
	${NORMAL_LINT}

evxface.o: $S/contrib/dev/acpica/events/evxface.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evxfevnt.ln: $S/contrib/dev/acpica/events/evxfevnt.c
	${NORMAL_LINT}

evxfevnt.o: $S/contrib/dev/acpica/events/evxfevnt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evxfgpe.ln: $S/contrib/dev/acpica/events/evxfgpe.c
	${NORMAL_LINT}

evxfgpe.o: $S/contrib/dev/acpica/events/evxfgpe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

evxfregn.ln: $S/contrib/dev/acpica/events/evxfregn.c
	${NORMAL_LINT}

evxfregn.o: $S/contrib/dev/acpica/events/evxfregn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exconfig.ln: $S/contrib/dev/acpica/executer/exconfig.c
	${NORMAL_LINT}

exconfig.o: $S/contrib/dev/acpica/executer/exconfig.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exconvrt.ln: $S/contrib/dev/acpica/executer/exconvrt.c
	${NORMAL_LINT}

exconvrt.o: $S/contrib/dev/acpica/executer/exconvrt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

excreate.ln: $S/contrib/dev/acpica/executer/excreate.c
	${NORMAL_LINT}

excreate.o: $S/contrib/dev/acpica/executer/excreate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exdebug.ln: $S/contrib/dev/acpica/executer/exdebug.c
	${NORMAL_LINT}

exdebug.o: $S/contrib/dev/acpica/executer/exdebug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exdump.ln: $S/contrib/dev/acpica/executer/exdump.c
	${NORMAL_LINT}

exdump.o: $S/contrib/dev/acpica/executer/exdump.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exfield.ln: $S/contrib/dev/acpica/executer/exfield.c
	${NORMAL_LINT}

exfield.o: $S/contrib/dev/acpica/executer/exfield.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exfldio.ln: $S/contrib/dev/acpica/executer/exfldio.c
	${NORMAL_LINT}

exfldio.o: $S/contrib/dev/acpica/executer/exfldio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exmisc.ln: $S/contrib/dev/acpica/executer/exmisc.c
	${NORMAL_LINT}

exmisc.o: $S/contrib/dev/acpica/executer/exmisc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exmutex.ln: $S/contrib/dev/acpica/executer/exmutex.c
	${NORMAL_LINT}

exmutex.o: $S/contrib/dev/acpica/executer/exmutex.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exnames.ln: $S/contrib/dev/acpica/executer/exnames.c
	${NORMAL_LINT}

exnames.o: $S/contrib/dev/acpica/executer/exnames.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exoparg1.ln: $S/contrib/dev/acpica/executer/exoparg1.c
	${NORMAL_LINT}

exoparg1.o: $S/contrib/dev/acpica/executer/exoparg1.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exoparg2.ln: $S/contrib/dev/acpica/executer/exoparg2.c
	${NORMAL_LINT}

exoparg2.o: $S/contrib/dev/acpica/executer/exoparg2.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exoparg3.ln: $S/contrib/dev/acpica/executer/exoparg3.c
	${NORMAL_LINT}

exoparg3.o: $S/contrib/dev/acpica/executer/exoparg3.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exoparg6.ln: $S/contrib/dev/acpica/executer/exoparg6.c
	${NORMAL_LINT}

exoparg6.o: $S/contrib/dev/acpica/executer/exoparg6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exprep.ln: $S/contrib/dev/acpica/executer/exprep.c
	${NORMAL_LINT}

exprep.o: $S/contrib/dev/acpica/executer/exprep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exregion.ln: $S/contrib/dev/acpica/executer/exregion.c
	${NORMAL_LINT}

exregion.o: $S/contrib/dev/acpica/executer/exregion.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exresnte.ln: $S/contrib/dev/acpica/executer/exresnte.c
	${NORMAL_LINT}

exresnte.o: $S/contrib/dev/acpica/executer/exresnte.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exresolv.ln: $S/contrib/dev/acpica/executer/exresolv.c
	${NORMAL_LINT}

exresolv.o: $S/contrib/dev/acpica/executer/exresolv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exresop.ln: $S/contrib/dev/acpica/executer/exresop.c
	${NORMAL_LINT}

exresop.o: $S/contrib/dev/acpica/executer/exresop.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exstore.ln: $S/contrib/dev/acpica/executer/exstore.c
	${NORMAL_LINT}

exstore.o: $S/contrib/dev/acpica/executer/exstore.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exstoren.ln: $S/contrib/dev/acpica/executer/exstoren.c
	${NORMAL_LINT}

exstoren.o: $S/contrib/dev/acpica/executer/exstoren.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exstorob.ln: $S/contrib/dev/acpica/executer/exstorob.c
	${NORMAL_LINT}

exstorob.o: $S/contrib/dev/acpica/executer/exstorob.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exsystem.ln: $S/contrib/dev/acpica/executer/exsystem.c
	${NORMAL_LINT}

exsystem.o: $S/contrib/dev/acpica/executer/exsystem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exutils.ln: $S/contrib/dev/acpica/executer/exutils.c
	${NORMAL_LINT}

exutils.o: $S/contrib/dev/acpica/executer/exutils.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwacpi.ln: $S/contrib/dev/acpica/hardware/hwacpi.c
	${NORMAL_LINT}

hwacpi.o: $S/contrib/dev/acpica/hardware/hwacpi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwgpe.ln: $S/contrib/dev/acpica/hardware/hwgpe.c
	${NORMAL_LINT}

hwgpe.o: $S/contrib/dev/acpica/hardware/hwgpe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwpci.ln: $S/contrib/dev/acpica/hardware/hwpci.c
	${NORMAL_LINT}

hwpci.o: $S/contrib/dev/acpica/hardware/hwpci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwregs.ln: $S/contrib/dev/acpica/hardware/hwregs.c
	${NORMAL_LINT}

hwregs.o: $S/contrib/dev/acpica/hardware/hwregs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwsleep.ln: $S/contrib/dev/acpica/hardware/hwsleep.c
	${NORMAL_LINT}

hwsleep.o: $S/contrib/dev/acpica/hardware/hwsleep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwtimer.ln: $S/contrib/dev/acpica/hardware/hwtimer.c
	${NORMAL_LINT}

hwtimer.o: $S/contrib/dev/acpica/hardware/hwtimer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwvalid.ln: $S/contrib/dev/acpica/hardware/hwvalid.c
	${NORMAL_LINT}

hwvalid.o: $S/contrib/dev/acpica/hardware/hwvalid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwxface.ln: $S/contrib/dev/acpica/hardware/hwxface.c
	${NORMAL_LINT}

hwxface.o: $S/contrib/dev/acpica/hardware/hwxface.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsaccess.ln: $S/contrib/dev/acpica/namespace/nsaccess.c
	${NORMAL_LINT}

nsaccess.o: $S/contrib/dev/acpica/namespace/nsaccess.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsalloc.ln: $S/contrib/dev/acpica/namespace/nsalloc.c
	${NORMAL_LINT}

nsalloc.o: $S/contrib/dev/acpica/namespace/nsalloc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsdump.ln: $S/contrib/dev/acpica/namespace/nsdump.c
	${NORMAL_LINT}

nsdump.o: $S/contrib/dev/acpica/namespace/nsdump.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nseval.ln: $S/contrib/dev/acpica/namespace/nseval.c
	${NORMAL_LINT}

nseval.o: $S/contrib/dev/acpica/namespace/nseval.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsinit.ln: $S/contrib/dev/acpica/namespace/nsinit.c
	${NORMAL_LINT}

nsinit.o: $S/contrib/dev/acpica/namespace/nsinit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsload.ln: $S/contrib/dev/acpica/namespace/nsload.c
	${NORMAL_LINT}

nsload.o: $S/contrib/dev/acpica/namespace/nsload.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsnames.ln: $S/contrib/dev/acpica/namespace/nsnames.c
	${NORMAL_LINT}

nsnames.o: $S/contrib/dev/acpica/namespace/nsnames.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsobject.ln: $S/contrib/dev/acpica/namespace/nsobject.c
	${NORMAL_LINT}

nsobject.o: $S/contrib/dev/acpica/namespace/nsobject.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsparse.ln: $S/contrib/dev/acpica/namespace/nsparse.c
	${NORMAL_LINT}

nsparse.o: $S/contrib/dev/acpica/namespace/nsparse.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nspredef.ln: $S/contrib/dev/acpica/namespace/nspredef.c
	${NORMAL_LINT}

nspredef.o: $S/contrib/dev/acpica/namespace/nspredef.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsrepair.ln: $S/contrib/dev/acpica/namespace/nsrepair.c
	${NORMAL_LINT}

nsrepair.o: $S/contrib/dev/acpica/namespace/nsrepair.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsrepair2.ln: $S/contrib/dev/acpica/namespace/nsrepair2.c
	${NORMAL_LINT}

nsrepair2.o: $S/contrib/dev/acpica/namespace/nsrepair2.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nssearch.ln: $S/contrib/dev/acpica/namespace/nssearch.c
	${NORMAL_LINT}

nssearch.o: $S/contrib/dev/acpica/namespace/nssearch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsutils.ln: $S/contrib/dev/acpica/namespace/nsutils.c
	${NORMAL_LINT}

nsutils.o: $S/contrib/dev/acpica/namespace/nsutils.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nswalk.ln: $S/contrib/dev/acpica/namespace/nswalk.c
	${NORMAL_LINT}

nswalk.o: $S/contrib/dev/acpica/namespace/nswalk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsxfeval.ln: $S/contrib/dev/acpica/namespace/nsxfeval.c
	${NORMAL_LINT}

nsxfeval.o: $S/contrib/dev/acpica/namespace/nsxfeval.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsxfname.ln: $S/contrib/dev/acpica/namespace/nsxfname.c
	${NORMAL_LINT}

nsxfname.o: $S/contrib/dev/acpica/namespace/nsxfname.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsxfobj.ln: $S/contrib/dev/acpica/namespace/nsxfobj.c
	${NORMAL_LINT}

nsxfobj.o: $S/contrib/dev/acpica/namespace/nsxfobj.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

psargs.ln: $S/contrib/dev/acpica/parser/psargs.c
	${NORMAL_LINT}

psargs.o: $S/contrib/dev/acpica/parser/psargs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

psloop.ln: $S/contrib/dev/acpica/parser/psloop.c
	${NORMAL_LINT}

psloop.o: $S/contrib/dev/acpica/parser/psloop.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

psopcode.ln: $S/contrib/dev/acpica/parser/psopcode.c
	${NORMAL_LINT}

psopcode.o: $S/contrib/dev/acpica/parser/psopcode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

psparse.ln: $S/contrib/dev/acpica/parser/psparse.c
	${NORMAL_LINT}

psparse.o: $S/contrib/dev/acpica/parser/psparse.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

psscope.ln: $S/contrib/dev/acpica/parser/psscope.c
	${NORMAL_LINT}

psscope.o: $S/contrib/dev/acpica/parser/psscope.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pstree.ln: $S/contrib/dev/acpica/parser/pstree.c
	${NORMAL_LINT}

pstree.o: $S/contrib/dev/acpica/parser/pstree.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

psutils.ln: $S/contrib/dev/acpica/parser/psutils.c
	${NORMAL_LINT}

psutils.o: $S/contrib/dev/acpica/parser/psutils.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pswalk.ln: $S/contrib/dev/acpica/parser/pswalk.c
	${NORMAL_LINT}

pswalk.o: $S/contrib/dev/acpica/parser/pswalk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

psxface.ln: $S/contrib/dev/acpica/parser/psxface.c
	${NORMAL_LINT}

psxface.o: $S/contrib/dev/acpica/parser/psxface.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsaddr.ln: $S/contrib/dev/acpica/resources/rsaddr.c
	${NORMAL_LINT}

rsaddr.o: $S/contrib/dev/acpica/resources/rsaddr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rscalc.ln: $S/contrib/dev/acpica/resources/rscalc.c
	${NORMAL_LINT}

rscalc.o: $S/contrib/dev/acpica/resources/rscalc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rscreate.ln: $S/contrib/dev/acpica/resources/rscreate.c
	${NORMAL_LINT}

rscreate.o: $S/contrib/dev/acpica/resources/rscreate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsdump.ln: $S/contrib/dev/acpica/resources/rsdump.c
	${NORMAL_LINT}

rsdump.o: $S/contrib/dev/acpica/resources/rsdump.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsinfo.ln: $S/contrib/dev/acpica/resources/rsinfo.c
	${NORMAL_LINT}

rsinfo.o: $S/contrib/dev/acpica/resources/rsinfo.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsio.ln: $S/contrib/dev/acpica/resources/rsio.c
	${NORMAL_LINT}

rsio.o: $S/contrib/dev/acpica/resources/rsio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsirq.ln: $S/contrib/dev/acpica/resources/rsirq.c
	${NORMAL_LINT}

rsirq.o: $S/contrib/dev/acpica/resources/rsirq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rslist.ln: $S/contrib/dev/acpica/resources/rslist.c
	${NORMAL_LINT}

rslist.o: $S/contrib/dev/acpica/resources/rslist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsmemory.ln: $S/contrib/dev/acpica/resources/rsmemory.c
	${NORMAL_LINT}

rsmemory.o: $S/contrib/dev/acpica/resources/rsmemory.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsmisc.ln: $S/contrib/dev/acpica/resources/rsmisc.c
	${NORMAL_LINT}

rsmisc.o: $S/contrib/dev/acpica/resources/rsmisc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsutils.ln: $S/contrib/dev/acpica/resources/rsutils.c
	${NORMAL_LINT}

rsutils.o: $S/contrib/dev/acpica/resources/rsutils.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rsxface.ln: $S/contrib/dev/acpica/resources/rsxface.c
	${NORMAL_LINT}

rsxface.o: $S/contrib/dev/acpica/resources/rsxface.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tbfadt.ln: $S/contrib/dev/acpica/tables/tbfadt.c
	${NORMAL_LINT}

tbfadt.o: $S/contrib/dev/acpica/tables/tbfadt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tbfind.ln: $S/contrib/dev/acpica/tables/tbfind.c
	${NORMAL_LINT}

tbfind.o: $S/contrib/dev/acpica/tables/tbfind.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tbinstal.ln: $S/contrib/dev/acpica/tables/tbinstal.c
	${NORMAL_LINT}

tbinstal.o: $S/contrib/dev/acpica/tables/tbinstal.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tbutils.ln: $S/contrib/dev/acpica/tables/tbutils.c
	${NORMAL_LINT}

tbutils.o: $S/contrib/dev/acpica/tables/tbutils.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tbxface.ln: $S/contrib/dev/acpica/tables/tbxface.c
	${NORMAL_LINT}

tbxface.o: $S/contrib/dev/acpica/tables/tbxface.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tbxfroot.ln: $S/contrib/dev/acpica/tables/tbxfroot.c
	${NORMAL_LINT}

tbxfroot.o: $S/contrib/dev/acpica/tables/tbxfroot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utalloc.ln: $S/contrib/dev/acpica/utilities/utalloc.c
	${NORMAL_LINT}

utalloc.o: $S/contrib/dev/acpica/utilities/utalloc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utcache.ln: $S/contrib/dev/acpica/utilities/utcache.c
	${NORMAL_LINT}

utcache.o: $S/contrib/dev/acpica/utilities/utcache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utcopy.ln: $S/contrib/dev/acpica/utilities/utcopy.c
	${NORMAL_LINT}

utcopy.o: $S/contrib/dev/acpica/utilities/utcopy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utdebug.ln: $S/contrib/dev/acpica/utilities/utdebug.c
	${NORMAL_LINT}

utdebug.o: $S/contrib/dev/acpica/utilities/utdebug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utdecode.ln: $S/contrib/dev/acpica/utilities/utdecode.c
	${NORMAL_LINT}

utdecode.o: $S/contrib/dev/acpica/utilities/utdecode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utdelete.ln: $S/contrib/dev/acpica/utilities/utdelete.c
	${NORMAL_LINT}

utdelete.o: $S/contrib/dev/acpica/utilities/utdelete.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uteval.ln: $S/contrib/dev/acpica/utilities/uteval.c
	${NORMAL_LINT}

uteval.o: $S/contrib/dev/acpica/utilities/uteval.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utglobal.ln: $S/contrib/dev/acpica/utilities/utglobal.c
	${NORMAL_LINT}

utglobal.o: $S/contrib/dev/acpica/utilities/utglobal.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utids.ln: $S/contrib/dev/acpica/utilities/utids.c
	${NORMAL_LINT}

utids.o: $S/contrib/dev/acpica/utilities/utids.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utinit.ln: $S/contrib/dev/acpica/utilities/utinit.c
	${NORMAL_LINT}

utinit.o: $S/contrib/dev/acpica/utilities/utinit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utlock.ln: $S/contrib/dev/acpica/utilities/utlock.c
	${NORMAL_LINT}

utlock.o: $S/contrib/dev/acpica/utilities/utlock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utmath.ln: $S/contrib/dev/acpica/utilities/utmath.c
	${NORMAL_LINT}

utmath.o: $S/contrib/dev/acpica/utilities/utmath.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utmisc.ln: $S/contrib/dev/acpica/utilities/utmisc.c
	${NORMAL_LINT}

utmisc.o: $S/contrib/dev/acpica/utilities/utmisc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utmutex.ln: $S/contrib/dev/acpica/utilities/utmutex.c
	${NORMAL_LINT}

utmutex.o: $S/contrib/dev/acpica/utilities/utmutex.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utobject.ln: $S/contrib/dev/acpica/utilities/utobject.c
	${NORMAL_LINT}

utobject.o: $S/contrib/dev/acpica/utilities/utobject.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utosi.ln: $S/contrib/dev/acpica/utilities/utosi.c
	${NORMAL_LINT}

utosi.o: $S/contrib/dev/acpica/utilities/utosi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utresrc.ln: $S/contrib/dev/acpica/utilities/utresrc.c
	${NORMAL_LINT}

utresrc.o: $S/contrib/dev/acpica/utilities/utresrc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utstate.ln: $S/contrib/dev/acpica/utilities/utstate.c
	${NORMAL_LINT}

utstate.o: $S/contrib/dev/acpica/utilities/utstate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utxface.ln: $S/contrib/dev/acpica/utilities/utxface.c
	${NORMAL_LINT}

utxface.o: $S/contrib/dev/acpica/utilities/utxface.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

utxferror.ln: $S/contrib/dev/acpica/utilities/utxferror.c
	${NORMAL_LINT}

utxferror.o: $S/contrib/dev/acpica/utilities/utxferror.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rijndael-alg-fst.ln: $S/crypto/rijndael/rijndael-alg-fst.c
	${NORMAL_LINT}

rijndael-alg-fst.o: $S/crypto/rijndael/rijndael-alg-fst.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rijndael-api-fst.ln: $S/crypto/rijndael/rijndael-api-fst.c
	${NORMAL_LINT}

rijndael-api-fst.o: $S/crypto/rijndael/rijndael-api-fst.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rijndael-api.ln: $S/crypto/rijndael/rijndael-api.c
	${NORMAL_LINT}

rijndael-api.o: $S/crypto/rijndael/rijndael-api.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sha1.ln: $S/crypto/sha1.c
	${NORMAL_LINT}

sha1.o: $S/crypto/sha1.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sha2.ln: $S/crypto/sha2/sha2.c
	${NORMAL_LINT}

sha2.o: $S/crypto/sha2/sha2.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aac.ln: $S/dev/aac/aac.c
	${NORMAL_LINT}

aac.o: $S/dev/aac/aac.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aac_cam.ln: $S/dev/aac/aac_cam.c
	${NORMAL_LINT}

aac_cam.o: $S/dev/aac/aac_cam.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aac_debug.ln: $S/dev/aac/aac_debug.c
	${NORMAL_LINT}

aac_debug.o: $S/dev/aac/aac_debug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aac_disk.ln: $S/dev/aac/aac_disk.c
	${NORMAL_LINT}

aac_disk.o: $S/dev/aac/aac_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aac_pci.ln: $S/dev/aac/aac_pci.c
	${NORMAL_LINT}

aac_pci.o: $S/dev/aac/aac_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aacraid.ln: $S/dev/aacraid/aacraid.c
	${NORMAL_LINT}

aacraid.o: $S/dev/aacraid/aacraid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aacraid_cam.ln: $S/dev/aacraid/aacraid_cam.c
	${NORMAL_LINT}

aacraid_cam.o: $S/dev/aacraid/aacraid_cam.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aacraid_debug.ln: $S/dev/aacraid/aacraid_debug.c
	${NORMAL_LINT}

aacraid_debug.o: $S/dev/aacraid/aacraid_debug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aacraid_pci.ln: $S/dev/aacraid/aacraid_pci.c
	${NORMAL_LINT}

aacraid_pci.o: $S/dev/aacraid/aacraid_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdDebug.ln: $S/dev/acpica/Osd/OsdDebug.c
	${NORMAL_LINT}

OsdDebug.o: $S/dev/acpica/Osd/OsdDebug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdHardware.ln: $S/dev/acpica/Osd/OsdHardware.c
	${NORMAL_LINT}

OsdHardware.o: $S/dev/acpica/Osd/OsdHardware.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdInterrupt.ln: $S/dev/acpica/Osd/OsdInterrupt.c
	${NORMAL_LINT}

OsdInterrupt.o: $S/dev/acpica/Osd/OsdInterrupt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdMemory.ln: $S/dev/acpica/Osd/OsdMemory.c
	${NORMAL_LINT}

OsdMemory.o: $S/dev/acpica/Osd/OsdMemory.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdSchedule.ln: $S/dev/acpica/Osd/OsdSchedule.c
	${NORMAL_LINT}

OsdSchedule.o: $S/dev/acpica/Osd/OsdSchedule.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdStream.ln: $S/dev/acpica/Osd/OsdStream.c
	${NORMAL_LINT}

OsdStream.o: $S/dev/acpica/Osd/OsdStream.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdSynch.ln: $S/dev/acpica/Osd/OsdSynch.c
	${NORMAL_LINT}

OsdSynch.o: $S/dev/acpica/Osd/OsdSynch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdTable.ln: $S/dev/acpica/Osd/OsdTable.c
	${NORMAL_LINT}

OsdTable.o: $S/dev/acpica/Osd/OsdTable.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi.ln: $S/dev/acpica/acpi.c
	${NORMAL_LINT}

acpi.o: $S/dev/acpica/acpi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_acad.ln: $S/dev/acpica/acpi_acad.c
	${NORMAL_LINT}

acpi_acad.o: $S/dev/acpica/acpi_acad.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_battery.ln: $S/dev/acpica/acpi_battery.c
	${NORMAL_LINT}

acpi_battery.o: $S/dev/acpica/acpi_battery.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_button.ln: $S/dev/acpica/acpi_button.c
	${NORMAL_LINT}

acpi_button.o: $S/dev/acpica/acpi_button.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_cmbat.ln: $S/dev/acpica/acpi_cmbat.c
	${NORMAL_LINT}

acpi_cmbat.o: $S/dev/acpica/acpi_cmbat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_cpu.ln: $S/dev/acpica/acpi_cpu.c
	${NORMAL_LINT}

acpi_cpu.o: $S/dev/acpica/acpi_cpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_ec.ln: $S/dev/acpica/acpi_ec.c
	${NORMAL_LINT}

acpi_ec.o: $S/dev/acpica/acpi_ec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_hpet.ln: $S/dev/acpica/acpi_hpet.c
	${NORMAL_LINT}

acpi_hpet.o: $S/dev/acpica/acpi_hpet.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_isab.ln: $S/dev/acpica/acpi_isab.c
	${NORMAL_LINT}

acpi_isab.o: $S/dev/acpica/acpi_isab.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_lid.ln: $S/dev/acpica/acpi_lid.c
	${NORMAL_LINT}

acpi_lid.o: $S/dev/acpica/acpi_lid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_package.ln: $S/dev/acpica/acpi_package.c
	${NORMAL_LINT}

acpi_package.o: $S/dev/acpica/acpi_package.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_pci.ln: $S/dev/acpica/acpi_pci.c
	${NORMAL_LINT}

acpi_pci.o: $S/dev/acpica/acpi_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_pci_link.ln: $S/dev/acpica/acpi_pci_link.c
	${NORMAL_LINT}

acpi_pci_link.o: $S/dev/acpica/acpi_pci_link.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_pcib.ln: $S/dev/acpica/acpi_pcib.c
	${NORMAL_LINT}

acpi_pcib.o: $S/dev/acpica/acpi_pcib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_pcib_acpi.ln: $S/dev/acpica/acpi_pcib_acpi.c
	${NORMAL_LINT}

acpi_pcib_acpi.o: $S/dev/acpica/acpi_pcib_acpi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_pcib_pci.ln: $S/dev/acpica/acpi_pcib_pci.c
	${NORMAL_LINT}

acpi_pcib_pci.o: $S/dev/acpica/acpi_pcib_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_perf.ln: $S/dev/acpica/acpi_perf.c
	${NORMAL_LINT}

acpi_perf.o: $S/dev/acpica/acpi_perf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_powerres.ln: $S/dev/acpica/acpi_powerres.c
	${NORMAL_LINT}

acpi_powerres.o: $S/dev/acpica/acpi_powerres.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_quirk.ln: $S/dev/acpica/acpi_quirk.c
	${NORMAL_LINT}

acpi_quirk.o: $S/dev/acpica/acpi_quirk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_resource.ln: $S/dev/acpica/acpi_resource.c
	${NORMAL_LINT}

acpi_resource.o: $S/dev/acpica/acpi_resource.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_smbat.ln: $S/dev/acpica/acpi_smbat.c
	${NORMAL_LINT}

acpi_smbat.o: $S/dev/acpica/acpi_smbat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_thermal.ln: $S/dev/acpica/acpi_thermal.c
	${NORMAL_LINT}

acpi_thermal.o: $S/dev/acpica/acpi_thermal.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_throttle.ln: $S/dev/acpica/acpi_throttle.c
	${NORMAL_LINT}

acpi_throttle.o: $S/dev/acpica/acpi_throttle.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_timer.ln: $S/dev/acpica/acpi_timer.c
	${NORMAL_LINT}

acpi_timer.o: $S/dev/acpica/acpi_timer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

adv_pci.ln: $S/dev/advansys/adv_pci.c
	${NORMAL_LINT}

adv_pci.o: $S/dev/advansys/adv_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

advansys.ln: $S/dev/advansys/advansys.c
	${NORMAL_LINT}

advansys.o: $S/dev/advansys/advansys.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

advlib.ln: $S/dev/advansys/advlib.c
	${NORMAL_LINT}

advlib.o: $S/dev/advansys/advlib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

advmcode.ln: $S/dev/advansys/advmcode.c
	${NORMAL_LINT}

advmcode.o: $S/dev/advansys/advmcode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

adw_pci.ln: $S/dev/advansys/adw_pci.c
	${NORMAL_LINT}

adw_pci.o: $S/dev/advansys/adw_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

adwcam.ln: $S/dev/advansys/adwcam.c
	${NORMAL_LINT}

adwcam.o: $S/dev/advansys/adwcam.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

adwlib.ln: $S/dev/advansys/adwlib.c
	${NORMAL_LINT}

adwlib.o: $S/dev/advansys/adwlib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

adwmcode.ln: $S/dev/advansys/adwmcode.c
	${NORMAL_LINT}

adwmcode.o: $S/dev/advansys/adwmcode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ae.ln: $S/dev/ae/if_ae.c
	${NORMAL_LINT}

if_ae.o: $S/dev/ae/if_ae.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_age.ln: $S/dev/age/if_age.c
	${NORMAL_LINT}

if_age.o: $S/dev/age/if_age.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

agp.ln: $S/dev/agp/agp.c
	${NORMAL_LINT}

agp.o: $S/dev/agp/agp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

agp_if.ln: $S/dev/agp/agp_if.m
	${NORMAL_LINT}

agp_if.o: $S/dev/agp/agp_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

ahci.ln: $S/dev/ahci/ahci.c
	${NORMAL_LINT}

ahci.o: $S/dev/ahci/ahci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic.ln: $S/dev/aic/aic.c
	${NORMAL_LINT}

aic.o: $S/dev/aic/aic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic_pccard.ln: $S/dev/aic/aic_pccard.c
	${NORMAL_LINT}

aic_pccard.o: $S/dev/aic/aic_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ahc_isa.ln: $S/dev/aic7xxx/ahc_isa.c
	${NORMAL_LINT}

ahc_isa.o: $S/dev/aic7xxx/ahc_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ahc_pci.ln: $S/dev/aic7xxx/ahc_pci.c
	${NORMAL_LINT}

ahc_pci.o: $S/dev/aic7xxx/ahc_pci.c
	${NORMAL_C} ${NO_WCONSTANT_CONVERSION}
	${NORMAL_CTFCONVERT}

ahd_pci.ln: $S/dev/aic7xxx/ahd_pci.c
	${NORMAL_LINT}

ahd_pci.o: $S/dev/aic7xxx/ahd_pci.c
	${NORMAL_C} ${NO_WCONSTANT_CONVERSION}
	${NORMAL_CTFCONVERT}

aic7770.ln: $S/dev/aic7xxx/aic7770.c
	${NORMAL_LINT}

aic7770.o: $S/dev/aic7xxx/aic7770.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic79xx.ln: $S/dev/aic7xxx/aic79xx.c
	${NORMAL_LINT}

aic79xx.o: $S/dev/aic7xxx/aic79xx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic79xx_osm.ln: $S/dev/aic7xxx/aic79xx_osm.c
	${NORMAL_LINT}

aic79xx_osm.o: $S/dev/aic7xxx/aic79xx_osm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic79xx_pci.ln: $S/dev/aic7xxx/aic79xx_pci.c
	${NORMAL_LINT}

aic79xx_pci.o: $S/dev/aic7xxx/aic79xx_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic7xxx.ln: $S/dev/aic7xxx/aic7xxx.c
	${NORMAL_LINT}

aic7xxx.o: $S/dev/aic7xxx/aic7xxx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic7xxx_93cx6.ln: $S/dev/aic7xxx/aic7xxx_93cx6.c
	${NORMAL_LINT}

aic7xxx_93cx6.o: $S/dev/aic7xxx/aic7xxx_93cx6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic7xxx_osm.ln: $S/dev/aic7xxx/aic7xxx_osm.c
	${NORMAL_LINT}

aic7xxx_osm.o: $S/dev/aic7xxx/aic7xxx_osm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

aic7xxx_pci.ln: $S/dev/aic7xxx/aic7xxx_pci.c
	${NORMAL_LINT}

aic7xxx_pci.o: $S/dev/aic7xxx/aic7xxx_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_alc.ln: $S/dev/alc/if_alc.c
	${NORMAL_LINT}

if_alc.o: $S/dev/alc/if_alc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ale.ln: $S/dev/ale/if_ale.c
	${NORMAL_LINT}

if_ale.o: $S/dev/ale/if_ale.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

amr.ln: $S/dev/amr/amr.c
	${NORMAL_LINT}

amr.o: $S/dev/amr/amr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

amr_disk.ln: $S/dev/amr/amr_disk.c
	${NORMAL_LINT}

amr_disk.o: $S/dev/amr/amr_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

amr_pci.ln: $S/dev/amr/amr_pci.c
	${NORMAL_LINT}

amr_pci.o: $S/dev/amr/amr_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_an.ln: $S/dev/an/if_an.c
	${NORMAL_LINT}

if_an.o: $S/dev/an/if_an.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_an_isa.ln: $S/dev/an/if_an_isa.c
	${NORMAL_LINT}

if_an_isa.o: $S/dev/an/if_an_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_an_pccard.ln: $S/dev/an/if_an_pccard.c
	${NORMAL_LINT}

if_an_pccard.o: $S/dev/an/if_an_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_an_pci.ln: $S/dev/an/if_an_pci.c
	${NORMAL_LINT}

if_an_pci.o: $S/dev/an/if_an_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata_if.ln: $S/dev/ata/ata_if.m
	${NORMAL_LINT}

ata_if.o: $S/dev/ata/ata_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

ata-all.ln: $S/dev/ata/ata-all.c
	${NORMAL_LINT}

ata-all.o: $S/dev/ata/ata-all.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-dma.ln: $S/dev/ata/ata-dma.c
	${NORMAL_LINT}

ata-dma.o: $S/dev/ata/ata-dma.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-lowlevel.ln: $S/dev/ata/ata-lowlevel.c
	${NORMAL_LINT}

ata-lowlevel.o: $S/dev/ata/ata-lowlevel.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-queue.ln: $S/dev/ata/ata-queue.c
	${NORMAL_LINT}

ata-queue.o: $S/dev/ata/ata-queue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-sata.ln: $S/dev/ata/ata-sata.c
	${NORMAL_LINT}

ata-sata.o: $S/dev/ata/ata-sata.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-card.ln: $S/dev/ata/ata-card.c
	${NORMAL_LINT}

ata-card.o: $S/dev/ata/ata-card.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-isa.ln: $S/dev/ata/ata-isa.c
	${NORMAL_LINT}

ata-isa.o: $S/dev/ata/ata-isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-pci.ln: $S/dev/ata/ata-pci.c
	${NORMAL_LINT}

ata-pci.o: $S/dev/ata/ata-pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-ahci.ln: $S/dev/ata/chipsets/ata-ahci.c
	${NORMAL_LINT}

ata-ahci.o: $S/dev/ata/chipsets/ata-ahci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-acard.ln: $S/dev/ata/chipsets/ata-acard.c
	${NORMAL_LINT}

ata-acard.o: $S/dev/ata/chipsets/ata-acard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-acerlabs.ln: $S/dev/ata/chipsets/ata-acerlabs.c
	${NORMAL_LINT}

ata-acerlabs.o: $S/dev/ata/chipsets/ata-acerlabs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-adaptec.ln: $S/dev/ata/chipsets/ata-adaptec.c
	${NORMAL_LINT}

ata-adaptec.o: $S/dev/ata/chipsets/ata-adaptec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-amd.ln: $S/dev/ata/chipsets/ata-amd.c
	${NORMAL_LINT}

ata-amd.o: $S/dev/ata/chipsets/ata-amd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-ati.ln: $S/dev/ata/chipsets/ata-ati.c
	${NORMAL_LINT}

ata-ati.o: $S/dev/ata/chipsets/ata-ati.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-cenatek.ln: $S/dev/ata/chipsets/ata-cenatek.c
	${NORMAL_LINT}

ata-cenatek.o: $S/dev/ata/chipsets/ata-cenatek.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-cypress.ln: $S/dev/ata/chipsets/ata-cypress.c
	${NORMAL_LINT}

ata-cypress.o: $S/dev/ata/chipsets/ata-cypress.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-cyrix.ln: $S/dev/ata/chipsets/ata-cyrix.c
	${NORMAL_LINT}

ata-cyrix.o: $S/dev/ata/chipsets/ata-cyrix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-highpoint.ln: $S/dev/ata/chipsets/ata-highpoint.c
	${NORMAL_LINT}

ata-highpoint.o: $S/dev/ata/chipsets/ata-highpoint.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-intel.ln: $S/dev/ata/chipsets/ata-intel.c
	${NORMAL_LINT}

ata-intel.o: $S/dev/ata/chipsets/ata-intel.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-ite.ln: $S/dev/ata/chipsets/ata-ite.c
	${NORMAL_LINT}

ata-ite.o: $S/dev/ata/chipsets/ata-ite.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-jmicron.ln: $S/dev/ata/chipsets/ata-jmicron.c
	${NORMAL_LINT}

ata-jmicron.o: $S/dev/ata/chipsets/ata-jmicron.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-marvell.ln: $S/dev/ata/chipsets/ata-marvell.c
	${NORMAL_LINT}

ata-marvell.o: $S/dev/ata/chipsets/ata-marvell.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-micron.ln: $S/dev/ata/chipsets/ata-micron.c
	${NORMAL_LINT}

ata-micron.o: $S/dev/ata/chipsets/ata-micron.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-national.ln: $S/dev/ata/chipsets/ata-national.c
	${NORMAL_LINT}

ata-national.o: $S/dev/ata/chipsets/ata-national.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-netcell.ln: $S/dev/ata/chipsets/ata-netcell.c
	${NORMAL_LINT}

ata-netcell.o: $S/dev/ata/chipsets/ata-netcell.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-nvidia.ln: $S/dev/ata/chipsets/ata-nvidia.c
	${NORMAL_LINT}

ata-nvidia.o: $S/dev/ata/chipsets/ata-nvidia.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-promise.ln: $S/dev/ata/chipsets/ata-promise.c
	${NORMAL_LINT}

ata-promise.o: $S/dev/ata/chipsets/ata-promise.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-serverworks.ln: $S/dev/ata/chipsets/ata-serverworks.c
	${NORMAL_LINT}

ata-serverworks.o: $S/dev/ata/chipsets/ata-serverworks.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-siliconimage.ln: $S/dev/ata/chipsets/ata-siliconimage.c
	${NORMAL_LINT}

ata-siliconimage.o: $S/dev/ata/chipsets/ata-siliconimage.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-sis.ln: $S/dev/ata/chipsets/ata-sis.c
	${NORMAL_LINT}

ata-sis.o: $S/dev/ata/chipsets/ata-sis.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ata-via.ln: $S/dev/ata/chipsets/ata-via.c
	${NORMAL_LINT}

ata-via.o: $S/dev/ata/chipsets/ata-via.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ath_pci.ln: $S/dev/ath/if_ath_pci.c
	${NORMAL_LINT}

if_ath_pci.o: $S/dev/ath/if_ath_pci.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

if_ath.ln: $S/dev/ath/if_ath.c
	${NORMAL_LINT}

if_ath.o: $S/dev/ath/if_ath.c
	${NORMAL_C} ${NO_WSOMETIMES_UNINITIALIZED} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

if_ath_debug.ln: $S/dev/ath/if_ath_debug.c
	${NORMAL_LINT}

if_ath_debug.o: $S/dev/ath/if_ath_debug.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

if_ath_keycache.ln: $S/dev/ath/if_ath_keycache.c
	${NORMAL_LINT}

if_ath_keycache.o: $S/dev/ath/if_ath_keycache.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

if_ath_tx.ln: $S/dev/ath/if_ath_tx.c
	${NORMAL_LINT}

if_ath_tx.o: $S/dev/ath/if_ath_tx.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

if_ath_tx_ht.ln: $S/dev/ath/if_ath_tx_ht.c
	${NORMAL_LINT}

if_ath_tx_ht.o: $S/dev/ath/if_ath_tx_ht.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

if_ath_sysctl.ln: $S/dev/ath/if_ath_sysctl.c
	${NORMAL_LINT}

if_ath_sysctl.o: $S/dev/ath/if_ath_sysctl.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ah_osdep.ln: $S/dev/ath/ah_osdep.c
	${NORMAL_LINT}

ah_osdep.o: $S/dev/ath/ah_osdep.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ah.ln: $S/dev/ath/ath_hal/ah.c
	${NORMAL_LINT}

ah.o: $S/dev/ath/ath_hal/ah.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ah_eeprom_v1.ln: $S/dev/ath/ath_hal/ah_eeprom_v1.c
	${NORMAL_LINT}

ah_eeprom_v1.o: $S/dev/ath/ath_hal/ah_eeprom_v1.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ah_eeprom_v3.ln: $S/dev/ath/ath_hal/ah_eeprom_v3.c
	${NORMAL_LINT}

ah_eeprom_v3.o: $S/dev/ath/ath_hal/ah_eeprom_v3.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ah_eeprom_v14.ln: $S/dev/ath/ath_hal/ah_eeprom_v14.c
	${NORMAL_LINT}

ah_eeprom_v14.o: $S/dev/ath/ath_hal/ah_eeprom_v14.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ah_eeprom_v4k.ln: $S/dev/ath/ath_hal/ah_eeprom_v4k.c
	${NORMAL_LINT}

ah_eeprom_v4k.o: $S/dev/ath/ath_hal/ah_eeprom_v4k.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ah_eeprom_9287.ln: $S/dev/ath/ath_hal/ah_eeprom_9287.c
	${NORMAL_LINT}

ah_eeprom_9287.o: $S/dev/ath/ath_hal/ah_eeprom_9287.c
	${NORMAL_C} ${NO_WSOMETIMES_UNINITIALIZED} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ah_regdomain.ln: $S/dev/ath/ath_hal/ah_regdomain.c
	${NORMAL_LINT}

ah_regdomain.o: $S/dev/ath/ath_hal/ah_regdomain.c
	${NORMAL_C} ${NO_WSHIFT_COUNT_NEGATIVE} ${NO_WSHIFT_COUNT_OVERFLOW} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

ar5210_attach.ln: $S/dev/ath/ath_hal/ar5210/ar5210_attach.c
	${NORMAL_LINT}

ar5210_attach.o: $S/dev/ath/ath_hal/ar5210/ar5210_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_beacon.ln: $S/dev/ath/ath_hal/ar5210/ar5210_beacon.c
	${NORMAL_LINT}

ar5210_beacon.o: $S/dev/ath/ath_hal/ar5210/ar5210_beacon.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_interrupts.ln: $S/dev/ath/ath_hal/ar5210/ar5210_interrupts.c
	${NORMAL_LINT}

ar5210_interrupts.o: $S/dev/ath/ath_hal/ar5210/ar5210_interrupts.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_keycache.ln: $S/dev/ath/ath_hal/ar5210/ar5210_keycache.c
	${NORMAL_LINT}

ar5210_keycache.o: $S/dev/ath/ath_hal/ar5210/ar5210_keycache.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_misc.ln: $S/dev/ath/ath_hal/ar5210/ar5210_misc.c
	${NORMAL_LINT}

ar5210_misc.o: $S/dev/ath/ath_hal/ar5210/ar5210_misc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_phy.ln: $S/dev/ath/ath_hal/ar5210/ar5210_phy.c
	${NORMAL_LINT}

ar5210_phy.o: $S/dev/ath/ath_hal/ar5210/ar5210_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_power.ln: $S/dev/ath/ath_hal/ar5210/ar5210_power.c
	${NORMAL_LINT}

ar5210_power.o: $S/dev/ath/ath_hal/ar5210/ar5210_power.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_recv.ln: $S/dev/ath/ath_hal/ar5210/ar5210_recv.c
	${NORMAL_LINT}

ar5210_recv.o: $S/dev/ath/ath_hal/ar5210/ar5210_recv.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_reset.ln: $S/dev/ath/ath_hal/ar5210/ar5210_reset.c
	${NORMAL_LINT}

ar5210_reset.o: $S/dev/ath/ath_hal/ar5210/ar5210_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5210_xmit.ln: $S/dev/ath/ath_hal/ar5210/ar5210_xmit.c
	${NORMAL_LINT}

ar5210_xmit.o: $S/dev/ath/ath_hal/ar5210/ar5210_xmit.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_attach.ln: $S/dev/ath/ath_hal/ar5211/ar5211_attach.c
	${NORMAL_LINT}

ar5211_attach.o: $S/dev/ath/ath_hal/ar5211/ar5211_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_beacon.ln: $S/dev/ath/ath_hal/ar5211/ar5211_beacon.c
	${NORMAL_LINT}

ar5211_beacon.o: $S/dev/ath/ath_hal/ar5211/ar5211_beacon.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_interrupts.ln: $S/dev/ath/ath_hal/ar5211/ar5211_interrupts.c
	${NORMAL_LINT}

ar5211_interrupts.o: $S/dev/ath/ath_hal/ar5211/ar5211_interrupts.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_keycache.ln: $S/dev/ath/ath_hal/ar5211/ar5211_keycache.c
	${NORMAL_LINT}

ar5211_keycache.o: $S/dev/ath/ath_hal/ar5211/ar5211_keycache.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_misc.ln: $S/dev/ath/ath_hal/ar5211/ar5211_misc.c
	${NORMAL_LINT}

ar5211_misc.o: $S/dev/ath/ath_hal/ar5211/ar5211_misc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_phy.ln: $S/dev/ath/ath_hal/ar5211/ar5211_phy.c
	${NORMAL_LINT}

ar5211_phy.o: $S/dev/ath/ath_hal/ar5211/ar5211_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_power.ln: $S/dev/ath/ath_hal/ar5211/ar5211_power.c
	${NORMAL_LINT}

ar5211_power.o: $S/dev/ath/ath_hal/ar5211/ar5211_power.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_recv.ln: $S/dev/ath/ath_hal/ar5211/ar5211_recv.c
	${NORMAL_LINT}

ar5211_recv.o: $S/dev/ath/ath_hal/ar5211/ar5211_recv.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_reset.ln: $S/dev/ath/ath_hal/ar5211/ar5211_reset.c
	${NORMAL_LINT}

ar5211_reset.o: $S/dev/ath/ath_hal/ar5211/ar5211_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5211_xmit.ln: $S/dev/ath/ath_hal/ar5211/ar5211_xmit.c
	${NORMAL_LINT}

ar5211_xmit.o: $S/dev/ath/ath_hal/ar5211/ar5211_xmit.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_ani.ln: $S/dev/ath/ath_hal/ar5212/ar5212_ani.c
	${NORMAL_LINT}

ar5212_ani.o: $S/dev/ath/ath_hal/ar5212/ar5212_ani.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_attach.ln: $S/dev/ath/ath_hal/ar5212/ar5212_attach.c
	${NORMAL_LINT}

ar5212_attach.o: $S/dev/ath/ath_hal/ar5212/ar5212_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_beacon.ln: $S/dev/ath/ath_hal/ar5212/ar5212_beacon.c
	${NORMAL_LINT}

ar5212_beacon.o: $S/dev/ath/ath_hal/ar5212/ar5212_beacon.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_eeprom.ln: $S/dev/ath/ath_hal/ar5212/ar5212_eeprom.c
	${NORMAL_LINT}

ar5212_eeprom.o: $S/dev/ath/ath_hal/ar5212/ar5212_eeprom.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_gpio.ln: $S/dev/ath/ath_hal/ar5212/ar5212_gpio.c
	${NORMAL_LINT}

ar5212_gpio.o: $S/dev/ath/ath_hal/ar5212/ar5212_gpio.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_interrupts.ln: $S/dev/ath/ath_hal/ar5212/ar5212_interrupts.c
	${NORMAL_LINT}

ar5212_interrupts.o: $S/dev/ath/ath_hal/ar5212/ar5212_interrupts.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_keycache.ln: $S/dev/ath/ath_hal/ar5212/ar5212_keycache.c
	${NORMAL_LINT}

ar5212_keycache.o: $S/dev/ath/ath_hal/ar5212/ar5212_keycache.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_misc.ln: $S/dev/ath/ath_hal/ar5212/ar5212_misc.c
	${NORMAL_LINT}

ar5212_misc.o: $S/dev/ath/ath_hal/ar5212/ar5212_misc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_phy.ln: $S/dev/ath/ath_hal/ar5212/ar5212_phy.c
	${NORMAL_LINT}

ar5212_phy.o: $S/dev/ath/ath_hal/ar5212/ar5212_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_power.ln: $S/dev/ath/ath_hal/ar5212/ar5212_power.c
	${NORMAL_LINT}

ar5212_power.o: $S/dev/ath/ath_hal/ar5212/ar5212_power.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_recv.ln: $S/dev/ath/ath_hal/ar5212/ar5212_recv.c
	${NORMAL_LINT}

ar5212_recv.o: $S/dev/ath/ath_hal/ar5212/ar5212_recv.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_reset.ln: $S/dev/ath/ath_hal/ar5212/ar5212_reset.c
	${NORMAL_LINT}

ar5212_reset.o: $S/dev/ath/ath_hal/ar5212/ar5212_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_rfgain.ln: $S/dev/ath/ath_hal/ar5212/ar5212_rfgain.c
	${NORMAL_LINT}

ar5212_rfgain.o: $S/dev/ath/ath_hal/ar5212/ar5212_rfgain.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5212_xmit.ln: $S/dev/ath/ath_hal/ar5212/ar5212_xmit.c
	${NORMAL_LINT}

ar5212_xmit.o: $S/dev/ath/ath_hal/ar5212/ar5212_xmit.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_ani.ln: $S/dev/ath/ath_hal/ar5416/ar5416_ani.c
	${NORMAL_LINT}

ar5416_ani.o: $S/dev/ath/ath_hal/ar5416/ar5416_ani.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_attach.ln: $S/dev/ath/ath_hal/ar5416/ar5416_attach.c
	${NORMAL_LINT}

ar5416_attach.o: $S/dev/ath/ath_hal/ar5416/ar5416_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_beacon.ln: $S/dev/ath/ath_hal/ar5416/ar5416_beacon.c
	${NORMAL_LINT}

ar5416_beacon.o: $S/dev/ath/ath_hal/ar5416/ar5416_beacon.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_cal.ln: $S/dev/ath/ath_hal/ar5416/ar5416_cal.c
	${NORMAL_LINT}

ar5416_cal.o: $S/dev/ath/ath_hal/ar5416/ar5416_cal.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_cal_iq.ln: $S/dev/ath/ath_hal/ar5416/ar5416_cal_iq.c
	${NORMAL_LINT}

ar5416_cal_iq.o: $S/dev/ath/ath_hal/ar5416/ar5416_cal_iq.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_cal_adcgain.ln: $S/dev/ath/ath_hal/ar5416/ar5416_cal_adcgain.c
	${NORMAL_LINT}

ar5416_cal_adcgain.o: $S/dev/ath/ath_hal/ar5416/ar5416_cal_adcgain.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_cal_adcdc.ln: $S/dev/ath/ath_hal/ar5416/ar5416_cal_adcdc.c
	${NORMAL_LINT}

ar5416_cal_adcdc.o: $S/dev/ath/ath_hal/ar5416/ar5416_cal_adcdc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_eeprom.ln: $S/dev/ath/ath_hal/ar5416/ar5416_eeprom.c
	${NORMAL_LINT}

ar5416_eeprom.o: $S/dev/ath/ath_hal/ar5416/ar5416_eeprom.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_gpio.ln: $S/dev/ath/ath_hal/ar5416/ar5416_gpio.c
	${NORMAL_LINT}

ar5416_gpio.o: $S/dev/ath/ath_hal/ar5416/ar5416_gpio.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_interrupts.ln: $S/dev/ath/ath_hal/ar5416/ar5416_interrupts.c
	${NORMAL_LINT}

ar5416_interrupts.o: $S/dev/ath/ath_hal/ar5416/ar5416_interrupts.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_keycache.ln: $S/dev/ath/ath_hal/ar5416/ar5416_keycache.c
	${NORMAL_LINT}

ar5416_keycache.o: $S/dev/ath/ath_hal/ar5416/ar5416_keycache.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_misc.ln: $S/dev/ath/ath_hal/ar5416/ar5416_misc.c
	${NORMAL_LINT}

ar5416_misc.o: $S/dev/ath/ath_hal/ar5416/ar5416_misc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_phy.ln: $S/dev/ath/ath_hal/ar5416/ar5416_phy.c
	${NORMAL_LINT}

ar5416_phy.o: $S/dev/ath/ath_hal/ar5416/ar5416_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_power.ln: $S/dev/ath/ath_hal/ar5416/ar5416_power.c
	${NORMAL_LINT}

ar5416_power.o: $S/dev/ath/ath_hal/ar5416/ar5416_power.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_recv.ln: $S/dev/ath/ath_hal/ar5416/ar5416_recv.c
	${NORMAL_LINT}

ar5416_recv.o: $S/dev/ath/ath_hal/ar5416/ar5416_recv.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_reset.ln: $S/dev/ath/ath_hal/ar5416/ar5416_reset.c
	${NORMAL_LINT}

ar5416_reset.o: $S/dev/ath/ath_hal/ar5416/ar5416_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5416_xmit.ln: $S/dev/ath/ath_hal/ar5416/ar5416_xmit.c
	${NORMAL_LINT}

ar5416_xmit.o: $S/dev/ath/ath_hal/ar5416/ar5416_xmit.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9130_attach.ln: $S/dev/ath/ath_hal/ar9001/ar9130_attach.c
	${NORMAL_LINT}

ar9130_attach.o: $S/dev/ath/ath_hal/ar9001/ar9130_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9130_phy.ln: $S/dev/ath/ath_hal/ar9001/ar9130_phy.c
	${NORMAL_LINT}

ar9130_phy.o: $S/dev/ath/ath_hal/ar9001/ar9130_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9130_eeprom.ln: $S/dev/ath/ath_hal/ar9001/ar9130_eeprom.c
	${NORMAL_LINT}

ar9130_eeprom.o: $S/dev/ath/ath_hal/ar9001/ar9130_eeprom.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9160_attach.ln: $S/dev/ath/ath_hal/ar9001/ar9160_attach.c
	${NORMAL_LINT}

ar9160_attach.o: $S/dev/ath/ath_hal/ar9001/ar9160_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9280_attach.ln: $S/dev/ath/ath_hal/ar9002/ar9280_attach.c
	${NORMAL_LINT}

ar9280_attach.o: $S/dev/ath/ath_hal/ar9002/ar9280_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9280_olc.ln: $S/dev/ath/ath_hal/ar9002/ar9280_olc.c
	${NORMAL_LINT}

ar9280_olc.o: $S/dev/ath/ath_hal/ar9002/ar9280_olc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9285_attach.ln: $S/dev/ath/ath_hal/ar9002/ar9285_attach.c
	${NORMAL_LINT}

ar9285_attach.o: $S/dev/ath/ath_hal/ar9002/ar9285_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9285_reset.ln: $S/dev/ath/ath_hal/ar9002/ar9285_reset.c
	${NORMAL_LINT}

ar9285_reset.o: $S/dev/ath/ath_hal/ar9002/ar9285_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9285_cal.ln: $S/dev/ath/ath_hal/ar9002/ar9285_cal.c
	${NORMAL_LINT}

ar9285_cal.o: $S/dev/ath/ath_hal/ar9002/ar9285_cal.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9285_phy.ln: $S/dev/ath/ath_hal/ar9002/ar9285_phy.c
	${NORMAL_LINT}

ar9285_phy.o: $S/dev/ath/ath_hal/ar9002/ar9285_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9285_diversity.ln: $S/dev/ath/ath_hal/ar9002/ar9285_diversity.c
	${NORMAL_LINT}

ar9285_diversity.o: $S/dev/ath/ath_hal/ar9002/ar9285_diversity.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9287_attach.ln: $S/dev/ath/ath_hal/ar9002/ar9287_attach.c
	${NORMAL_LINT}

ar9287_attach.o: $S/dev/ath/ath_hal/ar9002/ar9287_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9287_reset.ln: $S/dev/ath/ath_hal/ar9002/ar9287_reset.c
	${NORMAL_LINT}

ar9287_reset.o: $S/dev/ath/ath_hal/ar9002/ar9287_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9287_cal.ln: $S/dev/ath/ath_hal/ar9002/ar9287_cal.c
	${NORMAL_LINT}

ar9287_cal.o: $S/dev/ath/ath_hal/ar9002/ar9287_cal.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9287_olc.ln: $S/dev/ath/ath_hal/ar9002/ar9287_olc.c
	${NORMAL_LINT}

ar9287_olc.o: $S/dev/ath/ath_hal/ar9002/ar9287_olc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar2413.ln: $S/dev/ath/ath_hal/ar5212/ar2413.c
	${NORMAL_LINT}

ar2413.o: $S/dev/ath/ath_hal/ar5212/ar2413.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar2425.ln: $S/dev/ath/ath_hal/ar5212/ar2425.c
	${NORMAL_LINT}

ar2425.o: $S/dev/ath/ath_hal/ar5212/ar2425.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5111.ln: $S/dev/ath/ath_hal/ar5212/ar5111.c
	${NORMAL_LINT}

ar5111.o: $S/dev/ath/ath_hal/ar5212/ar5111.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5112.ln: $S/dev/ath/ath_hal/ar5212/ar5112.c
	${NORMAL_LINT}

ar5112.o: $S/dev/ath/ath_hal/ar5212/ar5112.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar5413.ln: $S/dev/ath/ath_hal/ar5212/ar5413.c
	${NORMAL_LINT}

ar5413.o: $S/dev/ath/ath_hal/ar5212/ar5413.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar2133.ln: $S/dev/ath/ath_hal/ar5416/ar2133.c
	${NORMAL_LINT}

ar2133.o: $S/dev/ath/ath_hal/ar5416/ar2133.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9280.ln: $S/dev/ath/ath_hal/ar9002/ar9280.c
	${NORMAL_LINT}

ar9280.o: $S/dev/ath/ath_hal/ar9002/ar9280.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9285.ln: $S/dev/ath/ath_hal/ar9002/ar9285.c
	${NORMAL_LINT}

ar9285.o: $S/dev/ath/ath_hal/ar9002/ar9285.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

ar9287.ln: $S/dev/ath/ath_hal/ar9002/ar9287.c
	${NORMAL_LINT}

ar9287.o: $S/dev/ath/ath_hal/ar9002/ar9287.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal
	${NORMAL_CTFCONVERT}

sample.ln: $S/dev/ath/ath_rate/sample/sample.c
	${NORMAL_LINT}

sample.o: $S/dev/ath/ath_rate/sample/sample.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

dfs_null.ln: $S/dev/ath/ath_dfs/null/dfs_null.c
	${NORMAL_LINT}

dfs_null.o: $S/dev/ath/ath_dfs/null/dfs_null.c
	${NORMAL_C} -I$S/dev/ath
	${NORMAL_CTFCONVERT}

if_bce.ln: $S/dev/bce/if_bce.c
	${NORMAL_LINT}

if_bce.o: $S/dev/bce/if_bce.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_bfe.ln: $S/dev/bfe/if_bfe.c
	${NORMAL_LINT}

if_bfe.o: $S/dev/bfe/if_bfe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_bge.ln: $S/dev/bge/if_bge.c
	${NORMAL_LINT}

if_bge.o: $S/dev/bge/if_bge.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bt.ln: $S/dev/buslogic/bt.c
	${NORMAL_LINT}

bt.o: $S/dev/buslogic/bt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bt_isa.ln: $S/dev/buslogic/bt_isa.c
	${NORMAL_LINT}

bt_isa.o: $S/dev/buslogic/bt_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bt_pci.ln: $S/dev/buslogic/bt_pci.c
	${NORMAL_LINT}

bt_pci.o: $S/dev/buslogic/bt_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_bxe.ln: $S/dev/bxe/if_bxe.c
	${NORMAL_LINT}

if_bxe.o: $S/dev/bxe/if_bxe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bxe_link.ln: $S/dev/bxe/bxe_link.c
	${NORMAL_LINT}

bxe_link.o: $S/dev/bxe/bxe_link.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cardbus.ln: $S/dev/cardbus/cardbus.c
	${NORMAL_LINT}

cardbus.o: $S/dev/cardbus/cardbus.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cardbus_cis.ln: $S/dev/cardbus/cardbus_cis.c
	${NORMAL_LINT}

cardbus_cis.o: $S/dev/cardbus/cardbus_cis.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cardbus_device.ln: $S/dev/cardbus/cardbus_device.c
	${NORMAL_LINT}

cardbus_device.o: $S/dev/cardbus/cardbus_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_cas.ln: $S/dev/cas/if_cas.c
	${NORMAL_LINT}

if_cas.o: $S/dev/cas/if_cas.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ciss.ln: $S/dev/ciss/ciss.c
	${NORMAL_LINT}

ciss.o: $S/dev/ciss/ciss.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ichss.ln: $S/dev/cpufreq/ichss.c
	${NORMAL_LINT}

ichss.o: $S/dev/cpufreq/ichss.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_cs.ln: $S/dev/cs/if_cs.c
	${NORMAL_LINT}

if_cs.o: $S/dev/cs/if_cs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_cs_isa.ln: $S/dev/cs/if_cs_isa.c
	${NORMAL_LINT}

if_cs_isa.o: $S/dev/cs/if_cs_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_cs_pccard.ln: $S/dev/cs/if_cs_pccard.c
	${NORMAL_LINT}

if_cs_pccard.o: $S/dev/cs/if_cs_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_dc.ln: $S/dev/dc/if_dc.c
	${NORMAL_LINT}

if_dc.o: $S/dev/dc/if_dc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dcphy.ln: $S/dev/dc/dcphy.c
	${NORMAL_LINT}

dcphy.o: $S/dev/dc/dcphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pnphy.ln: $S/dev/dc/pnphy.c
	${NORMAL_LINT}

pnphy.o: $S/dev/dc/pnphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_de.ln: $S/dev/de/if_de.c
	${NORMAL_LINT}

if_de.o: $S/dev/de/if_de.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dpt_pci.ln: $S/dev/dpt/dpt_pci.c
	${NORMAL_LINT}

dpt_pci.o: $S/dev/dpt/dpt_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dpt_scsi.ln: $S/dev/dpt/dpt_scsi.c
	${NORMAL_LINT}

dpt_scsi.o: $S/dev/dpt/dpt_scsi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ed.ln: $S/dev/ed/if_ed.c
	${NORMAL_LINT}

if_ed.o: $S/dev/ed/if_ed.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ed_novell.ln: $S/dev/ed/if_ed_novell.c
	${NORMAL_LINT}

if_ed_novell.o: $S/dev/ed/if_ed_novell.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ed_rtl80x9.ln: $S/dev/ed/if_ed_rtl80x9.c
	${NORMAL_LINT}

if_ed_rtl80x9.o: $S/dev/ed/if_ed_rtl80x9.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ed_pccard.ln: $S/dev/ed/if_ed_pccard.c
	${NORMAL_LINT}

if_ed_pccard.o: $S/dev/ed/if_ed_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ed_pci.ln: $S/dev/ed/if_ed_pci.c
	${NORMAL_LINT}

if_ed_pci.o: $S/dev/ed/if_ed_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

eisa_if.ln: $S/dev/eisa/eisa_if.m
	${NORMAL_LINT}

eisa_if.o: $S/dev/eisa/eisa_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

if_em.ln: $S/dev/e1000/if_em.c
	${NORMAL_LINT}

if_em.o: $S/dev/e1000/if_em.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

if_lem.ln: $S/dev/e1000/if_lem.c
	${NORMAL_LINT}

if_lem.o: $S/dev/e1000/if_lem.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

if_igb.ln: $S/dev/e1000/if_igb.c
	${NORMAL_LINT}

if_igb.o: $S/dev/e1000/if_igb.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_80003es2lan.ln: $S/dev/e1000/e1000_80003es2lan.c
	${NORMAL_LINT}

e1000_80003es2lan.o: $S/dev/e1000/e1000_80003es2lan.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_82540.ln: $S/dev/e1000/e1000_82540.c
	${NORMAL_LINT}

e1000_82540.o: $S/dev/e1000/e1000_82540.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_82541.ln: $S/dev/e1000/e1000_82541.c
	${NORMAL_LINT}

e1000_82541.o: $S/dev/e1000/e1000_82541.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_82542.ln: $S/dev/e1000/e1000_82542.c
	${NORMAL_LINT}

e1000_82542.o: $S/dev/e1000/e1000_82542.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_82543.ln: $S/dev/e1000/e1000_82543.c
	${NORMAL_LINT}

e1000_82543.o: $S/dev/e1000/e1000_82543.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_82571.ln: $S/dev/e1000/e1000_82571.c
	${NORMAL_LINT}

e1000_82571.o: $S/dev/e1000/e1000_82571.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_82575.ln: $S/dev/e1000/e1000_82575.c
	${NORMAL_LINT}

e1000_82575.o: $S/dev/e1000/e1000_82575.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_ich8lan.ln: $S/dev/e1000/e1000_ich8lan.c
	${NORMAL_LINT}

e1000_ich8lan.o: $S/dev/e1000/e1000_ich8lan.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_i210.ln: $S/dev/e1000/e1000_i210.c
	${NORMAL_LINT}

e1000_i210.o: $S/dev/e1000/e1000_i210.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_api.ln: $S/dev/e1000/e1000_api.c
	${NORMAL_LINT}

e1000_api.o: $S/dev/e1000/e1000_api.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_mac.ln: $S/dev/e1000/e1000_mac.c
	${NORMAL_LINT}

e1000_mac.o: $S/dev/e1000/e1000_mac.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_manage.ln: $S/dev/e1000/e1000_manage.c
	${NORMAL_LINT}

e1000_manage.o: $S/dev/e1000/e1000_manage.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_nvm.ln: $S/dev/e1000/e1000_nvm.c
	${NORMAL_LINT}

e1000_nvm.o: $S/dev/e1000/e1000_nvm.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_phy.ln: $S/dev/e1000/e1000_phy.c
	${NORMAL_LINT}

e1000_phy.o: $S/dev/e1000/e1000_phy.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_vf.ln: $S/dev/e1000/e1000_vf.c
	${NORMAL_LINT}

e1000_vf.o: $S/dev/e1000/e1000_vf.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_mbx.ln: $S/dev/e1000/e1000_mbx.c
	${NORMAL_LINT}

e1000_mbx.o: $S/dev/e1000/e1000_mbx.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

e1000_osdep.ln: $S/dev/e1000/e1000_osdep.c
	${NORMAL_LINT}

e1000_osdep.o: $S/dev/e1000/e1000_osdep.c
	${NORMAL_C} -I$S/dev/e1000
	${NORMAL_CTFCONVERT}

if_et.ln: $S/dev/et/if_et.c
	${NORMAL_LINT}

if_et.o: $S/dev/et/if_et.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ep.ln: $S/dev/ep/if_ep.c
	${NORMAL_LINT}

if_ep.o: $S/dev/ep/if_ep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ep_isa.ln: $S/dev/ep/if_ep_isa.c
	${NORMAL_LINT}

if_ep_isa.o: $S/dev/ep/if_ep_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ep_pccard.ln: $S/dev/ep/if_ep_pccard.c
	${NORMAL_LINT}

if_ep_pccard.o: $S/dev/ep/if_ep_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

esp_pci.ln: $S/dev/esp/esp_pci.c
	${NORMAL_LINT}

esp_pci.o: $S/dev/esp/esp_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ncr53c9x.ln: $S/dev/esp/ncr53c9x.c
	${NORMAL_LINT}

ncr53c9x.o: $S/dev/esp/ncr53c9x.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ex.ln: $S/dev/ex/if_ex.c
	${NORMAL_LINT}

if_ex.o: $S/dev/ex/if_ex.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ex_isa.ln: $S/dev/ex/if_ex_isa.c
	${NORMAL_LINT}

if_ex_isa.o: $S/dev/ex/if_ex_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ex_pccard.ln: $S/dev/ex/if_ex_pccard.c
	${NORMAL_LINT}

if_ex_pccard.o: $S/dev/ex/if_ex_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exca.ln: $S/dev/exca/exca.c
	${NORMAL_LINT}

exca.o: $S/dev/exca/exca.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

splash.ln: $S/dev/fb/splash.c
	${NORMAL_LINT}

splash.o: $S/dev/fb/splash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_fe.ln: $S/dev/fe/if_fe.c
	${NORMAL_LINT}

if_fe.o: $S/dev/fe/if_fe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_fe_pccard.ln: $S/dev/fe/if_fe_pccard.c
	${NORMAL_LINT}

if_fe_pccard.o: $S/dev/fe/if_fe_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_fxp.ln: $S/dev/fxp/if_fxp.c
	${NORMAL_LINT}

if_fxp.o: $S/dev/fxp/if_fxp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inphy.ln: $S/dev/fxp/inphy.c
	${NORMAL_LINT}

inphy.o: $S/dev/fxp/inphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_gem.ln: $S/dev/gem/if_gem.c
	${NORMAL_LINT}

if_gem.o: $S/dev/gem/if_gem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_gem_pci.ln: $S/dev/gem/if_gem_pci.c
	${NORMAL_LINT}

if_gem_pci.o: $S/dev/gem/if_gem_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_hme.ln: $S/dev/hme/if_hme.c
	${NORMAL_LINT}

if_hme.o: $S/dev/hme/if_hme.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_hme_pci.ln: $S/dev/hme/if_hme_pci.c
	${NORMAL_LINT}

if_hme_pci.o: $S/dev/hme/if_hme_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hptiop.ln: $S/dev/hptiop/hptiop.c
	${NORMAL_LINT}

hptiop.o: $S/dev/hptiop/hptiop.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ida.ln: $S/dev/ida/ida.c
	${NORMAL_LINT}

ida.o: $S/dev/ida/ida.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ida_disk.ln: $S/dev/ida/ida_disk.c
	${NORMAL_LINT}

ida_disk.o: $S/dev/ida/ida_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ida_pci.ln: $S/dev/ida/ida_pci.c
	${NORMAL_LINT}

ida_pci.o: $S/dev/ida/ida_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

iir.ln: $S/dev/iir/iir.c
	${NORMAL_LINT}

iir.o: $S/dev/iir/iir.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

iir_ctrl.ln: $S/dev/iir/iir_ctrl.c
	${NORMAL_LINT}

iir_ctrl.o: $S/dev/iir/iir_ctrl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

iir_pci.ln: $S/dev/iir/iir_pci.c
	${NORMAL_LINT}

iir_pci.o: $S/dev/iir/iir_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ips.ln: $S/dev/ips/ips.c
	${NORMAL_LINT}

ips.o: $S/dev/ips/ips.c
	${NORMAL_C} ${NO_WSOMETIMES_UNINITIALIZED}
	${NORMAL_CTFCONVERT}

ips_commands.ln: $S/dev/ips/ips_commands.c
	${NORMAL_LINT}

ips_commands.o: $S/dev/ips/ips_commands.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ips_disk.ln: $S/dev/ips/ips_disk.c
	${NORMAL_LINT}

ips_disk.o: $S/dev/ips/ips_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ips_ioctl.ln: $S/dev/ips/ips_ioctl.c
	${NORMAL_LINT}

ips_ioctl.o: $S/dev/ips/ips_ioctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ips_pci.ln: $S/dev/ips/ips_pci.c
	${NORMAL_LINT}

ips_pci.o: $S/dev/ips/ips_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ipw.ln: $S/dev/ipw/if_ipw.c
	${NORMAL_LINT}

if_ipw.o: $S/dev/ipw/if_ipw.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isp.ln: $S/dev/isp/isp.c
	${NORMAL_LINT}

isp.o: $S/dev/isp/isp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isp_freebsd.ln: $S/dev/isp/isp_freebsd.c
	${NORMAL_LINT}

isp_freebsd.o: $S/dev/isp/isp_freebsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isp_library.ln: $S/dev/isp/isp_library.c
	${NORMAL_LINT}

isp_library.o: $S/dev/isp/isp_library.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isp_pci.ln: $S/dev/isp/isp_pci.c
	${NORMAL_LINT}

isp_pci.o: $S/dev/isp/isp_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isp_target.ln: $S/dev/isp/isp_target.c
	${NORMAL_LINT}

isp_target.o: $S/dev/isp/isp_target.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_iwi.ln: $S/dev/iwi/if_iwi.c
	${NORMAL_LINT}

if_iwi.o: $S/dev/iwi/if_iwi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_iwn.ln: $S/dev/iwn/if_iwn.c
	${NORMAL_LINT}

if_iwn.o: $S/dev/iwn/if_iwn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ixgbe.ln: $S/dev/ixgbe/ixgbe.c
	${NORMAL_LINT}

ixgbe.o: $S/dev/ixgbe/ixgbe.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixv.ln: $S/dev/ixgbe/ixv.c
	${NORMAL_LINT}

ixv.o: $S/dev/ixgbe/ixv.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_phy.ln: $S/dev/ixgbe/ixgbe_phy.c
	${NORMAL_LINT}

ixgbe_phy.o: $S/dev/ixgbe/ixgbe_phy.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_api.ln: $S/dev/ixgbe/ixgbe_api.c
	${NORMAL_LINT}

ixgbe_api.o: $S/dev/ixgbe/ixgbe_api.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_common.ln: $S/dev/ixgbe/ixgbe_common.c
	${NORMAL_LINT}

ixgbe_common.o: $S/dev/ixgbe/ixgbe_common.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_mbx.ln: $S/dev/ixgbe/ixgbe_mbx.c
	${NORMAL_LINT}

ixgbe_mbx.o: $S/dev/ixgbe/ixgbe_mbx.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_vf.ln: $S/dev/ixgbe/ixgbe_vf.c
	${NORMAL_LINT}

ixgbe_vf.o: $S/dev/ixgbe/ixgbe_vf.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_82598.ln: $S/dev/ixgbe/ixgbe_82598.c
	${NORMAL_LINT}

ixgbe_82598.o: $S/dev/ixgbe/ixgbe_82598.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_82599.ln: $S/dev/ixgbe/ixgbe_82599.c
	${NORMAL_LINT}

ixgbe_82599.o: $S/dev/ixgbe/ixgbe_82599.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_x540.ln: $S/dev/ixgbe/ixgbe_x540.c
	${NORMAL_LINT}

ixgbe_x540.o: $S/dev/ixgbe/ixgbe_x540.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_dcb.ln: $S/dev/ixgbe/ixgbe_dcb.c
	${NORMAL_LINT}

ixgbe_dcb.o: $S/dev/ixgbe/ixgbe_dcb.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_dcb_82598.ln: $S/dev/ixgbe/ixgbe_dcb_82598.c
	${NORMAL_LINT}

ixgbe_dcb_82598.o: $S/dev/ixgbe/ixgbe_dcb_82598.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

ixgbe_dcb_82599.ln: $S/dev/ixgbe/ixgbe_dcb_82599.c
	${NORMAL_LINT}

ixgbe_dcb_82599.o: $S/dev/ixgbe/ixgbe_dcb_82599.c
	${NORMAL_C} -I$S/dev/ixgbe
	${NORMAL_CTFCONVERT}

if_jme.ln: $S/dev/jme/if_jme.c
	${NORMAL_LINT}

if_jme.o: $S/dev/jme/if_jme.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kbdmux.ln: $S/dev/kbdmux/kbdmux.c
	${NORMAL_LINT}

kbdmux.o: $S/dev/kbdmux/kbdmux.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

am7990.ln: $S/dev/le/am7990.c
	${NORMAL_LINT}

am7990.o: $S/dev/le/am7990.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

am79900.ln: $S/dev/le/am79900.c
	${NORMAL_LINT}

am79900.o: $S/dev/le/am79900.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_le_pci.ln: $S/dev/le/if_le_pci.c
	${NORMAL_LINT}

if_le_pci.o: $S/dev/le/if_le_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

lance.ln: $S/dev/le/lance.c
	${NORMAL_LINT}

lance.o: $S/dev/le/lance.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

led.ln: $S/dev/led/led.c
	${NORMAL_LINT}

led.o: $S/dev/led/led.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_lge.ln: $S/dev/lge/if_lge.c
	${NORMAL_LINT}

if_lge.o: $S/dev/lge/if_lge.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_malo.ln: $S/dev/malo/if_malo.c
	${NORMAL_LINT}

if_malo.o: $S/dev/malo/if_malo.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_malohal.ln: $S/dev/malo/if_malohal.c
	${NORMAL_LINT}

if_malohal.o: $S/dev/malo/if_malohal.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_malo_pci.ln: $S/dev/malo/if_malo_pci.c
	${NORMAL_LINT}

if_malo_pci.o: $S/dev/malo/if_malo_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md.ln: $S/dev/md/md.c
	${NORMAL_LINT}

md.o: $S/dev/md/md.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memdev.ln: $S/dev/mem/memdev.c
	${NORMAL_LINT}

memdev.o: $S/dev/mem/memdev.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memutil.ln: $S/dev/mem/memutil.c
	${NORMAL_LINT}

memutil.o: $S/dev/mem/memutil.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mfi.ln: $S/dev/mfi/mfi.c
	${NORMAL_LINT}

mfi.o: $S/dev/mfi/mfi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mfi_debug.ln: $S/dev/mfi/mfi_debug.c
	${NORMAL_LINT}

mfi_debug.o: $S/dev/mfi/mfi_debug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mfi_pci.ln: $S/dev/mfi/mfi_pci.c
	${NORMAL_LINT}

mfi_pci.o: $S/dev/mfi/mfi_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mfi_disk.ln: $S/dev/mfi/mfi_disk.c
	${NORMAL_LINT}

mfi_disk.o: $S/dev/mfi/mfi_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mfi_syspd.ln: $S/dev/mfi/mfi_syspd.c
	${NORMAL_LINT}

mfi_syspd.o: $S/dev/mfi/mfi_syspd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mfi_tbolt.ln: $S/dev/mfi/mfi_tbolt.c
	${NORMAL_LINT}

mfi_tbolt.o: $S/dev/mfi/mfi_tbolt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acphy.ln: $S/dev/mii/acphy.c
	${NORMAL_LINT}

acphy.o: $S/dev/mii/acphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

amphy.ln: $S/dev/mii/amphy.c
	${NORMAL_LINT}

amphy.o: $S/dev/mii/amphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atphy.ln: $S/dev/mii/atphy.c
	${NORMAL_LINT}

atphy.o: $S/dev/mii/atphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

axphy.ln: $S/dev/mii/axphy.c
	${NORMAL_LINT}

axphy.o: $S/dev/mii/axphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bmtphy.ln: $S/dev/mii/bmtphy.c
	${NORMAL_LINT}

bmtphy.o: $S/dev/mii/bmtphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

brgphy.ln: $S/dev/mii/brgphy.c
	${NORMAL_LINT}

brgphy.o: $S/dev/mii/brgphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ciphy.ln: $S/dev/mii/ciphy.c
	${NORMAL_LINT}

ciphy.o: $S/dev/mii/ciphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

e1000phy.ln: $S/dev/mii/e1000phy.c
	${NORMAL_LINT}

e1000phy.o: $S/dev/mii/e1000phy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

gentbi.ln: $S/dev/mii/gentbi.c
	${NORMAL_LINT}

gentbi.o: $S/dev/mii/gentbi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

icsphy.ln: $S/dev/mii/icsphy.c
	${NORMAL_LINT}

icsphy.o: $S/dev/mii/icsphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip1000phy.ln: $S/dev/mii/ip1000phy.c
	${NORMAL_LINT}

ip1000phy.o: $S/dev/mii/ip1000phy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

jmphy.ln: $S/dev/mii/jmphy.c
	${NORMAL_LINT}

jmphy.o: $S/dev/mii/jmphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

lxtphy.ln: $S/dev/mii/lxtphy.c
	${NORMAL_LINT}

lxtphy.o: $S/dev/mii/lxtphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mii.ln: $S/dev/mii/mii.c
	${NORMAL_LINT}

mii.o: $S/dev/mii/mii.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mii_bitbang.ln: $S/dev/mii/mii_bitbang.c
	${NORMAL_LINT}

mii_bitbang.o: $S/dev/mii/mii_bitbang.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mii_physubr.ln: $S/dev/mii/mii_physubr.c
	${NORMAL_LINT}

mii_physubr.o: $S/dev/mii/mii_physubr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

miibus_if.ln: $S/dev/mii/miibus_if.m
	${NORMAL_LINT}

miibus_if.o: $S/dev/mii/miibus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

mlphy.ln: $S/dev/mii/mlphy.c
	${NORMAL_LINT}

mlphy.o: $S/dev/mii/mlphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsgphy.ln: $S/dev/mii/nsgphy.c
	${NORMAL_LINT}

nsgphy.o: $S/dev/mii/nsgphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsphy.ln: $S/dev/mii/nsphy.c
	${NORMAL_LINT}

nsphy.o: $S/dev/mii/nsphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nsphyter.ln: $S/dev/mii/nsphyter.c
	${NORMAL_LINT}

nsphyter.o: $S/dev/mii/nsphyter.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pnaphy.ln: $S/dev/mii/pnaphy.c
	${NORMAL_LINT}

pnaphy.o: $S/dev/mii/pnaphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

qsphy.ln: $S/dev/mii/qsphy.c
	${NORMAL_LINT}

qsphy.o: $S/dev/mii/qsphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rdcphy.ln: $S/dev/mii/rdcphy.c
	${NORMAL_LINT}

rdcphy.o: $S/dev/mii/rdcphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rgephy.ln: $S/dev/mii/rgephy.c
	${NORMAL_LINT}

rgephy.o: $S/dev/mii/rgephy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rlphy.ln: $S/dev/mii/rlphy.c
	${NORMAL_LINT}

rlphy.o: $S/dev/mii/rlphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

smcphy.ln: $S/dev/mii/smcphy.c
	${NORMAL_LINT}

smcphy.o: $S/dev/mii/smcphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tdkphy.ln: $S/dev/mii/tdkphy.c
	${NORMAL_LINT}

tdkphy.o: $S/dev/mii/tdkphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tlphy.ln: $S/dev/mii/tlphy.c
	${NORMAL_LINT}

tlphy.o: $S/dev/mii/tlphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

truephy.ln: $S/dev/mii/truephy.c
	${NORMAL_LINT}

truephy.o: $S/dev/mii/truephy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ukphy.ln: $S/dev/mii/ukphy.c
	${NORMAL_LINT}

ukphy.o: $S/dev/mii/ukphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ukphy_subr.ln: $S/dev/mii/ukphy_subr.c
	${NORMAL_LINT}

ukphy_subr.o: $S/dev/mii/ukphy_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xmphy.ln: $S/dev/mii/xmphy.c
	${NORMAL_LINT}

xmphy.o: $S/dev/mii/xmphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mlx.ln: $S/dev/mlx/mlx.c
	${NORMAL_LINT}

mlx.o: $S/dev/mlx/mlx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mlx_disk.ln: $S/dev/mlx/mlx_disk.c
	${NORMAL_LINT}

mlx_disk.o: $S/dev/mlx/mlx_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mlx_pci.ln: $S/dev/mlx/mlx_pci.c
	${NORMAL_LINT}

mlx_pci.o: $S/dev/mlx/mlx_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mly.ln: $S/dev/mly/mly.c
	${NORMAL_LINT}

mly.o: $S/dev/mly/mly.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mmcbr_if.ln: $S/dev/mmc/mmcbr_if.m
	${NORMAL_LINT}

mmcbr_if.o: $S/dev/mmc/mmcbr_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

mmcbus_if.ln: $S/dev/mmc/mmcbus_if.m
	${NORMAL_LINT}

mmcbus_if.o: $S/dev/mmc/mmcbus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

mps.ln: $S/dev/mps/mps.c
	${NORMAL_LINT}

mps.o: $S/dev/mps/mps.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mps_config.ln: $S/dev/mps/mps_config.c
	${NORMAL_LINT}

mps_config.o: $S/dev/mps/mps_config.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mps_mapping.ln: $S/dev/mps/mps_mapping.c
	${NORMAL_LINT}

mps_mapping.o: $S/dev/mps/mps_mapping.c
	${NORMAL_C} ${NO_WSOMETIMES_UNINITIALIZED}
	${NORMAL_CTFCONVERT}

mps_pci.ln: $S/dev/mps/mps_pci.c
	${NORMAL_LINT}

mps_pci.o: $S/dev/mps/mps_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mps_sas.ln: $S/dev/mps/mps_sas.c
	${NORMAL_LINT}

mps_sas.o: $S/dev/mps/mps_sas.c
	${NORMAL_C} ${NO_WUNNEEDED_INTERNAL_DECL}
	${NORMAL_CTFCONVERT}

mps_sas_lsi.ln: $S/dev/mps/mps_sas_lsi.c
	${NORMAL_LINT}

mps_sas_lsi.o: $S/dev/mps/mps_sas_lsi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mps_table.ln: $S/dev/mps/mps_table.c
	${NORMAL_LINT}

mps_table.o: $S/dev/mps/mps_table.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mps_user.ln: $S/dev/mps/mps_user.c
	${NORMAL_LINT}

mps_user.o: $S/dev/mps/mps_user.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpt.ln: $S/dev/mpt/mpt.c
	${NORMAL_LINT}

mpt.o: $S/dev/mpt/mpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpt_cam.ln: $S/dev/mpt/mpt_cam.c
	${NORMAL_LINT}

mpt_cam.o: $S/dev/mpt/mpt_cam.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpt_debug.ln: $S/dev/mpt/mpt_debug.c
	${NORMAL_LINT}

mpt_debug.o: $S/dev/mpt/mpt_debug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpt_pci.ln: $S/dev/mpt/mpt_pci.c
	${NORMAL_LINT}

mpt_pci.o: $S/dev/mpt/mpt_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpt_raid.ln: $S/dev/mpt/mpt_raid.c
	${NORMAL_LINT}

mpt_raid.o: $S/dev/mpt/mpt_raid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpt_user.ln: $S/dev/mpt/mpt_user.c
	${NORMAL_LINT}

mpt_user.o: $S/dev/mpt/mpt_user.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_msk.ln: $S/dev/msk/if_msk.c
	${NORMAL_LINT}

if_msk.o: $S/dev/msk/if_msk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mvs.ln: $S/dev/mvs/mvs.c
	${NORMAL_LINT}

mvs.o: $S/dev/mvs/mvs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mvs_if.ln: $S/dev/mvs/mvs_if.m
	${NORMAL_LINT}

mvs_if.o: $S/dev/mvs/mvs_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

mvs_pci.ln: $S/dev/mvs/mvs_pci.c
	${NORMAL_LINT}

mvs_pci.o: $S/dev/mvs/mvs_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_mwl.ln: $S/dev/mwl/if_mwl.c
	${NORMAL_LINT}

if_mwl.o: $S/dev/mwl/if_mwl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_mwl_pci.ln: $S/dev/mwl/if_mwl_pci.c
	${NORMAL_LINT}

if_mwl_pci.o: $S/dev/mwl/if_mwl_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mwlhal.ln: $S/dev/mwl/mwlhal.c
	${NORMAL_LINT}

mwlhal.o: $S/dev/mwl/mwlhal.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_nge.ln: $S/dev/nge/if_nge.c
	${NORMAL_LINT}

if_nge.o: $S/dev/nge/if_nge.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

null.ln: $S/dev/null/null.c
	${NORMAL_LINT}

null.o: $S/dev/null/null.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

card_if.ln: $S/dev/pccard/card_if.m
	${NORMAL_LINT}

card_if.o: $S/dev/pccard/card_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

pccard.ln: $S/dev/pccard/pccard.c
	${NORMAL_LINT}

pccard.o: $S/dev/pccard/pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pccard_cis.ln: $S/dev/pccard/pccard_cis.c
	${NORMAL_LINT}

pccard_cis.o: $S/dev/pccard/pccard_cis.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pccard_cis_quirks.ln: $S/dev/pccard/pccard_cis_quirks.c
	${NORMAL_LINT}

pccard_cis_quirks.o: $S/dev/pccard/pccard_cis_quirks.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pccard_device.ln: $S/dev/pccard/pccard_device.c
	${NORMAL_LINT}

pccard_device.o: $S/dev/pccard/pccard_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

power_if.ln: $S/dev/pccard/power_if.m
	${NORMAL_LINT}

power_if.o: $S/dev/pccard/power_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

pccbb.ln: $S/dev/pccbb/pccbb.c
	${NORMAL_LINT}

pccbb.o: $S/dev/pccbb/pccbb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pccbb_isa.ln: $S/dev/pccbb/pccbb_isa.c
	${NORMAL_LINT}

pccbb_isa.o: $S/dev/pccbb/pccbb_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pccbb_pci.ln: $S/dev/pccbb/pccbb_pci.c
	${NORMAL_LINT}

pccbb_pci.o: $S/dev/pccbb/pccbb_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fixup_pci.ln: $S/dev/pci/fixup_pci.c
	${NORMAL_LINT}

fixup_pci.o: $S/dev/pci/fixup_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hostb_pci.ln: $S/dev/pci/hostb_pci.c
	${NORMAL_LINT}

hostb_pci.o: $S/dev/pci/hostb_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ignore_pci.ln: $S/dev/pci/ignore_pci.c
	${NORMAL_LINT}

ignore_pci.o: $S/dev/pci/ignore_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isa_pci.ln: $S/dev/pci/isa_pci.c
	${NORMAL_LINT}

isa_pci.o: $S/dev/pci/isa_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pci.ln: $S/dev/pci/pci.c
	${NORMAL_LINT}

pci.o: $S/dev/pci/pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pci_if.ln: $S/dev/pci/pci_if.m
	${NORMAL_LINT}

pci_if.o: $S/dev/pci/pci_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

pci_pci.ln: $S/dev/pci/pci_pci.c
	${NORMAL_LINT}

pci_pci.o: $S/dev/pci/pci_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pci_subr.ln: $S/dev/pci/pci_subr.c
	${NORMAL_LINT}

pci_subr.o: $S/dev/pci/pci_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pci_user.ln: $S/dev/pci/pci_user.c
	${NORMAL_LINT}

pci_user.o: $S/dev/pci/pci_user.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pcib_if.ln: $S/dev/pci/pcib_if.m
	${NORMAL_LINT}

pcib_if.o: $S/dev/pci/pcib_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

vga_pci.ln: $S/dev/pci/vga_pci.c
	${NORMAL_LINT}

vga_pci.o: $S/dev/pci/vga_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_pcn.ln: $S/dev/pcn/if_pcn.c
	${NORMAL_LINT}

if_pcn.o: $S/dev/pcn/if_pcn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_plip.ln: $S/dev/ppbus/if_plip.c
	${NORMAL_LINT}

if_plip.o: $S/dev/ppbus/if_plip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

lpt.ln: $S/dev/ppbus/lpt.c
	${NORMAL_LINT}

lpt.o: $S/dev/ppbus/lpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppb_1284.ln: $S/dev/ppbus/ppb_1284.c
	${NORMAL_LINT}

ppb_1284.o: $S/dev/ppbus/ppb_1284.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppb_base.ln: $S/dev/ppbus/ppb_base.c
	${NORMAL_LINT}

ppb_base.o: $S/dev/ppbus/ppb_base.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppb_msq.ln: $S/dev/ppbus/ppb_msq.c
	${NORMAL_LINT}

ppb_msq.o: $S/dev/ppbus/ppb_msq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppbconf.ln: $S/dev/ppbus/ppbconf.c
	${NORMAL_LINT}

ppbconf.o: $S/dev/ppbus/ppbconf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppbus_if.ln: $S/dev/ppbus/ppbus_if.m
	${NORMAL_LINT}

ppbus_if.o: $S/dev/ppbus/ppbus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

ppi.ln: $S/dev/ppbus/ppi.c
	${NORMAL_LINT}

ppi.o: $S/dev/ppbus/ppi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppc.ln: $S/dev/ppc/ppc.c
	${NORMAL_LINT}

ppc.o: $S/dev/ppc/ppc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppc_acpi.ln: $S/dev/ppc/ppc_acpi.c
	${NORMAL_LINT}

ppc_acpi.o: $S/dev/ppc/ppc_acpi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppc_isa.ln: $S/dev/ppc/ppc_isa.c
	${NORMAL_LINT}

ppc_isa.o: $S/dev/ppc/ppc_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppc_pci.ln: $S/dev/ppc/ppc_pci.c
	${NORMAL_LINT}

ppc_pci.o: $S/dev/ppc/ppc_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ppc_puc.ln: $S/dev/ppc/ppc_puc.c
	${NORMAL_LINT}

ppc_puc.o: $S/dev/ppc/ppc_puc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pty.ln: $S/dev/pty/pty.c
	${NORMAL_LINT}

pty.o: $S/dev/pty/pty.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

puc.ln: $S/dev/puc/puc.c
	${NORMAL_LINT}

puc.o: $S/dev/puc/puc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

puc_cfg.ln: $S/dev/puc/puc_cfg.c
	${NORMAL_LINT}

puc_cfg.o: $S/dev/puc/puc_cfg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

puc_pccard.ln: $S/dev/puc/puc_pccard.c
	${NORMAL_LINT}

puc_pccard.o: $S/dev/puc/puc_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

puc_pci.ln: $S/dev/puc/puc_pci.c
	${NORMAL_LINT}

puc_pci.o: $S/dev/puc/puc_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pucdata.ln: $S/dev/puc/pucdata.c
	${NORMAL_LINT}

pucdata.o: $S/dev/puc/pucdata.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rt2560.ln: $S/dev/ral/rt2560.c
	${NORMAL_LINT}

rt2560.o: $S/dev/ral/rt2560.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rt2661.ln: $S/dev/ral/rt2661.c
	${NORMAL_LINT}

rt2661.o: $S/dev/ral/rt2661.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rt2860.ln: $S/dev/ral/rt2860.c
	${NORMAL_LINT}

rt2860.o: $S/dev/ral/rt2860.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ral_pci.ln: $S/dev/ral/if_ral_pci.c
	${NORMAL_LINT}

if_ral_pci.o: $S/dev/ral/if_ral_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

harvest.ln: $S/dev/random/harvest.c
	${NORMAL_LINT}

harvest.o: $S/dev/random/harvest.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hash.ln: $S/dev/random/hash.c
	${NORMAL_LINT}

hash.o: $S/dev/random/hash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

probe.ln: $S/dev/random/probe.c
	${NORMAL_LINT}

probe.o: $S/dev/random/probe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

randomdev.ln: $S/dev/random/randomdev.c
	${NORMAL_LINT}

randomdev.o: $S/dev/random/randomdev.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

randomdev_soft.ln: $S/dev/random/randomdev_soft.c
	${NORMAL_LINT}

randomdev_soft.o: $S/dev/random/randomdev_soft.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

yarrow.ln: $S/dev/random/yarrow.c
	${NORMAL_LINT}

yarrow.o: $S/dev/random/yarrow.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_re.ln: $S/dev/re/if_re.c
	${NORMAL_LINT}

if_re.o: $S/dev/re/if_re.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_sf.ln: $S/dev/sf/if_sf.c
	${NORMAL_LINT}

if_sf.o: $S/dev/sf/if_sf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_sge.ln: $S/dev/sge/if_sge.c
	${NORMAL_LINT}

if_sge.o: $S/dev/sge/if_sge.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

siis.ln: $S/dev/siis/siis.c
	${NORMAL_LINT}

siis.o: $S/dev/siis/siis.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_sis.ln: $S/dev/sis/if_sis.c
	${NORMAL_LINT}

if_sis.o: $S/dev/sis/if_sis.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_sk.ln: $S/dev/sk/if_sk.c
	${NORMAL_LINT}

if_sk.o: $S/dev/sk/if_sk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_sn.ln: $S/dev/sn/if_sn.c
	${NORMAL_LINT}

if_sn.o: $S/dev/sn/if_sn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_sn_isa.ln: $S/dev/sn/if_sn_isa.c
	${NORMAL_LINT}

if_sn_isa.o: $S/dev/sn/if_sn_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_sn_pccard.ln: $S/dev/sn/if_sn_pccard.c
	${NORMAL_LINT}

if_sn_pccard.o: $S/dev/sn/if_sn_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clone.ln: $S/dev/sound/clone.c
	${NORMAL_LINT}

clone.o: $S/dev/sound/clone.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

unit.ln: $S/dev/sound/unit.c
	${NORMAL_LINT}

unit.o: $S/dev/sound/unit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sndbuf_dma.ln: $S/dev/sound/isa/sndbuf_dma.c
	${NORMAL_LINT}

sndbuf_dma.o: $S/dev/sound/isa/sndbuf_dma.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cmi.ln: $S/dev/sound/pci/cmi.c
	${NORMAL_LINT}

cmi.o: $S/dev/sound/pci/cmi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

csa.ln: $S/dev/sound/pci/csa.c
	${NORMAL_LINT}

csa.o: $S/dev/sound/pci/csa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

csapcm.ln: $S/dev/sound/pci/csapcm.c
	${NORMAL_LINT}

csapcm.o: $S/dev/sound/pci/csapcm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

emu10kx.ln: $S/dev/sound/pci/emu10kx.c
	${NORMAL_LINT}

emu10kx.o: $S/dev/sound/pci/emu10kx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

emu10kx-pcm.ln: $S/dev/sound/pci/emu10kx-pcm.c
	${NORMAL_LINT}

emu10kx-pcm.o: $S/dev/sound/pci/emu10kx-pcm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

emu10kx-midi.ln: $S/dev/sound/pci/emu10kx-midi.c
	${NORMAL_LINT}

emu10kx-midi.o: $S/dev/sound/pci/emu10kx-midi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

es137x.ln: $S/dev/sound/pci/es137x.c
	${NORMAL_LINT}

es137x.o: $S/dev/sound/pci/es137x.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ich.ln: $S/dev/sound/pci/ich.c
	${NORMAL_LINT}

ich.o: $S/dev/sound/pci/ich.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

via8233.ln: $S/dev/sound/pci/via8233.c
	${NORMAL_LINT}

via8233.o: $S/dev/sound/pci/via8233.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hdaa.ln: $S/dev/sound/pci/hda/hdaa.c
	${NORMAL_LINT}

hdaa.o: $S/dev/sound/pci/hda/hdaa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hdaa_patches.ln: $S/dev/sound/pci/hda/hdaa_patches.c
	${NORMAL_LINT}

hdaa_patches.o: $S/dev/sound/pci/hda/hdaa_patches.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hdac.ln: $S/dev/sound/pci/hda/hdac.c
	${NORMAL_LINT}

hdac.o: $S/dev/sound/pci/hda/hdac.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hdac_if.ln: $S/dev/sound/pci/hda/hdac_if.m
	${NORMAL_LINT}

hdac_if.o: $S/dev/sound/pci/hda/hdac_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

hdacc.ln: $S/dev/sound/pci/hda/hdacc.c
	${NORMAL_LINT}

hdacc.o: $S/dev/sound/pci/hda/hdacc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ac97.ln: $S/dev/sound/pcm/ac97.c
	${NORMAL_LINT}

ac97.o: $S/dev/sound/pcm/ac97.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ac97_if.ln: $S/dev/sound/pcm/ac97_if.m
	${NORMAL_LINT}

ac97_if.o: $S/dev/sound/pcm/ac97_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

ac97_patch.ln: $S/dev/sound/pcm/ac97_patch.c
	${NORMAL_LINT}

ac97_patch.o: $S/dev/sound/pcm/ac97_patch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

buffer.ln: $S/dev/sound/pcm/buffer.c snd_fxdiv_gen.h
	${NORMAL_LINT}

buffer.o: $S/dev/sound/pcm/buffer.c snd_fxdiv_gen.h
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

channel.ln: $S/dev/sound/pcm/channel.c
	${NORMAL_LINT}

channel.o: $S/dev/sound/pcm/channel.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

channel_if.ln: $S/dev/sound/pcm/channel_if.m
	${NORMAL_LINT}

channel_if.o: $S/dev/sound/pcm/channel_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

dsp.ln: $S/dev/sound/pcm/dsp.c
	${NORMAL_LINT}

dsp.o: $S/dev/sound/pcm/dsp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder.ln: $S/dev/sound/pcm/feeder.c
	${NORMAL_LINT}

feeder.o: $S/dev/sound/pcm/feeder.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder_chain.ln: $S/dev/sound/pcm/feeder_chain.c
	${NORMAL_LINT}

feeder_chain.o: $S/dev/sound/pcm/feeder_chain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder_eq.ln: $S/dev/sound/pcm/feeder_eq.c snd_fxdiv_gen.h
	${NORMAL_LINT}

feeder_eq.o: $S/dev/sound/pcm/feeder_eq.c snd_fxdiv_gen.h
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder_if.ln: $S/dev/sound/pcm/feeder_if.m
	${NORMAL_LINT}

feeder_if.o: $S/dev/sound/pcm/feeder_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

feeder_format.ln: $S/dev/sound/pcm/feeder_format.c snd_fxdiv_gen.h
	${NORMAL_LINT}

feeder_format.o: $S/dev/sound/pcm/feeder_format.c snd_fxdiv_gen.h
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder_matrix.ln: $S/dev/sound/pcm/feeder_matrix.c snd_fxdiv_gen.h
	${NORMAL_LINT}

feeder_matrix.o: $S/dev/sound/pcm/feeder_matrix.c snd_fxdiv_gen.h
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder_mixer.ln: $S/dev/sound/pcm/feeder_mixer.c snd_fxdiv_gen.h
	${NORMAL_LINT}

feeder_mixer.o: $S/dev/sound/pcm/feeder_mixer.c snd_fxdiv_gen.h
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder_rate.ln: $S/dev/sound/pcm/feeder_rate.c snd_fxdiv_gen.h
	${NORMAL_LINT}

feeder_rate.o: $S/dev/sound/pcm/feeder_rate.c snd_fxdiv_gen.h
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

feeder_volume.ln: $S/dev/sound/pcm/feeder_volume.c snd_fxdiv_gen.h
	${NORMAL_LINT}

feeder_volume.o: $S/dev/sound/pcm/feeder_volume.c snd_fxdiv_gen.h
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mixer.ln: $S/dev/sound/pcm/mixer.c
	${NORMAL_LINT}

mixer.o: $S/dev/sound/pcm/mixer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mixer_if.ln: $S/dev/sound/pcm/mixer_if.m
	${NORMAL_LINT}

mixer_if.o: $S/dev/sound/pcm/mixer_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

sndstat.ln: $S/dev/sound/pcm/sndstat.c
	${NORMAL_LINT}

sndstat.o: $S/dev/sound/pcm/sndstat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sound.ln: $S/dev/sound/pcm/sound.c
	${NORMAL_LINT}

sound.o: $S/dev/sound/pcm/sound.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vchan.ln: $S/dev/sound/pcm/vchan.c
	${NORMAL_LINT}

vchan.o: $S/dev/sound/pcm/vchan.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uaudio.ln: $S/dev/sound/usb/uaudio.c
	${NORMAL_LINT}

uaudio.o: $S/dev/sound/usb/uaudio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uaudio_pcm.ln: $S/dev/sound/usb/uaudio_pcm.c
	${NORMAL_LINT}

uaudio_pcm.o: $S/dev/sound/usb/uaudio_pcm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

midi.ln: $S/dev/sound/midi/midi.c
	${NORMAL_LINT}

midi.o: $S/dev/sound/midi/midi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpu401.ln: $S/dev/sound/midi/mpu401.c
	${NORMAL_LINT}

mpu401.o: $S/dev/sound/midi/mpu401.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpu_if.ln: $S/dev/sound/midi/mpu_if.m
	${NORMAL_LINT}

mpu_if.o: $S/dev/sound/midi/mpu_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

mpufoi_if.ln: $S/dev/sound/midi/mpufoi_if.m
	${NORMAL_LINT}

mpufoi_if.o: $S/dev/sound/midi/mpufoi_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

sequencer.ln: $S/dev/sound/midi/sequencer.c
	${NORMAL_LINT}

sequencer.o: $S/dev/sound/midi/sequencer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

synth_if.ln: $S/dev/sound/midi/synth_if.m
	${NORMAL_LINT}

synth_if.o: $S/dev/sound/midi/synth_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

if_ste.ln: $S/dev/ste/if_ste.c
	${NORMAL_LINT}

if_ste.o: $S/dev/ste/if_ste.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_stge.ln: $S/dev/stge/if_stge.c
	${NORMAL_LINT}

if_stge.o: $S/dev/stge/if_stge.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sym_hipd.ln: $S/dev/sym/sym_hipd.c $S/dev/sym/sym_{conf,defs}.h
	${NORMAL_LINT}

sym_hipd.o: $S/dev/sym/sym_hipd.c $S/dev/sym/sym_{conf,defs}.h
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

schistory.ln: $S/dev/syscons/schistory.c
	${NORMAL_LINT}

schistory.o: $S/dev/syscons/schistory.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scmouse.ln: $S/dev/syscons/scmouse.c
	${NORMAL_LINT}

scmouse.o: $S/dev/syscons/scmouse.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scterm.ln: $S/dev/syscons/scterm.c
	${NORMAL_LINT}

scterm.o: $S/dev/syscons/scterm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scvidctl.ln: $S/dev/syscons/scvidctl.c
	${NORMAL_LINT}

scvidctl.o: $S/dev/syscons/scvidctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

syscons.ln: $S/dev/syscons/syscons.c
	${NORMAL_LINT}

syscons.o: $S/dev/syscons/syscons.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysmouse.ln: $S/dev/syscons/sysmouse.c
	${NORMAL_LINT}

sysmouse.o: $S/dev/syscons/sysmouse.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ti.ln: $S/dev/ti/if_ti.c
	${NORMAL_LINT}

if_ti.o: $S/dev/ti/if_ti.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_tl.ln: $S/dev/tl/if_tl.c
	${NORMAL_LINT}

if_tl.o: $S/dev/tl/if_tl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

trm.ln: $S/dev/trm/trm.c
	${NORMAL_LINT}

trm.o: $S/dev/trm/trm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tw_cl_init.ln: $S/dev/twa/tw_cl_init.c
	${NORMAL_LINT}

tw_cl_init.o: $S/dev/twa/tw_cl_init.c
	${NORMAL_C} -I$S/dev/twa
	${NORMAL_CTFCONVERT}

tw_cl_intr.ln: $S/dev/twa/tw_cl_intr.c
	${NORMAL_LINT}

tw_cl_intr.o: $S/dev/twa/tw_cl_intr.c
	${NORMAL_C} -I$S/dev/twa
	${NORMAL_CTFCONVERT}

tw_cl_io.ln: $S/dev/twa/tw_cl_io.c
	${NORMAL_LINT}

tw_cl_io.o: $S/dev/twa/tw_cl_io.c
	${NORMAL_C} -I$S/dev/twa
	${NORMAL_CTFCONVERT}

tw_cl_misc.ln: $S/dev/twa/tw_cl_misc.c
	${NORMAL_LINT}

tw_cl_misc.o: $S/dev/twa/tw_cl_misc.c
	${NORMAL_C} -I$S/dev/twa
	${NORMAL_CTFCONVERT}

tw_osl_cam.ln: $S/dev/twa/tw_osl_cam.c
	${NORMAL_LINT}

tw_osl_cam.o: $S/dev/twa/tw_osl_cam.c
	${NORMAL_C} -I$S/dev/twa
	${NORMAL_CTFCONVERT}

tw_osl_freebsd.ln: $S/dev/twa/tw_osl_freebsd.c
	${NORMAL_LINT}

tw_osl_freebsd.o: $S/dev/twa/tw_osl_freebsd.c
	${NORMAL_C} -I$S/dev/twa
	${NORMAL_CTFCONVERT}

twe.ln: $S/dev/twe/twe.c
	${NORMAL_LINT}

twe.o: $S/dev/twe/twe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

twe_freebsd.ln: $S/dev/twe/twe_freebsd.c
	${NORMAL_LINT}

twe_freebsd.o: $S/dev/twe/twe_freebsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tws.ln: $S/dev/tws/tws.c
	${NORMAL_LINT}

tws.o: $S/dev/tws/tws.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tws_cam.ln: $S/dev/tws/tws_cam.c
	${NORMAL_LINT}

tws_cam.o: $S/dev/tws/tws_cam.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tws_hdm.ln: $S/dev/tws/tws_hdm.c
	${NORMAL_LINT}

tws_hdm.o: $S/dev/tws/tws_hdm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tws_services.ln: $S/dev/tws/tws_services.c
	${NORMAL_LINT}

tws_services.o: $S/dev/tws/tws_services.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tws_user.ln: $S/dev/tws/tws_user.c
	${NORMAL_LINT}

tws_user.o: $S/dev/tws/tws_user.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_tx.ln: $S/dev/tx/if_tx.c
	${NORMAL_LINT}

if_tx.o: $S/dev/tx/if_tx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_txp.ln: $S/dev/txp/if_txp.c
	${NORMAL_LINT}

if_txp.o: $S/dev/txp/if_txp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_bus_acpi.ln: $S/dev/uart/uart_bus_acpi.c
	${NORMAL_LINT}

uart_bus_acpi.o: $S/dev/uart/uart_bus_acpi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_bus_isa.ln: $S/dev/uart/uart_bus_isa.c
	${NORMAL_LINT}

uart_bus_isa.o: $S/dev/uart/uart_bus_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_bus_pccard.ln: $S/dev/uart/uart_bus_pccard.c
	${NORMAL_LINT}

uart_bus_pccard.o: $S/dev/uart/uart_bus_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_bus_pci.ln: $S/dev/uart/uart_bus_pci.c
	${NORMAL_LINT}

uart_bus_pci.o: $S/dev/uart/uart_bus_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_bus_puc.ln: $S/dev/uart/uart_bus_puc.c
	${NORMAL_LINT}

uart_bus_puc.o: $S/dev/uart/uart_bus_puc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_core.ln: $S/dev/uart/uart_core.c
	${NORMAL_LINT}

uart_core.o: $S/dev/uart/uart_core.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_dev_ns8250.ln: $S/dev/uart/uart_dev_ns8250.c
	${NORMAL_LINT}

uart_dev_ns8250.o: $S/dev/uart/uart_dev_ns8250.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_if.ln: $S/dev/uart/uart_if.m
	${NORMAL_LINT}

uart_if.o: $S/dev/uart/uart_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

uart_subr.ln: $S/dev/uart/uart_subr.c
	${NORMAL_LINT}

uart_subr.o: $S/dev/uart/uart_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_tty.ln: $S/dev/uart/uart_tty.c
	${NORMAL_LINT}

uart_tty.o: $S/dev/uart/uart_tty.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ehci.ln: $S/dev/usb/controller/ehci.c
	${NORMAL_LINT}

ehci.o: $S/dev/usb/controller/ehci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ehci_pci.ln: $S/dev/usb/controller/ehci_pci.c
	${NORMAL_LINT}

ehci_pci.o: $S/dev/usb/controller/ehci_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ohci.ln: $S/dev/usb/controller/ohci.c
	${NORMAL_LINT}

ohci.o: $S/dev/usb/controller/ohci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ohci_pci.ln: $S/dev/usb/controller/ohci_pci.c
	${NORMAL_LINT}

ohci_pci.o: $S/dev/usb/controller/ohci_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uhci.ln: $S/dev/usb/controller/uhci.c
	${NORMAL_LINT}

uhci.o: $S/dev/usb/controller/uhci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uhci_pci.ln: $S/dev/usb/controller/uhci_pci.c
	${NORMAL_LINT}

uhci_pci.o: $S/dev/usb/controller/uhci_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xhci.ln: $S/dev/usb/controller/xhci.c
	${NORMAL_LINT}

xhci.o: $S/dev/usb/controller/xhci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xhci_pci.ln: $S/dev/usb/controller/xhci_pci.c
	${NORMAL_LINT}

xhci_pci.o: $S/dev/usb/controller/xhci_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_controller.ln: $S/dev/usb/controller/usb_controller.c
	${NORMAL_LINT}

usb_controller.o: $S/dev/usb/controller/usb_controller.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

umass.ln: $S/dev/usb/storage/umass.c
	${NORMAL_LINT}

umass.o: $S/dev/usb/storage/umass.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

urio.ln: $S/dev/usb/storage/urio.c
	${NORMAL_LINT}

urio.o: $S/dev/usb/storage/urio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_busdma.ln: $S/dev/usb/usb_busdma.c
	${NORMAL_LINT}

usb_busdma.o: $S/dev/usb/usb_busdma.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_compat_linux.ln: $S/dev/usb/usb_compat_linux.c
	${NORMAL_LINT}

usb_compat_linux.o: $S/dev/usb/usb_compat_linux.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_core.ln: $S/dev/usb/usb_core.c
	${NORMAL_LINT}

usb_core.o: $S/dev/usb/usb_core.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_debug.ln: $S/dev/usb/usb_debug.c
	${NORMAL_LINT}

usb_debug.o: $S/dev/usb/usb_debug.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_dev.ln: $S/dev/usb/usb_dev.c
	${NORMAL_LINT}

usb_dev.o: $S/dev/usb/usb_dev.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_device.ln: $S/dev/usb/usb_device.c
	${NORMAL_LINT}

usb_device.o: $S/dev/usb/usb_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_dynamic.ln: $S/dev/usb/usb_dynamic.c
	${NORMAL_LINT}

usb_dynamic.o: $S/dev/usb/usb_dynamic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_error.ln: $S/dev/usb/usb_error.c
	${NORMAL_LINT}

usb_error.o: $S/dev/usb/usb_error.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_generic.ln: $S/dev/usb/usb_generic.c
	${NORMAL_LINT}

usb_generic.o: $S/dev/usb/usb_generic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_handle_request.ln: $S/dev/usb/usb_handle_request.c
	${NORMAL_LINT}

usb_handle_request.o: $S/dev/usb/usb_handle_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_hid.ln: $S/dev/usb/usb_hid.c
	${NORMAL_LINT}

usb_hid.o: $S/dev/usb/usb_hid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_hub.ln: $S/dev/usb/usb_hub.c
	${NORMAL_LINT}

usb_hub.o: $S/dev/usb/usb_hub.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_if.ln: $S/dev/usb/usb_if.m
	${NORMAL_LINT}

usb_if.o: $S/dev/usb/usb_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

usb_lookup.ln: $S/dev/usb/usb_lookup.c
	${NORMAL_LINT}

usb_lookup.o: $S/dev/usb/usb_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_mbuf.ln: $S/dev/usb/usb_mbuf.c
	${NORMAL_LINT}

usb_mbuf.o: $S/dev/usb/usb_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_msctest.ln: $S/dev/usb/usb_msctest.c
	${NORMAL_LINT}

usb_msctest.o: $S/dev/usb/usb_msctest.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_parse.ln: $S/dev/usb/usb_parse.c
	${NORMAL_LINT}

usb_parse.o: $S/dev/usb/usb_parse.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_pf.ln: $S/dev/usb/usb_pf.c
	${NORMAL_LINT}

usb_pf.o: $S/dev/usb/usb_pf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_process.ln: $S/dev/usb/usb_process.c
	${NORMAL_LINT}

usb_process.o: $S/dev/usb/usb_process.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_request.ln: $S/dev/usb/usb_request.c
	${NORMAL_LINT}

usb_request.o: $S/dev/usb/usb_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_transfer.ln: $S/dev/usb/usb_transfer.c
	${NORMAL_LINT}

usb_transfer.o: $S/dev/usb/usb_transfer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_util.ln: $S/dev/usb/usb_util.c
	${NORMAL_LINT}

usb_util.o: $S/dev/usb/usb_util.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_aue.ln: $S/dev/usb/net/if_aue.c
	${NORMAL_LINT}

if_aue.o: $S/dev/usb/net/if_aue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_axe.ln: $S/dev/usb/net/if_axe.c
	${NORMAL_LINT}

if_axe.o: $S/dev/usb/net/if_axe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_cdce.ln: $S/dev/usb/net/if_cdce.c
	${NORMAL_LINT}

if_cdce.o: $S/dev/usb/net/if_cdce.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_cue.ln: $S/dev/usb/net/if_cue.c
	${NORMAL_LINT}

if_cue.o: $S/dev/usb/net/if_cue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_kue.ln: $S/dev/usb/net/if_kue.c
	${NORMAL_LINT}

if_kue.o: $S/dev/usb/net/if_kue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_rue.ln: $S/dev/usb/net/if_rue.c
	${NORMAL_LINT}

if_rue.o: $S/dev/usb/net/if_rue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_udav.ln: $S/dev/usb/net/if_udav.c
	${NORMAL_LINT}

if_udav.o: $S/dev/usb/net/if_udav.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ruephy.ln: $S/dev/usb/net/ruephy.c
	${NORMAL_LINT}

ruephy.o: $S/dev/usb/net/ruephy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_ethernet.ln: $S/dev/usb/net/usb_ethernet.c
	${NORMAL_LINT}

usb_ethernet.o: $S/dev/usb/net/usb_ethernet.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_rum.ln: $S/dev/usb/wlan/if_rum.c
	${NORMAL_LINT}

if_rum.o: $S/dev/usb/wlan/if_rum.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_run.ln: $S/dev/usb/wlan/if_run.c
	${NORMAL_LINT}

if_run.o: $S/dev/usb/wlan/if_run.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_uath.ln: $S/dev/usb/wlan/if_uath.c
	${NORMAL_LINT}

if_uath.o: $S/dev/usb/wlan/if_uath.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_upgt.ln: $S/dev/usb/wlan/if_upgt.c
	${NORMAL_LINT}

if_upgt.o: $S/dev/usb/wlan/if_upgt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ural.ln: $S/dev/usb/wlan/if_ural.c
	${NORMAL_LINT}

if_ural.o: $S/dev/usb/wlan/if_ural.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_urtw.ln: $S/dev/usb/wlan/if_urtw.c
	${NORMAL_LINT}

if_urtw.o: $S/dev/usb/wlan/if_urtw.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_zyd.ln: $S/dev/usb/wlan/if_zyd.c
	${NORMAL_LINT}

if_zyd.o: $S/dev/usb/wlan/if_zyd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

u3g.ln: $S/dev/usb/serial/u3g.c
	${NORMAL_LINT}

u3g.o: $S/dev/usb/serial/u3g.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uark.ln: $S/dev/usb/serial/uark.c
	${NORMAL_LINT}

uark.o: $S/dev/usb/serial/uark.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ubsa.ln: $S/dev/usb/serial/ubsa.c
	${NORMAL_LINT}

ubsa.o: $S/dev/usb/serial/ubsa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uftdi.ln: $S/dev/usb/serial/uftdi.c
	${NORMAL_LINT}

uftdi.o: $S/dev/usb/serial/uftdi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipaq.ln: $S/dev/usb/serial/uipaq.c
	${NORMAL_LINT}

uipaq.o: $S/dev/usb/serial/uipaq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ulpt.ln: $S/dev/usb/serial/ulpt.c
	${NORMAL_LINT}

ulpt.o: $S/dev/usb/serial/ulpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uplcom.ln: $S/dev/usb/serial/uplcom.c
	${NORMAL_LINT}

uplcom.o: $S/dev/usb/serial/uplcom.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uslcom.ln: $S/dev/usb/serial/uslcom.c
	${NORMAL_LINT}

uslcom.o: $S/dev/usb/serial/uslcom.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uvisor.ln: $S/dev/usb/serial/uvisor.c
	${NORMAL_LINT}

uvisor.o: $S/dev/usb/serial/uvisor.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uvscom.ln: $S/dev/usb/serial/uvscom.c
	${NORMAL_LINT}

uvscom.o: $S/dev/usb/serial/uvscom.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_serial.ln: $S/dev/usb/serial/usb_serial.c
	${NORMAL_LINT}

usb_serial.o: $S/dev/usb/serial/usb_serial.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uhid.ln: $S/dev/usb/input/uhid.c
	${NORMAL_LINT}

uhid.o: $S/dev/usb/input/uhid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ukbd.ln: $S/dev/usb/input/ukbd.c
	${NORMAL_LINT}

ukbd.o: $S/dev/usb/input/ukbd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ums.ln: $S/dev/usb/input/ums.c
	${NORMAL_LINT}

ums.o: $S/dev/usb/input/ums.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

usb_quirk.ln: $S/dev/usb/quirk/usb_quirk.c
	${NORMAL_LINT}

usb_quirk.o: $S/dev/usb/quirk/usb_quirk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_vge.ln: $S/dev/vge/if_vge.c
	${NORMAL_LINT}

if_vge.o: $S/dev/vge/if_vge.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_vr.ln: $S/dev/vr/if_vr.c
	${NORMAL_LINT}

if_vr.o: $S/dev/vr/if_vr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_vx.ln: $S/dev/vx/if_vx.c
	${NORMAL_LINT}

if_vx.o: $S/dev/vx/if_vx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_vx_pci.ln: $S/dev/vx/if_vx_pci.c
	${NORMAL_LINT}

if_vx_pci.o: $S/dev/vx/if_vx_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

watchdog.ln: $S/dev/watchdog/watchdog.c
	${NORMAL_LINT}

watchdog.o: $S/dev/watchdog/watchdog.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_wb.ln: $S/dev/wb/if_wb.c
	${NORMAL_LINT}

if_wb.o: $S/dev/wb/if_wb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_wi.ln: $S/dev/wi/if_wi.c
	${NORMAL_LINT}

if_wi.o: $S/dev/wi/if_wi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_wi_pccard.ln: $S/dev/wi/if_wi_pccard.c
	${NORMAL_LINT}

if_wi_pccard.o: $S/dev/wi/if_wi_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_wi_pci.ln: $S/dev/wi/if_wi_pci.c
	${NORMAL_LINT}

if_wi_pci.o: $S/dev/wi/if_wi_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_wpi.ln: $S/dev/wpi/if_wpi.c
	${NORMAL_LINT}

if_wpi.o: $S/dev/wpi/if_wpi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_xe.ln: $S/dev/xe/if_xe.c
	${NORMAL_LINT}

if_xe.o: $S/dev/xe/if_xe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_xe_pccard.ln: $S/dev/xe/if_xe_pccard.c
	${NORMAL_LINT}

if_xe_pccard.o: $S/dev/xe/if_xe_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_xl.ln: $S/dev/xl/if_xl.c
	${NORMAL_LINT}

if_xl.o: $S/dev/xl/if_xl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xlphy.ln: $S/dev/xl/xlphy.c
	${NORMAL_LINT}

xlphy.o: $S/dev/xl/xlphy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dead_vnops.ln: $S/fs/deadfs/dead_vnops.c
	${NORMAL_LINT}

dead_vnops.o: $S/fs/deadfs/dead_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_devs.ln: $S/fs/devfs/devfs_devs.c
	${NORMAL_LINT}

devfs_devs.o: $S/fs/devfs/devfs_devs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_dir.ln: $S/fs/devfs/devfs_dir.c
	${NORMAL_LINT}

devfs_dir.o: $S/fs/devfs/devfs_dir.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_rule.ln: $S/fs/devfs/devfs_rule.c
	${NORMAL_LINT}

devfs_rule.o: $S/fs/devfs/devfs_rule.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_vfsops.ln: $S/fs/devfs/devfs_vfsops.c
	${NORMAL_LINT}

devfs_vfsops.o: $S/fs/devfs/devfs_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

devfs_vnops.ln: $S/fs/devfs/devfs_vnops.c
	${NORMAL_LINT}

devfs_vnops.o: $S/fs/devfs/devfs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fifo_vnops.ln: $S/fs/fifofs/fifo_vnops.c
	${NORMAL_LINT}

fifo_vnops.o: $S/fs/fifofs/fifo_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_conv.ln: $S/fs/msdosfs/msdosfs_conv.c
	${NORMAL_LINT}

msdosfs_conv.o: $S/fs/msdosfs/msdosfs_conv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_denode.ln: $S/fs/msdosfs/msdosfs_denode.c
	${NORMAL_LINT}

msdosfs_denode.o: $S/fs/msdosfs/msdosfs_denode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_fat.ln: $S/fs/msdosfs/msdosfs_fat.c
	${NORMAL_LINT}

msdosfs_fat.o: $S/fs/msdosfs/msdosfs_fat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_fileno.ln: $S/fs/msdosfs/msdosfs_fileno.c
	${NORMAL_LINT}

msdosfs_fileno.o: $S/fs/msdosfs/msdosfs_fileno.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_lookup.ln: $S/fs/msdosfs/msdosfs_lookup.c
	${NORMAL_LINT}

msdosfs_lookup.o: $S/fs/msdosfs/msdosfs_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_vfsops.ln: $S/fs/msdosfs/msdosfs_vfsops.c
	${NORMAL_LINT}

msdosfs_vfsops.o: $S/fs/msdosfs/msdosfs_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msdosfs_vnops.ln: $S/fs/msdosfs/msdosfs_vnops.c
	${NORMAL_LINT}

msdosfs_vnops.o: $S/fs/msdosfs/msdosfs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_commonkrpc.ln: $S/fs/nfs/nfs_commonkrpc.c
	${NORMAL_LINT}

nfs_commonkrpc.o: $S/fs/nfs/nfs_commonkrpc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_commonsubs.ln: $S/fs/nfs/nfs_commonsubs.c
	${NORMAL_LINT}

nfs_commonsubs.o: $S/fs/nfs/nfs_commonsubs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_commonport.ln: $S/fs/nfs/nfs_commonport.c
	${NORMAL_LINT}

nfs_commonport.o: $S/fs/nfs/nfs_commonport.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_commonacl.ln: $S/fs/nfs/nfs_commonacl.c
	${NORMAL_LINT}

nfs_commonacl.o: $S/fs/nfs/nfs_commonacl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clcomsubs.ln: $S/fs/nfsclient/nfs_clcomsubs.c
	${NORMAL_LINT}

nfs_clcomsubs.o: $S/fs/nfsclient/nfs_clcomsubs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clsubs.ln: $S/fs/nfsclient/nfs_clsubs.c
	${NORMAL_LINT}

nfs_clsubs.o: $S/fs/nfsclient/nfs_clsubs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clstate.ln: $S/fs/nfsclient/nfs_clstate.c
	${NORMAL_LINT}

nfs_clstate.o: $S/fs/nfsclient/nfs_clstate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clkrpc.ln: $S/fs/nfsclient/nfs_clkrpc.c
	${NORMAL_LINT}

nfs_clkrpc.o: $S/fs/nfsclient/nfs_clkrpc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clrpcops.ln: $S/fs/nfsclient/nfs_clrpcops.c
	${NORMAL_LINT}

nfs_clrpcops.o: $S/fs/nfsclient/nfs_clrpcops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clvnops.ln: $S/fs/nfsclient/nfs_clvnops.c
	${NORMAL_LINT}

nfs_clvnops.o: $S/fs/nfsclient/nfs_clvnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clnode.ln: $S/fs/nfsclient/nfs_clnode.c
	${NORMAL_LINT}

nfs_clnode.o: $S/fs/nfsclient/nfs_clnode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clvfsops.ln: $S/fs/nfsclient/nfs_clvfsops.c
	${NORMAL_LINT}

nfs_clvfsops.o: $S/fs/nfsclient/nfs_clvfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clport.ln: $S/fs/nfsclient/nfs_clport.c
	${NORMAL_LINT}

nfs_clport.o: $S/fs/nfsclient/nfs_clport.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clbio.ln: $S/fs/nfsclient/nfs_clbio.c
	${NORMAL_LINT}

nfs_clbio.o: $S/fs/nfsclient/nfs_clbio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_clnfsiod.ln: $S/fs/nfsclient/nfs_clnfsiod.c
	${NORMAL_LINT}

nfs_clnfsiod.o: $S/fs/nfsclient/nfs_clnfsiod.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_fha_new.ln: $S/fs/nfsserver/nfs_fha_new.c
	${NORMAL_LINT}

nfs_fha_new.o: $S/fs/nfsserver/nfs_fha_new.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdsocket.ln: $S/fs/nfsserver/nfs_nfsdsocket.c
	${NORMAL_LINT}

nfs_nfsdsocket.o: $S/fs/nfsserver/nfs_nfsdsocket.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdsubs.ln: $S/fs/nfsserver/nfs_nfsdsubs.c
	${NORMAL_LINT}

nfs_nfsdsubs.o: $S/fs/nfsserver/nfs_nfsdsubs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdstate.ln: $S/fs/nfsserver/nfs_nfsdstate.c
	${NORMAL_LINT}

nfs_nfsdstate.o: $S/fs/nfsserver/nfs_nfsdstate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdkrpc.ln: $S/fs/nfsserver/nfs_nfsdkrpc.c
	${NORMAL_LINT}

nfs_nfsdkrpc.o: $S/fs/nfsserver/nfs_nfsdkrpc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdserv.ln: $S/fs/nfsserver/nfs_nfsdserv.c
	${NORMAL_LINT}

nfs_nfsdserv.o: $S/fs/nfsserver/nfs_nfsdserv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdport.ln: $S/fs/nfsserver/nfs_nfsdport.c
	${NORMAL_LINT}

nfs_nfsdport.o: $S/fs/nfsserver/nfs_nfsdport.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfsdcache.ln: $S/fs/nfsserver/nfs_nfsdcache.c
	${NORMAL_LINT}

nfs_nfsdcache.o: $S/fs/nfsserver/nfs_nfsdcache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs.ln: $S/fs/procfs/procfs.c
	${NORMAL_LINT}

procfs.o: $S/fs/procfs/procfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_ctl.ln: $S/fs/procfs/procfs_ctl.c
	${NORMAL_LINT}

procfs_ctl.o: $S/fs/procfs/procfs_ctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_dbregs.ln: $S/fs/procfs/procfs_dbregs.c
	${NORMAL_LINT}

procfs_dbregs.o: $S/fs/procfs/procfs_dbregs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_fpregs.ln: $S/fs/procfs/procfs_fpregs.c
	${NORMAL_LINT}

procfs_fpregs.o: $S/fs/procfs/procfs_fpregs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_ioctl.ln: $S/fs/procfs/procfs_ioctl.c
	${NORMAL_LINT}

procfs_ioctl.o: $S/fs/procfs/procfs_ioctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_map.ln: $S/fs/procfs/procfs_map.c
	${NORMAL_LINT}

procfs_map.o: $S/fs/procfs/procfs_map.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_mem.ln: $S/fs/procfs/procfs_mem.c
	${NORMAL_LINT}

procfs_mem.o: $S/fs/procfs/procfs_mem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_note.ln: $S/fs/procfs/procfs_note.c
	${NORMAL_LINT}

procfs_note.o: $S/fs/procfs/procfs_note.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_osrel.ln: $S/fs/procfs/procfs_osrel.c
	${NORMAL_LINT}

procfs_osrel.o: $S/fs/procfs/procfs_osrel.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_regs.ln: $S/fs/procfs/procfs_regs.c
	${NORMAL_LINT}

procfs_regs.o: $S/fs/procfs/procfs_regs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_rlimit.ln: $S/fs/procfs/procfs_rlimit.c
	${NORMAL_LINT}

procfs_rlimit.o: $S/fs/procfs/procfs_rlimit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_status.ln: $S/fs/procfs/procfs_status.c
	${NORMAL_LINT}

procfs_status.o: $S/fs/procfs/procfs_status.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

procfs_type.ln: $S/fs/procfs/procfs_type.c
	${NORMAL_LINT}

procfs_type.o: $S/fs/procfs/procfs_type.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pseudofs.ln: $S/fs/pseudofs/pseudofs.c
	${NORMAL_LINT}

pseudofs.o: $S/fs/pseudofs/pseudofs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pseudofs_fileno.ln: $S/fs/pseudofs/pseudofs_fileno.c
	${NORMAL_LINT}

pseudofs_fileno.o: $S/fs/pseudofs/pseudofs_fileno.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pseudofs_vncache.ln: $S/fs/pseudofs/pseudofs_vncache.c
	${NORMAL_LINT}

pseudofs_vncache.o: $S/fs/pseudofs/pseudofs_vncache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pseudofs_vnops.ln: $S/fs/pseudofs/pseudofs_vnops.c
	${NORMAL_LINT}

pseudofs_vnops.o: $S/fs/pseudofs/pseudofs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_ctl.ln: $S/geom/geom_ctl.c
	${NORMAL_LINT}

geom_ctl.o: $S/geom/geom_ctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_dev.ln: $S/geom/geom_dev.c
	${NORMAL_LINT}

geom_dev.o: $S/geom/geom_dev.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_disk.ln: $S/geom/geom_disk.c
	${NORMAL_LINT}

geom_disk.o: $S/geom/geom_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_dump.ln: $S/geom/geom_dump.c
	${NORMAL_LINT}

geom_dump.o: $S/geom/geom_dump.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_event.ln: $S/geom/geom_event.c
	${NORMAL_LINT}

geom_event.o: $S/geom/geom_event.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_io.ln: $S/geom/geom_io.c
	${NORMAL_LINT}

geom_io.o: $S/geom/geom_io.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_kern.ln: $S/geom/geom_kern.c
	${NORMAL_LINT}

geom_kern.o: $S/geom/geom_kern.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_slice.ln: $S/geom/geom_slice.c
	${NORMAL_LINT}

geom_slice.o: $S/geom/geom_slice.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_subr.ln: $S/geom/geom_subr.c
	${NORMAL_LINT}

geom_subr.o: $S/geom/geom_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

geom_vfs.ln: $S/geom/geom_vfs.c
	${NORMAL_LINT}

geom_vfs.o: $S/geom/geom_vfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label.ln: $S/geom/label/g_label.c
	${NORMAL_LINT}

g_label.o: $S/geom/label/g_label.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_ext2fs.ln: $S/geom/label/g_label_ext2fs.c
	${NORMAL_LINT}

g_label_ext2fs.o: $S/geom/label/g_label_ext2fs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_iso9660.ln: $S/geom/label/g_label_iso9660.c
	${NORMAL_LINT}

g_label_iso9660.o: $S/geom/label/g_label_iso9660.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_msdosfs.ln: $S/geom/label/g_label_msdosfs.c
	${NORMAL_LINT}

g_label_msdosfs.o: $S/geom/label/g_label_msdosfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_ntfs.ln: $S/geom/label/g_label_ntfs.c
	${NORMAL_LINT}

g_label_ntfs.o: $S/geom/label/g_label_ntfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_reiserfs.ln: $S/geom/label/g_label_reiserfs.c
	${NORMAL_LINT}

g_label_reiserfs.o: $S/geom/label/g_label_reiserfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_ufs.ln: $S/geom/label/g_label_ufs.c
	${NORMAL_LINT}

g_label_ufs.o: $S/geom/label/g_label_ufs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_label_gpt.ln: $S/geom/label/g_label_gpt.c
	${NORMAL_LINT}

g_label_gpt.o: $S/geom/label/g_label_gpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part.ln: $S/geom/part/g_part.c
	${NORMAL_LINT}

g_part.o: $S/geom/part/g_part.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part_if.ln: $S/geom/part/g_part_if.m
	${NORMAL_LINT}

g_part_if.o: $S/geom/part/g_part_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

g_part_bsd.ln: $S/geom/part/g_part_bsd.c
	${NORMAL_LINT}

g_part_bsd.o: $S/geom/part/g_part_bsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part_ebr.ln: $S/geom/part/g_part_ebr.c
	${NORMAL_LINT}

g_part_ebr.o: $S/geom/part/g_part_ebr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part_gpt.ln: $S/geom/part/g_part_gpt.c
	${NORMAL_LINT}

g_part_gpt.o: $S/geom/part/g_part_gpt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_part_mbr.ln: $S/geom/part/g_part_mbr.c
	${NORMAL_LINT}

g_part_mbr.o: $S/geom/part/g_part_mbr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_raid.ln: $S/geom/raid/g_raid.c
	${NORMAL_LINT}

g_raid.o: $S/geom/raid/g_raid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_raid_ctl.ln: $S/geom/raid/g_raid_ctl.c
	${NORMAL_LINT}

g_raid_ctl.o: $S/geom/raid/g_raid_ctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

g_raid_md_if.ln: $S/geom/raid/g_raid_md_if.m
	${NORMAL_LINT}

g_raid_md_if.o: $S/geom/raid/g_raid_md_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

g_raid_tr_if.ln: $S/geom/raid/g_raid_tr_if.m
	${NORMAL_LINT}

g_raid_tr_if.o: $S/geom/raid/g_raid_tr_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

md_ddf.ln: $S/geom/raid/md_ddf.c
	${NORMAL_LINT}

md_ddf.o: $S/geom/raid/md_ddf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_intel.ln: $S/geom/raid/md_intel.c
	${NORMAL_LINT}

md_intel.o: $S/geom/raid/md_intel.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_jmicron.ln: $S/geom/raid/md_jmicron.c
	${NORMAL_LINT}

md_jmicron.o: $S/geom/raid/md_jmicron.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_nvidia.ln: $S/geom/raid/md_nvidia.c
	${NORMAL_LINT}

md_nvidia.o: $S/geom/raid/md_nvidia.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_promise.ln: $S/geom/raid/md_promise.c
	${NORMAL_LINT}

md_promise.o: $S/geom/raid/md_promise.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

md_sii.ln: $S/geom/raid/md_sii.c
	${NORMAL_LINT}

md_sii.o: $S/geom/raid/md_sii.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_concat.ln: $S/geom/raid/tr_concat.c
	${NORMAL_LINT}

tr_concat.o: $S/geom/raid/tr_concat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_raid0.ln: $S/geom/raid/tr_raid0.c
	${NORMAL_LINT}

tr_raid0.o: $S/geom/raid/tr_raid0.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_raid1.ln: $S/geom/raid/tr_raid1.c
	${NORMAL_LINT}

tr_raid1.o: $S/geom/raid/tr_raid1.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_raid1e.ln: $S/geom/raid/tr_raid1e.c
	${NORMAL_LINT}

tr_raid1e.o: $S/geom/raid/tr_raid1e.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tr_raid5.ln: $S/geom/raid/tr_raid5.c
	${NORMAL_LINT}

tr_raid5.o: $S/geom/raid/tr_raid5.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isa_if.ln: $S/isa/isa_if.m
	${NORMAL_LINT}

isa_if.o: $S/isa/isa_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

isa_common.ln: $S/isa/isa_common.c
	${NORMAL_LINT}

isa_common.o: $S/isa/isa_common.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isahint.ln: $S/isa/isahint.c
	${NORMAL_LINT}

isahint.o: $S/isa/isahint.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_bmap.ln: $S/fs/cd9660/cd9660_bmap.c
	${NORMAL_LINT}

cd9660_bmap.o: $S/fs/cd9660/cd9660_bmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_lookup.ln: $S/fs/cd9660/cd9660_lookup.c
	${NORMAL_LINT}

cd9660_lookup.o: $S/fs/cd9660/cd9660_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_node.ln: $S/fs/cd9660/cd9660_node.c
	${NORMAL_LINT}

cd9660_node.o: $S/fs/cd9660/cd9660_node.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_rrip.ln: $S/fs/cd9660/cd9660_rrip.c
	${NORMAL_LINT}

cd9660_rrip.o: $S/fs/cd9660/cd9660_rrip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_util.ln: $S/fs/cd9660/cd9660_util.c
	${NORMAL_LINT}

cd9660_util.o: $S/fs/cd9660/cd9660_util.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_vfsops.ln: $S/fs/cd9660/cd9660_vfsops.c
	${NORMAL_LINT}

cd9660_vfsops.o: $S/fs/cd9660/cd9660_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cd9660_vnops.ln: $S/fs/cd9660/cd9660_vnops.c
	${NORMAL_LINT}

cd9660_vnops.o: $S/fs/cd9660/cd9660_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bus_if.ln: $S/kern/bus_if.m
	${NORMAL_LINT}

bus_if.o: $S/kern/bus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

clock_if.ln: $S/kern/clock_if.m
	${NORMAL_LINT}

clock_if.o: $S/kern/clock_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

cpufreq_if.ln: $S/kern/cpufreq_if.m
	${NORMAL_LINT}

cpufreq_if.o: $S/kern/cpufreq_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

device_if.ln: $S/kern/device_if.m
	${NORMAL_LINT}

device_if.o: $S/kern/device_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

imgact_elf.ln: $S/kern/imgact_elf.c
	${NORMAL_LINT}

imgact_elf.o: $S/kern/imgact_elf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

imgact_shell.ln: $S/kern/imgact_shell.c
	${NORMAL_LINT}

imgact_shell.o: $S/kern/imgact_shell.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

init_main.ln: $S/kern/init_main.c
	${NORMAL_LINT}

init_main.o: $S/kern/init_main.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

init_sysent.ln: $S/kern/init_sysent.c
	${NORMAL_LINT}

init_sysent.o: $S/kern/init_sysent.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ksched.ln: $S/kern/ksched.c
	${NORMAL_LINT}

ksched.o: $S/kern/ksched.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_acct.ln: $S/kern/kern_acct.c
	${NORMAL_LINT}

kern_acct.o: $S/kern/kern_acct.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_clock.ln: $S/kern/kern_clock.c
	${NORMAL_LINT}

kern_clock.o: $S/kern/kern_clock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_condvar.ln: $S/kern/kern_condvar.c
	${NORMAL_LINT}

kern_condvar.o: $S/kern/kern_condvar.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_conf.ln: $S/kern/kern_conf.c
	${NORMAL_LINT}

kern_conf.o: $S/kern/kern_conf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_cons.ln: $S/kern/kern_cons.c
	${NORMAL_LINT}

kern_cons.o: $S/kern/kern_cons.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_cpu.ln: $S/kern/kern_cpu.c
	${NORMAL_LINT}

kern_cpu.o: $S/kern/kern_cpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_cpuset.ln: $S/kern/kern_cpuset.c
	${NORMAL_LINT}

kern_cpuset.o: $S/kern/kern_cpuset.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_context.ln: $S/kern/kern_context.c
	${NORMAL_LINT}

kern_context.o: $S/kern/kern_context.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_descrip.ln: $S/kern/kern_descrip.c
	${NORMAL_LINT}

kern_descrip.o: $S/kern/kern_descrip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_dtrace.ln: $S/kern/kern_dtrace.c
	${NORMAL_LINT}

kern_dtrace.o: $S/kern/kern_dtrace.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_environment.ln: $S/kern/kern_environment.c
	${NORMAL_LINT}

kern_environment.o: $S/kern/kern_environment.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_et.ln: $S/kern/kern_et.c
	${NORMAL_LINT}

kern_et.o: $S/kern/kern_et.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_event.ln: $S/kern/kern_event.c
	${NORMAL_LINT}

kern_event.o: $S/kern/kern_event.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_exec.ln: $S/kern/kern_exec.c
	${NORMAL_LINT}

kern_exec.o: $S/kern/kern_exec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_exit.ln: $S/kern/kern_exit.c
	${NORMAL_LINT}

kern_exit.o: $S/kern/kern_exit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_fail.ln: $S/kern/kern_fail.c
	${NORMAL_LINT}

kern_fail.o: $S/kern/kern_fail.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_fork.ln: $S/kern/kern_fork.c
	${NORMAL_LINT}

kern_fork.o: $S/kern/kern_fork.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_hhook.ln: $S/kern/kern_hhook.c
	${NORMAL_LINT}

kern_hhook.o: $S/kern/kern_hhook.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_idle.ln: $S/kern/kern_idle.c
	${NORMAL_LINT}

kern_idle.o: $S/kern/kern_idle.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_intr.ln: $S/kern/kern_intr.c
	${NORMAL_LINT}

kern_intr.o: $S/kern/kern_intr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_jail.ln: $S/kern/kern_jail.c
	${NORMAL_LINT}

kern_jail.o: $S/kern/kern_jail.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_khelp.ln: $S/kern/kern_khelp.c
	${NORMAL_LINT}

kern_khelp.o: $S/kern/kern_khelp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_kthread.ln: $S/kern/kern_kthread.c
	${NORMAL_LINT}

kern_kthread.o: $S/kern/kern_kthread.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_ktrace.ln: $S/kern/kern_ktrace.c
	${NORMAL_LINT}

kern_ktrace.o: $S/kern/kern_ktrace.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_linker.ln: $S/kern/kern_linker.c
	${NORMAL_LINT}

kern_linker.o: $S/kern/kern_linker.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_lock.ln: $S/kern/kern_lock.c
	${NORMAL_LINT}

kern_lock.o: $S/kern/kern_lock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_lockf.ln: $S/kern/kern_lockf.c
	${NORMAL_LINT}

kern_lockf.o: $S/kern/kern_lockf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_lockstat.ln: $S/kern/kern_lockstat.c
	${NORMAL_LINT}

kern_lockstat.o: $S/kern/kern_lockstat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_loginclass.ln: $S/kern/kern_loginclass.c
	${NORMAL_LINT}

kern_loginclass.o: $S/kern/kern_loginclass.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_malloc.ln: $S/kern/kern_malloc.c
	${NORMAL_LINT}

kern_malloc.o: $S/kern/kern_malloc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_mbuf.ln: $S/kern/kern_mbuf.c
	${NORMAL_LINT}

kern_mbuf.o: $S/kern/kern_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_mib.ln: $S/kern/kern_mib.c
	${NORMAL_LINT}

kern_mib.o: $S/kern/kern_mib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_module.ln: $S/kern/kern_module.c
	${NORMAL_LINT}

kern_module.o: $S/kern/kern_module.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_mtxpool.ln: $S/kern/kern_mtxpool.c
	${NORMAL_LINT}

kern_mtxpool.o: $S/kern/kern_mtxpool.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_mutex.ln: $S/kern/kern_mutex.c
	${NORMAL_LINT}

kern_mutex.o: $S/kern/kern_mutex.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_ntptime.ln: $S/kern/kern_ntptime.c
	${NORMAL_LINT}

kern_ntptime.o: $S/kern/kern_ntptime.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_osd.ln: $S/kern/kern_osd.c
	${NORMAL_LINT}

kern_osd.o: $S/kern/kern_osd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_physio.ln: $S/kern/kern_physio.c
	${NORMAL_LINT}

kern_physio.o: $S/kern/kern_physio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_pmc.ln: $S/kern/kern_pmc.c
	${NORMAL_LINT}

kern_pmc.o: $S/kern/kern_pmc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_priv.ln: $S/kern/kern_priv.c
	${NORMAL_LINT}

kern_priv.o: $S/kern/kern_priv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_proc.ln: $S/kern/kern_proc.c
	${NORMAL_LINT}

kern_proc.o: $S/kern/kern_proc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_prot.ln: $S/kern/kern_prot.c
	${NORMAL_LINT}

kern_prot.o: $S/kern/kern_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_racct.ln: $S/kern/kern_racct.c
	${NORMAL_LINT}

kern_racct.o: $S/kern/kern_racct.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_rangelock.ln: $S/kern/kern_rangelock.c
	${NORMAL_LINT}

kern_rangelock.o: $S/kern/kern_rangelock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_rctl.ln: $S/kern/kern_rctl.c
	${NORMAL_LINT}

kern_rctl.o: $S/kern/kern_rctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_resource.ln: $S/kern/kern_resource.c
	${NORMAL_LINT}

kern_resource.o: $S/kern/kern_resource.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_rmlock.ln: $S/kern/kern_rmlock.c
	${NORMAL_LINT}

kern_rmlock.o: $S/kern/kern_rmlock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_rwlock.ln: $S/kern/kern_rwlock.c
	${NORMAL_LINT}

kern_rwlock.o: $S/kern/kern_rwlock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sdt.ln: $S/kern/kern_sdt.c
	${NORMAL_LINT}

kern_sdt.o: $S/kern/kern_sdt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sema.ln: $S/kern/kern_sema.c
	${NORMAL_LINT}

kern_sema.o: $S/kern/kern_sema.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sharedpage.ln: $S/kern/kern_sharedpage.c
	${NORMAL_LINT}

kern_sharedpage.o: $S/kern/kern_sharedpage.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_shutdown.ln: $S/kern/kern_shutdown.c
	${NORMAL_LINT}

kern_shutdown.o: $S/kern/kern_shutdown.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sig.ln: $S/kern/kern_sig.c
	${NORMAL_LINT}

kern_sig.o: $S/kern/kern_sig.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_switch.ln: $S/kern/kern_switch.c
	${NORMAL_LINT}

kern_switch.o: $S/kern/kern_switch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sx.ln: $S/kern/kern_sx.c
	${NORMAL_LINT}

kern_sx.o: $S/kern/kern_sx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_synch.ln: $S/kern/kern_synch.c
	${NORMAL_LINT}

kern_synch.o: $S/kern/kern_synch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_syscalls.ln: $S/kern/kern_syscalls.c
	${NORMAL_LINT}

kern_syscalls.o: $S/kern/kern_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_sysctl.ln: $S/kern/kern_sysctl.c
	${NORMAL_LINT}

kern_sysctl.o: $S/kern/kern_sysctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_tc.ln: $S/kern/kern_tc.c
	${NORMAL_LINT}

kern_tc.o: $S/kern/kern_tc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_thr.ln: $S/kern/kern_thr.c
	${NORMAL_LINT}

kern_thr.o: $S/kern/kern_thr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_thread.ln: $S/kern/kern_thread.c
	${NORMAL_LINT}

kern_thread.o: $S/kern/kern_thread.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_time.ln: $S/kern/kern_time.c
	${NORMAL_LINT}

kern_time.o: $S/kern/kern_time.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_timeout.ln: $S/kern/kern_timeout.c
	${NORMAL_LINT}

kern_timeout.o: $S/kern/kern_timeout.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_umtx.ln: $S/kern/kern_umtx.c
	${NORMAL_LINT}

kern_umtx.o: $S/kern/kern_umtx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_uuid.ln: $S/kern/kern_uuid.c
	${NORMAL_LINT}

kern_uuid.o: $S/kern/kern_uuid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_xxx.ln: $S/kern/kern_xxx.c
	${NORMAL_LINT}

kern_xxx.o: $S/kern/kern_xxx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

link_elf.ln: $S/kern/link_elf.c
	${NORMAL_LINT}

link_elf.o: $S/kern/link_elf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

linker_if.ln: $S/kern/linker_if.m
	${NORMAL_LINT}

linker_if.o: $S/kern/linker_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

md5c.ln: $S/kern/md5c.c
	${NORMAL_LINT}

md5c.o: $S/kern/md5c.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

p1003_1b.ln: $S/kern/p1003_1b.c
	${NORMAL_LINT}

p1003_1b.o: $S/kern/p1003_1b.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

posix4_mib.ln: $S/kern/posix4_mib.c
	${NORMAL_LINT}

posix4_mib.o: $S/kern/posix4_mib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sched_ule.ln: $S/kern/sched_ule.c
	${NORMAL_LINT}

sched_ule.o: $S/kern/sched_ule.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

serdev_if.ln: $S/kern/serdev_if.m
	${NORMAL_LINT}

serdev_if.o: $S/kern/serdev_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

stack_protector.ln: $S/kern/stack_protector.c
	${NORMAL_LINT}

stack_protector.o: $S/kern/stack_protector.c
	${NORMAL_C:N-fstack-protector*}
	${NORMAL_CTFCONVERT}

subr_acl_nfs4.ln: $S/kern/subr_acl_nfs4.c
	${NORMAL_LINT}

subr_acl_nfs4.o: $S/kern/subr_acl_nfs4.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_acl_posix1e.ln: $S/kern/subr_acl_posix1e.c
	${NORMAL_LINT}

subr_acl_posix1e.o: $S/kern/subr_acl_posix1e.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_autoconf.ln: $S/kern/subr_autoconf.c
	${NORMAL_LINT}

subr_autoconf.o: $S/kern/subr_autoconf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_blist.ln: $S/kern/subr_blist.c
	${NORMAL_LINT}

subr_blist.o: $S/kern/subr_blist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_bus.ln: $S/kern/subr_bus.c
	${NORMAL_LINT}

subr_bus.o: $S/kern/subr_bus.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_bus_dma.ln: $S/kern/subr_bus_dma.c
	${NORMAL_LINT}

subr_bus_dma.o: $S/kern/subr_bus_dma.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_bufring.ln: $S/kern/subr_bufring.c
	${NORMAL_LINT}

subr_bufring.o: $S/kern/subr_bufring.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_clock.ln: $S/kern/subr_clock.c
	${NORMAL_LINT}

subr_clock.o: $S/kern/subr_clock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_devstat.ln: $S/kern/subr_devstat.c
	${NORMAL_LINT}

subr_devstat.o: $S/kern/subr_devstat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_disk.ln: $S/kern/subr_disk.c
	${NORMAL_LINT}

subr_disk.o: $S/kern/subr_disk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_eventhandler.ln: $S/kern/subr_eventhandler.c
	${NORMAL_LINT}

subr_eventhandler.o: $S/kern/subr_eventhandler.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_fattime.ln: $S/kern/subr_fattime.c
	${NORMAL_LINT}

subr_fattime.o: $S/kern/subr_fattime.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_firmware.ln: $S/kern/subr_firmware.c
	${NORMAL_LINT}

subr_firmware.o: $S/kern/subr_firmware.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_hash.ln: $S/kern/subr_hash.c
	${NORMAL_LINT}

subr_hash.o: $S/kern/subr_hash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_hints.ln: $S/kern/subr_hints.c
	${NORMAL_LINT}

subr_hints.o: $S/kern/subr_hints.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_kdb.ln: $S/kern/subr_kdb.c
	${NORMAL_LINT}

subr_kdb.o: $S/kern/subr_kdb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_kobj.ln: $S/kern/subr_kobj.c
	${NORMAL_LINT}

subr_kobj.o: $S/kern/subr_kobj.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_lock.ln: $S/kern/subr_lock.c
	${NORMAL_LINT}

subr_lock.o: $S/kern/subr_lock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_log.ln: $S/kern/subr_log.c
	${NORMAL_LINT}

subr_log.o: $S/kern/subr_log.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_module.ln: $S/kern/subr_module.c
	${NORMAL_LINT}

subr_module.o: $S/kern/subr_module.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_msgbuf.ln: $S/kern/subr_msgbuf.c
	${NORMAL_LINT}

subr_msgbuf.o: $S/kern/subr_msgbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_param.ln: $S/kern/subr_param.c
	${NORMAL_LINT}

subr_param.o: $S/kern/subr_param.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_pcpu.ln: $S/kern/subr_pcpu.c
	${NORMAL_LINT}

subr_pcpu.o: $S/kern/subr_pcpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_power.ln: $S/kern/subr_power.c
	${NORMAL_LINT}

subr_power.o: $S/kern/subr_power.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_prf.ln: $S/kern/subr_prf.c
	${NORMAL_LINT}

subr_prf.o: $S/kern/subr_prf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_prof.ln: $S/kern/subr_prof.c
	${NORMAL_LINT}

subr_prof.o: $S/kern/subr_prof.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_rman.ln: $S/kern/subr_rman.c
	${NORMAL_LINT}

subr_rman.o: $S/kern/subr_rman.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_rtc.ln: $S/kern/subr_rtc.c
	${NORMAL_LINT}

subr_rtc.o: $S/kern/subr_rtc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_sbuf.ln: $S/kern/subr_sbuf.c
	${NORMAL_LINT}

subr_sbuf.o: $S/kern/subr_sbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_scanf.ln: $S/kern/subr_scanf.c
	${NORMAL_LINT}

subr_scanf.o: $S/kern/subr_scanf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_sglist.ln: $S/kern/subr_sglist.c
	${NORMAL_LINT}

subr_sglist.o: $S/kern/subr_sglist.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_sleepqueue.ln: $S/kern/subr_sleepqueue.c
	${NORMAL_LINT}

subr_sleepqueue.o: $S/kern/subr_sleepqueue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_smp.ln: $S/kern/subr_smp.c
	${NORMAL_LINT}

subr_smp.o: $S/kern/subr_smp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_stack.ln: $S/kern/subr_stack.c
	${NORMAL_LINT}

subr_stack.o: $S/kern/subr_stack.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_taskqueue.ln: $S/kern/subr_taskqueue.c
	${NORMAL_LINT}

subr_taskqueue.o: $S/kern/subr_taskqueue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_trap.ln: $S/kern/subr_trap.c
	${NORMAL_LINT}

subr_trap.o: $S/kern/subr_trap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_turnstile.ln: $S/kern/subr_turnstile.c
	${NORMAL_LINT}

subr_turnstile.o: $S/kern/subr_turnstile.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_uio.ln: $S/kern/subr_uio.c
	${NORMAL_LINT}

subr_uio.o: $S/kern/subr_uio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

subr_unit.ln: $S/kern/subr_unit.c
	${NORMAL_LINT}

subr_unit.o: $S/kern/subr_unit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_capability.ln: $S/kern/sys_capability.c
	${NORMAL_LINT}

sys_capability.o: $S/kern/sys_capability.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_generic.ln: $S/kern/sys_generic.c
	${NORMAL_LINT}

sys_generic.o: $S/kern/sys_generic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_pipe.ln: $S/kern/sys_pipe.c
	${NORMAL_LINT}

sys_pipe.o: $S/kern/sys_pipe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_procdesc.ln: $S/kern/sys_procdesc.c
	${NORMAL_LINT}

sys_procdesc.o: $S/kern/sys_procdesc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_process.ln: $S/kern/sys_process.c
	${NORMAL_LINT}

sys_process.o: $S/kern/sys_process.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sys_socket.ln: $S/kern/sys_socket.c
	${NORMAL_LINT}

sys_socket.o: $S/kern/sys_socket.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

syscalls.ln: $S/kern/syscalls.c
	${NORMAL_LINT}

syscalls.o: $S/kern/syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysv_ipc.ln: $S/kern/sysv_ipc.c
	${NORMAL_LINT}

sysv_ipc.o: $S/kern/sysv_ipc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysv_msg.ln: $S/kern/sysv_msg.c
	${NORMAL_LINT}

sysv_msg.o: $S/kern/sysv_msg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysv_sem.ln: $S/kern/sysv_sem.c
	${NORMAL_LINT}

sysv_sem.o: $S/kern/sysv_sem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sysv_shm.ln: $S/kern/sysv_shm.c
	${NORMAL_LINT}

sysv_shm.o: $S/kern/sysv_shm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty.ln: $S/kern/tty.c
	${NORMAL_LINT}

tty.o: $S/kern/tty.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_info.ln: $S/kern/tty_info.c
	${NORMAL_LINT}

tty_info.o: $S/kern/tty_info.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_inq.ln: $S/kern/tty_inq.c
	${NORMAL_LINT}

tty_inq.o: $S/kern/tty_inq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_outq.ln: $S/kern/tty_outq.c
	${NORMAL_LINT}

tty_outq.o: $S/kern/tty_outq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_pts.ln: $S/kern/tty_pts.c
	${NORMAL_LINT}

tty_pts.o: $S/kern/tty_pts.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_tty.ln: $S/kern/tty_tty.c
	${NORMAL_LINT}

tty_tty.o: $S/kern/tty_tty.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tty_ttydisc.ln: $S/kern/tty_ttydisc.c
	${NORMAL_LINT}

tty_ttydisc.o: $S/kern/tty_ttydisc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_accf.ln: $S/kern/uipc_accf.c
	${NORMAL_LINT}

uipc_accf.o: $S/kern/uipc_accf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_domain.ln: $S/kern/uipc_domain.c
	${NORMAL_LINT}

uipc_domain.o: $S/kern/uipc_domain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_mbuf.ln: $S/kern/uipc_mbuf.c
	${NORMAL_LINT}

uipc_mbuf.o: $S/kern/uipc_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_mbuf2.ln: $S/kern/uipc_mbuf2.c
	${NORMAL_LINT}

uipc_mbuf2.o: $S/kern/uipc_mbuf2.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_shm.ln: $S/kern/uipc_shm.c
	${NORMAL_LINT}

uipc_shm.o: $S/kern/uipc_shm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_sockbuf.ln: $S/kern/uipc_sockbuf.c
	${NORMAL_LINT}

uipc_sockbuf.o: $S/kern/uipc_sockbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_socket.ln: $S/kern/uipc_socket.c
	${NORMAL_LINT}

uipc_socket.o: $S/kern/uipc_socket.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_syscalls.ln: $S/kern/uipc_syscalls.c
	${NORMAL_LINT}

uipc_syscalls.o: $S/kern/uipc_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uipc_usrreq.ln: $S/kern/uipc_usrreq.c
	${NORMAL_LINT}

uipc_usrreq.o: $S/kern/uipc_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_acl.ln: $S/kern/vfs_acl.c
	${NORMAL_LINT}

vfs_acl.o: $S/kern/vfs_acl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_bio.ln: $S/kern/vfs_bio.c
	${NORMAL_LINT}

vfs_bio.o: $S/kern/vfs_bio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_cache.ln: $S/kern/vfs_cache.c
	${NORMAL_LINT}

vfs_cache.o: $S/kern/vfs_cache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_cluster.ln: $S/kern/vfs_cluster.c
	${NORMAL_LINT}

vfs_cluster.o: $S/kern/vfs_cluster.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_default.ln: $S/kern/vfs_default.c
	${NORMAL_LINT}

vfs_default.o: $S/kern/vfs_default.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_export.ln: $S/kern/vfs_export.c
	${NORMAL_LINT}

vfs_export.o: $S/kern/vfs_export.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_extattr.ln: $S/kern/vfs_extattr.c
	${NORMAL_LINT}

vfs_extattr.o: $S/kern/vfs_extattr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_hash.ln: $S/kern/vfs_hash.c
	${NORMAL_LINT}

vfs_hash.o: $S/kern/vfs_hash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_init.ln: $S/kern/vfs_init.c
	${NORMAL_LINT}

vfs_init.o: $S/kern/vfs_init.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_lookup.ln: $S/kern/vfs_lookup.c
	${NORMAL_LINT}

vfs_lookup.o: $S/kern/vfs_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_mount.ln: $S/kern/vfs_mount.c
	${NORMAL_LINT}

vfs_mount.o: $S/kern/vfs_mount.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_mountroot.ln: $S/kern/vfs_mountroot.c
	${NORMAL_LINT}

vfs_mountroot.o: $S/kern/vfs_mountroot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_subr.ln: $S/kern/vfs_subr.c
	${NORMAL_LINT}

vfs_subr.o: $S/kern/vfs_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_syscalls.ln: $S/kern/vfs_syscalls.c
	${NORMAL_LINT}

vfs_syscalls.o: $S/kern/vfs_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vfs_vnops.ln: $S/kern/vfs_vnops.c
	${NORMAL_LINT}

vfs_vnops.o: $S/kern/vfs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

arc4random.ln: $S/libkern/arc4random.c
	${NORMAL_LINT}

arc4random.o: $S/libkern/arc4random.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bcd.ln: $S/libkern/bcd.c
	${NORMAL_LINT}

bcd.o: $S/libkern/bcd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bsearch.ln: $S/libkern/bsearch.c
	${NORMAL_LINT}

bsearch.o: $S/libkern/bsearch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

crc32.ln: $S/libkern/crc32.c
	${NORMAL_LINT}

crc32.o: $S/libkern/crc32.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fnmatch.ln: $S/libkern/fnmatch.c
	${NORMAL_LINT}

fnmatch.o: $S/libkern/fnmatch.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

index.ln: $S/libkern/index.c
	${NORMAL_LINT}

index.o: $S/libkern/index.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inet_aton.ln: $S/libkern/inet_aton.c
	${NORMAL_LINT}

inet_aton.o: $S/libkern/inet_aton.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inet_ntoa.ln: $S/libkern/inet_ntoa.c
	${NORMAL_LINT}

inet_ntoa.o: $S/libkern/inet_ntoa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inet_ntop.ln: $S/libkern/inet_ntop.c
	${NORMAL_LINT}

inet_ntop.o: $S/libkern/inet_ntop.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

inet_pton.ln: $S/libkern/inet_pton.c
	${NORMAL_LINT}

inet_pton.o: $S/libkern/inet_pton.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memcmp.ln: $S/libkern/memcmp.c
	${NORMAL_LINT}

memcmp.o: $S/libkern/memcmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

qsort.ln: $S/libkern/qsort.c
	${NORMAL_LINT}

qsort.o: $S/libkern/qsort.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

qsort_r.ln: $S/libkern/qsort_r.c
	${NORMAL_LINT}

qsort_r.o: $S/libkern/qsort_r.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

random.ln: $S/libkern/random.c
	${NORMAL_LINT}

random.o: $S/libkern/random.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rindex.ln: $S/libkern/rindex.c
	${NORMAL_LINT}

rindex.o: $S/libkern/rindex.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scanc.ln: $S/libkern/scanc.c
	${NORMAL_LINT}

scanc.o: $S/libkern/scanc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

skpc.ln: $S/libkern/skpc.c
	${NORMAL_LINT}

skpc.o: $S/libkern/skpc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcasecmp.ln: $S/libkern/strcasecmp.c
	${NORMAL_LINT}

strcasecmp.o: $S/libkern/strcasecmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcat.ln: $S/libkern/strcat.c
	${NORMAL_LINT}

strcat.o: $S/libkern/strcat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcmp.ln: $S/libkern/strcmp.c
	${NORMAL_LINT}

strcmp.o: $S/libkern/strcmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcpy.ln: $S/libkern/strcpy.c
	${NORMAL_LINT}

strcpy.o: $S/libkern/strcpy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strcspn.ln: $S/libkern/strcspn.c
	${NORMAL_LINT}

strcspn.o: $S/libkern/strcspn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strdup.ln: $S/libkern/strdup.c
	${NORMAL_LINT}

strdup.o: $S/libkern/strdup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strlcat.ln: $S/libkern/strlcat.c
	${NORMAL_LINT}

strlcat.o: $S/libkern/strlcat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strlcpy.ln: $S/libkern/strlcpy.c
	${NORMAL_LINT}

strlcpy.o: $S/libkern/strlcpy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strlen.ln: $S/libkern/strlen.c
	${NORMAL_LINT}

strlen.o: $S/libkern/strlen.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strncmp.ln: $S/libkern/strncmp.c
	${NORMAL_LINT}

strncmp.o: $S/libkern/strncmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strncpy.ln: $S/libkern/strncpy.c
	${NORMAL_LINT}

strncpy.o: $S/libkern/strncpy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strnlen.ln: $S/libkern/strnlen.c
	${NORMAL_LINT}

strnlen.o: $S/libkern/strnlen.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strsep.ln: $S/libkern/strsep.c
	${NORMAL_LINT}

strsep.o: $S/libkern/strsep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strspn.ln: $S/libkern/strspn.c
	${NORMAL_LINT}

strspn.o: $S/libkern/strspn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strstr.ln: $S/libkern/strstr.c
	${NORMAL_LINT}

strstr.o: $S/libkern/strstr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strtol.ln: $S/libkern/strtol.c
	${NORMAL_LINT}

strtol.o: $S/libkern/strtol.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strtoq.ln: $S/libkern/strtoq.c
	${NORMAL_LINT}

strtoq.o: $S/libkern/strtoq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strtoul.ln: $S/libkern/strtoul.c
	${NORMAL_LINT}

strtoul.o: $S/libkern/strtoul.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strtouq.ln: $S/libkern/strtouq.c
	${NORMAL_LINT}

strtouq.o: $S/libkern/strtouq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

strvalid.ln: $S/libkern/strvalid.c
	${NORMAL_LINT}

strvalid.o: $S/libkern/strvalid.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bpf.ln: $S/net/bpf.c
	${NORMAL_LINT}

bpf.o: $S/net/bpf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bpf_buffer.ln: $S/net/bpf_buffer.c
	${NORMAL_LINT}

bpf_buffer.o: $S/net/bpf_buffer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bpf_filter.ln: $S/net/bpf_filter.c
	${NORMAL_LINT}

bpf_filter.o: $S/net/bpf_filter.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bpf_zerocopy.ln: $S/net/bpf_zerocopy.c
	${NORMAL_LINT}

bpf_zerocopy.o: $S/net/bpf_zerocopy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if.ln: $S/net/if.c
	${NORMAL_LINT}

if.o: $S/net/if.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_clone.ln: $S/net/if_clone.c
	${NORMAL_LINT}

if_clone.o: $S/net/if_clone.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_dead.ln: $S/net/if_dead.c
	${NORMAL_LINT}

if_dead.o: $S/net/if_dead.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ethersubr.ln: $S/net/if_ethersubr.c
	${NORMAL_LINT}

if_ethersubr.o: $S/net/if_ethersubr.c
	${NORMAL_C} -I$S/contrib/pf
	${NORMAL_CTFCONVERT}

if_faith.ln: $S/net/if_faith.c
	${NORMAL_LINT}

if_faith.o: $S/net/if_faith.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_gif.ln: $S/net/if_gif.c
	${NORMAL_LINT}

if_gif.o: $S/net/if_gif.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_loop.ln: $S/net/if_loop.c
	${NORMAL_LINT}

if_loop.o: $S/net/if_loop.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_llatbl.ln: $S/net/if_llatbl.c
	${NORMAL_LINT}

if_llatbl.o: $S/net/if_llatbl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_media.ln: $S/net/if_media.c
	${NORMAL_LINT}

if_media.o: $S/net/if_media.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_mib.ln: $S/net/if_mib.c
	${NORMAL_LINT}

if_mib.o: $S/net/if_mib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_tun.ln: $S/net/if_tun.c
	${NORMAL_LINT}

if_tun.o: $S/net/if_tun.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_vlan.ln: $S/net/if_vlan.c
	${NORMAL_LINT}

if_vlan.o: $S/net/if_vlan.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

netisr.ln: $S/net/netisr.c
	${NORMAL_LINT}

netisr.o: $S/net/netisr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pfil.ln: $S/net/pfil.c
	${NORMAL_LINT}

pfil.o: $S/net/pfil.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

radix.ln: $S/net/radix.c
	${NORMAL_LINT}

radix.o: $S/net/radix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

radix_mpath.ln: $S/net/radix_mpath.c
	${NORMAL_LINT}

radix_mpath.o: $S/net/radix_mpath.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

raw_cb.ln: $S/net/raw_cb.c
	${NORMAL_LINT}

raw_cb.o: $S/net/raw_cb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

raw_usrreq.ln: $S/net/raw_usrreq.c
	${NORMAL_LINT}

raw_usrreq.o: $S/net/raw_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

route.ln: $S/net/route.c
	${NORMAL_LINT}

route.o: $S/net/route.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rtsock.ln: $S/net/rtsock.c
	${NORMAL_LINT}

rtsock.o: $S/net/rtsock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

zlib.ln: $S/net/zlib.c
	${NORMAL_LINT}

zlib.o: $S/net/zlib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211.ln: $S/net80211/ieee80211.c
	${NORMAL_LINT}

ieee80211.o: $S/net80211/ieee80211.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_action.ln: $S/net80211/ieee80211_action.c
	${NORMAL_LINT}

ieee80211_action.o: $S/net80211/ieee80211_action.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_ageq.ln: $S/net80211/ieee80211_ageq.c
	${NORMAL_LINT}

ieee80211_ageq.o: $S/net80211/ieee80211_ageq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_adhoc.ln: $S/net80211/ieee80211_adhoc.c
	${NORMAL_LINT}

ieee80211_adhoc.o: $S/net80211/ieee80211_adhoc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_amrr.ln: $S/net80211/ieee80211_amrr.c
	${NORMAL_LINT}

ieee80211_amrr.o: $S/net80211/ieee80211_amrr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_crypto.ln: $S/net80211/ieee80211_crypto.c
	${NORMAL_LINT}

ieee80211_crypto.o: $S/net80211/ieee80211_crypto.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_crypto_ccmp.ln: $S/net80211/ieee80211_crypto_ccmp.c
	${NORMAL_LINT}

ieee80211_crypto_ccmp.o: $S/net80211/ieee80211_crypto_ccmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_crypto_none.ln: $S/net80211/ieee80211_crypto_none.c
	${NORMAL_LINT}

ieee80211_crypto_none.o: $S/net80211/ieee80211_crypto_none.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_crypto_tkip.ln: $S/net80211/ieee80211_crypto_tkip.c
	${NORMAL_LINT}

ieee80211_crypto_tkip.o: $S/net80211/ieee80211_crypto_tkip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_crypto_wep.ln: $S/net80211/ieee80211_crypto_wep.c
	${NORMAL_LINT}

ieee80211_crypto_wep.o: $S/net80211/ieee80211_crypto_wep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_dfs.ln: $S/net80211/ieee80211_dfs.c
	${NORMAL_LINT}

ieee80211_dfs.o: $S/net80211/ieee80211_dfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_freebsd.ln: $S/net80211/ieee80211_freebsd.c
	${NORMAL_LINT}

ieee80211_freebsd.o: $S/net80211/ieee80211_freebsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_hostap.ln: $S/net80211/ieee80211_hostap.c
	${NORMAL_LINT}

ieee80211_hostap.o: $S/net80211/ieee80211_hostap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_ht.ln: $S/net80211/ieee80211_ht.c
	${NORMAL_LINT}

ieee80211_ht.o: $S/net80211/ieee80211_ht.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_hwmp.ln: $S/net80211/ieee80211_hwmp.c
	${NORMAL_LINT}

ieee80211_hwmp.o: $S/net80211/ieee80211_hwmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_input.ln: $S/net80211/ieee80211_input.c
	${NORMAL_LINT}

ieee80211_input.o: $S/net80211/ieee80211_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_ioctl.ln: $S/net80211/ieee80211_ioctl.c
	${NORMAL_LINT}

ieee80211_ioctl.o: $S/net80211/ieee80211_ioctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_mesh.ln: $S/net80211/ieee80211_mesh.c
	${NORMAL_LINT}

ieee80211_mesh.o: $S/net80211/ieee80211_mesh.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_monitor.ln: $S/net80211/ieee80211_monitor.c
	${NORMAL_LINT}

ieee80211_monitor.o: $S/net80211/ieee80211_monitor.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_node.ln: $S/net80211/ieee80211_node.c
	${NORMAL_LINT}

ieee80211_node.o: $S/net80211/ieee80211_node.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_output.ln: $S/net80211/ieee80211_output.c
	${NORMAL_LINT}

ieee80211_output.o: $S/net80211/ieee80211_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_phy.ln: $S/net80211/ieee80211_phy.c
	${NORMAL_LINT}

ieee80211_phy.o: $S/net80211/ieee80211_phy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_power.ln: $S/net80211/ieee80211_power.c
	${NORMAL_LINT}

ieee80211_power.o: $S/net80211/ieee80211_power.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_proto.ln: $S/net80211/ieee80211_proto.c
	${NORMAL_LINT}

ieee80211_proto.o: $S/net80211/ieee80211_proto.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_radiotap.ln: $S/net80211/ieee80211_radiotap.c
	${NORMAL_LINT}

ieee80211_radiotap.o: $S/net80211/ieee80211_radiotap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_ratectl.ln: $S/net80211/ieee80211_ratectl.c
	${NORMAL_LINT}

ieee80211_ratectl.o: $S/net80211/ieee80211_ratectl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_ratectl_none.ln: $S/net80211/ieee80211_ratectl_none.c
	${NORMAL_LINT}

ieee80211_ratectl_none.o: $S/net80211/ieee80211_ratectl_none.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_regdomain.ln: $S/net80211/ieee80211_regdomain.c
	${NORMAL_LINT}

ieee80211_regdomain.o: $S/net80211/ieee80211_regdomain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_scan.ln: $S/net80211/ieee80211_scan.c
	${NORMAL_LINT}

ieee80211_scan.o: $S/net80211/ieee80211_scan.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_scan_sta.ln: $S/net80211/ieee80211_scan_sta.c
	${NORMAL_LINT}

ieee80211_scan_sta.o: $S/net80211/ieee80211_scan_sta.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_sta.ln: $S/net80211/ieee80211_sta.c
	${NORMAL_LINT}

ieee80211_sta.o: $S/net80211/ieee80211_sta.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ieee80211_wds.ln: $S/net80211/ieee80211_wds.c
	${NORMAL_LINT}

ieee80211_wds.o: $S/net80211/ieee80211_wds.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ether.ln: $S/netinet/if_ether.c
	${NORMAL_LINT}

if_ether.o: $S/netinet/if_ether.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

igmp.ln: $S/netinet/igmp.c
	${NORMAL_LINT}

igmp.o: $S/netinet/igmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in.ln: $S/netinet/in.c
	${NORMAL_LINT}

in.o: $S/netinet/in.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_gif.ln: $S/netinet/in_gif.c
	${NORMAL_LINT}

in_gif.o: $S/netinet/in_gif.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_id.ln: $S/netinet/ip_id.c
	${NORMAL_LINT}

ip_id.o: $S/netinet/ip_id.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_mcast.ln: $S/netinet/in_mcast.c
	${NORMAL_LINT}

in_mcast.o: $S/netinet/in_mcast.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_pcb.ln: $S/netinet/in_pcb.c
	${NORMAL_LINT}

in_pcb.o: $S/netinet/in_pcb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_proto.ln: $S/netinet/in_proto.c
	${NORMAL_LINT}

in_proto.o: $S/netinet/in_proto.c
	${NORMAL_C} -I$S/contrib/pf
	${NORMAL_CTFCONVERT}

in_rmx.ln: $S/netinet/in_rmx.c
	${NORMAL_LINT}

in_rmx.o: $S/netinet/in_rmx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_ecn.ln: $S/netinet/ip_ecn.c
	${NORMAL_LINT}

ip_ecn.o: $S/netinet/ip_ecn.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_encap.ln: $S/netinet/ip_encap.c
	${NORMAL_LINT}

ip_encap.o: $S/netinet/ip_encap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_fastfwd.ln: $S/netinet/ip_fastfwd.c
	${NORMAL_LINT}

ip_fastfwd.o: $S/netinet/ip_fastfwd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_icmp.ln: $S/netinet/ip_icmp.c
	${NORMAL_LINT}

ip_icmp.o: $S/netinet/ip_icmp.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_input.ln: $S/netinet/ip_input.c
	${NORMAL_LINT}

ip_input.o: $S/netinet/ip_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_options.ln: $S/netinet/ip_options.c
	${NORMAL_LINT}

ip_options.o: $S/netinet/ip_options.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip_output.ln: $S/netinet/ip_output.c
	${NORMAL_LINT}

ip_output.o: $S/netinet/ip_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

raw_ip.ln: $S/netinet/raw_ip.c
	${NORMAL_LINT}

raw_ip.o: $S/netinet/raw_ip.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cc.ln: $S/netinet/cc/cc.c
	${NORMAL_LINT}

cc.o: $S/netinet/cc/cc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cc_newreno.ln: $S/netinet/cc/cc_newreno.c
	${NORMAL_LINT}

cc_newreno.o: $S/netinet/cc/cc_newreno.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_asconf.ln: $S/netinet/sctp_asconf.c
	${NORMAL_LINT}

sctp_asconf.o: $S/netinet/sctp_asconf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_auth.ln: $S/netinet/sctp_auth.c
	${NORMAL_LINT}

sctp_auth.o: $S/netinet/sctp_auth.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_bsd_addr.ln: $S/netinet/sctp_bsd_addr.c
	${NORMAL_LINT}

sctp_bsd_addr.o: $S/netinet/sctp_bsd_addr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_cc_functions.ln: $S/netinet/sctp_cc_functions.c
	${NORMAL_LINT}

sctp_cc_functions.o: $S/netinet/sctp_cc_functions.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_crc32.ln: $S/netinet/sctp_crc32.c
	${NORMAL_LINT}

sctp_crc32.o: $S/netinet/sctp_crc32.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_indata.ln: $S/netinet/sctp_indata.c
	${NORMAL_LINT}

sctp_indata.o: $S/netinet/sctp_indata.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_input.ln: $S/netinet/sctp_input.c
	${NORMAL_LINT}

sctp_input.o: $S/netinet/sctp_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_output.ln: $S/netinet/sctp_output.c
	${NORMAL_LINT}

sctp_output.o: $S/netinet/sctp_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_pcb.ln: $S/netinet/sctp_pcb.c
	${NORMAL_LINT}

sctp_pcb.o: $S/netinet/sctp_pcb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_peeloff.ln: $S/netinet/sctp_peeloff.c
	${NORMAL_LINT}

sctp_peeloff.o: $S/netinet/sctp_peeloff.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_ss_functions.ln: $S/netinet/sctp_ss_functions.c
	${NORMAL_LINT}

sctp_ss_functions.o: $S/netinet/sctp_ss_functions.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_sysctl.ln: $S/netinet/sctp_sysctl.c
	${NORMAL_LINT}

sctp_sysctl.o: $S/netinet/sctp_sysctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_timer.ln: $S/netinet/sctp_timer.c
	${NORMAL_LINT}

sctp_timer.o: $S/netinet/sctp_timer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp_usrreq.ln: $S/netinet/sctp_usrreq.c
	${NORMAL_LINT}

sctp_usrreq.o: $S/netinet/sctp_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctputil.ln: $S/netinet/sctputil.c
	${NORMAL_LINT}

sctputil.o: $S/netinet/sctputil.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_hostcache.ln: $S/netinet/tcp_hostcache.c
	${NORMAL_LINT}

tcp_hostcache.o: $S/netinet/tcp_hostcache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_input.ln: $S/netinet/tcp_input.c
	${NORMAL_LINT}

tcp_input.o: $S/netinet/tcp_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_lro.ln: $S/netinet/tcp_lro.c
	${NORMAL_LINT}

tcp_lro.o: $S/netinet/tcp_lro.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_output.ln: $S/netinet/tcp_output.c
	${NORMAL_LINT}

tcp_output.o: $S/netinet/tcp_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_offload.ln: $S/netinet/tcp_offload.c
	${NORMAL_LINT}

tcp_offload.o: $S/netinet/tcp_offload.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_reass.ln: $S/netinet/tcp_reass.c
	${NORMAL_LINT}

tcp_reass.o: $S/netinet/tcp_reass.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_sack.ln: $S/netinet/tcp_sack.c
	${NORMAL_LINT}

tcp_sack.o: $S/netinet/tcp_sack.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_subr.ln: $S/netinet/tcp_subr.c
	${NORMAL_LINT}

tcp_subr.o: $S/netinet/tcp_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_syncache.ln: $S/netinet/tcp_syncache.c
	${NORMAL_LINT}

tcp_syncache.o: $S/netinet/tcp_syncache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_timer.ln: $S/netinet/tcp_timer.c
	${NORMAL_LINT}

tcp_timer.o: $S/netinet/tcp_timer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_timewait.ln: $S/netinet/tcp_timewait.c
	${NORMAL_LINT}

tcp_timewait.o: $S/netinet/tcp_timewait.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tcp_usrreq.ln: $S/netinet/tcp_usrreq.c
	${NORMAL_LINT}

tcp_usrreq.o: $S/netinet/tcp_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

udp_usrreq.ln: $S/netinet/udp_usrreq.c
	${NORMAL_LINT}

udp_usrreq.o: $S/netinet/udp_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dest6.ln: $S/netinet6/dest6.c
	${NORMAL_LINT}

dest6.o: $S/netinet6/dest6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

frag6.ln: $S/netinet6/frag6.c
	${NORMAL_LINT}

frag6.o: $S/netinet6/frag6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

icmp6.ln: $S/netinet6/icmp6.c
	${NORMAL_LINT}

icmp6.o: $S/netinet6/icmp6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6.ln: $S/netinet6/in6.c
	${NORMAL_LINT}

in6.o: $S/netinet6/in6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_cksum.ln: $S/netinet6/in6_cksum.c
	${NORMAL_LINT}

in6_cksum.o: $S/netinet6/in6_cksum.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_gif.ln: $S/netinet6/in6_gif.c
	${NORMAL_LINT}

in6_gif.o: $S/netinet6/in6_gif.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_ifattach.ln: $S/netinet6/in6_ifattach.c
	${NORMAL_LINT}

in6_ifattach.o: $S/netinet6/in6_ifattach.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_mcast.ln: $S/netinet6/in6_mcast.c
	${NORMAL_LINT}

in6_mcast.o: $S/netinet6/in6_mcast.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_pcb.ln: $S/netinet6/in6_pcb.c
	${NORMAL_LINT}

in6_pcb.o: $S/netinet6/in6_pcb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_proto.ln: $S/netinet6/in6_proto.c
	${NORMAL_LINT}

in6_proto.o: $S/netinet6/in6_proto.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_rmx.ln: $S/netinet6/in6_rmx.c
	${NORMAL_LINT}

in6_rmx.o: $S/netinet6/in6_rmx.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in6_src.ln: $S/netinet6/in6_src.c
	${NORMAL_LINT}

in6_src.o: $S/netinet6/in6_src.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_forward.ln: $S/netinet6/ip6_forward.c
	${NORMAL_LINT}

ip6_forward.o: $S/netinet6/ip6_forward.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_id.ln: $S/netinet6/ip6_id.c
	${NORMAL_LINT}

ip6_id.o: $S/netinet6/ip6_id.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_input.ln: $S/netinet6/ip6_input.c
	${NORMAL_LINT}

ip6_input.o: $S/netinet6/ip6_input.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ip6_output.ln: $S/netinet6/ip6_output.c
	${NORMAL_LINT}

ip6_output.o: $S/netinet6/ip6_output.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mld6.ln: $S/netinet6/mld6.c
	${NORMAL_LINT}

mld6.o: $S/netinet6/mld6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nd6.ln: $S/netinet6/nd6.c
	${NORMAL_LINT}

nd6.o: $S/netinet6/nd6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nd6_nbr.ln: $S/netinet6/nd6_nbr.c
	${NORMAL_LINT}

nd6_nbr.o: $S/netinet6/nd6_nbr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nd6_rtr.ln: $S/netinet6/nd6_rtr.c
	${NORMAL_LINT}

nd6_rtr.o: $S/netinet6/nd6_rtr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

raw_ip6.ln: $S/netinet6/raw_ip6.c
	${NORMAL_LINT}

raw_ip6.o: $S/netinet6/raw_ip6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

route6.ln: $S/netinet6/route6.c
	${NORMAL_LINT}

route6.o: $S/netinet6/route6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scope6.ln: $S/netinet6/scope6.c
	${NORMAL_LINT}

scope6.o: $S/netinet6/scope6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sctp6_usrreq.ln: $S/netinet6/sctp6_usrreq.c
	${NORMAL_LINT}

sctp6_usrreq.o: $S/netinet6/sctp6_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

udp6_usrreq.ln: $S/netinet6/udp6_usrreq.c
	${NORMAL_LINT}

udp6_usrreq.o: $S/netinet6/udp6_usrreq.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_diskless.ln: $S/nfs/nfs_diskless.c
	${NORMAL_LINT}

nfs_diskless.o: $S/nfs/nfs_diskless.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_fha.ln: $S/nfs/nfs_fha.c
	${NORMAL_LINT}

nfs_fha.o: $S/nfs/nfs_fha.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_lock.ln: $S/nfs/nfs_lock.c
	${NORMAL_LINT}

nfs_lock.o: $S/nfs/nfs_lock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nfs_nfssvc.ln: $S/nfs/nfs_nfssvc.c
	${NORMAL_LINT}

nfs_nfssvc.o: $S/nfs/nfs_nfssvc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_advlock.ln: $S/nlm/nlm_advlock.c
	${NORMAL_LINT}

nlm_advlock.o: $S/nlm/nlm_advlock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_clnt.ln: $S/nlm/nlm_prot_clnt.c
	${NORMAL_LINT}

nlm_prot_clnt.o: $S/nlm/nlm_prot_clnt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_impl.ln: $S/nlm/nlm_prot_impl.c
	${NORMAL_LINT}

nlm_prot_impl.o: $S/nlm/nlm_prot_impl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_server.ln: $S/nlm/nlm_prot_server.c
	${NORMAL_LINT}

nlm_prot_server.o: $S/nlm/nlm_prot_server.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_svc.ln: $S/nlm/nlm_prot_svc.c
	${NORMAL_LINT}

nlm_prot_svc.o: $S/nlm/nlm_prot_svc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nlm_prot_xdr.ln: $S/nlm/nlm_prot_xdr.c
	${NORMAL_LINT}

nlm_prot_xdr.o: $S/nlm/nlm_prot_xdr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sm_inter_xdr.ln: $S/nlm/sm_inter_xdr.c
	${NORMAL_LINT}

sm_inter_xdr.o: $S/nlm/sm_inter_xdr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_rl.ln: $S/pci/if_rl.c
	${NORMAL_LINT}

if_rl.o: $S/pci/if_rl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

auth_none.ln: $S/rpc/auth_none.c
	${NORMAL_LINT}

auth_none.o: $S/rpc/auth_none.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

auth_unix.ln: $S/rpc/auth_unix.c
	${NORMAL_LINT}

auth_unix.o: $S/rpc/auth_unix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

authunix_prot.ln: $S/rpc/authunix_prot.c
	${NORMAL_LINT}

authunix_prot.o: $S/rpc/authunix_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clnt_dg.ln: $S/rpc/clnt_dg.c
	${NORMAL_LINT}

clnt_dg.o: $S/rpc/clnt_dg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clnt_rc.ln: $S/rpc/clnt_rc.c
	${NORMAL_LINT}

clnt_rc.o: $S/rpc/clnt_rc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clnt_vc.ln: $S/rpc/clnt_vc.c
	${NORMAL_LINT}

clnt_vc.o: $S/rpc/clnt_vc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

getnetconfig.ln: $S/rpc/getnetconfig.c
	${NORMAL_LINT}

getnetconfig.o: $S/rpc/getnetconfig.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

replay.ln: $S/rpc/replay.c
	${NORMAL_LINT}

replay.o: $S/rpc/replay.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpc_callmsg.ln: $S/rpc/rpc_callmsg.c
	${NORMAL_LINT}

rpc_callmsg.o: $S/rpc/rpc_callmsg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpc_generic.ln: $S/rpc/rpc_generic.c
	${NORMAL_LINT}

rpc_generic.o: $S/rpc/rpc_generic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpc_prot.ln: $S/rpc/rpc_prot.c
	${NORMAL_LINT}

rpc_prot.o: $S/rpc/rpc_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpcb_clnt.ln: $S/rpc/rpcb_clnt.c
	${NORMAL_LINT}

rpcb_clnt.o: $S/rpc/rpcb_clnt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

rpcb_prot.ln: $S/rpc/rpcb_prot.c
	${NORMAL_LINT}

rpcb_prot.o: $S/rpc/rpcb_prot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc.ln: $S/rpc/svc.c
	${NORMAL_LINT}

svc.o: $S/rpc/svc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_auth.ln: $S/rpc/svc_auth.c
	${NORMAL_LINT}

svc_auth.o: $S/rpc/svc_auth.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_auth_unix.ln: $S/rpc/svc_auth_unix.c
	${NORMAL_LINT}

svc_auth_unix.o: $S/rpc/svc_auth_unix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_dg.ln: $S/rpc/svc_dg.c
	${NORMAL_LINT}

svc_dg.o: $S/rpc/svc_dg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_generic.ln: $S/rpc/svc_generic.c
	${NORMAL_LINT}

svc_generic.o: $S/rpc/svc_generic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

svc_vc.ln: $S/rpc/svc_vc.c
	${NORMAL_LINT}

svc_vc.o: $S/rpc/svc_vc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit.ln: $S/security/audit/audit.c
	${NORMAL_LINT}

audit.o: $S/security/audit/audit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_arg.ln: $S/security/audit/audit_arg.c
	${NORMAL_LINT}

audit_arg.o: $S/security/audit/audit_arg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm.ln: $S/security/audit/audit_bsm.c
	${NORMAL_LINT}

audit_bsm.o: $S/security/audit/audit_bsm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm_domain.ln: $S/security/audit/audit_bsm_domain.c
	${NORMAL_LINT}

audit_bsm_domain.o: $S/security/audit/audit_bsm_domain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm_errno.ln: $S/security/audit/audit_bsm_errno.c
	${NORMAL_LINT}

audit_bsm_errno.o: $S/security/audit/audit_bsm_errno.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm_fcntl.ln: $S/security/audit/audit_bsm_fcntl.c
	${NORMAL_LINT}

audit_bsm_fcntl.o: $S/security/audit/audit_bsm_fcntl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm_klib.ln: $S/security/audit/audit_bsm_klib.c
	${NORMAL_LINT}

audit_bsm_klib.o: $S/security/audit/audit_bsm_klib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm_socket_type.ln: $S/security/audit/audit_bsm_socket_type.c
	${NORMAL_LINT}

audit_bsm_socket_type.o: $S/security/audit/audit_bsm_socket_type.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_bsm_token.ln: $S/security/audit/audit_bsm_token.c
	${NORMAL_LINT}

audit_bsm_token.o: $S/security/audit/audit_bsm_token.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_pipe.ln: $S/security/audit/audit_pipe.c
	${NORMAL_LINT}

audit_pipe.o: $S/security/audit/audit_pipe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_syscalls.ln: $S/security/audit/audit_syscalls.c
	${NORMAL_LINT}

audit_syscalls.o: $S/security/audit/audit_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_trigger.ln: $S/security/audit/audit_trigger.c
	${NORMAL_LINT}

audit_trigger.o: $S/security/audit/audit_trigger.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

audit_worker.ln: $S/security/audit/audit_worker.c
	${NORMAL_LINT}

audit_worker.o: $S/security/audit/audit_worker.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_audit.ln: $S/security/mac/mac_audit.c
	${NORMAL_LINT}

mac_audit.o: $S/security/mac/mac_audit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_cred.ln: $S/security/mac/mac_cred.c
	${NORMAL_LINT}

mac_cred.o: $S/security/mac/mac_cred.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_framework.ln: $S/security/mac/mac_framework.c
	${NORMAL_LINT}

mac_framework.o: $S/security/mac/mac_framework.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_inet.ln: $S/security/mac/mac_inet.c
	${NORMAL_LINT}

mac_inet.o: $S/security/mac/mac_inet.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_inet6.ln: $S/security/mac/mac_inet6.c
	${NORMAL_LINT}

mac_inet6.o: $S/security/mac/mac_inet6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_label.ln: $S/security/mac/mac_label.c
	${NORMAL_LINT}

mac_label.o: $S/security/mac/mac_label.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_net.ln: $S/security/mac/mac_net.c
	${NORMAL_LINT}

mac_net.o: $S/security/mac/mac_net.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_pipe.ln: $S/security/mac/mac_pipe.c
	${NORMAL_LINT}

mac_pipe.o: $S/security/mac/mac_pipe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_posix_sem.ln: $S/security/mac/mac_posix_sem.c
	${NORMAL_LINT}

mac_posix_sem.o: $S/security/mac/mac_posix_sem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_posix_shm.ln: $S/security/mac/mac_posix_shm.c
	${NORMAL_LINT}

mac_posix_shm.o: $S/security/mac/mac_posix_shm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_priv.ln: $S/security/mac/mac_priv.c
	${NORMAL_LINT}

mac_priv.o: $S/security/mac/mac_priv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_process.ln: $S/security/mac/mac_process.c
	${NORMAL_LINT}

mac_process.o: $S/security/mac/mac_process.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_socket.ln: $S/security/mac/mac_socket.c
	${NORMAL_LINT}

mac_socket.o: $S/security/mac/mac_socket.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_syscalls.ln: $S/security/mac/mac_syscalls.c
	${NORMAL_LINT}

mac_syscalls.o: $S/security/mac/mac_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_system.ln: $S/security/mac/mac_system.c
	${NORMAL_LINT}

mac_system.o: $S/security/mac/mac_system.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_sysv_msg.ln: $S/security/mac/mac_sysv_msg.c
	${NORMAL_LINT}

mac_sysv_msg.o: $S/security/mac/mac_sysv_msg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_sysv_sem.ln: $S/security/mac/mac_sysv_sem.c
	${NORMAL_LINT}

mac_sysv_sem.o: $S/security/mac/mac_sysv_sem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_sysv_shm.ln: $S/security/mac/mac_sysv_shm.c
	${NORMAL_LINT}

mac_sysv_shm.o: $S/security/mac/mac_sysv_shm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mac_vfs.ln: $S/security/mac/mac_vfs.c
	${NORMAL_LINT}

mac_vfs.o: $S/security/mac/mac_vfs.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

teken.ln: $S/teken/teken.c
	${NORMAL_LINT}

teken.o: $S/teken/teken.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_alloc.ln: $S/ufs/ffs/ffs_alloc.c
	${NORMAL_LINT}

ffs_alloc.o: $S/ufs/ffs/ffs_alloc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_balloc.ln: $S/ufs/ffs/ffs_balloc.c
	${NORMAL_LINT}

ffs_balloc.o: $S/ufs/ffs/ffs_balloc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_inode.ln: $S/ufs/ffs/ffs_inode.c
	${NORMAL_LINT}

ffs_inode.o: $S/ufs/ffs/ffs_inode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_snapshot.ln: $S/ufs/ffs/ffs_snapshot.c
	${NORMAL_LINT}

ffs_snapshot.o: $S/ufs/ffs/ffs_snapshot.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_softdep.ln: $S/ufs/ffs/ffs_softdep.c
	${NORMAL_LINT}

ffs_softdep.o: $S/ufs/ffs/ffs_softdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_subr.ln: $S/ufs/ffs/ffs_subr.c
	${NORMAL_LINT}

ffs_subr.o: $S/ufs/ffs/ffs_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_tables.ln: $S/ufs/ffs/ffs_tables.c
	${NORMAL_LINT}

ffs_tables.o: $S/ufs/ffs/ffs_tables.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_vfsops.ln: $S/ufs/ffs/ffs_vfsops.c
	${NORMAL_LINT}

ffs_vfsops.o: $S/ufs/ffs/ffs_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_vnops.ln: $S/ufs/ffs/ffs_vnops.c
	${NORMAL_LINT}

ffs_vnops.o: $S/ufs/ffs/ffs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ffs_suspend.ln: $S/ufs/ffs/ffs_suspend.c
	${NORMAL_LINT}

ffs_suspend.o: $S/ufs/ffs/ffs_suspend.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_acl.ln: $S/ufs/ufs/ufs_acl.c
	${NORMAL_LINT}

ufs_acl.o: $S/ufs/ufs/ufs_acl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_bmap.ln: $S/ufs/ufs/ufs_bmap.c
	${NORMAL_LINT}

ufs_bmap.o: $S/ufs/ufs/ufs_bmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_dirhash.ln: $S/ufs/ufs/ufs_dirhash.c
	${NORMAL_LINT}

ufs_dirhash.o: $S/ufs/ufs/ufs_dirhash.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_extattr.ln: $S/ufs/ufs/ufs_extattr.c
	${NORMAL_LINT}

ufs_extattr.o: $S/ufs/ufs/ufs_extattr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_gjournal.ln: $S/ufs/ufs/ufs_gjournal.c
	${NORMAL_LINT}

ufs_gjournal.o: $S/ufs/ufs/ufs_gjournal.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_inode.ln: $S/ufs/ufs/ufs_inode.c
	${NORMAL_LINT}

ufs_inode.o: $S/ufs/ufs/ufs_inode.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_lookup.ln: $S/ufs/ufs/ufs_lookup.c
	${NORMAL_LINT}

ufs_lookup.o: $S/ufs/ufs/ufs_lookup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_quota.ln: $S/ufs/ufs/ufs_quota.c
	${NORMAL_LINT}

ufs_quota.o: $S/ufs/ufs/ufs_quota.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_vfsops.ln: $S/ufs/ufs/ufs_vfsops.c
	${NORMAL_LINT}

ufs_vfsops.o: $S/ufs/ufs/ufs_vfsops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ufs_vnops.ln: $S/ufs/ufs/ufs_vnops.c
	${NORMAL_LINT}

ufs_vnops.o: $S/ufs/ufs/ufs_vnops.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

default_pager.ln: $S/vm/default_pager.c
	${NORMAL_LINT}

default_pager.o: $S/vm/default_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

device_pager.ln: $S/vm/device_pager.c
	${NORMAL_LINT}

device_pager.o: $S/vm/device_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

phys_pager.ln: $S/vm/phys_pager.c
	${NORMAL_LINT}

phys_pager.o: $S/vm/phys_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sg_pager.ln: $S/vm/sg_pager.c
	${NORMAL_LINT}

sg_pager.o: $S/vm/sg_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

swap_pager.ln: $S/vm/swap_pager.c
	${NORMAL_LINT}

swap_pager.o: $S/vm/swap_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uma_core.ln: $S/vm/uma_core.c
	${NORMAL_LINT}

uma_core.o: $S/vm/uma_core.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uma_dbg.ln: $S/vm/uma_dbg.c
	${NORMAL_LINT}

uma_dbg.o: $S/vm/uma_dbg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_contig.ln: $S/vm/vm_contig.c
	${NORMAL_LINT}

vm_contig.o: $S/vm/vm_contig.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_fault.ln: $S/vm/vm_fault.c
	${NORMAL_LINT}

vm_fault.o: $S/vm/vm_fault.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_glue.ln: $S/vm/vm_glue.c
	${NORMAL_LINT}

vm_glue.o: $S/vm/vm_glue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_init.ln: $S/vm/vm_init.c
	${NORMAL_LINT}

vm_init.o: $S/vm/vm_init.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_kern.ln: $S/vm/vm_kern.c
	${NORMAL_LINT}

vm_kern.o: $S/vm/vm_kern.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_map.ln: $S/vm/vm_map.c
	${NORMAL_LINT}

vm_map.o: $S/vm/vm_map.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_meter.ln: $S/vm/vm_meter.c
	${NORMAL_LINT}

vm_meter.o: $S/vm/vm_meter.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_mmap.ln: $S/vm/vm_mmap.c
	${NORMAL_LINT}

vm_mmap.o: $S/vm/vm_mmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_object.ln: $S/vm/vm_object.c
	${NORMAL_LINT}

vm_object.o: $S/vm/vm_object.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_page.ln: $S/vm/vm_page.c
	${NORMAL_LINT}

vm_page.o: $S/vm/vm_page.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_pageout.ln: $S/vm/vm_pageout.c
	${NORMAL_LINT}

vm_pageout.o: $S/vm/vm_pageout.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_pager.ln: $S/vm/vm_pager.c
	${NORMAL_LINT}

vm_pager.o: $S/vm/vm_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_phys.ln: $S/vm/vm_phys.c
	${NORMAL_LINT}

vm_phys.o: $S/vm/vm_phys.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_reserv.ln: $S/vm/vm_reserv.c
	${NORMAL_LINT}

vm_reserv.o: $S/vm/vm_reserv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_unix.ln: $S/vm/vm_unix.c
	${NORMAL_LINT}

vm_unix.o: $S/vm/vm_unix.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_zeroidle.ln: $S/vm/vm_zeroidle.c
	${NORMAL_LINT}

vm_zeroidle.o: $S/vm/vm_zeroidle.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vnode_pager.ln: $S/vm/vnode_pager.c
	${NORMAL_LINT}

vnode_pager.o: $S/vm/vnode_pager.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr.ln: $S/xdr/xdr.c
	${NORMAL_LINT}

xdr.o: $S/xdr/xdr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_array.ln: $S/xdr/xdr_array.c
	${NORMAL_LINT}

xdr_array.o: $S/xdr/xdr_array.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_mbuf.ln: $S/xdr/xdr_mbuf.c
	${NORMAL_LINT}

xdr_mbuf.o: $S/xdr/xdr_mbuf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_mem.ln: $S/xdr/xdr_mem.c
	${NORMAL_LINT}

xdr_mem.o: $S/xdr/xdr_mem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_reference.ln: $S/xdr/xdr_reference.c
	${NORMAL_LINT}

xdr_reference.o: $S/xdr/xdr_reference.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

xdr_sizeof.ln: $S/xdr/xdr_sizeof.c
	${NORMAL_LINT}

xdr_sizeof.o: $S/xdr/xdr_sizeof.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ia32_genassym.o: $S/compat/ia32/ia32_genassym.c
	${CC} ${CFLAGS:N-fno-common} -c ${.IMPSRC}

ia32_assym.h: $S/kern/genassym.sh ia32_genassym.o
	env NM='${NM}' sh $S/kern/genassym.sh ia32_genassym.o > ${.TARGET}

hpt27xx_lib.o: $S/dev/hpt27xx/amd64-elf.hpt27xx_lib.o.uu
	uudecode < $S/dev/hpt27xx/amd64-elf.hpt27xx_lib.o.uu
	${NORMAL_CTFCONVERT}

hptmvraid.o: $S/dev/hptmv/amd64-elf.raid.o.uu
	uudecode < $S/dev/hptmv/amd64-elf.raid.o.uu
	${NORMAL_CTFCONVERT}

hptnr_lib.o: $S/dev/hptnr/amd64-elf.hptnr_lib.o.uu
	uudecode < $S/dev/hptnr/amd64-elf.hptnr_lib.o.uu
	${NORMAL_CTFCONVERT}

hptrr_lib.o: $S/dev/hptrr/amd64-elf.hptrr_lib.o.uu
	uudecode < $S/dev/hptrr/amd64-elf.hptrr_lib.o.uu
	${NORMAL_CTFCONVERT}

acpi_machdep.ln: $S/amd64/acpica/acpi_machdep.c
	${NORMAL_LINT}

acpi_machdep.o: $S/amd64/acpica/acpi_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_switch.ln: $S/amd64/acpica/acpi_switch.S
	${NORMAL_LINT}

acpi_switch.o: $S/amd64/acpica/acpi_switch.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

acpi_wakecode.o: $S/amd64/acpica/acpi_wakecode.S assym.s
	${NORMAL_S}

acpi_wakecode.bin: acpi_wakecode.o
	objcopy -S -O binary acpi_wakecode.o ${.TARGET}

acpi_wakecode.h: acpi_wakecode.bin
	file2c -sx 'static char wakecode[] = {' '};' < acpi_wakecode.bin > ${.TARGET}

acpi_wakedata.h: acpi_wakecode.o
	${NM} -n --defined-only acpi_wakecode.o | while read offset dummy what; do echo "#define	$${what}	0x$${offset}"; done > ${.TARGET}

acpi_wakeup.ln: $S/amd64/acpica/acpi_wakeup.c
	${NORMAL_LINT}

acpi_wakeup.o: $S/amd64/acpica/acpi_wakeup.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

amd64_mem.ln: $S/amd64/amd64/amd64_mem.c
	${NORMAL_LINT}

amd64_mem.o: $S/amd64/amd64/amd64_mem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atomic.ln: $S/amd64/amd64/atomic.c
	${NORMAL_LINT}

atomic.o: $S/amd64/amd64/atomic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

autoconf.ln: $S/amd64/amd64/autoconf.c
	${NORMAL_LINT}

autoconf.o: $S/amd64/amd64/autoconf.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

bios.ln: $S/amd64/amd64/bios.c
	${NORMAL_LINT}

bios.o: $S/amd64/amd64/bios.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

cpu_switch.ln: $S/amd64/amd64/cpu_switch.S
	${NORMAL_LINT}

cpu_switch.o: $S/amd64/amd64/cpu_switch.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

elf_machdep.ln: $S/amd64/amd64/elf_machdep.c
	${NORMAL_LINT}

elf_machdep.o: $S/amd64/amd64/elf_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

exception.ln: $S/amd64/amd64/exception.S
	${NORMAL_LINT}

exception.o: $S/amd64/amd64/exception.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

fpu.ln: $S/amd64/amd64/fpu.c
	${NORMAL_LINT}

fpu.o: $S/amd64/amd64/fpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

identcpu.ln: $S/amd64/amd64/identcpu.c
	${NORMAL_LINT}

identcpu.o: $S/amd64/amd64/identcpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

in_cksum.ln: $S/amd64/amd64/in_cksum.c
	${NORMAL_LINT}

in_cksum.o: $S/amd64/amd64/in_cksum.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

initcpu.ln: $S/amd64/amd64/initcpu.c
	${NORMAL_LINT}

initcpu.o: $S/amd64/amd64/initcpu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

io.ln: $S/amd64/amd64/io.c
	${NORMAL_LINT}

io.o: $S/amd64/amd64/io.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

legacy.ln: $S/amd64/amd64/legacy.c
	${NORMAL_LINT}

legacy.o: $S/amd64/amd64/legacy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

locore.ln: $S/amd64/amd64/locore.S
	${NORMAL_LINT}

locore.o: $S/amd64/amd64/locore.S
	${NORMAL_S}

machdep.ln: $S/amd64/amd64/machdep.c
	${NORMAL_LINT}

machdep.o: $S/amd64/amd64/machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mem.ln: $S/amd64/amd64/mem.c
	${NORMAL_LINT}

mem.o: $S/amd64/amd64/mem.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

minidump_machdep.ln: $S/amd64/amd64/minidump_machdep.c
	${NORMAL_LINT}

minidump_machdep.o: $S/amd64/amd64/minidump_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mp_machdep.ln: $S/amd64/amd64/mp_machdep.c
	${NORMAL_LINT}

mp_machdep.o: $S/amd64/amd64/mp_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mpboot.ln: $S/amd64/amd64/mpboot.S
	${NORMAL_LINT}

mpboot.o: $S/amd64/amd64/mpboot.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

pmap.ln: $S/amd64/amd64/pmap.c
	${NORMAL_LINT}

pmap.o: $S/amd64/amd64/pmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ptrace_machdep.ln: $S/amd64/amd64/ptrace_machdep.c
	${NORMAL_LINT}

ptrace_machdep.o: $S/amd64/amd64/ptrace_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sigtramp.ln: $S/amd64/amd64/sigtramp.S
	${NORMAL_LINT}

sigtramp.o: $S/amd64/amd64/sigtramp.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

stack_machdep.ln: $S/amd64/amd64/stack_machdep.c
	${NORMAL_LINT}

stack_machdep.o: $S/amd64/amd64/stack_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

support.ln: $S/amd64/amd64/support.S
	${NORMAL_LINT}

support.o: $S/amd64/amd64/support.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

sys_machdep.ln: $S/amd64/amd64/sys_machdep.c
	${NORMAL_LINT}

sys_machdep.o: $S/amd64/amd64/sys_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

trap.ln: $S/amd64/amd64/trap.c
	${NORMAL_LINT}

trap.o: $S/amd64/amd64/trap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uio_machdep.ln: $S/amd64/amd64/uio_machdep.c
	${NORMAL_LINT}

uio_machdep.o: $S/amd64/amd64/uio_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uma_machdep.ln: $S/amd64/amd64/uma_machdep.c
	${NORMAL_LINT}

uma_machdep.o: $S/amd64/amd64/uma_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vm_machdep.ln: $S/amd64/amd64/vm_machdep.c
	${NORMAL_LINT}

vm_machdep.o: $S/amd64/amd64/vm_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pci_cfgreg.ln: $S/amd64/pci/pci_cfgreg.c
	${NORMAL_LINT}

pci_cfgreg.o: $S/amd64/pci/pci_cfgreg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_if.ln: $S/dev/acpica/acpi_if.m
	${NORMAL_LINT}

acpi_if.o: $S/dev/acpica/acpi_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

acpi_wmi_if.ln: $S/dev/acpi_support/acpi_wmi_if.m
	${NORMAL_LINT}

acpi_wmi_if.o: $S/dev/acpi_support/acpi_wmi_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

agp_amd64.ln: $S/dev/agp/agp_amd64.c
	${NORMAL_LINT}

agp_amd64.o: $S/dev/agp/agp_amd64.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

agp_i810.ln: $S/dev/agp/agp_i810.c
	${NORMAL_LINT}

agp_i810.o: $S/dev/agp/agp_i810.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

agp_intel.ln: $S/dev/agp/agp_intel.c
	${NORMAL_LINT}

agp_intel.o: $S/dev/agp/agp_intel.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

agp_via.ln: $S/dev/agp/agp_via.c
	${NORMAL_LINT}

agp_via.o: $S/dev/agp/agp_via.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

arcmsr.ln: $S/dev/arcmsr/arcmsr.c
	${NORMAL_LINT}

arcmsr.o: $S/dev/arcmsr/arcmsr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atkbd.ln: $S/dev/atkbdc/atkbd.c
	${NORMAL_LINT}

atkbd.o: $S/dev/atkbdc/atkbd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atkbd_atkbdc.ln: $S/dev/atkbdc/atkbd_atkbdc.c
	${NORMAL_LINT}

atkbd_atkbdc.o: $S/dev/atkbdc/atkbd_atkbdc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atkbdc.ln: $S/dev/atkbdc/atkbdc.c
	${NORMAL_LINT}

atkbdc.o: $S/dev/atkbdc/atkbdc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atkbdc_isa.ln: $S/dev/atkbdc/atkbdc_isa.c
	${NORMAL_LINT}

atkbdc_isa.o: $S/dev/atkbdc/atkbdc_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atkbdc_subr.ln: $S/dev/atkbdc/atkbdc_subr.c
	${NORMAL_LINT}

atkbdc_subr.o: $S/dev/atkbdc/atkbdc_subr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

psm.ln: $S/dev/atkbdc/psm.c
	${NORMAL_LINT}

psm.o: $S/dev/atkbdc/psm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ed_isa.ln: $S/dev/ed/if_ed_isa.c
	${NORMAL_LINT}

if_ed_isa.o: $S/dev/ed/if_ed_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_ed_wd80x3.ln: $S/dev/ed/if_ed_wd80x3.c
	${NORMAL_LINT}

if_ed_wd80x3.o: $S/dev/ed/if_ed_wd80x3.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fb.ln: $S/dev/fb/fb.c
	${NORMAL_LINT}

fb.o: $S/dev/fb/fb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vesa.ln: $S/dev/fb/vesa.c
	${NORMAL_LINT}

vesa.o: $S/dev/fb/vesa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vga.ln: $S/dev/fb/vga.c
	${NORMAL_LINT}

vga.o: $S/dev/fb/vga.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

iodev.ln: $S/dev/io/iodev.c
	${NORMAL_LINT}

iodev.o: $S/dev/io/iodev.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdc.ln: $S/dev/fdc/fdc.c
	${NORMAL_LINT}

fdc.o: $S/dev/fdc/fdc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdc_acpi.ln: $S/dev/fdc/fdc_acpi.c
	${NORMAL_LINT}

fdc_acpi.o: $S/dev/fdc/fdc_acpi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdc_isa.ln: $S/dev/fdc/fdc_isa.c
	${NORMAL_LINT}

fdc_isa.o: $S/dev/fdc/fdc_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

fdc_pccard.ln: $S/dev/fdc/fdc_pccard.c
	${NORMAL_LINT}

fdc_pccard.o: $S/dev/fdc/fdc_pccard.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hpt27xx_os_bsd.ln: $S/dev/hpt27xx/hpt27xx_os_bsd.c
	${NORMAL_LINT}

hpt27xx_os_bsd.o: $S/dev/hpt27xx/hpt27xx_os_bsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hpt27xx_osm_bsd.ln: $S/dev/hpt27xx/hpt27xx_osm_bsd.c
	${NORMAL_LINT}

hpt27xx_osm_bsd.o: $S/dev/hpt27xx/hpt27xx_osm_bsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hpt27xx_config.ln: $S/dev/hpt27xx/hpt27xx_config.c
	${NORMAL_LINT}

hpt27xx_config.o: $S/dev/hpt27xx/hpt27xx_config.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

entry.ln: $S/dev/hptmv/entry.c
	${NORMAL_LINT}

entry.o: $S/dev/hptmv/entry.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mv.ln: $S/dev/hptmv/mv.c
	${NORMAL_LINT}

mv.o: $S/dev/hptmv/mv.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

gui_lib.ln: $S/dev/hptmv/gui_lib.c
	${NORMAL_LINT}

gui_lib.o: $S/dev/hptmv/gui_lib.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hptproc.ln: $S/dev/hptmv/hptproc.c
	${NORMAL_LINT}

hptproc.o: $S/dev/hptmv/hptproc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ioctl.ln: $S/dev/hptmv/ioctl.c
	${NORMAL_LINT}

ioctl.o: $S/dev/hptmv/ioctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hptnr_os_bsd.ln: $S/dev/hptnr/hptnr_os_bsd.c
	${NORMAL_LINT}

hptnr_os_bsd.o: $S/dev/hptnr/hptnr_os_bsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hptnr_osm_bsd.ln: $S/dev/hptnr/hptnr_osm_bsd.c
	${NORMAL_LINT}

hptnr_osm_bsd.o: $S/dev/hptnr/hptnr_osm_bsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hptnr_config.ln: $S/dev/hptnr/hptnr_config.c
	${NORMAL_LINT}

hptnr_config.o: $S/dev/hptnr/hptnr_config.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hptrr_os_bsd.ln: $S/dev/hptrr/hptrr_os_bsd.c
	${NORMAL_LINT}

hptrr_os_bsd.o: $S/dev/hptrr/hptrr_os_bsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hptrr_osm_bsd.ln: $S/dev/hptrr/hptrr_osm_bsd.c
	${NORMAL_LINT}

hptrr_osm_bsd.o: $S/dev/hptrr/hptrr_osm_bsd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hptrr_config.ln: $S/dev/hptrr/hptrr_config.c
	${NORMAL_LINT}

hptrr_config.o: $S/dev/hptrr/hptrr_config.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kbd.ln: $S/dev/kbd/kbd.c
	${NORMAL_LINT}

kbd.o: $S/dev/kbd/kbd.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_nfe.ln: $S/dev/nfe/if_nfe.c
	${NORMAL_LINT}

if_nfe.o: $S/dev/nfe/if_nfe.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ivy.ln: $S/dev/random/ivy.c
	${NORMAL_LINT}

ivy.o: $S/dev/random/ivy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nehemiah.ln: $S/dev/random/nehemiah.c
	${NORMAL_LINT}

nehemiah.o: $S/dev/random/nehemiah.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scterm-teken.ln: $S/dev/syscons/scterm-teken.c
	${NORMAL_LINT}

scterm-teken.o: $S/dev/syscons/scterm-teken.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scvesactl.ln: $S/dev/syscons/scvesactl.c
	${NORMAL_LINT}

scvesactl.o: $S/dev/syscons/scvesactl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scvgarndr.ln: $S/dev/syscons/scvgarndr.c
	${NORMAL_LINT}

scvgarndr.o: $S/dev/syscons/scvgarndr.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scvtb.ln: $S/dev/syscons/scvtb.c
	${NORMAL_LINT}

scvtb.o: $S/dev/syscons/scvtb.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

uart_cpu_amd64.ln: $S/dev/uart/uart_cpu_amd64.c
	${NORMAL_LINT}

uart_cpu_amd64.o: $S/dev/uart/uart_cpu_amd64.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci.ln: $S/dev/isci/isci.c
	${NORMAL_LINT}

isci.o: $S/dev/isci/isci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_controller.ln: $S/dev/isci/isci_controller.c
	${NORMAL_LINT}

isci_controller.o: $S/dev/isci/isci_controller.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_domain.ln: $S/dev/isci/isci_domain.c
	${NORMAL_LINT}

isci_domain.o: $S/dev/isci/isci_domain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_interrupt.ln: $S/dev/isci/isci_interrupt.c
	${NORMAL_LINT}

isci_interrupt.o: $S/dev/isci/isci_interrupt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_io_request.ln: $S/dev/isci/isci_io_request.c
	${NORMAL_LINT}

isci_io_request.o: $S/dev/isci/isci_io_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_logger.ln: $S/dev/isci/isci_logger.c
	${NORMAL_LINT}

isci_logger.o: $S/dev/isci/isci_logger.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_oem_parameters.ln: $S/dev/isci/isci_oem_parameters.c
	${NORMAL_LINT}

isci_oem_parameters.o: $S/dev/isci/isci_oem_parameters.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_remote_device.ln: $S/dev/isci/isci_remote_device.c
	${NORMAL_LINT}

isci_remote_device.o: $S/dev/isci/isci_remote_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_sysctl.ln: $S/dev/isci/isci_sysctl.c
	${NORMAL_LINT}

isci_sysctl.o: $S/dev/isci/isci_sysctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_task_request.ln: $S/dev/isci/isci_task_request.c
	${NORMAL_LINT}

isci_task_request.o: $S/dev/isci/isci_task_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isci_timer.ln: $S/dev/isci/isci_timer.c
	${NORMAL_LINT}

isci_timer.o: $S/dev/isci/isci_timer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati.ln: $S/dev/isci/scil/sati.c
	${NORMAL_LINT}

sati.o: $S/dev/isci/scil/sati.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_abort_task_set.ln: $S/dev/isci/scil/sati_abort_task_set.c
	${NORMAL_LINT}

sati_abort_task_set.o: $S/dev/isci/scil/sati_abort_task_set.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_atapi.ln: $S/dev/isci/scil/sati_atapi.c
	${NORMAL_LINT}

sati_atapi.o: $S/dev/isci/scil/sati_atapi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_device.ln: $S/dev/isci/scil/sati_device.c
	${NORMAL_LINT}

sati_device.o: $S/dev/isci/scil/sati_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_inquiry.ln: $S/dev/isci/scil/sati_inquiry.c
	${NORMAL_LINT}

sati_inquiry.o: $S/dev/isci/scil/sati_inquiry.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_log_sense.ln: $S/dev/isci/scil/sati_log_sense.c
	${NORMAL_LINT}

sati_log_sense.o: $S/dev/isci/scil/sati_log_sense.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_lun_reset.ln: $S/dev/isci/scil/sati_lun_reset.c
	${NORMAL_LINT}

sati_lun_reset.o: $S/dev/isci/scil/sati_lun_reset.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_mode_pages.ln: $S/dev/isci/scil/sati_mode_pages.c
	${NORMAL_LINT}

sati_mode_pages.o: $S/dev/isci/scil/sati_mode_pages.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_mode_select.ln: $S/dev/isci/scil/sati_mode_select.c
	${NORMAL_LINT}

sati_mode_select.o: $S/dev/isci/scil/sati_mode_select.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_mode_sense.ln: $S/dev/isci/scil/sati_mode_sense.c
	${NORMAL_LINT}

sati_mode_sense.o: $S/dev/isci/scil/sati_mode_sense.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_mode_sense_10.ln: $S/dev/isci/scil/sati_mode_sense_10.c
	${NORMAL_LINT}

sati_mode_sense_10.o: $S/dev/isci/scil/sati_mode_sense_10.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_mode_sense_6.ln: $S/dev/isci/scil/sati_mode_sense_6.c
	${NORMAL_LINT}

sati_mode_sense_6.o: $S/dev/isci/scil/sati_mode_sense_6.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_move.ln: $S/dev/isci/scil/sati_move.c
	${NORMAL_LINT}

sati_move.o: $S/dev/isci/scil/sati_move.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_passthrough.ln: $S/dev/isci/scil/sati_passthrough.c
	${NORMAL_LINT}

sati_passthrough.o: $S/dev/isci/scil/sati_passthrough.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_read.ln: $S/dev/isci/scil/sati_read.c
	${NORMAL_LINT}

sati_read.o: $S/dev/isci/scil/sati_read.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_read_buffer.ln: $S/dev/isci/scil/sati_read_buffer.c
	${NORMAL_LINT}

sati_read_buffer.o: $S/dev/isci/scil/sati_read_buffer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_read_capacity.ln: $S/dev/isci/scil/sati_read_capacity.c
	${NORMAL_LINT}

sati_read_capacity.o: $S/dev/isci/scil/sati_read_capacity.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_reassign_blocks.ln: $S/dev/isci/scil/sati_reassign_blocks.c
	${NORMAL_LINT}

sati_reassign_blocks.o: $S/dev/isci/scil/sati_reassign_blocks.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_report_luns.ln: $S/dev/isci/scil/sati_report_luns.c
	${NORMAL_LINT}

sati_report_luns.o: $S/dev/isci/scil/sati_report_luns.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_request_sense.ln: $S/dev/isci/scil/sati_request_sense.c
	${NORMAL_LINT}

sati_request_sense.o: $S/dev/isci/scil/sati_request_sense.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_start_stop_unit.ln: $S/dev/isci/scil/sati_start_stop_unit.c
	${NORMAL_LINT}

sati_start_stop_unit.o: $S/dev/isci/scil/sati_start_stop_unit.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_synchronize_cache.ln: $S/dev/isci/scil/sati_synchronize_cache.c
	${NORMAL_LINT}

sati_synchronize_cache.o: $S/dev/isci/scil/sati_synchronize_cache.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_test_unit_ready.ln: $S/dev/isci/scil/sati_test_unit_ready.c
	${NORMAL_LINT}

sati_test_unit_ready.o: $S/dev/isci/scil/sati_test_unit_ready.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_unmap.ln: $S/dev/isci/scil/sati_unmap.c
	${NORMAL_LINT}

sati_unmap.o: $S/dev/isci/scil/sati_unmap.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_util.ln: $S/dev/isci/scil/sati_util.c
	${NORMAL_LINT}

sati_util.o: $S/dev/isci/scil/sati_util.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_verify.ln: $S/dev/isci/scil/sati_verify.c
	${NORMAL_LINT}

sati_verify.o: $S/dev/isci/scil/sati_verify.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_write.ln: $S/dev/isci/scil/sati_write.c
	${NORMAL_LINT}

sati_write.o: $S/dev/isci/scil/sati_write.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_write_and_verify.ln: $S/dev/isci/scil/sati_write_and_verify.c
	${NORMAL_LINT}

sati_write_and_verify.o: $S/dev/isci/scil/sati_write_and_verify.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_write_buffer.ln: $S/dev/isci/scil/sati_write_buffer.c
	${NORMAL_LINT}

sati_write_buffer.o: $S/dev/isci/scil/sati_write_buffer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sati_write_long.ln: $S/dev/isci/scil/sati_write_long.c
	${NORMAL_LINT}

sati_write_long.o: $S/dev/isci/scil/sati_write_long.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_abstract_list.ln: $S/dev/isci/scil/sci_abstract_list.c
	${NORMAL_LINT}

sci_abstract_list.o: $S/dev/isci/scil/sci_abstract_list.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_controller.ln: $S/dev/isci/scil/sci_base_controller.c
	${NORMAL_LINT}

sci_base_controller.o: $S/dev/isci/scil/sci_base_controller.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_domain.ln: $S/dev/isci/scil/sci_base_domain.c
	${NORMAL_LINT}

sci_base_domain.o: $S/dev/isci/scil/sci_base_domain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_iterator.ln: $S/dev/isci/scil/sci_base_iterator.c
	${NORMAL_LINT}

sci_base_iterator.o: $S/dev/isci/scil/sci_base_iterator.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_library.ln: $S/dev/isci/scil/sci_base_library.c
	${NORMAL_LINT}

sci_base_library.o: $S/dev/isci/scil/sci_base_library.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_logger.ln: $S/dev/isci/scil/sci_base_logger.c
	${NORMAL_LINT}

sci_base_logger.o: $S/dev/isci/scil/sci_base_logger.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_memory_descriptor_list.ln: $S/dev/isci/scil/sci_base_memory_descriptor_list.c
	${NORMAL_LINT}

sci_base_memory_descriptor_list.o: $S/dev/isci/scil/sci_base_memory_descriptor_list.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_memory_descriptor_list_decorator.ln: $S/dev/isci/scil/sci_base_memory_descriptor_list_decorator.c
	${NORMAL_LINT}

sci_base_memory_descriptor_list_decorator.o: $S/dev/isci/scil/sci_base_memory_descriptor_list_decorator.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_object.ln: $S/dev/isci/scil/sci_base_object.c
	${NORMAL_LINT}

sci_base_object.o: $S/dev/isci/scil/sci_base_object.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_observer.ln: $S/dev/isci/scil/sci_base_observer.c
	${NORMAL_LINT}

sci_base_observer.o: $S/dev/isci/scil/sci_base_observer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_phy.ln: $S/dev/isci/scil/sci_base_phy.c
	${NORMAL_LINT}

sci_base_phy.o: $S/dev/isci/scil/sci_base_phy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_port.ln: $S/dev/isci/scil/sci_base_port.c
	${NORMAL_LINT}

sci_base_port.o: $S/dev/isci/scil/sci_base_port.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_remote_device.ln: $S/dev/isci/scil/sci_base_remote_device.c
	${NORMAL_LINT}

sci_base_remote_device.o: $S/dev/isci/scil/sci_base_remote_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_request.ln: $S/dev/isci/scil/sci_base_request.c
	${NORMAL_LINT}

sci_base_request.o: $S/dev/isci/scil/sci_base_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_state_machine.ln: $S/dev/isci/scil/sci_base_state_machine.c
	${NORMAL_LINT}

sci_base_state_machine.o: $S/dev/isci/scil/sci_base_state_machine.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_state_machine_logger.ln: $S/dev/isci/scil/sci_base_state_machine_logger.c
	${NORMAL_LINT}

sci_base_state_machine_logger.o: $S/dev/isci/scil/sci_base_state_machine_logger.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_state_machine_observer.ln: $S/dev/isci/scil/sci_base_state_machine_observer.c
	${NORMAL_LINT}

sci_base_state_machine_observer.o: $S/dev/isci/scil/sci_base_state_machine_observer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_base_subject.ln: $S/dev/isci/scil/sci_base_subject.c
	${NORMAL_LINT}

sci_base_subject.o: $S/dev/isci/scil/sci_base_subject.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

sci_util.ln: $S/dev/isci/scil/sci_util.c
	${NORMAL_LINT}

sci_util.o: $S/dev/isci/scil/sci_util.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_controller.ln: $S/dev/isci/scil/scic_sds_controller.c
	${NORMAL_LINT}

scic_sds_controller.o: $S/dev/isci/scil/scic_sds_controller.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_library.ln: $S/dev/isci/scil/scic_sds_library.c
	${NORMAL_LINT}

scic_sds_library.o: $S/dev/isci/scil/scic_sds_library.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_pci.ln: $S/dev/isci/scil/scic_sds_pci.c
	${NORMAL_LINT}

scic_sds_pci.o: $S/dev/isci/scil/scic_sds_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_phy.ln: $S/dev/isci/scil/scic_sds_phy.c
	${NORMAL_LINT}

scic_sds_phy.o: $S/dev/isci/scil/scic_sds_phy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_port.ln: $S/dev/isci/scil/scic_sds_port.c
	${NORMAL_LINT}

scic_sds_port.o: $S/dev/isci/scil/scic_sds_port.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_port_configuration_agent.ln: $S/dev/isci/scil/scic_sds_port_configuration_agent.c
	${NORMAL_LINT}

scic_sds_port_configuration_agent.o: $S/dev/isci/scil/scic_sds_port_configuration_agent.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_remote_device.ln: $S/dev/isci/scil/scic_sds_remote_device.c
	${NORMAL_LINT}

scic_sds_remote_device.o: $S/dev/isci/scil/scic_sds_remote_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_remote_node_context.ln: $S/dev/isci/scil/scic_sds_remote_node_context.c
	${NORMAL_LINT}

scic_sds_remote_node_context.o: $S/dev/isci/scil/scic_sds_remote_node_context.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_remote_node_table.ln: $S/dev/isci/scil/scic_sds_remote_node_table.c
	${NORMAL_LINT}

scic_sds_remote_node_table.o: $S/dev/isci/scil/scic_sds_remote_node_table.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_request.ln: $S/dev/isci/scil/scic_sds_request.c
	${NORMAL_LINT}

scic_sds_request.o: $S/dev/isci/scil/scic_sds_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_sgpio.ln: $S/dev/isci/scil/scic_sds_sgpio.c
	${NORMAL_LINT}

scic_sds_sgpio.o: $S/dev/isci/scil/scic_sds_sgpio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_smp_remote_device.ln: $S/dev/isci/scil/scic_sds_smp_remote_device.c
	${NORMAL_LINT}

scic_sds_smp_remote_device.o: $S/dev/isci/scil/scic_sds_smp_remote_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_smp_request.ln: $S/dev/isci/scil/scic_sds_smp_request.c
	${NORMAL_LINT}

scic_sds_smp_request.o: $S/dev/isci/scil/scic_sds_smp_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_ssp_request.ln: $S/dev/isci/scil/scic_sds_ssp_request.c
	${NORMAL_LINT}

scic_sds_ssp_request.o: $S/dev/isci/scil/scic_sds_ssp_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_stp_packet_request.ln: $S/dev/isci/scil/scic_sds_stp_packet_request.c
	${NORMAL_LINT}

scic_sds_stp_packet_request.o: $S/dev/isci/scil/scic_sds_stp_packet_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_stp_remote_device.ln: $S/dev/isci/scil/scic_sds_stp_remote_device.c
	${NORMAL_LINT}

scic_sds_stp_remote_device.o: $S/dev/isci/scil/scic_sds_stp_remote_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_stp_request.ln: $S/dev/isci/scil/scic_sds_stp_request.c
	${NORMAL_LINT}

scic_sds_stp_request.o: $S/dev/isci/scil/scic_sds_stp_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scic_sds_unsolicited_frame_control.ln: $S/dev/isci/scil/scic_sds_unsolicited_frame_control.c
	${NORMAL_LINT}

scic_sds_unsolicited_frame_control.o: $S/dev/isci/scil/scic_sds_unsolicited_frame_control.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_controller.ln: $S/dev/isci/scil/scif_sas_controller.c
	${NORMAL_LINT}

scif_sas_controller.o: $S/dev/isci/scil/scif_sas_controller.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_controller_state_handlers.ln: $S/dev/isci/scil/scif_sas_controller_state_handlers.c
	${NORMAL_LINT}

scif_sas_controller_state_handlers.o: $S/dev/isci/scil/scif_sas_controller_state_handlers.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_controller_states.ln: $S/dev/isci/scil/scif_sas_controller_states.c
	${NORMAL_LINT}

scif_sas_controller_states.o: $S/dev/isci/scil/scif_sas_controller_states.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_domain.ln: $S/dev/isci/scil/scif_sas_domain.c
	${NORMAL_LINT}

scif_sas_domain.o: $S/dev/isci/scil/scif_sas_domain.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_domain_state_handlers.ln: $S/dev/isci/scil/scif_sas_domain_state_handlers.c
	${NORMAL_LINT}

scif_sas_domain_state_handlers.o: $S/dev/isci/scil/scif_sas_domain_state_handlers.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_domain_states.ln: $S/dev/isci/scil/scif_sas_domain_states.c
	${NORMAL_LINT}

scif_sas_domain_states.o: $S/dev/isci/scil/scif_sas_domain_states.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_high_priority_request_queue.ln: $S/dev/isci/scil/scif_sas_high_priority_request_queue.c
	${NORMAL_LINT}

scif_sas_high_priority_request_queue.o: $S/dev/isci/scil/scif_sas_high_priority_request_queue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_internal_io_request.ln: $S/dev/isci/scil/scif_sas_internal_io_request.c
	${NORMAL_LINT}

scif_sas_internal_io_request.o: $S/dev/isci/scil/scif_sas_internal_io_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_io_request.ln: $S/dev/isci/scil/scif_sas_io_request.c
	${NORMAL_LINT}

scif_sas_io_request.o: $S/dev/isci/scil/scif_sas_io_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_io_request_state_handlers.ln: $S/dev/isci/scil/scif_sas_io_request_state_handlers.c
	${NORMAL_LINT}

scif_sas_io_request_state_handlers.o: $S/dev/isci/scil/scif_sas_io_request_state_handlers.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_io_request_states.ln: $S/dev/isci/scil/scif_sas_io_request_states.c
	${NORMAL_LINT}

scif_sas_io_request_states.o: $S/dev/isci/scil/scif_sas_io_request_states.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_library.ln: $S/dev/isci/scil/scif_sas_library.c
	${NORMAL_LINT}

scif_sas_library.o: $S/dev/isci/scil/scif_sas_library.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_remote_device.ln: $S/dev/isci/scil/scif_sas_remote_device.c
	${NORMAL_LINT}

scif_sas_remote_device.o: $S/dev/isci/scil/scif_sas_remote_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_remote_device_ready_substate_handlers.ln: $S/dev/isci/scil/scif_sas_remote_device_ready_substate_handlers.c
	${NORMAL_LINT}

scif_sas_remote_device_ready_substate_handlers.o: $S/dev/isci/scil/scif_sas_remote_device_ready_substate_handlers.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_remote_device_ready_substates.ln: $S/dev/isci/scil/scif_sas_remote_device_ready_substates.c
	${NORMAL_LINT}

scif_sas_remote_device_ready_substates.o: $S/dev/isci/scil/scif_sas_remote_device_ready_substates.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_remote_device_starting_substate_handlers.ln: $S/dev/isci/scil/scif_sas_remote_device_starting_substate_handlers.c
	${NORMAL_LINT}

scif_sas_remote_device_starting_substate_handlers.o: $S/dev/isci/scil/scif_sas_remote_device_starting_substate_handlers.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_remote_device_starting_substates.ln: $S/dev/isci/scil/scif_sas_remote_device_starting_substates.c
	${NORMAL_LINT}

scif_sas_remote_device_starting_substates.o: $S/dev/isci/scil/scif_sas_remote_device_starting_substates.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_remote_device_state_handlers.ln: $S/dev/isci/scil/scif_sas_remote_device_state_handlers.c
	${NORMAL_LINT}

scif_sas_remote_device_state_handlers.o: $S/dev/isci/scil/scif_sas_remote_device_state_handlers.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_remote_device_states.ln: $S/dev/isci/scil/scif_sas_remote_device_states.c
	${NORMAL_LINT}

scif_sas_remote_device_states.o: $S/dev/isci/scil/scif_sas_remote_device_states.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_request.ln: $S/dev/isci/scil/scif_sas_request.c
	${NORMAL_LINT}

scif_sas_request.o: $S/dev/isci/scil/scif_sas_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_smp_activity_clear_affiliation.ln: $S/dev/isci/scil/scif_sas_smp_activity_clear_affiliation.c
	${NORMAL_LINT}

scif_sas_smp_activity_clear_affiliation.o: $S/dev/isci/scil/scif_sas_smp_activity_clear_affiliation.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_smp_io_request.ln: $S/dev/isci/scil/scif_sas_smp_io_request.c
	${NORMAL_LINT}

scif_sas_smp_io_request.o: $S/dev/isci/scil/scif_sas_smp_io_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_smp_phy.ln: $S/dev/isci/scil/scif_sas_smp_phy.c
	${NORMAL_LINT}

scif_sas_smp_phy.o: $S/dev/isci/scil/scif_sas_smp_phy.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_smp_remote_device.ln: $S/dev/isci/scil/scif_sas_smp_remote_device.c
	${NORMAL_LINT}

scif_sas_smp_remote_device.o: $S/dev/isci/scil/scif_sas_smp_remote_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_stp_io_request.ln: $S/dev/isci/scil/scif_sas_stp_io_request.c
	${NORMAL_LINT}

scif_sas_stp_io_request.o: $S/dev/isci/scil/scif_sas_stp_io_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_stp_remote_device.ln: $S/dev/isci/scil/scif_sas_stp_remote_device.c
	${NORMAL_LINT}

scif_sas_stp_remote_device.o: $S/dev/isci/scil/scif_sas_stp_remote_device.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_stp_task_request.ln: $S/dev/isci/scil/scif_sas_stp_task_request.c
	${NORMAL_LINT}

scif_sas_stp_task_request.o: $S/dev/isci/scil/scif_sas_stp_task_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_task_request.ln: $S/dev/isci/scil/scif_sas_task_request.c
	${NORMAL_LINT}

scif_sas_task_request.o: $S/dev/isci/scil/scif_sas_task_request.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_task_request_state_handlers.ln: $S/dev/isci/scil/scif_sas_task_request_state_handlers.c
	${NORMAL_LINT}

scif_sas_task_request_state_handlers.o: $S/dev/isci/scil/scif_sas_task_request_state_handlers.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_task_request_states.ln: $S/dev/isci/scil/scif_sas_task_request_states.c
	${NORMAL_LINT}

scif_sas_task_request_states.o: $S/dev/isci/scil/scif_sas_task_request_states.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

scif_sas_timer.ln: $S/dev/isci/scil/scif_sas_timer.c
	${NORMAL_LINT}

scif_sas_timer.o: $S/dev/isci/scil/scif_sas_timer.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio.ln: $S/dev/virtio/virtio.c
	${NORMAL_LINT}

virtio.o: $S/dev/virtio/virtio.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtqueue.ln: $S/dev/virtio/virtqueue.c
	${NORMAL_LINT}

virtqueue.o: $S/dev/virtio/virtqueue.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio_bus_if.ln: $S/dev/virtio/virtio_bus_if.m
	${NORMAL_LINT}

virtio_bus_if.o: $S/dev/virtio/virtio_bus_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

virtio_if.ln: $S/dev/virtio/virtio_if.m
	${NORMAL_LINT}

virtio_if.o: $S/dev/virtio/virtio_if.m
	${NORMAL_M}
	${NORMAL_CTFCONVERT}

virtio_pci.ln: $S/dev/virtio/pci/virtio_pci.c
	${NORMAL_LINT}

virtio_pci.o: $S/dev/virtio/pci/virtio_pci.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

if_vtnet.ln: $S/dev/virtio/network/if_vtnet.c
	${NORMAL_LINT}

if_vtnet.o: $S/dev/virtio/network/if_vtnet.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio_blk.ln: $S/dev/virtio/block/virtio_blk.c
	${NORMAL_LINT}

virtio_blk.o: $S/dev/virtio/block/virtio_blk.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio_balloon.ln: $S/dev/virtio/balloon/virtio_balloon.c
	${NORMAL_LINT}

virtio_balloon.o: $S/dev/virtio/balloon/virtio_balloon.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

virtio_scsi.ln: $S/dev/virtio/scsi/virtio_scsi.c
	${NORMAL_LINT}

virtio_scsi.o: $S/dev/virtio/scsi/virtio_scsi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

syscons_isa.ln: $S/isa/syscons_isa.c
	${NORMAL_LINT}

syscons_isa.o: $S/isa/syscons_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

vga_isa.ln: $S/isa/vga_isa.c
	${NORMAL_LINT}

vga_isa.o: $S/isa/vga_isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

kern_clocksource.ln: $S/kern/kern_clocksource.c
	${NORMAL_LINT}

kern_clocksource.o: $S/kern/kern_clocksource.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

link_elf_obj.ln: $S/kern/link_elf_obj.c
	${NORMAL_LINT}

link_elf_obj.o: $S/kern/link_elf_obj.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ia32_reg.ln: $S/amd64/ia32/ia32_reg.c
	${NORMAL_LINT}

ia32_reg.o: $S/amd64/ia32/ia32_reg.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ia32_signal.ln: $S/amd64/ia32/ia32_signal.c
	${NORMAL_LINT}

ia32_signal.o: $S/amd64/ia32/ia32_signal.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ia32_sigtramp.ln: $S/amd64/ia32/ia32_sigtramp.S
	${NORMAL_LINT}

ia32_sigtramp.o: $S/amd64/ia32/ia32_sigtramp.S
	${NORMAL_S}
	${NORMAL_CTFCONVERT}

ia32_syscall.ln: $S/amd64/ia32/ia32_syscall.c
	${NORMAL_LINT}

ia32_syscall.o: $S/amd64/ia32/ia32_syscall.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ia32_misc.ln: $S/amd64/ia32/ia32_misc.c
	${NORMAL_LINT}

ia32_misc.o: $S/amd64/ia32/ia32_misc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

freebsd32_ioctl.ln: $S/compat/freebsd32/freebsd32_ioctl.c
	${NORMAL_LINT}

freebsd32_ioctl.o: $S/compat/freebsd32/freebsd32_ioctl.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

freebsd32_misc.ln: $S/compat/freebsd32/freebsd32_misc.c
	${NORMAL_LINT}

freebsd32_misc.o: $S/compat/freebsd32/freebsd32_misc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

freebsd32_syscalls.ln: $S/compat/freebsd32/freebsd32_syscalls.c
	${NORMAL_LINT}

freebsd32_syscalls.o: $S/compat/freebsd32/freebsd32_syscalls.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

freebsd32_sysent.ln: $S/compat/freebsd32/freebsd32_sysent.c
	${NORMAL_LINT}

freebsd32_sysent.o: $S/compat/freebsd32/freebsd32_sysent.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

ia32_sysvec.ln: $S/compat/ia32/ia32_sysvec.c
	${NORMAL_LINT}

ia32_sysvec.o: $S/compat/ia32/ia32_sysvec.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

imgact_elf32.ln: $S/kern/imgact_elf32.c
	${NORMAL_LINT}

imgact_elf32.o: $S/kern/imgact_elf32.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memmove.ln: $S/libkern/memmove.c
	${NORMAL_LINT}

memmove.o: $S/libkern/memmove.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

memset.ln: $S/libkern/memset.c
	${NORMAL_LINT}

memset.o: $S/libkern/memset.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

x86bios.ln: $S/compat/x86bios/x86bios.c
	${NORMAL_LINT}

x86bios.o: $S/compat/x86bios/x86bios.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

x86emu.ln: $S/contrib/x86emu/x86emu.c
	${NORMAL_LINT}

x86emu.o: $S/contrib/x86emu/x86emu.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

OsdEnvironment.ln: $S/x86/acpica/OsdEnvironment.c
	${NORMAL_LINT}

OsdEnvironment.o: $S/x86/acpica/OsdEnvironment.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

acpi_apm.ln: $S/x86/acpica/acpi_apm.c
	${NORMAL_LINT}

acpi_apm.o: $S/x86/acpica/acpi_apm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

madt.ln: $S/x86/acpica/madt.c
	${NORMAL_LINT}

madt.o: $S/x86/acpica/madt.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

srat.ln: $S/x86/acpica/srat.c
	${NORMAL_LINT}

srat.o: $S/x86/acpica/srat.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

powernow.ln: $S/x86/cpufreq/powernow.c
	${NORMAL_LINT}

powernow.o: $S/x86/cpufreq/powernow.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

est.ln: $S/x86/cpufreq/est.c
	${NORMAL_LINT}

est.o: $S/x86/cpufreq/est.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

hwpstate.ln: $S/x86/cpufreq/hwpstate.c
	${NORMAL_LINT}

hwpstate.o: $S/x86/cpufreq/hwpstate.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

p4tcc.ln: $S/x86/cpufreq/p4tcc.c
	${NORMAL_LINT}

p4tcc.o: $S/x86/cpufreq/p4tcc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

atrtc.ln: $S/x86/isa/atrtc.c
	${NORMAL_LINT}

atrtc.o: $S/x86/isa/atrtc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

clock.ln: $S/x86/isa/clock.c
	${NORMAL_LINT}

clock.o: $S/x86/isa/clock.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isa.ln: $S/x86/isa/isa.c
	${NORMAL_LINT}

isa.o: $S/x86/isa/isa.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

isa_dma.ln: $S/x86/isa/isa_dma.c
	${NORMAL_LINT}

isa_dma.o: $S/x86/isa/isa_dma.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nmi.ln: $S/x86/isa/nmi.c
	${NORMAL_LINT}

nmi.o: $S/x86/isa/nmi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

orm.ln: $S/x86/isa/orm.c
	${NORMAL_LINT}

orm.o: $S/x86/isa/orm.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

pci_bus.ln: $S/x86/pci/pci_bus.c
	${NORMAL_LINT}

pci_bus.o: $S/x86/pci/pci_bus.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

qpi.ln: $S/x86/pci/qpi.c
	${NORMAL_LINT}

qpi.o: $S/x86/pci/qpi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

busdma_machdep.ln: $S/x86/x86/busdma_machdep.c
	${NORMAL_LINT}

busdma_machdep.o: $S/x86/x86/busdma_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

dump_machdep.ln: $S/x86/x86/dump_machdep.c
	${NORMAL_LINT}

dump_machdep.o: $S/x86/x86/dump_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

intr_machdep.ln: $S/x86/x86/intr_machdep.c
	${NORMAL_LINT}

intr_machdep.o: $S/x86/x86/intr_machdep.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

io_apic.ln: $S/x86/x86/io_apic.c
	${NORMAL_LINT}

io_apic.o: $S/x86/x86/io_apic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

local_apic.ln: $S/x86/x86/local_apic.c
	${NORMAL_LINT}

local_apic.o: $S/x86/x86/local_apic.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

mca.ln: $S/x86/x86/mca.c
	${NORMAL_LINT}

mca.o: $S/x86/x86/mca.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

msi.ln: $S/x86/x86/msi.c
	${NORMAL_LINT}

msi.o: $S/x86/x86/msi.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

nexus.ln: $S/x86/x86/nexus.c
	${NORMAL_LINT}

nexus.o: $S/x86/x86/nexus.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}

tsc.ln: $S/x86/x86/tsc.c
	${NORMAL_LINT}

tsc.o: $S/x86/x86/tsc.c
	${NORMAL_C}
	${NORMAL_CTFCONVERT}


.include "$S/conf/kern.post.mk"
