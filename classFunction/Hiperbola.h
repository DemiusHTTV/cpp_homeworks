#pragma once
#include "Function.h"

class Hiperbola : public Function {
    public:
    double  calc(double x) const override  {
        return 1/x;
    }

    private:
};
