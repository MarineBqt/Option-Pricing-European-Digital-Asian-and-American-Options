#pragma once
using namespace std;
#include "AmericanOption.h"
#include <vector>

class AmericanPutOption : public AmericanOption
{
protected:
    double _strike;

public:
    AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) { _strike = strike; }

    double payoff(double z) override
    {
        double res = 0;
        if (z <= _strike)
        {
            res = _strike - z;
        }
        return res;
    }



};