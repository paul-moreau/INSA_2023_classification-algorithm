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

        float scalarProduct(vector<float> vec1, vector<float> vec2);
        float norm(vector<float> vec);

        float applyMethod(vector<float> vecTesting, vector<float> vecTraining);
        void add2PredictedResult(multimap<int, vector<float>> training, vector<float> firstResult);

};
#endif //INSA_2022_CLASSIFICATION_ALGORITHM_ALGORITHM2_HPP
