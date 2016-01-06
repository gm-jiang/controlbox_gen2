#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.M3{1,0,4.7,4
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.om3g.dep
package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.om3g.dep: ;
endif

package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.om3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.om3g: package/package_ti.uia.runtime.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.om3g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.sm3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.sm3g: package/package_ti.uia.runtime.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.runtime/CtxFilter.om3g.dep
package/lib/lib/release/ti.uia.runtime/CtxFilter.om3g.dep: ;
endif

package/lib/lib/release/ti.uia.runtime/CtxFilter.om3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/CtxFilter.om3g: CtxFilter.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/CtxFilter.om3g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.runtime/CtxFilter.sm3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/CtxFilter.sm3g: CtxFilter.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/CtxFilter.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.runtime/LoggerSM.om3g.dep
package/lib/lib/release/ti.uia.runtime/LoggerSM.om3g.dep: ;
endif

package/lib/lib/release/ti.uia.runtime/LoggerSM.om3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/LoggerSM.om3g: LoggerSM.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/LoggerSM.om3g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.runtime/LoggerSM.sm3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/LoggerSM.sm3g: LoggerSM.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/LoggerSM.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.runtime/LogSnapshot.om3g.dep
package/lib/lib/release/ti.uia.runtime/LogSnapshot.om3g.dep: ;
endif

package/lib/lib/release/ti.uia.runtime/LogSnapshot.om3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/LogSnapshot.om3g: LogSnapshot.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/LogSnapshot.om3g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.runtime/LogSnapshot.sm3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/LogSnapshot.sm3g: LogSnapshot.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/LogSnapshot.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.runtime/LogSync.om3g.dep
package/lib/lib/release/ti.uia.runtime/LogSync.om3g.dep: ;
endif

package/lib/lib/release/ti.uia.runtime/LogSync.om3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/LogSync.om3g: LogSync.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/LogSync.om3g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.runtime/LogSync.sm3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/LogSync.sm3g: LogSync.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/LogSync.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.runtime/QueueDescriptor.om3g.dep
package/lib/lib/release/ti.uia.runtime/QueueDescriptor.om3g.dep: ;
endif

package/lib/lib/release/ti.uia.runtime/QueueDescriptor.om3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/QueueDescriptor.om3g: QueueDescriptor.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/QueueDescriptor.om3g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.runtime/QueueDescriptor.sm3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/QueueDescriptor.sm3g: QueueDescriptor.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/QueueDescriptor.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.runtime/ServiceMgr.om3g.dep
package/lib/lib/release/ti.uia.runtime/ServiceMgr.om3g.dep: ;
endif

package/lib/lib/release/ti.uia.runtime/ServiceMgr.om3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/ServiceMgr.om3g: ServiceMgr.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/ServiceMgr.om3g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.runtime/ServiceMgr.sm3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/ServiceMgr.sm3g: ServiceMgr.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/ServiceMgr.sm3g: export LD_LIBRARY_PATH=

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.runtime/UIAPacket.om3g.dep
package/lib/lib/release/ti.uia.runtime/UIAPacket.om3g.dep: ;
endif

package/lib/lib/release/ti.uia.runtime/UIAPacket.om3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/UIAPacket.om3g: UIAPacket.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c  -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2  -I/db/vtree/library/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/bios_6_41_02_41/packages/gnu/targets/arm//libs/install-native/arm-none-eabi/include   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/UIAPacket.om3g: export LD_LIBRARY_PATH=

package/lib/lib/release/ti.uia.runtime/UIAPacket.sm3g: | .interfaces
package/lib/lib/release/ti.uia.runtime/UIAPacket.sm3g: UIAPacket.c lib/release/ti.uia.runtime.am3g.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clm3g -S $< ...
	$(gnu.targets.arm.M3.rootDir)/bin/arm-none-eabi-gcc -c -MD -MF $@.dep -x c -S -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m3 -mthumb -mabi=aapcs -g -Dfar= -D__DYNAMIC_REENT__  -g  -Dxdc_target_name__=M3 -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_7_4  -O2   $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/release/ti.uia.runtime/UIAPacket.sm3g: export LD_LIBRARY_PATH=

clean,m3g ::
	-$(RM) package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.om3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/CtxFilter.om3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/LoggerSM.om3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/LogSnapshot.om3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/LogSync.om3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/QueueDescriptor.om3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/ServiceMgr.om3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/UIAPacket.om3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.sm3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/CtxFilter.sm3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/LoggerSM.sm3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/LogSnapshot.sm3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/LogSync.sm3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/QueueDescriptor.sm3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/ServiceMgr.sm3g
	-$(RM) package/lib/lib/release/ti.uia.runtime/UIAPacket.sm3g

lib/release/ti.uia.runtime.am3g: package/lib/lib/release/ti.uia.runtime/package/package_ti.uia.runtime.om3g package/lib/lib/release/ti.uia.runtime/CtxFilter.om3g package/lib/lib/release/ti.uia.runtime/LoggerSM.om3g package/lib/lib/release/ti.uia.runtime/LogSnapshot.om3g package/lib/lib/release/ti.uia.runtime/LogSync.om3g package/lib/lib/release/ti.uia.runtime/QueueDescriptor.om3g package/lib/lib/release/ti.uia.runtime/ServiceMgr.om3g package/lib/lib/release/ti.uia.runtime/UIAPacket.om3g lib/release/ti.uia.runtime.am3g.mak

clean::
	-$(RM) lib/release/ti.uia.runtime.am3g.mak
