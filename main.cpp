#include "DRandomForest.h"

const unsigned int MAX_SAMPLES = 10000;

int main()
{
    
    DData trainingData("fruit training set.csv", MAX_SAMPLES);

    DRandomForest randomForest;

    randomForest.fit(trainingData);

    DValue prediction = randomForest.classify(DSample(12, { DValue(47.1345), DValue(1.0), DValue(7653.831), DValue(1.0), DValue("?") }), trainingData);
    std::cout << prediction;

    /*
    DTree dtree;

    dtree.fit(trainingData);

    prediction = dtree.classify(DSample(12, { DValue(47.1345), DValue(1.0), DValue(7653.831), DValue(1.0), DValue("?") }), trainingData);
    std::cout << prediction;
    */
    

    return 0;

}





