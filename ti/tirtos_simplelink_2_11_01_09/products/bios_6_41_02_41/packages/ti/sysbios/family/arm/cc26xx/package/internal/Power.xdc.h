/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A65
 */

#ifndef ti_sysbios_family_arm_cc26xx_Power__INTERNAL__
#define ti_sysbios_family_arm_cc26xx_Power__INTERNAL__

#ifndef ti_sysbios_family_arm_cc26xx_Power__internalaccess
#define ti_sysbios_family_arm_cc26xx_Power__internalaccess
#endif

#include <ti/sysbios/family/arm/cc26xx/Power.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* standbyPolicy */
#undef ti_sysbios_family_arm_cc26xx_Power_standbyPolicy
#define ti_sysbios_family_arm_cc26xx_Power_standbyPolicy ti_sysbios_family_arm_cc26xx_Power_standbyPolicy__E

/* defaultClockFunc */
#undef ti_sysbios_family_arm_cc26xx_Power_defaultClockFunc
#define ti_sysbios_family_arm_cc26xx_Power_defaultClockFunc ti_sysbios_family_arm_cc26xx_Power_defaultClockFunc__E

/* defaultNotifyTrapFunc */
#undef ti_sysbios_family_arm_cc26xx_Power_defaultNotifyTrapFunc
#define ti_sysbios_family_arm_cc26xx_Power_defaultNotifyTrapFunc ti_sysbios_family_arm_cc26xx_Power_defaultNotifyTrapFunc__E

/* LF_clockFunc */
#undef ti_sysbios_family_arm_cc26xx_Power_LF_clockFunc
#define ti_sysbios_family_arm_cc26xx_Power_LF_clockFunc ti_sysbios_family_arm_cc26xx_Power_LF_clockFunc__E

/* XOSC_HF_clockFunc */
#undef ti_sysbios_family_arm_cc26xx_Power_XOSC_HF_clockFunc
#define ti_sysbios_family_arm_cc26xx_Power_XOSC_HF_clockFunc ti_sysbios_family_arm_cc26xx_Power_XOSC_HF_clockFunc__E

/* initiateCalibration */
#undef ti_sysbios_family_arm_cc26xx_Power_initiateCalibration
#define ti_sysbios_family_arm_cc26xx_Power_initiateCalibration ti_sysbios_family_arm_cc26xx_Power_initiateCalibration__E

/* startFirstMeasurement */
#undef ti_sysbios_family_arm_cc26xx_Power_startFirstMeasurement
#define ti_sysbios_family_arm_cc26xx_Power_startFirstMeasurement ti_sysbios_family_arm_cc26xx_Power_startFirstMeasurement__E

/* auxISR */
#undef ti_sysbios_family_arm_cc26xx_Power_auxISR
#define ti_sysbios_family_arm_cc26xx_Power_auxISR ti_sysbios_family_arm_cc26xx_Power_auxISR__E

/* getClockHandle */
#undef ti_sysbios_family_arm_cc26xx_Power_getClockHandle
#define ti_sysbios_family_arm_cc26xx_Power_getClockHandle ti_sysbios_family_arm_cc26xx_Power_getClockHandle__E

/* doWFI */
#undef ti_sysbios_family_arm_cc26xx_Power_doWFI
#define ti_sysbios_family_arm_cc26xx_Power_doWFI ti_sysbios_family_arm_cc26xx_Power_doWFI__E

/* getConstraintInfo */
#undef ti_sysbios_family_arm_cc26xx_Power_getConstraintInfo
#define ti_sysbios_family_arm_cc26xx_Power_getConstraintInfo ti_sysbios_family_arm_cc26xx_Power_getConstraintInfo__E

/* getDependencyCount */
#undef ti_sysbios_family_arm_cc26xx_Power_getDependencyCount
#define ti_sysbios_family_arm_cc26xx_Power_getDependencyCount ti_sysbios_family_arm_cc26xx_Power_getDependencyCount__E

/* getTransitionState */
#undef ti_sysbios_family_arm_cc26xx_Power_getTransitionState
#define ti_sysbios_family_arm_cc26xx_Power_getTransitionState ti_sysbios_family_arm_cc26xx_Power_getTransitionState__E

/* getTicksUntilWakeup */
#undef ti_sysbios_family_arm_cc26xx_Power_getTicksUntilWakeup
#define ti_sysbios_family_arm_cc26xx_Power_getTicksUntilWakeup ti_sysbios_family_arm_cc26xx_Power_getTicksUntilWakeup__E

/* getTransitionLatency */
#undef ti_sysbios_family_arm_cc26xx_Power_getTransitionLatency
#define ti_sysbios_family_arm_cc26xx_Power_getTransitionLatency ti_sysbios_family_arm_cc26xx_Power_getTransitionLatency__E

/* getXoscStartupTime */
#undef ti_sysbios_family_arm_cc26xx_Power_getXoscStartupTime
#define ti_sysbios_family_arm_cc26xx_Power_getXoscStartupTime ti_sysbios_family_arm_cc26xx_Power_getXoscStartupTime__E

