#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <fstream>
#include <map>
#include "utils.hpp"

class Data{
    private:
        int _nbData;                            //Nombre de données total enregistrés dans la multimap (=nombre de clés de la multimap)
        int _nbSampleMax;                       //Nombre de caractéristiques par données (=nombre de valeurs dans chaque vecteur)
        bool _training;                         //true => données pour l'apprentissage, false => données à tester, à revoir peut-être
        multimap<int,vector<float>> _data;      //multimap contenant les données (int, clé) ainsi que leurs caractéristiques (vector<float>, valeurs)
        
    public:
        Data();

        void print() const;

        //getters de la classe
        int getNbData() const {return _nbData;}
        int getNbSampleMax() const {return _nbSampleMax;}
        multimap<int,vector<float>> getData() const& {return _data;}
        
        int useFile(string pathFileReaded, string pathFileWrote, string position, int rate=100);
        int writeFile(string pathFile);
        vector<string> readFile(string pathFile) const;
        void readData(vector<string> lines);
        void applyRate2Data(int rate, string position);

        int readExistingFile(string pathFile);

        int howMuch(int key) const;
        
};
#endif
