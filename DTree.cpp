#include "DTree.h"



DTree::DTree(unsigned int _maxDepth, unsigned int _minSamplesPerSplit, unsigned int _minSamplesPerLeaf,
	         double _impurityThreshold,
			 bool _bootstrappingAllowed, bool _regression,
	         ImpurityFunctor _impurityFunction, FeatureFunctor _featureFunction) :

root(nullptr),
maxDepth(_maxDepth), minSamplesPerSplit(_minSamplesPerSplit), minSamplesPerLeaf(_minSamplesPerLeaf),
impurityThreshold(_impurityThreshold), 
bootstrappingAllowed(_bootstrappingAllowed), regression(_regression), 
impurityFunction(_impurityFunction), featureFunction(_featureFunction),
isTrained(false), strength(-1.0)
{
	
}

void DTree::calculateClassCounts(std::vector<unsigned int>& classCounts,
								 const DData& data, 
								 const std::vector<unsigned int>& sampleIndices,
	                             const std::vector<double>& sampleWeights
								)const

{
	double totalSamples = 0.0;

	double maxClassNumericValue = 0.0;
	double classNumericValue = 0.0;


	std::vector<unsigned int>::const_iterator indexIt = sampleIndices.begin();

	for (indexIt; indexIt != sampleIndices.end(); indexIt++)
		if ((classNumericValue = data[*indexIt].getTargetClassNumericValue()) > maxClassNumericValue)
			maxClassNumericValue = classNumericValue;


	classCounts.clear();
	classCounts.resize((unsigned int)(maxClassNumericValue + 1));

	indexIt = sampleIndices.begin();

	for (indexIt; indexIt != sampleIndices.end(); indexIt++)
	{
		classNumericValue = data[*indexIt].getTargetClassNumericValue();
		classCounts[(unsigned int)classNumericValue] += sampleWeights[*indexIt];

		totalSamples += sampleWeights[*indexIt];
	}

	//store the total sample count at the back of the counts by class vector
	classCounts.push_back((unsigned int)totalSamples);

}

void DTree::calculateMajorityClass(std::pair<double, unsigned int>& majorityClass, const std::vector<unsigned int>& classCounts) const
{
	unsigned int maxClassCount = 0;
	unsigned int mostCommonClassValue = 0;

	for (unsigned int classValue = 0; classValue < classCounts.size() - 1; classValue++)
	{
		if (classCounts[classValue] > maxClassCount)
		{
			maxClassCount = classCounts[classValue];
			mostCommonClassValue = classValue;
		}
	}

	majorityClass.first = (double)mostCommonClassValue;
	majorityClass.second = maxClassCount;
}

void DTree::generateThresholds(std::vector<double>& thresholds, unsigned int featureIndex, const DData& data, const std::vector<unsigned int>& sampleIndices)
{
	thresholds.clear();

	std::set<double> uniqueThresholds;
	std::vector<unsigned int>::const_iterator sampleIt = sampleIndices.begin();

	for (sampleIt; sampleIt != sampleIndices.end(); sampleIt++)
		uniqueThresholds.insert(data[*sampleIt][featureIndex].getNumericValue());

	if (data[0][featureIndex].isOrdered())
	{
		
		std::set<double>::iterator thresholdIt = uniqueThresholds.begin();
		std::set<double>::iterator thresholdItNext = ++uniqueThresholds.begin();
		

		for (thresholdIt, thresholdItNext; thresholdItNext != uniqueThresholds.end(); thresholdIt++, thresholdItNext++)
		{
			thresholds.push_back(((*thresholdIt)+(*thresholdItNext))/2);
		}
	}
	else
	{
		thresholds.assign(uniqueThresholds.begin(), uniqueThresholds.end());
	}

	
}

Split DTree::findBestSplit(double parentImpurity, const DData& data, const std::vector<unsigned int>& sampleIndices, const std::vector<double>& sampleWeights)
{
	std::vector<unsigned int> featureIndices;
	data.generateFeatureIndices(featureIndices, featureFunction);

	std::vector<unsigned int> leftIndices, leftClassCounts;
	std::vector<unsigned int> rightIndices, rightClassCounts;

	std::pair<double, unsigned int> leftMajorityClass, rightMajorityClass;

	std::vector<double> thresholds;


	Split current, best;

	best.gain = std::numeric_limits<double>::lowest();

	std::vector<unsigned int>::const_iterator featureIt = featureIndices.begin();
	std::vector<double>::const_iterator thresholdIt = thresholds.begin();

	for (featureIt; featureIt != featureIndices.end(); featureIt++)
	{
		current.featureIndex = *featureIt;

		generateThresholds(thresholds, current.featureIndex, data, sampleIndices);
		
		thresholdIt = thresholds.begin();
		for(thresholdIt; thresholdIt != thresholds.end(); thresholdIt++)
		{
			current.threshold = *thresholdIt;
			splitSampleIndices(current.featureIndex, current.threshold, data, sampleIndices, leftIndices, rightIndices);
			calculateClassCounts(leftClassCounts, data, leftIndices, sampleWeights);
			calculateClassCounts(rightClassCounts, data, rightIndices, sampleWeights);

			current.leftSampleCount = leftClassCounts.back();
			current.rightSampleCount = rightClassCounts.back();

			current.leftImpurity = impurityFunction(leftClassCounts);
			current.rightImpurity = impurityFunction(rightClassCounts);

			calculateMajorityClass(leftMajorityClass, leftClassCounts);
			calculateMajorityClass(rightMajorityClass, rightClassCounts);

			current.leftClassNumericValue = leftMajorityClass.first;
			current.rightClassNumericValue = rightMajorityClass.first;

			current.leftProbability = (double)leftMajorityClass.second / leftClassCounts.back();
			current.rightProbability = (double)rightMajorityClass.second / rightClassCounts.back();

			current.gain = parentImpurity - current.leftProbability*current.leftImpurity - current.rightProbability*current.rightImpurity;

			if (current.gain > best.gain)
			{
				best = current;
			}
		}

	}



	return best;
		
}

