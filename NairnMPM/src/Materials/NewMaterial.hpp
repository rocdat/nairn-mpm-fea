/********************************************************************************
    NewMaterial.hpp
    NairnMPM
    
    Created by John Nairn, July 13, 2008.
    Copyright (c) 2008 John A. Nairn, All rights reserved.

	Dependencies
		MaterialBase.hpp
	
	Creating a New Material
	 1. Replace NEWMATERIAL with unigue tag for this header file
	     and give it a unique number among all materials
	 2. Replace "NewMaterial" with class name for the new material
	 3. Replace MaterialBase with the actual parent class material
	     (if different)
********************************************************************************/

#ifndef NEWMATERIAL

#define NEWMATERIAL 100

#include "Materials/MaterialBase.hpp"

class NewMaterial : public MaterialBase
{
    public:
		// unique properties
		double newproperty;
        
        // constructors and destructors
		NewMaterial();
		NewMaterial(char *matName);
		
		// initialize
        virtual char *InputMat(char *,int &);
        virtual const char *VerifyProperties(int);
		virtual void ValidateUse(int);
		virtual void InitialLoadMechProps(int,int);
		virtual void PrintMechanicalProperties(void);
        //virtual char *MaterialData(void);
		//virtual void InitialLoadTransProps(void);
		//virtual void PrintTransportProperties(void);
		
		// methods
        //virtual void LoadMechanicalProps(MPMBase *,int);
		//virtual void LoadTransportProps(MPMBase *);
		//virtual double GetHeatCapacity(MPMBase *);
        virtual void MPMConstLaw(MPMBase *,double,double,double,double,double,int);
		virtual void MPMConstLaw(MPMBase *,double,double,double,double,double,double,double,double,double,double,int);
				
		// accessors
		virtual const char *MaterialType(void);
		virtual int MaterialTag();
		virtual bool ThreeDMaterial(void);
		//virtual double GetHistory(int,char *);
        virtual double WaveSpeed(void) = 0;
		//virtual double ShearWaveSpeed(void);
		//virtual double MaximumDiffusion(void);
        //virtual double MaximumDiffusivity(void);
		
    protected:

};

#endif
