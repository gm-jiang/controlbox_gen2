#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = ti/sysbios/family/arm/cc26xx
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/utils.js:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/utils.js
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/xdc.tci:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/xdc.tci
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/template.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/template.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/om2.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/om2.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/xmlgen.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/xmlgen.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/xmlgen2.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/xmlgen2.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/Warnings.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/Warnings.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/IPackage.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/IPackage.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/package.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/package.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/services/global/Clock.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/services/global/Clock.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/services/global/Trace.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/services/global/Trace.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/bld.js:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/bld.js
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/BuildEnvironment.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/BuildEnvironment.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/PackageContents.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/PackageContents.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/_gen.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/_gen.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Library.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Library.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Executable.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Executable.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Repository.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Repository.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Configuration.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Configuration.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Script.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Script.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Manifest.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Manifest.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Utils.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/Utils.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/ITarget.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/ITarget.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/ITarget2.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/ITarget2.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/ITarget3.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/ITarget3.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/ITargetFilter.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/ITargetFilter.xs
/db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/package.xs:
package.mak: /db/rtree/library/trees/xdcprod/xdcprod-t67/product/xdccore/Linux/xdctools_3_30_06_67_core/packages/xdc/bld/package.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/bios.bld:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/bios.bld
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/ITarget.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/ITarget.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/C28_large.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/C28_large.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/C28_float.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/C28_float.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/package.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/package.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/arm/elf/IArm.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/arm/elf/IArm.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/arm/elf/package.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/arm/elf/package.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/ITarget.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/ITarget.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/_utils.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/_utils.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/Linux86.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/Linux86.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/Mingw.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/Mingw.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/package.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/package.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/ITarget.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/ITarget.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/GCArmv6.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/GCArmv6.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/GCArmv7A.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/GCArmv7A.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/IM.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/IM.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/M3.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/M3.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/M4.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/M4.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/M4F.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/M4F.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/A8F.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/A8F.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/A9F.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/A9F.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/A15F.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/A15F.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/package.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/package.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/iar/targets/arm/ITarget.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/iar/targets/arm/ITarget.xs
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/iar/targets/arm/package.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/iar/targets/arm/package.xs
package.mak: package.bld
/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/sysbios/Build.xs:
package.mak: /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/sysbios/Build.xs
endif

ti.targets.arm.elf.M3.rootDir ?= /db/vendors/ti/arm/5.1.5/Linux
ti.targets.arm.elf.packageBase ?= /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/ti/targets/arm/elf/
gnu.targets.arm.M3.rootDir ?= /db/vendors/linaro/gcc-arm-none-eabi-4_7-2013q3
gnu.targets.arm.packageBase ?= /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm/
iar.targets.arm.M3.rootDir ?= /db/vendors/iar/arm/7.20.1/Linux
iar.targets.arm.packageBase ?= /db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/iar/targets/arm/
.PRECIOUS: $(XDCCFGDIR)/%.oem3
.PHONY: all,em3 .dlls,em3 .executables,em3 test,em3
all,em3: .executables,em3
.executables,em3: .libraries,em3
.executables,em3: .dlls,em3
.dlls,em3: .libraries,em3
.libraries,em3: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,em3
	@$(ECHO) xdc .executables,em3
	@$(ECHO) xdc .libraries,em3
	@$(ECHO) xdc .dlls,em3

.PRECIOUS: $(XDCCFGDIR)/%.om3g
.PHONY: all,m3g .dlls,m3g .executables,m3g test,m3g
all,m3g: .executables,m3g
.executables,m3g: .libraries,m3g
.executables,m3g: .dlls,m3g
.dlls,m3g: .libraries,m3g
.libraries,m3g: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,m3g
	@$(ECHO) xdc .executables,m3g
	@$(ECHO) xdc .libraries,m3g
	@$(ECHO) xdc .dlls,m3g

