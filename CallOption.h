#include <iostream>
using namespace std;
#include "Option.h"

class CallOption : public VanillaOption {
public:
    CallOption(double expiry, double strike) :VanillaOption(expiry, strike) {};
    double payoff(double z) {
        double p = 0;
        if (z > _strike) {
            p = z - _strike;
        }
        return p;
    }
    optionType GetOptionType() { return optionType::call; };

};