#pragma once

#include "DTree.h"
#include <map>


class DRandomForest
{
private:


	unsigned int dtreeCount;
	std::vector<DTree> decisionTrees;

	bool bootstrappingAllowed;
	bool regression;
	bool isTrained;

	double strength;

	void calculateStrength();

public:

	DRandomForest(unsigned int = 1000, bool = true, bool = false, bool = false);

	void fit(const DData&);

	DValue classify(const DSample&, const DData&)const;

	double getStrength()const;

};


