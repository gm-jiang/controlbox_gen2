/*
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== Build.xs ========
 */

var BIOS = null;
var Build = null;

var custom28xOpts = " -q -mo ";
var custom430xOpts = " -q --advice:power=1 ";
var customIar430xOpts = " --silent --diag_suppress=Pa050,Go005,Pe1053 -D_DLIB_FILE_DESCRIPTOR=1";
var custom6xOpts = " -q -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 ";
var customARP32xOpts = " -q --gen_func_subsections ";
var customArmOpts = " -q -ms --opt_for_speed=2 ";
var customGnuArmM3Opts = " ";
var customGnuArmM4Opts = " ";
var customGnuArmM4FOpts = " ";
var customGnuArmA9Opts = " ";
var customGnuArmA8Opts = " ";
var customGnuArmA15Opts = " ";
var customIarArmOpts = " --silent ";

var ccOptsList = {
    "ti.targets.C28_large"                      : custom28xOpts,
    "ti.targets.C28_float"                      : custom28xOpts,
    "ti.targets.msp430.elf.MSP430"              : custom430xOpts,
    "ti.targets.msp430.elf.MSP430X"             : custom430xOpts,
    "ti.targets.msp430.elf.MSP430X_small"       : custom430xOpts,
    "iar.targets.msp430.MSP430"                 : customIar430xOpts,
    "iar.targets.msp430.MSP430X_small"          : customIar430xOpts,
    "iar.targets.msp430.MSP430X_large"          : customIar430xOpts,
    "ti.targets.C64P"                           : custom6xOpts,
    "ti.targets.elf.C64P"                       : custom6xOpts,
    "ti.targets.C64P_big_endian"                : custom6xOpts,
    "ti.targets.elf.C64P_big_endian"            : custom6xOpts,
    "ti.targets.C674"                           : custom6xOpts,
    "ti.targets.elf.C674"                       : custom6xOpts,
    "ti.targets.elf.C67P"                       : custom6xOpts,
    "ti.targets.elf.C64T"                       : custom6xOpts,
    "ti.targets.elf.C66"                        : custom6xOpts,
    "ti.targets.elf.C66_big_endian"             : custom6xOpts,
    "ti.targets.arp32.elf.ARP32"                : customARP32xOpts,
    "ti.targets.arp32.elf.ARP32_far"            : customARP32xOpts,
    "ti.targets.arm.elf.Arm9"                   : customArmOpts,
    "ti.targets.arm.elf.A8F"                    : customArmOpts,
    "ti.targets.arm.elf.A8Fnv"                  : customArmOpts,
    "ti.targets.arm.elf.M0"                     : customArmOpts,
    "ti.targets.arm.elf.M3"                     : customArmOpts,
    "ti.targets.arm.elf.M4"                     : customArmOpts,
    "ti.targets.arm.elf.M4F"                    : customArmOpts,
    "gnu.targets.arm.M3"                        : customGnuArmM3Opts,
    "gnu.targets.arm.M4"                        : customGnuArmM4Opts,
    "gnu.targets.arm.M4F"                       : customGnuArmM4FOpts,
    "gnu.targets.arm.A8F"                       : customGnuArmA8Opts,
    "gnu.targets.arm.A9F"                       : customGnuArmA9Opts,
    "gnu.targets.arm.A15F"                      : customGnuArmA15Opts,
    "iar.targets.arm.M3"                        : customIarArmOpts,
    "iar.targets.arm.M4"                        : customIarArmOpts,
    "iar.targets.arm.M4F"                       : customIarArmOpts,
};

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    Build = this;

    /*
     * Set default verbose level for custom build flow
     * User can override this in their cfg file.
     */
    var SourceDir = xdc.module("xdc.cfg.SourceDir");
    SourceDir.verbose = 2;
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    BIOS = xdc.module("ti.sysbios.BIOS");

    var profile;

    /*
     * Get the profile associated with the ti.sysbios package.
     * The profile can be specified on a per package basis with a line like
     * this in your .cfg script:
     *
     * xdc.loadPackage('ti.sysbios').profile = "release";
     */
    if (this.$package.profile != undefined) {
        profile = this.$package.profile;
    }
    else {
        profile = Program.build.profile;
    }

    /*
     * Gracefully handle non-supported whole_program profiles
     */
    if (profile.match(/whole_program/)
        && (BIOS.libType != BIOS.LibType_Debug)) {
        /* allow build to proceed */
        BIOS.libType = BIOS.LibType_Debug;
        /* but warning the user */
        BIOS.$logWarning("The '" + profile +
            "' build profile will not be supported " +
            "in future releases of SYS/BIOS.  " +
            "Use 'release' or 'debug' profiles together with the " +
            "'BIOS.libType' configuration parameter to specify your " +
            "preferred library.  See the compatibility section of " +
            "your SYS/BIOS release notes for more information.",
            "Profile Deprecation Warning", BIOS);
    }

    /* 
     * Let the ROM's module$use() handle the BIOS.libType setting
     * if building a ROM application.
     */
    if (Build.buildROMApp == true) {
        return;
    }

    /* inform getLibs() about location of library */
    switch (BIOS.libType) {
        case BIOS.LibType_Instrumented:
	    if ((BIOS.$written("assertsEnabled") == true) &&
		(BIOS.assertsEnabled == false)) {
		BIOS.$logWarning(
		    "Asserts are enabled when BIOS.libType " +
		    "is set to BIOS.LibType_Instrumented",
                    BIOS, "assertsEnabled"
		);
	    }
	    BIOS.assertsEnabled = true;
	    
	    if ((BIOS.$written("logsEnabled") == true) &&
		(BIOS.logsEnabled == false)) {
		BIOS.$logWarning(
		    "Logs are enabled when BIOS.libType " +
		    "is set to BIOS.LibType_Instrumented",
                    BIOS, "logsEnabled"
		);
	    }
	    BIOS.logsEnabled = true;
            break;

        case BIOS.LibType_NonInstrumented:
	    if ((BIOS.$written("assertsEnabled") == true) &&
		(BIOS.assertsEnabled == true)) {
		BIOS.$logWarning(
		    "Asserts are disabled when BIOS.libType " +
		    "is set to BIOS.LibType_NonInstrumented",
                    BIOS, "assertsEnabled"
		);
	    }
	    BIOS.assertsEnabled = false;
	    if ((BIOS.$written("logsEnabled") == true) &&
		(BIOS.logsEnabled == true)) {
		BIOS.$logWarning(
		    "Logs are disabled when BIOS.libType " +
		    "is set to BIOS.LibType_NonInstrumented",
                    BIOS, "logsEnabled"
		);
	    }
	    BIOS.logsEnabled = false;
            break;

        case BIOS.LibType_Debug:
            xdc.useModule('ti.sysbios.knl.Clock'); /* Pull in Clock module so that hard references to Clock APIs are resolved */
            /* this fall through to the custom logic is on purpose */

        case BIOS.LibType_Custom:
            break;
    }

    this.$private.libraryName = "/sysbios.a" + Program.build.target.suffix;
    var SourceDir = xdc.useModule("xdc.cfg.SourceDir");

    /*
     * If BIOS.libDir has been explicitly specified by the user, use it.
     */
    if (BIOS.libDir !== null) {
        SourceDir.outputDir = BIOS.libDir;
    }
    else {
        var curPath = java.io.File(".").getCanonicalPath();
        /* If package.bld world AND building an application OR pre-built lib */
        if (java.io.File(curPath).getName() != "configPkg") {
            var appName = Program.name.substring(0, Program.name.lastIndexOf('.'));
            appName = appName + "_p" + Program.build.target.suffix + ".src";
            SourceDir.outputDir = "package/cfg/" + appName;
            SourceDir.toBuildDir = ".";
        }
        /* Here ONLY if building an application in CCS world */
        else {
            /* request output source directory for generated files */
            SourceDir.toBuildDir = "..";
        }
    }

    var src = SourceDir.create("sysbios");
    src.libraryName = "sysbios" + this.$private.libraryName;
    /*
     * save this directory in our private state (to be read during
     * generation, see Gen.xdt)
     */
    this.$private.outputDir = src.getGenSourceDir();
}

