/********************************************************************************
    MGSCGLMaterial.cpp
    NairnMPM
    
    Created by John Nairn, June 16, 2008.
    Copyright (c) 2008 John A. Nairn, All rights reserved.
********************************************************************************/

#include "Materials/MGSCGLMaterial.hpp"
#include "MPM_Classes/MPMBase.hpp"
#include "Exceptions/CommonException.hpp"
#include "Custom_Tasks/ConductionTask.hpp"
#include "Custom_Tasks/DiffusionTask.hpp"
#include "Global_Quantities/ThermalRamp.hpp"

#pragma mark MGSCGLMaterial::Constructors and Destructors

// Constructors
MGSCGLMaterial::MGSCGLMaterial() {}

/* The default contructor should call a parent class constructor and
	then fill in any new initialization.
	*/
// Constructors
MGSCGLMaterial::MGSCGLMaterial(char *matName) : IsoPlasticity(matName)
{
	// defaults are some Tungsten properties
	yield=2200.;		// MPa
	yieldMax=0.;		// MPa
	beta=0.0;			// dimensionless
	nhard=1.0;			// dimensionless
	
	gamma0=1.64;		// dimensionless
	C0=4004;			// m/sec
	S1=1.35;			// dimsionless
	S2=0.;				// sec/m
	
	GPp=0.01e-3;		// MPa^-1
	GTp=-2.2e-4;		// K^-1
}

#pragma mark MGSCGLMaterial::Initialization

// Read material properties
char *MGSCGLMaterial::InputMat(char *xName,int &input)
{
	// unique properties here and
	//	yield found in Isoplasticity super class
	//	G found in IsotropicMat
	//	rho, Cv found in material base class
	
	// here are the rest
    if(strcmp(xName,"gamma0")==0)
    {	input=DOUBLE_NUM;
        return((char *)&gamma0);
    }
    
    else if(strcmp(xName,"C0")==0)
    {	input=DOUBLE_NUM;
        return((char *)&C0);
    }
    
    else if(strcmp(xName,"S1")==0)
    {	input=DOUBLE_NUM;
        return((char *)&S1);
    }
	
    else if(strcmp(xName,"S2")==0)
    {	input=DOUBLE_NUM;
        return((char *)&S2);
    }
	
    else if(strcmp(xName,"GPpG0")==0)
    {	input=DOUBLE_NUM;
        return((char *)&GPp);
    }
	
    else if(strcmp(xName,"GTpG0")==0)
    {	input=DOUBLE_NUM;
        return((char *)&GTp);
    }
	
    else if(strcmp(xName,"betahard")==0)
    {	input=DOUBLE_NUM;
        return((char *)&beta);
    }
	
    else if(strcmp(xName,"nhard")==0)
    {	input=DOUBLE_NUM;
        return((char *)&nhard);
    }
	
    else if(strcmp(xName,"yieldMax")==0)
    {	input=DOUBLE_NUM;
        return((char *)&yieldMax);
    }
	
    return(IsoPlasticity::InputMat(xName,input));
}

// verify settings and some initial calculations
const char *MGSCGLMaterial::VerifyProperties(int np)
{	
	// check properties
	if(!readYield) return "The yield stress is missing";
	if(!read[G_PROP]) return "The shear modulus, G0, is missing";
	if(yieldMax<yield) return "The maximum yield stress is less than the initial yield stress";
	
	// needed because SetAnalysisProps never called
	CME3=betaI*concSaturation;

	// call super class
	return MaterialBase::VerifyProperties(np);
}

