/*
 * Custom OID/ioctl definitions for
 * Broadcom 802.11abg Networking Device Driver
 *
 * Definitions subject to change without notice.
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
 * $Id: wlioctl.h 286249 2011-09-27 01:39:42Z $
 */

#ifndef _wlioctl_h_
#define	_wlioctl_h_

#include <typedefs.h>
#include <proto/ethernet.h>
#include <proto/bcmevent.h>
#include <proto/802.11.h>
#include <bcmwifi.h>

#ifndef INTF_NAME_SIZ
#define INTF_NAME_SIZ	16
#endif

#define BWL_DEFAULT_PACKING

#include <packed_section_start.h>

#define	LEGACY2_WL_BSS_INFO_VERSION	108		

typedef struct wl_bss_info_108 {
	uint32		version;		
	uint32		length;			
	struct ether_addr BSSID;
	uint16		beacon_period;		
	uint16		capability;		
	uint8		SSID_len;
	uint8		SSID[32];
	struct {
		uint	count;			
		uint8	rates[16];		
	} rateset;				
	chanspec_t	chanspec;		
	uint16		atim_window;		
	uint8		dtim_period;		
	int16		RSSI;			
	int8		phy_noise;		

	uint8		n_cap;			
	uint32		nbss_cap;		
	uint8		ctl_ch;			
	uint32		reserved32[1];		
	uint8		flags;			
	uint8		reserved[3];		
	uint8		basic_mcs[MCSSET_LEN];	

	uint16		ie_offset;		
	uint32		ie_length;		

} wl_bss_info_108_t;

#define	WL_BSS_INFO_VERSION	109		

typedef struct wl_bss_info {
	uint32		version;		
	uint32		length;			
	struct ether_addr BSSID;
	uint16		beacon_period;		
	uint16		capability;		
	uint8		SSID_len;
	uint8		SSID[32];
	struct {
		uint	count;			
		uint8	rates[16];		
	} rateset;				
	chanspec_t	chanspec;		
	uint16		atim_window;		
	uint8		dtim_period;		
	int16		RSSI;			
	int8		phy_noise;		

	uint8		n_cap;			
	uint32		nbss_cap;		
	uint8		ctl_ch;			
	uint32		reserved32[1];		
	uint8		flags;			
	uint8		reserved[3];		
	uint8		basic_mcs[MCSSET_LEN];	

	uint16		ie_offset;		
	uint32		ie_length;		
	int16		SNR;			

} wl_bss_info_t;

typedef struct wl_bsscfg {
	uint32	wsec;
	uint32	WPA_auth;
	uint32	wsec_index;
	uint32	associated;
	uint32	BSS;
	uint32	phytest_on;
	struct ether_addr	prev_BSSID;
	struct ether_addr	BSSID;
} wl_bsscfg_t;

typedef struct wl_bss_config {
	uint32	atim_window;
	uint32	beacon_period;
	uint32	chanspec;
} wl_bss_config_t;

#define DLOAD_HANDLER_VER			1	
#define DLOAD_FLAG_VER_MASK		0xf000	
#define DLOAD_FLAG_VER_SHIFT	12	

#define DL_CRC_NOT_INUSE 			0x0001

enum {
	DL_TYPE_UCODE = 1,
	DL_TYPE_CLM = 2
};

enum {
	UCODE_FW,
	INIT_VALS,
	BS_INIT_VALS
};

struct wl_dload_data {
	uint16 flag;
	uint16 dload_type;
	uint32 len;
	uint32 crc;
	uint8  data[1];
};
typedef struct wl_dload_data wl_dload_data_t;

struct wl_ucode_info {
	uint32 ucode_type;
	uint32 num_chunks;
	uint32 chunk_len;
	uint32 chunk_num;
	uint8  data_chunk[1];
};
typedef struct wl_ucode_info wl_ucode_info_t;

struct wl_clm_dload_info {
	uint32 ds_id;
	uint32 clm_total_len;
	uint32 num_chunks;
	uint32 chunk_len;
	uint32 chunk_offset;
	uint8  data_chunk[1];
};
typedef struct wl_clm_dload_info wl_clm_dload_info_t;

typedef struct wlc_ssid {
	uint32		SSID_len;
	uchar		SSID[32];
} wlc_ssid_t;

#define WL_BSSTYPE_INFRA 1
#define WL_BSSTYPE_INDEP 0
#define WL_BSSTYPE_ANY   2

typedef struct wl_scan_params_hyb {
	wlc_ssid_t ssid;		
	struct ether_addr bssid;
	int8 bss_type;
	uint8 scan_type;		
	int32 pad2;			
	int32 pad3;			
	int32 pad4;			
	int32 pad5;			
	int32 pad6;
	uint16 pad7[1];			
} wl_scan_params_hyb_t;

typedef struct wl_scan_results {
	uint32 buflen;
	uint32 version;
	uint32 count;
	wl_bss_info_t bss_info[1];
} wl_scan_results_t;

#define WL_SCAN_RESULTS_FIXED_SIZE (sizeof(wl_scan_results_t) - sizeof(wl_bss_info_t))

#define WL_SCAN_RESULTS_SUCCESS	0
#define WL_SCAN_RESULTS_PARTIAL	1
#define WL_SCAN_RESULTS_PENDING	2
#define WL_SCAN_RESULTS_ABORTED	3

typedef struct wl_probe_params {
	wlc_ssid_t ssid;
	struct ether_addr bssid;
	struct ether_addr mac;
} wl_probe_params_t;

#define WL_NUMRATES		16	
typedef struct wl_rateset {
	uint32	count;			
	uint8	rates[WL_NUMRATES];	
} wl_rateset_t;

typedef struct wl_rateset_args {
	uint32	count;			
	uint8	rates[WL_NUMRATES];	
	uint8   mcs[MCSSET_LEN];        
} wl_rateset_args_t;

typedef struct wl_uint32_list {

	uint32 count;

	uint32 element[1];
} wl_uint32_list_t;

typedef struct wl_assoc_params {
	struct ether_addr bssid;	
	int32 chanspec_num;		
	chanspec_t chanspec_list[1];	
} wl_assoc_params_t;
#define WL_ASSOC_PARAMS_FIXED_SIZE 	OFFSETOF(wl_assoc_params_t, chanspec_list)

typedef wl_assoc_params_t wl_reassoc_params_t;
#define WL_REASSOC_PARAMS_FIXED_SIZE	WL_ASSOC_PARAMS_FIXED_SIZE

typedef wl_assoc_params_t wl_join_assoc_params_t;
#define WL_JOIN_ASSOC_PARAMS_FIXED_SIZE	WL_ASSOC_PARAMS_FIXED_SIZE

typedef struct wl_join_params {
	wlc_ssid_t ssid;
	wl_assoc_params_t params;	
} wl_join_params_t;
#define WL_JOIN_PARAMS_FIXED_SIZE 	(OFFSETOF(wl_join_params_t, params) + \
					 WL_ASSOC_PARAMS_FIXED_SIZE)

#define WLC_CNTRY_BUF_SZ	4		

typedef struct wl_country {
	char country_abbrev[WLC_CNTRY_BUF_SZ];	
	int32 rev;				
	char ccode[WLC_CNTRY_BUF_SZ];		
} wl_country_t;

#define	CRYPTO_ALGO_OFF			0
#define	CRYPTO_ALGO_WEP1		1
#define	CRYPTO_ALGO_TKIP		2
#define	CRYPTO_ALGO_WEP128		3
#define CRYPTO_ALGO_AES_CCM		4
#define CRYPTO_ALGO_AES_OCB_MSDU	5
#define CRYPTO_ALGO_AES_OCB_MPDU	6
#define CRYPTO_ALGO_NALG		7
#define CRYPTO_ALGO_PMK			12	

#define WSEC_GEN_MIC_ERROR	0x0001
#define WSEC_GEN_REPLAY		0x0002
#define WSEC_GEN_ICV_ERROR	0x0004
#define WSEC_GEN_MFP_ACT_ERROR	0x0008
#define WSEC_GEN_MFP_DISASSOC_ERROR	0x0010
#define WSEC_GEN_MFP_DEAUTH_ERROR	0x0020

#define WL_SOFT_KEY	(1 << 0)	
#define WL_PRIMARY_KEY	(1 << 1)	
#define WL_KF_RES_4	(1 << 4)	
#define WL_KF_RES_5	(1 << 5)	
#define WL_IBSS_PEER_GROUP_KEY	(1 << 6)	

typedef struct wl_wsec_key {
	uint32		index;		
	uint32		len;		
	uint8		data[DOT11_MAX_KEY_SIZE];	
	uint32		pad_1[18];
	uint32		algo;		
	uint32		flags;		
	uint32		pad_2[2];
	int		pad_3;
	int		iv_initialized;	
	int		pad_4;

	struct {
		uint32	hi;		
		uint16	lo;		
	} rxiv;
	uint32		pad_5[2];
	struct ether_addr ea;		
} wl_wsec_key_t;

#define WSEC_MIN_PSK_LEN	8
#define WSEC_MAX_PSK_LEN	64

#define WSEC_PASSPHRASE		(1<<0)

typedef struct {
	ushort	key_len;		
	ushort	flags;			
	uint8	key[WSEC_MAX_PSK_LEN];	
} wsec_pmk_t;

