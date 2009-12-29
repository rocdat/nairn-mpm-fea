/********************************************************************************
    MatPoint3D.hpp
    NairnMPM
    
    Created by John Nairn on 7/21/06.
    Copyright (c) 2006 John A. Nairn, All rights reserved.
	
	Dependencies
		MPMBase.hpp
********************************************************************************/

#ifndef _MATPOINT3D_

#define _MATPOINT3D_

#include "MPM_Classes/MPMBase.hpp"

class MatPoint3D : public MPMBase
{
    public:
        // constructors and destructors
        MatPoint3D();
        MatPoint3D(int,int,double);
        
        // methods
		virtual void SetOrigin(Vector *);
        virtual void SetPosition(Vector *);
        virtual void SetVelocity(Vector *);
        virtual double thickness(void);
		virtual void SetDilatedVolume(void);
		virtual void UpdateStrain(double,int,int);
		virtual Vector Fint(double,double,double);
		virtual Vector Fext(double fni);
		virtual void MovePosition(double,Vector *);
		virtual void MoveVelocity(double,double,Vector *);
		virtual void SetVelocitySpeed(double);
		virtual void AddTemperatureGradient(void);
		virtual void AddTemperatureGradient(Vector *);
		virtual double FCond(double,double,double);
		virtual void AddConcentrationGradient(void);
		virtual void AddConcentrationGradient(Vector *);
		virtual double FDiff(double,double,double);
};

#endif
