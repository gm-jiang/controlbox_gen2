#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = iar.targets.arm.M4{1,0,7.20,1
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.orm4: package/package_ti.sysbios.hal.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.srm4: package/package_ti.sysbios.hal.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.orm4: Cache.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.srm4: Cache.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.orm4: CacheNull.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.srm4: CacheNull.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.orm4: Core.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.srm4: Core.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.orm4: CoreNull.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.srm4: CoreNull.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.orm4: Hwi.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.srm4: Hwi.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.orm4: Hwi_stack.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.srm4: Hwi_stack.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.orm4: Hwi_startup.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.srm4: Hwi_startup.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.orm4: Power.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.srm4: Power.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.orm4: PowerNull.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.srm4: PowerNull.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.orm4: Seconds.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.srm4: Seconds.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.orm4: SecondsCallback.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.srm4: SecondsCallback.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.orm4: SecondsClock.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.srm4: SecondsClock.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.orm4: Timer.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.srm4: Timer.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.orm4: TimerNull.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.srm4: TimerNull.c lib/sysbios/debug/ti.sysbios.hal.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

clean,rm4 ::
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.srm4

lib/sysbios/debug/ti.sysbios.hal.arm4: package/lib/lib/sysbios/debug/ti.sysbios.hal/package/package_ti.sysbios.hal.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/Cache.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/CacheNull.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/Core.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/CoreNull.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_stack.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/Hwi_startup.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/Power.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/PowerNull.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/Seconds.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsCallback.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/SecondsClock.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/Timer.orm4 package/lib/lib/sysbios/debug/ti.sysbios.hal/TimerNull.orm4 lib/sysbios/debug/ti.sysbios.hal.arm4.mak

clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.hal.arm4.mak
