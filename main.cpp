#include "RandomForest.h"



int main()
{
    
    DData trainingData("fruit training set.csv");

    //RandomForest randomForest(100, trainingData);

    /*
    for (unsigned int i = 0; i < trainingData.getSampleSize(); i++)
        std::cout << trainingData[i][1].getStringValue() << " "
        << trainingData[i][1].getNumericValue() << "\n";

    std::cout << "\n";
    std::cout << "\n";

    for (unsigned int i = 0; i < trainingData.getSampleSize(); i++)
        std::cout << trainingData[i][3].getStringValue() << " "
        << trainingData[i][3].getNumericValue() << "\n";

    std::cout << "\n";
    std::cout << "\n";

    for (unsigned int i = 0; i < trainingData.getSampleSize(); i++)
        std::cout << trainingData[i][4].getStringValue() << " "
        << trainingData[i][4].getNumericValue() << "\n";

    */

    /*
    std::vector<unsigned int> kek;

    trainingData.generateFeatureIndices(kek, [](unsigned int x){return (unsigned int)std::sqrt(x);});

    unsigned int featureCount = trainingData[0].getFeatureCount();
    std::cout << featureCount << '\n';

    featureCount = (unsigned int)std::sqrt(featureCount);
    std::cout << featureCount << '\n';

    for (unsigned int i = 0; i < featureCount; i++)
        std::cout << kek[i] << " ";
    std::cout << '\n';
    
    std::vector<unsigned int> lmao;
    trainingData.generateSampleIndices(lmao);

    for (unsigned int i = 0; i < lmao.size(); i++)
        std::cout << lmao[i] << " ";
    */

    return 0;

}





