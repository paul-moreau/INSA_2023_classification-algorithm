#ifndef ALGORITHM1_HPP
#define ALGORITHM1_HPP

#include <iostream>
#include "data.hpp"
#include "algorithm.hpp"

using namespace std;

class Algorithm1 : public Algorithm{

    public:
        Algorithm1();
        ~Algorithm1();

        int traiter(Data dataRef, Data dataUnderTest);
        void const print();

};
#endif
