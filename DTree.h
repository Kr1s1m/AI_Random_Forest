#pragma once

#include "DData.h"
#include <unordered_map>


class DNode
{
public:
    std::unordered_map<std::string, unsigned int> amount;
    std::string label;
    double impurity;
    int depth;
    bool terminal;

    DNode* left;
    DNode* right;

};

class DTree
{
private:

    DNode* root;

    int maxDepth;
    int minSamplesPerSplit;
    int minSamplesPerLeaf;

    double impurityThreshold;


    void create();


public:

    DTree(int, int, int, double);

};

