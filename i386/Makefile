
#
# Makefile fragment for Linux 2.6
# Broadcom 802.11abg Networking Device Driver
#
# Copyright 2008, Broadcom Corporation
# All Rights Reserved.
# 
# This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
# the contents of this file may not be disclosed to third parties, copied
# or duplicated in any form, in whole or in part, without the prior
# written permission of Broadcom Corporation.
#
# $Id: Makefile_kbuild_portsrc,v 1.1.2.4.84.1 2009/08/11 01:19:20 Exp $

obj-m              += wl.o

wl-objs            := 
wl-objs            += src/wl/sys/wl_linux.o
wl-objs            += src/wl/sys/wl_iw.o
wl-objs            += src/shared/linux_osl.o

EXTRA_CFLAGS       :=
EXTRA_CFLAGS       += -I$(src)/src/include
EXTRA_CFLAGS       += -I$(src)/src/wl/sys

EXTRA_LDFLAGS      := $(src)/lib/wlc_hybrid.o_shipped

all:
	KBUILD_NOPEDANTIC=1 make -C /lib/modules/`uname -r`/build M=`pwd`

clean:
	KBUILD_NOPEDANTIC=1 make -C /lib/modules/`uname -r`/build M=`pwd` clean

install:
	install -D -m 755 wl.ko /lib/modules/`uname -r`/kernel/drivers/net/wireless/wl.ko
