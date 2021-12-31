#pragma once

#include <memory>

struct DNode
{

    double threshold;
    double impurity;
    double probability;
    double classNumericValue;

    unsigned int sampleCount;
    unsigned int featureIndex;
    unsigned int depth;
    
    bool orderedSplit;

    bool isTerminal;

    std::shared_ptr<DNode> left;
    std::shared_ptr<DNode> right;


};
