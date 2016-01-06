#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = c:/ti/tirtos_simplelink_2_11_01_09/packages;/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/uia_2_00_02_39/packages;/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages;
override XDCROOT = /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core
override XDCBUILDCFG = /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/tirtos.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = profile='release' CCWareDir='/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2' CC26xxWareDir='/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/cc26xxware_2_20_06_14829' ti.targets.arm.elf.M3='/db/vendors/ti/arm/5.1.5/Linux' ti.targets.arm.elf.M4='/db/vendors/ti/arm/5.1.5/Linux' iar.targets.arm.M3='/db/vendors/iar/arm/7.20.1/Linux' iar.targets.arm.M4='/db/vendors/iar/arm/7.20.1/Linux' gnu.targets.arm.M3='/db/vendors/linaro/gcc-arm-none-eabi-4_7-2013q3' gnu.targets.arm.M4='/db/vendors/linaro/gcc-arm-none-eabi-4_7-2013q3'
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = c:/ti/tirtos_simplelink_2_11_01_09/packages;/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/uia_2_00_02_39/packages;/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages;/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages;../..
HOSTOS = Linux
endif
