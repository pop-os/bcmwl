/*
 * Misc useful os-independent macros and functions.
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
 * $Id: bcmutils.h 285775 2011-09-23 05:11:53Z $
 */

#ifndef	_bcmutils_h_
#define	_bcmutils_h_

struct bcmstrbuf {
	char *buf;	
	unsigned int size;	
	char *origbuf;	
	unsigned int origsize;	
};

#include <osl.h>

#define SPINWAIT(exp, us) { \
	uint countdown = (us) + 9; \
	while ((exp) && (countdown >= 10)) {\
		OSL_DELAY(10); \
		countdown -= 10; \
	} \
}

typedef struct pktq_prec {
	void *head;     
	void *tail;     
	uint16 len;     
	uint16 max;     
} pktq_prec_t;

#ifndef PKTPOOL_LEN_MAX
#define PKTPOOL_LEN_MAX		40
#endif 
#define PKTPOOL_CB_MAX		3

struct pktpool;
typedef void (*pktpool_cb_t)(struct pktpool *pool, void *arg);
typedef struct {
	pktpool_cb_t cb;
	void *arg;
} pktpool_cbinfo_t;

typedef struct pktpool {
	bool inited;
	uint16 r;
	uint16 w;
	uint16 len;
	uint16 maxlen;
	uint16 plen;
	bool istx;
	bool empty;
	uint8 cbtoggle;
	uint8 cbcnt;
	uint8 ecbcnt;
	bool emptycb_disable;
	pktpool_cbinfo_t *availcb_excl;
	pktpool_cbinfo_t cbs[PKTPOOL_CB_MAX];
	pktpool_cbinfo_t ecbs[PKTPOOL_CB_MAX];
	void *q[PKTPOOL_LEN_MAX + 1];

} pktpool_t;

struct ether_addr;

extern uint pktsetprio(void *pkt, bool update_vtag);

typedef struct bcm_iovar {
	const char *name;	
	uint16 varid;		
	uint16 flags;		
	uint16 type;		
	uint16 minlen;		
} bcm_iovar_t;

#define IOV_GET 0 
#define IOV_SET 1 

#define IOVT_VOID	0	
#define IOVT_BOOL	1	
#define IOVT_INT8	2	
#define IOVT_UINT8	3	
#define IOVT_INT16	4	
#define IOVT_UINT16	5	
#define IOVT_INT32	6	
#define IOVT_UINT32	7	
#define IOVT_BUFFER	8	
#define BCM_IOVT_VALID(type) (((unsigned int)(type)) <= IOVT_BUFFER)

#define BCM_IOV_TYPE_INIT { \
	"void", \
	"bool", \
	"int8", \
	"uint8", \
	"int16", \
	"uint16", \
	"int32", \
	"uint32", \
	"buffer", \
	"" }

#define BCM_IOVT_IS_INT(type) (\
	(type == IOVT_BOOL) || \
	(type == IOVT_INT8) || \
	(type == IOVT_UINT8) || \
	(type == IOVT_INT16) || \
	(type == IOVT_UINT16) || \
	(type == IOVT_INT32) || \
	(type == IOVT_UINT32))

#define BCME_STRLEN 		64	
#define VALID_BCMERROR(e)  ((e <= 0) && (e >= BCME_LAST))

