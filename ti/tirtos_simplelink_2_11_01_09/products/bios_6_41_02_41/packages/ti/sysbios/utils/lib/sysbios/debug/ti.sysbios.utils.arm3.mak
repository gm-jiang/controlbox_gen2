#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = iar.targets.arm.M3{1,0,7.20,1
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.orm3.dep
package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.orm3.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.orm3: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.orm3: package/package_ti.sysbios.utils.c lib/sysbios/debug/ti.sysbios.utils.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.srm3: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.srm3: package/package_ti.sysbios.utils.c lib/sysbios/debug/ti.sysbios.utils.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.orm3.dep
package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.orm3.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.orm3: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.orm3: Load.c lib/sysbios/debug/ti.sysbios.utils.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.srm3: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.srm3: Load.c lib/sysbios/debug/ti.sysbios.utils.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.orm3.dep
package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.orm3.dep: ;
endif

package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.orm3: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.orm3: Load_CPU.c lib/sysbios/debug/ti.sysbios.utils.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.srm3: | .interfaces
package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.srm3: Load_CPU.c lib/sysbios/debug/ti.sysbios.utils.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_7_20_1 --debug --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_BIOS_smpEnabled__D=FALSE  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

clean,rm3 ::
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.orm3
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.orm3
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.orm3
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.srm3
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.srm3
	-$(RM) package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.srm3

lib/sysbios/debug/ti.sysbios.utils.arm3: package/lib/lib/sysbios/debug/ti.sysbios.utils/package/package_ti.sysbios.utils.orm3 package/lib/lib/sysbios/debug/ti.sysbios.utils/Load.orm3 package/lib/lib/sysbios/debug/ti.sysbios.utils/Load_CPU.orm3 lib/sysbios/debug/ti.sysbios.utils.arm3.mak

clean::
	-$(RM) lib/sysbios/debug/ti.sysbios.utils.arm3.mak
