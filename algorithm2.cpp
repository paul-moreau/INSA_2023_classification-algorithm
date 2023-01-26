//
// Created by Paul on 25/01/2023.
//

#include "algorithm2.hpp"
#include <math.h>

Algorithm2::Algorithm2() {
    _nbSample2Use = 70;
    _name = "Cosine";
}

Algorithm2::~Algorithm2(){

}

void Algorithm2::traiter(Data dataRef, Data dataUnderTest){
    multimap<int,vector<float>>::iterator itRef;
    multimap<int, vector<float>> ref;
    ref = dataRef.getData();

    multimap<int,vector<float>>::iterator itTest;
    multimap<int, vector<float>> test;
    test = dataUnderTest.getData();

    for(itTest = test.begin(); itTest != test.end(); itTest++){
        vector<float> cosine;
        for(itRef = ref.begin(); itRef != ref.end(); itRef++){
            vector<float> vecTest = (*itTest).second;
            vector<float> vecRef = (*itRef).second;
            float prodScal = produitScalaire(vecTest,vecRef);
            float normeTest = norme(vecTest);
            float normeRef = norme(vecRef);
            cosine.push_back(prodScal/(normeRef*normeTest));
        }
        float max = cosine[0];
        int indMax = 0;
        for(int i=0;i<cosine.size();i++){
            if(cosine[i]>max){
                max = cosine[i];
                indMax = i;
            }
        }
        int j=0;
        for(itRef=ref.begin();itRef!=ref.end();itRef++){
            if(j==indMax){
                _predictedResult.push_back((*itRef).first);
                itRef = ref.end();
            }
            j++;
        }
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