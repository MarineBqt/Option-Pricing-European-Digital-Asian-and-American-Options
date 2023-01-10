#pragma once
#include <iostream>
#include <random>
using namespace std;

class Random{
    public:
        Random(const Random&) = delete; //pas de clonage/copie constructeur

        static Random& getInstance(){
            static Random instance;
            return instance;
        }

        static double rand_unif() { return getInstance().IgeneratorUnif();}
        static double rand_norm() { return getInstance().IgeneratorNorm();}

    private:
        Random(){cout<<"Une instance"<<endl;} //constructeur
        double IgeneratorUnif(){  //generateur de nombre aléaroire 
            random_device rd;  
            mt19937 gen(rd());
            uniform_real_distribution <> dis(0,1); 
            return dis(gen);
        }
        double IgeneratorNorm(){  //generateur de nombre aléaroire 
            random_device rd;  
            mt19937 gen(rd());
            normal_distribution <> dis(0,1); 
            return dis(gen);
        }
};