#define WEP_ENABLED		0x0001
#define TKIP_ENABLED		0x0002
#define AES_ENABLED		0x0004
#define WSEC_SWFLAG		0x0008
#define SES_OW_ENABLED		0x0040	

#define WSEC_WEP_ENABLED(wsec)	((wsec) & WEP_ENABLED)
#define WSEC_TKIP_ENABLED(wsec)	((wsec) & TKIP_ENABLED)
#define WSEC_AES_ENABLED(wsec)	((wsec) & AES_ENABLED)

#define WSEC_ENABLED(wsec)	((wsec) & (WEP_ENABLED | TKIP_ENABLED | AES_ENABLED))
#define WSEC_SES_OW_ENABLED(wsec)	((wsec) & SES_OW_ENABLED)

#define WPA_AUTH_DISABLED	0x0000	
#define WPA_AUTH_NONE		0x0001	
#define WPA_AUTH_UNSPECIFIED	0x0002	
#define WPA_AUTH_PSK		0x0004	

#define WPA2_AUTH_UNSPECIFIED	0x0040	
#define WPA2_AUTH_PSK		0x0080	
#define WPA2_AUTH_MFP           0x1000  
#define WPA2_AUTH_TPK		0x2000 	

#define WPA_AUTH_PFN_ANY	0xffffffff	

#define	MAXPMKID		16

typedef struct _pmkid {
	struct ether_addr	BSSID;
	uint8			PMKID[WPA2_PMKID_LEN];
} pmkid_t;

typedef struct _pmkid_list {
	uint32	npmkid;
	pmkid_t	pmkid[1];
} pmkid_list_t;

typedef struct _pmkid_cand {
	struct ether_addr	BSSID;
	uint8			preauth;
} pmkid_cand_t;

typedef struct _pmkid_cand_list {
	uint32	npmkid_cand;
	pmkid_cand_t	pmkid_cand[1];
} pmkid_cand_list_t;

typedef struct {
	uint32	val;
	struct ether_addr ea;
} scb_val_t;

typedef struct {
	uint32 code;
	scb_val_t ioctl_args;
} authops_t;

typedef struct channel_info {
	int hw_channel;
	int target_channel;
	int scan_channel;
} channel_info_t;

struct maclist {
	uint count;			
	struct ether_addr ea[1];	
};

typedef struct get_pktcnt {
	uint rx_good_pkt;
	uint rx_bad_pkt;
	uint tx_good_pkt;
	uint tx_bad_pkt;
	uint rx_ocast_good_pkt; 
} get_pktcnt_t;

#define LQ_IDX_MIN              0
#define LQ_IDX_MAX              1
#define LQ_IDX_AVG              2
#define LQ_IDX_SUM              2
#define LQ_IDX_LAST             3
#define LQ_STOP_MONITOR         0
#define LQ_START_MONITOR        1

typedef struct {
	int rssi[LQ_IDX_LAST];  
	int snr[LQ_IDX_LAST];   
	int isvalid;            
} wl_lq_t; 

#define MCS_INDEX_SIZE                  33

typedef enum wl_wakeup_reason_type {
	LCD_ON = 1,
	LCD_OFF,
	DRC1_WAKE,
	DRC2_WAKE,
	REASON_LAST
} wl_wr_type_t;

typedef struct {

	uint32	id;

	uint8	reason;
} wl_wr_t;

typedef struct {
	struct	ether_addr ea;	
	uint8	ac_cat;	
	uint8	num_pkts;	
} wl_mac_ratehisto_cmd_t;	

typedef struct {
	uint32	rate[WLC_MAXRATE + 1];	
	uint32	mcs_index[MCS_INDEX_SIZE];	
	uint32	tsf_timer[2][2];	
} wl_mac_ratehisto_res_t;	

#define WLC_TXFILTER_OVERRIDE_DISABLED  0
#define WLC_TXFILTER_OVERRIDE_ENABLED   1

#define WL_IOCTL_ACTION_GET				0x0
#define WL_IOCTL_ACTION_SET				0x1
#define WL_IOCTL_ACTION_OVL_IDX_MASK	0x1e
#define WL_IOCTL_ACTION_OVL_RSV			0x20
#define WL_IOCTL_ACTION_OVL				0x40
#define WL_IOCTL_ACTION_MASK			0x7e
#define WL_IOCTL_ACTION_OVL_SHIFT		1

typedef struct wl_ioctl {
	uint cmd;	
	void *buf;	
	uint len;	
	uint8 set;	
	uint used;	
	uint needed;	
} wl_ioctl_t;

#define ioctl_subtype	set		
#define ioctl_pid	used		
#define ioctl_status	needed		

#define WLC_IOCTL_MAGIC		0x14e46c77

#define WLC_IOCTL_VERSION	1

#define	WLC_IOCTL_MAXLEN		8192	
#define	WLC_IOCTL_SMLEN			256	
#define WLC_IOCTL_MEDLEN		1536    
#define WLC_SAMPLECOLLECT_MAXLEN	10240	

#define WLC_GET_MAGIC				0
#define WLC_GET_VERSION				1
#define WLC_UP					2
#define WLC_DOWN				3
#define WLC_GET_LOOP				4
#define WLC_SET_LOOP				5
#define WLC_DUMP				6
#define WLC_GET_MSGLEVEL			7
#define WLC_SET_MSGLEVEL			8
#define WLC_GET_PROMISC				9
#define WLC_SET_PROMISC				10

#define WLC_GET_RATE				12
#define WLC_GET_MAX_RATE			13
#define WLC_GET_INSTANCE			14

#define WLC_GET_INFRA				19
#define WLC_SET_INFRA				20
#define WLC_GET_AUTH				21
#define WLC_SET_AUTH				22
#define WLC_GET_BSSID				23
#define WLC_SET_BSSID				24
#define WLC_GET_SSID				25
#define WLC_SET_SSID				26
#define WLC_RESTART				27

#define WLC_GET_CHANNEL				29
#define WLC_SET_CHANNEL				30
#define WLC_GET_SRL				31
#define WLC_SET_SRL				32
#define WLC_GET_LRL				33
#define WLC_SET_LRL				34
#define WLC_GET_PLCPHDR				35
#define WLC_SET_PLCPHDR				36
#define WLC_GET_RADIO				37
#define WLC_SET_RADIO				38
#define WLC_GET_PHYTYPE				39
#define WLC_DUMP_RATE				40
#define WLC_SET_RATE_PARAMS			41
#define WLC_GET_FIXRATE				42
#define WLC_SET_FIXRATE				43

#define WLC_GET_KEY				44
#define WLC_SET_KEY				45
#define WLC_GET_REGULATORY			46
#define WLC_SET_REGULATORY			47
#define WLC_GET_PASSIVE_SCAN			48
#define WLC_SET_PASSIVE_SCAN			49
#define WLC_SCAN				50
#define WLC_SCAN_RESULTS			51
#define WLC_DISASSOC				52
#define WLC_REASSOC				53
#define WLC_GET_ROAM_TRIGGER			54
#define WLC_SET_ROAM_TRIGGER			55
#define WLC_GET_ROAM_DELTA			56
#define WLC_SET_ROAM_DELTA			57
#define WLC_GET_ROAM_SCAN_PERIOD		58
#define WLC_SET_ROAM_SCAN_PERIOD		59
#define WLC_EVM					60	
#define WLC_GET_TXANT				61
#define WLC_SET_TXANT				62
#define WLC_GET_ANTDIV				63
#define WLC_SET_ANTDIV				64

#define WLC_GET_CLOSED				67
#define WLC_SET_CLOSED				68
#define WLC_GET_MACLIST				69
#define WLC_SET_MACLIST				70
#define WLC_GET_RATESET				71
#define WLC_SET_RATESET				72

#define WLC_LONGTRAIN				74
#define WLC_GET_BCNPRD				75
#define WLC_SET_BCNPRD				76
#define WLC_GET_DTIMPRD				77
#define WLC_SET_DTIMPRD				78
#define WLC_GET_SROM				79
#define WLC_SET_SROM				80
#define WLC_GET_WEP_RESTRICT			81
#define WLC_SET_WEP_RESTRICT			82
#define WLC_GET_COUNTRY				83
#define WLC_SET_COUNTRY				84
#define WLC_GET_PM				85
#define WLC_SET_PM				86
#define WLC_GET_WAKE				87
#define WLC_SET_WAKE				88

#define WLC_GET_FORCELINK			90	
#define WLC_SET_FORCELINK			91	
#define WLC_FREQ_ACCURACY			92	
#define WLC_CARRIER_SUPPRESS			93	
#define WLC_GET_PHYREG				94
#define WLC_SET_PHYREG				95
#define WLC_GET_RADIOREG			96
#define WLC_SET_RADIOREG			97
#define WLC_GET_REVINFO				98
#define WLC_GET_UCANTDIV			99
#define WLC_SET_UCANTDIV			100
#define WLC_R_REG				101
#define WLC_W_REG				102

