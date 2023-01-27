#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> split (const string &s, char delim);
void upper(string& s);
bool enoughArguments(int argc, char* argv[], int choice);
bool notTooMuchArguments(int argc, char* argv[], int choice);
void printAllArguments(int argc, char* argv[]);
#endif
