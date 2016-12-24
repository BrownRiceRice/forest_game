#include "SParam.hpp"

using namespace ParamWorld;

float SParam::generateUniform(float randNum) {
    if (isIntegral) {
        return round(randNum * (max - min) + min);
    }
    return randNum * (max - min) + min;
}

float SParam::generateGaussian(float mean, float variance,
        std::normal_distribution<float> unitNormalDistribution) {
    std::normal_distribution<float> dist(0.0f, 1.0f);
    float val= 0.0f;

    do {
        val = unitNormalDistribution(randomGenerator) * (max - min) / 2 * variance + mean;
    }
    while (val > max || val < min);

    if (isIntegral) {
        return round(val);
    }

    return val;
}

SParam::SParam(bool _isIntegral, float _min, float _max) :
        isIntegral(_isIntegral), randomGenerator(),
        min(_min), max(_max) {
    randomGenerator.seed((unsigned int)time(NULL));
}

// Empty destructor.
SParam::~SParam() {}
