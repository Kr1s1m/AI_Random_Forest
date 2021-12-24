#pragma once

#include "DSample.h"

class DData
{
private:

    std::vector<std::string> colNames;
    std::vector<DSample> samples;


    void loadFromCSV(const std::string&);

public:

    DData(const std::string&);

    const std::vector<DSample>& getSamples()const;
    int getSampleSize()const;



};