/*
 * Used for trimming the set of C files in the custom BIOS.lib
 * to the minimum required for the application.
 * Only odd case modules are in this list:
 * -More than just Mod.c files
 * -No Mod.c file
 */
var cFiles = {
    "ti.sysbios.utils.Load" :
        { cSources: ["Load.c", "Load_CPU.c"] },
    "ti.sysbios.hal.Hwi" :
        { cSources: ["Hwi.c", "Hwi_stack.c", "Hwi_startup.c"] },
    "ti.sysbios.io.GIO" :
        { cSources: ["GIO.c", "IOM_stub.c"] },
    "ti.sysbios.family.arm.m0.Clobber" :
        { cSources: [] },
    "ti.sysbios.family.arm.m3.Clobber" :
        { cSources: [] },
    "ti.sysbios.family.arm.m3.IntrinsicsSupport" :
        { cSources: [] },
    "ti.sysbios.family.arm.cc26xx.Power" :
        { cSources: ["Power.c", "Power_standbyPolicy.c", "Power_calibrateRCOSC.c", "pg2_leakage_workaround.c", "TimerGPT.c" ] },
    "ti.sysbios.family.arm.cc32xx.Power" :
        { cSources: ["Power.c", "Power_standbyPolicy.c"] },
    "ti.sysbios.family.arm.ducati.CTM" :
        { cSources: [] },
    "ti.sysbios.family.c28.Clobber" :
        { cSources: [] },
    "ti.sysbios.family.c28.IntrinsicsSupport" :
        { cSources: [] },
    "ti.sysbios.family.arp32.CTM" :
        { cSources: [] },
    "ti.sysbios.knl.Swi" :
        { cSources: ["Swi.c", "Swi_andn.c"] },
    "ti.sysbios.family.c64p.Hwi" :
        { cSources: ["Hwi.c", "Hwi_startup.c"] },
    "xdc.runtime.Defaults" :
        { cSources: [] },
    "xdc.runtime.Main" :
        { cSources: [] },
    "xdc.runtime.Types" :
        { cSources: [] },
    "xdc.runtime.Core" :
        { cSources: ["Core-mem.c", "Core-smem.c", "Core-label.c", "Core-params.c"] },
};

