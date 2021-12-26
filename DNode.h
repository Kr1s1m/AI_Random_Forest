#pragma once

#include <unordered_map>
#include <memory>

class DNode
{
private:

public:
    std::unordered_map<double, unsigned int> amount;

   

    double threshold;
    double impurity;
    double probability;

    unsigned int featureIndex;
    unsigned int depth;

    bool isTerminal;

    std::unique_ptr<DNode> left;
    std::unique_ptr<DNode> right;


};
