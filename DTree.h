#pragma once

#include "DData.h"
#include "DNode.h"



class DTree
{
private:

    std::unique_ptr<DNode> root;

    int maxDepth;
    int minSamplesPerSplit;
    int minSamplesPerLeaf;

    double impurityThreshold;

    std::function<double()> impurityFunction;
    std::function<unsigned(unsigned)> featureFunction;
    


public:

    DTree(int, int, int, double);

    void fit(const DData&);

    void classify(const DSample&)const;

};

