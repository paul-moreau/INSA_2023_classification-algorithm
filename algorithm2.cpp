#include "algorithm2.hpp"
#include <math.h>

//Default constructor
Algorithm2::Algorithm2() {
    _nbSample2Use = 70;
    _name = "Cosine";
    _id = 02;
    _percentage = 0;
}

//Constructor with a value for _nbSample2Use
Algorithm2::Algorithm2(int nbSample2Use) {
    _nbSample2Use = nbSample2Use;
    _name = "Cosine";
    _id = 02;
    _percentage = 0;
}

//Apply the specific method of the algorithm to the data
float Algorithm2::applyMethod(vector<float> vecTesting, vector<float> vecTraining){
    vector<float> newVecTesting, newVecTraining;
    //cout << "_nbSample2Use = " << _nbSample2Use << endl;
    for(int i=0;i<_nbSample2Use;i++){
        newVecTesting.push_back(vecTesting[i]);
        newVecTraining.push_back(vecTraining[i]);
    }
    float prodScal = produitScalaire(newVecTesting,newVecTraining);
    float normeTest = norme(newVecTesting);
    float normeRef = norme(newVecTraining);
    //cout << "prodScalaire = " << prodScal << " normeTest = " << normeTest << " normeRef"
    return prodScal/(normeRef*normeTest);
}

//Add the result predicted to a vector
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

//compute scalar product for 2 vectors
float Algorithm2::scalarProduct(vector<float> vec1, vector<float> vec2){
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

//compute the norm for a vector
float Algorithm2::norm(vector<float> vec){
    float res = 0;
    float sum = 0;
    for(int i=0;i<vec.size();i++){
        sum += vec[i] * vec[i];
    }
    res = sqrt(sum);
    return res;
}