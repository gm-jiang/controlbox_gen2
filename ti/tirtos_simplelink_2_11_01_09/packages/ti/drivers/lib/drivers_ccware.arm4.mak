#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = iar.targets.arm.M4{1,0,7.20,1
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/package/package_ti.drivers.orm4.dep
package/lib/lib/drivers_ccware/package/package_ti.drivers.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/package/package_ti.drivers.orm4: | .interfaces
package/lib/lib/drivers_ccware/package/package_ti.drivers.orm4: package/package_ti.drivers.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/package/package_ti.drivers.srm4: | .interfaces
package/lib/lib/drivers_ccware/package/package_ti.drivers.srm4: package/package_ti.drivers.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.orm4.dep
package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.orm4: | .interfaces
package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.orm4: ./gpio/GPIOCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.srm4: | .interfaces
package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.srm4: ./gpio/GPIOCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/I2C.orm4.dep
package/lib/lib/drivers_ccware/I2C.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/I2C.orm4: | .interfaces
package/lib/lib/drivers_ccware/I2C.orm4: I2C.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/I2C.srm4: | .interfaces
package/lib/lib/drivers_ccware/I2C.srm4: I2C.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/./i2c/I2CCC3200.orm4.dep
package/lib/lib/drivers_ccware/./i2c/I2CCC3200.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/./i2c/I2CCC3200.orm4: | .interfaces
package/lib/lib/drivers_ccware/./i2c/I2CCC3200.orm4: ./i2c/I2CCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/./i2c/I2CCC3200.srm4: | .interfaces
package/lib/lib/drivers_ccware/./i2c/I2CCC3200.srm4: ./i2c/I2CCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/PWM.orm4.dep
package/lib/lib/drivers_ccware/PWM.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/PWM.orm4: | .interfaces
package/lib/lib/drivers_ccware/PWM.orm4: PWM.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/PWM.srm4: | .interfaces
package/lib/lib/drivers_ccware/PWM.srm4: PWM.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.orm4.dep
package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.orm4: | .interfaces
package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.orm4: ./pwm/PWMTimerCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.srm4: | .interfaces
package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.srm4: ./pwm/PWMTimerCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/SDSPI.orm4.dep
package/lib/lib/drivers_ccware/SDSPI.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/SDSPI.orm4: | .interfaces
package/lib/lib/drivers_ccware/SDSPI.orm4: SDSPI.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/SDSPI.srm4: | .interfaces
package/lib/lib/drivers_ccware/SDSPI.srm4: SDSPI.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.orm4.dep
package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.orm4: | .interfaces
package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.orm4: ./sdspi/SDSPICC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.srm4: | .interfaces
package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.srm4: ./sdspi/SDSPICC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/SPI.orm4.dep
package/lib/lib/drivers_ccware/SPI.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/SPI.orm4: | .interfaces
package/lib/lib/drivers_ccware/SPI.orm4: SPI.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/SPI.srm4: | .interfaces
package/lib/lib/drivers_ccware/SPI.srm4: SPI.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.orm4.dep
package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.orm4: | .interfaces
package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.orm4: ./spi/SPICC3200DMA.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.srm4: | .interfaces
package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.srm4: ./spi/SPICC3200DMA.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/UART.orm4.dep
package/lib/lib/drivers_ccware/UART.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/UART.orm4: | .interfaces
package/lib/lib/drivers_ccware/UART.orm4: UART.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/UART.srm4: | .interfaces
package/lib/lib/drivers_ccware/UART.srm4: UART.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/./uart/UARTCC3200.orm4.dep
package/lib/lib/drivers_ccware/./uart/UARTCC3200.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/./uart/UARTCC3200.orm4: | .interfaces
package/lib/lib/drivers_ccware/./uart/UARTCC3200.orm4: ./uart/UARTCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/./uart/UARTCC3200.srm4: | .interfaces
package/lib/lib/drivers_ccware/./uart/UARTCC3200.srm4: ./uart/UARTCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.orm4.dep
package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.orm4: | .interfaces
package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.orm4: ./uart/UARTCC3200DMA.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.srm4: | .interfaces
package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.srm4: ./uart/UARTCC3200DMA.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/Watchdog.orm4.dep
package/lib/lib/drivers_ccware/Watchdog.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/Watchdog.orm4: | .interfaces
package/lib/lib/drivers_ccware/Watchdog.orm4: Watchdog.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/Watchdog.srm4: | .interfaces
package/lib/lib/drivers_ccware/Watchdog.srm4: Watchdog.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.orm4.dep
package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.orm4.dep: ;
endif

