#pragma once
struct Split
{
	unsigned int featureIndex;

	unsigned int leftSampleCount;
	unsigned int rightSampleCount;

	double threshold;

	double leftImpurity;
	double rightImpurity;

	double leftClassNumericValue;
	double rightClassNumericValue;

	double leftProbability;
	double rightProbability;

	double gain;

};

