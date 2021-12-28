#pragma once
#include <vector>
#include <cmath>
#include "DData.h"

double calculateGiniIndex(const std::vector<unsigned int>&);

double calculateShannonEntropy(const std::vector<unsigned int>&);