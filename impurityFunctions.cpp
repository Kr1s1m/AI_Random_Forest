#include "impurityFunctions.h"


double calculateGiniIndex(const std::vector<unsigned int>& classCounts)
{
	double giniIndex = 0.0;
	double currentProbability = 0.0;

	//sum of class counts is at the back of the vector, generatred while they were calculated
	double totalSamples = (double)classCounts.back();

	std::vector<unsigned int>::const_iterator classCountsIt = classCounts.begin();

	for (classCountsIt; classCountsIt != classCounts.end() - 1; classCountsIt++)
	{
		
		if (*classCountsIt == 0)
			continue;

		currentProbability = (double)(*classCountsIt) / totalSamples;

		giniIndex += currentProbability * (1 - currentProbability);
	}

	return giniIndex;
		
}

double calculateShannonEntropy(const std::vector<unsigned int>& classCounts)
{
	double shannonEntropy = 0.0;
	double currentProbability = 0.0;

	//sum of class counts is at the back of the vector, generatred while they were calculated
	double totalSamples = (double)classCounts.back();


	std::vector<unsigned int>::const_iterator classCountsIt = classCounts.begin();

	for (classCountsIt; classCountsIt != classCounts.end() - 1; classCountsIt++)
	{

		if (*classCountsIt == 0)
			continue;

		currentProbability = (double)(*classCountsIt) / totalSamples;

		shannonEntropy += currentProbability * std::log2(currentProbability);
	}

	return -shannonEntropy;
}