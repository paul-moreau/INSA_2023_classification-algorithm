#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include "data.hpp"

using namespace std;

class Algorithm{
    protected:
        int _nbSample2Use;
        vector<int> _result;
    public:
        virtual int traiter(Data dataRef, Data dataUnderTest) = 0;
        vector<int> getResult() const& {return _result;};
        virtual void const print()=0;
};
#endif
