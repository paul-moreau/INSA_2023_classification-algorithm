//
// Created by Paul on 25/01/2023.
//

#include "compareAlgo.hpp"

CompareAlgo::CompareAlgo(Data data4Testing, Data data4Training) {
    _data4Testing = data4Testing;
    _data4Training = data4Training;
}

void CompareAlgo::print(){
    cout << "------------------------PRINT  COMP------------------------" << endl;
    cout << "data d'entrainement : " << endl;
    _data4Training.print();
    cout << "data de test : " << endl;
    _data4Testing.print();
    cout << "percentage per algo : " << endl;
    multimap<Algorithm*,int>::iterator it;
    for(it=_percentagePerAlgo.begin();it!=_percentagePerAlgo.end();it++){
        cout << "algo 1 = " << (*it).second << endl;
    }
    cout << "-----------------------------------------------------------" << endl;
}

void CompareAlgo::whichAlgo(vector<Algorithm*> algos2Test){
    cout << "-------------ADD ALGOS-------------" << endl;
    vector<Algorithm*>::iterator it;
    for(it = algos2Test.begin();it!=algos2Test.end();it++){
        _percentagePerAlgo.insert(pair<Algorithm*,int>((*it),0));
    }
    cout << algos2Test.size() << " algorithmes a tester ajoutes" << endl;
    cout << "-----------------------------------" << endl;
}
void CompareAlgo::testerAlgo() {
    multimap<Algorithm*,int>::iterator it;
    for(it=_percentagePerAlgo.begin();it!=_percentagePerAlgo.end();it++){
        (*it).first->print();
        (*it).first->traiter(_data4Training,_data4Testing);
        (*it).first->print();
        multimap<int,vector<float>> data4Testing = _data4Testing.getData();
        multimap<int,vector<float>>::iterator itData;
        int result = 0;
        int goodResult = 0;
        int i = 0;
        for(itData = data4Testing.begin();itData!=data4Testing.end();itData++){
            if((*it).first->getPredictedResult()[i] == (*itData).first){
                goodResult++;
            }
            i++;
        }
        result = 100 * goodResult / data4Testing.size();
        (*it).second = result;
    }
}
