#include "Params/SceneParams.h"
#include <iostream>
#include "Params/ParamArray.hpp"

using namespace ParamWorld;

ParamArray<SP_Count> SceneParams::generate(float deviance)
{
    ParamArray<SP_Count> newVec;
    for (int i = 0; i < SP_Count; i++) {
        newVec[i] = AllParams[i]->generateGaussian(paramMeans[i], paramVariances[i] * deviance,
                                                   unitNormalDistribution);
    }
    return newVec;
}

ParamArray<SP_Count> SceneParams::randomSP()
{
    ParamArray<SP_Count> newVec;
    for (int i = 0; i < SP_Count; i++) {
        newVec[i] = AllParams[i]->generateUniform(unitUniformDistribution(randomGenerator));
    }
    return newVec;
}

void SceneParams::moveMeans(ParamArray<SP_Count> sp, bool towards)
{
    updateVariance(sp);

    // Calculate z-Scores
    ParamArray<SP_Count> diffs = sp - paramMeans;
    ParamArray<SP_Count> zScores = diffs.divideElement(paramVariances);

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
    // vectProd(zScores, paramVariances, paramVariances);

    // Move mean toward vector, also reuse zScores
    diffs = diffs * learningRate;
    if (towards) {
        paramMeans = paramMeans + diffs;
    } else {
        paramMeans = paramMeans - diffs;
    }

    // Update learning rates
    learningRate = std::max(learningMinimum, learningRate * learningDecay);
}

void SceneParams::changeVariability(float modifier)
{
    paramVariances = paramVariances * modifier;
    learningRate = std::max(std::min(learningRate * modifier, learningMaximum), learningMinimum);
}

void SceneParams::updateVariance(ParamArray<SP_Count> sp)
{
    nSavedChoices += 1;

    // Welford Algorithm
    auto onlineDelta = sp - onlineMean;
    onlineMean = onlineMean + (onlineDelta / nSavedChoices);
    auto onlineDelta2 = sp - onlineMean;
    onlineM2 = onlineM2 + (onlineDelta.multiplyElement(onlineDelta2));

    // For too few data points, no real variance
    if (nSavedChoices < 2) {
        return;
    }

    paramVariances = onlineM2 / (nSavedChoices - 1);
}

void SceneParams::resetVariability()
{
    for (int i = 0; i < SP_Count; i++) {
        paramVariances[i] = maximumVariance;
    }
    learningRate = learningMaximum;
}

SceneParams::SceneParams() : SceneParams((unsigned int)time(nullptr)) {}
SceneParams::SceneParams(unsigned int seed)
{
    randomGenerator.seed(((unsigned int)time(nullptr)));
    // Colors
    AllParams[SP_Red] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_Green] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_Blue] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_Alpha] = new SParam(false, 0.0f, 1.0f);

    AllParams[SP_Depth] = new SParam(true, 1.0f, 8.0f);
    AllParams[SP_Width] = new SParam(false, 0.1f, 2.0f);
    AllParams[SP_Height] = new SParam(false, 0.2f, 20.0f);
    AllParams[SP_Scale] = new SParam(false, 0.1f, .98f);
    AllParams[SP_SplitAngle] = new SParam(false, 0.1f, MATH_FLOAT_PI / 4);
    AllParams[SP_BranchR] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_BranchG] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_BranchB] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_LeafR] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_LeafG] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_LeafB] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_LeafSize] = new SParam(false, 0.5f, 2.0f);

    AllParams[SP_Rock_Depth] = new SParam(true, 2.0f, 5.0f);
    AllParams[SP_Rock_R] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_Rock_G] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_Rock_B] = new SParam(false, 0.0f, 1.0f);
    AllParams[SP_Rock_HeightMult] = new SParam(false, 0.3f, 1.8f);

    // Initialize variances to 1
    for (int i = 0; i < SP_Count; i++) {
        paramMeans[i] = AllParams[i]->generateUniform(
            static_cast<float>(rand()) /
            static_cast<float>(RAND_MAX));  // unitUniformDistribution(randomGenerator));
    }
}

SceneParams::~SceneParams() = default;
