#pragma once

#include "DTree.h"


class RandomForest
{
private:


	unsigned int dtreeCount;
	std::vector<DTree> decisionTrees;

public:

	RandomForest(unsigned int, DData&);

};


