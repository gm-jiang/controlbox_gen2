#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.M4{1,0,5.1,5
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.oem4: package/package_ti.sysbios.gates.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates/package -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.sem4: package/package_ti.sysbios.gates.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates/package -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.oem4: GateHwi.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.sem4: GateHwi.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.oem4: GateAll.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.sem4: GateAll.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.oem4: GateSwi.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.sem4: GateSwi.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.oem4: GateTask.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.sem4: GateTask.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.oem4: GateTest.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.sem4: GateTest.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.oem4: GateMutex.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.sem4: GateMutex.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.oem4: GateMutexPri.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.sem4: GateMutexPri.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.oem4: GateSpinlock.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.sem4: GateSpinlock.c lib/sysbios/debug/ti.sysbios.gates.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.gates -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.gates -fr=./package/lib/lib/sysbios/debug/ti.sysbios.gates
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 ::
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.sem4

lib/sysbios/debug/ti.sysbios.gates.aem4: package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.oem4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.oem4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.oem4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.oem4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.oem4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.oem4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.oem4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.oem4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.oem4 lib/sysbios/debug/ti.sysbios.gates.aem4.mak

clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.gates.aem4.mak
