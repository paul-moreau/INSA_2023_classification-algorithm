#include "data.hpp"

//méthode split utile pour split une string en un vector de string avec un char delimiter comme ' ' par exemple
//TODO : faire un fichier utils.cpp et mettre ce genre de méthodes qui n'ont rien à voir avec la classe en question (ici Data)
vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

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

//TODO: destructeur par default de la classe Data (détruire une multimap ??)
Data::~Data(){

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
//TODO: utiliser le retour de la fonction au lieu de juste un return 0 ?
//TODO: ici on passe d'abord les datas dans une matrice de float mais c'est surement possible de les passer dans la multimap directement
//TODO: ajouter du debug/des tests unitaires/de la gestion d'erreur ? (si le fichier existe pas ? si la "trame" du fichier n'est pas celle attendue ?)
int Data::readFile(string pathFile){
    ifstream fichier (pathFile, ios::in);
    
    vector<vector<float>> datas;

    //lecture du fichier et passage des données dans la class Data + dans une matrice de float
    if(fichier)
    {
        string line;
        vector<string> lines;
        while(getline(fichier,line)){
            lines.push_back(line);
        }
        fichier.close();
        _nbData = stoi(lines[0]);
        _nbSampleMax = stoi(lines[1]);
        for (int i=2;i<_nbData+2;i++){
            vector<string> oneLineOfData = split(lines[i],' ');
            vector<float> tempDatas;
            for(int j=0;j<_nbSampleMax+1;j++){
                tempDatas.push_back(stof(oneLineOfData[j]));
            }
            datas.push_back(tempDatas);
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    
    //Transformation de la matrice de float en une multimap de int/float
    for(vector<float> vf : datas){
        int key = vf[0];
        //cout << "key =" << key << endl;
        vector<float> temp;
        //cout << vf.size() << endl;
        for(int i=1;i<vf.size();i++){
            //cout << i << endl;
            temp.push_back(vf[i]);
        }
        _data.insert(pair<int,vector<float>>(key,temp));
    }
    
    //Affichage de toute les clés de la multimap
    //Comptage puis affichage du nombre de clés de la multimap
    //utile pour debug
    /*multimap<int,vector<float>>::iterator it;
    int nombreData = 0;
    cout << "_data contains:\n";
    for (it=_data.begin(); it!=_data.end(); ++it){
        nombreData++;
        cout << (*it).first << ' ';
    }
    cout<<endl;
    cout << "nb data = " << nombreData << endl;
    */

   //Début de gestion d'un fichier en écriture, à voir si on le fait et si oui quelle "trame" de fichier on choisit 
   /*ofstream result ("result.txt", ios::out);
    if(result){
        cout << datas.size();
        result << "size datas = " << datas.size() << endl;
        result << "_nbData = " << _nbData << endl;
        for(vector<float> vf : datas){
            for(float f : vf){
                result << f << ' ';
            }
            result << endl;
        }
    }else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
    }*/
    
    return 0;
}