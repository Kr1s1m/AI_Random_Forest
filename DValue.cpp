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
    string = "?";
    numeric = 0.0;
    ordered = false;
}

DValue::DValue(const DValue& other) :
    string(other.string), numeric(other.numeric), ordered(other.ordered)
{

}

bool DValue::operator==(const DValue& other)const
{
    return (numeric == other.numeric) && (ordered == other.ordered) && (string == other.string);
}

bool DValue::operator<(const DValue& other) const
{
    return numeric < other.numeric;
}

DValue& DValue::operator=(const DValue& other) 
{
    if (this != &other)
    {
        string = other.string;
        numeric = other.numeric;
        ordered = other.ordered;

    }
    return *this;
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
    if (value.isOrdered())
        os << value.numeric;
    else
        os << value.string;

    return os;
}
