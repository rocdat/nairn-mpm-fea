# Introduction #

This page gives brief history of the main changes in various version of the `NairnMPM` code engine.

# Version in the Code #


The version number is coded in the constructor of the `NairnMPM.cpp` class:

```
	version=7;					// main version
	subversion=2;					// subversion (must be < 10)
	buildnumber=0;					// build number
```

# Version History #

NairnMPM was first imported to `GoogleCode.com` as version 7.2.0. The versions currently in this project are as follows:

  * Current main trunk
    * Working on NairnMPM 10.1.0
    * Added two new damping options - particle damping and PIC damping; the later can also run simulations with mixed FLIP/PIC style updates. In making this change, also changed the way grid damping is implemented, but it should not make much of a difference.
    * Mooney can take E and nu OR K and G1. HEIsotropic and HEMGEOSMaterial can take G or G1.
    * Mooney, HEIsotropic, and HEMGEOSMaterial were revised to better handle residual stresses
    * Neohookean material as alternative to Mooney in its Neohookean mode. These two Neohookean materials used different strain energy functions.
    * New ClampedNeohookean material is hyperelastic-plastic material with softening based on critical elongations
    * HEMGEOSMaterial in tension was changed for better stability during large temperature changes.
    * `ReverseLoad` custom task can be triggered on any global quantity as well as crack length and it can hold for a specified time before reversing (or aborting). Finally, it had a bug using the hold style with load and traction BCs; the bug is fixed.
    * J integral calculations improved, especially when the contour encounters other cracks. A new `gridenergy` option might stabilize J calculations when crack tip has variations in kinetic or work energy on the particles.
    * Improved updating of crack plane when using the `avg` method, as long as the crack surface updating works well.
    * Added option to archive if selected number of propagations and/or debonds occur.
    * `VTKArchive` custom task can now archive volume gradient vectors and the number of points extrapolated to each node.
    * Selected materials can share material velocity fields in multimaterial mode.
    * `PressureTraction` law added a `minCOD` parameter to require some crack opening before the pressure is applied.
    * The internal coding for the Viscoelastic material was rewritten using internal variables. The new version now adds support for axisymmetric calculations and should correctly calculate dissipated energy (which can be converted into heat in adiabatic simulations).
    * Crack methods improved for interacting and intersecting cracks, for moving of crack surfaces, and for applying traction loads to nodes near cracks.
    * NairnFEAMPMViz add many new features including support for running calculations on a remote server and improved 2D graphics with option to output PDF version of the plots.
    * Can specify contact normal (if known).
    * The `TaitLiquid` can now set an initial pressure.

  * Release-5.0 (9 Feb 2014): On Jan 14, 2014, the OpenMP branch replaced the main trunk for this release. That branch was started on April 2, 2013 to make parallel code. It has lots of changes needed to be parallel. All MPM materials use buffers for any material class variable that changes with particle state. The entire problem is divided into patches with ghost nodes on boundaries (and some section divide work by patch). The Particles reordered by type, which helps some loops divided by type (e.g., rigid velocities). The crack velocity field calculation is done in the initiation phase. Many other changes have been done along the way, although many of these are just features and not crucial for parallel code:
    * Has NairnMPM 10.0.0
    * May 16: Torus object for 3D
    * May 22: Changed Johnson-Cook when above TM to be better
    * May 29: Heat flux BCs
    * July 26: Pyramid object for 3D and designation of symmetry planes for improved contact calculations.
    * Aug 6: Rigid contact materials all combined to single crack velocity field which is much better for rigid material within a crack. In the future might want regular materials to ignore cracks too (to wedge open crack with metal, for example).
    * Aug 13: Fixed bug in rigid particle z direction and z symmetry planes
    * Aug 23: Added option to track reaction forces at velocity and/or at rigid particle BCs. Also improved tracking of contact forces to use only post-update contact calculations (which agrees much better with expectations).
    * Sept 17: J integral approximately deals with interacting cracks by averaging velocities field of other cracks it encounters along the J contour. This change also fixed a velocity field bug that has long been in J calculations, but probably caused very small errors.
    * Sept 22: New traction law to apply constant normal stress on crack surfaces.
    * Oct 9: friction heating supported
    * Oct 25: J  fields averaging to approximately support interacting cracks
    * Nov 7: crack initialization parallized
    * Nov 18: allow time step in functions
    * Dec 5: Symmetry plane boundary condtions
    * Dec 9: mirror property for rigid material for better BCs
    * Dec 10: Artifical viscosity uses total volume raters
    * Dec 19: New energy and heat traction and changes to achieved quantities. Also tracks entropy and can archive internal energy and Helmholz free energy.
    * Dec 20: Tait liquid finished and seems fairly sound, although some instabilities.
    * Jan 2: Fixed 3D bug introduced Dec 11, 2013
    * Jan 8: All documentation simplified with the details moved to the OSUPDocs wiki page
    * Jan 22: Added Shell shape command for 3D simulations

  * Prior trunk version of release 5.0 (until 14 JAN 2014 - it was replaced by parallel branch; all additions below are in the new trunk)
    * Working on NairnMPM 9.2.0
    * Prints svn revision number of code used in output files
    * Hardening Laws have been separated from materials to allow one to select them independently - this approach creates a large number of material types. An alternate nonlinear hardening law is among the previously available hardening laws.
    * `MGSCGLMaterial` has been replaced by `MGEOSMaterial` that use a Mie-Grüneisen law for pressure and can pick any hardening law. This material has also be greatly improved for more accurate tracking of internal energy (as needed in the pressure law) and to allow artificial viscosity useful in shock wave calculations.
    * `SLMaterial`, `JohnsonCook`, and `VonMises` materials have been eliminated. Instead use the new `IsoPlasticity` or `MGEOSMaterial` and then select any hardening law.
    * The `HEIsotropic` hyperelastic-plastic material is now fully developed. It can use any hardening law.
    * A new `HEMGEOSMaterial` implements Mie-Grüneisen law for pressure and hyperelastic methods for shear. It can use any hardening law.
    * Thermodynamics of deformation is now better modeled. Materials now track work and heat energy separately and their sum is internal energy. Mechanical energy coupling for adiabatic process can now be used with conduction on or off.
    * The `Mooney` material has an option to model an ideal rubber elastic material that heats on stretching and cooling on contraction. The material also tracks entropy change and during isothermal loading in the new ideal rubber mode, force is given by f = -(dS/dL)<sub>T</sub>. This material now also allows three difference energy function for pressure calculations.
    * The `IdealGas` material now tracks entropy change.
    * The `VTKArchive` can archive several new quantities.
    * Crack tips now track material type to all propagation between materials in a composite.
    * Fixed bug in J calculation

  * release-4.0 (9 JAN 2013)
    * Has NairnMPM 9.0.0
    * Addition of axisymmetric option for MPM. It does not yet do J integral and a few materials types do not support it yet (the code will not run if you use an unsupported material). A paper on axisymmetric MPM has been submitted.
    * Multmaterial mode contact can now implement imperfect interface laws in addition to friction laws. It is set up with `Friction` commands in `MultiMaterialMode` command or in material definitions.
    * Two new `Normals` option for multimaterial mode were added. One finds the volume-weighted average volume gradient of the contacting materials (it has been made the default normals method) and the other is classic MPM method of using each material's own gradient (it is not recommended, but available for comparison). Recent work on contact has shown all normal methods can have problems. The best solution is to specify a known normal. When that is not possible, another option is to use `Vmin` option of `MultiMaterialMode` command to screen out contact nodes near free edges. These recommendations are in a submitted paper on imperfect interfaces in MPM contact.
    * Overall improvements in contact mechanics.
    * Added `CPDI` (convected particle domain integration) as option to `GIMP` command (2D and 3D)
    * Added `TractionBC` to apply loads to surfaces rather then directly to particles (which can reduce artifacts in particles with external loads)
    * The grid now supports 1, 4, 9,  16, or 25 particles per cell in 2D and 1, 8, or 27 in 3D and both GIMP and CPDI work for all options.
    * Added `DefGradTerms` to pick how many terms used in the new exponential expansion to find the incremental deformation gradient for hyperelastic materials. The default 2 is recommended.
    * The flux boundary condition for diffusion is now much better. It uses the real surface integral term in MPM diffusion analysis.
    * Finished Johnson-Cook material.
    * The `MGSCGLMaterial` can now do plane stress calculations
    * `BCBox` for particle or velocity boundary conditions can specify an axis to change it to a cylinder
    * All internal objects based on `BodyObjectController` were changed to derive from generalized `ShapeController`. The changes allowed several body object controllers to be deleted.
    * Cracks are now represented in a hierarchical binary tree. This new representation allows dramatic increase in efficiency for curved cracks or for any crack not aligned with x or y axes.
    * Added ideal gas material implemented as a hyperelastic material.
    * The `RigidMaterial` code has been improved to allow independent control of velocities in `x`, `y`, and `z` directions (`direction` = 0 to 7), each axis can use its own function, and the functions can depend on position and time. This change allows, for example, to have rigid materials move in a circular motion.
    * `RigidMaterials` for contact (`direction`=8) can now use separate functions for each coordinate to simulate more types of motion and the function can now depend on position and time.
    * `RigidMaterials` that set temperature or concentration with a function now use a new `valueFunction` property and it can be a function of position and time. Because temperature and concentration functions were set before using `settingFunction`, old files will have to be updated to this  new method.
    * Body forces for gravity were not correctly implemented for 3D before, but now work in 3D simulations.
    * `Cylinder` shape can add `radius` attribute to create a cone shape.
    * A new `CoupledSawTooth` traction law is implemented.
    * New `HistoryArchive` custom task to archive particle history data to tab-delimited text files.
    * New `AdjustTimeStep` custom task to adjust time step depending on particle state, but only for material types that can calculate a particle-state-dependent wave speed.
    * The skewed velocity condition had little use and has been removed. To get it just apply two conditions for x and y directions separately.
    * A new `-w` option to map relative files relative to the working directory rather than the input file.

  * release-3.0 (25 JAN 2012)
    * Has NairnMPM 8.1.0
    * Converted to using Xerces 3.1.1 and must link to 3.x or newer because new Xerces is not compatible with Xerces 2.8 or older.
    * Converted all `longs` to `ints` to avoid any potential machine-dependent issues in 64 bit compiles (NairnMPM can compile as 32 bit or 64 bit, and must match Xerces library bits)
    * Found bug in some 2D contact depending on machine/compiler combination and how they treated un-initialized doubles.
    * `min`, `max`, `min+`, _etc._ option in boundary conditions now enhanced to `min+n`, `min-n` (_etc._) where `n` is an floating point number to specify number of cells relative to edge of the grid. This option can now also be used when using shapes to create material points.
    * Changed `q` in user-defined functions to mean rotation during the simulation rather then material angle it meant before. Changed in 8.0.1 and it will invalidate old input files that used `q` in functions on particles that started with non-zero rotation angle.
    * Rewrote `MPMStep()` to organize all tasks into task objects. The tasks can be profiled. A future plan is to optimize each task, perhaps for multi-core processors.
    * Added `AltPropagate` command to allow competing fracture modes. Its initial use is for competition between interface fracture and fracture turning into the bulk.
    * The default `Vmin` for multimaterial contact was changed to 0.0.
    * Added new `RigidBias` attribute for `MultiMaterialMode` command that takes the normal from the volume gradient of the rigid material unless the magnitude of the volume gradient from the non-rigid material is higher by the `RigidBias` factor. It only applies when normals=0.
    * Multimaterial mode that has contact with rigid particles can now track contact forces on the grid by using either a new `VTKArchive` custom task option or a new `GlobalArchive` option to archive a sum of all contact forces.
    * New Trilinear traction law material was implemented.
    * Revised movement of crack surface particles to include more small movements and to ignore large movements. It works much better with some new cutting simulations.
    * Improved traction laws so they can be used with interacting cracks.
    * `VTKArchive` option for total strain
    * `Damping` command can use a function to have grid damping that varies with time.
    * `Polyhedron` command for more 3D objects
    * Added `Entity` command.
    * Enhanced `BMP` command to allow specifying distance per pixel and to superpose multiple images.
    * The previous Mooney material (which was not really working correctly) was rewritten and expanded to full Hyperelastic material and works in 2D (plane stress and plane strain) and in 3D. A subset of this material is a Neo-Hookean material.
    * Commands that specify materials with `mat` attribute can now use `matname` instead to specify materials by name. Using `mat` and `matname` options in the same input file should be avoided.

  * release-2.0 (25 JUL 2009)
    * Has NairnMPM 7.3.0
    * The `TriangularTraction` and `CubicTraction` traction law were changed to provided a mixed-mode cohesive law (by methods used by Thouless) with exponential criterion with user-input exponent.
    * The `TriangularTraction` traction law was improved to allow peak position to be zero, which results in pure linear softening.
    * A new type of rigid materials (with `SetDirection=8`) that can do frictional contact in multimaterial mode. It can also be used to wedge open cracks.
    * Revised algorithm for preventing crack surfaces from crossing the crack plane and a new option to turn that feature on or off (see `MovePlane` command).
    * A minor change in the way crack surface velocities are calculated that should only effect cracks that exit the body, but those cracks are better done now using the `exterior` crack tip defined in version 7.2.0.
    * Blocked custom tasks from turning off extrapolations and added material field to custom task methods
    * Added `unique` attribute to `ArchiveRoot` command to force creation of new results subfolder on each run.
    * Added `material` option to the `VTKArchive` custom task.
    * Von Mises material has added one nonlinear hardening law; before it only had linear hardening.
    * Transversely isotropic, orthotropic, and Hill plastic materials can now do 3D. Rotation methods in `Body` command used to specify initial orientation of particles. All seem to work, but it is difficult to verify off-axis orientations. (Warning: any checkout for 7.2.2 had 3D working, but broke the 2D version for these materials only. It is fixed when version changed to 7.2.3. Also some rotations and transport rotations were not correct until version 7.3.0)
    * Rewrote Newton-Rapheson algorithm in anisotropic plastic materials (Hill plastic) to add bracketing, which should eliminate instabilities that were common with certain values for anisotropic yield stresses.
    * Archive format changed to `ver6` to add archiving of 3 rotation angles of 3D particles needed for anisotropic materials.
    * More efficient at finding neighboring element when particles cross boundaries (2D, structured grid only)
    * Fixed error calculating particle mass for 3D grids when the elements were not perfect cubes.
    * Added `PropagateLength` command to select the amount of crack growth each time a crack propagates.
    * `RotateZ` (and `Y` and `X`) can now be used as alternate methods to set angles for MPM models read in using BMP files.
    * Added `<DevelFlag>` option in the `<Header>` for use in development coding.

  * release-1.0 (30 DEC 2009)
    * Has NairnMPM 7.2.0
    * `MultiMaterialMode` is supported with frictional contact
    * Automatically archives input command at (root).fmcmd
    * `ContactPosition` applies to both crack and multimaterials because it extrapolates displacement or position and never both
    * Added thickness attribute to grid. Cracks will use it and warn if set differently
    * Track interface energy in MPM with a global archive option
    * Revised material output with utility code methods
    * Updated code to compile in GNU 4.3.1
    * Rearranged x-y-z nodal point numbering to work better with 3rd-party visualization (like Paraview)
    * Added VTKArchive custom task to allow exporting of VTK Legacy files with grid data.
    * ver5 archive files to say if structured grid and to include archive time in ms
    * History archive can be Y, N, 1, 2, 3, -> 16 (using ASCII codes) to archive up to 4 history variables.
    * Also can global archive "history n"
    * Added MGSCGL material (not in NairnFEAMPM yet)
    * Added SL material (not in NairnFEAMPM yet)
    * Horiz, Vert, and Depth for the grid can specify cellsize rather than a number
    * `BCLine`, `BCArc`, `BCBox`, and `LdRect` can use `min` and `max` in coordinates
    * tolerance can be `*f` to be `f *` cell minumum size
    * Revisions led to new contact methods for cracks too.
      * Redid contact code - no longer interpret once, but interpret as needed
      * Similar changes in imperfect interface forces
      * Similar changes when moving crack surfaces (they may benefit further by looking for boundary condition velocities)
      * The move plave avg method uses a weighted average by mass extrapolated to each surface particle
      * Crack near edge can be designiated as `exterior` to mean crack plane is extrapolated but movement comes from within the body (by using tipmat=-1)

