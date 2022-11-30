#include <iostream>
#include <fstream>
using namespace std;


class Data{
    private:
        int nbData;
        int nbSampleMax;
        
    public:
        Data();
        ~Data();
        int readFile(string file);
};
