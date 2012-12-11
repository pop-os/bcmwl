/*
 * rc4.c
 * RC4 stream cipher
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
 * $Id: rc4.c 326246 2012-04-06 19:08:11Z $
 */

#include <typedefs.h>
#include <bcmcrypto/rc4.h>

void
BCMROMFN(prepare_key)(uint8 *key_data, int key_data_len, rc4_ks_t *ks)
{
	unsigned int counter, index1 = 0, index2 = 0;
	uint8 key_byte, temp;
	uint8 *key_state = ks->state;

	for (counter = 0; counter < RC4_STATE_NBYTES; counter++) {
		key_state[counter] = (uint8) counter;
	}

	for (counter = 0; counter < RC4_STATE_NBYTES; counter++) {
		key_byte = key_data[index1];
		index2 = (key_byte + key_state[counter] + index2) % RC4_STATE_NBYTES;
		temp = key_state[counter];
		key_state[counter] = key_state[index2];
		key_state[index2] = temp;
		index1 = (index1 + 1) % key_data_len;
	}

	ks->x = 0;
	ks->y = 0;
}

void
BCMROMFN(rc4)(uint8 *buf, int data_len, rc4_ks_t *ks)
{
	uint8 tmp;
	uint8 xor_ind, x = ks->x, y = ks->y, *key_state = ks->state;
	int i;

	for (i = 0; i < data_len; i++) {
		y += key_state[++x]; 
		tmp = key_state[x];
		key_state[x] = key_state[y];
		key_state[y] = tmp;
		xor_ind = key_state[x] + key_state[y];
		buf[i] ^= key_state[xor_ind];
	}

	ks->x = x;
	ks->y = y;
}
