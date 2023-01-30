#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>
#include <algorithm>
#include "data.hpp"

using namespace std;

class Algorithm{
    protected:
        int _nbSample2Use;
        vector<int> _predictedResult;
        string _name;
        int _id;
        float _percentage;
    public:
        void process(Data data4Training, Data data4Testing);
        void computePercentage(multimap<int,vector<float>> testing);

        virtual float applyMethod(vector<float> vecTesting, vector<float> vecTraining) = 0;
        virtual void add2PredictedResult(multimap<int, vector<float>> training,vector<float> firstResult) = 0;

        vector<int> getPredictedResult() const& {return _predictedResult;};
        string getName() const {return _name;};
        float getPercentage() const {return _percentage;};
        int getId() const {return _id;};

        void const print();
};
#endif
