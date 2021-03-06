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
 *  ======== ExampleList.xs ========
 */

var productGroup = environment["productGroup"];
var tirtosSupport = environment["tirtosSupport"];
var rootString;

if (tirtosSupport == "true") {
    rootString = "examples.root_" + productGroup + ".kernel";
}
else {
    rootString = "ti.sysbios.examples.root";
}

var examplesList = [
    {
        groupsTI: [rootString + ".targetsTI"],
        groupsGNU: [rootString + ".targetsGNU"],
        title: "Minimal",
        name: "minimal",
        description: "This example has a fairly minimal .cfg which is set up for a static application where all objects are defined statically (via configuration tool and/or target structures).  Dynamic memory allocation has been disabled. The .cfg file creates a single task which has a couple of print statements and a Task_sleep() call.",
        root: "./generic/minimal/",
        cFile: "main.c",
        cfgFile: "app.cfg",
        isHybrid: true,
        options: "NPW,TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI"],
        groupsGNU: [rootString + ".targetsGNU"],
        title: "Typical",
        name: "typical",
        description: "This example has a .cfg populated with a typical set of options and parameters.  This .cfg file is a good starting point for many applications.  Dynamic memory allocation and runtime create of is supported.  Unlike the 'Minimal' example, the single task is created at runtime using the Task_create() API.",
        root: "./generic/typical/",
        cFile: "main.c",
        cfgFile: "app.cfg",
        isHybrid: true,
        options: "NPW,TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI"],
        groupsGNU: [rootString + ".targetsGNU"],
        name: "typicalSeparate",
        title: "Typical (with separate config project)",
        description: "Same as the 'Typical' example except that the configuration project is a separate project from the app project.  The benefit of having a separate config project is that several applications can use the same configuration.  This helps save on build times and allows a team to share a common configuratin set up by a system integrator.",
        root: "./generic/typical/",
        cFile: "main.c",
        cfgFile: "app.cfg",
        isHybrid: false,
        options: "NPW",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "C++ Example (bigtime)",
        name: "bigtime",
        description: "In this program, C++ is used to create a real-time clock/calendar.",
        root: "./generic/bigtime/",
        cFile: "bigtime.cpp",
        cfgFile: "bigtime.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Clock Example",
        name: "clock",
        description: "The clock example shows how to use the ti.sysbios.knl.Clock module to create one-shot and periodic Clock Instances. Clock Instances are essentially functions that run after a certain number of Clock ticks.",
        root: "./generic/clock/",
        cFile: "clock.c",
        cfgFile: "clock.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Error Example",
        name: "error",
        description: "This example shows how to use Error_Blocks to catch runtime errors. An Error_Block is passed to Task_create() and then checked for create failure. When no Error_Block is passed, the application will terminate when an error occurs. The error.cfg file shows how to plug an error hook.",
        root: "./generic/error/",
        cFile: "error.c",
        cfgFile: "error.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Event Example",
        name: "event",
        description: "The event example shows how to use the ti.sysbios.knl.Event module. The ti.sysbios.knl.Event module solves the 'Wait on Multiple' problem. In this example a reader task waits on several events.",
        buildProfile: "release",
        root: "./generic/event/",
        cFile: "event.c",
        cfgFile: "event.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Hello Example",
        name: "hello",
        description: "The hello example serves as a basic sanity check program for SYS/BIOS. It demonstrates how to print the string 'hello world' to stdout.",
        buildProfile: "release",
        root: "./generic/hello/",
        cFile: "hello.c",
        cfgFile: "hello.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Log Example",
        name: "log",
        description: "This module shows how to use Log_info(), Log_error() and Log_warning() in a simple application. It shows how to enable USER1 logs for the Task module in the cfg file.",
        buildProfile: "release",
        root: "./generic/log/",
        cFile: "log.c",
        cfgFile: "log.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Memory Example",
        name: "memory",
        description: "This example shows the use of xdc.runtime.Memory module and different xdc.runtime.IHeap implementations to manage memory. A system heap is created statically using ti.sysbios.heaps.HeapMem.",
        buildProfile: "release",
        root: "./generic/memory/",
        cFile: "memory.c",
        cfgFile: "memory.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Task Mutex Example",
        name: "task",
        description: "This example shows the use of two tasks and one semaphore to protect data access.",
        buildProfile: "release",
        root: "./generic/mutex/",
        cFile: "mutex.c",
        cfgFile: "mutex.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Small Example",
        name: "small",
        description: "This simple example uses the Clock module to periodically post a software interrupt (Swi), and increments counters.  The configuration disables non-essential and debug-related SYS/BIOS features to reduce the application memory footprint.",
        buildProfile: "release",
        root: "./generic/small/",
        cFile: "small.c",
        cfgFile: "small.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Static Example",
        name: "static",
        description: "The static example focuses on SYS/BIOS configuration. It shows how to use and configure various modules, create static Instances and modify Program level configuration parameters.",
        buildProfile: "release",
        root: "./generic/static/",
        cFile: "static.c",
        cfgFile: "static.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI:[rootString + ".targetsTI.genericTI"],
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Swi Example",
        name: "swi",
        description: "The swi example shows how to use the ti.sysbios.knl.Swi module. It demonstrates how the various Swi APIs work.",
        buildProfile: "release",
        root: "./generic/swi/",
        cFile: "swi.c",
        cfgFile: "swi.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsGNU:[rootString + ".targetsGNU.genericGNU"],
        title: "Semi-Hosting Example",
        name: "semihost",
        description: "This example leverages Semi-Hosting for printf IO.  The configuration disables non-essential and debug-related SYS/BIOS features to reduce the application memory footprint.",
        buildProfile: "release",
        root: "./generic/semihost/",
        cFile: "semihost.c",
        cfgFile: "semihost.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI.genericTI"],
        groupsGNU: [rootString + ".targetsGNU.genericGNU"],
        title: "Benchmark Example",
        name: "benchmark",
        description: "This example gathers and prints benchmark timing data for some representative SYS/BIOS APIs.",
        root: "ti/sysbios/benchmarks/",
        cFile: "benchloop.c",
        cfgFile: "benchloop.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI.c28"],
        title: "Idle Example",
        name: "idle",
        description: "A 28x specific example which uses an Idle function to print to standard out and a log buffer",
        buildProfile: "release",
        root: "./c28/idle/",
        cFile: "idle.c",
        cfgFile: "idle.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI.c28"],
        title: "Swi Example",
        name: "swi28",
        description: "A 28x specific example which uses an Swi function and an Idle function to print to a log buffer",
        buildProfile: "release",
        root: "./c28/swi/",
        cFile: "swi.c",
        cfgFile: "swi.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI.c28"],
        title: "Task Example",
        name: "task28",
        description: "A 28x specific example which uses an task to print to a log buffer",
        buildProfile: "release",
        root: "./c28/task/",
        cFile: "task.c",
        cfgFile: "task.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI.c28"],
        title: "PIE Interrupt Example",
        name: "pie",
        description: "A 28x specific example which shows how to handle (simulated) peripheral interrupts from the PIE",
        buildProfile: "release",
        root: "./c28/pie/",
        cFile: "pie.c",
        cfgFile: "pie.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI.msp430"],
        title: "Idle Example",
        name: "idle",
        description: "An MSP430 specific example which uses an Idle function to print to standard out and a log buffer",
        buildProfile: "release",
        root: "./msp430/idle/",
        cFile: "idle.c",
        cfgFile: "idle.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI.msp430"],
        title: "Swi Example",
        name: "swi430",
        description: "An MSP430 specific example which uses an Swi function and an Idle function to print to a log buffer",
        buildProfile: "release",
        root: "./msp430/swi/",
        cFile: "swi.c",
        cfgFile: "swi.cfg",
        isHybrid: true,
        options: "TREX",
    },
    {
        groupsTI: [rootString + ".targetsTI.msp430"],
        title: "Task Example",
        name: "task430",
        description: "An MSP430 specific example which uses an task to print to a log buffer",
        buildProfile: "release",
        root: "./msp430/task/",
        cFile: "task.c",
        cfgFile: "task.cfg",
        isHybrid: true,
        options: "TREX",
    },
];
