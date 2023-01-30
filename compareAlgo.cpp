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
    cout << "Data d'entrainement : " << endl;
    _data4Training.print();
    cout << "Data de test : " << endl;
    _data4Testing.print();
    cout << "Percentage per algo : " << endl;
    vector<Algorithm*>::iterator it;
    for(it=_algos.begin();it!=_algos.end();it++){
        cout << (*it)->getName() << " = " << (*it)->getPercentage() << endl;
    }
    cout << "-----------------------------------------------------------" << endl;
}

void CompareAlgo::whichAlgo(vector<Algorithm*> algos2Test){
    cout << "-------------ADD ALGOS-------------" << endl;
    _algos = algos2Test;
    cout << _algos.size() << " algorithme(s) a tester ajoute(s)" << endl;
    for(int i=0;i<_algos.size();i++){
        _algos[i]->print();
    }
    cout << "-----------------------------------" << endl;
    cout << endl;
}
void CompareAlgo::testerAlgo() {
    vector<Algorithm*>::iterator it;
    for(it=_algos.begin();it!=_algos.end();it++){
        (*it)->traiter(_data4Training,_data4Testing);
    }
}
