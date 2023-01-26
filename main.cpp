
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
//TODO: gérer l'ordre des arguments pour que ça soit peut être + logique
//TODO: surement possible de le faire avec un switch et en mettant un préfixe à chaque argument genre 'FILE', "exemple.txt", "TRAINING", true... etc
static void readData(char *argv[], int argc, int c){
    cout << endl;

    //printAllArguments(argc, argv);

    bool training = true;
    string position = "START";
    int percentage = 100;
    string pathFile2Read, pathFile2Write;

    if((enoughArguments(argc,c))&&(notTooMuchArguments(argc,c))){
        pathFile2Read = argv[2];
        pathFile2Write = argv[3];
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
    }
    Data test;
    test.useFile(pathFile2Read,pathFile2Write,training,position,percentage);
    test.print();
    /*
    if(argc>3){
        cout << "training ? " << argv[3] << endl;
        string train = argv[3];
        upper(train);
        if(train=="TRUE"){
            training = true;
        }else{
            training = false;
        }
    }
    if(argc>4) {
        cout << "percentage of the file : " << argv[4] << endl;
    }
    //string position = argv[6];
    upper(position);
    cout << "bool training is = " << training << endl;
    Data test;
    cout << "------------MAIN  ENDED------------" << endl;
    test.print();
    test.useFile(argv[2], argv[5], training, position, stoi(argv[4]));
    test.print();
    int nbOf2 = test.howMuch(2);
    cout << "There are " << nbOf2 << " data to describe the 2" << endl;*/

}

static void guess(char *argv[], int argc, int c){
    printAllArguments(argc, argv);
    cout << "guess started, files in entry :" << endl;
    cout << "\tfor training : " << argv[2] << endl;
    cout << "\tfor testing : " << argv[3] << endl;

    Data dataTrain;
    dataTrain.readExistingFile(argv[2]);
    dataTrain.print();

    Data dataTest;
    dataTest.readExistingFile(argv[3]);
    dataTest.print();

    Algorithm1* algo = new Algorithm1();
    algo->print();
    cout << "entrée dans la fonction" << endl;
    algo->traiter(dataTrain,dataTest);
    cout << "sortie de la fonction" << endl;
    algo->print();
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
    cout << "coucou" << endl;
    comparatif->print();
    cout << "coucou" << endl;
    comparatif->whichAlgo(algos2Test);
    cout << "coucou" << endl;
    comparatif->print();
    cout << "coucou" << endl;
    comparatif->testerAlgo();
    cout << "coucou" << endl;
    comparatif->print();
}
