/*
 * Kernel compatibility helpers for the vendor SSV mac80211 driver.
 */

#ifndef _SSV_KERNEL_COMPAT_H_
#define _SSV_KERNEL_COMPAT_H_

#include <linux/version.h>

#ifndef MODULE_SUPPORTED_DEVICE
#define MODULE_SUPPORTED_DEVICE(_device)
#endif

/*
 * Linux 6.0 split interface-wide state out of struct ieee80211_bss_conf
 * into struct ieee80211_vif_cfg and moved STA HT capabilities to deflink.
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
#define SSV_VIF_ASSOC(_vif) ((_vif)->cfg.assoc)
#define SSV_VIF_AID(_vif) ((_vif)->cfg.aid)
#define SSV_BSS_ASSOC(_vif, _info) ((_vif)->cfg.assoc)
#define SSV_BSS_AID(_vif, _info) ((_vif)->cfg.aid)
#define SSV_STA_HT_CAP(_sta) ((_sta)->deflink.ht_cap)
#define SSV_MAC80211_CONF_TX_HAS_LINK_ID 1
#else
#define SSV_VIF_ASSOC(_vif) ((_vif)->bss_conf.assoc)
#define SSV_VIF_AID(_vif) ((_vif)->bss_conf.aid)
#define SSV_BSS_ASSOC(_vif, _info) ((_info)->assoc)
#define SSV_BSS_AID(_vif, _info) ((_info)->aid)
#define SSV_STA_HT_CAP(_sta) ((_sta)->ht_cap)
#define SSV_MAC80211_CONF_TX_HAS_LINK_ID 0
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 12, 0)
#define SSV_MAC80211_STOP_HAS_SUSPEND 1
#else
#define SSV_MAC80211_STOP_HAS_SUSPEND 0
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 18, 0)
#define SSV_MAC80211_CONFIG_HAS_RADIO_IDX 1
#define SSV_BSS_CHANGED_TYPE u64
#else
#define SSV_MAC80211_CONFIG_HAS_RADIO_IDX 0
#define SSV_BSS_CHANGED_TYPE u32
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
#define SSV_PROC_DATA(_inode) pde_data(_inode)
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0)
#define SSV_PROC_DATA(_inode) PDE_DATA(_inode)
#else
#define SSV_PROC_DATA(_inode) ({ \
	struct proc_dir_entry *_dp = PDE(_inode); \
	_dp->data; \
})
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 2, 0)
#define SSV_TIMER_DELETE_SYNC(_timer) timer_delete_sync(_timer)
#else
#define SSV_TIMER_DELETE_SYNC(_timer) del_timer_sync(_timer)
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0)
#define SSV_PLATFORM_REMOVE_RET void
#define SSV_PLATFORM_REMOVE_RETURN return
#else
#define SSV_PLATFORM_REMOVE_RET int
#define SSV_PLATFORM_REMOVE_RETURN return 0
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 18, 0)
#define SSV_FROM_TIMER(_var, _timer, _field) timer_container_of(_var, _timer, _field)
#define SSV_IEEE80211_TX_STATUS(_hw, _skb) ieee80211_tx_status_skb(_hw, _skb)
#define SSV_IEEE80211_BEACON_GET_TIM(_hw, _vif, _tim_offset, _tim_length) \
	ieee80211_beacon_get_tim(_hw, _vif, _tim_offset, _tim_length, 0)
#define SSV_USB_DRIVER_DEVICE_DRIVER(_driver) (&(_driver)->driver)
#else
#define SSV_FROM_TIMER(_var, _timer, _field) from_timer(_var, _timer, _field)
#define SSV_IEEE80211_TX_STATUS(_hw, _skb) ieee80211_tx_status(_hw, _skb)
#define SSV_IEEE80211_BEACON_GET_TIM(_hw, _vif, _tim_offset, _tim_length) \
	ieee80211_beacon_get_tim(_hw, _vif, _tim_offset, _tim_length)
#define SSV_USB_DRIVER_DEVICE_DRIVER(_driver) (&(_driver)->drvwrap.driver)
#endif

#ifdef IEEE80211_MAX_AMPDU_BUF
#define SSV_IEEE80211_MAX_AMPDU_BUF IEEE80211_MAX_AMPDU_BUF
#elif defined(IEEE80211_MAX_AMPDU_BUF_HT)
#define SSV_IEEE80211_MAX_AMPDU_BUF IEEE80211_MAX_AMPDU_BUF_HT
#else
#define SSV_IEEE80211_MAX_AMPDU_BUF 0x40
#endif

#ifdef RX_FLAG_HT
#define SSV_RX_STATUS_HT(_rxs) ((_rxs)->flag |= RX_FLAG_HT)
#else
#define SSV_RX_STATUS_HT(_rxs) ((_rxs)->encoding = RX_ENC_HT)
#endif

#ifdef RX_FLAG_40MHZ
#define SSV_RX_STATUS_40MHZ(_rxs) ((_rxs)->flag |= RX_FLAG_40MHZ)
#else
#define SSV_RX_STATUS_40MHZ(_rxs) ((_rxs)->bw = RATE_INFO_BW_40)
#endif

#ifdef RX_FLAG_SHORT_GI
#define SSV_RX_STATUS_SHORT_GI(_rxs) ((_rxs)->flag |= RX_FLAG_SHORT_GI)
#else
#define SSV_RX_STATUS_SHORT_GI(_rxs) ((_rxs)->enc_flags |= RX_ENC_FLAG_SHORT_GI)
#endif

#ifdef RX_FLAG_SHORTPRE
#define SSV_RX_STATUS_SHORTPRE(_rxs) ((_rxs)->flag |= RX_FLAG_SHORTPRE)
#else
#define SSV_RX_STATUS_SHORTPRE(_rxs) ((_rxs)->enc_flags |= RX_ENC_FLAG_SHORTPRE)
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 14, 0)
#define SSV_KERNEL_READ(_file, _buf, _len) \
	kernel_read((_file), (_buf), (_len), &((_file)->f_pos))
#define SSV_KERNEL_WRITE(_file, _buf, _len) \
	kernel_write((_file), (_buf), (_len), &((_file)->f_pos))
#else
#define SSV_KERNEL_READ(_file, _buf, _len) \
	kernel_read((_file), (_file)->f_pos, (_buf), (_len))
#define SSV_KERNEL_WRITE(_file, _buf, _len) \
	((_file)->f_op->write((_file), (_buf), (_len), &((_file)->f_pos)))
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 0, 0)
#define SSV_RATE_ALLOC_ARGS struct ieee80211_hw *hw
#define SSV_RATE_ALLOC_UNUSED_DEBUGFS
#else
#define SSV_RATE_ALLOC_ARGS struct ieee80211_hw *hw, struct dentry *debugfsdir
#define SSV_RATE_ALLOC_UNUSED_DEBUGFS (void)debugfsdir
#endif

static inline bool SSV_RATE_CONTROL_SEND_LOW(struct ieee80211_sta *sta,
					     void *priv_sta,
					     struct ieee80211_tx_rate_control *txrc)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)txrc->skb->data;
	struct ieee80211_tx_rate *rates = info->control.rates;
	u32 rate_idx_mask = txrc->rate_idx_mask;
	int i, rate_idx = 0;

	if (sta && priv_sta && ieee80211_is_data(hdr->frame_control) &&
	    !(info->flags & IEEE80211_TX_CTL_NO_ACK))
		return false;

	if (txrc->sband) {
		rate_idx = rate_lowest_index(txrc->sband, sta);
		if (rate_idx_mask) {
			for (i = 0; i < txrc->sband->n_bitrates; i++) {
				if ((rate_idx_mask & BIT(i)) &&
				    rate_supported(sta, txrc->sband->band, i)) {
					rate_idx = i;
					break;
				}
			}
		}
	}

	rates[0].idx = rate_idx;
	rates[0].flags = 0;
	if (txrc->short_preamble)
		rates[0].flags |= IEEE80211_TX_RC_USE_SHORT_PREAMBLE;
	rates[0].count = (info->flags & IEEE80211_TX_CTL_NO_ACK) ? 1 :
			 max_t(int, 1, txrc->hw->max_rate_tries);

	for (i = 1; i < IEEE80211_TX_MAX_RATES; i++) {
		rates[i].idx = -1;
		rates[i].count = 0;
		rates[i].flags = 0;
	}

	return true;
}

#endif /* _SSV_KERNEL_COMPAT_H_ */
