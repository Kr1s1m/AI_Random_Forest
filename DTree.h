#pragma once

#include "DData.h"
#include "DNode.h"

#include "impurityFunctions.h"
#include "featureFunctions.h"

using ImpurityFunctor = std::function<double(const std::vector<unsigned int>&)>;
using FeatureFunctor = std::function<unsigned int(unsigned int)>;

class DTree
{
private:

    std::unique_ptr<DNode> root;

    unsigned int maxDepth;
    unsigned int minSamplesPerSplit;
    unsigned int minSamplesPerLeaf;


    double impurityThreshold;
    double strength;

    bool isTrained;

    ImpurityFunctor impurityFunction;
    FeatureFunctor featureFunction;
    
    void calculateStrength(const DData&, std::vector<double>&);

    void calculateClassCounts(std::vector<unsigned int>&, const DData&,
                              std::vector<unsigned int>&, std::vector<double>&)const;

public:

    DTree(unsigned int = 4, unsigned int = 1, unsigned int = 1, double = -1.0,
          ImpurityFunctor = calculateGiniIndex, FeatureFunctor = squareRoot);


    double getStrength(const DData&, std::vector<double>&);


    void fit(const DData&);

    DValue classify(const DSample&)const;

};

