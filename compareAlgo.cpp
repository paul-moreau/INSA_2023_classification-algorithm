#include "compareAlgo.hpp"

//Constructor
CompareAlgo::CompareAlgo(Data data4Testing, Data data4Training) {
    _data4Testing = data4Testing;
    _data4Training = data4Training;
}

//Print compare algo, print data4Training, data4Testing and the percentage of good results predicted by algorithms
void CompareAlgo::print(){
    cout << "------------------------PRINT  COMP------------------------" << endl;
    cout << "Data for training : " << endl;
    _data4Training.print();
    cout << "Data for testing : " << endl;
    _data4Testing.print();
    cout << "Percentage per algo : " << endl;
    vector<Algorithm*>::iterator it;
    for(it=_algos.begin();it!=_algos.end();it++){
        cout << (*it)->getName() << " = " << (*it)->getPercentage() << endl;
    }
    cout << "-----------------------------------------------------------" << endl;
}

//add algo selected by user and print them
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

//Process data
void CompareAlgo::testAlgo() {
    vector<Algorithm*>::iterator it;
    for(it=_algos.begin();it!=_algos.end();it++){
        (*it)->process(_data4Training,_data4Testing);
    }
}
