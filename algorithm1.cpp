#include "algorithm1.hpp"

//Default constructor
Algorithm1::Algorithm1(){
    _nbSample2Use = 70;
    _name = "Mean of absolutes differences between each samples";
    _id = 01;
    _percentage = 0;
}

//Constructor with a value for _nbSample2Use
Algorithm1::Algorithm1(int nbSample2Use){
    _nbSample2Use = nbSample2Use;
    _name = "Mean of absolutes differences between each samples";
    _id = 01;
    _percentage = 0;
}

//Apply the specific method of the algorithm to the data
float Algorithm1::applyMethod(vector<float> vecTesting,vector<float> vecTraining){
    vector<float> diffPerSample;

    for(int i=0;i<_nbSample2Use;i++){
        float difference = abs(vecTesting[i]-vecTraining[i]);
        diffPerSample.push_back(difference);
    }
    float sum = 0;
    for(int i=0;i<diffPerSample.size();i++){
        sum += diffPerSample[i];
    }
    float mean = sum/diffPerSample.size();
    return mean;
}

//Add the result predicted to a vector
void Algorithm1::add2PredictedResult(multimap<int, vector<float>> training,vector<float> firstResult) {
    multimap<int,vector<float>>::iterator itTraining;
    int indMin = min_element(firstResult.begin(),firstResult.end()) - firstResult.begin();
    int j=0;
    for(itTraining=training.begin();itTraining!=training.end();itTraining++) {
        if (j == indMin) {
            _predictedResult.push_back((*itTraining).first);
            itTraining = training.end();
        }
        j++;
    }
}