.PRECIOUS: $(XDCCFGDIR)/%.orm3
.PHONY: all,rm3 .dlls,rm3 .executables,rm3 test,rm3
all,rm3: .executables,rm3
.executables,rm3: .libraries,rm3
.executables,rm3: .dlls,rm3
.dlls,rm3: .libraries,rm3
.libraries,rm3: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,rm3
	@$(ECHO) xdc .executables,rm3
	@$(ECHO) xdc .libraries,rm3
	@$(ECHO) xdc .dlls,rm3

all,em4 clean,em4 .libraries,em4 .dlls,em4 .executables,em4 test,em4:;
all,m4g clean,m4g .libraries,m4g .dlls,m4g .executables,m4g test,m4g:;
all,rm4 clean,rm4 .libraries,rm4 .dlls,rm4 .executables,rm4 test,rm4:;

all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_ti.sysbios.family.arm.cc26xx.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package ti.sysbios.family.arm.cc26xx" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

ifeq (,$(MK_NOGENDEPS))
-include package/package.cfg.dep
endif

package/package.cfg.xdc.inc: .interfaces $(XDCROOT)/packages/xdc/cfg/cfginc.js package.xdc
	@$(MSG) generating schema include file list ...
	$(CONFIG) -f $(XDCROOT)/packages/xdc/cfg/cfginc.js ti.sysbios.family.arm.cc26xx $@

.libraries,em3 .libraries: lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.aem3

-include lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.aem3.mak
lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.aem3: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.oem3  into $@ ...
	$(ti.targets.arm.elf.M3.rootDir)/bin/armar  rq $@   package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.oem3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.oem3 
lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.aem3: export C_DIR=
lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.aem3: PATH:=$(ti.targets.arm.elf.M3.rootDir)/bin/:$(PATH)

clean,em3 clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.aem3
.libraries,m3g .libraries: lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.am3g

-include lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.am3g.mak
lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.am3g: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.om3g  into $@ ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-ar  cr $@   package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.om3g package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.om3g 
lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.am3g: export LD_LIBRARY_PATH=

clean,m3g clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.am3g
.libraries,rm3 .libraries: lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.arm3

-include lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.arm3.mak
lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.arm3: 
	$(RM) $@
	@$(MSG) archiving package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.orm3  into $@ ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iarchive --silent -o $@   package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.orm3 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.orm3 

