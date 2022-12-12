#ifndef ALGORITHM1_HPP
#define ALGORITHM1_HPP

#include <iostream>
#include "data.hpp"
#include "algorithm.hpp"

using namespace std;

class Algorithm1 : public Algorithm{
    private:
        int _nbSample2Use;
    public:
        Algorithm1();
        ~Algorithm1();

        vector<int> traiter(Data dataRef, Data dataUnderTest);

};
#endif
