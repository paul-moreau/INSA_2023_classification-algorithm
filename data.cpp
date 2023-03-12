#include "data.hpp"

//default constructor of class Data
Data::Data(){
    _nbData = 0;
    _nbSampleMax = 0;
}

//Print all attributes of class Data except the multimap
void Data::print() const{
    cout << "------------PRINT  DATA------------" << endl;
    cout << "Nombre de data differentes : ";
    cout << this->_nbData << endl;
    cout << "Nombre de samples maximal par data : ";
    cout << this->_nbSampleMax << endl;
    for(auto it = _howMuchPerData.begin();it!=_howMuchPerData.end();++it){
        cout << "for " << (*it).first << ", there are " << (*it).second << " data" << endl;
    }
    cout << "-----------------------------------" << endl;
    cout << endl;
}

//read a file with the given structure
//exploit the file and store it in a multimap
//apply a rate to the read data
//write a file with our structure
int Data::useFile(string pathFileReaded, string pathFileWrote, string position, int rate){

    vector<string> lines = readFile(pathFileReaded);
    _nbData = stoi(lines[0]);
    _nbSampleMax = stoi(lines[1]);

    readData(lines);

    //Compute the number of key in the multimap
    //useful to debug
    multimap<int,vector<float>>::iterator it;
    int nombreData = 0;
    for (it=_data.begin(); it!=_data.end(); ++it){
        nombreData++;
    }
    if(nombreData != _nbData){
        cout << "ERREUR: Données du fichier mal lues." << endl;
    }
    for(int i=0;i<10;i++){
        _howMuchPerData.insert(pair(i,howMuch(i)));
    }
    if(rate!=100){
        applyRate2Data(rate,position);
    }
    writeFile(pathFileWrote);

    return 1;
}

//read a file
vector<string> Data::readFile(string pathFile) const{
    cout << "Read file in " << pathFile << " started" << endl;
    ifstream fileRead (pathFile, ios::in);
    vector<string> lines;
    if(fileRead) {
        string line;
        while (getline(fileRead, line)) {
            lines.push_back(line);
        }
        fileRead.close();
    }
    else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
    cout << "Read file in " << pathFile << " finished" << endl;
    return lines;
}

//convert the string read by readFile into a key and a vector<float> in to a multimap
void Data::readData(vector<string> lines){
    for (int i=2;i<_nbData+2;i++){
        vector<string> oneLineOfData = split(lines[i],' ');
        vector<float> tempDatas;
        for(int j=1;j<_nbSampleMax+1;j++){
            tempDatas.push_back(stof(oneLineOfData[j]));
        }
        int key = stoi(oneLineOfData[0]);
        _data.insert(pair<int, vector<float>>(key, tempDatas));
    }
}

//Apply a percentage to the read data, from the start or from the end of the multimap
//for example : read the first rate% of the file or the last rate% of the file
void Data::applyRate2Data(int rate, string position){
    int nbDataPerFigure = (_nbData/10) * rate / 100;
    _nbData = _nbData * rate / 100;

    int compteur = 0;
    int X = 100 - nbDataPerFigure;

    multimap<int,vector<float>> dataWithRate;
    if(position=="START"){
        multimap<int,vector<float>>::iterator it;
        for(it = _data.begin(); it != _data.end(); it++){
            dataWithRate.insert(pair<int, vector<float>>((*it).first, (*it).second));
            compteur++;
            if(compteur == nbDataPerFigure){
                compteur = 0;
                for(int i=0;i<X;i++){
                    it++;
                }
            }
        }
    }else{
        multimap<int,vector<float>>::reverse_iterator it;
        for(it = _data.rbegin(); it != _data.rend(); it++){
            dataWithRate.insert(pair<int, vector<float>>((*it).first, (*it).second));
            compteur++;
            if(compteur == nbDataPerFigure){
                compteur = 0;
                for(int i=0;i<X;i++){
                    it++;
                }
            }
        }
    }
    _data = dataWithRate;
}

//write _data in a file with our structure
int Data::writeFile(string pathFile){

    ofstream result (pathFile, ios::out);
    cout << "Write file in " << pathFile << " started" << endl;
    multimap<int,vector<float>>::iterator it;

    if(result){
        result << "_nbData=" << _nbData << "/";
        result << "_SampleMax=" << _nbSampleMax <<endl;
        for(it = _data.begin(); it != _data.end(); it++){
            result << (*it).first << " " ;
            for(float f : (*it).second){
                result << f << " ";
            }
            result << endl;
        }
        result.close();
        cout << "Write file in " << pathFile << " finished" << endl;
        cout << endl;
        return 1;
    }else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
        cout << "Write file in " << pathFile << " finished" << endl;
        cout << endl;
        return 0;
    }

}

//read a file with our structure
int Data::readExistingFile(string pathFile){

    vector<string> lines = readFile(pathFile);
    vector<string> firstLine = split(lines[0],'/');
    for (string s : firstLine){
        vector<string> arguments = split(s,'=');
        if(arguments[0]=="_nbData"){
            _nbData = stoi(arguments[1]);
        }else if(arguments[0]=="_SampleMax"){
            _nbSampleMax = stoi(arguments[1]);
        }
    }
    for (int i=1;i<_nbData+1;i++){
        vector<string> oneLineOfData = split(lines[i],' ');
        vector<float> tempDatas;
        for(int j=1;j<_nbSampleMax+1;j++){
            tempDatas.push_back(stof(oneLineOfData[j]));
        }
        int key = stoi(oneLineOfData[0]);
        _data.insert(pair<int, vector<float>>(key, tempDatas));
    }
    return 1;
}

//Compute the number of different data for the same result
int Data::howMuch(int key) const {
    int res = 0;
    if(!_data.empty()){
        if(0<=key<=9){
            auto it1 = _data.lower_bound(key);
            auto it2 = _data.upper_bound(key);
            while(it1 != it2){
                if(it1->first == key){
                    res++;
                }
                it1 ++ ;
            }
        }else{
            cout << "valeur recherchée doit être comprise entre 0 et 9" << endl;
            return 0;
        }
    }else{
        cout << "ERREUR: aucune donnée n'a été lue, comptage impossible" << endl;
        return 0;
    }
    return res;
}



