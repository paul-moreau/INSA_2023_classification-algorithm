//
// Created by Paul on 25/01/2023.
//

#include "algorithm.hpp"

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
void Algorithm::traiter(Data data4Training, Data data4Testing){
    multimap<int,vector<float>>::iterator itTraining;
    multimap<int, vector<float>> training;
    training = data4Training.getData();

    multimap<int,vector<float>>::iterator itTesting;
    multimap<int, vector<float>> testing;
    testing = data4Testing.getData();
    cout << "nbOfSample2Use = " << _nbSample2Use << endl;
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