#include "algorithm.hpp"

//print algorithm
//print name, the number of sample to use
//the predicted results and the percentage of good results
void const Algorithm::print(){
    cout << "-------------PRINT ALGO-------------" << endl;
    cout << "Name = " << _name << endl;
    cout << "Number of sample to use = " << _nbSample2Use << endl;
    cout << "Predicted results : " << endl;
    for(int i : _predictedResult){
        cout << i << " ";
    }
    cout << endl;
    cout << "Percentage of good results = " << _percentage << endl;
    cout << "-----------------------------------" << endl;
}

//process data from two differrent data : one for training and one for testing
void Algorithm::process(Data data4Training, Data data4Testing){
    multimap<int,vector<float>>::iterator itTraining;
    multimap<int, vector<float>> training;
    training = data4Training.getData();

    multimap<int,vector<float>>::iterator itTesting;
    multimap<int, vector<float>> testing;
    testing = data4Testing.getData();

    for(itTesting = testing.begin(); itTesting != testing.end(); itTesting++){
        vector<float> firstResult;
        for(itTraining = training.begin(); itTraining != training.end(); itTraining++){
            vector<float> vecTesting = (*itTesting).second;
            vector<float> vecTraining = (*itTraining).second;

            float f = applyMethod(vecTesting,vecTraining);
            firstResult.push_back(f);
        }
        add2PredictedResult(training,firstResult);

    }
    computePercentage(testing);
}

//Compute percentage of good results among predicted results
void Algorithm::computePercentage(multimap<int,vector<float>> testing) {
    int nbGoodResult = 0;
    int i = 0;

    multimap<int,vector<float>>::iterator itData;

    for(itData = testing.begin();itData!=testing.end();itData++){
        if(this->getPredictedResult()[i] == (*itData).first){
            nbGoodResult++;
        }
        i++;
    }
    _percentage = 100 * nbGoodResult / testing.size();
}