/********************************************************************************
    MPMBase.cpp
    NairnMPM
    
    Created by John Nairn on Tues Feb 5 2002.
    Copyright (c) 2001 John A. Nairn, All rights reserved.
********************************************************************************/

#include "MPM_Classes/MPMBase.hpp"
#include "Cracks/CrackHeader.hpp"
#include "Nodes/NodalPoint.hpp"

// globals
MPMBase **mpm;		// list of material points
long nmpms=0;		// number of material points

#pragma mark MPMBase::Constructors and Destructors

// Constructors
MPMBase::MPMBase()
{
}

MPMBase::MPMBase(int elem,int theMatl,double angin)
{
    int i;
    
    inElem=elem;
	mp=-1.;						// calculated in PreliminaryCalcs, unless set in input file
    matnum=theMatl;
	SetAngle0InDegrees(angin);
    
    for(i=1;i<MaxShapeNds;i++)
        vfld[i]=NO_CRACK;
        
    // zero stresses and strains
	ZeroTensor(&sp);
	ZeroTensor(&ep);
	ZeroTensor(&eplast);
	ZeroTensorAntisym(&wrot);
    
    // zero work and energies
    extWork=0.;
    plastEnergy=0.;
	dispEnergy=0.;
    strainEnergy=0.;
	
	// for J integral if needed
	velGrad=NULL;
	
	// material data is needed
	matData=NULL;
	
	// concentration (c units) and gradient (c units/mm)
	pConcentration=0.;
	pDiffusion=NULL;
    
	// temperature (degrees) and gradient (degrees/mm)
	SetTemperature(0.,0.);
	pTemp=NULL;

    // PS - when point created, velocity and position and ext force should be set too
	ZeroVector(&vel);
	
	elementCrossings=0;
}

// allocation diffusion data if need in this calculations
void MPMBase::AllocateTemperature(void)
{	pTemp=new TemperatureField;
	ZeroVector(&pTemp->DT);
}

// allocation diffusion data if need in this calculations
void MPMBase::AllocateDiffusion(void)
{	pDiffusion=new DiffusionField;
	pDiffusion->flux=0.;
	ZeroVector(&pDiffusion->Dc);
}

// allocation diffusion data if need in this calculations
void MPMBase::AllocateJStructures(void)
{	velGrad=new Tensor;
}

// Destructor (and it is virtual)
MPMBase::~MPMBase() { }

#pragma mark MPMBase::Methods

// reverse the direction (should only be done for rigid material particles)
void MPMBase::ReverseParticle(void)
{	vel.x=-vel.x;
    vel.y=-vel.y;
}

// stop the particle (should only be done for rigid material particles)
void MPMBase::StopParticle(void)
{	vel.x=0.;
    vel.y=0.;
}

#pragma mark MPMBase::Accessors

// set mass in PreliminaryCalcs, but only if input file did not set it first
void MPMBase::InitializeMass(double mass)
{	if(mp<0.) mp=mass;
}

// set or average velocity gradient (2D) (only needed for second J Term)
void MPMBase::SetVelocityGradient(double dvxx,double dvyy,double dvxy,double dvyx,int secondPass)
{
    if(JTerms!=2) return;
    if(!secondPass)
    {	velGrad->xx=dvxx;
        velGrad->yy=dvyy;
        velGrad->xy=dvxy;
        velGrad->zz=dvyx;		// yx stored in zz
    }
    else
    {	velGrad->xx=(velGrad->xx+dvxx)*0.5;
        velGrad->yy=(velGrad->yy+dvyy)*0.5;
        velGrad->xy=(velGrad->xy+dvxy)*0.5;
        velGrad->zz=(velGrad->zz+dvyx)*0.5;		// yx stored in zz
    }
}

// set concentration (only, and for all particles, during initialization)
void MPMBase::SetConcentration(double pConc,double pRefConc)
{	pConcentration=pConc;
	pPreviousConcentration=pRefConc;
}

// set temperature (only and for all particles, during initialization)
void MPMBase::SetTemperature(double pTempSet,double pRefTemp)
{	pTemperature=pTempSet;
	pPreviousTemperature=pRefTemp;
}

// material ID (convert to zero based)
int MPMBase::MatID(void) { return matnum-1; }			// zero based material array in data storage
int MPMBase::ArchiveMatID(void) { return matnum; }		// one based for archiving

