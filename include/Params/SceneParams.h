#ifndef SceneParams_h
#define SceneParams_h

#include "AvailableParameters.h"
#include "SParam.hpp"
#include "ParamArray.hpp"

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
	ParamArray<SP_Count> onlineMean = ParamArray<SP_Count>(0.0f);
	ParamArray<SP_Count> onlineM2  = ParamArray<SP_Count>(0.0f);

	// Random number generators
	std::default_random_engine randomGenerator;
	std::uniform_real_distribution<float> unitUniformDistribution{};
	std::normal_distribution<float> unitNormalDistribution{};

	// Available Parameters
	SParam **AllParams = (SParam **)malloc(SP_Count * sizeof(SParam *));

	// The current global "mean" parameter vector
	ParamArray<SP_Count> paramMeans;
	ParamArray<SP_Count> paramVariances = ParamArray<SP_Count>(1.0f);

	// deviance is a multiplier applied to the variance of each parameter
	ParamArray<SP_Count> generate(float deviance);

	// Total random (valid) parameter
	ParamArray<SP_Count> randomSP();

	// Move paramMeans towards/away from sp
	void moveMeans(ParamArray<SP_Count> sp, bool towards);

	// Increase the variance so that learning is quick again
	void changeVariability(float modifier);

	// Updates the global variance so far
	void updateVariance(ParamArray<SP_Count> sp);

	// Reset variance to highest possible level
	void resetVariability();

	/*
	* Constructor and Destructor
	*/
	SceneParams();
    SceneParams(unsigned int seed);
	~SceneParams();
};
}

#endif // SceneParams_h
