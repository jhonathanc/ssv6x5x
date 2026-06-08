#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

KSYMTAB_DATA(tu_cfgfirmwarepath, "", "");
KSYMTAB_DATA(tu_ssv_initmac, "", "");
KSYMTAB_DATA(ssv_rx_nr_recvbuff, "", "");
KSYMTAB_DATA(ssv_rx_use_wq, "", "");
KSYMTAB_FUNC(ssv_init_cli, "", "");
KSYMTAB_FUNC(ssv_deinit_cli, "", "");
KSYMTAB_FUNC(tu_ssvdevice_init, "", "");
KSYMTAB_FUNC(tu_ssvdevice_exit, "", "");
KSYMTAB_FUNC(snprintf_res, "", "");
KSYMTAB_DATA(tu_ssv_cfg, "", "");
KSYMTAB_DATA(tu_cfg_cmds, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_hci_deregister, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_hci_register, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_hci_init, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_hci_exit, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_dev_probe, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_dev_remove, "", "");
KSYMTAB_FUNC(ssv6xxx_umac_hci_start, "", "");
KSYMTAB_FUNC(ssv6xxx_umac_test, "", "");
KSYMTAB_FUNC(ssv6xxx_umac_reg_read, "", "");
KSYMTAB_FUNC(ssv6xxx_umac_reg_write, "", "");
KSYMTAB_FUNC(ssv6xxx_umac_tx_frame, "", "");
KSYMTAB_FUNC(ssv6xxx_umac_attach, "", "");
KSYMTAB_FUNC(ssv6xxx_umac_deattach, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_init, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_exit, "", "");
KSYMTAB_FUNC(ssv6xxx_usb_init, "", "");
KSYMTAB_FUNC(ssv6xxx_usb_exit, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_sdio_probe, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_sdio_remove, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_sdio_suspend, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_sdio_resume, "", "");
KSYMTAB_DATA(tu_ssv6xxx_sdio_driver, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_sdio_init, "", "");
KSYMTAB_FUNC(tu_ssv6xxx_sdio_exit, "", "");

MODULE_INFO(depends, "mac80211,cfg80211");

MODULE_ALIAS("platform:SSV6200A");
MODULE_ALIAS("platform:RSV6200A");
MODULE_ALIAS("platform:SSV6006A");
MODULE_ALIAS("platform:SSV6006C");
MODULE_ALIAS("platform:SSV6006D");
MODULE_ALIAS("usb:v8065p6000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("sdio:c*v3030d3030*");
