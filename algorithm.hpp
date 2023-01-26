#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include "data.hpp"

using namespace std;

class Algorithm{
    protected:
        int _nbSample2Use;
        vector<int> _predictedResult;
        string _name;
    public:
        virtual void traiter(Data dataRef, Data dataUnderTest) = 0;
        vector<int> getPredictedResult() const& {return _predictedResult;};
        string getName() const {return _name;};
        void const print();
};
#endif