#define WLC_GET_MACMODE				105
#define WLC_SET_MACMODE				106
#define WLC_GET_MONITOR				107
#define WLC_SET_MONITOR				108
#define WLC_GET_GMODE				109
#define WLC_SET_GMODE				110
#define WLC_GET_LEGACY_ERP			111
#define WLC_SET_LEGACY_ERP			112
#define WLC_GET_RX_ANT				113
#define WLC_GET_CURR_RATESET			114	
#define WLC_GET_SCANSUPPRESS			115
#define WLC_SET_SCANSUPPRESS			116
#define WLC_GET_AP				117
#define WLC_SET_AP				118
#define WLC_GET_EAP_RESTRICT			119
#define WLC_SET_EAP_RESTRICT			120
#define WLC_SCB_AUTHORIZE			121
#define WLC_SCB_DEAUTHORIZE			122
#define WLC_GET_WDSLIST				123
#define WLC_SET_WDSLIST				124
#define WLC_GET_ATIM				125
#define WLC_SET_ATIM				126
#define WLC_GET_RSSI				127
#define WLC_GET_PHYANTDIV			128
#define WLC_SET_PHYANTDIV			129
#define WLC_AP_RX_ONLY				130
#define WLC_GET_TX_PATH_PWR			131
#define WLC_SET_TX_PATH_PWR			132
#define WLC_GET_WSEC				133
#define WLC_SET_WSEC				134
#define WLC_GET_PHY_NOISE			135
#define WLC_GET_BSS_INFO			136
#define WLC_GET_PKTCNTS				137
#define WLC_GET_LAZYWDS				138
#define WLC_SET_LAZYWDS				139
#define WLC_GET_BANDLIST			140
#define WLC_GET_BAND				141
#define WLC_SET_BAND				142
#define WLC_SCB_DEAUTHENTICATE			143
#define WLC_GET_SHORTSLOT			144
#define WLC_GET_SHORTSLOT_OVERRIDE		145
#define WLC_SET_SHORTSLOT_OVERRIDE		146
#define WLC_GET_SHORTSLOT_RESTRICT		147
#define WLC_SET_SHORTSLOT_RESTRICT		148
#define WLC_GET_GMODE_PROTECTION		149
#define WLC_GET_GMODE_PROTECTION_OVERRIDE	150
#define WLC_SET_GMODE_PROTECTION_OVERRIDE	151
#define WLC_UPGRADE				152

#define WLC_GET_IGNORE_BCNS			155
#define WLC_SET_IGNORE_BCNS			156
#define WLC_GET_SCB_TIMEOUT			157
#define WLC_SET_SCB_TIMEOUT			158
#define WLC_GET_ASSOCLIST			159
#define WLC_GET_CLK				160
#define WLC_SET_CLK				161
#define WLC_GET_UP				162
#define WLC_OUT					163
#define WLC_GET_WPA_AUTH			164
#define WLC_SET_WPA_AUTH			165
#define WLC_GET_UCFLAGS				166
#define WLC_SET_UCFLAGS				167
#define WLC_GET_PWRIDX				168
#define WLC_SET_PWRIDX				169
#define WLC_GET_TSSI				170
#define WLC_GET_SUP_RATESET_OVERRIDE		171
#define WLC_SET_SUP_RATESET_OVERRIDE		172

#define WLC_GET_PROTECTION_CONTROL		178
#define WLC_SET_PROTECTION_CONTROL		179
#define WLC_GET_PHYLIST				180
#define WLC_ENCRYPT_STRENGTH			181	
#define WLC_DECRYPT_STATUS			182	
#define WLC_GET_KEY_SEQ				183
#define WLC_GET_SCAN_CHANNEL_TIME		184
#define WLC_SET_SCAN_CHANNEL_TIME		185
#define WLC_GET_SCAN_UNASSOC_TIME		186
#define WLC_SET_SCAN_UNASSOC_TIME		187
#define WLC_GET_SCAN_HOME_TIME			188
#define WLC_SET_SCAN_HOME_TIME			189
#define WLC_GET_SCAN_NPROBES			190
#define WLC_SET_SCAN_NPROBES			191
#define WLC_GET_PRB_RESP_TIMEOUT		192
#define WLC_SET_PRB_RESP_TIMEOUT		193
#define WLC_GET_ATTEN				194
#define WLC_SET_ATTEN				195
#define WLC_GET_SHMEM				196	
#define WLC_SET_SHMEM				197	

#define WLC_SET_WSEC_TEST			200
#define WLC_SCB_DEAUTHENTICATE_FOR_REASON	201
#define WLC_TKIP_COUNTERMEASURES		202
#define WLC_GET_PIOMODE				203
#define WLC_SET_PIOMODE				204
#define WLC_SET_ASSOC_PREFER			205
#define WLC_GET_ASSOC_PREFER			206
#define WLC_SET_ROAM_PREFER			207
#define WLC_GET_ROAM_PREFER			208
#define WLC_SET_LED				209
#define WLC_GET_LED				210
#define WLC_GET_INTERFERENCE_MODE		211
#define WLC_SET_INTERFERENCE_MODE		212
#define WLC_GET_CHANNEL_QA			213
#define WLC_START_CHANNEL_QA			214
#define WLC_GET_CHANNEL_SEL			215
#define WLC_START_CHANNEL_SEL			216
#define WLC_GET_VALID_CHANNELS			217
#define WLC_GET_FAKEFRAG			218
#define WLC_SET_FAKEFRAG			219
#define WLC_GET_PWROUT_PERCENTAGE		220
#define WLC_SET_PWROUT_PERCENTAGE		221
#define WLC_SET_BAD_FRAME_PREEMPT		222
#define WLC_GET_BAD_FRAME_PREEMPT		223
#define WLC_SET_LEAP_LIST			224
#define WLC_GET_LEAP_LIST			225
#define WLC_GET_CWMIN				226
#define WLC_SET_CWMIN				227
#define WLC_GET_CWMAX				228
#define WLC_SET_CWMAX				229
#define WLC_GET_WET				230
#define WLC_SET_WET				231
#define WLC_GET_PUB				232

#define WLC_GET_KEY_PRIMARY			235
#define WLC_SET_KEY_PRIMARY			236

#define WLC_GET_ACI_ARGS			238
#define WLC_SET_ACI_ARGS			239
#define WLC_UNSET_CALLBACK			240
#define WLC_SET_CALLBACK			241
#define WLC_GET_RADAR				242
#define WLC_SET_RADAR				243
#define WLC_SET_SPECT_MANAGMENT			244
#define WLC_GET_SPECT_MANAGMENT			245
#define WLC_WDS_GET_REMOTE_HWADDR		246	
#define WLC_WDS_GET_WPA_SUP			247
#define WLC_SET_CS_SCAN_TIMER			248
#define WLC_GET_CS_SCAN_TIMER			249
#define WLC_MEASURE_REQUEST			250
#define WLC_INIT				251
#define WLC_SEND_QUIET				252
#define WLC_KEEPALIVE			253
#define WLC_SEND_PWR_CONSTRAINT			254
#define WLC_UPGRADE_STATUS			255
#define WLC_CURRENT_PWR				256
#define WLC_GET_SCAN_PASSIVE_TIME		257
#define WLC_SET_SCAN_PASSIVE_TIME		258
#define WLC_LEGACY_LINK_BEHAVIOR		259
#define WLC_GET_CHANNELS_IN_COUNTRY		260
#define WLC_GET_COUNTRY_LIST			261
#define WLC_GET_VAR				262	
#define WLC_SET_VAR				263	
#define WLC_NVRAM_GET				264	
#define WLC_NVRAM_SET				265
#define WLC_NVRAM_DUMP				266
#define WLC_REBOOT				267
#define WLC_SET_WSEC_PMK			268
#define WLC_GET_AUTH_MODE			269
#define WLC_SET_AUTH_MODE			270
#define WLC_GET_WAKEENTRY			271
#define WLC_SET_WAKEENTRY			272
#define WLC_NDCONFIG_ITEM			273	
#define WLC_NVOTPW				274
#define WLC_OTPW				275
#define WLC_IOV_BLOCK_GET			276
#define WLC_IOV_MODULES_GET			277
#define WLC_SOFT_RESET				278
#define WLC_GET_ALLOW_MODE			279
#define WLC_SET_ALLOW_MODE			280
#define WLC_GET_DESIRED_BSSID			281
#define WLC_SET_DESIRED_BSSID			282
#define	WLC_DISASSOC_MYAP			283
#define WLC_GET_NBANDS				284	
#define WLC_GET_BANDSTATES			285	
#define WLC_GET_WLC_BSS_INFO			286	
#define WLC_GET_ASSOC_INFO			287	
#define WLC_GET_OID_PHY				288	
#define WLC_SET_OID_PHY				289	
#define WLC_SET_ASSOC_TIME			290	
#define WLC_GET_DESIRED_SSID			291	
#define WLC_GET_CHANSPEC			292	
#define WLC_GET_ASSOC_STATE			293	
#define WLC_SET_PHY_STATE			294	
#define WLC_GET_SCAN_PENDING			295	
#define WLC_GET_SCANREQ_PENDING			296	
#define WLC_GET_PREV_ROAM_REASON		297	
#define WLC_SET_PREV_ROAM_REASON		298	
#define WLC_GET_BANDSTATES_PI			299	
#define WLC_GET_PHY_STATE			300	
#define WLC_GET_BSS_WPA_RSN			301	
#define WLC_GET_BSS_WPA2_RSN			302	
#define WLC_GET_BSS_BCN_TS			303	
#define WLC_GET_INT_DISASSOC			304	
#define WLC_SET_NUM_PEERS			305     
#define WLC_GET_NUM_BSS				306	
#define WLC_PHY_SAMPLE_COLLECT			307	

