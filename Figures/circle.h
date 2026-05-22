#pragma once
#include <string>
#include "figure.h"
class Circle : public Figure {
    Point c;
    double r;

public:
    Circle(Point c, double r) : c(c), r(r) {}

    double calc_area() override {
        return 3.1415 * r * r;
    }

    double calc_perimeter() override {
        return 2 * 3.1415 * r;
    }

    std::string name() override {
        return "Circle";
    }
};