var biosPackages = [
    "ti.sysbios",
    "ti.sysbios.family.arm",
    "ti.sysbios.family.arm.a8",
    "ti.sysbios.family.arm.a8.intcps",
    "ti.sysbios.family.arm.a8.omap3430",
    "ti.sysbios.family.arm.a8.sim",
    "ti.sysbios.family.arm.a8.ti81xx",
    "ti.sysbios.family.arm.a9",
    "ti.sysbios.family.arm.a9.am437x",
    "ti.sysbios.family.arm.a15",
    "ti.sysbios.family.arm.a15.smp",
    "ti.sysbios.family.arm.a15.tci66xx",
    "ti.sysbios.family.arm.gic",
    "ti.sysbios.family.arm.systimer",
    "ti.sysbios.family.arm.arm9",
    "ti.sysbios.family.arm.cc26xx",
    "ti.sysbios.family.arm.cc32xx",
    "ti.sysbios.family.arm.da830",
    "ti.sysbios.family.arm.dm6446",
    "ti.sysbios.family.arm.ducati",
    "ti.sysbios.family.arm.ducati.dm8148",
    "ti.sysbios.family.arm.ducati.omap4430",
    "ti.sysbios.family.arm.ducati.smp",
    "ti.sysbios.family.arm.exc",
    "ti.sysbios.family.arm.f28m35x",
    "ti.sysbios.family.arm.lm4",
    "ti.sysbios.family.arm.lm4.rtc",
    "ti.sysbios.family.arm.lm3",
    "ti.sysbios.family.arm.m0",
    "ti.sysbios.family.arm.m3",
    "ti.sysbios.family.arm.msp432",
    "ti.sysbios.family.arm.msp432.init",
    "ti.sysbios.family.arm.omap1030",
    "ti.sysbios.family.arm.sim1030",
    "ti.sysbios.family.arm.tms570",
    "ti.sysbios.family.arm.v7a",
    "ti.sysbios.family.arm.v7a.smp",
    "ti.sysbios.family.c28",
    "ti.sysbios.family.c28.f28m35x",
    "ti.sysbios.family.c28.f2837x",
    "ti.sysbios.family.c62",
    "ti.sysbios.family.c64",
    "ti.sysbios.family.c64p",
    "ti.sysbios.family.c64p.dm6437",
    "ti.sysbios.family.c64p.dm6446",
    "ti.sysbios.family.c64p.omap3430",
    "ti.sysbios.family.c64p.primus",
    "ti.sysbios.family.c64p.tci6482",
    "ti.sysbios.family.c64p.tci6488",
    "ti.sysbios.family.c64p.tesla",
    "ti.sysbios.family.c64p.ti81xx",
    "ti.sysbios.family.c66",
    "ti.sysbios.family.c66.tci66xx",
    "ti.sysbios.family.c67p",
    "ti.sysbios.family.c674",
    "ti.sysbios.family.msp430",
    "ti.sysbios.family.arp32",
    "ti.sysbios.family.shared.vayu",
    "ti.sysbios.gates",
    "ti.sysbios.hal",
    "ti.sysbios.hal.ammu",
    "ti.sysbios.hal.unicache",
    "ti.sysbios.heaps",
    "ti.sysbios.io",
    "ti.sysbios.knl",
    "ti.sysbios.misc",
    "ti.sysbios.rta",
    "ti.sysbios.rts",
    "ti.sysbios.rts.gnu",
    "ti.sysbios.rts.iar",
    "ti.sysbios.rom.c28",
    "ti.sysbios.smp",
    "ti.sysbios.syncs",
    "ti.sysbios.timers.dmtimer",
    "ti.sysbios.timers.gptimer",
    "ti.sysbios.timers.timer64",
    "ti.sysbios.utils",
    "ti.sysbios.xdcruntime",
];

var xdcPackages = [
    "xdc.runtime",
    "xdc.runtime.knl",
];

