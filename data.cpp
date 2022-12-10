#include "data.hpp"
//default constructor of class Data
Data::Data(){
    _nbData = 0;
    _nbSampleMax = 0;
    _training = true;
}

//Constructor with all arguments except the multimap 
Data::Data(int nbData, int nbSampleMax, bool training){
    _nbData = nbData;
    _nbSampleMax = nbSampleMax;
    _training = training;
}

//Est ce que ça marche ? en tous cas ça compile
Data::~Data(){
    multimap<int,vector<float>>::iterator it;
    for (it=_data.begin(); it!=_data.end(); ++it){
        delete &(*it).first;
        delete[] &(*it).second;
    }

}

//Print all arguments of class Data except the multimap
//TODO: surcharge de l'opérateur << ?
void Data::print() const{
    cout << "------------PRINT  DATA------------" << endl;
    cout << "Data d'entrainement :" << _training << endl;
    cout << "nombre de Data differentes : " << endl;
    cout << this->_nbData << endl;
    cout << "nombre de Samples Maximal par Data : " << endl;
    cout << this->_nbSampleMax << endl;
    cout << "-----------------------------------" << endl;
}

//lit un fichier et remplit la multimap de la class Data
//TODO: ajouter du debug/de la gestion d'erreur ? (si le fichier existe pas ? si la "trame" du fichier n'est pas celle attendue ?)
int Data::useFile(string pathFileReaded, string pathFileWrote, bool training, int rate){

    vector<string> lines = readFile(pathFileReaded);

    _training = training;
    _nbData = stoi(lines[0]);
    _nbSampleMax = stoi(lines[1]);

    readData(lines);

    //Comptage du nombre de clés de la multimap
    //utile pour debug
    multimap<int,vector<float>>::iterator it;
    int nombreData = 0;
    for (it=_data.begin(); it!=_data.end(); ++it){
        nombreData++;
    }
    if(nombreData != _nbData){
        cout << "ERREUR: Données du fichier mal lues." << endl;
    }

    applyRate2Data(rate);
    writeFile(pathFileWrote);

    return 1;
}

//lit un fichier
vector<string> Data::readFile(string pathFile) const{

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
    return lines;
}

//met le résultat de readFile dans _data
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

//Applique un taux à _data
//TODO gérer le fait d'une division donnant un résultat non entier, ici pas pris en compte
void Data::applyRate2Data(int rate){

    multimap<int,vector<float>>::iterator it;

    int nbDataPerFigure = (_nbData/10) * rate / 100;
    _nbData = _nbData * rate / 100;

    int compteur = 0;
    int X = 100 - nbDataPerFigure;

    multimap<int,vector<float>> dataWithRate;

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
    _data = dataWithRate;
}

//Ecrit _data dans un fichier
int Data::writeFile(string pathFile){

    ofstream result (pathFile, ios::out);
    cout << "write file in " << pathFile << " started" << endl;
    multimap<int,vector<float>>::iterator it;

    if(result){
        result << "_nbData=" << _nbData << "/";
        result << "_SampleMax=" << _nbSampleMax << endl;
        for(it = _data.begin(); it != _data.end(); it++){
            result << (*it).first << " " ;
            for(float f : (*it).second){
                result << f << " ";
            }
            result << endl;
        }
        result.close();
        cout << endl;
        return 1;
    }else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
        return 0;
    }
}

//Compte le nombre de data différentes pour le même résultat
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



