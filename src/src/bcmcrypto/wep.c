/*
 *   wep.c - WEP functions
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
 * $Id: wep.c 326246 2012-04-06 19:08:11Z $
 */

#include <typedefs.h>

#include <osl.h>

#include <bcmutils.h>
#include <bcmcrypto/rc4.h>
#include <bcmcrypto/wep.h>
#include <proto/802.11.h>

void
BCMROMFN(wep_encrypt)(uint buf_len, uint8 *buf, uint sec_len, uint8 *sec_data)
{
	uint8 key_data[16];
	uint32 ICV;
	rc4_ks_t ks;
	uint8 *body = buf + DOT11_IV_LEN;
	uint body_len = buf_len - (DOT11_IV_LEN + DOT11_ICV_LEN);
	uint8 *picv = body + body_len;

	memcpy(key_data, buf, 3);
	memcpy(&key_data[3], sec_data, sec_len);

	prepare_key(key_data, sec_len + 3, &ks);

	ICV = ~hndcrc32(body, body_len, CRC32_INIT_VALUE);
	picv[0] = ICV & 0xff;
	picv[1] = (ICV >> 8) & 0xff;
	picv[2] = (ICV >> 16) & 0xff;
	picv[3] = (ICV >> 24) & 0xff;

	rc4(body, body_len + DOT11_ICV_LEN, &ks);
}

bool
BCMROMFN(wep_decrypt)(uint buf_len, uint8 *buf, uint sec_len, uint8 *sec_data)
{
	uint8 key_data[16];
	rc4_ks_t ks;

	memcpy(key_data, buf, 3);
	memcpy(&key_data[3], sec_data, sec_len);

	prepare_key(key_data, sec_len + 3, &ks);

	rc4(buf + DOT11_IV_LEN, buf_len - DOT11_IV_LEN, &ks);

	return (hndcrc32(buf + DOT11_IV_LEN, buf_len - DOT11_IV_LEN, CRC32_INIT_VALUE) ==
		CRC32_GOOD_VALUE);
}
