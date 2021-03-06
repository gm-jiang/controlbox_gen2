#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = iar.targets.arm.M3{1,0,7.20,1
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.orm3.dep
package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.orm3.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.orm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.orm3: package/package_ti.sysbios.fatfs.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.srm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.srm3: package/package_ti.sysbios.fatfs.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/ff.orm3.dep
package/lib/lib/release/ti.sysbios.fatfs/ff.orm3.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/ff.orm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/ff.orm3: ff.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.sysbios.fatfs/ff.srm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/ff.srm3: ff.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/diskio.orm3.dep
package/lib/lib/release/ti.sysbios.fatfs/diskio.orm3.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/diskio.orm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/diskio.orm3: diskio.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.sysbios.fatfs/diskio.srm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/diskio.srm3: diskio.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/ramdisk.orm3.dep
package/lib/lib/release/ti.sysbios.fatfs/ramdisk.orm3.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/ramdisk.orm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/ramdisk.orm3: ramdisk.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.sysbios.fatfs/ramdisk.srm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/ramdisk.srm3: ramdisk.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.orm3.dep
package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.orm3.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.orm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.orm3: syncsysbios.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.srm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.srm3: syncsysbios.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.sysbios.fatfs/memsysbios.orm3.dep
package/lib/lib/release/ti.sysbios.fatfs/memsysbios.orm3.dep: ;
endif

package/lib/lib/release/ti.sysbios.fatfs/memsysbios.orm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/memsysbios.orm3: memsysbios.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.sysbios.fatfs/memsysbios.srm3: | .interfaces
package/lib/lib/release/ti.sysbios.fatfs/memsysbios.srm3: memsysbios.c lib/release/ti.sysbios.fatfs.arm3.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm3 $< ...
	LC_ALL=C $(iar.targets.arm.M3.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M3 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dxdc_target_name__=M3 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M3.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

clean,rm3 ::
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.orm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/ff.orm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/diskio.orm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/ramdisk.orm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.orm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/memsysbios.orm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.srm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/ff.srm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/diskio.srm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/ramdisk.srm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.srm3
	-$(RM) package/lib/lib/release/ti.sysbios.fatfs/memsysbios.srm3

lib/release/ti.sysbios.fatfs.arm3: package/lib/lib/release/ti.sysbios.fatfs/package/package_ti.sysbios.fatfs.orm3 package/lib/lib/release/ti.sysbios.fatfs/ff.orm3 package/lib/lib/release/ti.sysbios.fatfs/diskio.orm3 package/lib/lib/release/ti.sysbios.fatfs/ramdisk.orm3 package/lib/lib/release/ti.sysbios.fatfs/syncsysbios.orm3 package/lib/lib/release/ti.sysbios.fatfs/memsysbios.orm3 lib/release/ti.sysbios.fatfs.arm3.mak

clean::
	-$(RM) lib/release/ti.sysbios.fatfs.arm3.mak
