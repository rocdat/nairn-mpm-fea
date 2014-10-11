/********************************************************************************
    HyperElastic.hpp
    NairnMPM
    
    Created by John Nairn on Wed Jan 24 2007.
    Copyright (c) 2007 John A. Nairn, All rights reserved.
 
    Base class for all Hyperelastic materials. It should have methods common
    to all.

	Dependencies
		MaterialBase.hpp
********************************************************************************/

#ifndef _HYPERELASTIC_

#define _HYPERELASTIC_

#include "Materials/MaterialBase.hpp"

enum { HALF_J_SQUARED_MINUS_1_MINUS_LN_J=0,J_MINUS_1_SQUARED,LN_J_SQUARED };

class HyperElastic : public MaterialBase
{
    public:
        double Kbulk;               // bulk modulus
		double aI;                  // thermal expansion isotropic
        int UofJOption;             // pick U(J) function
		// double betaI;			// moisture expansion isotopic (in base material)
        
        // constructors and destructors
        HyperElastic();
        HyperElastic(char *);
    
        // initialize
        virtual char *InputMat(char *,int &);
        virtual void SetInitialParticleState(MPMBase *,int);
        virtual void InitialLoadMechProps(int,int);
    
		// Methods (make virtual if any subclass needs them)
        double IncrementDeformation(MPMBase *,double,double,double,double,double,Tensor *);
        double IncrementDeformation(MPMBase *,double,double,double,double,double,double,double,double,double,Tensor *);
		double GetResidualStretch(MPMBase *);
    
        // Accessors
        virtual double GetVolumetricTerms(double,double *);
        virtual double GetCurrentRelativeVolume(MPMBase *);
    
    protected:
        double Ksp;                 // specific bulk modulus
};

#endif
