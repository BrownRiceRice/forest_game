#ifndef SceneParams_h
#define SceneParams_h

#include "AvailableParameters.h"
#include "SParam.h"

#include <algorithm>
#include <math.h>
#include <random>
#include <vector>
#include <iomanip>
#include <string>
#include <map>
#include <cmath>

#define MATH_FLOAT_PI 3.1415926f

using namespace ParamWorld;

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
	float *generate(float deviance)
	{
		float *newVec = (float *)malloc(SP_Count * sizeof(float));
		for (int i = 0; i < SP_Count; i++)
		{
			newVec[i] = AllParams[i]->generateGaussian(paramMeans[i], paramVariances[i] * deviance, unitNormalDistribution);
		}
		return newVec;
	}

	// Total random (valid) parameter
	float *randomSP()
	{
		float *newVec = (float *)malloc(SP_Count * sizeof(float));
		for (int i = 0; i < SP_Count; i++)
		{
			newVec[i] = AllParams[i]->generateUniform(unitUniformDistribution(randomGenerator));
		}
		return newVec;
	}

	// Move paramMeans towards/away from sp
	void moveMeans(float *sp, bool towards)
	{
		updateVariance(sp);

		// Calculate z-Scores
		float *diffs = (float *)malloc(SP_Count * sizeof(float));
		float *zScores = (float *)malloc(SP_Count * sizeof(float));
		vectMinus(sp, paramMeans, diffs);
		vectDiv(diffs, paramVariances, zScores);

		// Map zScores => max(1, abs(zScores))
		for (int i = 0; i < SP_Count; i++)
		{
			float z = zScores[i];
			if (z < 1.0f)
			{
				if (z >= -1.0f)
				{
					zScores[i] = 1;
				}
				else
				{
					zScores[i] = -z;
				}
			}
		}

		// Increase variances of far away params
		//vectProd(zScores, paramVariances, paramVariances);

		// Move mean toward vector, also reuse zScores
		vectProdScalar(diffs, learningRate, diffs);
		if (towards)
		{
			vectAdd(paramMeans, diffs, paramMeans);
		}
		else
		{
			vectMinus(paramMeans, diffs, paramMeans);
		}

		// Update learning rates
		learningRate = std::max(learningMinimum, learningRate * learningDecay);
	}

	// Increase the variance so that learning is quick again
	void changeVariability(float modifier)
	{
		vectProdScalar(paramVariances, modifier, paramVariances);
		learningRate = std::max(std::min(learningRate * modifier, learningMaximum), learningMinimum);
	}

	// Updates the global variance so far
	void updateVariance(float *sp)
	{
		nSavedChoices += 1;

		// For too few data points, no real variance
		if (nSavedChoices < 2)
		{
			return;
		}

		// Welford Algorithm
		vectMinus(sp, onlineMean, onlineDelta);
		vectDivScalar(onlineDelta, nSavedChoices, onlineDeltaN);
		vectAdd(onlineMean, onlineDeltaN, onlineMean);
		vectMinus(sp, onlineMean, onlineDelta2);
		vectProd(onlineDelta, onlineDelta2, onlineM2Right);
		vectAdd(onlineM2, onlineM2Right, onlineM2);
		vectDivScalar(onlineM2, nSavedChoices - 1, paramVariances);
	}

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
	SceneParams()
	{

		randomGenerator.seed(((unsigned int)time(NULL)));
		// Colors
		AllParams[SP_Red] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_Green] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_Blue] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_Alpha] = new SParam(false, 0.0f, 1.0f);

		AllParams[SP_Depth] = new SParam(true, 1.0f, 8.0f);
		AllParams[SP_Width] = new SParam(false, 0.1f, 2.0f);
		AllParams[SP_Height] = new SParam(false, 0.2f, 20.0f);
		AllParams[SP_Scale] = new SParam(false, 0.1f, .98f);
		AllParams[SP_SplitAngle] = new SParam(false, 0.1f, MATH_FLOAT_PI/4);
		AllParams[SP_BranchR] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_BranchG] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_BranchB] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_LeafR] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_LeafG] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_LeafB] = new SParam(false, 0.0f, 1.0f);
		AllParams[SP_LeafSize] = new SParam(false, 0.5f, 2.0f);

		// Initialize variances to 1
		for (int i = 0; i < SP_Count; i++)
		{
			paramVariances[i] = 1.0f;
			paramMeans[i] = AllParams[i]->generateUniform(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));//unitUniformDistribution(randomGenerator));
			//nSavedChoices = 0.0f;
			onlineDelta[i] = 0.0f;
			onlineDeltaN[i] = 0.0f;
			onlineMean[i] = 0.0f;
			onlineDelta2[i] = 0.0f;
			onlineM2Right[i] = 0.0f;
			onlineM2[i] = 0.0f;
		}
	}

	~SceneParams() {};
};

#endif // SceneParams_h