void DTree::splitSampleIndices(unsigned int featureIndex, double threshold, const DData& data, const std::vector<unsigned int>& sampleIndices, std::vector<unsigned int>& leftIndices, std::vector<unsigned int>& rightIndices)
{
	leftIndices.clear();
	rightIndices.clear();

	std::vector<unsigned int>::const_iterator sampleIt = sampleIndices.begin();

	if (data[0][featureIndex].isOrdered())
	{
		for (sampleIt; sampleIt != sampleIndices.end(); sampleIt++)
			if (data[*sampleIt][featureIndex].getNumericValue() > threshold)
				leftIndices.push_back(*sampleIt);
			else
				rightIndices.push_back(*sampleIt);
	}
	else
	{
		for (sampleIt; sampleIt != sampleIndices.end(); sampleIt++)
			if (data[*sampleIt][featureIndex].getNumericValue() == threshold)
				leftIndices.push_back(*sampleIt);
			else
				rightIndices.push_back(*sampleIt);
	}
	
}



std::shared_ptr<DNode> DTree::createNode(unsigned int depth, double impurity, unsigned int sampleCount, double classNumericValue, double probability)
{

	std::shared_ptr<DNode> node(new DNode());

	node->depth = depth;
	node->sampleCount = sampleCount;
	node->impurity = impurity;
	node->classNumericValue = classNumericValue;
	node->probability = probability;


	return node;
}

void DTree::buildTree(const DData& data, const std::vector<unsigned int>& sampleIndices, const std::vector<double>& sampleWeights)
{

	std::stack<std::pair<std::shared_ptr<DNode>, std::vector<unsigned int>>> nodes;

	std::vector<unsigned int> classCounts;
	std::pair<double, unsigned int> majorityClass;

	calculateClassCounts(classCounts, data, sampleIndices, sampleWeights);
	calculateMajorityClass(majorityClass, classCounts);

	root = createNode(0, impurityFunction(classCounts), classCounts.back(), majorityClass.first, (double)majorityClass.second/classCounts.back());

	nodes.push({ root, sampleIndices });

	while (!nodes.empty())
	{
		std::pair<std::shared_ptr<DNode>, std::vector<unsigned int>> currentNode = nodes.top();
		nodes.pop();

		
		if (currentNode.first->depth == maxDepth ||
			currentNode.first->impurity < impurityThreshold ||
			currentNode.first->sampleCount < minSamplesPerSplit)
		{
			currentNode.first->isTerminal = true;
			continue;
		}

		Split best = findBestSplit(currentNode.first->impurity, data, currentNode.second, sampleWeights);

		std::vector<unsigned int> leftIndices, rightIndices;
		splitSampleIndices(best.featureIndex, best.threshold, data, currentNode.second, leftIndices, rightIndices);

		if (leftIndices.size() < minSamplesPerLeaf || rightIndices.size() < minSamplesPerLeaf)
		{
			currentNode.first->isTerminal = true;
			continue;
		}

		std::shared_ptr<DNode> leftChild = createNode(currentNode.first->depth + 1, best.leftImpurity, best.leftSampleCount, best.leftClassNumericValue, best.leftProbability);
		std::shared_ptr<DNode> rightChild = createNode(currentNode.first->depth + 1, best.rightImpurity, best.rightSampleCount, best.rightClassNumericValue, best.rightProbability);


		currentNode.first->featureIndex = best.featureIndex;
		currentNode.first->threshold = best.threshold;
		currentNode.first->orderedSplit = data[0][best.featureIndex].isOrdered();

		currentNode.first->left = leftChild;
		currentNode.first->right = rightChild;

		nodes.push({ leftChild, leftIndices });
		nodes.push({ rightChild, rightIndices });
		
	}


}


void DTree::fit(const DData& data)
{
	std::vector<unsigned int> sampleIndices;
	std::vector<double> sampleWeights;

	data.generateSampleIndices(sampleIndices, sampleWeights, bootstrappingAllowed);

	buildTree(data, sampleIndices, sampleWeights);

	isTrained = true;
}

DValue DTree::classify(const DSample& sample, const DData& data) const
{
	
	if (!isTrained)
		return DValue();


	std::shared_ptr<DNode> current = root;
	
	while (!current->isTerminal)
	{
		if (current->orderedSplit)
		{
			if (sample[current->featureIndex].getNumericValue() > current->threshold)
				current = current->left;
			else
				current = current->right;
		}
		else
		{
			if (sample[current->featureIndex].getNumericValue() == current->threshold)
				current = current->left;
			else
				current = current->right;
		}
	}

	std::vector<DSample>::const_iterator sampleIt = data.getSamples().begin();

	for (sampleIt; sampleIt != data.getSamples().end(); sampleIt++)
	{
		if (sampleIt->getTargetClassNumericValue() == current->classNumericValue)
			return sampleIt->getTargetClass();
	}

	return DValue();
}


void DTree::calculateStrength(const DData& data, const std::vector<double>& sampleWeights)
{
	if (!isTrained)
		return;

	double correctClassifications = 0.0;
	double totalClassifications = 0.0;

	unsigned int sampleIndex = 0;

	for (sampleIndex; sampleIndex < sampleWeights.size(); sampleIndex++)
	{

		if (sampleWeights[sampleIndex] > 0.0)
			continue;

		if (classify(data[sampleIndex], data) == data[sampleIndex].getTargetClass())
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