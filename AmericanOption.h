#pragma once
using namespace std;
#include "Option.h"
#include <vector>

class AmericanOption : public Option
{
protected:
    double _strike;


public:
    AmericanOption(double _expiry, double _strike) : Option(_expiry)
    {
        this->_strike = _strike;
    }


    bool isAmericanOption() override { return true; };


};