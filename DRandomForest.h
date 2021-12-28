#pragma once

#include "DTree.h"


class DRandomForest
{
private:


	unsigned int dtreeCount;
	std::vector<DTree> decisionTrees;

	bool bootstrappingAllowed;

public:

	DRandomForest(unsigned int);

	void fit(const DData&);

	void classify(const DSample&)const;

};


