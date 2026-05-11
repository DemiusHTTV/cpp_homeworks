#pragma once
#include "Function.h"
#include <cmath>

class Exponenta : public Function {
    public:
    double  calc(double x) const override {
        return std::exp(x);
    }
    private:
};
