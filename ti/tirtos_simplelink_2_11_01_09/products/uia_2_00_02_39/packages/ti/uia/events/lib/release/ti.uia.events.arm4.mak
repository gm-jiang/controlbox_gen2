#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = iar.targets.arm.M4{1,0,7.20,1
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.orm4.dep
package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.orm4.dep: ;
endif

package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.orm4: | .interfaces
package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.orm4: package/package_ti.uia.events.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.srm4: | .interfaces
package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.srm4: package/package_ti.uia.events.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.events/UIAAppCtx.orm4.dep
package/lib/lib/release/ti.uia.events/UIAAppCtx.orm4.dep: ;
endif

package/lib/lib/release/ti.uia.events/UIAAppCtx.orm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAAppCtx.orm4: UIAAppCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.uia.events/UIAAppCtx.srm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAAppCtx.srm4: UIAAppCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.events/UIAChanCtx.orm4.dep
package/lib/lib/release/ti.uia.events/UIAChanCtx.orm4.dep: ;
endif

package/lib/lib/release/ti.uia.events/UIAChanCtx.orm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAChanCtx.orm4: UIAChanCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.uia.events/UIAChanCtx.srm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAChanCtx.srm4: UIAChanCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.events/UIAFrameCtx.orm4.dep
package/lib/lib/release/ti.uia.events/UIAFrameCtx.orm4.dep: ;
endif

package/lib/lib/release/ti.uia.events/UIAFrameCtx.orm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAFrameCtx.orm4: UIAFrameCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.uia.events/UIAFrameCtx.srm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAFrameCtx.srm4: UIAFrameCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.events/UIAThreadCtx.orm4.dep
package/lib/lib/release/ti.uia.events/UIAThreadCtx.orm4.dep: ;
endif

package/lib/lib/release/ti.uia.events/UIAThreadCtx.orm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAThreadCtx.orm4: UIAThreadCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.uia.events/UIAThreadCtx.srm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAThreadCtx.srm4: UIAThreadCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/release/ti.uia.events/UIAUserCtx.orm4.dep
package/lib/lib/release/ti.uia.events/UIAUserCtx.orm4.dep: ;
endif

package/lib/lib/release/ti.uia.events/UIAUserCtx.orm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAUserCtx.orm4: UIAUserCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/release/ti.uia.events/UIAUserCtx.srm4: | .interfaces
package/lib/lib/release/ti.uia.events/UIAUserCtx.srm4: UIAUserCtx.c lib/release/ti.uia.events.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -D_DLIB_FILE_DESCRIPTOR -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

clean,rm4 ::
	-$(RM) package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.orm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAAppCtx.orm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAChanCtx.orm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAFrameCtx.orm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAThreadCtx.orm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAUserCtx.orm4
	-$(RM) package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.srm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAAppCtx.srm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAChanCtx.srm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAFrameCtx.srm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAThreadCtx.srm4
	-$(RM) package/lib/lib/release/ti.uia.events/UIAUserCtx.srm4

lib/release/ti.uia.events.arm4: package/lib/lib/release/ti.uia.events/package/package_ti.uia.events.orm4 package/lib/lib/release/ti.uia.events/UIAAppCtx.orm4 package/lib/lib/release/ti.uia.events/UIAChanCtx.orm4 package/lib/lib/release/ti.uia.events/UIAFrameCtx.orm4 package/lib/lib/release/ti.uia.events/UIAThreadCtx.orm4 package/lib/lib/release/ti.uia.events/UIAUserCtx.orm4 lib/release/ti.uia.events.arm4.mak

clean::
	-$(RM) lib/release/ti.uia.events.arm4.mak
