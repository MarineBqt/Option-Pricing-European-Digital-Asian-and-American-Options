#include <iostream>
using namespace std;
#include "Option.h"

class PutOption : public VanillaOption {
public:
    PutOption(double expiry, double strike) :VanillaOption(expiry, strike) {};

    double payoff(double z) {
        double p = 0;
        if (z <= _strike) {
            p = _strike - z;
        }
        return p;
    }
    optionType GetOptionType() { return optionType::put; };
};