// Constant properties used in constitutive law
void MGSCGLMaterial::InitialLoadMechProps(int makeSpecific,int np)
{	
	yldred = yield*1.e6/rho;
	yldMaxred = yieldMax*1.e6/rho;
	
	double rhoC02=1000.*rho*C0*C0;				// Pa
	double Cv=1000.*heatCapacityVol;		// J/(kg K)
	double rhoCvT0=1000.*rho*Cv*thermal.reference;	// Pa
	double g2=gamma0*gamma0;
	
	k1=(rhoC02-g2*rhoCvT0)/rho;	// Pa
	k2=(2.*rhoC02*S1-0.5*g2*gamma0*rhoCvT0)/rho;
	k3=(3.*rhoC02*S1*S1 - gamma0*rhoC02*S1/3. + 2.*rhoC02*S2*C0 - g2*g2*rhoCvT0/6.)/rho;
	
	// gamma0 rho heatCapacityVol has units J/(cm^3-K) = MPa/K, multiply by 1.e6 and divide by rho to make specific
	gRhoCv=gamma0*heatCapacityVol*1.e6;
	
	G0red = G*1.e6/rho;
	Gred = G0red;
	GPpred = GPp*rho*1.e-6;
	Kred = k1*1.e6/rho;
	
	// thermal expansion is handled in EOS in GetPressureChange() so need to set
	// CTE3 used by Isoplasticity to 0;
	// Not sure if this material can handle solvent expansion?
	CTE3=0.;
	
	// superclass sets yldred, but that replaced above, nothing else needed
	
	// plane stress correction done in GetPressureChange()
	psRed=1.;
}

// print mechanical properties to the results
void MGSCGLMaterial::PrintMechanicalProperties(void)
{
	// core properties
	PrintProperty("C0",C0,"m/s");
	PrintProperty("S1",S1,"");
	PrintProperty("S2",S2,"s/m");
	PrintProperty("gam0",gamma0,"");
	cout << endl;
	
	// calculated moduli
	PrintProperty("k1",k1*rho*1.e-6,"");
	PrintProperty("k2",k2*rho*1.e-6,"");
	PrintProperty("k3",k3*rho*1.e-6,"");
	cout << endl;
	
	// shear
	PrintProperty("G0",G,"");
	PrintProperty("Gp'/G0",GPp,"MPa^-1");
	PrintProperty("GT'/G0",GTp,"K^-1");
	cout << endl;
	
	// yield
	PrintYieldProperties();
	
	// effective CTE (in ppm/K)
	double effAlpha = (1.e12*heatCapacityVol*gamma0)/(3.*k1);
	PrintProperty("a",effAlpha,"");
	PrintProperty("T0",thermal.reference,"K");
	cout <<  endl;
}

// print just yield properties to output window
void MGSCGLMaterial::PrintYieldProperties(void)
{
	PrintProperty("yld",yield,"");
	PrintProperty("beta",beta,"");
	PrintProperty("nhard",nhard,"");
	PrintProperty("yMax",yieldMax,"");
	cout << endl;
}

// Print transport properties
void MGSCGLMaterial::PrintTransportProperties(void)
{
	// Conductivity constants
	if(ConductionTask::active)
	{	MaterialBase::PrintTransportProperties();
		PrintProperty("Cv",1000.*heatCapacityVol,"J/(kg-K)");
	}
	else
	{	PrintProperty("Cp",1000.*heatCapacity,"J/(kg-K)");
		PrintProperty("Cv",1000.*heatCapacityVol,"J/(kg-K)");
	}
	cout << endl;
}

#pragma mark MGSCGLMaterial::Custom Methods