function getDefaultCustomCCOpts()
{
    var BIOS = xdc.module('ti.sysbios.BIOS');
    var Build = xdc.module('ti.sysbios.Build');

    /* start with target.cc.opts */
    var customCCOpts = Program.build.target.cc.opts;

    /* add target unique custom ccOpts */
    if (!(ccOptsList[Program.build.target.$name] === undefined)) {
        customCCOpts += ccOptsList[Program.build.target.$name];
    }

    /* Gnu targets need to pick up ccOpts.prefix and suffix */
    if (Program.build.target.$name.match(/gnu/)) {
        customCCOpts += " -O3 -I" + Program.build.target.targetPkgPath +
            "/libs/install-native/$(GCCTARG)/include ";
        customCCOpts = Program.build.target.ccOpts.prefix + " " + customCCOpts;
        customCCOpts += Program.build.target.ccOpts.suffix + " ";

        /* Workaround for SDOCM00102122 */
        customCCOpts = customCCOpts.replace("-Wall","");
    }
    else if (Program.build.target.$name.match(/iar/)) {
        customCCOpts += " --mfc -Ohs ";
    }
    else {
        /* ti targets do program level compile */
        customCCOpts += " --program_level_compile -o3 -g --optimize_with_debug ";
    }

    /* undo optimizations if this is a Debug build */
    if (BIOS.libType == BIOS.LibType_Debug) {
        if (Program.build.target.$name.match(/gnu/)) {
            customCCOpts = customCCOpts.replace("-O3","");
            /* add in stack frames for stack back trace */
            customCCOpts += " -mapcs ";
        }
        else if (Program.build.target.$name.match(/iar/)) {
            customCCOpts = customCCOpts.replace("-Ohs","--debug");
        }
        else {
            customCCOpts = customCCOpts.replace(" -o3","");
            customCCOpts = customCCOpts.replace(" --optimize_with_debug","");
            if (Program.build.target.$name.match(/arm/)) {
                customCCOpts = customCCOpts.replace(" --opt_for_speed=2","");
            }
        }
    }

    return (customCCOpts);
}

/*
 *  ======== getDefs ========
 */
