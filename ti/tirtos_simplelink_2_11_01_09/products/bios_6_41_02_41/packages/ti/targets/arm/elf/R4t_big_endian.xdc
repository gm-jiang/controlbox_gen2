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

/*!
 *  ======== R4t_big_endian.xdc ========
 *  Cortex R4 big endian thumb2 (ELF)
 */
metaonly module R4t_big_endian inherits ti.targets.arm.elf.IR4_big_endian {
    override readonly config string name        = "R4t_big_endian";
    override readonly config string suffix      = "er4te";
    override readonly config string rts         = "ti.targets.arm.rtsarm";

    override readonly config xdc.bld.ITarget.Model model = {
        endian: "big",
        codeModel: "thumb2",
        shortEnums: true
    };

    override readonly config xdc.bld.ITarget2.Command cc = {
        cmd:  "armcl -c",
        opts: "-mt --endian=big -mv7R4 --abi=eabi"
    };

    override readonly config xdc.bld.ITarget2.Command asm = {
        cmd:  "armcl -c",
        opts: "-mt --endian=big -mv7R4 --abi=eabi"
    };
}
/*
 *  @(#) ti.targets.arm.elf; 1, 0, 0,500; 1-21-2015 19:57:37; /db/ztree/library/trees/xdctargets/xdctargets-h42x/src/ xlibrary

 */

