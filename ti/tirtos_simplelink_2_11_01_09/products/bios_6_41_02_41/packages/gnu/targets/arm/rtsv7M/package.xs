/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */
/*
 *  ======== Package.getLibs ========
 */
function getLibs(prog)
{
    var libs = "lib/boot.a" + Program.build.target.suffix + ";lib/syscalls.a"
        + Program.build.target.suffix;

    if (prog.targetModules().length > 0 && this.Settings.bootOnly == false) {
        libs = "lib/" + this.$name + ".a" + Program.build.target.suffix + ";"
            + libs;
    }
    return (libs);
}
/*
 *  @(#) gnu.targets.arm.rtsv7M; 1, 0, 0,121; 1-21-2015 20:20:04; /db/ztree/library/trees/xdctargets/xdctargets-h42x/src/ xlibrary

 */