#define BCME_OK				0	
#define BCME_ERROR			-1	
#define BCME_BADARG			-2	
#define BCME_BADOPTION			-3	
#define BCME_NOTUP			-4	
#define BCME_NOTDOWN			-5	
#define BCME_NOTAP			-6	
#define BCME_NOTSTA			-7	
#define BCME_BADKEYIDX			-8	
#define BCME_RADIOOFF 			-9	
#define BCME_NOTBANDLOCKED		-10	
#define BCME_NOCLK			-11	
#define BCME_BADRATESET			-12	
#define BCME_BADBAND			-13	
#define BCME_BUFTOOSHORT		-14	
#define BCME_BUFTOOLONG			-15	
#define BCME_BUSY			-16	
#define BCME_NOTASSOCIATED		-17	
#define BCME_BADSSIDLEN			-18	
#define BCME_OUTOFRANGECHAN		-19	
#define BCME_BADCHAN			-20	
#define BCME_BADADDR			-21	
#define BCME_NORESOURCE			-22	
#define BCME_UNSUPPORTED		-23	
#define BCME_BADLEN			-24	
#define BCME_NOTREADY			-25	
#define BCME_EPERM			-26	
#define BCME_NOMEM			-27	
#define BCME_ASSOCIATED			-28	
#define BCME_RANGE			-29	
#define BCME_NOTFOUND			-30	
#define BCME_WME_NOT_ENABLED		-31	
#define BCME_TSPEC_NOTFOUND		-32	
#define BCME_ACM_NOTSUPPORTED		-33	
#define BCME_NOT_WME_ASSOCIATION	-34	
#define BCME_SDIO_ERROR			-35	
#define BCME_DONGLE_DOWN		-36	
#define BCME_VERSION			-37 	
#define BCME_TXFAIL			-38 	
#define BCME_RXFAIL			-39	
#define BCME_NODEVICE			-40 	
#define BCME_NMODE_DISABLED		-41 	
#define BCME_LAST			BCME_NMODE_DISABLED

#ifndef ABS
#define	ABS(a)			(((a) < 0) ? -(a) : (a))
#endif 

#ifndef MIN
#define	MIN(a, b)		(((a) < (b)) ? (a) : (b))
#endif 

#ifndef MAX
#define	MAX(a, b)		(((a) > (b)) ? (a) : (b))
#endif 

#define CEIL(x, y)		(((x) + ((y) - 1)) / (y))
#define	ROUNDUP(x, y)		((((x) + ((y) - 1)) / (y)) * (y))
#define	ISALIGNED(a, x)		(((uintptr)(a) & ((x) - 1)) == 0)
#define ALIGN_ADDR(addr, boundary) (void *)(((uintptr)(addr) + (boundary) - 1) \
	                                         & ~((boundary) - 1))
#define ALIGN_SIZE(size, boundary) (((size) + (boundary) - 1) \
	                                         & ~((boundary) - 1))
#define	ISPOWEROF2(x)		((((x) - 1) & (x)) == 0)
#define VALID_MASK(mask)	!((mask) & ((mask) + 1))
#ifndef OFFSETOF
#define	OFFSETOF(type, member)	((uint)(uintptr)&((type *)0)->member)
#endif 
#ifndef ARRAYSIZE
#define ARRAYSIZE(a)		(sizeof(a) / sizeof(a[0]))
#endif

typedef struct bcm_tlv {
	uint8	id;
	uint8	len;
	uint8	data[1];
} bcm_tlv_t;

#define bcm_valid_tlv(elt, buflen) ((buflen) >= 2 && (int)(buflen) >= (int)(2 + (elt)->len))

#define ETHER_ADDR_STR_LEN	18	

#if defined(BCMDBG) || defined(DHD_DEBUG) || defined(BCMDBG_ERR) || \
	defined(BCMDBG_DUMP)
extern int bcm_format_flags(const bcm_bit_desc_t *bd, uint32 flags, char* buf, int len);
extern int bcm_format_hex(char *str, const void *bytes, int len);
#endif
extern bcm_tlv_t *BCMROMFN(bcm_parse_tlvs)(void *buf, int buflen, uint key);

typedef uint32 mbool;

extern int bcm_bprintf(struct bcmstrbuf *b, const char *fmt, ...);

extern uint16 BCMROMFN(bcm_qdbm_to_mw)(uint8 qdbm);
extern uint8 BCMROMFN(bcm_mw_to_qdbm)(uint16 mw);
extern uint bcm_mkiovar(char *name, char *data, uint datalen, char *buf, uint len);

unsigned int process_nvram_vars(char *varbuf, unsigned int len);

#endif	
