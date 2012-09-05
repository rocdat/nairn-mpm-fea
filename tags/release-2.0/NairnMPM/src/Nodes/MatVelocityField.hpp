/********************************************************************************
    MatVelocityField.hpp
    NairnMPM
    
    Created by John Nairn on 3 April 2009.
    Copyright (c) 2009 John A. Nairn, All rights reserved.
	
	Dependencies
		none
********************************************************************************/

#ifndef _MATVELOCITYFIELD_

#define _MATVELOCITYFIELD_

#define MAX_FIELDS_FOR_CRACKS 4

class MatVelocityField
{
	public:
		int numberPoints;			// number of material points in this field
		double mass;				// total mass of this field
		Vector pk;					// momentum
		Vector vk;					// velocity
		Vector fint;				// internal force
		Vector fext;				// external force
		Vector ftot;				// total force
		Vector disp;				// displacement for contact calculations
		Vector *massGrad;			// mass gradient allocated in multimaterial mode
				
        // constructors and destructors
        MatVelocityField();
		~MatVelocityField();
		void Zero(void);
		
		// methods
		void AddMomentumTask1(Vector *,Vector *);
		void ChangeMatMomentum(Vector *,bool,double);
		void CalcVelocityForStrainUpdate(void);
		void CalcFtotTask3(double);
	
		// accessors
		void Describe(void);
	
		// class methods
		static bool ActiveField(MatVelocityField *);
		static bool ActiveNonrigidField(MatVelocityField *mvf);
		static bool ActiveRigidField(MatVelocityField *mvf);
	
	private:
};

#endif