# Archival Version History #

Prior to being in `GoogleCode.com`, NairnMPM was in a local repository. That repository is available if needed. The prior versions are:

  * `NairnCode2_0_0` (4 NOV 2008)
    * Has NairnMPM 6.6.2
    * Propagate into a traction material (and documentation of traction laws)
    * Add diffusion, condutions, and residual stress to 3D
    * 3D is all documented
    * Added `<net>` option to spread out total load equally over all found particles
    * Deleted Dugdale material
    * Improved Von Mises Hardening material and made it 3D as well
    * Added Hill Plastic - an anisotropic plastic material
    * `LeaveLimit` option to keep running even in particles leave the grid (they are moved back in)
    * Materials can have color, but only role is in programs that read the file
    * `ContactPosition` command to allow contact when crack surface were not initially in contact (approximately)

  * `NairnCode1_5_0` (14 MAR 2008)
    * Has NairnMPM 6.5
    * `SettingFunction` in rigid materials for time-dependent settings.
    * Feedback damping added target kinetic energy option and global archive can record the feedback alpha
    * Adding option to have traction law between crack surfaces - it is currently undocumented and not completed

  * `NairnCode1_4_0` (25 OCT 2007)
    * Has NairnMPM 6.4.0
    * Element crossings counted and can be archived
    * All materials now calculate szz and ezz, before elastic only found it when archiving (found error in prior szz and ezz in off axis, anisotropic materials now fixed)
    * Skewed velocity boundary conditions and skewed rigid particles
    * Arbitrary function of time and position allowed for all boundary conditions
    * Added base class isotropic diffusion and conductivity so it is now available in all materials. Aniostropic materials or those whose transport properties depend on particle state must override
    * Some material class reorganization such as printing to output window
    * Concentration flux boundary conditions.
    * Coupled moisture expansion and residual stresses and strains and all materials have moisture expansion coefficients
    * BCArc command for grid and particle BCs
    * `Line` and `Circle` in `CrackList` to create crack segments
    * Added `MovePlane` command for two ways to move crack plane. Also fixed some bugs found in crack surface movement, but only one one side of the crack had no particles
    * BMPRegion an have second mask to give orientation of particles too.
    * 3D for isotropic (no res stress, diffusion, conductions, cracks, gravity, custom tasks)
    * Some memory changes to only allocate data that are needed to allow larger calculations)

  * `NairnCode1_3_0` (19 FEB 2007)
    * Has NairnMPM 6.3.0
    * `LoadMechanicalProperties()` always called before constitutive law. Can be used to change properties depending on particle state (stress, temperature, etc.). Replaces `LoadMechProps()`, which only had particle angle (and can still be used if angle is only property that matters).
    * New option to select method to find propagation direction
    * Implementation of spline methods to do crack calculations

  * `NairnCode1_2_0` (8 FEB 2007)
    * Has NairnFEA 6.2.0
    * Fixed problem in transport calculations when points use same anistropic material but with different angles
    * Imperfect interface may be done - fixed problems that depending on location or orientation of interface
    * Started energy coupling between temperature and dissipated energy, but only in vonMises material and appears to be off by factor of 4

  * `NairnCode1_1_0` (18 JAN 2007)
    * Has NairnMPM 6.1.0
    * Imperfect interface in place, but not yet done or documented
    * GIMP methods in 2D
    * Removed Update Strain Last option

  * `NairnCode1_0_0` (22 DEC 2006)
    * Has NairnMPM 6.0.0
    * Beginning of 3D calculations, but not documented
    * Code reorganized and `NairnFEA` and `NairnMPM` combined into single `NairnCode`

