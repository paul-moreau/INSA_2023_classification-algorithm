
#include <iostream>
#include <getopt.h>
#include "data.hpp"
#include "algorithm1.hpp"
#include "algorithm2.hpp"
#include "compareAlgo.hpp"


static void help(void);
static void readData(char *argv[],int argc, int c);
static void guess(char *argv[],int argc, int c);
static void compare(char *argv[], int argc, int c);

static struct option opts[] = {
	{ "help", 0, 0, 'h' },
	{ "readData", 1, 0, 'r' },
	{ "guess", 1, 0, 'g' },
	{ "compare", 1, 0, 'c' },
};
/*int main(){
    Data dataTrain;
    dataTrain.readExistingFile("../data/train.txt");
    dataTrain.print();

    Data dataTest;
    dataTest.readExistingFile("../data/test.txt");
    dataTest.print();

    Algorithm1* algo = new Algorithm1();
    algo->print();
    algo->traiter(dataTrain,dataTest);
    //algo->print();
    CompareAlgo* comparatif = new CompareAlgo(dataTest,dataTrain);
    vector<Algorithm*> algos2Test;
    algos2Test.push_back(algo);
    comparatif->whichAlgo(algos2Test);
    comparatif->testerAlgo();
}*/

int main(int argc, char *argv[]){
    int c, option_index = 0;
    int p=0;
    c = getopt_long(argc, argv, "hr:g:c :", opts,
            &option_index);

    switch (c)
    {
        case 'h':
            help();
            break;

        case 'r':
            readData(argv, argc, c);
            break;

        case 'g':
            guess(argv, argc, c);
            break;

        case 'c':
            compare(argv, argc, c);
            break;
    }
    return 0;

}

static void help(void){
	printf( "UsageTest: main.exe [options] ...\n"
		"  -h --help\t\t\tPrint this help message\n"
		"  -r --readData\t\t\tStore data from <file> in memory\n"
		"  -g --guess\t\t\tUse <algorithm> for <files> for <k> elements\n"
		"  -c --compare\t\t\tCompare functionning of <algorithm1> with <algorithm2> with <file> for <k> elements\n");
}

//TODO: rendre tout ça plus propre de manière générale
//TODO: ajouter commentaires
//TODO: surement possible de le faire avec un switch et en mettant un préfixe à chaque argument genre 'FILE', "exemple.txt", "TRAINING", true... etc
static void readData(char *argv[], int argc, int c){
    cout << endl;

    if((enoughArguments(argc,c))&&(notTooMuchArguments(argc,c))){
        bool training = true;
        string position = "START";
        int percentage = 100;
        string pathFile2Read = argv[2];
        string pathFile2Write = argv[3];
        //cas possibles
        // 5 : training pas par défault
        // 6 : pourcentage pas par défault
        // 7 : position pas par défault
        if(argc>=5){
            string strTraining = argv[4];
            upper(strTraining);
            if(strTraining=="TRUE"){
                training = true;
            }else{
                training = false;
            }
        }
        if(argc>=6){
            percentage = stoi(argv[5]);
        }
        if(argc>=7){
            position = argv[6];
            upper(position);
        }
        Data test;
        test.useFile(pathFile2Read,pathFile2Write,training,position,percentage);
        test.print();
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }

}

static void guess(char *argv[], int argc, int c){
    cout << endl;

    if((enoughArguments(argc,c))&&(notTooMuchArguments(argc,c))){
        string pathData4Training = argv[2];
        string pathData4Testing = argv[3];

        Data Data4Training;
        Data4Training.readExistingFile(argv[2]);
        Data4Training.print();

        Data Data4Testing;
        Data4Testing.readExistingFile(argv[3]);
        Data4Testing.print();

        int choice = 02;
        int nbSample = min(Data4Training.getNbSampleMax(),Data4Testing.getNbSampleMax());
        Algorithm* algo;
        if(argc>=5){
            string strChoice = argv[4];
            choice = stoi(strChoice);
        }
        if(argc>=6){
            string strNbSample = argv[5];
            if(stoi(strNbSample)>nbSample){
                cout << "Le nombre de sample choisi n'est pas pris en compte car il est trop grand : " << endl;
                cout << "il doit etre < " << nbSample << endl;
                cout << endl;
            }else if(stoi(strNbSample)<0){
                cout << "Le nombre de sample choisi n'est pas pris en compte car il est négatif" << endl;
                cout << endl;
            }else{
                nbSample = stoi(strNbSample);
            }
        }
        switch(choice){
            case 01:
                algo = new Algorithm1(nbSample);
                break;
            case 02:
                algo = new Algorithm2(nbSample);
                break;
            default:
                cout << "Choix inconnu : " << choice << endl;
                cout << choice << " n'est pas un choix possible, " << 02 << " sera le choix retenu." << endl;
                algo = new Algorithm2(nbSample);
                break;
        }
        algo->traiter(Data4Training,Data4Testing);
        algo->print();
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }
}

static void compare(char *argv[], int argc, int c){
    Data dataTrain;
    dataTrain.readExistingFile(argv[2]);
    dataTrain.print();

    Data dataTest;
    dataTest.readExistingFile(argv[3]);
    dataTest.print();

    CompareAlgo* comparatif = new CompareAlgo(dataTest,dataTrain);

    vector<Algorithm*> algos2Test;
    Algorithm2* algo = new Algorithm2();
    Algorithm1* algo1 = new Algorithm1();

    algos2Test.push_back(algo);
    algos2Test.push_back(algo1);

    comparatif->print();

    comparatif->whichAlgo(algos2Test);

    comparatif->print();

    comparatif->testerAlgo();

    comparatif->print();
}
