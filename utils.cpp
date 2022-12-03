#include <vector>
#include <string>
#include <sstream>

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