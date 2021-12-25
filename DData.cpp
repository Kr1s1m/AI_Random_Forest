#include "DData.h"

void DData::loadFromCSV(const std::string& _fileName)
{
    std::ifstream ifile(_fileName);

    std::string line;
    std::string token;


    ifile >> line;
    std::istringstream iss(line);

    while (std::getline(iss, token, ';'))
        colNames.push_back(token);

    line.clear();
    iss.clear();

    while (ifile >> line)
    {
        DSample sample;

        iss.str(line);
        iss >> sample;

        samples.push_back(sample);

        line.clear();
        iss.clear();
        
    }

    ifile.close();

}

void DData::enumerateUnordered()
{
    if (samples.empty())  
        return;
       

    unsigned int featureIndex = 0;   
    std::vector<DSample>::iterator it = samples.begin();

    unsigned int featureCount = (*it).getFeatures().size();


    for (featureIndex; featureIndex < featureCount; featureIndex++)
    {
        if ((*it)[featureIndex].isOrdered())
            continue;
        
        double currentEnumeration = 0.0;
        std::string currentLabel;

        std::unordered_map<std::string, double> toNumeric;
        

        for (it; it != samples.end(); it++)
        {
            currentLabel = (*it)[featureIndex].getStringValue();

            if (toNumeric.find(currentLabel) != toNumeric.end())
            {
                (*it).getFeatureWriteAcessAt(featureIndex).setNumericValue(toNumeric[currentLabel]);
            }
            else
            {
                
                (*it).getFeatureWriteAcessAt(featureIndex).setNumericValue(currentEnumeration);
               
                toNumeric.insert(std::make_pair(currentLabel, currentEnumeration));
                currentEnumeration += 1.0;
            }
        }

        it = samples.begin();

    }

}

DData::DData(const std::string& _fileName)
{
    fileName = _fileName;

    loadFromCSV(_fileName);
    enumerateUnordered();
    
}

const std::string& DData::getFileName() const
{
    return fileName;
}

const std::vector<DSample>& DData::getSamples() const
{
    return samples;
}

const std::vector<std::string>& DData::getColNames() const
{
    return colNames;
}

int DData::getSampleSize() const
{
    return samples.size();
}

const DSample& DData::operator[](unsigned int index)const
{
    if (index > samples.size() - 1 || index < 0 || samples.empty())
    {
        std::cerr << "Out of bounds index in DData.samples array!";
        exit(1);
    }

    return samples[index];
}

void DData::addSample(const DSample& sample)
{

    samples.push_back(sample);

    std::ofstream ofile(fileName, std::ios_base::app);
    ofile << sample;
    ofile.close();

}

void DData::saveInside(const std::string& outputFileName) const
{
    std::ofstream ofile(outputFileName);

    std::vector<std::string>::const_iterator it1;
   
    for (it1 = colNames.begin(); it1 != colNames.end() - 1; it1++)
        ofile << *it1 << ';';
    ofile << *it1 << '\n';

    std::vector<DSample>::const_iterator it2;

    for (it2 = samples.begin(); it2 != samples.end(); it2++)
        ofile << *it2;

    ofile.close();
}
