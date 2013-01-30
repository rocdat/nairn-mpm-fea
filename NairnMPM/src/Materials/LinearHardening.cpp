/********************************************************************************
    LinearHardening.hpp
    NairnMPM

    Created by John Nairn, 1/17/2103
    Copyright (c) 2013 John A. Nairn, All rights reserved.

    Hardening Law is
        sigma = yield (1 + K ep)
        Use zero to get elastic plastic
 
    Previous code used yield + Ep ep   or   yield*K = Ep
        It also allowed entry of ET which was coverted to Ep=E ET/(E-ET)
        or 1/K = yield((1/ET) - (1/E)). The switch had to be made because
        this law can be used with materials that do not define E
********************************************************************************/

#include "Materials/LinearHardening.hpp"

#pragma mark LinearHardening::Constructors and Destructors

// Constructors
LinearHardening::LinearHardening() {}

// Constructors
LinearHardening::LinearHardening(MaterialBase *pair) : HardeningLawBase(pair)
{
    beta = 0.;
    Ep = -1.;
}

#pragma mark LinearHardening::Initialize

// Read hardening law properties
char *LinearHardening::InputMat(char *xName,int &input)
{
    // dimensionless coefficient for hardening
    if(strcmp(xName,"Khard")==0)
    {   input=DOUBLE_NUM;
        return((char *)&beta);
    }

    else if(strcmp(xName,"Ep")==0)
    {   input=DOUBLE_NUM;
        return((char *)&Ep);
    }
    
    return HardeningLawBase::InputMat(xName,input);
}

// get reduced stress than done
void LinearHardening::InitialLoadMechProps(int makeSpecific,int np)
{
    // call first to get reduced yield stress
    HardeningLawBase::InitialLoadMechProps(makeSpecific,np);
    
    // Use Ep if it was entered and is non-negative
    if(Ep >= 0.)
		beta = Ep/yield;
	else
		Ep = beta*yield;
    
	// save some multiplies (it is reduced plastic modulus)
    Epred = yldred*beta;
}

// print just yield properties to output window
void LinearHardening::PrintYieldProperties(void)
{
    cout << GetHardeningLawName() << endl;
    MaterialBase::PrintProperty("yld",yield,"");
    MaterialBase::PrintProperty("K",beta,"");
    MaterialBase::PrintProperty("Ep",Ep,"");
    cout << endl;
}

#pragma mark LinearHardening::Law Methods

// Return yield stress for current conditions (alpint for cum. plastic strain and dalpha/delTime for plastic strain rate)
double LinearHardening::GetYield(MPMBase *mptr,int np,double delTime)
{
	return yldred + Epred*alpint;
}

// Get derivative of sqrt(2./3.)*yield with respect to lambda for plane strain and 3D
// ... and using dep/dlambda = sqrt(2./3.)
// ... and epdot = dalpha/delTime with dalpha = sqrt(2./3.)lamda or depdot/dlambda = sqrt(2./3.)/delTime
double LinearHardening::GetKPrime(MPMBase *mptr,int np,double delTime)
{
	return TWOTHIRDS*Epred;
}

// Get derivative of (1./3.)*yield^2 with respect to lambda for plane stress only
// ... and using dep/dlambda = sqrt(2./3.)*fnp1 where ep=alpint
// ... and epdot = dalpha/delTime with dalpha = sqrt(2./3.)*lambda*fnp1 or depdot/dlambda = sqrt(2./3.)*fnp1/delTime
// Also equal to sqrt(2./3.)*GetYield()*GetKPrime()*fnp1, but in separate call for efficiency
double LinearHardening::GetK2Prime(MPMBase *mptr,double fnp1,double delTime)
{
	return SQRT_EIGHT27THS*(yldred + Epred*alpint)*Epred*fnp1; 
}

#pragma mark HardeningLawBase::Return Mapping

// Linear law can do return mapping analytically, except for plane stress
double LinearHardening::SolveForLambdaBracketed(MPMBase *mptr,int np,double strial,Tensor *stk,double Gred,double psKred,double Ptrial,double delTime)
{
	// plane stress is numerical
	if(np==PLANE_STRESS_MPM)
    {   // The unbracketed one is faster and seems stable for this hardening law
        return HardeningLawBase::SolveForLambda(mptr,np,strial,stk,Gred,psKred,Ptrial,delTime);
    }
    
	// closed form for plane strain and 3D
	double lambdak = (strial - SQRT_TWOTHIRDS*(yldred + Epred*alpint))/(2.*(Gred + Epred/3.));
	UpdateTrialAlpha(mptr,np,lambdak,(double)1.);
	return lambdak;
}

// Linear law can do return mapping analytically, except for plane stress
double LinearHardening::HESolveForLambdaBracketed(MPMBase *mptr,int np,double strial,double Gred,double Ie1bar)
{
	// plane stress is not supported yet
	if(np==PLANE_STRESS_MPM) return 0.0;
	
    // Find  lambda for this plastic state
	double lambdak = (strial - SQRT_TWOTHIRDS*(yldred + Epred*alpint))/(2.*(Gred*Ie1bar + Epred/3.));
	UpdateTrialAlpha(mptr,np,lambdak,(double)1.);
	return lambdak;
}

#pragma mark LinearHardening::Accessors

// hardening law name
const char *LinearHardening::GetHardeningLawName(void) { return "Linear hardening"; }
