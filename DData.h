#pragma once

#include "DSample.h"
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>
#include <functional>
#include <numeric>
#include <algorithm>
#include "random_unique.h"

class DData
{
private:
    std::string fileName;

    std::vector<std::string> colNames;
    std::vector<DSample> samples;

    std::vector<unsigned int> featureIndices;

    bool isLoaded;

    void loadFromCSV(const std::string&);
    void enumerateUnordered();

public:

    DData(const std::string&);

    const std::string& getFileName()const;
    const std::vector<DSample>& getSamples()const;
    const std::vector<std::string>& getColNames()const;
    const std::vector<unsigned int>& getFeatureIndices()const;
    int getSampleSize()const;

    const DSample& operator[](unsigned int) const;

    void addSample(const DSample&);
    void saveInside(const std::string&) const;

    void generateFeatureIndices(std::vector<unsigned int>&, std::function<unsigned int(unsigned int)>)const;
    void generateSampleIndices(std::vector<unsigned int>&, std::vector<double>&, bool)const;

};
