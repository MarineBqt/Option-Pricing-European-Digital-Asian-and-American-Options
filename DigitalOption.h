/*#pragma once
using namespace std;
#include "Option.h"
#include <iostream>

class DigitalOption : public Option
{
protected:
    double _strike;

public:
    double get_strike();

    DigitalOption(double _expiry, double strike) : Option(_expiry)
    {
        if (_expiry < 0)
        {
            cout << "error, enter positive value for _expiry" << endl;
        }
        if (strike < 0)
        {
            cout << "error, enter positive value for _strike" << endl;
        }
        else
        {
            _strike = strike;
        }
    }

    //optionName GetOptionName() override {return optionName::DigitalOption;};

    enum class optionType { digitalCall, digitalPut };
    virtual optionType GetOptionType() = 0;

    friend class BlackScholesPricer; //allows for BSP to access vanillaOption protected attributes 
};*/