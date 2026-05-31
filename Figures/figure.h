#pragma once

#include <string>

struct Point {
    double x;
    double y;
};

class Figure {
public:
    virtual double calc_perimeter() const = 0;
    virtual std::string name() const = 0;

    virtual ~Figure() = default;
};
