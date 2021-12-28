#pragma once

#include "DData.h"
#include "DNode.h"

#include "impurityFunctions.h"

using ImpurityFunctor = std::function<double(std::vector<unsigned int>&, std::vector<double>&)>;
using FeatureFunctor = std::function<double(std::vector<unsigned int>&, std::vector<double>&)>;

class DTree
{
private:

    std::unique_ptr<DNode> root;

    int maxDepth;
    int minSamplesPerSplit;
    int minSamplesPerLeaf;

    double impurityThreshold;
    
    double strength;

    ImpurityFunctor impurityFunction;
    FeatureFunctor featureFunction;
    
    void calculateStrength(const DData&, std::vector<double>&);

public:

    DTree(int, int, int, double, ImpurityFunctor, FeatureFunctor);

    void fit(const DData&);

    DValue classify(const DSample&)const;

};

