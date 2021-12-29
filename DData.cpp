#include "DData.h"

void DData::loadFromCSV(const std::string& _fileName, unsigned int maxSamples)
{

    std::ifstream ifile(_fileName);
    unsigned int totalSamplesLoaded = 0;

    std::string line;
    std::string token;

    unsigned int featureIndex = 0;
    

    ifile >> line;
    std::istringstream iss(line);

    while (std::getline(iss, token, ';'))
    {
        colNames.push_back(token);
        featureIndices.push_back(featureIndex++);
    }
    
    //pop two: one for id, one for class
    featureIndices.pop_back();
    featureIndices.pop_back();

    line.clear();
    iss.clear();

    while (totalSamplesLoaded < maxSamples && ifile >> line)
    {
        DSample sample;

        iss.str(line);
        iss >> sample;

        samples.push_back(sample);
        totalSamplesLoaded++;

        line.clear();
        iss.clear();
        
    }


    ifile.close();

    isLoaded = !samples.empty();

}

void DData::enumerateUnordered()
{
    if (!isLoaded)  
        return;
       
    
    unsigned int featureIndex = 0;
    //getFeatureCount() + 1, because we want to enumerate the target class at the back of the vector
    unsigned int featureCount = samples[featureIndex].getFeatureCount() + 1;
    

    
    std::vector<DSample>::iterator it = samples.begin();

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

DData::DData(const std::string& _fileName, unsigned int _maxSamples)
{
    fileName = _fileName;

    loadFromCSV(_fileName, _maxSamples);
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

const std::vector<unsigned int>& DData::getFeatureIndices() const
{
    return featureIndices;
}

int DData::getSampleSize() const
{
    return samples.size();
}

const DSample& DData::operator[](unsigned int index)const
{
    if (!isLoaded)
    {
        std::cerr << "Data was not loaded into DData object!";
        exit(1);
    }

    if (index > samples.size() - 1 || index < 0 || samples.empty())
    {
        std::cerr << "Out of bounds index in DData.samples array!";
        exit(1);
    }

    return samples[index];
}

void DData::addSample(const DSample& sample)
{

    if (!isLoaded)
        return;

    samples.push_back(sample);

    std::ofstream ofile(fileName, std::ios_base::app);
    ofile << sample;
    ofile.close();

}

void DData::saveInside(const std::string& outputFileName) const
{
    if (!isLoaded)
        return;

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

void DData::generateFeatureIndices(std::vector<unsigned int>& randomFeatureIndices, std::function<unsigned int(unsigned int)> featureFunc) const
{
    if (samples.empty() || featureIndices.empty() || !isLoaded)
        return;

 
    unsigned int originalFeatureCount = featureIndices.size();
    unsigned int mutatedFeatureCount = featureFunc(originalFeatureCount);

    

    //if mutated =/= original
    if (mutatedFeatureCount < originalFeatureCount)
    {
        //make sure the vector is clean
        randomFeatureIndices.clear();

        //allocate shuffling space by filling vector with original indices
        randomFeatureIndices.assign(featureIndices.begin(), featureIndices.end());

        //randomly pick and place mutatedFeatureCount elements at the front of randomFeatureIndices
        //*automatically stops shuffling after mutatedFeatureCount random elements are placed
        random_unique(randomFeatureIndices.begin(), randomFeatureIndices.end(), mutatedFeatureCount);

        //remove and free the memory for the indices that we dont need (which we did not pick)
        randomFeatureIndices.erase(randomFeatureIndices.begin() + mutatedFeatureCount, randomFeatureIndices.end());
    }
    
    
}


void DData::generateSampleIndices(std::vector<unsigned int>& sampleIndices, std::vector<double>& sampleWeights, bool bootstrappigAllowed) const
{
    if (!isLoaded || samples.empty())
        return;


    sampleIndices.clear();
    sampleWeights.clear();

    if (bootstrappigAllowed)
    {
        std::random_device randomDevice;
        std::mt19937 randomGenerator(randomDevice());
        std::uniform_int_distribution<> uniformDistirbution(0, samples.size() - 1);

        std::set<unsigned int> uniqueSampleIndices;

        sampleWeights = std::vector<double>(samples.size());

        unsigned int generatedIndex = 0;

        for (std::vector<DSample>::const_iterator it = samples.begin(); it != samples.end(); it++)
        {
            generatedIndex = uniformDistirbution(randomGenerator);

            uniqueSampleIndices.insert(generatedIndex);
            sampleWeights[generatedIndex]++;
        }

        sampleIndices.assign(uniqueSampleIndices.begin(), uniqueSampleIndices.end());
    }
    else
    {
        unsigned int sampleIndex = 0;
        const double sampleWeight = 1.0;

        for (std::vector<DSample>::const_iterator it = samples.begin(); it != samples.end(); it++)
        {
            sampleIndices.push_back(sampleIndex++);
            sampleWeights.push_back(sampleWeight);
        }
    }
        
}
