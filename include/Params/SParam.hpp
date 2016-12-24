#ifndef SPARAM_H
#define SPARAM_H

#include <algorithm>
#include <math.h>
#include <random>

namespace ParamWorld {
class SParam {
public:

	bool isIntegral;
	float min;
	float max;
	std::mt19937 randomGenerator;

	// Generates a uniform valid value using rejection sampling.
	float generateUniform(float randNum);

 	// Generates a gaussian valid value using rejection sampling.
	float generateGaussian(float mean, float variance,
		std::normal_distribution<float> unitNormalDistribution);

	// Constructor
	SParam(bool _isIntegral, float _min, float _max);

	~SParam();
};
}

#endif // SParam_h
