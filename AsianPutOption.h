#pragma once
#include <iostream>
using namespace std;
#include "AsianOption.h"
#include <vector>

class AsianPutOption : public AsianOption
{
protected:
    double _strike;

public:
    AsianPutOption(vector<double> vec, double strike) : AsianOption(vec.back(), vec)
    {
        _expiry = vec.back();
        _strike = strike;
    }

    double payoff(double z) override
    {
        double res = 0;
        if (z <= _strike)
        {
            res = _strike - z;
        }
        return res;
    }

    double payoffPath(vector<double> vec) override
    {
        double z = 0;
        double m = vec.size();
        double res = 0;
        for (int i = 0; i < m; i++)
        {
            z += vec[i];
        }
        z = z / m;

        //arbitrage
        res = payoff(z);
        return res;
    }

};