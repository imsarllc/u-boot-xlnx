/*
 * (C) Copyright 2013 Xilinx, Inc.
 *
 * Configuration for Micro Zynq Evaluation and Development Board - MicroZedBoard
 * See zynq-common.h for Zynq common configs
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQ_MICROZED_H
#define __CONFIG_ZYNQ_MICROZED_H

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootargs=console=ttyPS0,115200 root=/dev/mmcblk0p2 rw rootwait \0" \
	"ethaddr=00:0a:35:00:01:22\0" \
	"fdt_high=0x20000000\0"	\
	"devicetree_image=devicetree.dtb\0" \
	"kernel_image=uImage\0" \
	"kernel_size=0x500000\0"	\
	"devicetree_size=0x20000\0"	\
	"ramdisk_size=0x5E0000\0"	\
	"qspiboot=echo Copying Linux from QSPI flash to RAM... && " \
		"sf probe 0 0 0 && " \
		"sf read 0x3000000 0x100000 ${kernel_size} && " \
		"sf read 0x2A00000 0x600000 ${devicetree_size} && " \
		"echo Copying ramdisk... && " \
		"sf read 0x2000000 0x620000 ${ramdisk_size} && " \
		"bootm 0x3000000 0x2000000 0x2A00000\0" \
	"sdboot=echo Copying Linux from SD to RAM... && " \
		"mmcinfo && " \
		"fatload mmc 0 0x3000000 ${kernel_image} && " \
		"fatload mmc 0 0x2A00000 ${devicetree_image} && " \
		"bootm 0x3000000 - 0x2A00000\0" \
	"bitstream_image=fpga.bit\0" \
	"bootcmd=run mmc_loadbit_fat; run sdboot\0" \
	"loadbit_addr=0x100000\0" \
	"mmc_loadbit_fat=echo \"Loading bitstream from SD/MMC/eMMC to RAM..\" && " \
		"mmcinfo && fatload mmc 0 ${loadbit_addr} ${bitstream_image} && " \
		"fpga loadb 0 ${loadbit_addr} ${filesize}\0"
 
#include <configs/zynq-common.h>

#endif /* __CONFIG_ZYNQ_MICROZED_H */
