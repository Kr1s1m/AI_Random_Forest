#pragma once

#include "DTree.h"
#include <ctime>
#include "ThreadPool.h"

class DRandomForest
{
private:

	std::vector<DTree> decisionTrees;

	unsigned int threadCount;

	unsigned int dtreeCount;
	unsigned int maxDepth;
	unsigned int minSamplesPerSplit;
	unsigned int minSamplesPerLeaf;

	double impurityThreshold;
	double outOfBagError;

	bool bootstrappingAllowed;
	bool regression;
	bool isTrained;
	bool multithread;

	ImpurityFunctor impurityFunction;
	FeatureFunctor featureFunction;

	void multiThreadFit(const DData&);
	void mainThreadFit(const DData&);

	void calculateOutOfBagError();

public:

	DRandomForest(unsigned int = 200, unsigned int = 7, unsigned int = 1, unsigned int = 1, double = 0.01,
		bool = true, bool = false, bool = true, ImpurityFunctor = calculateShannonEntropy, FeatureFunctor = squareRoot);

	void fit(const DData&);
	void reset();

	DValue classify(const DSample&)const;

	bool classifyBatch(const DData&)const;

	double getOutOfBagError()const;

};