function getDefs()
{
    var BIOS = xdc.module("ti.sysbios.BIOS");
    var Hwi = xdc.module("ti.sysbios.hal.Hwi");
    var Settings = xdc.module("ti.sysbios.family.Settings");
    var HwiDelegate = Settings.getDefaultHwiDelegate();
    var HwiDelegateName = HwiDelegate.replace(/\./g, "_");

    var Swi = xdc.module("ti.sysbios.knl.Swi");
    var Task = xdc.module("ti.sysbios.knl.Task");
    var Clock = xdc.module("ti.sysbios.knl.Clock");
    var Semaphore = xdc.module("ti.sysbios.knl.Semaphore");
    var Load = xdc.module("ti.sysbios.utils.Load");
    var Defaults = xdc.module('xdc.runtime.Defaults');
    var Diags = xdc.module("xdc.runtime.Diags");

    var defs =   " -Dti_sysbios_BIOS_swiEnabled__D=" + (BIOS.swiEnabled ? "TRUE" : "FALSE")
               + " -Dti_sysbios_BIOS_taskEnabled__D=" + (BIOS.taskEnabled ? "TRUE" : "FALSE")
               + " -Dti_sysbios_BIOS_clockEnabled__D=" + (BIOS.clockEnabled ? "TRUE" : "FALSE")
               + " -Dti_sysbios_BIOS_runtimeCreatesEnabled__D=" + (BIOS.runtimeCreatesEnabled ? "TRUE" : "FALSE");

    if (xdc.module(HwiDelegate).hooks.length == 0) {
        defs += " -Dti_sysbios_hal_Hwi_DISABLE_ALL_HOOKS";
    }

    if (Swi.hooks.length == 0) {
        defs += " -Dti_sysbios_knl_Swi_DISABLE_ALL_HOOKS";
    }

    if (Task.hooks.length == 0) {
        defs += " -Dti_sysbios_knl_Task_DISABLE_ALL_HOOKS";
    }

    defs += " -Dti_sysbios_BIOS_smpEnabled__D="
            + (BIOS.smpEnabled ? "TRUE" : "FALSE");

    if (BIOS.smpEnabled == false) {
        defs += " -Dti_sysbios_Build_useHwiMacros";
    }

    if ((BIOS.buildingAppLib == true) && (Build.buildROM == false)) {
        defs += " -Dti_sysbios_knl_Swi_numPriorities__D=" + Swi.numPriorities;
        defs += " -Dti_sysbios_knl_Task_deleteTerminatedTasks__D=" + (Task.deleteTerminatedTasks ? "TRUE" : "FALSE");
        defs += " -Dti_sysbios_knl_Task_numPriorities__D=" + Task.numPriorities;
        defs += " -Dti_sysbios_knl_Task_checkStackFlag__D=" + (Task.checkStackFlag ? "TRUE" : "FALSE");

        if (BIOS.useSK) {
            defs += " -Dti_sysbios_BIOS_useSK__D=1";
        }

        /*
         * Add Clock module defs
         */
        switch (Clock.tickSource) {
            case Clock.TickSource_TIMER:
                defs += " -Dti_sysbios_knl_Clock_TICK_SOURCE=ti_sysbios_knl_Clock_TickSource_TIMER";
                break;
            case Clock.TickSource_USER:
                defs += " -Dti_sysbios_knl_Clock_TICK_SOURCE=ti_sysbios_knl_Clock_TickSource_USER";
                break;
            case Clock.TickSource_NULL:
                defs += " -Dti_sysbios_knl_Clock_TICK_SOURCE=ti_sysbios_knl_Clock_TickSource_NULL";
                break;
        }

        if (Clock.tickMode == Clock.TickMode_DYNAMIC) {
            defs += " -Dti_sysbios_knl_Clock_TICK_MODE=ti_sysbios_knl_Clock_TickMode_DYNAMIC";
        }
        else {
            defs += " -Dti_sysbios_knl_Clock_TICK_MODE=ti_sysbios_knl_Clock_TickMode_PERIODIC";
        }

        /*
         * map hal Core module APIs to their delegates
         */

        var coreDelegate;

        if (xdc.module('ti.sysbios.hal.Core').CoreProxy != null) {
            coreDelegate = xdc.module('ti.sysbios.hal.Core').CoreProxy.delegate$;
        }
        else {
            var coreDelegateString = Settings.getDefaultCoreDelegate();
            if (coreDelegateString == null) {
                coreDelegate = xdc.module('ti.sysbios.hal.CoreNull');
            }
            else {
                coreDelegate = xdc.module(coreDelegateString);
            }
        }

        var coreDelegateName = coreDelegate.$name;
        coreDelegateName = coreDelegateName.replace(/\./g, "_");

        defs += " -Dti_sysbios_hal_Core_delegate_getId="
                + coreDelegateName
                + "_getId__E";
        defs += " -Dti_sysbios_hal_Core_delegate_interruptCore="
                + coreDelegateName
                + "_interruptCore__E";
        defs += " -Dti_sysbios_hal_Core_delegate_lock="
                + coreDelegateName
             + "_lock__E";
        defs += " -Dti_sysbios_hal_Core_delegate_unlock="
                + coreDelegateName
             + "_unlock__E";

        defs += " -Dti_sysbios_hal_Core_numCores__D=" + coreDelegate.numCores;

        defs += " -D" + coreDelegateName + "_numCores__D=" + coreDelegate.numCores;

        /*
         * add Load module #defines
         */
        defs += " -Dti_sysbios_utils_Load_taskEnabled__D=" + (Load.taskEnabled ? "TRUE" : "FALSE");
        defs += " -Dti_sysbios_utils_Load_swiEnabled__D=" + (Load.swiEnabled ? "TRUE" : "FALSE");
    }

    if (Hwi.dispatcherSwiSupport) {
        defs += " -D"+HwiDelegateName+"_dispatcherSwiSupport__D=TRUE";
    }
    else {
        defs += " -D"+HwiDelegateName+"_dispatcherSwiSupport__D=FALSE";
    }

    if (Hwi.dispatcherTaskSupport) {
        defs += " -D"+HwiDelegateName+"_dispatcherTaskSupport__D=TRUE";
    }
    else {
        defs += " -D"+HwiDelegateName+"_dispatcherTaskSupport__D=FALSE";
    }

    if (Hwi.dispatcherAutoNestingSupport) {
        defs += " -D"+HwiDelegateName+"_dispatcherAutoNestingSupport__D=TRUE";
    }
    else {
        defs += " -D"+HwiDelegateName+"_dispatcherAutoNestingSupport__D=FALSE";
    }

    if (Hwi.dispatcherIrpTrackingSupport) {
        defs += " -D"+HwiDelegateName+"_dispatcherIrpTrackingSupport__D=TRUE";
    }
    else {
        defs += " -D"+HwiDelegateName+"_dispatcherIrpTrackingSupport__D=FALSE";
    }

    if (Semaphore.supportsEvents) {
        defs += " -Dti_sysbios_knl_Semaphore_supportsEvents__D=TRUE";
    }
    else {
        defs += " -Dti_sysbios_knl_Semaphore_supportsEvents__D=FALSE";
    }

    if (Semaphore.supportsPriority) {
        defs += " -Dti_sysbios_knl_Semaphore_supportsPriority__D=TRUE";
    }
    else {
        defs += " -Dti_sysbios_knl_Semaphore_supportsPriority__D=FALSE";
    }

    if ((BIOS.assertsEnabled == false) ||
        ((Defaults.common$.diags_ASSERT == Diags.ALWAYS_OFF)
            && (Defaults.common$.diags_INTERNAL == Diags.ALWAYS_OFF))) {
        defs += " -Dxdc_runtime_Assert_DISABLE_ALL";
    }

    if (BIOS.logsEnabled == false) {
        defs += " -Dxdc_runtime_Log_DISABLE_ALL";
    }

    return (defs);
}

