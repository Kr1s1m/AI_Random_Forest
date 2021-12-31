#include "DRandomForest.h"

#include <chrono>

const unsigned int MAX_SAMPLES = 10000;

int main()
{
    
    DData trainingData("fruit training set.csv", MAX_SAMPLES);
    DData testData("test set.csv", MAX_SAMPLES);

    DRandomForest randomForest;
    randomForest.fit(trainingData);

    auto now = std::chrono::system_clock::now();
    auto UTC = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();


    std::ofstream results("test results " + std::to_string(UTC) + ".txt");

    for (auto sample : testData.getSamples())
    {
        

        DValue prediction = randomForest.classify(sample, trainingData);

        results << "prediction: " << prediction.getNumericValue() 
                << " actual: " << sample.getTargetClassNumericValue() 
                << " out-of-bag-error " << randomForest.getStrength() 
                << "\n";
    }

    results.close();

    return 0;

}





