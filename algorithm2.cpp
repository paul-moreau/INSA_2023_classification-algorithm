//
// Created by Paul on 25/01/2023.
//

#include "algorithm2.hpp"
#include <math.h>

Algorithm2::Algorithm2() {
    _nbSample2Use = 70;
    _name = "Cosine";
    _id = 02;
    _percentage = 0;
}
Algorithm2::Algorithm2(int nbSample2Use) {
    _nbSample2Use = nbSample2Use;
    _name = "Cosine";
    _id = 02;
    _percentage = 0;
}

Algorithm2::~Algorithm2(){

}

float Algorithm2::applyMethod(vector<float> vectTesting, vector<float> vecTraining){
    float prodScal = produitScalaire(vectTesting,vecTraining);
    float normeTest = norme(vectTesting);
    float normeRef = norme(vecTraining);
    return prodScal/(normeRef*normeTest);
}

void Algorithm2::add2PredictedResult(multimap<int, vector<float>> training,vector<float> firstResult) {
    multimap<int,vector<float>>::iterator itTraining;
    int indMax = max_element(firstResult.begin(),firstResult.end()) - firstResult.begin();
    int j=0;
    for(itTraining=training.begin();itTraining!=training.end();itTraining++) {
        if (j == indMax) {
            _predictedResult.push_back((*itTraining).first);
            itTraining = training.end();
        }
        j++;
    }
}

float Algorithm2::produitScalaire(vector<float> vec1, vector<float> vec2){
    float res = 0;
    if(vec1.size()!=vec2.size()){
        cout << "error for produitScalaire" << endl;
    }else{
        for(int i=0;i<vec1.size();i++){
            res += vec1[i]*vec2[i];
        }
    }
    return res;
}

float Algorithm2::norme(vector<float> vec){
    float res = 0;
    float sum = 0;
    for(int i=0;i<vec.size();i++){
        sum += vec[i] * vec[i];
    }
    res = sqrt(sum);
    return res;
}