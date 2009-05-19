April 27, 2009
Linux kernel space driver 5.10.91.9 GOLD


DISCLAIMER
----------

This is the OFFICIAL GOLD release of Broadcom's Linux kernel space hybrid driver for
use with Broadcom BCM43224-based (device ID 4353) hardware.


IMPORTANT NOTE AND DISCUSSION OF HYBRID DRIVER
----------------------------------------------

There are different tar's for 32-bit and 64-bit x86 CPU architectures.  Make sure you use
the appropriate tar, as the hybrid binary must be of the appropriate architectural type.

Otherwise the hybrid binary is agnostic to the specific version of Linux kernel
because it is designed to perform all interactions with the OS through OS specific
files (wl_linux.c, wl_iw.c) and an OS abstraction layer file (osl_linux.c). 
All of these interactions are done through functions which make the hybrid binary
OS version independent.  All Linux OS specific code is provided in source form
allowing re-targeting to different kernel versions and fixing OS related issues.


BUILD AND INSTALLATION INSTRUCTIONS
-----------------------------------

hybrid-portsrc-x86_32-v5_10_91_9.tar.gz
hybrid-portsrc-x86_64-v5_10_91_9.tar.gz

On the target machine, setup the source/hybrid/build directory

1.  Create a new directory:                 mkdir hybrid_wl
2.  Go to that directory:                   cd hybrid_wl
3.  Untar the appropriate 32/64 bit file
      to that directory
        32 bit:                             tar -xzf <path>/hybrid-portsrc-x86_32-v5_10_91_9.tar.gz
        64 bit:                             tar -xzf <path>/hybrid-portsrc-x86_64-v5_10_91_9.tar.gz

After untar'ing you should have a src and lib sub directory plus a Linux
2.6 "kbuild" external makefile (Makefile).   The lib sub directory has the pre-built
binary, wlc_hybrid.o_shipped.  

You use the standard Linux 2.6 kernel build system as follows to make a Linux loadable
kernel module (LKM):

On the target machine, and cd'ed to the directory that contains the Makefile (fragment)

4.  Cleanup (optional):                  make -C /lib/modules/<2.6.xx.xx>/build M=`pwd` clean
5.  Build the LKM, i.e. wl.ko:           make -C /lib/modules/<2.6.xx.xx>/build M=`pwd`

You should now have a LKM, wl.ko inside this directory.

On this or a machine with the same kernel version, install the driver.

1.  Validate you don't have loaded (or built into the kernel) the Linux community provided
      driver for Broadcom hardware.  This exists in two forms: either "bcm43xx" or a split form
      of "b43" plus "b43legacy".  If these modules were loaded you would either
        a) rmmod bcm43xx or
        b) rmmod b43; rmmod b43legacy
1a. Validate you don't have a older wl.ko driver loaded from previous install.
      If the module exist, remove it and replace with new driver:
        a) rmmod wl.ko
2.  Replacing existing driver with wl.ko just build in step 5 above.
      (most likely path to find wl.ko is: /lib/modules/<kernel_version>/kernel/driver/net/wireless
       or /lib/modules/<kernel_version>/kernel.net/update/)
3.  depmod
4.  modprobe wl

Some kernels come with a pre-installed Broadcom driver that supports Broadcom's 43xx family of
PCIE cards.  If the kernel supports one of those pre-installed driver, you must remove it in order
to install the new driver.  Some of the existing drivers provided by the Linux community that support
Broadcom hardware are b43/b43legacy/bcm43xx.  There is also a ssb driver that is loaded along with
b43.  This ssb driver also must be removed.

If the kernel supports blacklist, you can add those drivers to the blacklist file so that it will
not be loaded on next reboot.


ISSUES FIXED IN THIS RELEASE
----------------------------
#72138 - SLED11 / Ubuntu 8.04: 43224 fails to associate after 6 hours


KNOWN ISSUES AND LIMITATIONS
----------------------------
#72238 - 20% lower throughput on channels 149, 153, 157, and 161
#72324 - Ubuntu 8.04: cannot ping when Linux STA is IBSS creator with WEP enabled
#72216 - Ubuntu 8.04: standby/resume with WPA2 and wpa_supplicant causes a continuous assoc/disassoc loop
         (issue with wpa_supplicant, restarting wpa_supplicant fixes the issue)
