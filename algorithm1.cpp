#include "algorithm1.hpp"

Algorithm1::Algorithm1(){
    _nbSample2Use = 70;
}

Algorithm1::~Algorithm1(){

}

const void Algorithm1::print() {
    cout << "------------PRINT  Algo1------------" << endl;
    cout << "Number of sample to use = " << _nbSample2Use << endl;
    cout << "Affichage de result : " << endl;
    for(int i : _result){
        cout << i << " ";
    }
    cout << endl;
    cout << "-----------------------------------" << endl;
}

int Algorithm1::traiter(Data dataRef, Data dataUnderTest) {
    cout << "coucou" << endl;
    multimap<int,vector<float>>::iterator itRef;
    multimap<int, vector<float>> ref;
    ref = dataRef.getData();

    multimap<int,vector<float>>::iterator itTest;
    multimap<int, vector<float>> test;
    test = dataUnderTest.getData();

    for(itTest = test.begin(); itTest != test.end(); itTest++){
        vector<float> diff;
        for(itRef = ref.begin(); itRef != ref.end(); itRef++){
            vector<float> diffPerSample;
            vector<float> vecTest = (*itTest).second;
            vector<float> vecRef = (*itRef).second;
            for(int i=0;i<vecTest.size();i++){
                float difference = abs(vecTest[i]-vecRef[i]);
                diffPerSample.push_back(difference);
            }
            float sum = 0;
            for(int i=0;i<diffPerSample.size();i++){
                sum += diffPerSample[i];
            }
            float mean = sum/diffPerSample.size();
            diff.push_back(mean);
        }
        float min = diff[0];
        int indMin = 0;
        for(int i=1;i<diff.size();i++){
            if(diff[i]<min){
                min = diff[i];
                indMin = i;
            }
        }
        int j=0;
        for(itRef=ref.begin();itRef!=ref.end();itRef++) {
            if (j == indMin) {
                _result.push_back((*itRef).first);
                itRef = ref.end();
            }
            j++;
        }
    }
    cout << "coucou ds la fct" << endl;
    this->print();
    return 0;
}
