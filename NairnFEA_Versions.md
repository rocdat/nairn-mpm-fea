# Introduction #

This page gives brief history of the main changes in various version of the `NairnFEA` code engine.

# Version in the Code #

The version number is coded in the constructor of the `NairnFEA.cpp` class:

```
	version=2;				// NairnFEA version number
	subversion=7;				// subversion number
	buildnumber=0;				// build number
```

# Version History #

NairnFEA was first imported to `GoogleCode.com` as version 2.7.0. The versions currently in this project are as follows:

  * Current main trunk
    * Working on NairnFEA 4.0.0

  * Release-5.0 (9 Feb 2014): On Jan 14, 2014, an OpenMP branch replaced the main trunk for this release. That branch was started on April 2, 2013 to make parallel code. The FEA parallelization was done in August.
    * Working on NairnFEA 4.0.0
    * Aug 28: FEA uses parallel in matrix inversion.
    * Aug 30: Fixed FEA bug when using three stress to apply quadratic variation in stress.

  * Prior trunk version of release 5.0 (this  version was deleted on Jan 14, 2014 when the OpenMP branch replaced the main trunk)
    * Working on NairnFEA 3.0.0

  * Release-4.0 (9 JAN 2013)
    * Has NairnFEA 3.0.0
    * Allows `Body` and `Hole` commands to set elements with no material using shape commands.
    * A new `-w` option to map relative files relative to the working directory rather than the input file.

  * Release-3.0 (25 JAN 2012)
    * Has NairnFEA 2.9.0
    * Converted to using Xerces 3.1.1 and must link to 3.x or newer because new Xerces is not compatible with Xerces 2.8 or older.
    * Converted all `longs` to `ints` to avoid any potential machine-dependent issues in 64 bit compiles (NairnFEA can compile as 32 bit or 64 bit, and must match Xerces library bits).
    * Added `Lagrange2D` element for 9 node quadrilateral (9th node in the center). It is integrated using 9 Gaussian points, because using less gave singular matrix in some simple problems.
    * Added `Entity` command.
    * Enhanced `BMP` command to allow specifying distance per pixel and to superpose multiple images.
    * Commands that specify materials with `mat` attribute can now use `matname` instead to specify materials by name. Using `mat` and `matname` options in the same input file should be avoided.

  * release-2.0 (25 JUL 2010)
    * Has NairnFEA 2.7.1
    * Added `<DevelFlag>` option in the `<Header>` for use in development coding.

  * release-1.0 (30 DEC 2009)
    * Has NairnFEA 2.7.0
    * Updated code to compile in GNU 4.3.1
    * Convert BMP file and angle file to fill elements in a mesh and remove unused elements and nodes
    * Requence finds connectivity issues and should be on when BMP is used

# Archival Version History #

Prior to being in `GoogleCode.com`, NairnMPM was in a local repository. That repository is available if needed. The prior versions are:

  * `NairnCode2_0_0` (4 NOV 2008)
    * Has NairnFEA 2.6.0
    * Fixed bug in new BMP commands when thermal stresses were used
    * Add y and z (axisymmetric) direction peridocity

  * `NairnCode1_5_0` (14 MAR 2008)
    * Has NairnFEA 2.5.0
    * Add methods from NairnMPM to interpret BMP files, but not yet used in FEA commands

  * `NairnCode1_4_0` (25 OCT 2007)
    * Has NairnFEA 2.4.0
    * User functions are now allowed to set properties as a function or x and y. They have been implemented in Temperature and Area (for angle) commands and in DisBC and LoadBC boundary conditions
    * Some material class reorganization such as printing to output window
    * Periodic in both x and y
    * New FEABoundaryCondition class as base class for all boundary conditions
    * CrackTip command to setup quarter point elements

  * `NairnCode1_3_0` (19 FEB 2007)
    * Has NairnFEA 2.3.0
    * No changes

  * `NairnCode1_2_0` (8 FEB 2007)
    * Has NairnFEA 2.2.0
    * Periodic BCs appear to be done, but for x direction only

  * `NairnCode1_1_0` (18 JAN 2007)
    * Has NairnFEA 2.1.0
    * Begnning of periodic boundary conditions, but not documented yet
    * Bug in anisotropic CTE with rotated material fixed

  * `NairnCode1_0_0` (22 DEC 2006)
    * Has NairnFEA 2.0.0
    * Code reorganized and NairnFEA and NairnMPM combined in single NairnCode

# Additional NairnFEA History #

The following versions are from a prior repository and are no longer available:

  * NairnFEA1\_6\_0 (14 FEB 2006) - based on NairnMPM5\_1\_0
    * Imperfect interfaces
    * Bug in 4-node AS with stress BC fixed
    * Code reoroganized. Main calc, reading, and archiving to objects

  * NairnFEA1\_5\_1 (15 JUL 2005) - based on NairnMPM5\_0\_2
    * FEA with keypoints, paths, and areas and BCs with them too
    * Resquence nodes
    * CST elements
    * Anisotropic Materials
    * Prints version number in output
    * Nearly done except interface elements, 1/4 pt elements, and temperature expressions

  * NairnFEA1\_0\_1 (15 JUL 2005) - unknown NairnMPM basis
    * Basic building blocks for keypoints, paths, and areas, but not use yet
    * Based on NairnMPM5\_0\_0