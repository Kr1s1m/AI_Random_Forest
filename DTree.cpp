#include "DTree.h"



DTree::DTree(unsigned int _maxDepth, unsigned int _minSamplesPerSplit, unsigned int _minSamplesPerLeaf,
	         double _impurityThreshold,
	         ImpurityFunctor _impurityFunction, FeatureFunctor _featureFunction) :

maxDepth(_maxDepth), minSamplesPerSplit(_minSamplesPerSplit), minSamplesPerLeaf(_minSamplesPerLeaf),
impurityThreshold(_impurityThreshold), 
strength(-1.0), isTrained(false),
impurityFunction(_impurityFunction), featureFunction(_featureFunction)
{
	
}

DValue DTree::classify(const DSample&) const
{
	return DValue();
}


void DTree::calculateStrength(const DData& data, std::vector<double>& sampleWeights)
{
	double correctClassifications = 0.0;
	double totalClassifications = 0.0;

	unsigned int sampleIndex = 0;

	for (sampleIndex; sampleIndex < sampleWeights.size() - 1; sampleIndex++)
	{

		if (sampleWeights[sampleIndex] > 0.0)
			continue;

		if (classify(data[sampleIndex]) == data[sampleIndex].getTargetClass())
			correctClassifications++;

		totalClassifications++;
	}

	strength = correctClassifications / totalClassifications;
}