// Find pressure using Mie-Gruneisen EOS
// Also get shear modulus here since it is not needed until after this is called
double MGSCGLMaterial::GetPressureChange(MPMBase *mptr,double &delV,int np)
{
	// 3*delV is total incremental volumetric strain relative to free-swelling volume
	// Note that swelling looks like a problem because the sums of strains needs to be adjusted
	//		to stress-free state
	
	// initial states
	Tensor *ep=mptr->GetStrainTensor();
	double x0 = -(ep->xx+ep->yy+ep->zz);
	Tensor *sptr=mptr->GetStressTensor();
	double pressure0 = -(sptr->xx+sptr->yy+sptr->zz)/3.;
	double dTemp=mptr->pPreviousTemperature-thermal.reference;
	
	// plane stress needs to adjust delV
	// Note: this calculation is based on initial state, because final state not known yet
	if(np==PLANE_STRESS_MPM)
	{	Kred = k1 + x0*(2.*k2 + 3.*k3*x0);
		double neta0=pow(1./(1.-x0),ONETHIRD);
		Gred = G0red*(1.+GPpred*pressure0/neta0 + GTp*dTemp);
		delV *= 1./(Kred/(2.*Gred) + TWOTHIRDS);			// scale by (1-2nu)/(1-nu) for plane stress
	}
	
	// M-G EOS
	double x = x0 - 3.*delV;
	double pressure = x*(k1 + x*(k2 + x*k3)) + gRhoCv*dTemp;
	
	// SCGL shear modulus
	double neta=pow(1./(1.-x),ONETHIRD);
	Gred = G0red*(1.+GPpred*pressure/neta + GTp*dTemp);
	
	// plane stress terms
	if(np==PLANE_STRESS_MPM)
	{	Kred = k1 + x*(2.*k2 + 3.*k3*x);
		double psRed0 = 1./(Kred/(2.*Gred) + TWOTHIRDS);	// (1-2nu)/(1-nu) for plane stress
		psLr2G = (Kred/(2.*Gred) - ONETHIRD)*psRed0;		// nu/(1-nu) to find ezz
		psKred = Kred*psRed0;                               // E/(3(1-v)) to find lambda
	}
	
	// return change in pressure
	return pressure-pressure0;
}

// Return yield stress for current conditions (alpint for cum. plastic strain and dalpha/delTime for plastic strain rate)
// yield = yldred*(1 + beta ep)^n * Gred/G0red, where ep=alpint
// but leading term is limited to yldMaxred
double MGSCGLMaterial::GetYield(MPMBase *mptr,int np,double delTime)
{	return fmin(yldred*pow(1.+beta*alpint,nhard),yldMaxred)*Gred/G0red;
}

// Get derivative of sqrt(2./3.)*yield with respect to lambda for plane strain and 3D
// ... and using dep/dlambda = sqrt(2./3.)
// ... and epdot = dalpha/delTime with dalpha = sqrt(2./3.)lamda or depdot/dlambda = sqrt(2./3.)/delTime
double MGSCGLMaterial::GetKPrime(MPMBase *mptr,int np,double delTime)
{	
	// slope zero if in constant max yield condition
	if(yldred*pow(1.+beta*alpint,nhard)>=yldMaxred) return 0.;
	
	// return slope
	double factor=yldred*Gred/G0red;
	double bfactor = DbleEqual(nhard,1.) ? beta :
				beta*nhard*pow(1.+beta*alpint,nhard-1.) ;
	return TWOTHIRDS*factor*bfactor;
}

// this material does not support plane stress calculations
double MGSCGLMaterial::GetK2Prime(MPMBase *mptr,double fnp1,double delTime)
{
	// slope zero if in constant max yield condition
	if(yldred*pow(1.+beta*alpint,nhard)>=yldMaxred) return 0.;

	double factor=yldred*Gred/G0red;
	return SQRT_EIGHT27THS*factor*factor*beta*nhard*pow(1.+beta*alpint,2.*nhard-1)*fnp1;
}

#pragma mark MGSCGLMaterial::Accessors

// Return the material tag
int MGSCGLMaterial::MaterialTag(void) { return MGSCGLMATERIAL; }

// return unique, short name for this material
const char *MGSCGLMaterial::MaterialType(void) { return "M-G, SGCL Material"; }

/*	calculate wave speed in mm/sec. Uses sqrt((K+4G/3)/rho) which is dilational wave speed
    K in Pa is 1000*rho*C0, G is in MPa, rho is in g/cm^3
*/
double MGSCGLMaterial::WaveSpeed(bool threeD,MPMBase *mptr) { return 1000.*sqrt(C0*C0+4000.*G/(3.*rho)); }

