#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.M4{1,0,4.7,4
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.om4g.dep
package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.om4g.dep: ;
endif

package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.om4g: | .interfaces
package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.om4g: package/package_ti.uia.sysbios.c lib/release/ti.uia.sysbios.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.sm4g: | .interfaces
package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.sm4g: package/package_ti.uia.sysbios.c lib/release/ti.uia.sysbios.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.sm4g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.om4g.dep
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.om4g.dep: ;
endif

package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.om4g: | .interfaces
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.om4g: LoggerStreamer.c lib/release/ti.uia.sysbios.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.sm4g: | .interfaces
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.sm4g: LoggerStreamer.c lib/release/ti.uia.sysbios.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.sm4g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.om4g.dep
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.om4g.dep: ;
endif

package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.om4g: | .interfaces
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.om4g: LoggerStreamer2.c lib/release/ti.uia.sysbios.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.sm4g: | .interfaces
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.sm4g: LoggerStreamer2.c lib/release/ti.uia.sysbios.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.sm4g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.sysbios/LoggerIdle.om4g.dep
package/lib/lib/release/ti.uia.sysbios/LoggerIdle.om4g.dep: ;
endif

package/lib/lib/release/ti.uia.sysbios/LoggerIdle.om4g: | .interfaces
package/lib/lib/release/ti.uia.sysbios/LoggerIdle.om4g: LoggerIdle.c lib/release/ti.uia.sysbios.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.sysbios/LoggerIdle.om4g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.sysbios/LoggerIdle.sm4g: | .interfaces
package/lib/lib/release/ti.uia.sysbios/LoggerIdle.sm4g: LoggerIdle.c lib/release/ti.uia.sysbios.am4g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm4g -S $< ...
	$(gnu.targets.arm.M4.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.sysbios/LoggerIdle.sm4g: export LD_LIBRARY_PATH=

clean,m4g ::
	-$(RM) package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.om4g
	-$(RM) package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.om4g
	-$(RM) package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.om4g
	-$(RM) package/lib/lib/release/ti.uia.sysbios/LoggerIdle.om4g
	-$(RM) package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.sm4g
	-$(RM) package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.sm4g
	-$(RM) package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.sm4g
	-$(RM) package/lib/lib/release/ti.uia.sysbios/LoggerIdle.sm4g

lib/release/ti.uia.sysbios.am4g: package/lib/lib/release/ti.uia.sysbios/package/package_ti.uia.sysbios.om4g package/lib/lib/release/ti.uia.sysbios/LoggerStreamer.om4g package/lib/lib/release/ti.uia.sysbios/LoggerStreamer2.om4g package/lib/lib/release/ti.uia.sysbios/LoggerIdle.om4g lib/release/ti.uia.sysbios.am4g.mak

clean::
	-$(RM) lib/release/ti.uia.sysbios.am4g.mak