/*
 *  ======== getCFiles ========
 */
function getCFiles(target)
{
    var biosSources ="";
    var xdcSources = "";
    var cfgBase = "";
    var File = xdc.module("xdc.services.io.File");
    
    cfgBase = String(java.io.File(Program.cfgBase + ".c").getCanonicalPath());
    cfgBase = File.getDOSPath(cfgBase);
    cfgBase = cfgBase.replace(/\\/g, "/");
    cfgBase = cfgBase.substring(0, cfgBase.lastIndexOf('/') + 1);
    var appName = Program.name.substring(0, Program.name.lastIndexOf('.'));
    appName = appName + "_p" + Program.build.target.suffix + "_config.c";

    /*
     * logic to trim the C files down to just what the application needs
     */
    biosSources += "BIOS.c ";
    for each (var mod in Program.targetModules()) {
        var mn = mod.$name;
        var pn = mn.substring(0, mn.lastIndexOf("."));
        var packageMatch = false;

        /* sanity check package path */
        for (var i = 0; i < biosPackages.length; i++) {
            if (pn == biosPackages[i]) {
                packageMatch = true;
                break;
            }
        }

        if (packageMatch && !mn.match(/Proxy/) && !mn.match(/BIOS/)) {
            if (cFiles[mn] === undefined) {
                var prefix = mn.substr(mn.indexOf("sysbios") + 8);
                var modstr = mn.substr(mn.lastIndexOf(".")+1);
                prefix = prefix.substring(0, prefix.lastIndexOf('.')+1);
                prefix = prefix.replace(/\./g, "/");
                biosSources += prefix + modstr + ".c ";
            }
            else {
                for (i in cFiles[mn].cSources) {
                    var prefix = mn.substr(mn.indexOf("sysbios") + 8);
                    prefix = prefix.substring(0, prefix.lastIndexOf('.')+1);
                    prefix = prefix.replace(/\./g, "/");
                    biosSources += prefix + cFiles[mn].cSources[i] + " ";
                }
            }
        }

        var Types = xdc.module('xdc.runtime.Types');
        if (packageMatch && mod.common$.outPolicy == Types.SEPARATE_FILE) {
            biosSources += cfgBase + mn + "_config.c ";
        }
    }
    
    if (Program.build.target.name.match(/430/)) {
        biosSources += "./HwiFuncs.c ";
    }

    if (BIOS.includeXdcRuntime == true) {
        biosSources += "xdc/runtime/xdc_noinit.c ";
        for each (var mod in Program.targetModules()) {
            var mn = mod.$name;
            var pn = mn.substring(0, mn.lastIndexOf("."));
            var packageMatch = false;

            /* sanity check package path */
            for (var i = 0; i < xdcPackages.length; i++) {
                if (pn == xdcPackages[i]) {
                    packageMatch = true;
                    break;
                }
            }

            if (packageMatch && !mn.match(/Proxy/)) {
                if (cFiles[mn] === undefined) {
                    var prefix = mn.substr(mn.indexOf("xdc"));
                    var modstr = mn.substr(mn.lastIndexOf(".")+1);
                    prefix = prefix.substring(0, prefix.lastIndexOf('.')+1);
                    prefix = prefix.replace(/\./g, "/");
                    biosSources += prefix + modstr + ".c ";
                }
                else {
                    for (i in cFiles[mn].cSources) {
                        var prefix = mn.substr(mn.indexOf("xdc"));
                        prefix = prefix.substring(0, prefix.lastIndexOf('.')+1);
                        prefix = prefix.replace(/\./g, "/");
                        biosSources += prefix + cFiles[mn].cSources[i] + " ";
                    }
                }
            }

            var Types = xdc.module('xdc.runtime.Types');
            if (packageMatch && mod.common$.outPolicy == Types.SEPARATE_FILE) {
                biosSources += cfgBase + mn + "_config.c ";
            }
        }
    }

    /* remove trailing " " */
    biosSources = biosSources.substring(0, biosSources.length-1);

    return (biosSources);
}

/*
 *  ======== getAsmFiles ========
 */
