/*
 * tkmic.h
 * Prototypes for TKIP Message Integrity Check (MIC) functions.
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
 * $Id: tkmic.h 326246 2012-04-06 19:08:11Z $
 */

#ifndef _TKMIC_H_
#define _TKMIC_H_

#include <typedefs.h>

#define ROTR32(x, n)	(((x)<<(32-(n))) | ((uint32)(x)>>(n)))

#define ROTL32(x, n)	ROTR32(x, 32-n)
#define XSWAP32(x)	((((x)>> 8) & 0x00ff00ff) | (((x)<< 8) & 0xff00ff00))

extern void BCMROMFN(tkip_mic)(uint32 k0, uint32 k1, int n, uint8 *m, uint32 *left, uint32 *right);

extern int BCMROMFN(tkip_mic_eom)(uint8 *m, uint n, uint o);

#endif 
