
September 10, 2009
Linux kernel space hybrid driver 5.10.91.9.3 Gold

DISCLAIMER
----------

This is an Official Release of Broadcom's hybrid Linux driver for use with Broadcom
based hardware.

IMPORTANT NOTE AND DISCUSSION OF HYBRID DRIVER
----------------------------------------------

There are different tar's for 32 bit and 64 bit x86 CPU architectures.  Make sure you use the
appropriate tar, as the hybrid binary must be of the appropriate architectural type.

Otherwise the hybrid binary is agnostic to the specific version of Linux kernel
because it is designed to perform all interactions with the OS through OS specific
files (wl_linux.c, wl_iw.c, osl_linux.c) that are shipped in source form. You compile 
this source on your system and link with a precompiled .o file (wlc_hybrid.o_shipped) 
which contains the rest of the driver.

ABOUT THIS RELEASE
-------------------
This is a rollup release.  It includes and depracates all previous releases and
patches.  At the time of release there are no existing applicable patches for this
release from Broadcom.


BUILD AND INSTALLATION INSTRUCTIONS
-----------------------------------

1. Setup the directory by untarring the proper tarball:

For 32 bit: 	hybrid-portsrc.tar.gz
For 64 bit: 	hybrid-portsrc-x86_64.tar.gz

# mkdir hybrid_wl
# cd hybrid_wl
# tar xzf <path>/hybrid-portsrc.tar or <path>/hybrid-portsrc-x86_64.tar.gz

2. Build the driver as a Linux loadable kernel module (LKM):

# make clean   (optional)
# make

When the build completes, it will produce a wl.ko file in the top level
directory.

3: Remove any other drivers for the Broadcom wireless.

There are several open source drivers that are used to drive Broadcom 802.11
chips such as b43 and ssb. If any of these are present they need to be removed before this 
driver can be installed.  Any previous revisions of the wl driver also need to
be removed.

# lsmod  | grep "b43\|ssb\|wl"

If any of these are installed, remove them:
# rmmod b43
# rmmod ssb
# rmmod wl

To blacklist these drivers and prevent them from loading in the future:
# echo "blacklist ssb" >> /etc/modprobe.d/blacklist.conf
# echo "blacklist b43" >> /etc/modprobe.d/blacklist.conf

4: Insmod the driver.

If you were already running a previous version of wl, you'll want to provide a
clean transition from the older driver. (The path to previous driver is usually
/lib/modules/<kernel-version>/kernel/net/wireless)

# rmmod wl 
# mv <path-to-prev-driver>/wl.ko <path-to-prev-driver>/wl.ko.orig
# cp wl.ko <path-to-prev-driver>/wl.ko
# depmod
# modprobe wl

Otherwise, if you have not previously installed a wl driver do this:

# modprobe lib80211
# insmod wl.ko

wl.ko is now operational.  It may take several seconds for the Network Manager
to notice a new network driver has been installed and show the surrounding
wireless networks.

COMMON ISSUES/QUESTIONS
-----------------------

If there is a problem, usually some clues can be gleaned from the system log
via the 'dmesg' command.

Why aren't channels 12 & 13 supported?  The driver only supports the default
locale setting wich is ROW (Rest Of World) which does not include channels 12 or 13.

I see this output, is it harmful?  WARNING: modpost: missing MODULE_LICENSE()
No it is not harmful and it is expected and should be ignored.

Is my Brcm device with PCI Device ID XYZ Supported?  These PCI Device IDs are supported:

	  Device ID	Product Name
          ---------   	-------------
          0x4311  	4311 2.4 Ghz
          0x4312  	4311 Dualband
          0x4313  	4311 5 Ghz
          0x4315  	4312 2.4 Ghz
          0x4328  	4321 Dualband
          0x4329  	4321 2.4 Ghz
          0x432a  	4321 5 Ghz
          0x432b  	4322 Dualband
          0x432c  	4322 2.4 Ghz
          0x432d  	4322 5 Ghz
          0x4353  	43224 Dualband
          0x4357  	43225 2.4 Ghz


ISSUES FIXED AND WHAT'S NEW IN THIS RELEASE
-------------------------------------------
+ Supports Linux kernel 2.6.29, 2.6.30.1, 2.6.31
+ Supports hidden networks
+ Supports rfkill in kernels <  2.6.31


KNOWN ISSUES AND LIMITATIONS
----------------------------
#72238 - 20% lower throughput on channels 149, 153, 157, and 161
#72324 - Ubuntu 8.04: cannot ping when Linux STA is IBSS creator with WEP enabled
#72216 - Ubuntu 8.04: standby/resume with WPA2 and wpa_supplicant causes a continuous 
	assoc/disassoc loop (issue with wpa_supplicant, restarting wpa_supplicant fixes the issue)
#76739 Ubuntu9.04: unable to connect to hidden network after stdby/resume
#76793 Ubuntu9.04: STA fails to create IBSS network in 5 Ghz band
#76814 Wireless option is Grayed out in Network Manager in FC-11-64bit

