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
 *  ======== package.xs ========
 */

/*
 *  ======== getLibs ========
 *  This package does not build any libraries.
 */
function getLibs() {
    var WiFi = xdc.module("ti.drivers.WiFi");
    var TIRTOS = xdc.module("ti.tirtos.TIRTOS");

    var instrumentedString = "";
    var retString = "";
    var driverGroup = "";
    var wiFiHostDriverType = "";

    if (TIRTOS.libType == TIRTOS.LibType_Instrumented) {
        instrumentedString = "_instrumented"
    }

    if (Program.cpu.deviceName.match(/F28M3.*/)) {
        driverGroup = "_mware" + instrumentedString + ".a" + Program.build.target.suffix + ";";
        retString += "../drivers/lib/drivers" + driverGroup;
    }
    else if (Program.cpu.deviceName.match(/LM4F.*/) ||
             Program.cpu.deviceName.match(/TM4E.*/) ||
             Program.cpu.deviceName.match(/TM4C.*/)) {
        driverGroup = "_tivaware" + instrumentedString + ".a" + Program.build.target.suffix + ";";
        retString += "../drivers/lib/drivers" + driverGroup;
    }
    else if (Program.cpu.deviceName.match(/CC32.*/)) {
        driverGroup = "_ccware" + instrumentedString + ".a" + Program.build.target.suffix + ";";
        retString += "../drivers/lib/drivers" + driverGroup;
    }
    else if (Program.cpu.deviceName.match(/CC26.*/)) {
        driverGroup = "_cc26xxware" + instrumentedString + ".a" + Program.build.target.suffix + ";";
        retString += "../drivers/lib/drivers" + driverGroup;
    }
    else if (Program.build.target.suffix == "e430X") {
        driverGroup = "_" + Program.cpu.deviceName.match(/MSP430.*/) + instrumentedString + ".ae430X;";
        retString += "../drivers/lib/drivers" + driverGroup;
    }
    else if (Program.build.target.suffix == "r430XS") {
        driverGroup = "_" + Program.cpu.deviceName.match(/MSP430.*/) + instrumentedString + ".ar430XS;";
        retString += "../drivers/lib/drivers" + driverGroup;
    }
    else {
        throw ("Driver not found for this device " + Program.cpu.deviceName +
               " and target " + Program.build.target.suffix);
    }

    /* Add all the WiFi driver to retString */
    if (WiFi.$used == true) {
        retString += "../drivers/lib/";
        switch (WiFi.libType) {
            case WiFi.LibType_Instrumented:
                instrumentedString += "_instrumented"
                break;
            case WiFi.LibType_NonInstrumented:
                instrumentedString += ""
                break;
        }

        if (Program.cpu.deviceName.match(/LM4F.*/) ||
             Program.cpu.deviceName.match(/TM4E.*/) ||
             Program.cpu.deviceName.match(/TM4C.*/)) {
            driverGroup = "_tivaware" + instrumentedString + ".a" + Program.build.target.suffix + ";";
        }
        else if (Program.build.target.suffix == "e430X") {
            driverGroup = "_" + Program.cpu.deviceName.match(/MSP430.*/) + instrumentedString + ".ae430X;";
        }
        else if (Program.build.target.suffix == "r430XS") {
            driverGroup = "_" + Program.cpu.deviceName.match(/MSP430.*/) + instrumentedString + ".ar430XS;";
        }

        /* CC3000 used */
        if (WiFi.deviceType == WiFi.DeviceType_SimpleLink_CC3000) {
            switch (WiFi.hdType) {
                case WiFi.HDType_SingleThread:
                    wiFiHostDriverType += "_singlethread"
                    break;
                case WiFi.HDType_MultiThread:
                    wiFiHostDriverType += "_multithread"
                    break;
            }
            retString += "wifi" + wiFiHostDriverType + driverGroup;
        }
        /* CC3100 used */
        else {
            retString += "wifi_cc3100" + driverGroup;
        }
    }

    return (retString);
};
