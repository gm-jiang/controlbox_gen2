#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /packages;/packages;/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages
override XDCROOT = /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core
override XDCBUILDCFG = /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/uia_2_00_02_39/uia.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = ti.targets.C28_large="" ti.targets.C28_float="" ti.targets.C64P="" ti.targets.C64P_big_endian="" ti.targets.C64T="" ti.targets.C674="" ti.targets.arm.elf.Arm9="" ti.targets.arm.elf.A8Fnv="" ti.targets.arm.elf.M3="/db/vendors/ti/arm/5.1.5/Linux" ti.targets.arm.elf.M4="/db/vendors/ti/arm/5.1.5/Linux" ti.targets.arm.elf.M4F="" ti.targets.elf.C64P="" ti.targets.elf.C64P_big_endian="" ti.targets.elf.C64T="" ti.targets.elf.C66="" ti.targets.elf.C66_big_endian="" ti.targets.elf.C674="" ti.targets.msp430.elf.MSP430X="" ti.targets.msp430.elf.MSP430X_small="" ti.targets.arp32.elf.ARP32="" ti.targets.arp32.elf.ARP32_far="" gnu.targets.arm.M3="/db/vendors/linaro/gcc-arm-none-eabi-4_7-2013q3" gnu.targets.arm.M4="/db/vendors/linaro/gcc-arm-none-eabi-4_7-2013q3" gnu.targets.arm.M4F="" gnu.targets.arm.A8F="" gnu.targets.arm.A9F="" gnu.targets.arm.A15F="" iar.targets.msp430.MSP430X_small="" iar.targets.arm.M3="/db/vendors/iar/arm/7.20.1/Linux" iar.targets.arm.M4="/db/vendors/iar/arm/7.20.1/Linux" iar.targets.arm.M4F=""
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /packages;/packages;/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages;/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages;../../..
HOSTOS = Linux
endif
