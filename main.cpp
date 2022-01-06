#include "DRandomForest.h"

const unsigned int MAX_SAMPLES = 256;

const unsigned int DTREE_COUNT = 100;
const unsigned int MAX_DEPTH = 9;
const unsigned int MIN_SPLIT = 1;
const unsigned int MIN_LEAF = 1;

const double IMPURITY_THRESHOLD = 0.01;
const double OUT_OF_BAG_ERROR_THRESHOLD = 0.0025;

const bool BOOTSTRAPPING_ALLOWED = true;
const bool REGRESSION = false;
const bool MULTITHREAD = true;

const ImpurityFunctor IMPURITY_FUNCTION = calculateShannonEntropy;
const FeatureFunctor FEATURE_FUNCTION = squareRoot;


int main()
{ 
    //object initialization

    DData trainingData("fruit training set 2.csv", MAX_SAMPLES);
    DData testData("fruit test set.csv", MAX_SAMPLES);

    DRandomForest randomForest(
                               DTREE_COUNT, MAX_DEPTH, MIN_SPLIT, MIN_LEAF, 
                               IMPURITY_THRESHOLD,
                               BOOTSTRAPPING_ALLOWED, REGRESSION, MULTITHREAD,
                               IMPURITY_FUNCTION, 
                               FEATURE_FUNCTION
                              );




    //object interface use

    randomForest.fit(trainingData);

    /*
    while (randomForest.getOutOfBagError() > OUT_OF_BAG_ERROR_THRESHOLD)
    {
        randomForest.reset();
        randomForest.fit(trainingData);
    }
    */
    
    
    randomForest.classifyBatch(testData);

    return 0;

}





