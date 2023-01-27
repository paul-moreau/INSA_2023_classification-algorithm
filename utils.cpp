

#include "utils.hpp"
#include <iostream>
//méthode split utile pour split une string en un vector de string avec un char delimiter comme ' ' par exemple
vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

//Testée, je crois que ça fonctionne
void upper(string& s){
    for(auto &c : s){
            c = toupper(c);
    }
}

void printAllArguments(int argc, char* argv[]){
    cout << "--------PRINT ALL ARGUMENTS--------" << endl;
    cout << "nombre d'arguments = " << argc - 2 << endl;
    for(int i=2;i<argc;i++){
        cout << argv[i] << endl;
    }
    cout << "-----PRINT ALL ARGUMENTS ENDED-----" << endl;
}

//A compléter quand on sera plus précis sur ce qu'on veut pour les commandes excatement
//Pas testée
//Utile ? Pas sur que ça soit utile dans tous les cas (exemple de --help), mais dans le reste je pense que oui
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
    }
    return res;
}

//A compléter quand on sera plus précis sur ce qu'on veut pour les commandes excatement
//Pas testée
//Utile ? Pas sur que ça soit utile dans tous les cas (exemple de --help), mais dans le reste je pense que oui
bool notTooMuchArguments(int argc, char* argv[], int choice){
    bool res = true;
    switch(choice){
        case 'h':
            if(argc>2){
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
    }
    return res;
}
