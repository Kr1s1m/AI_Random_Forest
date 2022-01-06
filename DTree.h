#pragma once

#include "DData.h"
#include "DNode.h"
#include "Split.h"

#include "impurityFunctions.h"
#include "featureFunctions.h"

#include<stack>


using ImpurityFunctor = std::function<double(const std::vector<unsigned int>&)>;
using FeatureFunctor = std::function<unsigned int(unsigned int)>;

class DTree
{
private:

    std::shared_ptr<DNode> root;

    unsigned int maxDepth;
    unsigned int minSamplesPerSplit;
    unsigned int minSamplesPerLeaf;

    double impurityThreshold;
    double outOfBagError;

    bool bootstrappingAllowed;
    bool regression;
    bool isTrained;

    ImpurityFunctor impurityFunction;
    FeatureFunctor featureFunction;
    
    


    void calculateClassCounts(std::vector<unsigned int>&, const DData&,
                              const std::vector<unsigned int>&, const std::vector<double>&)const;

    void calculateMajorityClass(std::pair<double, unsigned int>&, const std::vector<unsigned int>&)const;

    Split findBestSplit(double, const DData&, const std::vector<unsigned int>&, const std::vector<double>&);

    void generateThresholds(std::vector<double>&, unsigned int, const DData&, const std::vector<unsigned int>&);

    void splitSampleIndices(unsigned int, double, const DData&, const std::vector<unsigned int>&, std::vector<unsigned int>&, std::vector<unsigned int>&);

    std::shared_ptr<DNode> createNode(unsigned int, double, unsigned int, double, double);

    void buildTree(const DData&, const std::vector<unsigned int>&, const std::vector<double>&);

    void calculateOutOfBagError(const DData&, const std::vector<double>&);

    

public:

    DTree(unsigned int = 7, unsigned int = 1, unsigned int = 1, double = 0.01,
          bool = true, bool = false,
          ImpurityFunctor = calculateShannonEntropy, FeatureFunctor = squareRoot);

    void fit(const DData&);

    DValue classify(const DSample&)const;

    double getOutOfBagError()const;

    

};

