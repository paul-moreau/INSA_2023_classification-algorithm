#include "algorithm1.hpp"

Algorithm1::Algorithm1(){
    _nbSample2Use = 70;
}

Algorithm1::~Algorithm1(){

}

vector<int> Algorithm1::traiter(Data dataRef, Data dataUnderTest) {

    cout << "coucou" << endl;

    multimap<int,vector<float>>::iterator itRef;
    multimap<int, vector<float>> ref;
    ref = dataRef.getData();

    cout << "coucou" << endl;

    multimap<int,vector<float>>::iterator itTest;
    multimap<int, vector<float>> test;
    //Problème au niveau du getter ?
    test = dataUnderTest.getData();

    vector<int> result;

    cout << "coucou" << endl;

    itTest = test.begin();
    cout << (*itTest).first << endl;
    cout << (*itTest).second.size() << endl;
    itTest = test.end();
    cout << (*itTest).first << endl;
    cout << (*itTest).second.size() << endl;

    for(itTest = test.begin(); itTest != test.end(); itTest++){
        cout << "coucou1" << endl;
        vector<float> diff;
        for(itRef = ref.begin(); itRef != ref.begin(); itRef++){
            vector<float> diffPerSample;
            vector<float> vecTest = (*itTest).second;
            vector<float> vecRef = (*itRef).second;
            for(int i=0;i<vecTest.size();i++){
                float difference = abs(vecTest[i]-vecRef[i]);
                diffPerSample.push_back(difference);
            }
            float sum;
            for(int i=0;i<diffPerSample.size();i++){
                sum += diffPerSample[i];
            }
            float mean = sum/diffPerSample.size();
            diff.push_back(mean);
        }
        cout << "coucou2" << endl;
        float min = diff[0];
        int indMin = 0;
        for(int i=1;i<diff.size();i++){
            if(diff[i]<min){
                min = diff[i];
                indMin = i;
            }
        }
        cout << "coucou3" << endl;
        int j=0;
        for(itRef=ref.begin();itRef!=ref.end();itRef++){
            if(j==indMin){
                result.push_back((*itRef).first);
                itRef = ref.end();
            }
            j++;
        }
        cout << "coucou4" << endl;
    }
    cout << "coucou end traiter" << endl;
    for(int i : result){
        cout << i << endl;
    }
    return result;
}
