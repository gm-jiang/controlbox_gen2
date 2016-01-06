/* Paths to external source libraries */
xdcargs = java.lang.System.getenv("XDCARGS").split(" ");
var commonBld = xdc.loadCapsule("ti/tirtos/build/common.bld");

var BIOSVer = "";
var TivaWareVer = "";
var MWareVer = "";
var MSP430WareVer = "";
var CC26xxVer = "";
var CCWareVer = "";
var NDKVer = "";

/* Parse out the XDCARGS options for the library source paths */
for (x = 0; x < xdcargs.length; x++) {
    if (xdcargs[x].match(/^TIVAWARE=/)) {
        TivaWareVer = xdcargs[x].match(/TivaWare_C_Series-[0-9\.a-zA-Z]*/);
    }
    if (xdcargs[x].match(/^CC26XXWARE=/)) {
        CC26xxVer = xdcargs[x].match(/cc26xxware[0-9\.a-z_]*/);
    }
    if (xdcargs[x].match(/^CCWARE=/)) {
        CCWareVer = xdcargs[x].match(/CC3200_driverlib_[0-9\.a-z_]*/);
    }
    if (xdcargs[x].match(/^MWARE=/)) {
        MWareVer = xdcargs[x].match(/MWare_v\d{3}[a-zA-Z]?/);
    }
    if (xdcargs[x].match(/^MSP430WARE=/) || xdcargs[x].match(/^MSP430WareDir=/)) {
        MSP430WareVer = xdcargs[x].match(/MSP430Ware(_\d\d?){4}[a-zA-Z]?/)[0];
    }
    if (xdcargs[x].match(/^BIOS=/)) {
        BIOSVer = xdcargs[x].match(/bios_[0-9a-zA-Z_]*/);
    }
    if (xdcargs[x].match(/^NDK=/)) {
        NDKVer = xdcargs[x].match(/ndk_[0-9a-zA-Z_]*/);
    }
}

/* Filters for which devices to show */
var filterTMDXDOCK28M36_M3 = [
    {deviceFamily:"ARM", deviceId:".*F28M36P63C2.*", toolChain:"TI"},
];

var filterTMDXDOCK28M36_M3Demo = [
    {deviceFamily:"ARM", deviceId:".*F28M36P63C2.*", toolChain:"TI"},
];

var filterTMDXDOCKH52C1_M3 = [
    {deviceFamily:"ARM", deviceId:".*F28M35H52C1.*", toolChain:"TI"},
];

var filterTMDXDOCKH52C1_M3Demo = [
    {deviceFamily:"ARM", deviceId:".*F28M35H52C1.*", toolChain:"TI"},
];

var filterTMDXDOCKH52C1_C28 = [
    {deviceFamily:"C2000", deviceId:".*F28M35H52C1.*", toolChain:"TI"},
];

var filterTMDXDOCK28M36_C28 = [
    {deviceFamily:"C2000", deviceId:".*F28M36P63C2.*", toolChain:"TI"},
];

var filterDK_TM4C123G = [
    {deviceFamily:"ARM", deviceId:".*TM4C123GH6PGE.*", toolChain:"TI"},
];

var filterDK_TM4C129X = [
    {deviceFamily:"ARM", deviceId:".*TM4C129XNCZAD.*", toolChain:"TI"},
];

var filterEK_TM4C1294XL = [
    {deviceFamily:"ARM", deviceId:".*TM4C1294NCPDT.*", toolChain:"TI"},
];

var filterEKS_LM4F232 = [
    {deviceFamily:"ARM", deviceId:".*LM4F232H5QD.*", toolChain:"TI"},
];

var filterEK_TM4C123GXL = [
    {deviceFamily:"ARM", deviceId:".*TM4C123GH6PM.*", toolChain:"TI"},
];

var filterEK_LM4F120XL = [
    {deviceFamily:"ARM", deviceId:".*LM4F120H5QR.*", toolChain:"TI"},
];

var filterCC2650DK = [
    {deviceFamily: "ARM", deviceId: ".*CC265.*", toolChain: "TI"},
];

var filterCC2650STK_BLE = [
    {deviceFamily: "ARM", deviceId: ".*CC265.*", toolChain: "TI"},
];

var filterCC3200_LP = [
    {deviceFamily: "ARM", deviceId: ".*CC3200.*", toolChain: "TI"},
];

var filterMSP_EXP430F5529LP = [
    {deviceFamily: "MSP430", deviceId:".*MSP430F5529.*", toolChain:"TI"},
];

var filterMSP_EXP430F5529 = [
    {deviceFamily: "MSP430", deviceId:".*MSP430F5529.*", toolChain:"TI"},
];

var filterMSP_EXP430FR5969LP = [
    {deviceFamily: "MSP430", deviceId:".*MSP430FR5969", toolChain:"TI"},
];

/*
 * linkerCommandFile is used below since CCS/project wizard does not allow the
 * use of linkerCommandFile like we'd like.  The workaround is to provide
 * the .cmd file in the fileList[] array and set linkerCommandFile to "".
 */

/* TMDXDOCK28M36 M3 */
var TMDXDOCK28M36_M3 =
{
    name: "TMDXDOCK28M36_M3",
    trexName: "TMDXDOCK28M36 Experimenter Kit",
    tools: ["TI"],
    productGroup: "C2000",
    variant: "m3",
    filter: filterTMDXDOCK28M36_M3,
    root: "boards/TMDXDOCK28M36/",
    type: "MWare",
    platforms: {
        TI: "ti.platforms.concertoM3:F28M36P63C2",
    },
    targets: {
        TI: "ti.targets.arm.elf.M3",
    },
    fileList: ["Board.h", "TMDXDOCK28M36.c", "TMDXDOCK28M36.h"],
    linkercmd: {
        TI: "TMDXDOCK28M36.cmd",
    },
    compilerBuildOptions: {
        TI: " -I${COM_TI_RTSC_TIRTOSC2000_INSTALL_DIR}/products/" + MWareVer
            + "/MWare --gcc --gen_func_subsections=on -Dccs -DMWARE",
        TI_makefile:  " -mv7M3 --code_state=16 --abi=eabi -me --gen_func_subsections=on"
             + "  --gcc --gen_func_subsections=on -Dccs -DMWARE"
             + " -I$(CODEGEN_INSTALLATION_DIR)/include -I$(MWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI: " -l${COM_TI_RTSC_TIRTOSC2000_INSTALL_DIR}/products/" + MWareVer
            + "/MWare/driverlib/ccs/Debug/driverlib.lib"
            + " -l${COM_TI_RTSC_TIRTOSC2000_INSTALL_DIR}/products/"
            + MWareVer + "/MWare/usblib/ccs/Debug/usblib.lib -x",
        TI_makefile: " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
              + " --reread_libs --warn_sections --display_error_number"
              + " --diag_wrap=off --rom_model TMDXDOCK28M36.cmd -lrtsv7M3_T_le_eabi.lib"
              + " -l$(MWARE_INSTALLATION_DIR)/driverlib/ccs/Debug/driverlib.lib"
              + " -l$(MWARE_INSTALLATION_DIR)/usblib/ccs/Debug/usblib.lib"
              + " -l$(MWARE_INSTALLATION_DIR)/grlib/ccs/Debug/grlib.lib -x",
    },
    peripherals: ["Ethernet", "FatFs", "GPIO", "I2C", "SPI", "UART", "USB",
                  "Watchdog", "Demo"]
};