#define WLC_GET_CMD				309

#define WLC_SET_INTERFERENCE_OVERRIDE_MODE	311	
#define WLC_GET_INTERFERENCE_OVERRIDE_MODE	312	
#define WLC_GET_WAI_RESTRICT			313	
#define WLC_SET_WAI_RESTRICT			314	
#define WLC_SET_WAI_REKEY			315	
#define WLC_SET_NAT_CONFIG			316	
#define WLC_GET_NAT_STATE			317
#define WLC_LAST				318

#ifndef EPICTRL_COOKIE
#define EPICTRL_COOKIE		0xABADCEDE
#endif

#define CMN_IOCTL_OFF 0x180

#define WL_OID_BASE		0xFFE41420

#define WL_AUTH_OPEN_SYSTEM		0	
#define WL_AUTH_SHARED_KEY		1	
#define WL_AUTH_OPEN_SHARED		3	

#define WL_RADIO_SW_DISABLE		(1<<0)
#define WL_RADIO_HW_DISABLE		(1<<1)
#define WL_RADIO_MPC_DISABLE		(1<<2)
#define WL_RADIO_COUNTRY_DISABLE	(1<<3)	

#define	WL_SPURAVOID_OFF	0
#define	WL_SPURAVOID_ON1	1
#define	WL_SPURAVOID_ON2	2

#define WL_TXPWR_OVERRIDE	(1U<<31)
#define WL_TXPWR_NEG   (1U<<30)

#define WL_PHY_PAVARS_LEN	6	

#define WL_PHY_PAVARS2_NUM	3	
#define WL_PHY_PAVAR_VER	1	
typedef struct wl_pavars2 {
	uint16 ver;		
	uint16 len;		
	uint16 inuse;		
	uint16 phy_type;	
	uint16 bandrange;
	uint16 chain;
	uint16 inpa[WL_PHY_PAVARS2_NUM];	
} wl_pavars2_t;

typedef struct wl_po {
	uint16	phy_type;	
	uint16	band;
	uint16	cckpo;
	uint32	ofdmpo;
	uint16	mcspo[8];
} wl_po_t;

#define WLC_TXPWR_MAX		(127)	

#define WL_DIAG_INTERRUPT			1	
#define WL_DIAG_LOOPBACK			2	
#define WL_DIAG_MEMORY				3	
#define WL_DIAG_LED				4	
#define WL_DIAG_REG				5	
#define WL_DIAG_SROM				6	
#define WL_DIAG_DMA				7	

#define WL_DIAGERR_SUCCESS			0
#define WL_DIAGERR_FAIL_TO_RUN			1	
#define WL_DIAGERR_NOT_SUPPORTED		2	
#define WL_DIAGERR_INTERRUPT_FAIL		3	
#define WL_DIAGERR_LOOPBACK_FAIL		4	
#define WL_DIAGERR_SROM_FAIL			5	
#define WL_DIAGERR_SROM_BADCRC			6	
#define WL_DIAGERR_REG_FAIL			7	
#define WL_DIAGERR_MEMORY_FAIL			8	
#define WL_DIAGERR_NOMEM			9	
#define WL_DIAGERR_DMA_FAIL			10	

#define WL_DIAGERR_MEMORY_TIMEOUT		11	
#define WL_DIAGERR_MEMORY_BADPATTERN		12	

#define	WLC_BAND_AUTO		0	
#define	WLC_BAND_5G		1	
#define	WLC_BAND_2G		2	
#define	WLC_BAND_ALL		3	

#define WL_CHAN_FREQ_RANGE_2G      0
#define WL_CHAN_FREQ_RANGE_5GL     1
#define WL_CHAN_FREQ_RANGE_5GM     2
#define WL_CHAN_FREQ_RANGE_5GH     3

#define WL_CHAN_FREQ_RANGE_5GLL_5BAND    4
#define WL_CHAN_FREQ_RANGE_5GLH_5BAND    5
#define WL_CHAN_FREQ_RANGE_5GML_5BAND    6
#define WL_CHAN_FREQ_RANGE_5GMH_5BAND    7
#define WL_CHAN_FREQ_RANGE_5GH_5BAND     8

#define	WLC_PHY_TYPE_A		0
#define	WLC_PHY_TYPE_B		1
#define	WLC_PHY_TYPE_G		2
#define	WLC_PHY_TYPE_N		4
#define	WLC_PHY_TYPE_LP		5
#define	WLC_PHY_TYPE_SSN	6
#define	WLC_PHY_TYPE_HT		7
#define	WLC_PHY_TYPE_LCN	8
#define	WLC_PHY_TYPE_LCN40	10
#define	WLC_PHY_TYPE_NULL	0xf

#define WLC_MACMODE_DISABLED	0	
#define WLC_MACMODE_DENY	1	
#define WLC_MACMODE_ALLOW	2	

#define GMODE_LEGACY_B		0
#define GMODE_AUTO		1
#define GMODE_ONLY		2
#define GMODE_B_DEFERRED	3
#define GMODE_PERFORMANCE	4
#define GMODE_LRS		5
#define GMODE_MAX		6

#define WLC_PLCP_AUTO	-1
#define WLC_PLCP_SHORT	0
#define WLC_PLCP_LONG	1

#define WLC_PROTECTION_AUTO		-1
#define WLC_PROTECTION_OFF		0
#define WLC_PROTECTION_ON		1
#define WLC_PROTECTION_MMHDR_ONLY	2
#define WLC_PROTECTION_CTS_ONLY		3

#define WLC_PROTECTION_CTL_OFF		0
#define WLC_PROTECTION_CTL_LOCAL	1
#define WLC_PROTECTION_CTL_OVERLAP	2

#define WLC_N_PROTECTION_OFF		0
#define WLC_N_PROTECTION_OPTIONAL	1
#define WLC_N_PROTECTION_20IN40		2
#define WLC_N_PROTECTION_MIXEDMODE	3

#define WLC_N_PREAMBLE_MIXEDMODE	0
#define WLC_N_PREAMBLE_GF		1
#define WLC_N_PREAMBLE_GF_BRCM          2

#define WLC_N_BW_20ALL			0
#define WLC_N_BW_40ALL			1
#define WLC_N_BW_20IN2G_40IN5G		2

#define WLC_N_TXRX_CHAIN0		0
#define WLC_N_TXRX_CHAIN1		1

#define WLC_N_SGI_20			0x01
#define WLC_N_SGI_40			0x02

#define WLC_SGI_ALL				0x02

#define PM_OFF	0
#define PM_MAX	1
#define PM_FAST 2
#define PM_FORCE_OFF 3 		

#define	INTERFERE_OVRRIDE_OFF	-1	
#define	INTERFERE_NONE	0	
#define	NON_WLAN	1	
#define	WLAN_MANUAL	2	
#define	WLAN_AUTO	3	
#define	WLAN_AUTO_W_NOISE	4	
#define AUTO_ACTIVE	(1 << 7) 

typedef struct wl_aci_args {
	int enter_aci_thresh; 
	int exit_aci_thresh; 
	int usec_spin; 
	int glitch_delay; 
	uint16 nphy_adcpwr_enter_thresh;	
	uint16 nphy_adcpwr_exit_thresh;	
	uint16 nphy_repeat_ctr;		
	uint16 nphy_num_samples;	
	uint16 nphy_undetect_window_sz;	
	uint16 nphy_b_energy_lo_aci;	
	uint16 nphy_b_energy_md_aci;	
	uint16 nphy_b_energy_hi_aci;	
	uint16 nphy_noise_noassoc_glitch_th_up; 
	uint16 nphy_noise_noassoc_glitch_th_dn;
	uint16 nphy_noise_assoc_glitch_th_up;
	uint16 nphy_noise_assoc_glitch_th_dn;
	uint16 nphy_noise_assoc_aci_glitch_th_up;
	uint16 nphy_noise_assoc_aci_glitch_th_dn;
	uint16 nphy_noise_assoc_enter_th;
	uint16 nphy_noise_noassoc_enter_th;
	uint16 nphy_noise_assoc_rx_glitch_badplcp_enter_th;
	uint16 nphy_noise_noassoc_crsidx_incr;
	uint16 nphy_noise_assoc_crsidx_incr;
	uint16 nphy_noise_crsidx_decr;
} wl_aci_args_t;

#define TRIGGER_NOW				0
#define TRIGGER_CRS				0x01
#define TRIGGER_CRSDEASSERT			0x02
#define TRIGGER_GOODFCS				0x04
#define TRIGGER_BADFCS				0x08
#define TRIGGER_BADPLCP				0x10
#define TRIGGER_CRSGLITCH			0x20
#define WL_ACI_ARGS_LEGACY_LENGTH	16	
#define	WL_SAMPLECOLLECT_T_VERSION	1	
typedef struct wl_samplecollect_args {

	uint8 coll_us;
	int cores;

	uint16 version;     
	uint16 length;      
	uint8 trigger;
	uint16 timeout;
	uint16 mode;
	uint32 pre_dur;
	uint32 post_dur;
	uint8 gpio_sel;
	bool downsamp;
	bool be_deaf;
	bool agc;		
	bool filter;		
} wl_samplecollect_args_t;

