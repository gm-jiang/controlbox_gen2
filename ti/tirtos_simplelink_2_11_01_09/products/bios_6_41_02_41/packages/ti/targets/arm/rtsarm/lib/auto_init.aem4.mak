#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.M4{1,0,5.1,5
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.oem4.dep
package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.oem4.dep: ;
endif

package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.oem4: | .interfaces
package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.oem4: package/package_ti.targets.arm.rtsarm.c lib/auto_init.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_5_1_5 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/auto_init/package -fr=./package/lib/lib/auto_init/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/auto_init/package -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_5_1_5 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/auto_init/package -fr=./package/lib/lib/auto_init/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.oem4: export C_DIR=
package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.sem4: | .interfaces
package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.sem4: package/package_ti.targets.arm.rtsarm.c lib/auto_init.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_5_1_5 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/auto_init/package -fr=./package/lib/lib/auto_init/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/auto_init/package -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -ms -g  -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_5_1_5 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/auto_init/package -fr=./package/lib/lib/auto_init/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.sem4: export C_DIR=
package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/auto_init/auto_init.oem4.dep
package/lib/lib/auto_init/auto_init.oem4.dep: ;
endif

package/lib/lib/auto_init/auto_init.oem4: | .interfaces
package/lib/lib/auto_init/auto_init.oem4: auto_init.asm lib/auto_init.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) asmem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -qq --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_5_1_5   $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fr=./package/lib/lib/auto_init -fa $<
	$(MKDEP) -a $@.dep -p package/lib/lib/auto_init -s oem4 $< -C  -qq --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_5_1_5   $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include 
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/auto_init/auto_init.oem4: export C_DIR=
package/lib/lib/auto_init/auto_init.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 ::
	-$(RM) package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.oem4
	-$(RM) package/lib/lib/auto_init/auto_init.oem4
	-$(RM) package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.sem4

lib/auto_init.aem4: package/lib/lib/auto_init/package/package_ti.targets.arm.rtsarm.oem4 package/lib/lib/auto_init/auto_init.oem4 lib/auto_init.aem4.mak

clean::
	-$(RM) lib/auto_init.aem4.mak