/* TMDXDOCKH52C1 M3 */
var TMDXDOCKH52C1_M3 =
{
    name: "TMDXDOCKH52C1_M3",
    trexName: "TMDXDOCKH52C1 Experimenter Kit",
    tools: ["TI"],
    productGroup: "C2000",
    variant: "m3",
    filter: filterTMDXDOCKH52C1_M3,
    root: "boards/TMDXDOCKH52C1/",
    type: "MWare",
    platforms: {
        TI: "ti.platforms.concertoM3:F28M35H52C1",
    },
    targets: {
        TI: "ti.targets.arm.elf.M3",
    },
    fileList: ["Board.h", "TMDXDOCKH52C1.c", "TMDXDOCKH52C1.h"],
    linkercmd: {
        TI: "TMDXDOCKH52C1.cmd",
    },
    compilerBuildOptions: {
        TI: " -I${COM_TI_RTSC_TIRTOSC2000_INSTALL_DIR}/products/" + MWareVer
            + "/MWare --gcc --gen_func_subsections=on -Dccs -DMWARE",
        TI_makefile:  " -mv7M3 --code_state=16 --abi=eabi -me --gen_func_subsections=on"
             + "  --gcc --gen_func_subsections=on -Dccs -DMWARE"
             + " -I$(CODEGEN_INSTALLATION_DIR)/include -I$(MWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI: " -l${COM_TI_RTSC_TIRTOSC2000_INSTALL_DIR}/products/" + MWareVer
            + "/MWare/driverlib/ccs/Debug/driverlib.lib"
            + " -l${COM_TI_RTSC_TIRTOSC2000_INSTALL_DIR}/products/" + MWareVer
            + "/MWare/usblib/ccs/Debug/usblib.lib -x",
        TI_makefile: " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
              + " --reread_libs --warn_sections --display_error_number"
              + " --diag_wrap=off --rom_model TMDXDOCKH52C1.cmd -lrtsv7M3_T_le_eabi.lib"
              + " -l$(MWARE_INSTALLATION_DIR)/driverlib/ccs/Debug/driverlib.lib"
              + " -l$(MWARE_INSTALLATION_DIR)/usblib/ccs/Debug/usblib.lib"
              + " -l$(MWARE_INSTALLATION_DIR)/grlib/ccs/Debug/grlib.lib -x",
    },
    peripherals: ["Ethernet", "FatFs", "GPIO", "I2C", "SPI", "UART", "USB",
                  "Watchdog", "Demo"]
};

