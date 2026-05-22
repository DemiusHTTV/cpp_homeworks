#pragma once
#include <string>

class Figure {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimeter() = 0;
    virtual std::string name() = 0;

    virtual ~Figure() {}
};
struct Point {
    double x, y;
};