/* isStableXOSC_HF */
#undef ti_sysbios_family_arm_cc26xx_Power_isStableXOSC_HF
#define ti_sysbios_family_arm_cc26xx_Power_isStableXOSC_HF ti_sysbios_family_arm_cc26xx_Power_isStableXOSC_HF__E

/* releaseConstraint */
#undef ti_sysbios_family_arm_cc26xx_Power_releaseConstraint
#define ti_sysbios_family_arm_cc26xx_Power_releaseConstraint ti_sysbios_family_arm_cc26xx_Power_releaseConstraint__E

/* releaseDependency */
#undef ti_sysbios_family_arm_cc26xx_Power_releaseDependency
#define ti_sysbios_family_arm_cc26xx_Power_releaseDependency ti_sysbios_family_arm_cc26xx_Power_releaseDependency__E

/* registerNotify */
#undef ti_sysbios_family_arm_cc26xx_Power_registerNotify
#define ti_sysbios_family_arm_cc26xx_Power_registerNotify ti_sysbios_family_arm_cc26xx_Power_registerNotify__E

/* setConstraint */
#undef ti_sysbios_family_arm_cc26xx_Power_setConstraint
#define ti_sysbios_family_arm_cc26xx_Power_setConstraint ti_sysbios_family_arm_cc26xx_Power_setConstraint__E

/* setDependency */
#undef ti_sysbios_family_arm_cc26xx_Power_setDependency
#define ti_sysbios_family_arm_cc26xx_Power_setDependency ti_sysbios_family_arm_cc26xx_Power_setDependency__E

/* shutdown */
#undef ti_sysbios_family_arm_cc26xx_Power_shutdown
#define ti_sysbios_family_arm_cc26xx_Power_shutdown ti_sysbios_family_arm_cc26xx_Power_shutdown__E

/* sleep */
#undef ti_sysbios_family_arm_cc26xx_Power_sleep
#define ti_sysbios_family_arm_cc26xx_Power_sleep ti_sysbios_family_arm_cc26xx_Power_sleep__E

/* switchXOSC_HF */
#undef ti_sysbios_family_arm_cc26xx_Power_switchXOSC_HF
#define ti_sysbios_family_arm_cc26xx_Power_switchXOSC_HF ti_sysbios_family_arm_cc26xx_Power_switchXOSC_HF__E

/* unregisterNotify */
#undef ti_sysbios_family_arm_cc26xx_Power_unregisterNotify
#define ti_sysbios_family_arm_cc26xx_Power_unregisterNotify ti_sysbios_family_arm_cc26xx_Power_unregisterNotify__E

/* idleCPU */
#undef ti_sysbios_family_arm_cc26xx_Power_idleCPU
#define ti_sysbios_family_arm_cc26xx_Power_idleCPU ti_sysbios_family_arm_cc26xx_Power_idleCPU__E

/* notify */
#define Power_notify ti_sysbios_family_arm_cc26xx_Power_notify__I

/* serviceNotifyQ */
#define Power_serviceNotifyQ ti_sysbios_family_arm_cc26xx_Power_serviceNotifyQ__I

/* Module_startup */
#undef ti_sysbios_family_arm_cc26xx_Power_Module_startup
#define ti_sysbios_family_arm_cc26xx_Power_Module_startup ti_sysbios_family_arm_cc26xx_Power_Module_startup__E

/* Instance_init */
#undef ti_sysbios_family_arm_cc26xx_Power_Instance_init
#define ti_sysbios_family_arm_cc26xx_Power_Instance_init ti_sysbios_family_arm_cc26xx_Power_Instance_init__E

/* Instance_finalize */
#undef ti_sysbios_family_arm_cc26xx_Power_Instance_finalize
#define ti_sysbios_family_arm_cc26xx_Power_Instance_finalize ti_sysbios_family_arm_cc26xx_Power_Instance_finalize__E

/* module */
#define Power_module ((ti_sysbios_family_arm_cc26xx_Power_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_arm_cc26xx_Power_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_sysbios_family_arm_cc26xx_Power__cplusplus)
#define module ((ti_sysbios_family_arm_cc26xx_Power_Module_State *)(xdc__MODOBJADDR__(ti_sysbios_family_arm_cc26xx_Power_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sysbios_family_arm_cc26xx_Power_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sysbios_family_arm_cc26xx_Power_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sysbios_family_arm_cc26xx_Power_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sysbios_family_arm_cc26xx_Power_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sysbios_family_arm_cc26xx_Power_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sysbios_family_arm_cc26xx_Power_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sysbios_family_arm_cc26xx_Power_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sysbios_family_arm_cc26xx_Power_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sysbios_family_arm_cc26xx_Power_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sysbios_family_arm_cc26xx_Power_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sysbios_family_arm_cc26xx_Power_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sysbios_family_arm_cc26xx_Power_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sysbios_family_arm_cc26xx_Power_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sysbios_family_arm_cc26xx_Power_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sysbios_family_arm_cc26xx_Power_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sysbios_family_arm_cc26xx_Power_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sysbios_family_arm_cc26xx_Power_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sysbios_family_arm_cc26xx_Power_Module_GateProxy_query


#endif /* ti_sysbios_family_arm_cc26xx_Power__INTERNAL____ */
