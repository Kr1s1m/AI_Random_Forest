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

void DTree::calculateClassCounts(std::vector<unsigned int>& classCounts,
								 const DData& data, 
								 std::vector<unsigned int>& sampleIndices,
	                             std::vector<double>& sampleWeights)
const

{
	double totalSamples = 0.0;

	double maxClassNumericValue = 0.0;
	double classNumericValue = 0.0;



	std::vector<unsigned int>::const_iterator indexIt = sampleIndices.begin();

	for (indexIt; indexIt != sampleIndices.end(); indexIt++)
		if (classNumericValue = data[*indexIt].getTargetClass().getNumericValue() > maxClassNumericValue)
			maxClassNumericValue = classNumericValue;

	classCounts.clear();
	classCounts.resize((unsigned int)(++maxClassNumericValue));

	indexIt = sampleIndices.begin();

	for (indexIt; indexIt != sampleIndices.end(); indexIt++)
	{
		classNumericValue = data[*indexIt].getTargetClass().getNumericValue();
		classCounts[(unsigned int)classNumericValue] += sampleWeights[*indexIt];

		totalSamples += sampleWeights[*indexIt];
	}

	//store the total sample count at the back of the counts by class vector
	classCounts.push_back((unsigned int)totalSamples);

}


void DTree::fit(const DData&)
{


	isTrained = true;
}

DValue DTree::classify(const DSample&) const
{
	if (!isTrained)
	{
		return DValue();
	}


	return DValue();
}


void DTree::calculateStrength(const DData& data, std::vector<double>& sampleWeights)
{
	double correctClassifications = 0.0;
	double totalClassifications = 0.0;

	unsigned int sampleIndex = 0;

	for (sampleIndex; sampleIndex < sampleWeights.size(); sampleIndex++)
	{

		if (sampleWeights[sampleIndex] > 0.0)
			continue;

		if (classify(data[sampleIndex]) == data[sampleIndex].getTargetClass())
			correctClassifications++;

		totalClassifications++;
	}

	strength = correctClassifications / totalClassifications;
}


double DTree::getStrength(const DData& data, std::vector<double>& sampleWeights)
{
	if (strength == -1.0 && isTrained)
		calculateStrength(data, sampleWeights);

	return strength;
}