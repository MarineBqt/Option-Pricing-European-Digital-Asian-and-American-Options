#pragma once
using namespace std;
#include "AmericanOption.h"
#include <vector>

class AmericanCallOption : public AmericanOption
{
protected:
    double _strike;

public:
    AmericanCallOption(double expiry, double strike) : AmericanOption(expiry, strike) {_strike = strike;}

    

    double payoff(double z) override
    {
        double res = 0;
        if (z >= _strike)
        {
            res = z - _strike;
        }
        return res;
    }
};