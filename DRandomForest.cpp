#include "DRandomForest.h"


DRandomForest::DRandomForest(unsigned int _dtreeCount, unsigned int _maxDepth, unsigned int _minSamplesPerSplit,
	unsigned int _minSamplesPerLeaf, double _impurityThreshold, bool _bootstrappingAllowed, bool _regression,
	ImpurityFunctor _impurityFunction, FeatureFunctor _featureFunction):

	dtreeCount(_dtreeCount), maxDepth(_maxDepth), minSamplesPerSplit(_minSamplesPerSplit),
	minSamplesPerLeaf(_minSamplesPerLeaf), impurityThreshold(_impurityThreshold),
	bootstrappingAllowed(_bootstrappingAllowed), regression(_regression),
	isTrained(false), outOfBagError(-1.0),
	impurityFunction(_impurityFunction), featureFunction(_featureFunction)
{
	decisionTrees = std::vector<DTree>(dtreeCount,
		DTree(maxDepth, minSamplesPerSplit, minSamplesPerLeaf, impurityThreshold,
			  bootstrappingAllowed, regression, impurityFunction, featureFunction));
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

void DRandomForest::fit(const DData& data)
{
	unsigned int treeIndex = 0;
	unsigned int remainingTrees = dtreeCount;

	std::vector<DTree>::iterator treeIt = decisionTrees.begin();

	for (treeIt; treeIt != decisionTrees.end(); treeIt++)
	{
		system("cls");

		std::cout << "Fitting tree "         << treeIndex++      
				  << "\nTrees in fit queue: " << --remainingTrees
				  << "\n";

		treeIt->fit(data);
	}
		
	system("cls");

	std::cout << "Fitting \"" << data.getFileName() << "\" has finished.\n";
		      

	isTrained = true;

	std::cout << "Calculating out-of-bag error for forest...\n";

	calculateOutOfBagError();

	std::cout << "Done.\n"
	<< "Your random forest is now trained and ready for use!\n\n";
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

	std::cout << "Batch \""                << testData.getFileName() << "\" classification complete!\n"
			  << "Results saved inside \"" << resultsFileName        << "\".\n";

	return true;

}


double DRandomForest::getOutOfBagError() const
{
	return outOfBagError;
}