#define	WL_SAMPLEDATA_HEADER_TYPE	1
#define WL_SAMPLEDATA_HEADER_SIZE	80	
#define	WL_SAMPLEDATA_TYPE		2
#define	WL_SAMPLEDATA_SEQ		0xff	
#define	WL_SAMPLEDATA_MORE_DATA		0x100	
#define	WL_SAMPLEDATA_T_VERSION		1	

#define	WL_SAMPLEDATA_T_VERSION_SPEC_AN 2

typedef struct wl_sampledata {
	uint16 version;	
	uint16 size;	
	uint16 tag;	
	uint16 length;	
	uint32 flag;	
} wl_sampledata_t;

#define WL_ERROR_VAL		0x00000001
#define WL_TRACE_VAL		0x00000002
#define WL_PRHDRS_VAL		0x00000004
#define WL_PRPKT_VAL		0x00000008
#define WL_INFORM_VAL		0x00000010
#define WL_TMP_VAL		0x00000020
#define WL_OID_VAL		0x00000040
#define WL_RATE_VAL		0x00000080
#define WL_ASSOC_VAL		0x00000100
#define WL_PRUSR_VAL		0x00000200
#define WL_PS_VAL		0x00000400
#define WL_TXPWR_VAL		0x00000800	
#define WL_PORT_VAL		0x00001000
#define WL_DUAL_VAL		0x00002000
#define WL_WSEC_VAL		0x00004000
#define WL_WSEC_DUMP_VAL	0x00008000
#define WL_LOG_VAL		0x00010000
#define WL_NRSSI_VAL		0x00020000	
#define WL_LOFT_VAL		0x00040000	
#define WL_REGULATORY_VAL	0x00080000
#define WL_PHYCAL_VAL		0x00100000	
#define WL_RADAR_VAL		0x00200000	
#define WL_MPC_VAL		0x00400000
#define WL_APSTA_VAL		0x00800000
#define WL_DFS_VAL		0x01000000
#define WL_BA_VAL		0x02000000	
#define WL_ACI_VAL		0x04000000
#define WL_MBSS_VAL		0x04000000
#define WL_CAC_VAL		0x08000000
#define WL_AMSDU_VAL		0x10000000
#define WL_AMPDU_VAL		0x20000000
#define WL_FFPLD_VAL		0x40000000

#define WL_DPT_VAL 		0x00000001
#define WL_SCAN_VAL		0x00000002
#define WL_WOWL_VAL		0x00000004
#define WL_COEX_VAL		0x00000008
#define WL_RTDC_VAL		0x00000010
#define WL_PROTO_VAL		0x00000020
#define WL_BTA_VAL		0x00000040
#define WL_CHANINT_VAL		0x00000080
#define WL_THERMAL_VAL		0x00000100	
#define WL_P2P_VAL		0x00000200
#define WL_ITFR_VAL		0x00000400
#define WL_MCHAN_VAL		0x00000800
#define WL_TDLS_VAL		0x00001000

#define	WL_LED_NUMGPIO		32	

#define	WL_LED_OFF		0		
#define	WL_LED_ON		1		
#define	WL_LED_ACTIVITY		2		
#define	WL_LED_RADIO		3		
#define	WL_LED_ARADIO		4		
#define	WL_LED_BRADIO		5		
#define	WL_LED_BGMODE		6		
#define	WL_LED_WI1		7
#define	WL_LED_WI2		8
#define	WL_LED_WI3		9
#define	WL_LED_ASSOC		10		
#define	WL_LED_INACTIVE		11		
#define	WL_LED_ASSOCACT		12		
#define WL_LED_WI4		13
#define WL_LED_WI5		14
#define	WL_LED_BLINKSLOW	15		
#define	WL_LED_BLINKMED		16		
#define	WL_LED_BLINKFAST	17		
#define	WL_LED_BLINKCUSTOM	18		
#define	WL_LED_BLINKPERIODIC	19		
#define WL_LED_ASSOC_WITH_SEC 	20		

#define WL_LED_START_OFF 	21		
#define	WL_LED_NUMBEHAVIOR	22

#define	WL_LED_BEH_MASK		0x7f		
#define	WL_LED_AL_MASK		0x80		

#define WL_NUMCHANNELS		64
#define WL_NUMCHANSPECS		100

#define WL_WDS_WPA_ROLE_AUTH	0	
#define WL_WDS_WPA_ROLE_SUP	1	
#define WL_WDS_WPA_ROLE_AUTO	255	

#define WL_EVENTING_MASK_LEN	16

#define WL_JOIN_PREF_RSSI	1	
#define WL_JOIN_PREF_WPA	2	
#define WL_JOIN_PREF_BAND	3	
#define WL_JOIN_PREF_RSSI_DELTA	4	
#define WL_JOIN_PREF_TRANS_PREF	5	

#define WLJP_BAND_ASSOC_PREF	255	

#define WL_WPA_ACP_MCS_ANY	"\x00\x00\x00\x00"

struct tsinfo_arg {
	uint8 octets[3];
};

#define	NFIFO			6	

#define	WL_CNT_T_VERSION	8	

typedef struct {
	uint16	version;	
	uint16	length;		

	uint32	txframe;	
	uint32	txbyte;		
	uint32	txretrans;	
	uint32	txerror;	
	uint32	txctl;		
	uint32	txprshort;	
	uint32	txserr;		
	uint32	txnobuf;	
	uint32	txnoassoc;	
	uint32	txrunt;		
	uint32	txchit;		
	uint32	txcmiss;	

	uint32	txuflo;		
	uint32	txphyerr;	
	uint32	txphycrs;

	uint32	rxframe;	
	uint32	rxbyte;		
	uint32	rxerror;	
	uint32	rxctl;		
	uint32	rxnobuf;	
	uint32	rxnondata;	
	uint32	rxbadds;	
	uint32	rxbadcm;	
	uint32	rxfragerr;	
	uint32	rxrunt;		
	uint32	rxgiant;	
	uint32	rxnoscb;	
	uint32	rxbadproto;	
	uint32	rxbadsrcmac;	
	uint32	rxbadda;	
	uint32	rxfilter;	

	uint32	rxoflo;		
	uint32	rxuflo[NFIFO];	

	uint32	d11cnt_txrts_off;	
	uint32	d11cnt_rxcrc_off;	
	uint32	d11cnt_txnocts_off;	

	uint32	dmade;		
	uint32	dmada;		
	uint32	dmape;		
	uint32	reset;		
	uint32	tbtt;		
	uint32	txdmawar;
	uint32	pkt_callback_reg_fail;	

	uint32	txallfrm;	
	uint32	txrtsfrm;	
	uint32	txctsfrm;	
	uint32	txackfrm;	
	uint32	txdnlfrm;	
	uint32	txbcnfrm;	
	uint32	txfunfl[8];	
	uint32	txtplunfl;	
	uint32	txphyerror;	
	uint32	rxfrmtoolong;	
	uint32	rxfrmtooshrt;	
	uint32	rxinvmachdr;	
	uint32	rxbadfcs;	
	uint32	rxbadplcp;	
	uint32	rxcrsglitch;	
	uint32	rxstrt;		
	uint32	rxdfrmucastmbss; 
	uint32	rxmfrmucastmbss; 
	uint32	rxcfrmucast;	
	uint32	rxrtsucast;	
	uint32	rxctsucast;	
	uint32	rxackucast;	
	uint32	rxdfrmocast;	
	uint32	rxmfrmocast;	
	uint32	rxcfrmocast;	
	uint32	rxrtsocast;	
	uint32	rxctsocast;	
	uint32	rxdfrmmcast;	
	uint32	rxmfrmmcast;	
	uint32	rxcfrmmcast;	
	uint32	rxbeaconmbss;	
	uint32	rxdfrmucastobss; 
	uint32	rxbeaconobss;	
	uint32	rxrsptmout;	
	uint32	bcntxcancl;	
	uint32	rxf0ovfl;	
	uint32	rxf1ovfl;	
	uint32	rxf2ovfl;	
	uint32	txsfovfl;	
	uint32	pmqovfl;	
	uint32	rxcgprqfrm;	
	uint32	rxcgprsqovfl;	
	uint32	txcgprsfail;	
	uint32	txcgprssuc;	
	uint32	prs_timeout;	
	uint32	rxnack;		
	uint32	frmscons;	
	uint32	txnack;		
	uint32	txglitch_nack;	
	uint32	txburst;	

	uint32	txfrag;		
	uint32	txmulti;	
	uint32	txfail;		
	uint32	txretry;	
	uint32	txretrie;	
	uint32	rxdup;		
	uint32	txrts;		
	uint32	txnocts;	
	uint32	txnoack;	
	uint32	rxfrag;		
	uint32	rxmulti;	
	uint32	rxcrc;		
	uint32	txfrmsnt;	
	uint32	rxundec;	

	uint32	tkipmicfaill;	
	uint32	tkipcntrmsr;	
	uint32	tkipreplay;	
	uint32	ccmpfmterr;	
	uint32	ccmpreplay;	
	uint32	ccmpundec;	
	uint32	fourwayfail;	
	uint32	wepundec;	
	uint32	wepicverr;	
	uint32	decsuccess;	
	uint32	tkipicverr;	
	uint32	wepexcluded;	

	uint32	txchanrej;	
	uint32	psmwds;		
	uint32	phywatchdog;	

	uint32	prq_entries_handled;	
	uint32	prq_undirected_entries;	
	uint32	prq_bad_entries;	
	uint32	atim_suppress_count;	
	uint32	bcn_template_not_ready;	
	uint32	bcn_template_not_ready_done; 
	uint32	late_tbtt_dpc;	

	uint32  rx1mbps;	
	uint32  rx2mbps;	
	uint32  rx5mbps5;	
	uint32  rx6mbps;	
	uint32  rx9mbps;	
	uint32  rx11mbps;	
	uint32  rx12mbps;	
	uint32  rx18mbps;	
	uint32  rx24mbps;	
	uint32  rx36mbps;	
	uint32  rx48mbps;	
	uint32  rx54mbps;	
	uint32  rx108mbps; 	
	uint32  rx162mbps;	
	uint32  rx216mbps;	
	uint32  rx270mbps;	
	uint32  rx324mbps;	
	uint32  rx378mbps;	
	uint32  rx432mbps;	
	uint32  rx486mbps;	
	uint32  rx540mbps;	

	uint32	pktengrxducast; 
	uint32	pktengrxdmcast; 

	uint32	rfdisable;	
	uint32	bphy_rxcrsglitch;	

	uint32	txexptime;	

	uint32	txmpdu_sgi;	
	uint32	rxmpdu_sgi;	
	uint32	txmpdu_stbc;	
	uint32	rxmpdu_stbc;	

	uint32	rxundec_mcst;	

	uint32	tkipmicfaill_mcst;	
	uint32	tkipcntrmsr_mcst;	
	uint32	tkipreplay_mcst;	
	uint32	ccmpfmterr_mcst;	
	uint32	ccmpreplay_mcst;	
	uint32	ccmpundec_mcst;	
	uint32	fourwayfail_mcst;	
	uint32	wepundec_mcst;	
	uint32	wepicverr_mcst;	
	uint32	decsuccess_mcst;	
	uint32	tkipicverr_mcst;	
	uint32	wepexcluded_mcst;	

	uint32	dma_hang;	
	uint32	reinit;		
} wl_cnt_t;

