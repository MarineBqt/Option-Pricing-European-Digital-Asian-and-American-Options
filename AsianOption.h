#pragma once
#include <iostream>
using namespace std;
#include "Option.h"
#include <vector>

class AsianOption : public Option
{
protected:
    vector<double> vec;


public:
    AsianOption(double _expiry, vector<double> vec) : Option(_expiry)
    {
        this->vec = vec;
    }


    vector<double> getTimeSteps()
    {
        return vec;
    }


    double payoffPath(vector<double> v) override 
    {
        double res = 0;
        double m = v.size();
        for (int i = 0; i < m; i++)
        {
            res += v[i];
        }
        res = payoff(res/m);

        return res;
    }

    bool isAsianOption() override { return true; };
    friend class BlackScholesMCPricer;

};