#include <iostream>
#include <getopt.h>
#include "data.hpp"
#include "algorithm1.hpp"
#include "algorithm2.hpp"
#include "compareAlgo.hpp"

static void help(char *argv[],int argc, int c);
static void readData(char *argv[],int argc, int c);
static void guess(char *argv[],int argc, int c);
static void compare(char *argv[], int argc, int c);
static void algorithms(char *argv[], int argc, int c);

const int NUMBER_OF_AVAILABLE_ALGORITHMS = 2;

//declaration of commands available for user
static struct option opts[] = {
	{ "help", 0, 0, 'h' },
	{ "readData", 1, 0, 'r' },
	{ "guess", 1, 0, 'g' },
	{ "compare", 1, 0, 'c' },
    { "algorithms", 0, 0, 'a' }
};

int main(int argc, char *argv[]){
    int c, option_index = 0;
    int p=0;
    c = getopt_long(argc, argv, "hr:g:c :a", opts,
            &option_index);

    switch (c){
        case 'h':
            help(argv, argc, c);
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
        case 'a':
            algorithms(argv, argc, c);
            break;
    }
    return 0;

}

//print help about the program and about commands available for the program
//describe arguments of each commands
static void help(char *argv[],int argc, int c){
    if((enoughArguments(argc,argv,c))&&(notTooMuchArguments(argc,argv,c))){
        if(argc==2){
            printf( "UsageTest: classifier.exe [options] ...\n"
                    "\t-h --help\t\t\tPrint this help message\n"
                    "\t-r --readData\t\t\tStore data from <file> in memory\n"
                    "\t-g --guess\t\t\tUse <algorithm> for <files> for <k> elements\n"
                    "\t-c --compare\t\t\tCompare functionning of <algorithm1> with <algorithm2> with <file> for <k> elements\n"
                    "\t-a --algorithms\t\t\tPrint available algorithms\n");
        }else{
            string choice = argv[2];
            upper(choice);
            if((choice=="R")||(choice=="READDATA")){
                printf("-r --readData : Store data from <file> in memory\n"
                        "Example : -r pathFileIn pathFileOut percentage position\n"
                        "\t\tpathFileIn : mandatory, string\n"
                        "\t\t\tPath of the file with data for reading\n"
                        "\t\tpathFileOut : mandatory, string\n"
                        "\t\t\tPath of the file in which data will be write\n"
                        "\t\tpercentage : optional, int, default value 100\n"
                        "\t\t\tPercentage read from the file\n"
                        "\t\tposition : optional, string, start or end, default value start\n"
                        "\t\t\tRead the beginning or the end of the file \n");
            }else if((choice=="G")||(choice=="GUESS")){
                printf( "-g --guess : Use <algorithm> for <files> for <k> elements\n"
                        "Example : -g pathFileForTraining pathFileForTesting AlgorithmId k\n"
                        "\t\tpathFileForTraining : mandatory, string\n"
                        "\t\t\tPath of the file with data to train the classifier\n"
                        "\t\tpathFileForTesting : mandatory, string\n"
                        "\t\t\tPath of the file with data to test\n"
                        "\t\tAlgorithmId : mandatory, int\n"
                        "\t\t\tId of the algorithm, must be in the list of algorithm (see also -h a)\n"
                        "\t\tk : optional, int, default value maximal number of samples per data\n"
                        "\t\t\tNumber of samples per data to use, should be inferior or equal to the maximal number of samples per data \n");
            }else if((choice=="C")||(choice=="COMPARE")){
                printf( "-c --compare : Compare functionning of <algorithm1> with <algorithm2> with <files> for <k> elements\n"
                        "Example : -c pathFileForTraining  pathFileForTesting numberOfAlgorithmToCompare AlgorithmId1 ... AlgorithmIdX k\n"
                        "\t\tpathFileForTraining : mandatory, string\n"
                        "\t\t\tPath of the file with data to train the classifier\n"
                        "\t\tpathFileForTesting : mandatory, string\n"
                        "\t\t\tPath of the file with data to test\n"
                        "\t\tnumberOfAlgorithmToCompare : mandatory, int\n"
                        "\t\t\tNumber of Algorithm which will be tested\n"
                        "\t\tAlgorithmIdX : mandatory, int, \n"
                        "\t\t\tId of the algorithm, must be in the list of algorithm (see also -h a)\n"
                        "\t\t\tIt is necessary to have same number of Id as in numberOfAlgorithmToCompare \n"
                        "\t\tk : optional, int, default value maximal number of samples per data\n"
                        "\t\t\tNumber of samples per data to use, should be inferior or equal to the maximal number of samples per data \n");
            }else if((choice=="A")||(choice=="ALGORITHMS")) {
                printf("trivial");
            }else{
                printf("Unknown command");
            }
        }
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }
}

//print each available algorithms (name and Id)
static void algorithms(char *argv[],int argc, int c){
    if((enoughArguments(argc,argv,c))&&(notTooMuchArguments(argc,argv,c))){
        Algorithm1 algo1;
        cout << "Name : " << algo1.getName() << ", ID = " << algo1.getId() << endl;
        Algorithm2 algo2;
        cout << "Name : " << algo2.getName() << ", ID = " << algo2.getId() << endl;
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }
}

//read data from a file, able to read a percentage of the file and to read it from the start or from the end
static void readData(char *argv[], int argc, int c){
    cout << endl;

    if((enoughArguments(argc,argv,c))&&(notTooMuchArguments(argc,argv,c))){
        string position = "START";
        int percentage = 100;
        string pathFile2Read = argv[2];
        string pathFile2Write = argv[3];
        //cas possibles
        // 6 : pourcentage pas par défault
        // 7 : position pas par défault
        if(argc>=5){
            try{
                percentage = stoi(argv[4]);
            }catch(std::invalid_argument & e){
                cout << "Error with " << e.what() << " : invalid argument, argument must be an integer" << endl;
            }
        }
        if(argc>=6){
            position = argv[5];
            upper(position);
            if((position!="START")&&(position!="END")){
                cout << "Invalid argument, position must be 'start' or 'end'" << endl;
                cout << "Default position of lecture = 'start' " << endl;
                position = "START";
            }
        }
        cout << endl;
        Data test;
        test.useFile(pathFile2Read,pathFile2Write,position,percentage);
        test.print();
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }

}

//guess data with a file used for training the program and a file with only one algorithm
//the number of sample used, k, is optional and user-adjustable
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
        algo->process(data4Training,data4Testing);
        algo->print();
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }
}

//compare the functionning of algorithms which are selected by Id
//the number of sample used, k, is optional and user-adjustable
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
            string strNbSample = argv[5+nbAlgo2Test];
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

        comparatif->testAlgo();

        comparatif->print();
    }else{
        cout << "not enough arguments or too much arguments " << endl;
        printAllArguments(argc,argv);
    }



}
