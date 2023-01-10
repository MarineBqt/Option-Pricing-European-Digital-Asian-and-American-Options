#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Option {
public:
    Option(double expiry) { _expiry = expiry; }; //constructeur Option(double expiry):_expiry(expiry){}
    virtual ~Option(){}; //
    double getExpiry() { return _expiry; };
    virtual double payoff(double) = 0;  //fonction h 
    virtual double payoffPath(vector<double> vec) { // return h(St1..Stm)
        return payoff(vec.back()); //return h(Stm) de base
    }
    virtual bool isAsianOption() { return false; }
    virtual bool isAmericanOption() { return false; }
protected:
    double _expiry;
};

class VanillaOption : public Option {
public:
    VanillaOption(double expiry, double strike) :Option(expiry) { if (strike >= 0 and expiry >= 0) { _strike = strike; } };
    //~VanillaOption(){}; //
    enum class optionType { call, put };
    virtual optionType GetOptionType() = 0;
protected:
    double _strike;
    friend class BlackScholesPricer;
    friend class BlackScholesMCPricer;

};

class DigitalOption : public Option {
public:
    DigitalOption(double expiry, double strike) :Option(expiry) { if (strike >= 0 and expiry >= 0) { _strike = strike; } };
    //~DigitalOption(){}; //
    enum class optionType { digitalCall, digitalPut };
    virtual optionType GetOptionType() = 0;
protected:
    double _strike;
    friend class BlackScholesPricer;
    friend class BlackScholesMCPricer;
};
