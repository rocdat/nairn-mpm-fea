# Introduction #

This page give s brief history of the main changes in various version of the `NairnFEAMPMViz` Java application.

# Version in the Code #

The version number is code using a static variable for the `NairnFEAMPMViz` class:

```
public static final String versionReadable="Version 3.0.0";
```

# Version History #

NairnFEAMPMViz was first imported to `GoogleCode.com` as version 3.0.0. The versions currently in this project are as follows:

  * Current main trunk
    * Working on NairnFEAMPMViz 6.1.0
    * A new scripted control option can control operation of the NairnFEAMPMViz app such as to run multiple simulations and save the results. See new help topic on the scripting language.
    * Additions to commands language
      * Added PIC option to `Damping` and added `PDamping` and `PFBDamping`
      * Added Neo-Hookean material
      * Added grid energy option to `JContour`
      * Added maximum propagations to `ArchiveTime`
    * Bug fixes in commands language
      * `Damping` and `Displacement` can take value or function
      * FEA temperature fixed
      * `@key` expression was not working, but now fixed
      * Allows `Rect` and `Oval` when in `Poly` (and terminates the `Poly`)
    * Fixes and improvements to the built-in interpretive language:
      * Better with string expressions within an argument
      * added `pi`, `tab`, and `return` as keywords
      * Fixed problem with `atan`, `asin`, and `acos` not working
      * String expression can be used for numbers (if they are a number)
      * Repeat loop with no iterations broke out of all loops, now just that omits the one with no loops
    * Option to transform particles in MPM plots had sign error on shear and is fixed (was only noticeable when high shear deformation).
    * Plotting of membrane particles (currently only in OSParticulas) transforms membrane particles for their actual size

  * Release-5.0 (9 Feb 2014): On Jan 14, 2014, the OpenMP branch replaced the main trunk of this release. That branch was to make parallel code and also to convert the Java app to fully support scripting language from the Mac app called NairnFEMPM.
    * Has NairnFEAMPMViz 6.0.
    * Now supports scripting language to set up calculations. The language is almost identical to the language in the NairnFEAMPM app.
    * All documentation was revised to briefly explain the new scripting commands.
    * All material types are documented in a separate help topic
    * Example scripted files are in nairn-fea-mpm code project

  * Previous trunk version of release 5.0 (this version was deleted when it was replaced by the OpenMP branch on Jan 14, 2014).
    * Has NairnFEAMPMViz 4.0.

  * release-4.0 (9 JAN 2013)
    * Has NairnFEAMPMViz 4.0.
    * Update to handle the new axisymmetric MPM option in NairnMPM.
    * Started a scripting language similar to NairnFEAMPM (Mac app), which is a much better way to create models than using direct `XML` commands. Most of the FEA commands and some of the MPM commands are done. The scripting language itself is modeled on the NairnFEAMPM language, but still lacks some features of that language. What is present is mostly compatible.
    * Enhanced help window to document new scripting commands and all material types.
    * Continuous development of the user interface.

  * release-3.0 (25 JAN 2012)
    * Has NairnFEAMPMViz 3.3.0.
    * Reorganized the code moving all application details to a separate package.
    * Particle and mesh plots now have their own menu and can change the plot quantity.
    * Time and X-Y plots can add labels, which can be dragged to move and double clicked to edit.
    * Go To Line command for windows with commands.
    * Scale Results to plot mesh and particles with different units.
    * The Window menu tracks more windows.
    * On Mac, menus move to the top of the screen (but Mac users should use the Mac app instead)
    * Fixed one bug in mesh plots that clipped to particles.
    * Recent files menu
    * Can open 3D results. Can see text output, but only limited plotting options.
    * Updated to read FEA results with 9-node Lagrange elements
    * Find/Replace window for editing of input files or for finding in analysis results.

  * release-2.0 (25 JUL 2010)
    * Has NairnFEAMPMViz 3.1.0
    * Can zoom in on particle and mesh plots
    * MPM mesh plots can clip plot to the particles
    * Added menu command to export movie frames (MPM plots)
    * If change limits and click Replot, plot will now be redrawn with new limits (before had to change frame)
    * Added color wells for plot elements
    * Added purple to red spectrum
    * Synchronize time selected between plot and control panel for MPM plots

  * release-1.0 (30 DEC 2009)
    * Has NairnFEAMPMViz 3.0.0
    * Organized into windows with no button bar
    * Added dtd validation options
    * Icon tool bars
    * Two new color options for plots and discrete spectra option

# Archival Version History #

Prior to being in `GoogleCode.com`, NairnFEAMPMViz was in a local repository. That repository is available if needed. The prior versions are:


  * `NairnCode1_5_0` (14 MAR 2008)
    * Has `NairnFEAMPMViz 2.1.0`
    * Can plot debonded crack length (when using traction laws)
    * Read rotational strains and plot using deformation gradient
    * Export graphic files from all plot windows

  * `NairnCode1_5_0` (14 MAR 2008)
    * Has `NairnFEAMPMViz 2.0.0`
    * Can now load command files and submit jobs
    * Some inspector options in the plotting

  * `NairnCode1_4_0` (25 OCT 2007)
    * Has `NairnFEAMPMViz 1.0.0`
    * First full featured version including both MPM and FEA Visualization

  * `NairnCode1_3_0` (19 FEB 2007)
    * Has `NairnFEAMPMViz` (preliminary version)
    * Only particle plots and only MPM visualization
    * First `NairnCode` to include NairnFEAMPMViz tool