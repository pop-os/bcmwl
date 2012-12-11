/*
 *
 * Memory pool type definitions
 *
 * Prealloc memory pools:
 *    These memory pools are memory allocators based on subdividing a single
 *    block of memory into homogenous objects. It's suitable for data structures
 *    with a statically configured maximum # of objects, such as using tunable
 *    parameters. It's not suitable for heterogenous data structures nor for
 *    data structures where the maximum count is unbounded.
 *
 *    Since the memory for all the objects is preallocated during initialization,
 *    that memory is unavailable to the rest of the system. This is appropriate both for
 *    small data structures, and for medium/large data structures where the peak and average
 *    utilization are similar. For data structures where average utilization is low but peak
 *    is very high, it's better to use the real heap so the memory gets freed when it's
 *    not in use.
 *
 *    Each individual memory pool can obtain it's memory from the user/client
 *    code or from the heap, as desired.
 *
 *
 * Heap memory pools:
 *    The memory pool allocator uses the heap (malloc/free) for memory.
 *    In this case, the pool allocator is just providing statistics and instrumentation
 *    on top of the heap, without modifying the heap allocation implementation.
 *
 * The memory pool component consists of two major abstractions:
 *     Manager: the factory for memory pools
 *     Pool: an individual pool that can allocate objects
 *
 * The memory pool manager maintains an array of individual pools so that instrumentation
 * can examine and manage all of them globally.
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
 * $Id$
 */

#ifndef _BCM_MPOOL_PRI_H
#define _BCM_MPOOL_PRI_H 1

#include "osl.h"
#include "typedefs.h"
#include "bcm_mpool_pub.h"

typedef struct bcm_mp_free_list {
	struct bcm_mp_free_list *next;  
} bcm_mp_free_list_t;

typedef struct bcm_mp_prealloc_pool {

	uint16             nobj;             
	unsigned int       padded_objsz;     
	void               *malloc_memstart; 
	bcm_mp_free_list_t *free_objp;       
} bcm_mp_prealloc_pool_t;

typedef struct bcm_mp_heap_pool {

	osl_t *osh;   
} bcm_mp_heap_pool_t;

typedef struct bcm_mp_pool {

	char   name[BCM_MP_NAMELEN];      
	unsigned int objsz;               
	uint16 num_alloc;                 
	uint16 high_water;                
	uint16 failed_alloc;              
	uint16 flags;                     

	union {
		bcm_mp_prealloc_pool_t p;  
		bcm_mp_heap_pool_t     h;  
	} u;
} bcm_mp_pool_t;

#define BCM_MP_TYPE_MASK     0x0003 
#define BCM_MP_TYPE_HEAP     0      
#define BCM_MP_TYPE_PREALLOC 1      

#define BCM_MP_GET_POOL_TYPE(pool) (((pool)->flags) & BCM_MP_TYPE_MASK)
#define BCM_MP_SET_POOL_TYPE(pool, type) ((pool)->flags = ((pool)->flags & ~BCM_MP_TYPE_MASK) \
	                                                   | (type))

#define BCM_MP_POOL_IN_USE_MASK 0x0004

#define BCM_MP_SET_IN_USE(pool) ((pool)->flags |= BCM_MP_POOL_IN_USE_MASK)
#define BCM_MP_CLEAR_IN_USE(pool) ((pool)->flags &= ~BCM_MP_POOL_IN_USE_MASK)
#define BCM_MP_IS_IN_USE(pool) (((pool)->flags & BCM_MP_POOL_IN_USE_MASK) == \
	                                         BCM_MP_POOL_IN_USE_MASK)

typedef struct bcm_mpm_mgr {
	bcm_mp_pool_t      *pool_objs;   
	bcm_mp_free_list_t *free_pools;  
	uint16             npools;       
	uint16             max_pools;    
	osl_t              *osh;         
} bcm_mpm_mgr_t;

#endif 
