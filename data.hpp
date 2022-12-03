#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;


class Data{
    private:
        int _nbData;                            //Nombre de données total enregistrés dans la multimap (=nombre de clés de la multimap)
        int _nbSampleMax;                       //Nombre de caractéristiques par données (=nombre de valeurs dans chaque vecteur)
        bool _training;                         //true => données pour l'apprentissage, false => données à tester, à revoir peut-être
        multimap<int,vector<float>> _data;      //multimap contenant les données (int, clé) ainsi que leurs caractéristiques (vector<float>, valeurs)
        
    public:
        Data();
        Data(int nbData, int nbSampleMax, bool training);
        ~Data();

        void print() const;

        //getters de la classe
        int getNbData() const {return _nbData;}
        int getNbSampleMax() const {return _nbSampleMax;}
        bool isTraining() const {return _training;}
        multimap<int,vector<float>> getData() const {return _data;}
        
        int readFile(string pathFile);
        int howMuch(int key) const;
        
};
#endif
