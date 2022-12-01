
#include <iostream>
#include <getopt.h>
#include "data.hpp"
using namespace std;

static void help(void);

static struct option opts[] = {
	{ "help", 0, 0, 'h' },
	{ "readData", 1, 0, 'r' },
	{ "guess", 1, 0, 'g' },
	{ "compare", 1, 0, 'c' },
};

int main(int argc, char *argv[]){
    int c, option_index = 0;
    int p=0;
    //Data test;
    c = getopt_long(argc, argv, "hr:g:c :", opts,
            &option_index);
    switch (c)
    {
        case 'h':
            help();
            break;

        case 'r':
            cout<<"r";

            //p=test.readFile(argv[2]);
            break;

        case 'g':
            cout<<"g";
            break;

        case 'c':
            cout<<"c";
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


