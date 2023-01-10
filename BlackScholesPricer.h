#include <iostream>
#include <math.h>
using namespace std;
#include "Option.h"

class BlackScholesPricer {
public:
    BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility) {
        _option = option;
        _asset_price = asset_price;
        _interest_rate = interest_rate;
        _volatility = volatility;
    }
    BlackScholesPricer(DigitalOption* optiond, double asset_price, double interest_rate, double volatility) {  //
        _optionD = optiond;
        _asset_price = asset_price;
        _interest_rate = interest_rate;
        _volatility = volatility;
    }
    double operatorVanilla() {  //operator
        double d1 = (log(_asset_price / _option->_strike) + (_interest_rate + 0.5 * _volatility * _volatility) * _option->_expiry) / (_volatility * sqrt(_option->_expiry));
        double d2 = d1 - _volatility * sqrt(_option->_expiry);
        double optionPrice;
        if (_option->GetOptionType() == VanillaOption::optionType::call) {
            double N_d1 = (erf(d1 / sqrt(2)) / 2) + 0.5;
            double N_d2 = (erf(d2 / sqrt(2)) / 2) + 0.5;
            optionPrice = _asset_price * N_d1 - _option->_strike * exp(-_interest_rate * _option->_expiry) * N_d2;
        }
        else {
            double N_d1 = (erf(-d1 / sqrt(2)) / 2) + 0.5;
            double N_d2 = (erf(-d2 / sqrt(2)) / 2) + 0.5;
            optionPrice = -_asset_price * N_d1 + _option->_strike * exp(-_interest_rate * _option->_expiry) * N_d2;
        }
        return optionPrice;
    }

    double operatorDigital() {  //operator
        double d1 = (log(_asset_price / _optionD->_strike) + (_interest_rate + 0.5 * _volatility * _volatility) * _optionD->_expiry) / (_volatility * sqrt(_optionD->_expiry));
        double d2 = d1 - _volatility * sqrt(_optionD->_expiry);
        double optionPrice;
        if (_optionD->GetOptionType() == DigitalOption::optionType::digitalCall) {
            double N_d1 = (erf(d1 / sqrt(2)) / 2) + 0.5;
            double N_d2 = (erf(d2 / sqrt(2)) / 2) + 0.5;
            optionPrice = exp(-_interest_rate * _optionD->_expiry) * N_d2;
        }
        else {
            double N_d1 = (erf(-d1 / sqrt(2)) / 2) + 0.5;  //N(-d1)
            double N_d2 = (erf(-d2 / sqrt(2)) / 2) + 0.5;  //N(-d2)
            optionPrice = exp(-_interest_rate * _optionD->_expiry) * N_d2;
        }
        return optionPrice;
    }

    double operator()() {
        double optionPrice;
        if (_optionD) {
            optionPrice = operatorDigital();
        }
        else {
            optionPrice = operatorVanilla();
        }
        return optionPrice;
    }

    double deltaVanilla() {
        double d1 = (log(_asset_price / _option->_strike) + (_interest_rate + 0.5 * _volatility * _volatility) * _option->_expiry) / (_volatility * sqrt(_option->_expiry));
        double del;
        if (_option->GetOptionType() == VanillaOption::optionType::call) {

            del = (erf(d1 / sqrt(2)) / 2) + 0.5;
        }
        else {
            del = (erf(d1 / sqrt(2)) / 2) + 0.5 - 1;
        }
        return del;
    }

    double deltaDigital() {
        double d1 = (log(_asset_price / _optionD->_strike) + (_interest_rate + 0.5 * _volatility * _volatility) * _optionD->_expiry) / (_volatility * sqrt(_optionD->_expiry));
        double d2 = d1 - _volatility * sqrt(_optionD->_expiry);
        double del;
        if (_optionD->GetOptionType() == DigitalOption::optionType::digitalCall) {

            del = exp(-_interest_rate * _optionD->_expiry) * Normal_PDF(d2) / (_volatility * _optionD->_strike * sqrt(_optionD->_expiry));
        }
        else {
            del = -exp(-_interest_rate * _optionD->_expiry) * Normal_PDF(d2) / (_volatility * _optionD->_strike * sqrt(_optionD->_expiry));
        }
        return del;
    }
    double delta() {
        double del;
        if (_optionD) {
            del = deltaDigital();
        }
        else {
            del = deltaVanilla();
        }
        return del;
    }
    double Normal_PDF(const double& x) {
        const double Pi = 3.14159265358979323846;
        return (1.0 / (double)pow(2 * Pi, 0.5)) * exp(-0.5 * x * x);
    }

private:
    VanillaOption* _option;
    DigitalOption* _optionD; //
    double _asset_price;
    double _interest_rate;
    double _volatility;

};