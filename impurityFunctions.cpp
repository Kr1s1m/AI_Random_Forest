#include "impurityFunctions.h"


double calculateGiniIndex(std::vector<unsigned int>& sampleIndices, std::vector<double>& sampleWeights)
{
	double giniIndex = 0.0;

	double totalSamples = 0.0;

	std::vector<unsigned int>::const_iterator indexIt = sampleIndices.begin();

	for (indexIt; indexIt != sampleIndices.end(); indexIt++)
		totalSamples += sampleWeights[*indexIt];

	indexIt = sampleIndices.begin();
	double currentProbability = 0.0;

	for (indexIt; indexIt != sampleIndices.end(); indexIt++)
	{
		currentProbability = sampleWeights[*indexIt] / totalSamples;

		giniIndex += currentProbability * (1 - currentProbability);
	}

	return giniIndex;
		
}

double calculateShannonEntropy(std::vector<unsigned int>& sampleIndices, std::vector<double>& sampleWeights)
{
	double shanonEntropy = 0.0;

	double totalSamples = 0.0;

	std::vector<unsigned int>::const_iterator indexIt = sampleIndices.begin();

	for (indexIt; indexIt != sampleIndices.end(); indexIt++)
		totalSamples += sampleWeights[*indexIt];

	indexIt = sampleIndices.begin();
	double currentProbability = 0.0;

	for (indexIt; indexIt != sampleIndices.end(); indexIt++)
	{
		currentProbability = sampleWeights[*indexIt] / totalSamples;

		shanonEntropy += currentProbability * std::log2(currentProbability);
	}

	return -shanonEntropy;
}