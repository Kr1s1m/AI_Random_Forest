#pragma once
#include <string>
#include <iostream>

class DValue
{
private:
    std::string string;
    double numeric;
    bool ordered;

public:

    DValue(std::string);
    DValue(double);

    DValue(std::string, double, bool);
    DValue();

    DValue(const DValue&);

    bool operator==(const DValue&)const;
    bool operator<(const DValue&)const;
    DValue& operator=(const DValue&);

    const std::string& getStringValue()const;
    double getNumericValue()const;
    bool isOrdered()const;

    void setNumericValue(double);

    friend std::ostream& operator<<(std::ostream&, const DValue&);

};


