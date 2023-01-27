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
        Algorithm2(int nbSample2Use);
        ~Algorithm2();

        float produitScalaire(vector<float> vec1, vector<float> vec2);
        float norme(vector<float> vec);

        float applyMethod(vector<float> vectTesting, vector<float> vecTraining);
        void add2PredictedResult(multimap<int, vector<float>> training, vector<float> firstResult);

};


#endif //INSA_2022_CLASSIFICATION_ALGORITHM_ALGORITHM2_HPP
