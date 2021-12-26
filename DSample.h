#pragma once

#include <vector>
#include "DValue.h"


class DSample
{
private:
    unsigned int id;
    std::vector<DValue> features;

public:

    DSample();
    DSample(unsigned int, const std::vector<DValue>&);

    int getID()const;
    unsigned int getFeatureCount()const;
    const std::vector<DValue>& getFeatures()const;
    const DValue& getTargetClass()const;

    const DValue& operator[](unsigned int) const;

    DValue& getFeatureWriteAcessAt(unsigned int);

    friend std::istream& operator>>(std::istream&, DSample&);
    friend std::ostream& operator<<(std::ostream&, const DSample&);

};

