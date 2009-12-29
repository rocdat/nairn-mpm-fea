/********************************************************************************
    Quad2D.hpp
    NairnFEA
    
    Created by John Nairn on Fri Oct 22 2004.
    Copyright (c) 2004 John A. Nairn, All rights reserved.
	
	Dependencies
		ElementBase.hpp
********************************************************************************/

#ifndef _QUAD2D_

#define _QUAD2D_

#include "Elements/ElementBase.hpp"

class Quad2D : public ElementBase
{
    public:
        double thickness;
        
        // constructors
        Quad2D(long,long *,int,double,double);
        
        // prototypes
		virtual int FaceNodes(void);
        virtual double GetArea(void);
		virtual double GetVolume(void);
        virtual short PtInElement(Vector &);
        virtual double GetThickness(void);
		virtual void CalcEdgeLoads(double *,int,int,double *,int);
		virtual void MakeQuarterPointNodes(int,vector<int> &);
		virtual void AdjustMidSideNode(int,int,int,vector<int> &);
};

#endif
