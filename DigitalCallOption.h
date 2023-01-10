#include <iostream>
using namespace std;
#include "Option.h"

class DigitalCallOption : public DigitalOption {
public:
    DigitalCallOption(double expiry, double strike) :DigitalOption(expiry, strike) {};

    double payoff(double z) {
        double p = 0;
        if (z >= _strike) {
            p = 1;
        }
        return p;
    }
    optionType GetOptionType() { return optionType::digitalCall; };
};