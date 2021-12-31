#include "DRandomForest.h"


DRandomForest::DRandomForest(unsigned int _dtreeCount, bool _bootstrappingAllowed, bool _regression, bool _isTrained):
	dtreeCount(_dtreeCount), bootstrappingAllowed(_bootstrappingAllowed), isTrained(_isTrained), strength(-1.0)
{
	decisionTrees = std::vector<DTree>(_dtreeCount);
}

void DRandomForest::fit(const DData& data)
{
	std::vector<DTree>::iterator treeIt = decisionTrees.begin();

	for (treeIt; treeIt != decisionTrees.end(); treeIt++)
		treeIt->fit(data);

	isTrained = true;

	calculateStrength();
}

DValue DRandomForest::classify(const DSample& sample, const DData& data) const
{
	/*
	std::vector<DTree>::const_iterator treeIt = decisionTrees.begin();

	for (treeIt; treeIt != decisionTrees.end(); treeIt++)
		std::cout << treeIt->classify(sample, data) << '\n';

	return DValue();
	*/

	
	
	std::unordered_map<unsigned int, unsigned int> votes;

	std::vector<DTree>::const_iterator treeIt = decisionTrees.begin();

	for (treeIt; treeIt != decisionTrees.end(); treeIt++)
		votes[(unsigned int)treeIt->classify(sample, data).getNumericValue()]++;

	

	return std::max_element(votes.begin(), votes.end(), [](const auto& x, const auto& y) {return x.second < y.second; })->first;
	
	
}

void DRandomForest::calculateStrength()
{
	if (!isTrained)
		return;

	double strengthSum = 0.0;

	std::vector<DTree>::const_iterator treeIt = decisionTrees.begin();

	for (treeIt; treeIt != decisionTrees.end(); treeIt++)
		strengthSum += treeIt->getStrength();

	strength = strengthSum / (double)dtreeCount;
}

double DRandomForest::getStrength() const
{
	return strength;
}
