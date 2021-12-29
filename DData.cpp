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

void DData::generateFeatureIndices(std::vector<unsigned int>& featureIndices, std::function<unsigned int(unsigned int)> featureFunc) const
{
    if (samples.empty())
        return;

 
    unsigned int originalFeatureCount = (*this)[0].getFeatureCount();
    unsigned int mutatedFeatureCount = featureFunc(originalFeatureCount);

    featureIndices = std::vector<unsigned int>(originalFeatureCount);

    //fill featureIndices with valid indices - range(0,.., featureCount-1)
    std::iota(featureIndices.begin(), featureIndices.end(), 0);

    //if mutated =/= original
    if (mutatedFeatureCount < originalFeatureCount)
    {
        //randomly pick and place mutatedFeatureCount elements at the front of featureIndices
        random_unique(featureIndices.begin(), featureIndices.end(), mutatedFeatureCount);

        //remove and free the memory for the indices that we dont need
        featureIndices.erase(featureIndices.begin() + mutatedFeatureCount, featureIndices.end());
    }
    
    
}


void DData::generateSampleIndices(std::vector<unsigned int>& sampleIndices, std::vector<double>& sampleWeights) const
{
    if (samples.empty())
        return;


    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<> uniformDistirbution(0, samples.size() - 1);

    std::set<unsigned int> uniqueSampleIndices;

    sampleIndices.clear();
    sampleWeights.clear();

    sampleWeights = std::vector<double>(samples.size());

    for (std::vector<DSample>::const_iterator it = samples.begin(); it != samples.end(); it++)
    {
        unsigned int generatedIndex = uniformDistirbution(randomGenerator);

        uniqueSampleIndices.insert(generatedIndex);
        sampleWeights[generatedIndex]++;
    }

    sampleIndices.assign(uniqueSampleIndices.begin(), uniqueSampleIndices.end());
        
}
