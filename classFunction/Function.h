#pragma once

class Function{
public:
    virtual ~Function() = default;
    virtual double calc(double x) = 0;
};
