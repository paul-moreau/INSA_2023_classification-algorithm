#include "data.hpp"
//default constructor of class Data
Data::Data(){
    _nbData = 0;
    _nbSampleMax = 0;
}

//Print all arguments of class Data except the multimap
//TODO: surcharge de l'opérateur << ?
void Data::print() const{
    cout << "------------PRINT  DATA------------" << endl;
    cout << "Nombre de data differentes : ";
    cout << this->_nbData << endl;
    cout << "Nombre de samples maximal par data : ";
    cout << this->_nbSampleMax << endl;
    cout << "-----------------------------------" << endl;
    cout << endl;
}

//lit un fichier et remplit la multimap de la class Data
//TODO: ajouter du debug/de la gestion d'erreur ? (si le fichier existe pas ? si la "trame" du fichier n'est pas celle attendue ?)
int Data::useFile(string pathFileReaded, string pathFileWrote, string position, int rate){

    vector<string> lines = readFile(pathFileReaded);
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

    applyRate2Data(rate,position);
    writeFile(pathFileWrote);

    return 1;
}

//lit un fichier
//TODO: A mettre dans utils ?
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

//Ecrit _data dans un fichier
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



