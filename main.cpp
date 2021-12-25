#include "RandomForest.h"

int main()
{
    
    DData trainingData("fruit training set.csv");
    //RandomForest randomForest(100, trainingData);

    for (unsigned int i = 0; i < trainingData.getSampleSize(); i++)
        std::cout << trainingData[i][1].getStringValue() << " "
        << trainingData[i][1].getNumericValue() << "\n";
        
    return 0;

}





