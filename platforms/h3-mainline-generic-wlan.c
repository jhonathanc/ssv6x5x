/*
 * Copyright (c) 2015 iComm-semi Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/version.h>
#include <linux/module.h>
#include <linux/delay.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 0, 0))
#include <linux/printk.h>
#else
#include <config/printk.h>
#endif

static int g_wifidev_registered = 0;
extern int tu_ssvdevice_init(void);
extern void tu_ssvdevice_exit(void);
#ifdef CONFIG_SSV_SUPPORT_AES_ASM
extern int aes_init(void);
extern void aes_fini(void);
extern int sha1_mod_init(void);
extern void sha1_mod_fini(void);
#endif

int initWlan(void)
{
    int ret = 0;

    ret = tu_ssvdevice_init();
    if (!ret)
        g_wifidev_registered = 1;

    return ret;
}

void exitWlan(void)
{
    if (g_wifidev_registered) {
        tu_ssvdevice_exit();
        msleep(50);
        g_wifidev_registered = 0;
    }
    return;
}

static __init int tu_generic_wifi_init_module(void)
{
    int ret;

    printk(KERN_INFO "ssv6x5x: init generic H3/mainline wrapper\n");
#ifdef CONFIG_SSV_SUPPORT_AES_ASM
    sha1_mod_init();
    aes_init();
#endif
    ret = initWlan();
#ifdef CONFIG_SSV_SUPPORT_AES_ASM
    if (ret) {
        aes_fini();
        sha1_mod_fini();
    }
#endif
    return ret;
}

static __exit void tu_generic_wifi_exit_module(void)
{
    printk(KERN_INFO "ssv6x5x: exit generic H3/mainline wrapper\n");
    exitWlan();
#ifdef CONFIG_SSV_SUPPORT_AES_ASM
    aes_fini();
    sha1_mod_fini();
#endif
}

EXPORT_SYMBOL(tu_generic_wifi_init_module);
EXPORT_SYMBOL(tu_generic_wifi_exit_module);
module_init(tu_generic_wifi_init_module);
module_exit(tu_generic_wifi_exit_module);

MODULE_LICENSE("Dual BSD/GPL");
