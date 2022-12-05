#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include "data.hpp"

using namespace std;

class Algorithm{
    public:
        virtual ~Algorithm(){};
        virtual vector<int> traiter(Data dataRef, Data dataUnderTest) = 0;
};
#endif
