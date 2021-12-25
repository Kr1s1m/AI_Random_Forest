#include "DSample.h"


DSample::DSample()
{
    id = 0;
    features = std::vector<DValue>();
}

DSample::DSample(unsigned int _id, const std::vector<DValue>& _features)
{
    id = _id;

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
    return features.back();
}

const DValue& DSample::operator[](unsigned int index) const
{
    if (index > features.size() - 1 || index < 0 || features.empty())
    {
        std::cerr << "Out of bounds index in DSample.features array!";
        exit(1);
    }

    return features[index];
}

DValue& DSample::getFeatureWriteAcessAt(unsigned int featureIndex)
{
    return features[featureIndex];
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


    return is;
}

std::ostream& operator<<(std::ostream& os, const DSample& sample)
{

    std::vector<DValue>::const_iterator it = sample.features.begin();

    os << sample.id << ';';

    for (it; it != sample.features.end(); it++)
        if (it->isOrdered())
            os << it->getNumericValue() << ';';
        else
            os << it->getStringValue() << ';';


    os << sample.getTargetClass().getStringValue() << '\n';

    return os;
}


