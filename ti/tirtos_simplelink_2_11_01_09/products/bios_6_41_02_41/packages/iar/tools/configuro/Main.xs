/* 
 *  Copyright (c) 2013 Texas Instruments and others.
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
 *  ======== Main.xs ========
 *  Main entry point
 */
/*
 *  ======== File ========
 *  Used for performing file operations
 */
var File = xdc.useModule("xdc.services.io.File");

/*
 *  ======== opts ========
 *  command line options
 */
var opts = {};

/*
 *  ======== run ========
 *  Main function, executed from the command line.
 */
function run(cmdr, args)
{
    /* put config parameters in a local copy so mappings() can add to them */
    for (var p in this) {
        opts[p] = this[p];
    }

    /* check if all the required options are provided */
    if (opts["compileOptions"] == null || opts["linkOptions"] == null
        || opts["rootDir"] == null || opts["device"] == null) {
        cmdr.usage();
        cmdr.error("One or more required options were not provided");
    }

    /* convert Windows paths to Linux paths */
    for (var p in this) {
        opts[p] = opts[p].replace(/\\/g, '/');
    }

    /* find the config file */
    var cfg = "";
    if (args.length > 0) {
        cfg = args[0].replace(/\\/g, '/');
    }
    else {
        cfg = findCfg(cmdr);
    }
    print("\nUsing RTSC configuration file: " + cfg + "...\n");

    /* If 'cfg' doesn't contain any '/', it's a file in the current directory
     * so we add './' to make the computation of 'output' below work.
     */
    if (cfg.lastIndexOf('/') == -1) {
        cfg = "./" + cfg;
    }

    /* check the output directory */
    if (opts["output"] == "") {
        opts["output"] = cfg.substring(0, cfg.lastIndexOf('/')) + "/configPkg";
    }

    /* fetch the target/platform/profile */
    mappings(cmdr);

    /* get the include paths and symbol definitions */
    var cOpts = getCompileOpts();

    /* check if we need to clean the generated source libs */
    if (!(File.exists(opts["output"] +"/package.mak"))) {
        var mklibs = cfg.substring(0, cfg.lastIndexOf('/') + 1) 
                     + "src/makefile.libs";

        if (File.exists(mklibs)) {
            print("\nA previous project clean has been detected. Cleaning"
                  + " the generated source libraries before building...\n");
            cleanLibs(cmdr, mklibs);
        }
    } 

    /* execute xdc.tools.configuro */
    var configuro = xdc.useModule('xdc.tools.configuro.Main');
    configuro.exec(["-o",  opts["output"], "-t", opts["t"], "-p",  opts["p"],
        "-r", opts["profile"], "-c", opts["rootDir"], "--compileOptions",
        cOpts, "--linkOptions", opts["linkOptions"], cfg]);
}

/*
 *  ======== cleanLibs ========
 *  Runs clean on the supplied makefile
 */
function cleanLibs(cmdr, makefile)
{
    var genDir = makefile.substring(0, makefile.lastIndexOf('/'));

    /* try to use $XDCROOT/gmake, otherwise hope it's along user's path */
    var gmake = environment["xdc.root"] + "/gmake";
    if (!File.exists(gmake)) {
        gmake = gmake + ".exe";
    }
    if (!File.exists(gmake)) {
        cmdr.error("can't find gmake in XDCROOT ("
            + environment["xdc.root"]
            + "), trying gmake along your path ...", this);
        gmake = "gmake";
    }

    var buildCmd = gmake + ' -f ' + makefile + ' GEN_SRC_DIR=' + genDir
                   + ' clean';

    var status = {};
    var result = xdc.exec(buildCmd, {
        envs: ["MAKELEVEL=0"],
        useEnv: true,
        merge: false,
        outStream: java.lang.System.out,
        errStream: java.lang.System.err,
        }, status);
}

/*
 *  ======== findCfg ========
 *  Searches  for config file in the directory provided
 */
function findCfg(cmdr)
{
    var cfg = "";
    var projDir = "";

    try {
        projDir = opts["projFile"];
        projDir = projDir.substring(0, projDir.lastIndexOf('/'));
        var ewp = File.open(opts["projFile"], "r");

        var line = null;
        while ((line = ewp.readLine()) != null) {
            if (line.match(/\<name\>.*\.cfg\<\/name\>/)) {
                /* Get filename from "<name>$PROJ_DIR$\app.cfg</name>" */
                cfg = line.substring(line.lastIndexOf('$') + 2, line.lastIndexOf('<'));

                /* Has it been excluded from Build? */
                if (((line = ewp.readLine()) != null) && line.match(/excluded/)) {
                    var config = /Release/;
                    if (opts["compileOptions"].match(/--debug/)) {
                        config = /Debug/;
                    }

                    if (((line = ewp.readLine()) != null) && line.match(config)) {
                        cfg = "";
                        continue;
                    }
                }
                break;
            }
        }

        if (cfg == "") {
            throw(new Error(".cfg file not found"));
        }
    }
    catch (e) {
        cmdr.error("RTSC configuration file (.cfg) was not found");
    }

    return (projDir + "/" + cfg);
}

/*
 *  ======== getCompileOpts ========
 *  Get the compiler include path and symbol definitions
 */
