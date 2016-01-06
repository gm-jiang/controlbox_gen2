/*
 *  Copyright 2014 by Texas Instruments Incorporated.
 *
 */

package xdc.tools.platformWizard;

/*!
 *  ======== Main ========
 * @_nodoc
 */
metaonly module Main inherits xdc.tools.ICmd {

    override config String usage[] = [
        ' -r <repository for platform package>',
        ' -x <XML schema file>',
                '<platform package name>'
    ];

instance:
        
    @CommandOption("r")
    config String repositoryPath = null;
        
    @CommandOption("x")
    config String schemaFile = null;
        
    override Any run(xdc.tools.Cmdr.Instance cmdr, String args[]);
}
/*
 *  @(#) xdc.tools.platformWizard; 1,0,0,162; 10-15-2014 16:33:43; /db/ztree/library/trees/xdctools/xdctools-f57x/src/
 */

