#ifndef SceneParams_h
#define SceneParams_h

#include "AvailableParameters.h"
#include "SParam.hpp"

#include <algorithm>
#include <math.h>
#include <random>
#include <vector>
#include <iomanip>
#include <string>
#include <map>
#include <cmath>

#define MATH_FLOAT_PI 3.1415926f
namespace ParamWorld {

class SceneParams
{
public:

	// Learning rate and its decay and minimum
	float learningRate = 0.75f; // initial
	float learningDecay = 1.0f - 0.001f;
	float learningMaximum = 0.5f;
	float learningMinimum = 0.1f;
	float maximumVariance = 1.5f;

	// Variance calculation, online
	float nSavedChoices = 0.0f;
	float onlineDelta[SP_Count];
	float onlineDeltaN[SP_Count];
	float onlineMean[SP_Count];
	float onlineDelta2[SP_Count];
	float onlineM2Right[SP_Count];
	float onlineM2[SP_Count];

	// Random number generators
	std::default_random_engine randomGenerator;
	std::uniform_real_distribution<float> unitUniformDistribution{};
	std::normal_distribution<float> unitNormalDistribution{};

	// Available Parameters
	SParam **AllParams = (SParam **)malloc(SP_Count * sizeof(SParam *));

	// The current global "mean" parameter vector
	float paramMeans[SP_Count];
	float paramVariances[SP_Count];

	// deviance is a multiplier applied to the variance of each parameter
	float *generate(float deviance);

	// Total random (valid) parameter
	float *randomSP();

	// Move paramMeans towards/away from sp
	void moveMeans(float *sp, bool towards);

	// Increase the variance so that learning is quick again
	void changeVariability(float modifier);

	// Updates the global variance so far
	void updateVariance(float *sp);

	// Reset variance to highest possible level
	void resetVariability();

	/*
	* Mathematical functions
	*/
	void vectMinus(float *v1, float *v2, float *diff);
	void vectAdd(float *v1, float *v2, float *sum);
	void vectProd(float *v1, float *v2, float *prod);
	void vectProdScalar(float *v1, float c, float *prod);
	void vectDiv(float *v1, float *v2, float *quot);
	void vectDivScalar(float *v1, float c, float *quot);
	float l2_norm(float *v);

	/*
	* Constructor and Destructor
	*/
	SceneParams();
    SceneParams(unsigned int seed);
	~SceneParams();
};
}

#endif // SceneParams_h
