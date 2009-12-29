/********************************************************************************
	CrackVelocityFieldMulti.hpp
	NairnMPM
 
	Created by John Nairn on 11 August 2009.
	Copyright (c) 2009 John A. Nairn, All rights reserved.
 
	Dependencies
		CrackVelocityField.hpp, MatVelocityField.hpp
********************************************************************************/

#ifndef _CRACKVELOCITYFIELDMULTI_

#define _CRACKVELOCITYFIELDMULTI_

#include "Nodes/CrackVelocityField.hpp"

class CrackVelocityFieldMulti : public CrackVelocityField
{
	public:
		
        // constructors and destructors
		CrackVelocityFieldMulti(short,int);
		virtual void ZeroMatFields(void);
	
		// specific task methods
		virtual double GetTotalMassTask1(void);
		virtual void AddMassGradient(int,double,double,double,double,MPMBase *);
	
		virtual void AddFintSpreadTask3(Vector *);
		virtual void AddFextSpreadTask3(Vector *);
		virtual void CalcFtotTask3(double);
	
		virtual void UpdateMomentaTask4(double);
	
		virtual void RezeroNodeTask6(void);
	
		virtual void MaterialContact(int,int,bool,double);
		virtual void GetMassGradient(int,Vector *,double);
		virtual void CalcVelocityForStrainUpdate(void);
	
		// boundary conditions
		virtual void SetXMomVel(void);
		virtual void SetYMomVel(void);
		virtual void SetZMomVel(void);
		virtual void SetSkewMomVel(double);
		virtual void AddXMomVel(double);
		virtual void AddYMomVel(double);
		virtual void AddZMomVel(double);
		virtual void AddSkewMomVel(double,double);
		virtual void SetXFtot(double);
		virtual void SetYFtot(double);
		virtual void SetZFtot(double);
		virtual void SetSkewFtot(double,double);
		virtual void AddXFtot(double,double);
		virtual void AddYFtot(double,double);
		virtual void AddZFtot(double,double);
		virtual void AddSkewFtot(double,double,double);
	
		// accessors
		virtual double GetTotalMass(void);
		virtual double GetMass(int);
		virtual Vector GetCMatMomentum(void);
		virtual Vector GetCMDisplacement(void);
		virtual Vector GetCMatFtot(void);
		virtual void ChangeMomentum(Vector *,bool,double);
		virtual int CopyFieldMomenta(Vector *,int);
		virtual int PasteFieldMomenta(Vector *,int);
	
	private:
		int numberMaterials;		// number of materials in this crack velocity field

};

#endif