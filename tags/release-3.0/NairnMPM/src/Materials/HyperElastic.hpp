/********************************************************************************
    HyperElastic.hpp
    NairnMPM
    
    Created by John Nairn on Wed Jan 24 2007.
    Copyright (c) 2007 John A. Nairn, All rights reserved.
 
    Isotropic, hyperelastic materials with subclasses to implement various
	theories

	Dependencies
		MaterialBase.hpp
********************************************************************************/

#ifndef _HYPERELASTIC_

#define _HYPERELASTIC_

#include "Materials/MaterialBase.hpp"

class HyperElastic : public MaterialBase
{
    public:
		double aI;				// thermal expansion isotropic
		// double beta;			// moisture expansion isotopic (in base material)
        
        // constructors and destructors
        HyperElastic();
        HyperElastic(char *);
        
		// Methods
		void GetDeformationGrad(double F[][3],MPMBase *,double,double,double,double,bool);
		void GetDeformationGrad(double F[][3],MPMBase *,double,double,double,double,double,double,double,double,double,bool);
		Tensor GetLeftCauchyTensor2D(double F[][3]);
		Tensor GetLeftCauchyTensor3D(double F[][3]);
		double GetResidualStretch(MPMBase *);
};

#endif