function getCompileOpts()
{
    var cOpts = " ";
    var inQuotes = false;
    var compOpts = opts["compileOptions"];

    for (var i = 0; i < compOpts.length; i++) {
        /* Will process only the options */
        if (compOpts[i] == '-') {
            if (i != 0) {
                if (compOpts[i - 1] != ' ') {
                    continue;
                }
            }
 
            i++;
            if (!(i < compOpts.length)) {
                /* break for */
                break;
            }

            /* Is it an include option or a symbol definition? */
            if (compOpts[i] == 'I' || compOpts[i] == 'D') {
                var opt = " -";

                do {
                    opt += compOpts[i];
                    i++;
                    if (!(i < compOpts.length)) {
                        /* break while */
                        break;
                    }

                    /* Loop whitespace or tabs */
                } while (compOpts[i] == ' ' || compOpts[i] == '\t');

                if (!(i < compOpts.length)) {
                    /* break for */
                    break;
                }

                /* Quoted strings have to be handled differently */
                if (compOpts[i] == '"') {
                    inQuotes = true;
                    opt += compOpts[i];
                    i++;
                }

                for (;i < compOpts.length; i++) {
                    opt += compOpts[i];
                    if ((inQuotes && (compOpts[i] == '"'))
                        || (!inQuotes && (compOpts[i] == ' '))) {

                        inQuotes = false;
                        /* break inner for */
                        break;
                    }
                }
                cOpts += opt + " ";
            }
        }
    }

    return (cOpts);
}

/*
 *  ======== mappings ========
 *  Maps compiler options to target/platform/profile
 */
function mappings(cmdr)
{
    function findTarget(file)
    {
        var tjs = new Packages.xdc.services.mapping.TargetMapping();
        tjs.readFile(file);
        var tmap = new Packages.java.util.HashMap();
        tmap.put("device", opts["device"]);
        tmap.put("CompilerBuildOptions", opts["compileOptions"]);
        var targ = tjs.getTarget(tmap);
        if (targ != null) {
            targ = targ.replace(".elf", "") + "";
        }
        return (targ);
    }

    function findPlatform(file)
    {
        var pjs = new Packages.xdc.services.mapping.PlatformMapping();
        pjs.readFile(file);
        var pmap = new Packages.java.util.HashMap();
        pmap.put("device", opts["device"]);
        pmap.put("target", opts["t"]);
        var platArray = pjs.getPlatforms(pmap).toArray();
        if (platArray.length > 0) {
            return (platArray[0] + "");
        }
        return (null);
    }

    var xdcpath = environment['xdc.path'];
    var dirArray = xdcpath.split(";");
    var tjson;
    var pjson;
    var foundt = false;
    var foundp = false;

    xdc.loadPackage("xdc.services.mapping");
    /* The JSON files listing targets and platforms are currently in etc/
     * directories of the RTSC products. In the future they should be on the
     * package path. The current search looks in both places, but after
     * ECL432052 is fixed, 'etc' directories will be removed from the search.
     */
    var searchPath = [];
    for (var i = 0; i < dirArray.length; i++) {
        if (dirArray[i] == "") {
            continue;
        }
        searchPath.push(dirArray[i] + "/../etc");
        searchPath.push(dirArray[i]);
    }
    for (var i = 0; i < searchPath.length; i++) {
        var dir = searchPath[i];
        fileDir = new java.io.File(dir);
        if (!fileDir.exists()) {
            continue;
        }
        var fileArray = fileDir.list();
        for (var j = 0; j < fileArray.length; j++) {
            var file = new java.io.File(fileArray[j]);
            if (!file.isDirectory()
                && (file.getName() + "").match(/.*target.*json$/)) {
                tjson = dir + "/" + file;
                opts["t"] = findTarget(tjson);
                if (opts["t"] != null) {
                    break;
                }
            }
        }
        if (opts["t"] != null) {
            break;
        }
    }
    if (tjson == undefined) {
        cmdr.error("Cannot find a JSON file with RTSC target mappings.");
    }
    if (opts["t"] == null) {
        cmdr.error("The compiler options '" + opts["compileOptions"]
            + "' specify an architecture which is not supported.");
    }

    for (var i = 0; i < searchPath.length; i++) {
        var dir = searchPath[i];
        fileDir = new java.io.File(dir);
        if (!fileDir.exists()) {
            continue;
        }
        var fileArray = fileDir.list();
        for (var j = 0; j < fileArray.length; j++) {
            var file = new java.io.File(fileArray[j]);
            if (!file.isDirectory()
                && (file.getName() + "").match(/.*platform.*json$/)) {
                pjson = dir + "/" + file;
                opts["p"] = findPlatform(pjson);
                if (opts["p"] != null) {
                    break;
                }
            }
        }
        if (opts["p"] != null) {
            break;
        }
    }
    if (pjson == undefined) {
        cmdr.error("Cannot find a JSON file with RTSC platform mappings.");
    }
    if (opts["p"] == null) {
        cmdr.error("There is no platform for the RTSC target '"
            + opts["t"] + "'.");
    }

    /* profile */
    if (opts["profile"] == "") {
        if (opts["compileOptions"].match(/--debug/)) {
            opts["profile"] = "debug";
        }
        else {
            opts["profile"] = "release";
        }
    }

    /* Add _full to profile to link full library configuration */
    if (opts["compileOptions"].match(/dl430xsff/)
        || opts["compileOptions"].match(/DLib_Config_Full.h/)) {
        opts["profile"] += "_full";
    }
}
/*
 *  @(#) iar.tools.configuro; 1, 0, 0,34; 10-15-2014 16:32:45; /db/ztree/library/trees/xdctools/xdctools-f57x/src/
 */
