#include "DRandomForest.h"



int main()
{
    
    DData trainingData("fruit training set.csv");

    DTree dtree;

    dtree.fit(trainingData);

    //DRandomForest randomForest(100, trainingData);

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

    for (unsigned int i = 0; i < kek.size(); i++)
        std::cout << kek[i] << " ";
    std::cout << '\n';
    
    std::set<unsigned int> lmao;
    std::vector<double> lmaow;

    trainingData.generateSampleIndices(lmao, lmaow);

    for (auto l : lmao)
        std::cout << l << " ";

    std::cout << '\n';

    for (unsigned int i = 0; i < lmaow.size(); i++)
        std::cout << lmaow[i] << " ";
    */
    
    /*
    std::vector<unsigned int> classCounts = { 7, 0, 4, 0, 0, 1, 12 };

    std::cout << calculateGiniIndex(classCounts) << '\n';
    std::cout << calculateShannonEntropy(classCounts) << '\n';
    */
    
    

    return 0;

}