function getAsmFiles(target)
{
    var asmSources = "";
    
    /*
     * logic to trim the C files down to just what the application needs
     */
    for each (var mod in Program.targetModules()) {
        var mn = mod.$name;
        var pn = mn.substring(0, mn.lastIndexOf("."));
        var packageMatch = false;

        /* sanity check package path */
        for (var i = 0; i < biosPackages.length; i++) {
            if (pn == biosPackages[i]) {
                packageMatch = true;
                break;
            }
        }

        if (packageMatch && !mn.match(/Proxy/) && !mn.match(/BIOS/)) {
            if (mod.$private.getAsmFiles !== undefined) {
                var prefix = mn.substr(mn.indexOf("sysbios") + 8);
                var modstr = mn.substr(mn.lastIndexOf(".")+1);
                prefix = prefix.substring(0, prefix.lastIndexOf('.')+1);
                prefix = prefix.replace(/\./g, "/");
		var modAsmFiles = mod.$private.getAsmFiles(target);
		for (var j in modAsmFiles) {
		    asmSources += prefix + modAsmFiles[j] + " ";
		}
            }
	}
    }

    if (asmSources.length != 0) {
	/* remove trailing " " */
	asmSources = asmSources.substring(0, asmSources.length-1);
    }	

    return (asmSources.split(' '));
}

/*
 *  ======== getIncludePaths ========
 *  get the include path from the compiler command line
 */
function getIncludePaths()
{
    var incs = " ";
    var type = 0; /* 1: quotes */
    var prefix = Program.build.target.ccOpts.prefix;

    /*
     * First look for TI compiler's '--include_path=' option. This is
     * a contiguous string (no spaces) so it will be a single token.
     */
    var tokens = prefix.split(" ");
    for (i=0; i < tokens.length; i++) {
        if (tokens[i].match(/--include_path/)) {
	    incs += tokens[i] + " ";
        }
    }

    /*
     * Now look for TI, IAR and gcc's -I options.  There may be 0 or more
     * spaces after the -I.
     */
    for (var i = 0; i < prefix.length; i++) {
        /* Will process only the options */
        if (prefix[i] == '-') {
            i++;
            if (!(i < prefix.length)) {
                break;
            }

            /* Is it an include option? */
            if (prefix[i] == 'I') {
                var opt = prefix[i];

                do {
                   i++;
                   if (!(i < prefix.length)) {
                       /* break while */
                       break;
                   }
                    /* Skip whitespace */
                } while (prefix[i] == ' ');

                if (!(i < prefix.length)) {
                    break;
                }

                /* Quoted strings have to handled differently */
                if (prefix[i] == '"') {
                    type = 1;
                }

                /* Lets not forget the processed characters */
                incs += " -" + opt + prefix[i];
                i++;
                for (;i < prefix.length; i++) {
                     incs += prefix[i];
                     if (((type == 1) && (prefix[i] == '"')) ||
		             ((type == 0) && (prefix[i] == ' '))) {
                         type = 0;
                         incs += " ";
                         break;
                     }
                }
            }
        }
    }

    if (Build.buildROMApp == false) {
        return (incs);
    }

    /* add includes to non BIOS/XDC modules */
    for each (var mod in Program.targetModules()) {
        var mn = mod.$name;
        var pn = mn.substring(0, mn.lastIndexOf("."));
        var packageMatch = false;

        /* sanity check package path */
        for (var i = 0; i < biosPackages.length; i++) {
            if (pn == biosPackages[i]) {
                packageMatch = true;
                break;
            }
        }

        if (packageMatch == true) {
            continue;
        }

        /* sanity check package path */
        for (var i = 0; i < xdcPackages.length; i++) {
            if (pn == xdcPackages[i]) {
                packageMatch = true;
                break;
            }
        }

        var File = xdc.module("xdc.services.io.File");
        if (packageMatch == false) {
            incs += " -I" + File.getDOSPath(mod.$package.packageRepository) + " ";
        }
    }

    return (incs);
}

/*
 *  ======== getCcArgs ========
 *  called by BIOS.getCCOpts() to insert module-provided cc opts into
 *  custom library build compile line.
 */
function getCcArgs()
{
    var Build = xdc.module("ti.sysbios.Build");

    var ccArgs = "";

    for (var i = 0; i < Build.ccArgs.length; i++) {
        ccArgs += " " + Build.ccArgs[i];
    }

    return (ccArgs);
}

/*
 *  ======== getLibs ========
 */
function getLibs(pkg)
{
    var BIOS = xdc.module("ti.sysbios.BIOS");

    switch (BIOS.libType) {
        case BIOS.LibType_Custom:
        case BIOS.LibType_Instrumented:
        case BIOS.LibType_NonInstrumented:
        case BIOS.LibType_Debug:
            return null;
            break;
    }

    var lib = "";
    var name = pkg.$name + ".a" + prog.build.target.suffix;

    if (BIOS.smpEnabled == true) {
        lib = "lib/smpbios/debug/" + name;
    }
    else {
        lib = "lib/sysbios/debug/" + name;
    }

    if (java.io.File(pkg.packageBase + lib).exists()) {
        return lib;
    }

    /* could not find any library, throw exception */
    throw Error("Library not found: " + name);
}


/*
 *  ======== getProfiles ========
 *  Determines which profiles to build for.
 *
 *  Any argument in XDCARGS which does not contain platform= is treated
 *  as a profile. This way multiple build profiles can be specified by
 *  separating them with a space.
 */