typedef struct {
	uint16  version;    
	uint16  length;     

	uint32  txframe;    
	uint32  txbyte;     
	uint32  txretrans;  
	uint32  txerror;    
	uint32  txctl;      
	uint32  txprshort;  
	uint32  txserr;     
	uint32  txnobuf;    
	uint32  txnoassoc;  
	uint32  txrunt;     
	uint32  txchit;     
	uint32  txcmiss;    

	uint32  txuflo;     
	uint32  txphyerr;   
	uint32  txphycrs;

	uint32  rxframe;    
	uint32  rxbyte;     
	uint32  rxerror;    
	uint32  rxctl;      
	uint32  rxnobuf;    
	uint32  rxnondata;  
	uint32  rxbadds;    
	uint32  rxbadcm;    
	uint32  rxfragerr;  
	uint32  rxrunt;     
	uint32  rxgiant;    
	uint32  rxnoscb;    
	uint32  rxbadproto; 
	uint32  rxbadsrcmac;    
	uint32  rxbadda;    
	uint32  rxfilter;   

	uint32  rxoflo;     
	uint32  rxuflo[NFIFO];  

	uint32  d11cnt_txrts_off;   
	uint32  d11cnt_rxcrc_off;   
	uint32  d11cnt_txnocts_off; 

	uint32  dmade;      
	uint32  dmada;      
	uint32  dmape;      
	uint32  reset;      
	uint32  tbtt;       
	uint32  txdmawar;
	uint32  pkt_callback_reg_fail;  

	uint32  txallfrm;   
	uint32  txrtsfrm;   
	uint32  txctsfrm;   
	uint32  txackfrm;   
	uint32  txdnlfrm;   
	uint32  txbcnfrm;   
	uint32  txfunfl[8]; 
	uint32  txtplunfl;  
	uint32  txphyerror; 
	uint32  rxfrmtoolong;   
	uint32  rxfrmtooshrt;   
	uint32  rxinvmachdr;    
	uint32  rxbadfcs;   
	uint32  rxbadplcp;  
	uint32  rxcrsglitch;    
	uint32  rxstrt;     
	uint32  rxdfrmucastmbss; 
	uint32  rxmfrmucastmbss; 
	uint32  rxcfrmucast;    
	uint32  rxrtsucast; 
	uint32  rxctsucast; 
	uint32  rxackucast; 
	uint32  rxdfrmocast;    
	uint32  rxmfrmocast;    
	uint32  rxcfrmocast;    
	uint32  rxrtsocast; 
	uint32  rxctsocast; 
	uint32  rxdfrmmcast;    
	uint32  rxmfrmmcast;    
	uint32  rxcfrmmcast;    
	uint32  rxbeaconmbss;   
	uint32  rxdfrmucastobss; 
	uint32  rxbeaconobss;   
	uint32  rxrsptmout; 
	uint32  bcntxcancl; 
	uint32  rxf0ovfl;   
	uint32  rxf1ovfl;   
	uint32  rxf2ovfl;   
	uint32  txsfovfl;   
	uint32  pmqovfl;    
	uint32  rxcgprqfrm; 
	uint32  rxcgprsqovfl;   
	uint32  txcgprsfail;    
	uint32  txcgprssuc; 
	uint32  prs_timeout;    
	uint32  rxnack;
	uint32  frmscons;
	uint32  txnack;
	uint32  txglitch_nack;  
	uint32  txburst;    

	uint32  txfrag;     
	uint32  txmulti;    
	uint32  txfail;     
	uint32  txretry;    
	uint32  txretrie;   
	uint32  rxdup;      
	uint32  txrts;      
	uint32  txnocts;    
	uint32  txnoack;    
	uint32  rxfrag;     
	uint32  rxmulti;    
	uint32  rxcrc;      
	uint32  txfrmsnt;   
	uint32  rxundec;    

	uint32  tkipmicfaill;   
	uint32  tkipcntrmsr;    
	uint32  tkipreplay; 
	uint32  ccmpfmterr; 
	uint32  ccmpreplay; 
	uint32  ccmpundec;  
	uint32  fourwayfail;    
	uint32  wepundec;   
	uint32  wepicverr;  
	uint32  decsuccess; 
	uint32  tkipicverr; 
	uint32  wepexcluded;    

	uint32  rxundec_mcst;   

	uint32  tkipmicfaill_mcst;  
	uint32  tkipcntrmsr_mcst;   
	uint32  tkipreplay_mcst;    
	uint32  ccmpfmterr_mcst;    
	uint32  ccmpreplay_mcst;    
	uint32  ccmpundec_mcst; 
	uint32  fourwayfail_mcst;   
	uint32  wepundec_mcst;  
	uint32  wepicverr_mcst; 
	uint32  decsuccess_mcst;    
	uint32  tkipicverr_mcst;    
	uint32  wepexcluded_mcst;   

	uint32  txchanrej;  
	uint32  txexptime;  
	uint32  psmwds;     
	uint32  phywatchdog;    

	uint32  prq_entries_handled;    
	uint32  prq_undirected_entries; 
	uint32  prq_bad_entries;    
	uint32  atim_suppress_count;    
	uint32  bcn_template_not_ready; 
	uint32  bcn_template_not_ready_done; 
	uint32  late_tbtt_dpc;  

	uint32  rx1mbps;    
	uint32  rx2mbps;    
	uint32  rx5mbps5;   
	uint32  rx6mbps;    
	uint32  rx9mbps;    
	uint32  rx11mbps;   
	uint32  rx12mbps;   
	uint32  rx18mbps;   
	uint32  rx24mbps;   
	uint32  rx36mbps;   
	uint32  rx48mbps;   
	uint32  rx54mbps;   
	uint32  rx108mbps;  
	uint32  rx162mbps;  
	uint32  rx216mbps;  
	uint32  rx270mbps;  
	uint32  rx324mbps;  
	uint32  rx378mbps;  
	uint32  rx432mbps;  
	uint32  rx486mbps;  
	uint32  rx540mbps;  

	uint32  pktengrxducast; 
	uint32  pktengrxdmcast; 

	uint32  rfdisable;  
	uint32  bphy_rxcrsglitch;   

	uint32  txmpdu_sgi; 
	uint32  rxmpdu_sgi; 
	uint32  txmpdu_stbc;    
	uint32  rxmpdu_stbc;    
} wl_cnt_ver_six_t;

#define WL_WME_CNT_VERSION	1	

typedef struct {
	uint32 packets;
	uint32 bytes;
} wl_traffic_stats_t;

typedef struct {
	uint16	version;	
	uint16	length;		

	wl_traffic_stats_t tx[AC_COUNT];	
	wl_traffic_stats_t tx_failed[AC_COUNT];	
	wl_traffic_stats_t rx[AC_COUNT];	
	wl_traffic_stats_t rx_failed[AC_COUNT];	

	wl_traffic_stats_t forward[AC_COUNT];	

	wl_traffic_stats_t tx_expired[AC_COUNT];	

} wl_wme_cnt_t;

