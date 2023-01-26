//
// Created by Paul on 25/01/2023.
//

#ifndef INSA_2022_CLASSIFICATION_ALGORITHM_ALGORITHM2_HPP
#define INSA_2022_CLASSIFICATION_ALGORITHM_ALGORITHM2_HPP

#include <iostream>
#include "data.hpp"
#include "algorithm.hpp"

using namespace std;

class Algorithm2 : public Algorithm{

    public:
        Algorithm2();
        ~Algorithm2();

        void traiter(Data dataRef,Data dataUnderTest);
        float produitScalaire(vector<float> vec1, vector<float> vec2);
        float norme(vector<float> vec);
};


#endif //INSA_2022_CLASSIFICATION_ALGORITHM_ALGORITHM2_HPP
