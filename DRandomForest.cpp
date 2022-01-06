#include "DRandomForest.h"


DRandomForest::DRandomForest(unsigned int _dtreeCount, unsigned int _maxDepth, unsigned int _minSamplesPerSplit, 
							 unsigned int _minSamplesPerLeaf, double _impurityThreshold,
							 bool _bootstrappingAllowed, bool _regression, bool _multithread,
							 ImpurityFunctor _impurityFunction, FeatureFunctor _featureFunction) :

	threadCount(std::thread::hardware_concurrency()),
	dtreeCount(_dtreeCount), maxDepth(_maxDepth), minSamplesPerSplit(_minSamplesPerSplit),
	minSamplesPerLeaf(_minSamplesPerLeaf), impurityThreshold(_impurityThreshold),
	bootstrappingAllowed(_bootstrappingAllowed), regression(_regression),
	multithread(_multithread), isTrained(false), outOfBagError(100.0),
	impurityFunction(_impurityFunction), featureFunction(_featureFunction)

{
	decisionTrees.reserve(_dtreeCount);
}


void DRandomForest::calculateOutOfBagError()
{
	if (!isTrained)
		return;

	double errorSum = 0.0;

	std::vector<DTree>::const_iterator treeIt = decisionTrees.begin();

	for (treeIt; treeIt != decisionTrees.end(); treeIt++)
		errorSum += treeIt->getOutOfBagError();

	outOfBagError = errorSum / (double)dtreeCount;
}


void DRandomForest::multiThreadFit(const DData& data)
{
	ThreadPool threadPool(threadCount);
	std::vector<std::future<DTree>> poolResults;

	for (unsigned int treeIndex = 0; treeIndex < dtreeCount; treeIndex++)
	{
		poolResults.emplace_back(threadPool.enqueue(

			[&, treeIndex]()
			{

				DTree dtree(maxDepth, minSamplesPerSplit, minSamplesPerLeaf, impurityThreshold,
							bootstrappingAllowed, regression,
							impurityFunction, featureFunction
							);

				dtree.fit(data);

				return dtree;

			}

		));
	}

	std::vector<std::future<DTree>>::iterator resultIterator = poolResults.begin();

	for (resultIterator; resultIterator != poolResults.end(); resultIterator++)
		decisionTrees.push_back(resultIterator->get());

}

void DRandomForest::mainThreadFit(const DData& data)
{

	for (unsigned int treeIndex = 0; treeIndex != dtreeCount; treeIndex++)
	{
		DTree dtree(maxDepth, minSamplesPerSplit, minSamplesPerLeaf, impurityThreshold,
					bootstrappingAllowed, regression,
					impurityFunction, featureFunction
				   );

		dtree.fit(data);

		decisionTrees.push_back(dtree);
	}
}

void DRandomForest::fit(const DData& data)
{

	std::cout << "Fitting trees to \"" << data.getFileName() << "\", please wait.... ";

	if (multithread)
	{
		multiThreadFit(data);
	}	
	else
	{
		mainThreadFit(data);
	}
			
	isTrained = true;

	std::cout << "Done.\n";
		   
	std::cout << "Calculating out-of-bag error for forest... ";

	calculateOutOfBagError();

	std::cout << "Done.\n"
	<< "Your random forest is now trained and ready.\n\n";
}

void DRandomForest::reset()
{
	if (!isTrained)
		return;

	std::cout << "Resetting forest... ";

	decisionTrees.clear();

	isTrained = false;

	std::cout << "Done.\n\n";
}

DValue DRandomForest::classify(const DSample& sample) const
{
	if (!isTrained)
		return DValue();

	double currentClass, mostVotedClass;
	unsigned int mostVotes = 0;
	
	std::unordered_map<unsigned int, unsigned int> votes;

	std::vector<DTree>::const_iterator treeIt = decisionTrees.begin();

	for (treeIt; treeIt != decisionTrees.end(); treeIt++)
	{
		currentClass = treeIt->classify(sample).getNumericValue();

		votes[(unsigned int)currentClass]++;

		if (votes[(unsigned int)currentClass] > mostVotes)
		{
			mostVotes = votes[(unsigned int)currentClass];
			mostVotedClass = currentClass;
		}
			
	}
		
	return DValue(mostVotedClass);

	//return std::max_element(votes.begin(), votes.end(), [](const auto& x, const auto& y) {return x.second < y.second; })->first;
}

bool DRandomForest::classifyBatch(const DData& testData) const
{
	if (!isTrained)
		return false;

	std::cout << "Batch \"" << testData.getFileName() << "\" classification in progress... ";

	std::string resultsFileName = "results " + std::to_string(time(0)) + ".txt";
	std::ofstream resultsFile(resultsFileName);

	resultsFile << "Forest total out-of-bag error: " << getOutOfBagError() << "%\n";

	std::vector<DSample>::const_iterator testSamplesIt = testData.getSamples().begin();
	for (testSamplesIt; testSamplesIt != testData.getSamples().end(); testSamplesIt++)
	{

		resultsFile << "prediction: " << classify(*testSamplesIt).getNumericValue()  << "\t"
					<< "actual: "	  << testSamplesIt->getTargetClassNumericValue() << "\n";
	}

	resultsFile.close();

	std::cout << "Done.\n"
			  << "Results saved inside \"" << resultsFileName << "\".\n\n";

	return true;

}


double DRandomForest::getOutOfBagError() const
{
	return outOfBagError;
}