struct wl_msglevel2 {
	uint32 low;
	uint32 high;
};

#define WLC_ROAM_TRIGGER_DEFAULT	0 
#define WLC_ROAM_TRIGGER_BANDWIDTH	1 
#define WLC_ROAM_TRIGGER_DISTANCE	2 
#define WLC_ROAM_TRIGGER_AUTO		3 
#define WLC_ROAM_TRIGGER_MAX_VALUE	3 

enum {
	PFN_LIST_ORDER,
	PFN_RSSI
};

enum {
	DISABLE,
	ENABLE
};

#define SORT_CRITERIA_BIT		0
#define AUTO_NET_SWITCH_BIT		1
#define ENABLE_BKGRD_SCAN_BIT		2
#define IMMEDIATE_SCAN_BIT		3
#define	AUTO_CONNECT_BIT		4

#define SORT_CRITERIA_MASK		0x01
#define AUTO_NET_SWITCH_MASK		0x02
#define ENABLE_BKGRD_SCAN_MASK		0x04
#define IMMEDIATE_SCAN_MASK		0x08
#define	AUTO_CONNECT_MASK		0x10

#define PFN_VERSION			1

typedef struct wl_pfn_param {
	int32 version;			
	int32 scan_freq;		
	int32 lost_network_timeout;	
	int16 flags;			
	int16 rssi_margin;		
} wl_pfn_param_t;

typedef struct wl_pfn {
	wlc_ssid_t		ssid;			
	int32			bss_type;		
	int32			infra;			
	int32			auth;			
	uint32			wpa_auth;		
	int32			wsec;			
} wl_pfn_t;

#define TOE_TX_CSUM_OL		0x00000001
#define TOE_RX_CSUM_OL		0x00000002

typedef struct wl_sslpnphy_papd_debug_data {
	uint8 psat_pwr;
	uint8 psat_indx;
	uint8 final_idx;
	uint8 start_idx;
	int32 min_phase;
	int32 voltage;
	int8 temperature;
} wl_sslpnphy_papd_debug_data_t;
typedef struct wl_sslpnphy_debug_data {
	int16 papdcompRe [64];
	int16 papdcompIm [64];
} wl_sslpnphy_debug_data_t;
typedef struct wl_sslpnphy_spbdump_data {
	uint16 tbl_length;
	int16 spbreal[256];
	int16 spbimg[256];
} wl_sslpnphy_spbdump_data_t;
typedef struct wl_sslpnphy_percal_debug_data {
	uint cur_idx;
	uint tx_drift;
	uint8 prev_cal_idx;
	uint percal_ctr;
	int nxt_cal_idx;
	uint force_1idxcal;
	uint onedxacl_req;
	int32 last_cal_volt;
	int8 last_cal_temp;
	uint vbat_ripple;
	uint exit_route;
	int32 volt_winner;
} wl_sslpnphy_percal_debug_data_t;
#define WL_WOWL_MAGIC	(1 << 0)	
#define WL_WOWL_NET	(1 << 1)	
#define WL_WOWL_DIS	(1 << 2)	
#define WL_WOWL_RETR	(1 << 3)	
#define WL_WOWL_BCN	(1 << 4)	
#define WL_WOWL_TST	(1 << 5)	
#define WL_WOWL_M1      (1 << 6)        
#define WL_WOWL_EAPID   (1 << 7)        
#define WL_WOWL_PME_GPIO (1 << 8)   
#define WL_WOWL_KEYROT  (1 << 14)       
#define WL_WOWL_BCAST	(1 << 15)	

#define MAGIC_PKT_MINLEN 102	

typedef struct {
	uint masksize;		
	uint offset;		
	uint patternoffset;	
	uint patternsize;	
	ulong id;		
	uint reasonsize;	

} wl_wowl_pattern_t;

typedef struct {
	uint			count;
	wl_wowl_pattern_t	pattern[1];
} wl_wowl_pattern_list_t;

typedef struct {
	uint8	pci_wakeind;	
	uint16	ucode_wakeind;	
} wl_wowl_wakeind_t;

typedef struct wl_txrate_class {
	uint8		init_rate;
	uint8		min_rate;
	uint8		max_rate;
} wl_txrate_class_t;

#define WLC_OBSS_SCAN_PASSIVE_DWELL_DEFAULT		20	
#define WLC_OBSS_SCAN_PASSIVE_DWELL_MIN			5	
#define WLC_OBSS_SCAN_PASSIVE_DWELL_MAX			1000	
#define WLC_OBSS_SCAN_ACTIVE_DWELL_DEFAULT		10	
#define WLC_OBSS_SCAN_ACTIVE_DWELL_MIN			10	
#define WLC_OBSS_SCAN_ACTIVE_DWELL_MAX			1000	
#define WLC_OBSS_SCAN_WIDTHSCAN_INTERVAL_DEFAULT	300	
#define WLC_OBSS_SCAN_WIDTHSCAN_INTERVAL_MIN		10	
#define WLC_OBSS_SCAN_WIDTHSCAN_INTERVAL_MAX		900	
#define WLC_OBSS_SCAN_CHANWIDTH_TRANSITION_DLY_DEFAULT	5
#define WLC_OBSS_SCAN_CHANWIDTH_TRANSITION_DLY_MIN	5
#define WLC_OBSS_SCAN_CHANWIDTH_TRANSITION_DLY_MAX	100
#define WLC_OBSS_SCAN_PASSIVE_TOTAL_PER_CHANNEL_DEFAULT	200	
#define WLC_OBSS_SCAN_PASSIVE_TOTAL_PER_CHANNEL_MIN	200	
#define WLC_OBSS_SCAN_PASSIVE_TOTAL_PER_CHANNEL_MAX	10000	
#define WLC_OBSS_SCAN_ACTIVE_TOTAL_PER_CHANNEL_DEFAULT	20	
#define WLC_OBSS_SCAN_ACTIVE_TOTAL_PER_CHANNEL_MIN	20	
#define WLC_OBSS_SCAN_ACTIVE_TOTAL_PER_CHANNEL_MAX	10000	
#define WLC_OBSS_SCAN_ACTIVITY_THRESHOLD_DEFAULT	25	
#define WLC_OBSS_SCAN_ACTIVITY_THRESHOLD_MIN		0	
#define WLC_OBSS_SCAN_ACTIVITY_THRESHOLD_MAX		100	

typedef struct wl_obss_scan_arg {
	int16	passive_dwell;
	int16	active_dwell;
	int16	bss_widthscan_interval;
	int16	passive_total;
	int16	active_total;
	int16	chanwidth_transition_delay;
	int16	activity_threshold;
} wl_obss_scan_arg_t;

#define WL_OBSS_SCAN_PARAM_LEN	sizeof(wl_obss_scan_arg_t)
#define WL_MIN_NUM_OBSS_SCAN_ARG 7	

#define WL_COEX_INFO_MASK		0x07
#define WL_COEX_INFO_REQ		0x01
#define	WL_COEX_40MHZ_INTOLERANT	0x02
#define	WL_COEX_WIDTH20			0x04

#define	WLC_RSSI_INVALID	 0	

#define MAX_RSSI_LEVELS 8

typedef struct wl_rssi_event {
	uint32 rate_limit_msec;		
	uint8 num_rssi_levels;		
	int8 rssi_levels[MAX_RSSI_LEVELS];	
} wl_rssi_event_t;

typedef struct wl_action_obss_coex_req {
	uint8 info;
	uint8 num;
	uint8 ch_list[1];
} wl_action_obss_coex_req_t;

#define WL_IOV_MAC_PARAM_LEN  4

#define WL_IOV_PKTQ_LOG_PRECS 16

typedef struct {
	uint32 num_addrs;
	char   addr_type[WL_IOV_MAC_PARAM_LEN];
	struct ether_addr ea[WL_IOV_MAC_PARAM_LEN];
} wl_iov_mac_params_t;

typedef struct {
	uint32 requested;      
	uint32 stored;         
	uint32 saved;          
	uint32 selfsaved;      
	uint32 full_dropped;   
	uint32 dropped;        
	uint32 sacrified;      
	uint32 busy;           
	uint32 retry;          
	uint32 ps_retry;       
	uint32 retry_drop;     
	uint32 max_avail;      
	uint32 max_used;       
	uint32 queue_capacity; 
} pktq_log_counters_v01_t;

typedef struct {
	uint8                num_prec[WL_IOV_MAC_PARAM_LEN];
	pktq_log_counters_v01_t  counters[WL_IOV_MAC_PARAM_LEN][WL_IOV_PKTQ_LOG_PRECS];
	char                 headings[1];
} pktq_log_format_v01_t;

typedef struct {
	uint32               version;
	wl_iov_mac_params_t  params;
	union {
		pktq_log_format_v01_t v01;
	} pktq_log;
} wl_iov_pktq_log_t;

#define EXTLOG_CUR_VER		0x0100

#define MAX_ARGSTR_LEN		18 

#define LOG_MODULE_COMMON	0x0001
#define LOG_MODULE_ASSOC	0x0002
#define LOG_MODULE_EVENT	0x0004
#define LOG_MODULE_MAX		3			

