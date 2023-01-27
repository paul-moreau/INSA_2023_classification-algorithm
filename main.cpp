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

    if((enoughArguments(argc,argv,c))&&(notTooMuchArguments(argc,argv,c))){
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

    if((enoughArguments(argc,argv,c))&&(notTooMuchArguments(argc,argv,c))){
        string pathData4Training = argv[2];
        string pathData4Testing = argv[3];

        Data data4Training;
        data4Training.readExistingFile(pathData4Training);
        data4Training.print();

        Data data4Testing;
        data4Testing.readExistingFile(pathData4Testing);
        data4Testing.print();

        int choice = 02;
        int nbSample = min(data4Training.getNbSampleMax(),data4Testing.getNbSampleMax());
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
                cout << "Choix d'algorithme inconnu : " << choice << endl;
                cout << choice << " n'est pas un choix possible, " << 02 << " sera le choix retenu." << endl;
                algo = new Algorithm2(nbSample);
                break;
        }
        algo->traiter(data4Training,data4Testing);
        algo->print();
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }
}

static void compare(char *argv[], int argc, int c){
    cout << endl;

    if((enoughArguments(argc,argv,c))&&(notTooMuchArguments(argc,argv,c))){
        string pathData4Training = argv[2];
        string pathData4Testing = argv[3];

        Data data4Training;
        data4Training.readExistingFile(pathData4Training);
        data4Training.print();

        Data data4Testing;
        data4Testing.readExistingFile(pathData4Testing);
        data4Testing.print();

        int nbSample = min(data4Training.getNbSampleMax(),data4Testing.getNbSampleMax());

        int nbAlgo2Test = stoi(argv[4]);
        
        if(argc > 5+nbAlgo2Test){
            string strNbSample = argv[4+nbAlgo2Test];
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

        vector<Algorithm*> algo2Test;
        for(int i=5;i<5+nbAlgo2Test;i++){
            Algorithm* algo;
            int choice = stoi(argv[i]);
            switch(choice){
                case 01:
                    algo = new Algorithm1(nbSample);
                    break;
                case 02:
                    algo = new Algorithm2(nbSample);
                    break;
                default:
                    cout << "Choix d'algorithme inconnu : " << choice << endl;
                    cout << choice << " n'est pas un choix possible, " << 02 << " sera le choix retenu." << endl;
                    algo = new Algorithm2(nbSample);
                    break;
            }
            algo2Test.push_back(algo);
        }

        CompareAlgo* comparatif = new CompareAlgo(data4Testing,data4Training);

        comparatif->whichAlgo(algo2Test);

        comparatif->testerAlgo();

        comparatif->print();
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }



}
