#pragma once

#include "DTree.h"
#include <ctime>

class DRandomForest
{
private:

	std::vector<DTree> decisionTrees;

	unsigned int dtreeCount;
	unsigned int maxDepth;
	unsigned int minSamplesPerSplit;
	unsigned int minSamplesPerLeaf;

	double impurityThreshold;
	double outOfBagError;

	bool bootstrappingAllowed;
	bool regression;
	bool isTrained;

	ImpurityFunctor impurityFunction;
	FeatureFunctor featureFunction;

	void calculateOutOfBagError();

public:

	DRandomForest(unsigned int = 200, unsigned int = 10, unsigned int = 1, unsigned int = 1, double = 0.01,
		bool = true, bool = false, ImpurityFunctor = calculateShannonEntropy, FeatureFunctor = squareRoot);

	void fit(const DData&);

	DValue classify(const DSample&)const;

	bool classifyBatch(const DData&)const;

	double getOutOfBagError()const;

};


