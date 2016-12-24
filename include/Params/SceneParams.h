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
	void resetVariability()
	{
		for (int i = 0; i < SP_Count; i++)
		{
			paramVariances[i] = maximumVariance;
		}
		learningRate = learningMaximum;
	}

	/*
	* Mathematical functions
	*/
	void vectMinus(float *v1, float *v2, float *diff)
	{
		for (int i = 0; i < SP_Count; i++)
		{
			diff[i] = v1[i] - v2[i];
		}
	}

	void vectAdd(float *v1, float *v2, float *sum)
	{
		for (int i = 0; i < SP_Count; i++)
		{
			sum[i] = v1[i] + v2[i];
		}
	}

	void vectProd(float *v1, float *v2, float *prod)
	{
		for (int i = 0; i < SP_Count; i++)
		{
			prod[i] = v1[i] * v2[i];
		}
	}

	void vectProdScalar(float *v1, float c, float *prod)
	{
		for (int i = 0; i < SP_Count; i++)
		{
			prod[i] = v1[i] * c;
		}
	}

	void vectDiv(float *v1, float *v2, float *quot)
	{
		for (int i = 0; i < SP_Count; i++)
		{
			quot[i] = v1[i] / v2[i];
		}
	}

	void vectDivScalar(float *v1, float c, float *quot)
	{
		for (int i = 0; i < SP_Count; i++)
		{
			quot[i] = v1[i] / c;
		}
	}

	float l2_norm(float *v)
	{
		float sum = 0;
		for (int i = 0; i < SP_Count; i++)
		{
			sum += v[i] * v[i];
		}
		return sqrt(sum);
	}

	/*
	* Constructor and Destructor
	*/
	SceneParams();

	~SceneParams();
};
}

#endif // SceneParams_h
