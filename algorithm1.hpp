#ifndef ALGORITHM1_HPP
#define ALGORITHM1_HPP

#include <iostream>
#include "data.hpp"
#include "algorithm.hpp"

using namespace std;

class Algorithm1 : public Algorithm{

    public:
        Algorithm1();
        Algorithm1(int nbSample2Use);
        ~Algorithm1();

        float applyMethod(vector<float> vectTesting, vector<float> vecTraining);
        void add2PredictedResult(multimap<int, vector<float>> training, vector<float> firstResult);
};
#endif
