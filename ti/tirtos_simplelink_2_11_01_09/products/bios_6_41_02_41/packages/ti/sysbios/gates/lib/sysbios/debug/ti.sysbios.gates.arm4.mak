#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = iar.targets.arm.M4{1,0,7.20,1
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.orm4: package/package_ti.sysbios.gates.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.srm4: package/package_ti.sysbios.gates.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.orm4: GateHwi.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.srm4: GateHwi.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.orm4: GateAll.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.srm4: GateAll.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.orm4: GateSwi.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.srm4: GateSwi.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.orm4: GateTask.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.srm4: GateTask.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.orm4: GateTest.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.srm4: GateTest.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.orm4: GateMutex.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.srm4: GateMutex.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.orm4: GateMutexPri.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.srm4: GateMutexPri.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.orm4.dep
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.orm4.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.orm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.orm4: GateSpinlock.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.srm4: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.srm4: GateSpinlock.c lib/sysbios/debug/ti.sysbios.gates.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

clean,rm4 ::
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.orm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.srm4
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.srm4

lib/sysbios/debug/ti.sysbios.gates.arm4: package/lib/lib/sysbios/debug/ti.sysbios.gates/package/package_ti.sysbios.gates.orm4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateHwi.orm4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateAll.orm4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSwi.orm4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTask.orm4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateTest.orm4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutex.orm4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateMutexPri.orm4 package/lib/lib/sysbios/debug/ti.sysbios.gates/GateSpinlock.orm4 lib/sysbios/debug/ti.sysbios.gates.arm4.mak

clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.gates.arm4.mak