package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.orm4: | .interfaces
package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.orm4: ./watchdog/WatchdogCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.srm4: | .interfaces
package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.srm4: ./watchdog/WatchdogCC3200.c lib/drivers_ccware.arm4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clrm4 $< ...
	LC_ALL=C $(iar.targets.arm.M4.rootDir)/bin/iccarm  --silent --aeabi --cpu=Cortex-M4 --diag_suppress=Pa050,Go005 --endian=little -e --thumb  -Dewarm -DIAR  -Dxdc_target_name__=M4 -Dxdc_target_types__=iar/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_7_20_1 -Ohs --dlib_config $(iar.targets.arm.M4.rootDir)/inc/c/DLib_Config_Normal.h  -I/home/xlibrary/trees/zumaprod/zumaprod-e09/tirtos_simplelink_2_11_01_09/products/CC3200_driverlib_1.0.2 -DCCWARE  -Dxdc_runtime_Assert_DISABLE_CONDITIONAL_ASSERT -Dxdc_runtime_Log_DISABLE_ALL -Dxdc_runtime_Assert_DISABLE_ALL  $(XDCINCS)  -o $@  $<
	
	-@$(FIXDEP) $@.dep $@.dep
	

clean,rm4 ::
	-$(RM) package/lib/lib/drivers_ccware/package/package_ti.drivers.orm4
	-$(RM) package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.orm4
	-$(RM) package/lib/lib/drivers_ccware/I2C.orm4
	-$(RM) package/lib/lib/drivers_ccware/./i2c/I2CCC3200.orm4
	-$(RM) package/lib/lib/drivers_ccware/PWM.orm4
	-$(RM) package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.orm4
	-$(RM) package/lib/lib/drivers_ccware/SDSPI.orm4
	-$(RM) package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.orm4
	-$(RM) package/lib/lib/drivers_ccware/SPI.orm4
	-$(RM) package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.orm4
	-$(RM) package/lib/lib/drivers_ccware/UART.orm4
	-$(RM) package/lib/lib/drivers_ccware/./uart/UARTCC3200.orm4
	-$(RM) package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.orm4
	-$(RM) package/lib/lib/drivers_ccware/Watchdog.orm4
	-$(RM) package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.orm4
	-$(RM) package/lib/lib/drivers_ccware/package/package_ti.drivers.srm4
	-$(RM) package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.srm4
	-$(RM) package/lib/lib/drivers_ccware/I2C.srm4
	-$(RM) package/lib/lib/drivers_ccware/./i2c/I2CCC3200.srm4
	-$(RM) package/lib/lib/drivers_ccware/PWM.srm4
	-$(RM) package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.srm4
	-$(RM) package/lib/lib/drivers_ccware/SDSPI.srm4
	-$(RM) package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.srm4
	-$(RM) package/lib/lib/drivers_ccware/SPI.srm4
	-$(RM) package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.srm4
	-$(RM) package/lib/lib/drivers_ccware/UART.srm4
	-$(RM) package/lib/lib/drivers_ccware/./uart/UARTCC3200.srm4
	-$(RM) package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.srm4
	-$(RM) package/lib/lib/drivers_ccware/Watchdog.srm4
	-$(RM) package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.srm4

lib/drivers_ccware.arm4: package/lib/lib/drivers_ccware/package/package_ti.drivers.orm4 package/lib/lib/drivers_ccware/./gpio/GPIOCC3200.orm4 package/lib/lib/drivers_ccware/I2C.orm4 package/lib/lib/drivers_ccware/./i2c/I2CCC3200.orm4 package/lib/lib/drivers_ccware/PWM.orm4 package/lib/lib/drivers_ccware/./pwm/PWMTimerCC3200.orm4 package/lib/lib/drivers_ccware/SDSPI.orm4 package/lib/lib/drivers_ccware/./sdspi/SDSPICC3200.orm4 package/lib/lib/drivers_ccware/SPI.orm4 package/lib/lib/drivers_ccware/./spi/SPICC3200DMA.orm4 package/lib/lib/drivers_ccware/UART.orm4 package/lib/lib/drivers_ccware/./uart/UARTCC3200.orm4 package/lib/lib/drivers_ccware/./uart/UARTCC3200DMA.orm4 package/lib/lib/drivers_ccware/Watchdog.orm4 package/lib/lib/drivers_ccware/./watchdog/WatchdogCC3200.orm4 lib/drivers_ccware.arm4.mak

clean::
	-$(RM) lib/drivers_ccware.arm4.mak