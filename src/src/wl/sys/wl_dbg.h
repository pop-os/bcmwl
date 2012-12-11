/*
 * Minimal debug/trace/assert driver definitions for
 * Broadcom 802.11 Networking Adapter.
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
 * $Id: wl_dbg.h 261155 2011-05-23 23:51:32Z $
 */

#ifndef _wl_dbg_h_
#define _wl_dbg_h_

extern uint32 wl_msg_level;
extern uint32 wl_msg_level2;

#if 0 && (VERSION_MAJOR > 9)
#include <IOKit/apple80211/IO8Log.h>
#define WL_PRINT(args)		do { printf args; IO8Log args; } while (0)
#else
#define WL_PRINT(args)		printf args
#endif

#ifdef BCMDBG

#define	WL_NONE(args)		do {if (wl_msg_level & 0) WL_PRINT(args);} while (0)

#define	WL_ERROR(args)		do {if (wl_msg_level & WL_ERROR_VAL) WL_PRINT(args);} while (0)
#define	WL_TRACE(args)		do {if (wl_msg_level & WL_TRACE_VAL) WL_PRINT(args);} while (0)

#else	

#define WL_NONE(args)

#ifdef BCMDBG_ERR
#define	WL_ERROR(args)		WL_PRINT(args)
#else
#define	WL_ERROR(args)
#endif 
#define	WL_TRACE(args)
#define WL_APSTA_UPDN(args)
#define WL_APSTA_RX(args)
#define WL_WSEC(args)
#define WL_WSEC_DUMP(args)

#endif 

extern uint32 wl_msg_level;
extern uint32 wl_msg_level2;
#endif 
