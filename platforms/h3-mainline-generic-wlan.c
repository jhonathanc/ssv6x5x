/*
 * Mainline Armbian wrapper for the vendor one-Module SSV6x5x build.
 *
 * Power sequencing and SDIO card-detect are handled by the board device tree
 * and the MMC stack on mainline kernels.
 */

#include <linux/delay.h>
#include <linux/module.h>
#include <linux/printk.h>

extern int tu_ssvdevice_init(void);
extern void tu_ssvdevice_exit(void);

static int g_wifidev_registered;

int initWlan(void)
{
	int ret;

	msleep(150);
	ret = tu_ssvdevice_init();
	if (!ret)
		g_wifidev_registered = 1;

	return ret;
}

void exitWlan(void)
{
	if (g_wifidev_registered) {
		tu_ssvdevice_exit();
		g_wifidev_registered = 0;
	}
}

static int __init tu_generic_wifi_init_module(void)
{
	pr_info("%s\n", __func__);
	return initWlan();
}

static void __exit tu_generic_wifi_exit_module(void)
{
	msleep(100);
	exitWlan();
}

module_init(tu_generic_wifi_init_module);
module_exit(tu_generic_wifi_exit_module);

MODULE_LICENSE("Dual BSD/GPL");
