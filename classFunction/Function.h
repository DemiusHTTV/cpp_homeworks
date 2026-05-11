#pragma once

#include <stdexcept>

class Function{
public:
    virtual ~Function() = default;
    virtual double calc(double x) const = 0;


    double integrate(double a, double b, int n) const;
    double derivative(double x, double h) const;
};
