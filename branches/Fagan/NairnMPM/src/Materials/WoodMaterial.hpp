/********************************************************************************
	WoodMaterial.hpp
	NairnMPM
 
	Created by John Nairn on 6/4/10.
	Copyright 2010 Oregon State University. All rights reserved.
 
	Dependencies
		HillPlastic.hpp (AnisoPlasticity.hpp Orthotropic.hpp TranIsotropic.hpp
			Elastic.hpp MaterialBase.hpp)
********************************************************************************/

#ifndef WOODMATERIAL

#define WOODMATERIAL 19

#include "Materials/HillPlastic.hpp"

class WoodMaterial : public HillPlastic
{
	public:
		// unique properties
		
		// constructors and destructors
		WoodMaterial();
		WoodMaterial(char *matName);
		
		// initialize
		virtual char *InputMat(char *,int &);
		virtual const char *VerifyProperties(int);
		virtual void InitialLoadMechProps(int,int);
		virtual void PrintMechanicalProperties(void);
		
		// methods
		virtual void LoadMechanicalProps(MPMBase *,int);
		
		// accessors
		virtual const char *MaterialType(void);
		virtual int MaterialTag();
		
	protected:
	double tempC1,tempC2,currentRatio;
	
};

#endif

