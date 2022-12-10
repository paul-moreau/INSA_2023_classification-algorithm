
#include <iostream>
#include <getopt.h>
#include "data.hpp"


static void help(void);
static void readData(char *argv[],int argc);

static struct option opts[] = {
	{ "help", 0, 0, 'h' },
	{ "readData", 1, 0, 'r' },
	{ "guess", 1, 0, 'g' },
	{ "compare", 1, 0, 'c' },
};

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
            //cout << "you hit readData" << endl;
            readData(argv, argc);
            //int abcd = stoi("1");
            /*int abc ;
            abc = stoi("1");
            cout << abc << endl;*/
            break;

        case 'g':
            cout << "you hit guess" << endl;
            break;

        case 'c':
            cout << "you hit compare" << endl;
            break;
    }
    return 0;

}

static void help(void)
{
	printf( "Usage: main.exe [options] ...\n"
		"  -h --help\t\t\tPrint this help message\n"
		"  -r --readData\t\t\tStore data from <file> in memory\n"
		"  -g --guess\t\t\tUse <algorithm> for <file> for <k> elements\n"
		"  -c --compare\t\t\tCompare functionning of <algorithm1> with <algorithm2> with <file> for <k> elements\n");
}

static void readData(char *argv[],int argc){
    printAllArguments(argc, argv);
    cout << "-----------MAIN  STARTED-----------" << endl;
    cout << "argc = " << argc << endl;
    cout << "read Data started, pathfile in entry : " << argv[2] << endl;
    cout << "pathfile in exit : " << argv[5] << endl;
    string testString = argv[5];
    cout << testString << endl;
    bool training = 4;
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
    if(argc>4){
        cout << "percentage of the file : " << argv[4] << endl;
    }
    cout << "bool training is = " << training << endl;
    Data test;
    cout << "------------MAIN  ENDED------------" << endl;
    test.print();



    test.useFile(argv[2], testString, training, stoi(argv[4]));

    test.print();

    int nbOf2 = test.howMuch(2);
    cout << "There are " << nbOf2 << " data to describe the 2" << endl;


    
}
