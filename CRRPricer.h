#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "Option.h"
#include "BinaryTree.h"
using namespace std;

class CRRPricer {
public:
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate) {
        if (option->isAsianOption() == true) {   //throw an exception if it's an AsianOption
            throw invalid_argument("received Asian Option");
        }
        else if (up > interest_rate and interest_rate > down) { //check for no arbitrage
            _option = option;
            _depth = depth;
            _interest_rate = interest_rate;
            _up = up;
            _down = down;
            _asset_price = asset_price;
        }
        else {
            cout << "error: arbitrage" << endl;
        }
    };

    CRRPricer(Option* option, int depth, double assetPrice, double interestRate, double vol)
    {
        _option = option;
        _depth = depth;
        _depth=5;
        _asset_price = assetPrice;
        _interest_rate = interestRate;
        _volatility = vol;


        double h = _option->getExpiry() / (double)depth;
        _up = exp((_interest_rate + _volatility * _volatility / 2) * h + _volatility * sqrt(h)) - 1;
        _down = exp((_interest_rate + _volatility * _volatility / 2) * h - _volatility * sqrt(h)) - 1;
        R = exp(_interest_rate * h) - 1;

    }

    double fastPower(double x, int n)
    {
        if (n == 0) {
            return 1;
        }
        if (n % 2 == 0) {
            return fastPower(x * x, n / 2);
        }
        else {
            return x * fastPower(x * x, (n - 1) / 2);
        }
    }

    BinaryTree<double> BT;

    void compute() {  //return stock price for each step n and node i
        double S;
        BT.setDepth(_depth);
        for (int n = 0; n <= _depth; n++) {
            for (int i = 0; i < n + 1; i++) {
                S = _asset_price * fastPower(1 + _up, i) * fastPower(1 + _down, n - i);
                BT.setNode(n, i, S);
            }
        }
        if (_option->isAmericanOption()) {
            double q = (_interest_rate - _down) / (_up - _down);
            AmericanTree.setDepth(_depth);
                for (int n = 0; n <= _depth; n++) {
                    for (int i = 0; i < n + 1; i++) {
                        double ivalue = _option->payoff(BT.getNode(n, i)); //S(N,i)
                        AmericanTree.setNode(n,i,H(n,i) == ivalue);
                    }   
                }
        }
    }

    double get(int n, int i) {  //return H(0,0) : price of the option
        BinaryTree<double> H_BT;
        H_BT.setDepth(_depth);
        double q = (_interest_rate - _down) / (_up - _down);
        for (int n = _depth; n >= 0; n--) {   //parcours de l'arbre invers�
            for (int i = n; i >= 0; i--) {
                if (n == _depth) { //� maturit� N  H_N(N,i)=h(S_N,i)
                    double S_N = BT.getNode(_depth, i);
                    double H_N = _option->payoff(S_N);
                    H_BT.setNode(n, i, H_N);
                }
                else {
                    double H_n = (q * H_BT.getNode(n + 1, i + 1) + (1 - q) * H_BT.getNode(n + 1, i)) / (1 + _interest_rate);
                    H_BT.setNode(n, i, H_n);
                }
            }
        }
        //H_BT.display();
        return H_BT.getNode(n, i);
    }

    double facto(int i) {
        double fac = 1;
        for (int n = 1; n <= i; n++) {
            fac *= n;
        }
        return fac;
    }

    double sum(int idx = 0) {
        double somme = 0;
        double q = (_interest_rate - _down) / (_up - _down);
        for (int i = idx; i <= _depth; i++) {
            double fac = (facto(_depth) / (facto(i) * facto(_depth - i)));
            somme += fac * fastPower(q, i) * fastPower(1 - q, _depth - i) * _option->payoff(BT.getNode(_depth, i));
            //cout << "n = " << i << " ; " << BT.getNode(_depth, i) << " ; " << somme << endl;;
        }
        return somme;
    }

    double get_Closed_From() {  //return H(0,0) : price of the option Closed Formula
        return sum()/ fastPower(1 + _interest_rate, _depth);
    }

    double operator()(bool closed_form = false) {    //void
        compute();
        if (_option->isAmericanOption())
        {
            return H(0, 0);
        }
        else if (closed_form == false) {
            return get_Closed_From(); //Price of the option : H(0,0)
        }
        else {
            return get(0, 0);
        }
    }

    // Americaines :  ----------------------------
    double H(int n, int i)
    {
        return max(get(n,i), _option->payoff(BT.getNode(n, i)));
    }

    bool getExercise(int a, int b)
    {
        return AmericanTree.getNode(a, b);
    }

private:
    Option* _option;
    int _depth;  //N
    double _asset_price; //S0
    double _up;  //U
    double _down;  //D
    double _interest_rate; //r
    double _volatility;
    double R; // pour les americaines
    BinaryTree<bool> AmericanTree; // American tree
};