function getProfiles(xdcArgs)
{
    /*
     * cmdlProf[1] gets matched to "whole_program,debug" if
     * ["abc", "profile=whole_program,debug"] is passed in as xdcArgs
     */
    var cmdlProf = (" " + xdcArgs.join(" ") + " ").match(/ profile=([^ ]+) /);

    if (cmdlProf == null) {
        /* No profile=XYZ found */
        return [];
    }

    /* Split "whole_program,debug" into ["whole_program", "debug"] */
    var profiles = cmdlProf[1].split(',');

    return profiles;
}

/*
 *  ======== buildLibs ========
 *  This function generates the makefile goals for the libraries
 *  produced by a ti.sysbios package.
 */
function buildLibs(objList, relList, filter, xdcArgs, incs)
{
    for (var i = 0; i < xdc.module('xdc.bld.BuildEnvironment').targets.length; i++) {
        var targ = xdc.module('xdc.bld.BuildEnvironment').targets[i];

        /* skip target if not supported */
        if (!supportsTarget(targ, filter)) {
            continue;
        }

        var profiles = getProfiles(xdcArgs);

        /* If no profiles were assigned, use only the default one. */
        if (profiles.length == 0) {
            profiles[0] = "debug";
        }

        for (var j = 0; j < profiles.length; j++) {
            var ccopts = "";
            var asmopts = "";

            if (profiles[j] == "smp") {
                var libPath = "lib/smpbios/debug/";
                ccopts += " -Dti_sysbios_BIOS_smpEnabled__D=TRUE";
                asmopts += " -Dti_sysbios_BIOS_smpEnabled__D=TRUE";
            }
            else {
                var libPath = "lib/sysbios/debug/";
                /* build all package libs using Hwi macros */
                ccopts += " -Dti_sysbios_Build_useHwiMacros";
                ccopts += " -Dti_sysbios_BIOS_smpEnabled__D=FALSE";
                asmopts += " -Dti_sysbios_BIOS_smpEnabled__D=FALSE";

                if ((targ.$name == "ti.targets.arm.elf.A8") ||
                    (targ.$name == "ti.targets.arm.elf.A8F") ||
                    (targ.$name == "ti.targets.arm.elf.A8Fnv") ||
                    (targ.$name == "gnu.targets.arm.A8F")) {
                    ccopts +=
                        " -Dti_sysbios_family_arm_a8_intcps_Hwi_enableAsidTagging__D=FALSE";
                    asmopts +=
                        " -Dti_sysbios_family_arm_a8_intcps_Hwi_enableAsidTagging__D=FALSE";
                }

                if (targ.$name == "gnu.targets.arm.A15F") {
                    ccopts +=
                        " -Dti_sysbios_family_arm_gic_Hwi_enableAsidTagging__D=FALSE";
                    asmopts +=
                        " -Dti_sysbios_family_arm_gic_Hwi_enableAsidTagging__D=FALSE";
                }
            }

            /* confirm that this target supports this profile */
            if (targ.profiles[profiles[j]] !== undefined) {
                var profile = profiles[j];
                var lib = Pkg.addLibrary(libPath + Pkg.name,
                                targ, {
                                profile: profile,
                                copts: ccopts,
                                aopts: asmopts,
                                releases: relList,
				incs: incs,
                                });
                lib.addObjects(objList);
                /* suppress debug libs from exports */
                Pkg.attrs.relScript = "ti/sysbios/libFilter.xs";
            }
        }
    }
}


/*
 *  ======== supportsTarget ========
 *  Returns true if target is in the filter object. If filter
 *  is null or empty, that's taken to mean all targets are supported.
 */
function supportsTarget(target, filter)
{
    var list, field;

    if (filter == null) {
        return true;
    }

    /*
     * For backwards compatibility, we support filter as an array of
     * target names.  The preferred approach is to specify filter as
     * an object with 'field' and 'list' elements.
     *
     * Old form:
     *     var trgFilter = [ "Arm9", "Arm9t", "Arm9t_big_endian" ]
     *
     * New (preferred) form:
     *
     *     var trgFilter = {
     *         field: "isa",
     *         list: [ "v5T", "v7R" ]
     *     };
     *
     */
    if (filter instanceof Array) {
        list = filter;
        field = "name";
    }
    else {
        list = filter.list;
        field = filter.field;
    }

    if (list == null || field == null) {
        throw("invalid filter parameter, must specify list and field!");
    }

    if (field == "noIsa") {
        if (String(','+list.toString()+',').match(','+target["isa"]+',')) {
            return (false);
        }
        return (true);
    }

    /*
     * add ',' at front and and tail of list and field strings to allow
     * use of simple match API.  For example, the string is updated to:
     * ',v5T,v7R,' to allow match of ',v5t,'.
     */
    if (String(','+list.toString()+',').match(','+target[field]+',')) {
        return (true);
    }

    return (false);
}
