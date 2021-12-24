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
        iss.str(line);

        //std::istringstream iss(line);

        DSample sample;
        iss >> sample;

        samples.push_back(sample);

        line.clear();
        iss.clear();
        
    }

    ifile.close();

}

DData::DData(const std::string& _fileName)
{
    fileName = _fileName;

    loadFromCSV(_fileName);
    
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
