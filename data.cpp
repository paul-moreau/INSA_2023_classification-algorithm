#include "data.hpp"
#include "utils.cpp"

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
    cout << "Data d'entrainement :" << _training << endl;
    cout << "nombre de Data differentes : " << endl;
    cout << this->_nbData << endl;
    cout << "nombre de Samples Maximal par Data : " << endl;
    cout << this->_nbSampleMax << endl;
}

//lit un fichier et remplit la multimap de la class Data
//TODO: réécrire dans un fichier dont on connait l'entete ? 
//TODO: ajouter du debug/des tests unitaires/de la gestion d'erreur ? (si le fichier existe pas ? si la "trame" du fichier n'est pas celle attendue ?)
int Data::readFile(string pathFile){
    ifstream fileRead (pathFile, ios::in);

    //File read and extraction of data to put them in Data class attributes 
    if(fileRead)
    {
        string line;
        vector<string> lines;
        while(getline(fileRead,line)){
            lines.push_back(line);
        }
        fileRead.close();

        _nbData = stoi(lines[0]);
        _nbSampleMax = stoi(lines[1]);

        //_data : string to int for key and string to float for caracteristics values, all in the multimap
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
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        return 0;
    }
    
    //Affichage de toute les clés de la multimap
    //Comptage puis affichage du nombre de clés de la multimap
    //utile pour debug
    multimap<int,vector<float>>::iterator it;
    int nombreData = 0;
    int test =0;
    //cout << "_data contains:\n";
    for (it=_data.begin(); it!=_data.end(); ++it){
        nombreData++;
        //cout << (*it).first << ' ';
    }
    if(nombreData != _nbData){
        cout << "ERREUR: Données du fichier mal lues." << endl;
    }
    //cout<<endl;
    //cout << "nb data = " << nombreData << endl;
    

   //Début de gestion d'un fichier en écriture, à voir si on le fait et si oui quelle "trame" de fichier on choisit 
    ofstream result ("dataRead.txt", ios::out);

    if(result){
        result << "nombreData=" << nombreData << "/";
        result << "_nbData=" << _nbData << "/";
        result << "_SampleMax=" << _nbSampleMax << endl;
        for(it = _data.begin(); it != _data.end(); ++it){
            result << (*it).first << " " ;
            for(float f : (*it).second){
                result << f << " ";
            }
            result << endl;
        }
        result.close();
    }else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
        return 0;
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