#pragma once
#include <iostream>
#include <vector>
#include "Option.h"
#include "MT.h"
#include "AsianOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "CRRPricer.h"

using namespace std;

class BlackScholesMCPricer {
public:

    //Constructeur -----------------------------------------------------------------------------

    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility){
        this->option = option;
        this->initial_price = initial_price;
        this->interest_rate = interest_rate;
        this->volatility = volatility;
    };

    int getNbPaths() { return nb_paths; }


    // Generation pour affiner l'estimation du prix du CALL/PUT -----------------------------------------------------------------------------
    void generate(int n) {
        double T = 0;
        if (!option->isAsianOption()) {
            T = option->getExpiry();
            nb_paths += n;
            double ST = 1;
            for (int i = 0; i < n; i++) {
                double z= Random::rand_norm();
                double ST = initial_price * exp((interest_rate - 0.5 * volatility * volatility) * T + volatility * sqrt(T) * z);
                _payoff += option->payoff(ST);
            }
            pricer = exp(-interest_rate * T) * _payoff / nb_paths;

            //actualisation
            sum += pricer;
            squaredsum += pricer * pricer;
        }
        else{
            double S0 = initial_price;
            nb_paths += n;
            AsianOption* a = dynamic_cast<AsianOption*>(option);
            vector<double> t = a->getTimeSteps();
            T = t.back();
            int m = t.size();


            // G�n�ration du payoff : -----------------------------------------------------------------------------
            for (int i = 0; i < n; i++) { // On souhaite g�n�rer n nouveau payoffs que l'on stockera pour estimer le prix et l'affiner avec la loi des grands nombres

                // G�n�ration des norm random : -----------------------------------------------------------------------------
                vector<double> z(m);
                for (int i = 0; i < m; i++) {
                    z[i] = Random::rand_norm();
                }
                // G�n�ration et actualisation de _payoff ------------------------------------------------------------------
                vector<double> St(m);
                St[0] = S0 * exp((interest_rate - volatility * volatility * 0.5) * t[0] + volatility * sqrt(t[0]) * z[0]);
                for (int j = 1; j < m; j++) {
                    St[j] = St[j - 1] * exp((interest_rate - volatility * volatility * 0.5) * (t[j] - t[j - 1]) + volatility * sqrt(t[j] - t[j - 1]) * z[j]);
                }
                _payoff += a->payoffPath(St);
            }

            //Actualisation des attributs :  -----------------------------------------------------------------------------
            pricer = _payoff * exp(-interest_rate * T) / nb_paths;
            sum += pricer;
            squaredsum += pricer * pricer;
        }
    }

    // Intervalle de confiance pour le prix du CALL/PUT: 

    vector<double> confidenceInterval() {
        double mean = sum / nb_paths;
        double var = (squaredsum / nb_paths) - mean * mean;
        return { pricer - 1.96*sqrt(var / nb_paths), pricer + 1.96 * sqrt(var / nb_paths) };
    }

    double operator()()
    {
        return pricer;
    }
    
protected:
    Option* option;
    double initial_price;
    double interest_rate;
    double volatility;
    int nb_paths;

    double _payoff;
    double pricer;

    double sum;
    double squaredsum;
};  