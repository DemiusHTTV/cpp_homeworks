#pragma once
#include "Function.h"

class Parabola : public Function {
    public:
    double calc(double x) const override {
        return x*x;
    }
    private:
};
