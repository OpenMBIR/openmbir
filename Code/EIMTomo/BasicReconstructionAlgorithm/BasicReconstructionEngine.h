/*
 *  ComputationEngineOptimized.h
 *  HAADFSTEM_Xcode
 *
 *  Created by Singanallur Venkatakrishnan on 6/29/11.
 *  Copyright 2011 Purdue University. All rights reserved.
 *
 */

#ifndef COMPUTATIONENGINE_H_
#define COMPUTATIONENGINE_H_


#include "EIMTomo/EIMTomo.h"

#include "BasicReconstructionStructures.h"
#include "BasicReconstructionInputs.h"


	//#define DEBUG
#define PROFILE_RESOLUTION 1536
//#define PI 4*atan(1)//3.14159265
	//Beam Parameters - This is set to some number <<< Sinogram->delta_r.
//#define BEAM_WIDTH 0.050000
#define BEAM_RESOLUTION 512
#define AREA_WEIGHTED
//#define ROI //Region Of Interest
	//#define DISTANCE_DRIVEN
	//#define CORRECTION
//#define STORE_A_MATRIX
//	#define WRITE_INTERMEDIATE_RESULTS
#define COST_CALCULATE
#define BEAM_CALCULATION
#define DETECTOR_RESPONSE_BINS 64
#ifdef CORRECTION
	double *NORMALIZATION_FACTOR;
#endif

class BREngine
{
  public:
	    BREngine();
	    virtual ~BREngine();

	void CE_CalculateSinCos(Sino*);
	void CE_InitializeBeamProfile(Sino*);
	void CE_MinMax(double*,double*);
	void* CE_CalculateVoxelProfile(Sino*,Geom*);
	int CE_MAPICDReconstruct(Sino*,Geom*,CommandLineInputs*);
	void* CE_CalculateAMatrixColumn(uint16_t ,uint16_t , uint16_t ,Sino* ,Geom* ,double**);
	double CE_DerivOfCostFunc(double);
	double CE_ComputeCost(double***  ,double***  ,Sino* ,Geom* );
	void* CE_CalculateAMatrixColumnPartial(uint16_t,uint16_t,uint16_t,Sino*,Geom*,double***);
//	void* CE_CalculateAMatrixColumnPartial(uint16_t,uint16_t,Sino*,Geom*,double**);
	void* CE_DetectorResponse(uint16_t ,uint16_t ,Sino* ,Geom* ,double**);

	void ForwardProject(Sino *Sinogram,Geom* Geom);


	template<class Functor>
	double  solve(
	        Functor* f, /* pointer to function to be solved */
	        double a,      /* minimum value of solution */
	        double b,      /* maximum value of solution */
	        double err,    /* accuarcy of solution */
	        int *code      /* error code */
	        )
	/* Solves equation (*f)(x) = 0 on x in [a,b]. Uses half interval method.*/
	/* Requires that (*f)(a) and (*f)(b) have opposite signs.   */
	/* Returns code=0 if signs are opposite.        */
	/* Returns code=1 if signs are both positive.         */
	/* Returns code=-1 if signs are both negative.        */
	{
	  int     signa,signb,signc;
	  double  fa,fb,fc,c,signaling_nan();
	  double  dist;

	  fa = f->execute(a);
	  signa = fa>0;
	  fb = f->execute(b);
	  signb = fb>0;

	  /* check starting conditions */
	  if( signa==signb ) {
	    if(signa==1) *code = 1;
	    else *code = -1;
	    return(0.0);
	  }
	  else *code = 0;

	  /* half interval search */
	  if( (dist=b-a)<0 ) dist = -dist;
	  while(dist>err) {
	    c = (b+a)/2;
	    fc = f->execute(c);  signc = fc>0;
	    if(signa == signc) { a = c; fa = fc; }
	    else { b = c; fb = fc; }
	    if( (dist=b-a)<0 ) dist = -dist;
	  }

	  /* linear interpolation */
	  if( (fb-fa)==0 ) return(a);
	  else {
	    c = (a*fb - b*fa)/(fb-fa);
	    return(c);
	  }
	}


private:
	bool CE_Cancel;
	//Markov Random Field Prior parameters - Globals -:(
	double FILTER[3][3][3];
	double THETA1;
	double THETA2;
	double NEIGHBORHOOD[3][3][3];
	double V;
	double MRF_P ;//= 1.1;
	double SIGMA_X_P;

	double* cosine;
	double* sine;//used to store cosine and sine of all angles through which sample is tilted
	double* BeamProfile;//used to store the shape of the e-beam
	double BEAM_WIDTH;
	double OffsetR;
	double OffsetT;

	BREngine(const BREngine&); // Copy Constructor Not Implemented
  void operator=(const BREngine&); // Operator '=' Not Implemented

};
#endif //CompEngine
