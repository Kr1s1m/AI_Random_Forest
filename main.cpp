#include "RandomForest.h"


int main()
{
    
    DData trainingData("fruit training set.csv");
    RandomForest randomForest(100, trainingData);

    return 0;
}





