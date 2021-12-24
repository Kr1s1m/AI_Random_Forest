#pragma once

#include <iostream>
#include <string>
#include <vector>


struct DValue
{
    std::string string;
    double numeric;
    bool ordered;

    DValue(std::string);
    DValue(double);

    DValue(std::string, double, bool);
    DValue();

};

class DSample
{
private:
    unsigned int id;
    std::vector<DValue> features;
    DValue target;

public:

    DSample();
    DSample(unsigned int, const std::vector<DValue>&, DValue);

    int getID()const;
    const std::vector<DValue>& getFeatures()const;
    const DValue& getTargetClass()const;

    friend std::istream& operator>>(std::istream&, DSample&);
    friend std::ostream& operator<<(std::ostream&, const DSample&);

};

