#include "utils.hpp"
#include <iostream>

//split a string with a char used for delimiter
vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

//transform a string in uppercase
void upper(string& s){
    for(auto &c : s){
            c = toupper(c);
    }
}

//print all arguments entered by the user
void printAllArguments(int argc, char* argv[]){
    cout << "--------PRINT ALL ARGUMENTS--------" << endl;
    cout << "number of arguments = " << argc - 2 << endl;
    for(int i=2;i<argc;i++){
        cout << argv[i] << endl;
    }
    cout << "-----PRINT ALL ARGUMENTS ENDED-----" << endl;
}

//Test if there is enough arguments for each commands
bool enoughArguments(int argc, char* argv[], int choice){
    bool res = false;
    switch(choice){
        case 'h':
            if(argc>1){
                res = true;
            }
            break;
        case 'r':
            if(argc>3){
                res = true;
            }
            break;

        case 'g':
            if(argc>=4){
                res = true;
            }
            break;

        case 'c':
            if(argc>=5){
                int nbAlgo2Test = stoi(argv[4]);
                if(argc>4+nbAlgo2Test){
                    res = true;
                }
            }
            break;
        case 'a':
            if(argc>1){
                res = true;
            }
    }
    return res;
}

//Test if there is not too much arguments for each commands
bool notTooMuchArguments(int argc, char* argv[], int choice){
    bool res = true;
    switch(choice){
        case 'h':
            if(argc>4){
                res = false;
            }
            break;
        case 'r':
            if(argc>6){
                res = false;
            }
            break;

        case 'g':
            if(argc>6){
                res = false;
            }
            break;

        case 'c':
            if(argc>=5){
                int nbAlgo2Test = stoi(argv[4]);
                if(argc>6+nbAlgo2Test){
                    res = false;
                }
            }
            break;
        case 'a':
            if(argc>2){
                res = false;
            }
            break;
    }
    return res;
}