clean,rm3 clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.arm3
test:;
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
package_ti.sysbios.family.arm.cc26xx.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.oem3
package_ti.sysbios.family.arm.cc26xx.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.sem3
Alarm.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.oem3
Alarm.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.sem3
Boot.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.oem3
Boot.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.sem3
Power.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.oem3
Power.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.sem3
Power_standbyPolicy.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.oem3
Power_standbyPolicy.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.sem3
Power_calibrateRCOSC.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.oem3
Power_calibrateRCOSC.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.sem3
pg2_leakage_workaround.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.oem3
pg2_leakage_workaround.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.sem3
Seconds.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.oem3
Seconds.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.sem3
Timer.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.oem3
Timer.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.sem3
TimestampProvider.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.oem3
TimestampProvider.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.sem3
TimerGPT.oem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.oem3
TimerGPT.sem3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.sem3
package_ti.sysbios.family.arm.cc26xx.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.om3g
package_ti.sysbios.family.arm.cc26xx.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.sm3g
Alarm.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.om3g
Alarm.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.sm3g
Boot.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.om3g
Boot.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.sm3g
Power.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.om3g
Power.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.sm3g
Power_standbyPolicy.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.om3g
Power_standbyPolicy.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.sm3g
Power_calibrateRCOSC.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.om3g
Power_calibrateRCOSC.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.sm3g
pg2_leakage_workaround.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.om3g
pg2_leakage_workaround.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.sm3g
Seconds.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.om3g
Seconds.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.sm3g
Timer.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.om3g
Timer.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.sm3g
TimestampProvider.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.om3g
TimestampProvider.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.sm3g
TimerGPT.om3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.om3g
TimerGPT.sm3g,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.sm3g
package_ti.sysbios.family.arm.cc26xx.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.orm3
package_ti.sysbios.family.arm.cc26xx.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package/package_ti.sysbios.family.arm.cc26xx.srm3
Alarm.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.orm3
Alarm.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Alarm.srm3
Boot.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.orm3
Boot.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Boot.srm3
Power.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.orm3
Power.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power.srm3
Power_standbyPolicy.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.orm3
Power_standbyPolicy.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_standbyPolicy.srm3
Power_calibrateRCOSC.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.orm3
Power_calibrateRCOSC.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Power_calibrateRCOSC.srm3
pg2_leakage_workaround.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.orm3
pg2_leakage_workaround.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/pg2_leakage_workaround.srm3
Seconds.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.orm3
Seconds.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Seconds.srm3
Timer.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.orm3
Timer.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/Timer.srm3
TimestampProvider.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.orm3
TimestampProvider.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimestampProvider.srm3
TimerGPT.orm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.orm3
TimerGPT.srm3,copy : package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/TimerGPT.srm3

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg $(XDCROOT)/packages/xdc/cfg/Main.xs | .interfaces
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,ti_sysbios_family_arm_cc26xx
ifeq (,$(MK_NOGENDEPS))
-include package/rel/ti_sysbios_family_arm_cc26xx.tar.dep
-include package/rel/ti_sysbios_family_arm_cc26xx.tar.rcl.dep
endif
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: package/package.bld.xml
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: package/build.cfg
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: package/package.xdc.inc
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: package.bld
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Power.xdt
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: PowerCC2650.h
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Boot.xdt
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Boot.xml
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Alarm.xml
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: TimestampProvider.xml
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: pg2_leakage_workaround.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Power_calibrateRCOSC.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Power.xml
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: package/package.cfg.xdc.inc
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.aem3
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: package/package_ti.sysbios.family.arm.cc26xx.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Alarm.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Boot.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Power.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Power_standbyPolicy.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Seconds.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: Timer.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: TimestampProvider.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: TimerGPT.c
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.am3g
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: lib/sysbios/debug/ti.sysbios.family.arm.cc26xx.arm3
package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

ti_sysbios_family_arm_cc26xx.tar: package/rel/ti_sysbios_family_arm_cc26xx.xdc.inc package/rel/ti_sysbios_family_arm_cc26xx/ti/sysbios/family/arm/cc26xx/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/ti_sysbios_family_arm_cc26xx.xdc.inc,package/rel/ti_sysbios_family_arm_cc26xx.tar.dep, ti/sysbios/libFilter.xs)


release release,ti_sysbios_family_arm_cc26xx: all ti_sysbios_family_arm_cc26xx.tar
clean:: .clean
	-$(RM) ti_sysbios_family_arm_cc26xx.tar
	-$(RM) package/rel/ti_sysbios_family_arm_cc26xx.xdc.inc
	-$(RM) package/rel/ti_sysbios_family_arm_cc26xx.tar.dep

clean:: .clean
	-$(RM) .libraries $(wildcard .libraries,*)
clean:: 
	-$(RM) .dlls $(wildcard .dlls,*)
#
# The following clean rule removes user specified
# generated files or directories.
#
	-$(RMDIR) lib/

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard lib))
    $(shell $(MKDIR) lib)
endif
ifeq (,$(wildcard lib/sysbios))
    $(shell $(MKDIR) lib/sysbios)
endif
ifeq (,$(wildcard lib/sysbios/debug))
    $(shell $(MKDIR) lib/sysbios/debug)
endif
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
ifeq (,$(wildcard package/lib/lib))
    $(shell $(MKDIR) package/lib/lib)
endif
ifeq (,$(wildcard package/lib/lib/sysbios))
    $(shell $(MKDIR) package/lib/lib/sysbios)
endif
ifeq (,$(wildcard package/lib/lib/sysbios/debug))
    $(shell $(MKDIR) package/lib/lib/sysbios/debug)
endif
ifeq (,$(wildcard package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx))
    $(shell $(MKDIR) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx)
endif
ifeq (,$(wildcard package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package))
    $(shell $(MKDIR) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.cc26xx/package)
endif
endif
clean::
	-$(RMDIR) package


