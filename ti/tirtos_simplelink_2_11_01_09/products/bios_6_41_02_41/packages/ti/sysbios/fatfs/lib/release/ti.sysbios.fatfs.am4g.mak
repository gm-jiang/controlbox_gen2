#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.M4{1,0,4.7,4
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.om4g.dep
package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.om4g.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.om4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.om4g: package/package_ti.sysbios.fatfs.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.sm4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.sm4g: package/package_ti.sysbios.fatfs.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.sm4g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/ff.om4g.dep
package/lib/lib/release/ti.sysbios.fatfs/ff.om4g.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/ff.om4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/ff.om4g: ff.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/ff.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.sysbios.fatfs/ff.sm4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/ff.sm4g: ff.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/ff.sm4g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/diskio.om4g.dep
package/lib/lib/release/ti.sysbios.fatfs/diskio.om4g.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/diskio.om4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/diskio.om4g: diskio.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/diskio.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.sysbios.fatfs/diskio.sm4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/diskio.sm4g: diskio.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/diskio.sm4g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/ramdisk.om4g.dep
package/lib/lib/release/ti.sysbios.fatfs/ramdisk.om4g.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/ramdisk.om4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/ramdisk.om4g: ramdisk.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/ramdisk.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.sysbios.fatfs/ramdisk.sm4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/ramdisk.sm4g: ramdisk.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/ramdisk.sm4g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.om4g.dep
package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.om4g.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.om4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.om4g: syncsysbios.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.sm4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.sm4g: syncsysbios.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.sm4g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/memsysbios.om4g.dep
package/lib/lib/release/ti.sysbios.fatfs/memsysbios.om4g.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/memsysbios.om4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/memsysbios.om4g: memsysbios.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/memsysbios.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.sysbios.fatfs/memsysbios.sm4g: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/memsysbios.sm4g: memsysbios.c lib/release/ti.sysbios.fatfs.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.sysbios.fatfs/memsysbios.sm4g: export LD_LIBRARY_PATH=

clean,m4g ::
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.om4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/ff.om4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/diskio.om4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/ramdisk.om4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.om4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/memsysbios.om4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.sm4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/ff.sm4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/diskio.sm4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/ramdisk.sm4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.sm4g
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/memsysbios.sm4g

lib/release/ti.sysbios.fatfs.am4g: package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.om4g package/lib/lib/release/ti.sysbios.fatfs/ff.om4g package/lib/lib/release/ti.sysbios.fatfs/diskio.om4g package/lib/lib/release/ti.sysbios.fatfs/ramdisk.om4g package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.om4g package/lib/lib/release/ti.sysbios.fatfs/memsysbios.om4g lib/release/ti.sysbios.fatfs.am4g.mak

clean::
	-$(RM) lib/release/ti.sysbios.fatfs.am4g.mak
