#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.M4{1,0,5.1,5
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.oem4: package/package_ti.sysbios.family.arm.lm4.c lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.sem4: package/package_ti.sysbios.family.arm.lm4.c lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.oem4: Seconds.c lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.sem4: Seconds.c lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.oem4: Timer.c lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.sem4: Timer.c lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.oem4: TimestampProvider.c lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.sem4: TimestampProvider.c lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4 -fr=./package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 ::
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.sem4

lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4: package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/package/package_ti.sysbios.family.arm.lm4.oem4 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Seconds.oem4 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/Timer.oem4 package/lib/lib/sysbios/debug/ti.sysbios.family.arm.lm4/TimestampProvider.oem4 lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak

clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.family.arm.lm4.aem4.mak
