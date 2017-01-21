#include "Params/SceneParams.h"
#include "Params/ParamArray.hpp"

using namespace ParamWorld;

ParamArray<SP_Count> SceneParams::generate(float deviance) {
	ParamArray<SP_Count> newVec;
	for (int i = 0; i < SP_Count; i++) {
		newVec[i] = AllParams[i]->generateGaussian(paramMeans[i], paramVariances[i] * deviance, unitNormalDistribution);
	}
	return newVec;
}

ParamArray<SP_Count> SceneParams::randomSP() {
	ParamArray<SP_Count> newVec;
	for (int i = 0; i < SP_Count; i++) {
		newVec[i] = AllParams[i]->generateUniform(unitUniformDistribution(randomGenerator));
	}
	return newVec;
}

void SceneParams::moveMeans(ParamArray<SP_Count> sp, bool towards) {
	updateVariance(sp);

	// Calculate z-Scores
	//float *diffs = (float *)malloc(SP_Count * sizeof(float));
	//float *zScores = (float *)malloc(SP_Count * sizeof(float));
    ParamArray<SP_Count> diffs = sp - paramMeans; // vectMinus(sp, paramMeans, diffs);
	ParamArray<SP_Count> zScores = diffs - paramVariances; // vectDiv(diffs, paramVariances, zScores);

	// Map zScores => max(1, abs(zScores))
	for (int i = 0; i < SP_Count; i++) {
		float z = zScores[i];
		if (z < 1.0f) {
			if (z >= -1.0f) {
				zScores[i] = 1;
			} else {
				zScores[i] = -z;
			}
		}
	}

	// Increase variances of far away params
	//vectProd(zScores, paramVariances, paramVariances);

	// Move mean toward vector, also reuse zScores
	diffs = diffs * learningRate; // diffsvectProdScalar(diffs, learningRate, diffs);
	if (towards) {
		paramMeans = paramMeans - diffs; // vectAdd(paramMeans, diffs, paramMeans);
	} else {
		paramMeans = paramMeans - diffs; // vectMinus(paramMeans, diffs, paramMeans);
	}

	// Update learning rates
	learningRate = std::max(learningMinimum, learningRate * learningDecay);
}

void SceneParams::changeVariability(float modifier) {
    paramVariances = paramVariances * modifier;
	//vectProdScalar(paramVariances, modifier, paramVariances);
	learningRate = std::max(std::min(learningRate * modifier, learningMaximum), learningMinimum);
}

void SceneParams::updateVariance(ParamArray<SP_Count> sp) {
	nSavedChoices += 1;

	// For too few data points, no real variance
	if (nSavedChoices < 2) {
		return;
	}

	// Welford Algorithm
    onlineDelta = sp - onlineMean; // vectMinus(sp, onlineMean, onlineDelta);
    onlineDeltaN = onlineDelta / nSavedChoices; // vectDivScalar(onlineDelta, nSavedChoices, onlineDeltaN);
    onlineMean = onlineMean + onlineDeltaN; // vectAdd(onlineMean, onlineDeltaN, onlineMean);
	onlineDelta2 = sp - onlineMean; // vectMinus(sp, onlineMean, onlineDelta2);
	onlineM2Right = onlineDelta.multiplyElement(onlineDelta2); // vectProd(onlineDelta, onlineDelta2, onlineM2Right);
	onlineM2 = onlineM2 + onlineM2Right; // vectAdd(onlineM2, onlineM2Right, onlineM2);
	paramVariances = onlineM2 / (nSavedChoices - 1); // vectDivScalar(onlineM2, nSavedChoices - 1, paramVariances);
}

void SceneParams::resetVariability() {
	for (int i = 0; i < SP_Count; i++) {
		paramVariances[i] = maximumVariance;
	}
	learningRate = learningMaximum;
}

void SceneParams::vectMinus(float *v1, float *v2, float *diff) {
	for (int i = 0; i < SP_Count; i++) {
		diff[i] = v1[i] - v2[i];
	}
}

void SceneParams::vectAdd(float *v1, float *v2, float *sum) {
	for (int i = 0; i < SP_Count; i++)
	{
		sum[i] = v1[i] + v2[i];
	}
}

void SceneParams::vectProd(float *v1, float *v2, float *prod) {
	for (int i = 0; i < SP_Count; i++) {
		prod[i] = v1[i] * v2[i];
	}
}

void SceneParams::vectProdScalar(float *v1, float c, float *prod) {
	for (int i = 0; i < SP_Count; i++) {
		prod[i] = v1[i] * c;
	}
}

void SceneParams::vectDiv(float *v1, float *v2, float *quot) {
	for (int i = 0; i < SP_Count; i++) {
		quot[i] = v1[i] / v2[i];
	}
}

void SceneParams::vectDivScalar(float *v1, float c, float *quot) {
	for (int i = 0; i < SP_Count; i++) {
	    quot[i] = v1[i] / c;
	}
}

float SceneParams::l2_norm(float *v) {
	float sum = 0.0f;
	for (int i = 0; i < SP_Count; i++) {
		sum += v[i] * v[i];
	}
	return sqrt(sum);
}

SceneParams::SceneParams() {
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

SceneParams::~SceneParams() {}