// element ID (convert to zero based)
int MPMBase::ElemID(void) { return inElem-1; }					// zero based element array in data storage
void MPMBase::ChangeElemID(int newElem)
{	inElem=newElem+1;		// set using zero basis
	elementCrossings++;		// count crossings
}
int MPMBase::ArchiveElemID(void) { return inElem; }			// one based for archiving

// return current element crossings for archiving and reset to zero
int MPMBase::GetResetElementCrossings(void)
{	int was=elementCrossings;
	elementCrossings=0;
	return was;
}

// get deformation gradient terms
double MPMBase::GetDuDy(void) { return (ep.xy+eplast.xy-wrot.xy)/2.; }
double MPMBase::GetDvDx(void) { return (ep.xy+eplast.xy+wrot.xy)/2.; }

// angle0 is initial 2D orientation angle
double MPMBase::GetRotation(void) { return angle0-0.5*wrot.xy; }
double MPMBase::GetRotationInDegrees(void) { return 180.*(angle0-0.5*wrot.xy)/PI_CONSTANT; }
void MPMBase::SetAngle0InDegrees(double angle) { angle0=PI_CONSTANT*angle/180.; }
double MPMBase::GetAngle0InDegrees(void) { return 180.*angle0/PI_CONSTANT; }
void MPMBase::IncrementRotationStrain(double rotXY) { wrot.xy+=rotXY; }
void MPMBase::IncrementRotationStrain(double rotXY,double rotXZ,double rotYZ)
{	wrot.xy+=rotXY;
	wrot.xz+=rotXZ;
	wrot.yz+=rotYZ;
}
TensorAntisym *MPMBase::GetRotationStrainTensor(void) { return & wrot; }

// energies
double MPMBase::GetPlastEnergy(void) { return plastEnergy; }
void MPMBase::AddPlastEnergy(double energyInc) { plastEnergy+=energyInc; }
double MPMBase::GetDispEnergy(void) { return dispEnergy; }
void MPMBase::AddDispEnergy(double energyInc) { dispEnergy+=energyInc; }
void MPMBase::SetDispEnergy(double energy) { dispEnergy=energy; }
double MPMBase::GetStrainEnergy(void) { return strainEnergy; }
void MPMBase::AddStrainEnergy(double energyInc) { strainEnergy+=energyInc; }
double MPMBase::GetExtWork(void) { return extWork; }

// pointers to variables
Vector *MPMBase::GetPFext(void) { return &pFext; }
Vector *MPMBase::GetNcpos(void) { return &ncpos; }
Vector *MPMBase::GetAcc(void) { return &acc; }
Tensor *MPMBase::GetVelGrad(void) { return velGrad; }
Tensor *MPMBase::GetStressTensor(void) { return &sp; }
Tensor *MPMBase::GetStrainTensor(void) { return &ep; }
Tensor *MPMBase::GetPlasticStrainTensor(void) { return &eplast; }

// history data
char *MPMBase::GetHistoryPtr(void) { return matData; }
void MPMBase::SetHistoryPtr(char *createMatData)
{	if(matData!=NULL) free(matData);
	matData=createMatData;
}
double MPMBase::GetHistoryDble(void)
{	// assumes matData starts with a double and gets that first one
	double *h=(double *)matData;
	return *h;
}
void MPMBase::SetHistoryDble(double history)
{	// assumes matData starts with a double and sets that first one
	double *h=(double *)matData;
	*h=history;
}
double MPMBase::GetHistoryDble(int index)
{	// assumes matData is array of doubles and gets one an index (0 based)
	double *h=(double *)matData;
	return h[index];
}
void MPMBase::SetHistoryDble(int index,double history)
{	// assumes matData is array of doubles and sets one an index (0 based)
	double *h=(double *)matData;
	h[index]=history;
}

#pragma mark MPMBase Class Methods

/**********************************************************
    Update Strains on all particles
    Must impose grid velocity BCs and velocity
		alterations due to contact first
	secondPass will be TRUE only for USAVG method
**********************************************************/
void MPMBase::FullStrainUpdate(double strainTime,int secondPass,int np)
{
    NodalPoint::GetGridVelocitiesForStrainUpdate();			// velocities needed for strain update
	
	// loop over particles
    long p;
	for(p=0;p<nmpms;p++)
		mpm[p]->UpdateStrain(strainTime,secondPass,np);
}


