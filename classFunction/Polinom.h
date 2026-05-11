#pragma once
#include "Function.h"
#include <vector>
#include <cmath>
class Polinom: public Function {
    std::vector<double> coeffs;
public:
    Polinom(double a, double b, double c) : coeffs({a, b, c}) {}
    double calc(double x) const override{
        double res =0;
        for (std::size_t i = 0; i < coeffs.size(); i++){
            res += coeffs[i] * pow(x, i);
        }
        return res;
    }

};
