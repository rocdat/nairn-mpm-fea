/********************************************************************************
	UpdateStrainsLastTask.cpp
	NairnMPM

	Created by John Nairn on July 22, 2010
	Copyright (c) 2010 John A. Nairn, All rights reserved.
 
	A strain update at the end of the MPM step is used in the SZS and
		the USAVG method. For these to be stable, the new particle momenta
		have to be re-extrapolated to the grid
 
	Zero nodes and extrpolate particle momenta and and positions
		to the grid.
 
	Once done, adject momenta for material contact, crack contact, and
		boundary conditions
	
	Since will reuse initial locations (i.e. shape functions and their gradients
		on each particle are the same), the mass, volume, and mass gradient
		would not change, even if re-extrapolated, and thus they do not
		need to be changed.
 
	For rigid particles, only displacement changed and it is found when node
		rezeroed
 
	After new extrapolations, update strains on all particles
********************************************************************************/

#include "NairnMPM_Class/UpdateStrainsLastTask.hpp"
#include "NairnMPM_Class/UpdateStrainsFirstTask.hpp"
#include "NairnMPM_Class/NairnMPM.hpp"
#include "Materials/MaterialBase.hpp"
#include "MPM_Classes/MPMBase.hpp"
#include "Elements/ElementBase.hpp"
#include "Cracks/CrackHeader.hpp"
#include "Custom_Tasks/TransportTask.hpp"
#include "Nodes/NodalPoint.hpp"
#include "Cracks/CrackSurfaceContact.hpp"
#include "Boundary_Conditions/NodalVelBC.hpp"

#pragma mark CONSTRUCTORS

UpdateStrainsLastTask::UpdateStrainsLastTask(const char *name) : MPMTask(name)
{
}

#pragma mark REQUIRED METHODS

// Get total grid point forces (except external forces)
void UpdateStrainsLastTask::Execute(void)
{
	int i,p,iel,matfld,numnds,nds[maxShapeNodes];
	MaterialBase *matID;
	double mp,fn[maxShapeNodes],xDeriv[maxShapeNodes],yDeriv[maxShapeNodes],zDeriv[maxShapeNodes];
	short vfld;
	TransportTask *nextTransport;
	
	// zero again (which finds new positions for rigid particles)
	for(i=1;i<=nnodes;i++)
		nd[i]->RezeroNodeTask6(timestep);
	
	// loop over non-rigid particles
	for(p=0;p<nmpms;p++)
	{	matID=theMaterials[mpm[p]->MatID()];
		if(matID->Rigid()) continue;            // skip rigid BCs and rigid contact materials
		mp=mpm[p]->mp;			// in g
		matfld=matID->GetField();
		
		// find shape functions (why ever need gradients?)
		iel=mpm[p]->ElemID();
		if(fmobj->multiMaterialMode)
        {   // Need gradients for volume gradient
            theElements[iel]->GetShapeGradients(&numnds,fn,nds,mpm[p]->GetNcpos(),xDeriv,yDeriv,zDeriv,mpm[p]);
        }
		else
			theElements[iel]->GetShapeFunctions(&numnds,fn,nds,mpm[p]->GetNcpos(),mpm[p]);
		
		for(i=1;i<=numnds;i++)
		{	vfld=(short)mpm[p]->vfld[i];
			
			// velocity from updated velocities
			nd[nds[i]]->AddMomentumTask6(vfld,matfld,fn[i]*mp,&mpm[p]->vel);
			
			// add updated displacement and volume (if cracks, not 3D)
			contact.AddDisplacementVolume(vfld,matfld,nd[nds[i]],mpm[p],fn[i]);
            
            // material contact calculations
			nd[nds[i]]->AddVolumeGradient(vfld,matfld,mpm[p],xDeriv[i],yDeriv[i],zDeriv[i]);
		}
	}
	
	// update nodal values for transport properties (when coupled to strain)
	nextTransport=transportTasks;
	while(nextTransport!=NULL)
		nextTransport=nextTransport->UpdateNodalValues(timestep);
	
	// adjust momenta for multimaterial contack
	NodalPoint::MaterialContact(fmobj->multiMaterialMode,FALSE,timestep);
	
	// adjust momenta for crack contact
	CrackHeader::ContactConditions(FALSE);
	
	// import grid boundary conditions
	NodalVelBC::GridMomentumConditions(FALSE);
	
	// update strains based on current velocities
	UpdateStrainsFirstTask::FullStrainUpdate(strainTimestep,(fmobj->mpmApproach==USAVG_METHOD),fmobj->np);
}