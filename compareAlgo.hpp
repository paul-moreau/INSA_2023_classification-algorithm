//
// Created by Paul on 25/01/2023.
//

#ifndef INSA_2022_CLASSIFICATION_ALGORITHM_COMPAREALGO_HPP
#define INSA_2022_CLASSIFICATION_ALGORITHM_COMPAREALGO_HPP

#include <iostream>
#include "data.hpp"
#include "algorithm.hpp"
#include "algorithm1.hpp"

using namespace std;

class CompareAlgo {
    private:
        Data _data4Testing;
        Data _data4Training;
        vector<Algorithm*> _algos;

public:
    CompareAlgo(Data data4Testing, Data data4Training);
    void whichAlgo(vector<Algorithm*> algos2Test);
    void testerAlgo();
    void print();
};


#endif //INSA_2022_CLASSIFICATION_ALGORITHM_COMPAREALGO_HPP
