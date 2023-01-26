//
// Created by Paul on 25/01/2023.
//

#include "algorithm.hpp"

void const Algorithm::print(){
    cout << "-------------PRINT ALGO-------------" << endl;
    cout << "Name = " << _name << endl;
    cout << "Number of sample to use = " << _nbSample2Use << endl;
    cout << "Affichage de result : " << endl;
    for(int i : _predictedResult){
        cout << i << " ";
    }
    cout << endl;
    cout << "-----------------------------------" << endl;
}
