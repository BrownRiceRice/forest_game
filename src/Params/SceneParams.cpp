#include "Params/SceneParams.h"


using namespace ParamWorld;

float *SceneParams::generate(float deviance) {
	float *newVec = (float *)malloc(SP_Count * sizeof(float));
	for (int i = 0; i < SP_Count; i++) {
		newVec[i] = AllParams[i]->generateGaussian(paramMeans[i], paramVariances[i] * deviance, unitNormalDistribution);
	}
	return newVec;
}

float *SceneParams::randomSP() {
	float *newVec = (float *)malloc(SP_Count * sizeof(float));
	for (int i = 0; i < SP_Count; i++) {
		newVec[i] = AllParams[i]->generateUniform(unitUniformDistribution(randomGenerator));
	}
	return newVec;
}

void SceneParams::moveMeans(float *sp, bool towards) {
	updateVariance(sp);

	// Calculate z-Scores
	float *diffs = (float *)malloc(SP_Count * sizeof(float));
	float *zScores = (float *)malloc(SP_Count * sizeof(float));
	vectMinus(sp, paramMeans, diffs);
	vectDiv(diffs, paramVariances, zScores);

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
	vectProdScalar(diffs, learningRate, diffs);
	if (towards) {
		vectAdd(paramMeans, diffs, paramMeans);
	} else {
		vectMinus(paramMeans, diffs, paramMeans);
	}

	// Update learning rates
	learningRate = std::max(learningMinimum, learningRate * learningDecay);
}

void SceneParams::changeVariability(float modifier) {
	vectProdScalar(paramVariances, modifier, paramVariances);
	learningRate = std::max(std::min(learningRate * modifier, learningMaximum), learningMinimum);
}

void SceneParams::updateVariance(float *sp) {
	nSavedChoices += 1;

	// For too few data points, no real variance
	if (nSavedChoices < 2) {
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
