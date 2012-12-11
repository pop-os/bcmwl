/*
 * Forward declarations for commonly used wl driver structs
 *
 * Copyright (C) 2011, Broadcom Corporation. All Rights Reserved.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id: wlc_types.h 266255 2011-06-13 20:18:59Z $
 */

#ifndef _wlc_types_h_
#define _wlc_types_h_

typedef struct wlc_info wlc_info_t;
typedef struct wlc_if wlc_if_t;
typedef struct wl_if wl_if_t;
typedef struct led_info led_info_t;
typedef struct bmac_led bmac_led_t;
typedef struct bmac_led_info bmac_led_info_t;
typedef struct seq_cmds_info wlc_seq_cmds_info_t;
typedef struct wlc_ccx ccx_t;
typedef struct wlc_ccx_rm ccx_rm_t;
typedef struct apps_wlc_psinfo apps_wlc_psinfo_t;
typedef struct scb_module scb_module_t;
typedef struct ba_info ba_info_t;
typedef struct wlc_frminfo wlc_frminfo_t;
typedef struct amsdu_info amsdu_info_t;
typedef struct cram_info cram_info_t;
typedef struct wlc_extlog_info wlc_extlog_info_t;
typedef struct wlc_txq_info wlc_txq_info_t;
typedef struct _wlc_hwtimer_to wlc_hwtimer_to_t;
typedef struct wlc_cac wlc_cac_t;
typedef struct ampdu_info ampdu_info_t;
typedef struct ratesel_info ratesel_info_t;
typedef struct wlc_ap_info wlc_ap_info_t;
typedef struct wlc_scan_info wlc_scan_info_t;
typedef struct dpt_info dpt_info_t;
typedef struct tdls_info tdls_info_t;
typedef struct wlc_auth_info wlc_auth_info_t;
typedef struct wowl_info wowl_info_t;
typedef struct wlc_plt_info wlc_plt_pub_t;
typedef struct supplicant supplicant_t;
typedef struct authenticator authenticator_t;
typedef struct antsel_info antsel_info_t;
typedef struct lmac_info lmac_info_t;
typedef struct bmac_pmq bmac_pmq_t;
typedef struct wlc_rrm_info wlc_rrm_info_t;
typedef struct rm_info rm_info_t;

struct d11init;

#ifndef _hnddma_pub_
#define _hnddma_pub_
typedef const struct hnddma_pub hnddma_t;
#endif 

typedef struct wlc_dpc_info wlc_dpc_info_t;

typedef struct wlc_11h_info wlc_11h_info_t;
typedef struct wlc_tpc_info wlc_tpc_info_t;
typedef struct wlc_csa_info wlc_csa_info_t;
typedef struct wlc_quiet_info wlc_quiet_info_t;

typedef struct wlc_11d_info wlc_11d_info_t;
typedef struct wlc_cntry_info wlc_cntry_info_t;

typedef struct wlc_dfs_info wlc_dfs_info_t;

typedef struct bsscfg_module bsscfg_module_t;

#endif	
