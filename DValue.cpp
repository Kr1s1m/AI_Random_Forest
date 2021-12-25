#include "DValue.h"


DValue::DValue(std::string _string) : string(_string)
{
    ordered = false;
    numeric = 0.0;
}

DValue::DValue(double _numeric) : numeric(_numeric)
{
    ordered = true;
    string = std::to_string(_numeric);
}

DValue::DValue(std::string _string, double _numeric, bool _ordered) :
    string(_string), numeric(_numeric), ordered(_ordered)
{

}

DValue::DValue()
{
    string = "";
    numeric = 0.0;
    ordered = false;
}

const std::string& DValue::getStringValue() const
{
    return string;
}

double DValue::getNumericValue() const
{
    return numeric;
}

bool DValue::isOrdered() const
{
    return ordered;
}

void DValue::setNumericValue(double _numeric)
{
    numeric = _numeric;
}

std::ostream& operator<<(std::ostream& os, const DValue& value)
{
    return os << value.string;
}