/* DK_TM4C123G */
var DK_TM4C123G =
{
    name: "DK_TM4C123G",
    trexName: "DK-TM4C123G Evaluation Kit",
    tools: ["TI", "IAR", "GNU"],
    productGroup: "TivaC",
    filter: filterDK_TM4C123G,
    root: "boards/DK_TM4C123G/",
    type: "TivaWare",
    platforms: {
        TI: "ti.platforms.tiva:TM4C123GH6PGE",
        IAR: "ti.platforms.tiva:TM4C123GH6PGE",
        GNU: "ti.platforms.tiva:TM4C123GH6PGE"
    },
    targets: {
        TI: "ti.targets.arm.elf.M4F",
        IAR: "iar.targets.arm.M4F",
        GNU: "gnu.targets.arm.M4F"
    },
    fileList: ["Board.h", "DK_TM4C123G.c", "DK_TM4C123G.h"],
    linkercmd: {
        TI: "DK_TM4C123G.cmd",
        IAR: "TM4C123GH6.icf",
        GNU: "tm4c123gh6pge.lds"
    },
    compilerBuildOptions: {
        TI:  " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
             + " -DPART_TM4C123GH6PGE --gcc --gen_func_subsections=on -Dccs -DTIVAWARE"
             + " -DTARGET_IS_BLIZZARD_RA1",
        TI_makefile:  " -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi"
             + " -me --gen_func_subsections=on -DPART_TM4C123GH6PGE --gcc --gen_func_subsections=on -Dccs"
             + "  -DTIVAWARE -DTARGET_IS_BLIZZARD_RA1"
             + " -I$(CODEGEN_INSTALLATION_DIR)/include -I$(TIVAWARE_INSTALLATION_DIR)",
        IAR_makefile: " --debug --silent -DPART_TM4C123GH6PGE -DTIVAWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
        GNU: " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
             + " -mfpu=fpv4-sp-d16 -D PART_TM4C123GH6PGE -D TIVAWARE -D gcc"
             + " -ffunction-sections -fdata-sections"
             + " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer,
        GNU_makefile: " -D PART_TM4C123GH6PGE -D TIVAWARE -D gcc -Wall"
             + " -ffunction-sections -fdata-sections"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI:   " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/driverlib/ccs/Debug/driverlib.lib"
              + " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/usblib/ccs/Debug/usblib.lib"
              + " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/grlib/ccs/Debug/grlib.lib -x",
        TI_makefile:   " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
              + " --reread_libs --warn_sections --display_error_number"
              + " --diag_wrap=off --rom_model DK_TM4C123G.cmd -llibc.a"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/driverlib/ccs/Debug/driverlib.lib"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/usblib/ccs/Debug/usblib.lib"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/grlib/ccs/Debug/grlib.lib -x",
        IAR_makefile:  " $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
              + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a"
              + " --silent --cpu=Cortex-M4F --semihosting=iar_breakpoint"
              + " --config TM4C123GH6.icf --entry=__iar_program_start"
              + " --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall"
              + " --map $(NAME).map",
        GNU:  " -nostartfiles -static --gc-sections -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/"
              + TivaWareVer + "/driverlib/gcc"
              + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/usblib/gcc"
              + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + BIOSVer
              + "/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/armv7e-m/fpu",
        GNU_makefile:  " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
              + " -mfpu=fpv4-sp-d16 -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
              + " -Wl,-T,tm4c123gh6pge.lds -Wl,-T,$(NAME)/linker.cmd -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L$(TIVAWARE_INSTALLATION_DIR)/driverlib/gcc"
              + " -L$(TIVAWARE_INSTALLATION_DIR)/usblib/gcc"
              + " -L$(XDCTOOLS_INSTALLATION_DIR)/packages/gnu/targets/arm/libs/install-native/"
              + "arm-none-eabi/lib/armv7e-m/fpu"
    },
    compilerIncludes: {
        IAR: "-DPART_TM4C123GH6PGE -DTIVAWARE -Dewarm"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerIncludes: {
        IAR: " $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
             + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a",
    },
    peripherals: ["FatFs", "GPIO", "I2C", "SPI", "UART", "USB", "Watchdog",
                  "WiFi", "Demo"]
};

/* EKS_LM4F232 */
var EKS_LM4F232 =
{
    name: "EKS_LM4F232",
    trexName: "EKS-LM4F232 Evaluation Kit",
    tools: ["TI", "IAR", "GNU"],
    productGroup: "TivaC",
    filter: filterEKS_LM4F232,
    root: "boards/DK_TM4C123G/",
    type: "TivaWare",
    platforms: {
        TI: "ti.platforms.tiva:TM4C123GH6PGE",
        IAR: "ti.platforms.tiva:TM4C123GH6PGE",
        GNU: "ti.platforms.tiva:TM4C123GH6PGE"
    },
    targets: {
        TI: "ti.targets.arm.elf.M4F",
        IAR: "iar.targets.arm.M4F",
        GNU: "gnu.targets.arm.M4F"
    },
    fileList: ["Board.h", "DK_TM4C123G.c", "DK_TM4C123G.h"],
    linkercmd: {
        TI: "DK_TM4C123G.cmd",
        IAR: "TM4C123GH6.icf",
        GNU: "tm4c123gh6pge.lds"
    },
    compilerBuildOptions: {
        TI:  " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
             + " -DPART_TM4C123GH6PGE --gcc --gen_func_subsections=on -Dccs -DTIVAWARE"
             + " -DTARGET_IS_BLIZZARD_RA1",
        TI_makefile:  " -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi"
             + " -me --gen_func_subsections=on -DPART_TM4C123GH6PGE --gcc --gen_func_subsections=on -Dccs"
             + "  -DTIVAWARE -DTARGET_IS_BLIZZARD_RA1"
             + " -I$(CODEGEN_INSTALLATION_DIR)/include -I$(TIVAWARE_INSTALLATION_DIR)",
        IAR_makefile: " --debug --silent -DPART_TM4C123GH6PGE -DTIVAWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
        GNU: " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
             + " -mfpu=fpv4-sp-d16 -D PART_TM4C123GH6PGE -D TIVAWARE -D gcc"
             + " -ffunction-sections -fdata-sections"
             + " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer,
        GNU_makefile: " -D PART_TM4C123GH6PGE -D TIVAWARE -D gcc -Wall"
             + " -ffunction-sections -fdata-sections"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI:   " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/driverlib/ccs/Debug/driverlib.lib"
              + " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/usblib/ccs/Debug/usblib.lib"
              + " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/grlib/ccs/Debug/grlib.lib -x",
        TI_makefile:   " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
              + " --reread_libs --warn_sections --display_error_number"
              + " --diag_wrap=off --rom_model DK_TM4C123G.cmd -llibc.a"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/driverlib/ccs/Debug/driverlib.lib"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/usblib/ccs/Debug/usblib.lib"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/grlib/ccs/Debug/grlib.lib -x",
        IAR_makefile:  " $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
              + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a"
              + " --silent --cpu=Cortex-M4F --semihosting=iar_breakpoint"
              + " --config TM4C123GH6.icf --entry=__iar_program_start"
              + " --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall"
              + " --map $(NAME).map",
        GNU:  " -nostartfiles -static --gc-sections -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/"
              + TivaWareVer + "/driverlib/gcc"
              + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/usblib/gcc"
              + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/product/" + BIOSVer
              + "/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/armv7e-m/fpu",
        GNU_makefile:  " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
              + " -mfpu=fpv4-sp-d16 -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
              + " -Wl,-T,tm4c123gh6pge.lds -Wl,-T,$(NAME)/linker.cmd -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L$(TIVAWARE_INSTALLATION_DIR)/driverlib/gcc"
              + " -L$(TIVAWARE_INSTALLATION_DIR)/usblib/gcc"
              + " -L$(XDCTOOLS_INSTALLATION_DIR)/packages/gnu/targets/arm/libs/install-native/"
              + "arm-none-eabi/lib/armv7e-m/fpu"
    },
    compilerIncludes: {
        IAR: " -DPART_TM4C123GH6PGE -DTIVAWARE -Dewarm"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerIncludes: {
        IAR: " $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
             + "$(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a",
    },
    peripherals: ["FatFs", "GPIO", "I2C", "SPI", "UART", "USB", "Watchdog",
                  "WiFi", "Demo"]
};

/* EK_TM4C123GXL */
var EK_TM4C123GXL =
{
    name: "EK_TM4C123GXL",
    trexName: "EK-TM4C123GXL Launchpad",
    tools: ["TI", "IAR", "GNU"],
    productGroup: "TivaC",
    filter: filterEK_TM4C123GXL,
    root: "boards/EK_TM4C123GXL/",
    type: "TivaWare",
    platforms: {
        TI: "ti.platforms.tiva:TM4C123GH6PM",
        IAR: "ti.platforms.tiva:TM4C123GH6PM",
        GNU: "ti.platforms.tiva:TM4C123GH6PM"
    },
    targets: {
        TI: "ti.targets.arm.elf.M4F",
        IAR: "iar.targets.arm.M4F",
        GNU: "gnu.targets.arm.M4F"
    },
    fileList: ["Board.h", "EK_TM4C123GXL.c", "EK_TM4C123GXL.h"],
    linkercmd: {
        TI: "EK_TM4C123GXL.cmd",
        IAR: "LM4F120GXL.icf",
        GNU: "tm4c123gh6pm.lds"
    },
    compilerBuildOptions: {
        TI: " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + " -DPART_TM4C123GH6PM --gcc --gen_func_subsections=on -Dccs -DTIVAWARE",
        TI_makefile:  " -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi"
             + " -me --gen_func_subsections=on -DPART_TM4C123GH6PM --gcc --gen_func_subsections=on -Dccs"
             + "  -DTIVAWARE -DTARGET_IS_BLIZZARD_RA1"
             + " -I$(CODEGEN_INSTALLATION_DIR)/include -I$(TIVAWARE_INSTALLATION_DIR)",
        IAR_makefile: " --debug --silent -DPART_TM4C123GH6PM -DTIVAWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
        GNU: " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
             + " -mfpu=fpv4-sp-d16 -D PART_TM4C123GH6PM -D TIVAWARE -D gcc"
             + " -ffunction-sections -fdata-sections"
             + " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer,
        GNU_makefile: " -D PART_TM4C123GH6PM -D TIVAWARE -D gcc -Wall"
             + " -ffunction-sections -fdata-sections"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI: " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + "/driverlib/ccs/Debug/driverlib.lib"
            + " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + "/usblib/ccs/Debug/usblib.lib -x",
        TI_makefile: " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
              + " --reread_libs --warn_sections --display_error_number"
              + " --diag_wrap=off --rom_model EK_TM4C123GXL.cmd -llibc.a"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/driverlib/ccs/Debug/driverlib.lib"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/usblib/ccs/Debug/usblib.lib"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/grlib/ccs/Debug/grlib.lib -x",
        IAR_makefile: " $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
             + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a"
             + " --silent --cpu=Cortex-M4F --semihosting=iar_breakpoint"
             + " --config LM4F120GXL.icf --entry=__iar_program_start --redirect"
             + " _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall --map"
             + " $(NAME).map",
        GNU: " -nostartfiles -static --gc-sections -lusb -ldriver -lgcc -lc"
             + " -lm -lrdimon -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/"
             + TivaWareVer + "/driverlib/gcc"
             + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
             + "/usblib/gcc  -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + BIOSVer
             + "/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/armv7e-m/fpu",
        GNU_makefile:  " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
              + " -mfpu=fpv4-sp-d16 -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
              + " -Wl,-T,tm4c123gh6pm.lds -Wl,-T,$(NAME)/linker.cmd -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L$(TIVAWARE_INSTALLATION_DIR)/driverlib/gcc"
              + " -L$(TIVAWARE_INSTALLATION_DIR)/usblib/gcc"
              + " -L$(XDCTOOLS_INSTALLATION_DIR)/packages/gnu/targets/arm/libs/install-native/"
              + "arm-none-eabi/lib/armv7e-m/fpu"
    },
    compilerIncludes: {
        IAR: "-DPART_TM4C123GH6PM -DTIVAWARE -Dewarm"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerIncludes: {
        IAR: "  $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
             + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a ",
    },
    peripherals: ["FatFs", "GPIO", "I2C", "PWM", "SPI", "UART", "USB", "Watchdog",
                  "WiFi"]
};

/* EK_LM4F120XL */
var EK_LM4F120XL =
{
    name: "EK_LM4F120XL",
    trexName: "EK-LM4F120XL Launchpad",
    tools: ["TI", "IAR", "GNU"],
    productGroup: "TivaC",
    filter: filterEK_LM4F120XL,
    root: "boards/EK_LM4F120XL/",
    type: "TivaWare",
    platforms: {
        TI: "ti.platforms.tiva:LM4F120H5QR",
        IAR: "ti.platforms.tiva:LM4F120H5QR",
        GNU: "ti.platforms.tiva:LM4F120H5QR"
    },
    targets: {
        TI: "ti.targets.arm.elf.M4F",
        IAR: "iar.targets.arm.M4F",
        GNU: "gnu.targets.arm.M4F"
    },
    fileList: ["Board.h", "EK_LM4F120XL.c", "EK_LM4F120XL.h"],
    linkercmd: {
        TI: "EK_LM4F120XL.cmd",
        IAR: "LM4F120GXL.icf",
        GNU: "tm4c123gh6pm.lds"
    },
    compilerBuildOptions: {
        TI: " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + " -DPART_TM4C123GH6PM --gcc --gen_func_subsections=on -Dccs -DTIVAWARE",
        TI_makefile:  " -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi"
             + " -me --gen_func_subsections=on -DPART_TM4C123GH6PM --gcc --gen_func_subsections=on -Dccs"
             + "  -DTIVAWARE -DTARGET_IS_BLIZZARD_RA1"
             + " -I$(CODEGEN_INSTALLATION_DIR)/include -I$(TIVAWARE_INSTALLATION_DIR)",
        IAR_makefile: " --debug --silent -DPART_TM4C123GH6PM -DTIVAWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
        GNU: " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
             + " -mfpu=fpv4-sp-d16 -D PART_TM4C123GH6PM -D TIVAWARE -D gcc"
             + " -ffunction-sections -fdata-sections"
             + " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer,
        GNU_makefile: " -D PART_TM4C123GH6PM -D TIVAWARE -D gcc -Wall"
             + " -ffunction-sections -fdata-sections"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI: " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + "/driverlib/ccs/Debug/driverlib.lib"
            + " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + "/usblib/ccs/Debug/usblib.lib -x",
        TI_makefile: " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
              + " --reread_libs --warn_sections --display_error_number"
              + " --diag_wrap=off --rom_model EK_LM4F120XL.cmd -llibc.a"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/driverlib/ccs/Debug/driverlib.lib"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/usblib/ccs/Debug/usblib.lib"
              + " -l$(TIVAWARE_INSTALLATION_DIR)/grlib/ccs/Debug/grlib.lib -x",
        IAR_makefile: " $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
             + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a"
             + " --silent --cpu=Cortex-M4F --semihosting=iar_breakpoint"
             + " --config LM4F120GXL.icf --entry=__iar_program_start"
             + " --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall"
             + " --map $(NAME).map",
        GNU:  " -nostartfiles -static --gc-sections -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/"
              + TivaWareVer + "/driverlib/gcc"
              + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/usblib/gcc  -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + BIOSVer
              + "/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/armv7e-m/fpu",
        GNU_makefile: " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
              + " -mfpu=fpv4-sp-d16 -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
              + " -Wl,-T,tm4c123gh6pm.lds -Wl,-T,$(NAME)/linker.cmd -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L$(TIVAWARE_INSTALLATION_DIR)/driverlib/gcc"
              + " -L$(TIVAWARE_INSTALLATION_DIR)/usblib/gcc"
              + " -L$(XDCTOOLS_INSTALLATION_DIR)/packages/gnu/targets/arm/libs/install-native/"
              + "arm-none-eabi/lib/armv7e-m/fpu"
    },
    compilerIncludes: {
        IAR: " -DPART_TM4C123GH6PM -DTIVAWARE -Dewarm"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerIncludes: {
        IAR: "  $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
             + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a ",
    },
    peripherals: ["FatFs", "GPIO", "I2C", "SPI", "UART", "USB", "Watchdog",
                  "WiFi"]
};

/* DK_TM4C129X */
var DK_TM4C129X =
{
    name: "DK_TM4C129X",
    trexName: "DK-TM4C129X Evaluation Kit",
    tools: ["TI", "IAR", "GNU"],
    productGroup: "TivaC",
    filter: filterDK_TM4C129X,
    root: "boards/DK_TM4C129X/",
    type: "TivaWare",
    platforms: {
        TI: "ti.platforms.tiva:TM4C129XNCZAD",
        IAR: "ti.platforms.tiva:TM4C129XNCZAD",
        GNU: "ti.platforms.tiva:TM4C129XNCZAD",
    },
    targets: {
        TI: "ti.targets.arm.elf.M4F",
        IAR: "iar.targets.arm.M4F",
        GNU: "gnu.targets.arm.M4F"
    },
    fileList: ["Board.h", "DK_TM4C129X.c", "DK_TM4C129X.h"],
    linkercmd: {
        TI: "DK_TM4C129X.cmd",
        IAR: "TM4C129XNC.icf",
        GNU: "tm4c129xnczad.lds"
    },
    compilerBuildOptions: {
        TI: " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + " -DPART_TM4C129XNCZAD --gcc --gen_func_subsections=on -Dccs -DTIVAWARE",
        TI_makefile:  " -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi"
             + " -me --gen_func_subsections=on -DPART_TM4C129XNCZAD --gcc --gen_func_subsections=on -Dccs"
             + "  -DTIVAWARE"
             + " -I$(CODEGEN_INSTALLATION_DIR)/include -I$(TIVAWARE_INSTALLATION_DIR)",
        IAR_makefile: " --debug --silent -DPART_TM4C129XNCZAD -DTIVAWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
        GNU: " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
             + " -mfpu=fpv4-sp-d16 -D PART_TM4C129XNCZAD -D TIVAWARE -D gcc"
             + " -ffunction-sections -fdata-sections"
             + " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer,
        GNU_makefile: " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
             + " -mfpu=fpv4-sp-d16 -D PART_TM4C129XNCZAD -D TIVAWARE -D gcc -Wall"
             + " -ffunction-sections -fdata-sections"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI: " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + "/driverlib/ccs/Debug/driverlib.lib"
            + " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + "/usblib/ccs/Debug/usblib.lib -x",
        TI_makefile: " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
            + " --reread_libs --warn_sections --display_error_number"
            + " --diag_wrap=off --rom_model DK_TM4C129X.cmd -llibc.a"
            + " -l$(TIVAWARE_INSTALLATION_DIR)/driverlib/ccs/Debug/driverlib.lib"
            + " -l$(TIVAWARE_INSTALLATION_DIR)/usblib/ccs/Debug/usblib.lib"
            + " -l$(TIVAWARE_INSTALLATION_DIR)/grlib/ccs/Debug/grlib.lib",
        IAR_makefile: " $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
             + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a"
             + " --silent --cpu=Cortex-M4F --semihosting=iar_breakpoint"
             + " --config TM4C129XNC.icf --entry=__iar_program_start"
             + " --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall"
             + " --map $(NAME).map",
        GNU:  " -nostartfiles -static --gc-sections -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/"
              + TivaWareVer + "/driverlib/gcc"
              + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
              + "/usblib/gcc -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + BIOSVer
              + "/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/armv7e-m/fpu",
        GNU_makefile:  " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
              + " -mfpu=fpv4-sp-d16 -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
              + " -Wl,-T,tm4c129xnczad.lds -Wl,-T,$(NAME)/linker.cmd -lusb -ldriver -lgcc -lc"
              + " -lm -lrdimon -L$(TIVAWARE_INSTALLATION_DIR)/driverlib/gcc"
              + " -L$(TIVAWARE_INSTALLATION_DIR)/usblib/gcc"
              + " -L$(XDCTOOLS_INSTALLATION_DIR)/packages/gnu/targets/arm/libs/install-native/"
              + "arm-none-eabi/lib/armv7e-m/fpu"
    },
    compilerIncludes: {
        IAR: " -DPART_TM4C129XNCZAD -DTIVAWARE -Dewarm"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerIncludes: {
        IAR: "$(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a "
           + "$(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a ",
    },
    peripherals: ["Ethernet", "FatFs", "GPIO", "I2C", "PWM", "SPI", "UART", "USB",
                  "Watchdog", "WiFi"]
};

/* EK_TM4C1294XL */
var EK_TM4C1294XL =
{
    name: "EK_TM4C1294XL",
    trexName: "EK-TM4C1294XL",
    tools: ["TI", "IAR", "GNU"],
    productGroup: "TivaC",
    filter: filterEK_TM4C1294XL,
    root: "boards/EK_TM4C1294XL/",
    type: "TivaWare",
    platforms: {
        TI: "ti.platforms.tiva:TM4C1294NCPDT",
        IAR: "ti.platforms.tiva:TM4C1294NCPDT",
        GNU: "ti.platforms.tiva:TM4C1294NCPDT",
    },
    targets: {
        TI: "ti.targets.arm.elf.M4F",
        IAR: "iar.targets.arm.M4F",
        GNU: "gnu.targets.arm.M4F"
    },
    fileList: ["Board.h", "EK_TM4C1294XL.c", "EK_TM4C1294XL.h"],
    linkercmd: {
        TI: "EK_TM4C1294XL.cmd",
        IAR: "TM4C1294NC.icf",
        GNU: "tm4c1294ncpdt.lds"
    },
    compilerBuildOptions: {
        TI: " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + " -DPART_TM4C1294NCPDT --gcc --gen_func_subsections=on -Dccs -DTIVAWARE",
        TI_makefile:  " -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi"
             + " -me --gen_func_subsections=on -DPART_TM4C1294NCPDT --gcc --gen_func_subsections=on -Dccs"
             + "  -DTIVAWARE"
             + " -I$(CODEGEN_INSTALLATION_DIR)/include"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
        IAR_makefile: " --debug --silent -DPART_TM4C1294NCPDT -DTIVAWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
        GNU: " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
             + " -mfpu=fpv4-sp-d16 -D PART_TM4C1294NCPDT -D TIVAWARE -D gcc"
             + " -ffunction-sections -fdata-sections"
             + " -I${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer,
        GNU_makefile: " -D PART_TM4C1294NCPDT -D TIVAWARE -D gcc -Wall"
             + " -ffunction-sections -fdata-sections"
             + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI: " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + "/driverlib/ccs/Debug/driverlib.lib"
            + " -l${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer
            + "/usblib/ccs/Debug/usblib.lib -x",
        TI_makefile: " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
            + " --reread_libs --warn_sections --display_error_number"
            + " --diag_wrap=off --rom_model EK_TM4C1294XL.cmd -llibc.a"
            + " -l$(TIVAWARE_INSTALLATION_DIR)/driverlib/ccs/Debug/driverlib.lib"
            + " -l$(TIVAWARE_INSTALLATION_DIR)/usblib/ccs/Debug/usblib.lib"
            + " -l$(TIVAWARE_INSTALLATION_DIR)/grlib/ccs/Debug/grlib.lib",
        IAR_makefile: " $(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a"
            + " $(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a"
            + " --silent --cpu=Cortex-M4F --semihosting=iar_breakpoint"
            + " --config TM4C1294NC.icf --entry=__iar_program_start"
            + " --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall"
            + " --map $(NAME).map",
        GNU:  " -nostartfiles -static --gc-sections -lusb -ldriver -lgcc -lc"
            + " -lm -lrdimon -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer + "/driverlib/gcc"
            + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + TivaWareVer + "/usblib/gcc"
            + " -L${COM_TI_RTSC_TIRTOSTIVAC_INSTALL_DIR}/products/" + BIOSVer + "/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/armv7e-m/fpu",
        GNU_makefile:  " -march=armv7e-m -mcpu=cortex-m4 -mthumb -mfloat-abi=hard"
            + " -mfpu=fpv4-sp-d16 -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
            + " -Wl,-T,tm4c1294ncpdt.lds -Wl,-T,$(NAME)/linker.cmd -lusb -ldriver -lgcc -lc"
            + " -lm -lrdimon -L$(TIVAWARE_INSTALLATION_DIR)/driverlib/gcc"
            + " -L$(TIVAWARE_INSTALLATION_DIR)/usblib/gcc"
            + " -L$(XDCTOOLS_INSTALLATION_DIR)/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/armv7e-m/fpu"
    },
    compilerIncludes: {
        IAR: " -DPART_TM4C1294NCPDT -DTIVAWARE -Dewarm"
           + " -I$(TIVAWARE_INSTALLATION_DIR)",
    },
    linkerIncludes: {
        IAR: "$(TIVAWARE_INSTALLATION_DIR)/driverlib/ewarm/Exe/driverlib.a "
           + "$(TIVAWARE_INSTALLATION_DIR)/usblib/ewarm/Exe/usblib.a ",
    },
    peripherals: ["Ethernet", "FatFs", "GPIO", "I2C", "PWM", "SPI", "UART", "USB",
                  "Watchdog", "WiFi"]
};

/* CC2650DK */
var CC2650DK = {
    name: "CC2650DK",
    trexName: "CC2650DK",
    //tools: ["TI", "IAR", "GNU"],
    tools: ["TI", "IAR"],
    productGroup: "SimpleLink",
    filter: filterCC2650DK,
    root: "boards/CC2650DK/",
    type: "CC26XXWare",
    platforms: {
        TI:  "ti.platforms.simplelink:CC2650F128",
        IAR: "ti.platforms.simplelink:CC2650F128",
        GNU: "ti.platforms.simplelink:CC2650F128"
    },
    targets: {
        TI:  "ti.targets.arm.elf.M3",
        IAR: "iar.targets.arm.M3",
        GNU: "gnu.targets.arm.M3"
    },
    fileList: ["Board.c", "Board.h"],
    linkercmd: {
        TI:  "CC2650DK.cmd",
        IAR: "CC2650DK.icf",
        GNU: "CC2650DK.lds"
    },
    compilerBuildOptions: {
        TI:
               " -mv7M3 --code_state=16 --abi=eabi -me -g --gcc --gen_func_subsections=on"
             + "  --display_error_number --diag_warning=255 --diag_wrap=off -DCC26XXWARE"
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CC26xxVer,
        TI_makefile:
               " -mv7M3 --code_state=16 --abi=eabi -me -g --gcc --gen_func_subsections=on"
             + "  --display_error_number --diag_warning=255 --diag_wrap=off -DCC26XXWARE"
             + " -I$(CC26XXWARE_INSTALLATION_DIR)",

        IAR_makefile:
               " --debug --silent -DCC26XXWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(CC26XXWARE_INSTALLATION_DIR)",

         GNU:
               " -mcpu=cortex-m3 -march=armv7-m -mthumb -mfloat-abi=soft -DCC26XXWARE"
             + " -ffunction-sections -fdata-sections -g -gstrict-dwarf -Wall"
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CC26xxVer,
         GNU_makefile:
               " -mcpu=cortex-m3 -march=armv7-m -mthumb -mfloat-abi=soft -DCC26XXWARE"
             + " -ffunction-sections -fdata-sections -g -gstrict-dwarf -Wall"
             + " -I$(CC26XXWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI:
               " -l${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CC26xxVer + "/driverlib/bin/ccs/driverlib.lib -x",
        TI_makefile:
               " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
             + " --reread_libs --warn_sections --display_error_number"
             + " --diag_wrap=off --rom_model CC2650DK.cmd -llibc.a"
             + " -l$(CC26XXWARE_INSTALLATION_DIR)/driverlib/bin/ccs/driverlib.lib",

        IAR_makefile:
               " --silent --cpu=Cortex-M3 --semihosting=iar_breakpoint"
             + " --config CC2650DK.icf --entry=__iar_program_start"
             + " --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall"
             + " --map $(NAME).map"
             + " $(CC26XXWARE_INSTALLATION_DIR)/driverlib/bin/iar/driverlib.lib",

        GNU:
               " -nostartfiles -static --gc-sections -lgcc -lc -lm"
             + " ${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CC26xxVer + "/driverlib/bin/ccs/driverlib.lib",
        GNU_makefile:
               " -mcpu=cortex-m3 -march=armv7-m -mthumb -mfloat-abi=soft"
             + " -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
             + " -Wl,-T,CC2650DK.lds -Wl,-T,$(NAME)/linker.cmd -lgcc -lc -lm"
             + " $(CC26XXWARE_INSTALLATION_DIR)/driverlib/bin/ccs/driverlib.lib",
    },
    compilerIncludes: {
        IAR:
               " -DCC26XXWARE -Dewarm"
             + " -I$(CC26XXWARE_INSTALLATION_DIR)",
    },
    linkerIncludes: {
        IAR:
               " $(CC26XXWARE_INSTALLATION_DIR)/driverlib/bin/iar/driverlib.lib ",
    },
    peripherals: ["FatFs", "GPIO", "I2C", "LCD", "SPI", "PIN", "UART", "Watchdog", "Demo"]
};

/* CC2650STK_BLE */
var CC2650STK_BLE = {
    name: "CC2650STK_BLE",
    trexName: "CC2650STK-BLE (SensorTag)",
    //tools: ["TI", "IAR", "GNU"],
    tools: ["TI", "IAR"],
    productGroup: "SimpleLink",
    filter: filterCC2650STK_BLE,
    root: "boards/CC2650STK_BLE/",
    type: "CC26XXWare",
    platforms: {
        TI:  "ti.platforms.simplelink:CC2650F128",
        IAR: "ti.platforms.simplelink:CC2650F128",
        GNU: "ti.platforms.simplelink:CC2650F128"
    },
    targets: {
        TI:  "ti.targets.arm.elf.M3",
        IAR: "iar.targets.arm.M3",
        GNU: "gnu.targets.arm.M3"
    },
    fileList: ["Board.c", "Board.h"],
    linkercmd: {
        TI:  "CC2650STK_BLE.cmd",
        IAR: "CC2650STK_BLE.icf",
        GNU: "CC2650STK_BLE.lds"
    },
    compilerBuildOptions: {
        TI:
               " -mv7M3 --code_state=16 --abi=eabi -me -g --gcc --gen_func_subsections=on"
             + "  --display_error_number --diag_warning=255 --diag_wrap=off -DCC26XXWARE"
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CC26xxVer,
        TI_makefile:
               " -mv7M3 --code_state=16 --abi=eabi -me -g --gcc --gen_func_subsections=on"
             + "  --display_error_number --diag_warning=255 --diag_wrap=off -DCC26XXWARE"
             + " -I$(CC26XXWARE_INSTALLATION_DIR)",

        IAR_makefile:
               " --debug --silent -DCC26XXWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(CC26XXWARE_INSTALLATION_DIR)",

         GNU:
               " -mcpu=cortex-m3 -march=armv7-m -mthumb -mfloat-abi=soft -DCC26XXWARE"
             + " -ffunction-sections -fdata-sections -g -gstrict-dwarf -Wall"
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CC26xxVer,
         GNU_makefile:
               " -mcpu=cortex-m3 -march=armv7-m -mthumb -mfloat-abi=soft -DCC26XXWARE"
             + " -ffunction-sections -fdata-sections -g -gstrict-dwarf -Wall"
             + " -I$(CC26XXWARE_INSTALLATION_DIR)",
    },
    linkerBuildOptions: {
        TI:
               " -l${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CC26xxVer + "/driverlib/bin/ccs/driverlib.lib -x",
        TI_makefile:
               " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
             + " --reread_libs --warn_sections --display_error_number"
             + " --diag_wrap=off --rom_model CC2650STK_BLE.cmd -llibc.a"
             + " -l$(CC26XXWARE_INSTALLATION_DIR)/driverlib/bin/ccs/driverlib.lib",

        IAR_makefile:
               " --silent --cpu=Cortex-M3 --semihosting=iar_breakpoint"
             + " --config CC2650STK_BLE.icf --entry=__iar_program_start"
             + " --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall"
             + " --map $(NAME).map"
             + " $(CC26XXWARE_INSTALLATION_DIR)/driverlib/bin/iar/driverlib.lib",

        GNU:
               " -nostartfiles -static --gc-sections -lgcc -lc -lm"
             + " ${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CC26xxVer + "/driverlib/bin/ccs/driverlib.lib",
        GNU_makefile:
               " -mcpu=cortex-m3 -march=armv7-m -mthumb -mfloat-abi=soft"
             + " -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
             + " -Wl,-T,CC2650STK_BLE.lds -Wl,-T,$(NAME)/linker.cmd -lgcc -lc -lm"
             + " $(CC26XXWARE_INSTALLATION_DIR)/driverlib/bin/ccs/driverlib.lib",
    },
    compilerIncludes: {
        IAR:
               " -DCC26XXWARE -Dewarm"
             + " -I$(CC26XXWARE_INSTALLATION_DIR)",
    },
    linkerIncludes: {
        IAR:
               " $(CC26XXWARE_INSTALLATION_DIR)/driverlib/bin/iar/driverlib.lib ",
    },
    peripherals: ["FatFs", "GPIO", "I2C", "SPI", "PIN", "UART", "Watchdog", "Demo"]
};

/* CC3200_LP */
var CC3200_LP = {
    name: "CC3200_LP",
    trexName: "CC3200-LAUNCHXL",
    tools: ["TI", "IAR", "GNU"],
    productGroup: "SimpleLink",
    filter: filterCC3200_LP,
    root: "boards/CC3200_LP/",
    type: "CCWare",
    platforms: {
        TI: "ti.platforms.simplelink:CC3200",
        IAR: "ti.platforms.simplelink:CC3200",
        GNU: "ti.platforms.simplelink:CC3200"
    },
    targets: {
        TI: "ti.targets.arm.elf.M4",
        IAR: "iar.targets.arm.M4",
        GNU: "gnu.targets.arm.M4"
    },
    fileList: ["Board.h", "CC3200_LP.c", "CC3200_LP.h"],
    linkercmd: {
        TI: "CC3200_LP.cmd",
        IAR: "cc3200.icf",
        GNU: "cc3200.lds"
    },
    compilerBuildOptions: {
        TI:    " -mv7M4 --code_state=16 --abi=eabi -me -DPART_CC3200 -g --display_error_number --diag_warning=255 --diag_wrap=off"
             + " -Dccs -DCCWARE --gen_func_subsections=on"
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CCWareVer
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CCWareVer + "/inc"
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CCWareVer + "/driverlib",
        TI_makefile:
               " -mv7M4 --code_state=16 --abi=eabi -me -DPART_CC3200 -g --display_error_number --diag_warning=255 --diag_wrap=off"
             + " -Dccs -DCCWARE --gen_func_subsections=on"
             + " -I$(CCWARE_INSTALLATION_DIR)"
             + " -I$(CCWARE_INSTALLATION_DIR)/inc"
             + " -I$(CCWARE_INSTALLATION_DIR)/driverlib",

        IAR_makefile:
               " --debug --silent -DPART_CC3200 -DCCWARE -Dewarm"
             + " -I$(CGTOOLS)/inc/c/DLib_Config_Normal.h"
             + " -I$(CCWARE_INSTALLATION_DIR)"
             + " -I$(CCWARE_INSTALLATION_DIR)/inc"
             + " -I$(CCWARE_INSTALLATION_DIR)/driverlib",

         GNU:  " -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=soft -Dgcc"
             + " -DPART_CC3200 -DCCWARE"
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CCWareVer
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CCWareVer + "/inc"
             + " -I${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CCWareVer + "/driverlib"
             + " -ffunction-sections -fdata-sections -g -gstrict-dwarf -Wall",
         GNU_makefile:
               " -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=soft -Dgcc"
             + " -DPART_CC3200 -DCCWARE"
             + " -I$(CCWARE_INSTALLATION_DIR)"
             + " -I$(CCWARE_INSTALLATION_DIR)/inc"
             + " -I$(CCWARE_INSTALLATION_DIR)/driverlib"
             + " -ffunction-sections -fdata-sections -g -gstrict-dwarf -Wall",
    },
    linkerBuildOptions: {
        TI:    " -l${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CCWareVer + "/driverlib/ccs/Release/driverlib.a -x",

        TI_makefile:
               " -m$(NAME).map -i$(CODEGEN_INSTALLATION_DIR)/lib"
             + " --reread_libs --warn_sections --display_error_number"
             + " --diag_wrap=off --rom_model CC3200_LP.cmd -llibc.a"
             + " -l$(CCWARE_INSTALLATION_DIR)/driverlib/ccs/Release/driverlib.a",

        IAR_makefile: " $(CCWARE_INSTALLATION_DIR)/driverlib/ewarm/Release/Exe/driverlib.a"
             + " --silent --cpu=Cortex-M4 --semihosting=iar_breakpoint"
             + " --config cc3200.icf --entry=__iar_program_start"
             + " --redirect _Printf=_PrintfSmall --redirect _Scanf=_ScanfSmall"
             + " --map $(NAME).map",

        GNU:   " -nostartfiles -static --gc-sections -ldriver -lgcc -lc -lm -lrdimon "
             + " -L${COM_TI_RTSC_TIRTOSSIMPLELINK_INSTALL_DIR}/products/" + CCWareVer + "/driverlib/gcc/exe",
        GNU_makefile:
               " -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=soft"
             + " -nostartfiles -static -Wl,-Map,$(NAME).map -Wl,--gc-sections"
             + " -Wl,-T,cc3200.lds -Wl,-T,$(NAME)/linker.cmd -ldriver -lgcc -lc -lm -lrdimon "
             + " -L$(CCWARE_INSTALLATION_DIR)/driverlib/gcc/exe",
    },
    compilerIncludes: {
        IAR: " -DPART_CC3200 -DCCWARE -Dewarm"
           + " -I$(CCWARE_INSTALLATION_DIR)"
           + " -I$(CCWARE_INSTALLATION_DIR)/inc"
           + " -I$(CCWARE_INSTALLATION_DIR)/driverlib",
    },
    linkerIncludes: {
        IAR: "$(CCWARE_INSTALLATION_DIR)/driverlib/ewarm/Release/Exe/driverlib.a ",
    },
    peripherals: ["FatFs", "GPIO", "I2C", "PWM", "SPI", "UART", "Watchdog", "Demo"]
};

/* TMDXDOCK28M36 C28 */
var TMDXDOCK28M36_C28 =
{
    name: "TMDXDOCK28M36_C28",
    trexName: "TMDXDOCK28M36 Experimenter Kit",
    tools: ["TI"],
    productGroup: "C2000",
    variant: "c28",
    filter: filterTMDXDOCK28M36_C28,
    root: "boards/TMDXDOCK28M36/",
    platforms: {
        TI: "ti.platforms.concertoC28:$DeviceId$",
    },
    targets: {
        TI: "ti.targets.C28_float",
    },
    fileList: [],
    linkercmd: {
        TI: "demo_c28.cmd",
    },
    compilerBuildOptions: {
        TI: "",
    },
    linkerBuildOptions: {
        TI: "",
    },
    peripherals: ["Demo"]
};

/* TMDXDOCKH52C1 C28 */
var TMDXDOCKH52C1_C28 =
{
    name: "TMDXDOCKH52C1_C28",
    trexName: "TMDXDOCKH52C1 Experimenter Kit",
    tools: ["TI"],
    productGroup: "C2000",
    variant: "c28",
    filter: filterTMDXDOCKH52C1_C28,
    root: "boards/TMDXDOCKH52C1/",
    platforms: {
        TI: "ti.platforms.concertoC28:$DeviceId$",
    },
    targets: {
        TI: "ti.targets.C28_float",
    },
    fileList: [],
    linkercmd: {
        TI: "demo_c28.cmd",
    },
    compilerBuildOptions: {
        TI: "",
    },
    linkerBuildOptions: {
        TI: "",
    },
    peripherals: ["Demo"]
};

/* MSP_EXP430F5529LP */
var MSP_EXP430F5529LP =
{
    name: "MSP_EXP430F5529LP",
    trexName: "MSP-EXP430F5529 Launchpad",
    tools: ["TI", "IAR"],
    productGroup: "MSP430",
    variant: "msp430",
    filter: filterMSP_EXP430F5529LP,
    root: "boards/MSP_EXP430F5529LP/",
    type: "MSP430Ware",
    platforms: {
        TI: "ti.platforms.msp430:MSP430F5529",
        IAR: "ti.platforms.msp430:MSP430F5529",
    },
    targets: {
        TI:  "ti.targets.msp430.elf.MSP430X",
        IAR: "iar.targets.msp430.MSP430X_small",
    },
    fileList: ["Board.h", "MSP_EXP430F5529LP.c", "MSP_EXP430F5529LP.h"],
    linkercmd: {
        TI: "MSP_EXP430F5529LP.cmd",
        IAR: "lnk430f5529.xcl",
    },
    compilerBuildOptions: {
        TI: commonBld.getCompilerLinkerOptions("MSP430F5529",
            "${COM_TI_RTSC_TIRTOSMSP430_INSTALL_DIR}/products/" + MSP430WareVer).copts
            + " -DMSP430WARE -Dccs",
        TI_makefile: " -vmspx --abi=eabi " +commonBld.getCompilerLinkerOptions("MSP430F5529",
            "$(MSP430WARE_INSTALLATION_DIR)").copts + " -DMSP430WARE -Dccs"
            + " -I$(CODEGEN_INSTALLATION_DIR)/include"
            + " -I$(CODEGEN_INSTALLATION_DIR)/../../../ccs_base/msp430/include",
        IAR_makefile:" --debug --silent  -D__MSP430F5529__ -DMSP430WARE"
            + " -I$(MSP430WARE_INSTALLATION_DIR)/driverlib/MSP430F5xx_6xx"
            + " --diag_suppress=Pa050,Go005 --dlib_config="
            + "\"$(CODEGEN_INSTALLATION_DIR)/lib/dlib/dl430xsfn.h\""
            + " -I\"$(CODEGEN_INSTALLATION_DIR)/inc\"",
    },
    linkerBuildOptions: {
        TI: commonBld.getCompilerLinkerOptions("MSP430F5529",
            "${COM_TI_RTSC_TIRTOSMSP430_INSTALL_DIR}/products/"
            + MSP430WareVer).lIncludeLibPath + " -x",
        TI_makefile: commonBld.getCompilerLinkerOptions("MSP430F5529",
            "$(MSP430WARE_INSTALLATION_DIR)").lIncludeLibPath
            + " -i$(CODEGEN_INSTALLATION_DIR)/../../../ccs_base/msp430/include"
            + " -i$(CODEGEN_INSTALLATION_DIR)/lib --reread_libs"
            + " -m$(NAME).map MSP_EXP430F5529LP.cmd -llibc.a -x ",
        IAR_makefile: " -S -D_STACK_SIZE=400 -D_DATA16_HEAP_SIZE=0 -D_DATA20_HEAP_SIZE=0"
            + " -f lnk430f5529.xcl -s __program_start -C"
            + " $(MSP430WARE_INSTALLATION_DIR)/driverlib/iar-MSP430F5529/"
            + "iar-MSP430F5529.r43 -C \"$(CODEGEN_INSTALLATION_DIR)/lib/"
            + "dlib/dl430xsfn.r43\" -rt -e_PrintfSmall=_Printf"
            + " -e_ScanfSmall=_Scanf -xens -l $(NAME).map",
    },
    compilerIncludes: {
        IAR: "-DMSP430WARE -I$(MSP430WARE_INSTALLATION_DIR)/driverlib/MSP430F5xx_6xx ",
    },
    linkerIncludes: {
        IAR: " $(MSP430WARE_INSTALLATION_DIR)/driverlib/iar-MSP430F5529/iar-MSP430F5529.r43 ",
    },
    peripherals: ["FatFs", "GPIO", "I2C", "UART", "USB", "Watchdog", "WiFi"]
};

var MSP_EXP430F5529 =
{
    name: "MSP_EXP430F5529",
    trexName: "MSP-EXP430F5529 Experimenter Board",
    tools: ["TI", "IAR"],
    productGroup: "MSP430",
    variant: "msp430",
    filter: filterMSP_EXP430F5529,
    root: "boards/MSP_EXP430F5529/",
    type: "MSP430Ware",
    platforms: {
        TI: "ti.platforms.msp430:MSP430F5529",
        IAR: "ti.platforms.msp430:MSP430F5529",
    },
    targets: {
        TI:  "ti.targets.msp430.elf.MSP430X",
        IAR: "iar.targets.msp430.MSP430X_small",
    },
    fileList: ["Board.h", "MSP_EXP430F5529.c", "MSP_EXP430F5529.h"],
    linkercmd: {
        TI: "MSP_EXP430F5529.cmd",
        IAR: "lnk430f5529.xcl",
    },
    compilerBuildOptions: {
        TI: commonBld.getCompilerLinkerOptions("MSP430F5529",
            "${COM_TI_RTSC_TIRTOSMSP430_INSTALL_DIR}/products/" + MSP430WareVer).copts
            + " -DMSP430WARE -Dccs "
            + " -I${COM_TI_RTSC_TIRTOSMSP430_INSTALL_DIR}/products/" + MSP430WareVer + "/grlib/grlib ",
        TI_makefile: " -vmspx --abi=eabi " +commonBld.getCompilerLinkerOptions("MSP430F5529",
            "$(MSP430WARE_INSTALLATION_DIR)").copts + " -DMSP430WARE -Dccs"
            + " -I$(MSP430WARE_INSTALLATION_DIR)/grlib/grlib "
            + " -I$(CODEGEN_INSTALLATION_DIR)/include"
            + " -I$(CODEGEN_INSTALLATION_DIR)/../../../ccs_base/msp430/include",
        IAR_makefile:" --debug --silent  -D__MSP430F5529__ -DMSP430WARE"
            + " -I$(MSP430WARE_INSTALLATION_DIR)/driverlib/MSP430F5xx_6xx"
            + " -I$(MSP430WARE_INSTALLATION_DIR)/grlib/grlib "
            + " --diag_suppress=Pa050,Go005 --dlib_config="
            + "\"$(CODEGEN_INSTALLATION_DIR)/lib/dlib/dl430xsfn.h\""
            + " -I\"$(CODEGEN_INSTALLATION_DIR)/inc\"",
    },
    linkerBuildOptions: {
        TI: commonBld.getCompilerLinkerOptions("MSP430F5529",
            "${COM_TI_RTSC_TIRTOSMSP430_INSTALL_DIR}/products/"
            + MSP430WareVer).lIncludeLibPath + " -x",
        TI_makefile: commonBld.getCompilerLinkerOptions("MSP430F5529",
            "$(MSP430WARE_INSTALLATION_DIR)").lIncludeLibPath
            + " -i$(CODEGEN_INSTALLATION_DIR)/../../../ccs_base/msp430/include"
            + " -i$(CODEGEN_INSTALLATION_DIR)/lib --reread_libs --rom_model"
            + " -m$(NAME).map MSP_EXP430F5529.cmd -llibc.a -x ",
        IAR_makefile: " -S -D_STACK_SIZE=400 -D_DATA16_HEAP_SIZE=0 -D_DATA20_HEAP_SIZE=0"
            + " -f lnk430f5529.xcl -s __program_start -C"
            + " $(MSP430WARE_INSTALLATION_DIR)/driverlib/iar-MSP430F5529/"
            + "iar-MSP430F5529.r43 -C \"$(CODEGEN_INSTALLATION_DIR)/lib/"
            + "dlib/dl430xsfn.r43\" -rt -e_PrintfSmall=_Printf"
            + " -e_ScanfSmall=_Scanf -xens -l $(NAME).map",
    },
    compilerIncludes: {
        IAR: "-DMSP430WARE -I$(MSP430WARE_INSTALLATION_DIR)/driverlib/MSP430F5xx_6xx ",
    },
    linkerIncludes: {
        IAR: " $(MSP430WARE_INSTALLATION_DIR)/driverlib/iar-MSP430F5529/iar-MSP430F5529.r43 ",
    },
    peripherals: ["Demo", "FatFs", "GPIO", "I2C", "UART", "USB", "Watchdog", "WiFi"]
};

var MSP_EXP430FR5969LP =
{
    name: "MSP_EXP430FR5969LP",
    trexName: "MSP-EXP430FR5969 Launchpad",
    tools: ["TI", "IAR"],
    productGroup: "MSP430",
    variant: "msp430",
    filter: filterMSP_EXP430FR5969LP,
    root: "boards/MSP_EXP430FR5969LP/",
    type: "MSP430Ware",
    platforms: {
        TI: "ti.platforms.msp430:MSP430FR5969",
        IAR: "ti.platforms.msp430:MSP430FR5969",
    },
    targets: {
        TI:  "ti.targets.msp430.elf.MSP430X",
        IAR: "iar.targets.msp430.MSP430X_small",
    },
    fileList: ["Board.h", "MSP_EXP430FR5969LP.c", "MSP_EXP430FR5969LP.h"],
    linkercmd: {
        TI: "MSP_EXP430FR5969LP.cmd",
        IAR: "lnk430fr5969.xcl",
    },
    compilerBuildOptions: {
        TI: commonBld.getCompilerLinkerOptions("MSP430FR5969",
            "${COM_TI_RTSC_TIRTOSMSP430_INSTALL_DIR}/products/" + MSP430WareVer).copts
            + " -I${COM_TI_RTSC_TIRTOSMSP430_INSTALL_DIR}/products/" + MSP430WareVer + "/grlib/grlib "
            + " -DMSP430WARE -Dccs ",
        TI_makefile: " -vmspx --abi=eabi " +
            commonBld.getCompilerLinkerOptions("MSP430FR5969",
            "$(MSP430WARE_INSTALLATION_DIR)").copts + " -DMSP430WARE -Dccs"
            + " -I$(MSP430WARE_INSTALLATION_DIR)/grlib/grlib "
            + " -I$(CODEGEN_INSTALLATION_DIR)/include"
            + " -I$(CODEGEN_INSTALLATION_DIR)/../../../ccs_base/msp430/include",
        IAR_makefile:" --debug --silent  -D__MSP430FR5969__ -DMSP430WARE"
            + " -I$(MSP430WARE_INSTALLATION_DIR)/driverlib/MSP430FR5xx_6xx"
            + " -I$(MSP430WARE_INSTALLATION_DIR)/grlib/grlib "
            + " --diag_suppress=Pa050,Go005 --dlib_config="
            + "\"$(CODEGEN_INSTALLATION_DIR)/lib/dlib/dl430xsfn.h\""
            + " -I\"$(CODEGEN_INSTALLATION_DIR)/inc\"",
    },
    linkerBuildOptions: {
        TI: commonBld.getCompilerLinkerOptions("MSP430FR5969",
            "${COM_TI_RTSC_TIRTOSMSP430_INSTALL_DIR}/products/"
            + MSP430WareVer).lIncludeLibPath + " -x",
        TI_makefile: commonBld.getCompilerLinkerOptions("MSP430FR5969",
            "$(MSP430WARE_INSTALLATION_DIR)").lIncludeLibPath
            + " -i$(CODEGEN_INSTALLATION_DIR)/../../../ccs_base/msp430/include"
            + " -i$(CODEGEN_INSTALLATION_DIR)/lib --reread_libs --rom_model"
            + " -m$(NAME).map MSP_EXP430FR5969LP.cmd -llibc.a -x ",
        IAR_makefile: " -S -D_STACK_SIZE=400 -D_DATA16_HEAP_SIZE=0 -D_DATA20_HEAP_SIZE=0"
            + " -f lnk430fr5969.xcl -s __program_start -C"
            + " $(MSP430WARE_INSTALLATION_DIR)/driverlib/iar-MSP430FR5969/"
            + "iar-MSP430FR5969.r43 -C \"$(CODEGEN_INSTALLATION_DIR)/lib/"
            + "dlib/dl430xsfn.r43\" -rt -e_PrintfSmall=_Printf"
            + " -e_ScanfSmall=_Scanf -xens -l $(NAME).map",
    },
    compilerIncludes: {
        IAR: "-DMSP430WARE -I$(MSP430WARE_INSTALLATION_DIR)/driverlib/MSP430FR5xx_6xx ",
    },
    linkerIncludes: {
        IAR: " $(MSP430WARE_INSTALLATION_DIR)/driverlib/iar-MSP430FR5969/iar-MSP430FR5969.r43 ",
    },
    peripherals: ["Demo", "FatFs", "GPIO", "I2C", "UART", "Watchdog", "WiFi"]
};

var allBoards = [
    TMDXDOCK28M36_M3,
    TMDXDOCKH52C1_M3,
    TMDXDOCK28M36_C28,
    TMDXDOCKH52C1_C28,
    EKS_LM4F232,
    DK_TM4C123G,
    DK_TM4C129X,
    EK_TM4C1294XL,
    EK_LM4F120XL,
    EK_TM4C123GXL,
    CC2650DK,
    CC2650STK_BLE,
    CC3200_LP,
    MSP_EXP430F5529LP,
    MSP_EXP430F5529,
    MSP_EXP430FR5969LP
];

var examplesgenBoards = [
    TMDXDOCK28M36_M3,
    TMDXDOCKH52C1_M3,
    EKS_LM4F232,
    DK_TM4C123G,
    DK_TM4C129X,
    EK_TM4C1294XL,
    EK_LM4F120XL,
    EK_TM4C123GXL,
    CC2650DK,
    CC2650STK_BLE,
    CC3200_LP,
    MSP_EXP430F5529LP,
    MSP_EXP430F5529,
    MSP_EXP430FR5969LP
];

function supportsTool(Board, tool) {
    for (var i = 0; i < Board.tools.length; i++) {
        if (Board.tools[i] == tool) {
            return true;
        }
    }
    return false;
}

function inProductGroup(Board, productGroup) {
    if (Board.productGroup == productGroup) {
        return true;
    }
    return false;

}
