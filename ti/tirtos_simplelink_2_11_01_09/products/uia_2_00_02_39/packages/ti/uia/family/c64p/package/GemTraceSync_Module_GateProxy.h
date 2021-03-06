/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A65
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_uia_family_c64p_GemTraceSync_Module_GateProxy__include
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy__include

#ifndef __nested__
#define __nested__
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/uia/family/c64p/package/package.defs.h>

#include <xdc/runtime/IGateProvider.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* Q_BLOCKING */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Q_BLOCKING (1)

/* Q_PREEMPTING */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Q_PREEMPTING (2)


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsEnabled;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsEnabled ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsIncluded;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsIncluded ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsMask;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsMask ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__gateObj;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__gateObj ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__gatePrms;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__gatePrms ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__id;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__id ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerDefined;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerDefined ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerObj;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerObj ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn0;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn0 ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn1;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn1 ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn2;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn2 ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn4;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn4 ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn8;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn8 ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__startupDoneFxn ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__count;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__count ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__heap;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__heap ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__sizeof;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__sizeof ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__table;
__extern __FAR__ const CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__table ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__table__C;


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Struct {
    const ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Fxns__ *__fxns;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2 *__sysp;
    xdc_Bool (*query)(xdc_Int);
    xdc_IArg (*enter)(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle);
    xdc_Void (*leave)(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle, xdc_IArg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Fxns__ ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_startup( state ) (-1)

/* Handle__label__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle__label__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__startupDone__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__startupDone__S")
__extern xdc_Bool ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__create__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__create__S")
__extern xdc_Ptr ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar *__pa, xdc_SizeT __psz, xdc_runtime_Error_Block *__eb );

/* create */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_create, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_create")
__extern ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle ti_uia_family_c64p_GemTraceSync_Module_GateProxy_create( const ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params *__prms, xdc_runtime_Error_Block *__eb );

/* Object__delete__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__delete__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__delete__S")
__extern xdc_Void ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__delete__S( xdc_Ptr instp );

/* delete */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_delete, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_delete")
__extern Void ti_uia_family_c64p_GemTraceSync_Module_GateProxy_delete(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle *instp);

/* Object__destruct__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__destruct__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__destruct__S")
__extern xdc_Void ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__get__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__get__S")
__extern xdc_Ptr ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__first__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__first__S")
__extern xdc_Ptr ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__next__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__next__S")
__extern xdc_Ptr ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params__init__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params__init__S")
__extern xdc_Void ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__abstract__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__abstract__S")
__extern xdc_Bool ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__delegate__S, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__delegate__S")
__extern xdc_Ptr ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__delegate__S( void );

/* query__E */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_query ti_uia_family_c64p_GemTraceSync_Module_GateProxy_query__E
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_query__E, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_query")
__extern xdc_Bool ti_uia_family_c64p_GemTraceSync_Module_GateProxy_query__E( xdc_Int qual );

/* enter__E */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_enter ti_uia_family_c64p_GemTraceSync_Module_GateProxy_enter__E
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_enter__E, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_enter")
__extern xdc_IArg ti_uia_family_c64p_GemTraceSync_Module_GateProxy_enter__E( ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle __inst );

/* leave__E */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_leave ti_uia_family_c64p_GemTraceSync_Module_GateProxy_leave__E
xdc__CODESECT(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_leave__E, "ti_uia_family_c64p_GemTraceSync_Module_GateProxy_leave")
__extern xdc_Void ti_uia_family_c64p_GemTraceSync_Module_GateProxy_leave__E( ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle __inst, xdc_IArg key );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline xdc_runtime_IGateProvider_Module ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_upCast( void )
{
    return (xdc_runtime_IGateProvider_Module)ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__delegate__S();
}

/* Module_to_xdc_runtime_IGateProvider */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_to_xdc_runtime_IGateProvider ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_upCast

/* Handle_upCast */
static inline xdc_runtime_IGateProvider_Handle ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_upCast( ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle i )
{
    return (xdc_runtime_IGateProvider_Handle)i;
}

/* Handle_to_xdc_runtime_IGateProvider */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_to_xdc_runtime_IGateProvider ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_upCast

/* Handle_downCast */
static inline ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_downCast( xdc_runtime_IGateProvider_Handle i )
{
    xdc_runtime_IGateProvider_Handle i2 = (xdc_runtime_IGateProvider_Handle)i;
if (ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__abstract__S()) return (ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle)i;
    return (void*)i2->__fxns == (void*)ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__delegate__S() ? (ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle)i : 0;
}

/* Handle_from_xdc_runtime_IGateProvider */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_from_xdc_runtime_IGateProvider ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_downCast


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_startupDone() ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__startupDone__S()

/* Object_heap */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object_heap() ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__heap__C

/* Module_heap */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_heap() ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object__heap__C

/* Module_id */
static inline CT__ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__id ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_id( void ) 
{
    return ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module__id__C;
}

/* Proxy_abstract */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy_abstract() ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__abstract__S()

/* Proxy_delegate */
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy_delegate() ((xdc_runtime_IGateProvider_Module)ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy__delegate__S())

/* Params_init */
static inline void ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params_init( ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params *prms ) 
{
    if (prms) {
        ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params__init__S(prms, 0, sizeof(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params_copy(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params *dst, const ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params *src) 
{
    if (dst) {
        ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params__init__S(dst, (const void *)src, sizeof(ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_uia_family_c64p_GemTraceSync_Module_GateProxy__top__
#undef __nested__
#endif

#endif /* ti_uia_family_c64p_GemTraceSync_Module_GateProxy__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_uia_family_c64p_GemTraceSync_Module_GateProxy__nolocalnames)

#ifndef ti_uia_family_c64p_GemTraceSync_Module_GateProxy__localnames__done
#define ti_uia_family_c64p_GemTraceSync_Module_GateProxy__localnames__done

/* module prefix */
#define GemTraceSync_Module_GateProxy_Instance ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Instance
#define GemTraceSync_Module_GateProxy_Handle ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle
#define GemTraceSync_Module_GateProxy_Module ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module
#define GemTraceSync_Module_GateProxy_Object ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object
#define GemTraceSync_Module_GateProxy_Struct ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Struct
#define GemTraceSync_Module_GateProxy_Q_BLOCKING ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Q_BLOCKING
#define GemTraceSync_Module_GateProxy_Q_PREEMPTING ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Q_PREEMPTING
#define GemTraceSync_Module_GateProxy_Params ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params
#define GemTraceSync_Module_GateProxy_query ti_uia_family_c64p_GemTraceSync_Module_GateProxy_query
#define GemTraceSync_Module_GateProxy_enter ti_uia_family_c64p_GemTraceSync_Module_GateProxy_enter
#define GemTraceSync_Module_GateProxy_leave ti_uia_family_c64p_GemTraceSync_Module_GateProxy_leave
#define GemTraceSync_Module_GateProxy_Module_name ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_name
#define GemTraceSync_Module_GateProxy_Module_id ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_id
#define GemTraceSync_Module_GateProxy_Module_startup ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_startup
#define GemTraceSync_Module_GateProxy_Module_startupDone ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_startupDone
#define GemTraceSync_Module_GateProxy_Module_hasMask ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_hasMask
#define GemTraceSync_Module_GateProxy_Module_getMask ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_getMask
#define GemTraceSync_Module_GateProxy_Module_setMask ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_setMask
#define GemTraceSync_Module_GateProxy_Object_heap ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object_heap
#define GemTraceSync_Module_GateProxy_Module_heap ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_heap
#define GemTraceSync_Module_GateProxy_construct ti_uia_family_c64p_GemTraceSync_Module_GateProxy_construct
#define GemTraceSync_Module_GateProxy_create ti_uia_family_c64p_GemTraceSync_Module_GateProxy_create
#define GemTraceSync_Module_GateProxy_handle ti_uia_family_c64p_GemTraceSync_Module_GateProxy_handle
#define GemTraceSync_Module_GateProxy_struct ti_uia_family_c64p_GemTraceSync_Module_GateProxy_struct
#define GemTraceSync_Module_GateProxy_Handle_label ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_label
#define GemTraceSync_Module_GateProxy_Handle_name ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_name
#define GemTraceSync_Module_GateProxy_Instance_init ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Instance_init
#define GemTraceSync_Module_GateProxy_Object_count ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object_count
#define GemTraceSync_Module_GateProxy_Object_get ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object_get
#define GemTraceSync_Module_GateProxy_Object_first ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object_first
#define GemTraceSync_Module_GateProxy_Object_next ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object_next
#define GemTraceSync_Module_GateProxy_Object_sizeof ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Object_sizeof
#define GemTraceSync_Module_GateProxy_Params_copy ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params_copy
#define GemTraceSync_Module_GateProxy_Params_init ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Params_init
#define GemTraceSync_Module_GateProxy_Instance_State ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Instance_State
#define GemTraceSync_Module_GateProxy_Proxy_abstract ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy_abstract
#define GemTraceSync_Module_GateProxy_Proxy_delegate ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Proxy_delegate
#define GemTraceSync_Module_GateProxy_delete ti_uia_family_c64p_GemTraceSync_Module_GateProxy_delete
#define GemTraceSync_Module_GateProxy_destruct ti_uia_family_c64p_GemTraceSync_Module_GateProxy_destruct
#define GemTraceSync_Module_GateProxy_Module_upCast ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_upCast
#define GemTraceSync_Module_GateProxy_Module_to_xdc_runtime_IGateProvider ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Module_to_xdc_runtime_IGateProvider
#define GemTraceSync_Module_GateProxy_Handle_upCast ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_upCast
#define GemTraceSync_Module_GateProxy_Handle_to_xdc_runtime_IGateProvider ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_to_xdc_runtime_IGateProvider
#define GemTraceSync_Module_GateProxy_Handle_downCast ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_downCast
#define GemTraceSync_Module_GateProxy_Handle_from_xdc_runtime_IGateProvider ti_uia_family_c64p_GemTraceSync_Module_GateProxy_Handle_from_xdc_runtime_IGateProvider

#endif /* ti_uia_family_c64p_GemTraceSync_Module_GateProxy__localnames__done */
#endif
