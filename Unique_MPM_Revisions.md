# Introduction #

When the current code seems to be broken, it might be necessary to check out previous revisions to see what changed to cause the problem. This partial list has notes on certain key features put into various versions and on when source code was actually changed. Non-unique versions mean only comments or documentation was changed, but no source code was changed (or a change appear in several commits).


# Known Unique Revisions #

Revisions before the start of the table or after the end of table have not been checked. Revisions between any two numbers should be avoided when comparing to older code. Those revisions are either identical or might have a partial commit and should not be used.

| Revision | Date | Change highlights |
|:---------|:-----|:------------------|
| [r45](https://code.google.com/p/nairn-mpm-fea/source/detail?r=45) | 29 Dec 2009 | Official 1.0 now on Google Code |
| [r79](https://code.google.com/p/nairn-mpm-fea/source/detail?r=79) | 30 Dec 2009 | Changed to 7.2.1 |
| [r104](https://code.google.com/p/nairn-mpm-fea/source/detail?r=104) | 14 Jan 2010 | Changed to 7.2.1, Anisotropic 3D, but<br>broke. Fixed in <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=120'>r120</a> <br>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=120'>r120</a> </td><td> 13 Mar 2010 </td><td> Changed to 7.2.3, Fixed broken 2D code </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=151'>r151</a> </td><td> 5 May 2010 </td><td> Added <code>nmix</code> for mixed mode fracture criteria </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=157'>r157</a> </td><td> 10 May 2010 </td><td> Tried combining rigid particles between crack velocity fields </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=158'>r158</a> </td><td> 10 May 2010 </td><td> Corrected volume gradient calculation in rigid contact to divide by rho<sup>2</sup> </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=159'>r159</a> </td><td> 11 May 2010 </td><td> Removed combining of rigid particles </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=160'>r160</a> </td><td> 11 May 2010 </td><td>  </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=161'>r161</a> </td><td> 21 May 2010 </td><td> Rotation calculations in <code>Generators.cpp</code> </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=168'>r168</a> </td><td> 3 Jun 2010 </td><td> Changed to 7.3.0, Anisotropic 3D materials ready </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=173'>r173</a> </td><td> 4 Jun 2010 </td><td> Added <code>WoodMaterial</code> </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=176'>r176</a> </td><td> 4 Jun 2010 </td><td> Work on <code>WoodMaterial</code> </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=177'>r177</a> </td><td> 9 Jun 2010 </td><td>  </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=180'>r180</a> </td><td> 9 Jun 2010 </td><td> Only change in <code>PrintTensor()</code> </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=181'>r181</a> </td><td> 24 Jun 2010 </td><td>  </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=183'>r183</a> </td><td> 14 Jul 2010 </td><td> Only change in <code>NodalPoint::GetMassGradient()</code>, but should have no affect </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=188'>r188</a> </td><td> 25 Jul 2010 </td><td> Tagged as release 2.0, but should be same as <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=181'>r181</a> </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=189'>r189</a> </td><td> 25 Jul 2010 </td><td> Changed to 8.0.0, Converted <code>MPMStep()</code> to use task objects </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=200'>r200</a> </td><td> 30 Jul 2010 </td><td> Added Normals=2 option </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=204'>r204</a> </td><td> 4 Aug 2010 </td><td>  </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=205'>r205</a> </td><td> 6 Aug 2010 </td><td> Added development flags to Rigid contact to try other methods </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=206'>r206</a> </td><td> 11 Aug 2010 </td><td> Removed Normals=2 and replaced with <code>RigidBias</code> </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=211'>r211</a> </td><td> 18 Aug 2010 </td><td> Work on tracking of rigid contact forces </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=218'>r218</a> </td><td> 26 Aug 2010 </td><td> Added <code>DevelFlag</code> for cutting, but rest should be same as <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=211'>r211</a> </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=223'>r223</a> </td><td> 15 Sep 2010 </td><td> Added <code>VTKArchive</code> for contact forces on grid.<br> A global archive option for contact did not work for more than one component<br>Broken single material mode </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=225'>r225</a> </td><td> 16 Sep 2010 </td><td> Fixed global archiving of more than one component of total contact force on the grid<br>Broken single material mode </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=228'>r228</a> </td><td> 16 Sep 2010 </td><td> Fixed single material mode broken in <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=223'>r223</a> and <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=225'>r225</a><br>Note that <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=227'>r227</a> is same but had logging enabled </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=231'>r231</a> </td><td> 21 Sep 2010 </td><td> Added Trilinear Traction law material </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=234'>r234</a> </td><td> 23 Sep 2010 </td><td> Changed movement of surface particles to crack surfaces<br>Ignores large movements because they are usually wrong </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=239'>r239</a> </td><td> 28 Sep 2010 </td><td> Changed to 8.0.1, Changed meaning of <code>q</code> in user defined functions </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=259'>r259</a> </td><td> 14 Oct 2010 </td><td> Improved traction laws to work with interacting cracks </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=264'>r264</a> </td><td> 3 Nov 2010 </td><td> Traction loads better balanced<br>Improved surface mass calculation when updating crack surfaces and plane by <code>avg</code><br>Wide-open cracks with no tractions are collapsed<br>Added <code>VKArchive</code> option for total strain </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=274'>r274</a> </td><td> 1 DEC 2010 </td><td> Converted to Xerces 3.1.1 (now required to compile and run)<br>Fixed bug in contact detection on some machines (depending on uninitialized doubles)<br>Converted <code>longs</code> to <code>ints</code> to avoid machine-dependent 64 bit results (NairnMPM can compile either) </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=289'>r289</a> </td><td> 13 JAN 2011 </td><td> Added Polyhedron option for 3D simulations </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=312'>r312</a> </td><td> 18 APR 2011 </td><td> Langrange 2D element added. It is used in FEA. I does not seem to work well in MPM (and therefore disabled). It might work if a GIMP option is added. </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=322'>r322</a> </td><td> 7 JUN 2011 </td><td> Enhanced Polyhedron option for 3D simulations and enhanced BMP command for new options </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=324'>r324</a> </td><td> 6 JUL 2011 </td><td> Converted Mooney material into full 2D and 3D, isotropic, hyperelastic material </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=374'>r374</a> </td><td> 26 JAN 2012 </td><td> Release 3.0 tagged. See wiki on NairnMPM versions </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=410'>r410</a> </td><td> 1 JUN 2012 </td><td> Added ideal gas material </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=430'>r430</a> </td><td> 29 AUG 2012 </td><td> Added binary tree crack method </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=468'>r468</a> </td><td> 28 SEP 2012 </td><td> Added CPDI, traction BCs, started HEDevelopment branch </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=504'>r504</a> </td><td> 29 OCT 2012 </td><td> Revised Mooney material for incremental deformation gradient </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=532'>r532</a> </td><td> 7 DEC 2012 </td><td> GIMP with other numbers or particles per element </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=536'>r536</a> </td><td> 7 DEC 2012 </td><td> Axisymmetric branch brought into main trunk </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=560'>r560</a> </td><td> 19 DEC 2012 </td><td> Added energy dissipation calculation to viscoelastic materials </td></tr>
<tr><td> <a href='https://code.google.com/p/nairn-mpm-fea/source/detail?r=579'>r579</a> </td><td> 6 JAN 2013 </td><td> Added working directory option </td></tr></tbody></table>

This list is no longer being maintained, but you can browse through versions in the <a href='http://code.google.com/p/nairn-mpm-fea/source/list'>source list page</a> to get an idea if which revisions had real changes a which had only cosmetic or documentation changes.