# Additional NairnMPM History #

The following versions are from a prior repository and no longer available:

  * NairnMPM5\_1\_0 (14 FEB 2006)
    * Code reorganization to merge better with FEA code. All common FEA/MPM code was moved to "common" classes.
    * Creation of NairnMPM class which runs the calculations. The "main&qout; is now generic code for both FEA and MPM.
    * Created a class to handle reading of input files.
    * Created a class to handle archiving of results.
    * Moved nearly all global variables to member variables of main classes.

  * NairnMPM5\_0\_2 (05 DEC 2005)
    * Feedback damping as new damping options.
    * Prints version number used for calculations.
    * Many internal changes for more robust reading of input files and future coordination with FEA code.

  * NairnMPM5\_0\_0 (15 JUL 2005)
    * Added third digit in version number to hold build number after minor changes
    * Detects crack contact now by extrapolated displacement combined with velocity of the surfaces. Contact means crack surfaces are overlapped and that they are approaching each other.
    * Two new crack propagation criterion (6 and 7) or COD and on total energy release rate (J integral).
    * Velocity BC near crack modified to only set velocity for same side of crack
    * Will now detect crack leaving the mesh and will stop crack propagation when it happens
    * Isotropic work hardening for Von Mises material
    * Interacting cracks are possible
    * Silent boundary conditions added
    * Custom friction setting for each crack
    * Revised code to read XML files with "object" controllers
    * Fixed problem when velocity, temperature, or concentration boundary conditions were on a node but they did not start at time zero

  * NairnMPM4\_0 (3 FEB 2005)
    * A new BMP option to create material points based on a gray scale image in a BMP file
    * An abort option (flag -a) will exit after setting up the problem and can be used to check the discretization of the problem
    * Many more commands can take an optional units attribute (see documentation for when allowed)

  * NairnMPM3\_3 (19 NOV 2004)
    * Thermal conductivity started (only for isotropic materials and only with fixed temperature boundary conditions)
    * Crack tip heating started (but only for unit thickness)
    * `Fixed` cracks or cracks in which surfaces do not move cracks (for special uses)
    * `Fixed` crack propagation direction (for special uses)
    * Initiation time option for steady state crack propagation
    * Rigid materials (for moving velocity boundary conditions)
    * An option to ouput nodes and elements in separate text files (see Mesh definition)

  * NairnMPM3\_2 (1 APR 2004)
    * More options for crack propagation
    * Support for linear viscoelastic materials completed
    * Addition of diffusion calculations (but in a preliminary way and not coupled to swelling strains)
    * These recent changes since `NairnCode1_0_0` should be added to versions.html in documentation

  * NairnMPM3\_1 (23 MAR 2004)
    * The XML input format was revised to make it more modular, make it easier to understand,
    * make it easier to read and maintain the DTD file, and to use better names for some tags. For example, all mesh creation commands are now in a `<Mesh>` element; all grid boundary conditions are within a `<GridBCs>` element; and are particle boundary conditions are within a `<ParticleBCs>` element.
    * The DTD file was added to the input folder of the checkout.

  * NairnMPM3\_0 (18 MAR 2004)
    * Reorganized all headers
    * Added Mooney, Von Mises, Viscoelastic, and Bistable Isotropic materials
    * Custom tasks defined; some prior tasks moved to custom tasks and new `ReverseLoad` task to reverse applied load under any simulation-results condition
    * J Integral, stress intensity factor, crack propagation, and various other crack options
    * First version of Diffusion calculations (but uncoupled to stresses and only allows zero-flux or variable concentration boundary conditions). An example Diffusion.fmcmd file is provided.

  * NairnMPM2\_2 (10 MAR 2003)
    * Reorganized all headers to make project easier to use as it gets bigger and to make it more compatible with NairnFEA code that is in development and will reuse some of the NairnMPM classes.

  * NairnMPM2\_1 (31 JAN 2002)
    * Added transversely isotropic and orthotropic materials

  * NairnMPM2\_0 (22 JAN 2003)
    * This is MPM code with fracture and has the newly revised method for archiving data.
    * As a first use of the new archived methods, the material points can now optionally archive particle strain energy and the separate components of the shear strain (du/dy and dv/dx).


