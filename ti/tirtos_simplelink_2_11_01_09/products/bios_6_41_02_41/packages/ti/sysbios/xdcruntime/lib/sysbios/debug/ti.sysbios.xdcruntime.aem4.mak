#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.M4{1,0,5.1,5
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.oem4: package/package_ti.sysbios.xdcruntime.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.sem4: package/package_ti.sysbios.xdcruntime.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.oem4: GateThreadSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.sem4: GateThreadSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.oem4: GateProcessSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.sem4: GateProcessSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.oem4: SemThreadSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.sem4: SemThreadSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.oem4: SemProcessSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.sem4: SemProcessSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.oem4: ThreadSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.sem4: ThreadSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.oem4.dep
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.oem4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.oem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.oem4: CacheSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.oem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.sem4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.sem4: CacheSupport.c lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_1_5 --symdebug:dwarf  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime -fr=./package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.sem4: export C_DIR=
package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 ::
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.oem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.sem4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.sem4

lib/sysbios/debug/ti.sysbios.xdcruntime.aem4: package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/package/package_ti.sysbios.xdcruntime.oem4 package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateThreadSupport.oem4 package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/GateProcessSupport.oem4 package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemThreadSupport.oem4 package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/SemProcessSupport.oem4 package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/ThreadSupport.oem4 package/lib/lib/sysbios/debug/ti.sysbios.xdcruntime/CacheSupport.oem4 lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak

clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.xdcruntime.aem4.mak
