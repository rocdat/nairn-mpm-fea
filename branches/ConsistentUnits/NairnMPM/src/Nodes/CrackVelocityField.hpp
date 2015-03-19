/********************************************************************************
	CrackVelocityField.hpp
	nairn-mpm-fea
 
	Created by John Nairn on 11 August 2009.
	Copyright (c) 2009 John A. Nairn, All rights reserved.
 
	Dependencies
		MatVelocityField.hpp
********************************************************************************/

#ifndef _CRACKVELOCITYFIELD_

#define _CRACKVELOCITYFIELD_

#define FIRST_CRACK 0
#define SECOND_CRACK 1

#define MASS_MOMENTUM_CALL 1
#define UPDATE_MOMENTUM_CALL 2
#define UPDATE_STRAINS_LAST_CALL 4

#include "Nodes/MatVelocityField.hpp"

class MPMBase;
class NodalPoint;

class CrackVelocityField
{
	public:
		// variables (changed in MPM time step)
		short loc[2];				// crack location's
		int crackNum[2];			// crack number's/crackNum[0] used for total particles when moving crack planes by ctr mass
		Vector norm[2];				// crack normal's/norm[0] used for velocity when moving crack planes by ctr mass
		DispField *df;				// For J and K calculations
		
		// constants (not changed in MPM time step)
	
		// constructors and destructors
        CrackVelocityField(short,int);
        virtual ~CrackVelocityField();
		virtual void Zero(short,int,bool);
		virtual void ZeroMatFields() = 0;
		virtual void AddMatVelocityField(int);
        virtual bool NeedsMatVelocityField(int) const;
		virtual void MatchRealFields(CrackVelocityField *);
		virtual void MatchMatVelocityFields(MatVelocityField **);
		
		// specific task methods
		virtual void AddMomentumTask1(int,Vector *,Vector *,int);
		virtual void AddMass(int,double);
		virtual void AddMassTask1(int,double,int);
		virtual double GetTotalMassAndCount(void) = 0;
		virtual void AddVolumeGradient(int,MPMBase *,double,double,double);
		virtual void CopyVolumeGradient(int,Vector *);
		virtual void CopyMassAndMomentum(NodalPoint *,int);
        virtual void CopyMassAndMomentumLast(NodalPoint *,int);
        virtual void RezeroNodeTask6(double) = 0;
        void AddMomentumTask6(int,double,Vector *);
	
		void AddFtotTask3(int,Vector *);
		virtual void CopyGridForces(NodalPoint *,int);
		virtual void AddFtotSpreadTask3(Vector *) = 0;
	
		virtual void UpdateMomentaOnField(double) = 0;
	
		void IncrementDelvaTask5(int,double,Vector *,Vector *) const;
	
		void CreateStrainField(void);
		void DeleteStrainField(void);
		
		short IncrementDelvTask8(double,Vector *,double *);
		int CollectMomentaTask8(Vector *,double *) const;
		void SetCMVelocityTask8(Vector *,int);
		bool GetCMVelocityTask8(Vector *) const;
	
		void AddNormals(Vector *,int);
		void AddDisplacement(int,double,Vector *);
		void AddVolume(int,double);
	
		// methods
		virtual void MaterialContactOnCVF(NodalPoint *,int,double,int,MaterialInterfaceNode **,MaterialInterfaceNode **);
		virtual bool HasVolumeGradient(int) const;
		virtual void GetVolumeGradient(int,const NodalPoint *,Vector *,double) const;
		virtual void CalcVelocityForStrainUpdate(void) = 0;
		virtual void AdjustForSymmetry(NodalPoint *,Vector *,bool) const;
	
		// boundary conditions
        virtual void SetMomVel(Vector *) = 0;
        virtual void AddMomVel(Vector *,double) = 0;
		virtual void ReflectMomVel(Vector *,CrackVelocityField *) = 0;
        virtual void SetFtotDirection(Vector *,double,Vector *) = 0;
        virtual void AddFtotDirection(Vector *,double,double,Vector *) = 0;
		virtual void ReflectFtotDirection(Vector *,double,CrackVelocityField *,Vector *) = 0;
	
		// accessors
		short location(int);
		int crackNumber(int);
		bool crackAndLocation(int,int,int);
		int OppositeCrackTo(int,int,int *);
		void SetLocationAndCrack(short,int,int);
		MatVelocityField **GetMaterialVelocityFields(void);
		virtual double GetTotalMass(bool) const = 0;
		virtual void AddKineticEnergyAndMass(double &,double &) = 0;
		virtual double GetVolumeNonrigid(void) = 0;
		virtual double GetVolumeTotal(NodalPoint *) const = 0;
		virtual Vector GetCMatMomentum(bool &,double *) const = 0;
		virtual Vector GetCMDisplacement(NodalPoint *) const = 0;
		virtual Vector GetCMatFtot(void) = 0;
		virtual void ChangeCrackMomentum(Vector *,bool,double) = 0;
		virtual int CopyFieldMomenta(Vector *,int) = 0;
		virtual int PasteFieldMomenta(Vector *,int) = 0;
		Vector GetVelocity(int);
		Vector GetContactForce(int);
		virtual int GetNumberPoints(void);
		virtual void SetNumberPoints(int);
		virtual int GetNumberPointsNonrigid(void);
		virtual bool HasPointsNonrigid(void) const;
		virtual void Describe(void) const;
		virtual void SumAndClearRigidContactForces(Vector *,bool);
	
		// class methods
		static bool ActiveField(CrackVelocityField *);
        static bool ActiveCrackField(CrackVelocityField *);
		static bool ActiveNonrigidField(CrackVelocityField *cvf);
		static bool ActiveNonrigidField(CrackVelocityField *,int);
		static CrackVelocityField *CreateCrackVelocityField(int,short,int);
	
	protected:
		// variables (changed in MPM time step)
		int numberPoints;			// total number of materials points in this field/field [0] changed to sum of all in task 8
		MatVelocityField **mvf;		// material velocity fields
        bool hasCrackPoints;        // shows a particle sees this field during initialization
		// unscaled nonrigid volume (ignores dilation) only used for imperfect interface forces and material contact
		// unscaleRigidVolume is due to rigid contaft materials (type 8) (always zero unless multimaterial mode)
};

#endif
