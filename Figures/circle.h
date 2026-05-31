#pragma once

#include <string>
#include "figure.h"

class Circle : public Figure {
private:
    Point c;
    double r;

public:
    Circle(Point c, double r) : c(c), r(r) {}

    Point getCenter() const { return c; }
    double getRadius() const { return r; }

    double calc_perimeter() const override {
        return 2 * 3.1415 * r;
    }

    std::string name() const override {
        return "Circle";
    }
};
