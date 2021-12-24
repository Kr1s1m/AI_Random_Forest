#pragma once

#include <iostream>
#include <string>
#include <vector>


struct DValue
{
    std::string string;
    double numeric;
    bool ordered;

};

class DSample
{
private:
    int id;
    std::vector<DValue> features;
    DValue target;

public:


    friend std::istream& operator>>(std::istream&, DSample&);
    friend std::ostream& operator<<(std::ostream&, const DSample&);

};

