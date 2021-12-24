#include "DSample.h"


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

DSample::DSample()
{
    id = 0;
    features = std::vector<DValue>();
    target = DValue();
}

DSample::DSample(unsigned int _id, const std::vector<DValue>& _features, DValue _target):
    id(_id), target(_target)
{
    std::vector<DValue>::const_iterator it;

    for (it = _features.begin(); it != _features.end(); it++)
        features.push_back(*it);


}

int DSample::getID() const
{
    return id;
}

const std::vector<DValue>& DSample::getFeatures() const
{
    return features;
}

const DValue& DSample::getTargetClass() const
{
    return target;
}

std::istream& operator>>(std::istream& is, DSample& sample)
{
 

    std::string token;

    std::getline(is, token, ';');
    sample.id = stoi(token);

    while (std::getline(is, token, ';'))
    {
        bool isOrdered = (token[0] == '-' || std::isdigit(token[0]));
        double numeric = isOrdered ? std::stod(token) : 0.0;

        sample.features.push_back(DValue( token, numeric, isOrdered ));
    }

    std::vector<DValue>::iterator lastFeaturePtr = sample.features.end() - 1;

    sample.target = *lastFeaturePtr;
    sample.features.erase(lastFeaturePtr);

    return is;
}

std::ostream& operator<<(std::ostream& os, const DSample& sample)
{

    std::vector<DValue>::const_iterator it = sample.features.begin();

    os << sample.id << ';';

    for (it; it != sample.features.end(); it++)
        if (it->numeric)
            os << it->numeric << ';';
        else
            os << it->string << ';';


    os << sample.target.string << '\n';

    return os;
}


