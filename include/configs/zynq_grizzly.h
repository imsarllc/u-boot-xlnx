/*
 * Configuration settings for the ImSAR Grizzly board
 * See zynq_common.h for Zynq common configs
 */

#ifndef __CONFIG_ZYNQ_GRIZZLY_H
#define __CONFIG_ZYNQ_GRIZZLY_H

#define CONFIG_ZYNQ_PS_CLK_FREQ  50000000UL

#define PHYS_SDRAM_1_SIZE (512 * 1024 * 1024)

#define CONFIG_ZYNQ_SERIAL_UART0
#define CONFIG_ZYNQ_GEM0
#define CONFIG_ZYNQ_GEM_PHY_ADDR0	7

#define CONFIG_SYS_NO_FLASH

#define CONFIG_ZYNQ_SDHCI0
#define CONFIG_ZYNQ_I2C0
#define CONFIG_ZYNQ_EEPROM
#define CONFIG_ZYNQ_BOOT_FREEBSD

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bitsz=0x0109C0F6\0" \
	"bootargs=console=ttyPS0,115200 root=/dev/mmcblk0p2 rw rootwait earlyprintk\0" \
	"clear=sf probe 0 && sf erase 80000 20000\0" \
	"devicetree_image=devicetree.dtb\0" \
	"ethaddr=00:0a:35:00:01:22\0" \
	"fdt_high=0x20000000\0"	\
	"fpga_buff=0x0100000\0" \
	"fpga_offset=0x100000\0" \
	"grizzlyboot=qspiboot reset_qspi_addr sdboot\0" \
	"kernel_image=uImage\0" \
	"load_bit=echo Loading bit file && fpga loadb 0 ${fpga_buff} ${bitsz}\0" \
	"qspiboot=run read_fpga && run load_bit || " \
		"echo FPGA load failed && setenv devicetree_image fallback.dtb\0" \
	"read_fpga=echo Loading FPGA from QSPI && sf probe 0 0 0 && sf read ${fpga_buff} ${fpga_offset} ${bitsz}\0" \
	"reset_qspi_addr=sf probe 0 0 0 && sf read 0x0100000 0x100000 1" \
	"sdboot=echo Copying Linux from SD to RAM... && " \
		"mmcinfo && " \
		"fatload mmc 0 0x3000000 ${kernel_image} && " \
		"fatload mmc 0 0x2A00000 ${devicetree_image} && " \
		"bootm 0x3000000 - 0x2A00000\0"

#include <configs/zynq-common.h>

#undef  CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND		"run $grizzlyboot"

#endif /* __CONFIG_ZYNQ_GRIZZLY_H */
