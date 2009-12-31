/********************************************************************************
	CrackVelocityField.hpp
	NairnMPM
 
	Created by John Nairn on 11 August 2009.
	Copyright (c) 2009 John A. Nairn, All rights reserved.
 
	Dependencies
		MatVelocityField.hpp
********************************************************************************/

#ifndef _CRACKVELOCITYFIELD_

#define _CRACKVELOCITYFIELD_

#define FIRST_CRACK 0
#define SECOND_CRACK 1

#include "Nodes/MatVelocityField.hpp"

class MPMBase;

class CrackVelocityField
{
	public:
		int numberPoints;			// total number of materials points in this field/field [0] change to summ of all in task 8
	
		short loc[2];				// crack location's
		int crackNum[2];			// crack number's
		Vector norm[2];				// crack normal's/norm[0] used for velocity when moving crack planes
		double unscaledVolume;		// unscaled volume (ignores dilation) only used for imperfect interface forces
		DispField *df;				// For J and K calculations
		
        // constructors and destructors
        CrackVelocityField(short,int);
        virtual ~CrackVelocityField();
		void Zero(short,int,bool);
		virtual void ZeroMatFields() = 0;
		
		// specific task methods
		void AddMomentumTask1(int,Vector *,Vector *);
		void AddMassTask1(int,double);
		virtual double GetTotalMassTask1(void) = 0;
		virtual void AddMassGradient(int,double,double,double,double,MPMBase *);
	
		void AddFintTask3(int,Vector *);
		virtual void AddFintSpreadTask3(Vector *) = 0;
		void AddFextTask3(int,Vector *);
		virtual void AddFextSpreadTask3(Vector *) = 0;
		virtual void CalcFtotTask3(double) = 0;
	
		virtual void UpdateMomentaTask4(double) = 0;
	
		void IncrementDelvaTask5(int,double,Vector *,Vector *);
	
		virtual void RezeroNodeTask6(void) = 0;
		void AddMomentumTask6(int,double,Vector *);
	
		void CreateStrainField(void);
		void DeleteStrainField(void);
		
		short IncrementDelvTask8(double,Vector *,double);
		int CollectMomentaTask8(Vector *);
		void SetCMVelocityTask8(Vector *,int);
		bool GetCMVelocityTask8(Vector *);
	
		// methods
		virtual void MaterialContact(int,int,bool,double);
		virtual void GetMassGradient(int,Vector *,double);
		void AddNormals(Vector *,int);
		void AddDisplacement(int,double,Vector *);
		void AddUnscaledVolume(double);
		virtual void CalcVelocityForStrainUpdate(void) = 0;
	
		// boundary conditions
		virtual void SetXMomVel(void) = 0;
		virtual void SetYMomVel(void) = 0;
		virtual void SetZMomVel(void) = 0;
		virtual void SetSkewMomVel(double) = 0;
		virtual void AddXMomVel(double) = 0;
		virtual void AddYMomVel(double) = 0;
		virtual void AddZMomVel(double) = 0;
		virtual void AddSkewMomVel(double,double) = 0;
		virtual void SetXFtot(double) = 0;
		virtual void SetYFtot(double) = 0;
		virtual void SetZFtot(double) = 0;
		virtual void SetSkewFtot(double,double) = 0;
		virtual void AddXFtot(double,double) = 0;
		virtual void AddYFtot(double,double) = 0;
		virtual void AddZFtot(double,double) = 0;
		virtual void AddSkewFtot(double,double,double) = 0;
	
		// accessors
		short location(int);
		int crackNumber(int);
		int OppositeCrackTo(int,int);
		void SetLocationAndCrack(short,int,int);
		virtual double GetTotalMass(void) = 0;
		virtual double GetMass(int) = 0;
		virtual Vector GetCMatMomentum(void) = 0;
		virtual Vector GetCMDisplacement(void) = 0;
		virtual Vector GetCMatFtot(void) = 0;
		virtual void ChangeMomentum(Vector *,bool,double) = 0;
		virtual int CopyFieldMomenta(Vector *,int) = 0;
		virtual int PasteFieldMomenta(Vector *,int) = 0;
		Vector GetVelocity(int);
		void Describe(void);
	
		// class methods
		static bool ActiveField(CrackVelocityField *);
		static CrackVelocityField *CreateCrackVelocityField(short,int);
	
	protected:
		MatVelocityField **mvf;		// material velocity fields
};

#endif