#define WL_LOG_LEVEL_DISABLE	0
#define WL_LOG_LEVEL_ERR	1
#define WL_LOG_LEVEL_WARN	2
#define WL_LOG_LEVEL_INFO	3
#define WL_LOG_LEVEL_MAX	WL_LOG_LEVEL_INFO	

#define LOG_FLAG_EVENT		1

#define LOG_ARGTYPE_NULL	0
#define LOG_ARGTYPE_STR		1	
#define LOG_ARGTYPE_INT		2	
#define LOG_ARGTYPE_INT_STR	3	
#define LOG_ARGTYPE_STR_INT	4	

typedef struct wlc_extlog_cfg {
	int max_number;
	uint16 module;	
	uint8 level;
	uint8 flag;
	uint16 version;
} wlc_extlog_cfg_t;

typedef struct log_record {
	uint32 time;
	uint16 module;
	uint16 id;
	uint8 level;
	uint8 sub_unit;
	uint8 seq_num;
	int32 arg;
	char str[MAX_ARGSTR_LEN];
} log_record_t;

typedef struct wlc_extlog_req {
	uint32 from_last;
	uint32 num;
} wlc_extlog_req_t;

typedef struct wlc_extlog_results {
	uint16 version;
	uint16 record_len;
	uint32 num;
	log_record_t logs[1];
} wlc_extlog_results_t;

typedef struct log_idstr {
	uint16	id;
	uint16	flag;
	uint8	arg_type;
	const char	*fmt_str;
} log_idstr_t;

#define FMTSTRF_USER		1

typedef enum {
	FMTSTR_DRIVER_UP_ID = 0,
	FMTSTR_DRIVER_DOWN_ID = 1,
	FMTSTR_SUSPEND_MAC_FAIL_ID = 2,
	FMTSTR_NO_PROGRESS_ID = 3,
	FMTSTR_RFDISABLE_ID = 4,
	FMTSTR_REG_PRINT_ID = 5,
	FMTSTR_EXPTIME_ID = 6,
	FMTSTR_JOIN_START_ID = 7,
	FMTSTR_JOIN_COMPLETE_ID = 8,
	FMTSTR_NO_NETWORKS_ID = 9,
	FMTSTR_SECURITY_MISMATCH_ID = 10,
	FMTSTR_RATE_MISMATCH_ID = 11,
	FMTSTR_AP_PRUNED_ID = 12,
	FMTSTR_KEY_INSERTED_ID = 13,
	FMTSTR_DEAUTH_ID = 14,
	FMTSTR_DISASSOC_ID = 15,
	FMTSTR_LINK_UP_ID = 16,
	FMTSTR_LINK_DOWN_ID = 17,
	FMTSTR_RADIO_HW_OFF_ID = 18,
	FMTSTR_RADIO_HW_ON_ID = 19,
	FMTSTR_EVENT_DESC_ID = 20,
	FMTSTR_PNP_SET_POWER_ID = 21,
	FMTSTR_RADIO_SW_OFF_ID = 22,
	FMTSTR_RADIO_SW_ON_ID = 23,
	FMTSTR_PWD_MISMATCH_ID = 24,
	FMTSTR_FATAL_ERROR_ID = 25,
	FMTSTR_AUTH_FAIL_ID = 26,
	FMTSTR_ASSOC_FAIL_ID = 27,
	FMTSTR_IBSS_FAIL_ID = 28,
	FMTSTR_EXTAP_FAIL_ID = 29,
	FMTSTR_MAX_ID
} log_fmtstr_id_t;

#include <packed_section_end.h>

#include <packed_section_start.h>

#define VNDR_IE_CMD_LEN		4	

#define VNDR_IE_BEACON_FLAG	0x1
#define VNDR_IE_PRBRSP_FLAG	0x2
#define VNDR_IE_ASSOCRSP_FLAG	0x4
#define VNDR_IE_AUTHRSP_FLAG	0x8
#define VNDR_IE_PRBREQ_FLAG	0x10
#define VNDR_IE_ASSOCREQ_FLAG	0x20
#define VNDR_IE_CUSTOM_FLAG	0x100 

#define VNDR_IE_INFO_HDR_LEN	(sizeof(uint32))

typedef BWL_PRE_PACKED_STRUCT struct {
	uint32 pktflag;			
	vndr_ie_t vndr_ie_data;		
} BWL_POST_PACKED_STRUCT vndr_ie_info_t;

typedef BWL_PRE_PACKED_STRUCT struct {
	int iecount;			
	vndr_ie_info_t vndr_ie_list[1];	
} BWL_POST_PACKED_STRUCT vndr_ie_buf_t;

typedef BWL_PRE_PACKED_STRUCT struct {
	char cmd[VNDR_IE_CMD_LEN];	
	vndr_ie_buf_t vndr_ie_buffer;	
} BWL_POST_PACKED_STRUCT vndr_ie_setbuf_t;

typedef BWL_PRE_PACKED_STRUCT struct sta_prbreq_wps_ie_hdr {
	struct ether_addr staAddr;
	uint16 ieLen;
} BWL_POST_PACKED_STRUCT sta_prbreq_wps_ie_hdr_t;

typedef BWL_PRE_PACKED_STRUCT struct sta_prbreq_wps_ie_data {
	sta_prbreq_wps_ie_hdr_t hdr;
	uint8 ieData[1];
} BWL_POST_PACKED_STRUCT sta_prbreq_wps_ie_data_t;

typedef BWL_PRE_PACKED_STRUCT struct sta_prbreq_wps_ie_list {
	uint32 totLen;
	uint8 ieDataList[1];
} BWL_POST_PACKED_STRUCT sta_prbreq_wps_ie_list_t;

#include <packed_section_end.h>

#define ASSERTLOG_CUR_VER	0x0100
#define MAX_ASSRTSTR_LEN	64

typedef struct assert_record {
	uint32 time;
	uint8 seq_num;
	char str[MAX_ASSRTSTR_LEN];
} assert_record_t;

typedef struct assertlog_results {
	uint16 version;
	uint16 record_len;
	uint32 num;
	assert_record_t logs[1];
} assertlog_results_t;

#define LOGRRC_FIX_LEN	8
#define IOBUF_ALLOWED_NUM_OF_LOGREC(type, len) ((len - LOGRRC_FIX_LEN)/sizeof(type))

#define BCM_ACTION_RFAWARE		0x77
#define BCM_ACTION_RFAWARE_DCS  0x01

#define BCM_DCS_IOVAR		0x1
#define BCM_DCS_UNKNOWN		0xFF

typedef struct wl_bcmdcs_data {
	uint reason;
	chanspec_t chspec;
} wl_bcmdcs_data_t;

#define WL_11N_2x2			1
#define WL_11N_3x3			3
#define WL_11N_4x4			4

#define WLFEATURE_DISABLE_11N		0x00000001
#define WLFEATURE_DISABLE_11N_STBC_TX	0x00000002
#define WLFEATURE_DISABLE_11N_STBC_RX	0x00000004
#define WLFEATURE_DISABLE_11N_SGI_TX	0x00000008
#define WLFEATURE_DISABLE_11N_SGI_RX	0x00000010
#define WLFEATURE_DISABLE_11N_AMPDU_TX	0x00000020
#define WLFEATURE_DISABLE_11N_AMPDU_RX	0x00000040
#define WLFEATURE_DISABLE_11N_GF	0x00000080

typedef struct {
	uint32 ipaddr;		
	uint32 ipaddr_mask;	
	uint32 ipaddr_gateway;	
	uint8 mac_gateway[6];	
	uint32 ipaddr_dns;	
	uint8 mac_dns[6];	
	uint8 GUID[38];		
} nat_if_info_t;

typedef struct {
	uint op;		
	bool pub_if;		
	nat_if_info_t if_info;	
} nat_cfg_t;

#define NAT_OP_ENABLE		1	
#define NAT_OP_DISABLE		2	
#define NAT_OP_DISABLE_ALL	3	

#define NAT_STATE_ENABLED	1	
#define NAT_STATE_DISABLED	2	

typedef struct {
	int state;	
} nat_state_t;

#define BTA_STATE_LOG_SZ	64

enum {
	HCIReset = 1,
	HCIReadLocalAMPInfo,
	HCIReadLocalAMPASSOC,
	HCIWriteRemoteAMPASSOC,
	HCICreatePhysicalLink,
	HCIAcceptPhysicalLinkRequest,
	HCIDisconnectPhysicalLink,
	HCICreateLogicalLink,
	HCIAcceptLogicalLink,
	HCIDisconnectLogicalLink,
	HCILogicalLinkCancel,
	HCIAmpStateChange,
	HCIWriteLogicalLinkAcceptTimeout
};

#define CHANNEL_5G_LOW_START	36	
#define CHANNEL_5G_MID_START	52	
#define CHANNEL_5G_HIGH_START	100	
#define CHANNEL_5G_UPPER_START	149	

enum {
	SPATIAL_MODE_2G_IDX = 0,
	SPATIAL_MODE_5G_LOW_IDX,
	SPATIAL_MODE_5G_MID_IDX,
	SPATIAL_MODE_5G_HIGH_IDX,
	SPATIAL_MODE_5G_UPPER_IDX,
	SPATIAL_MODE_MAX_IDX
};

#endif 
