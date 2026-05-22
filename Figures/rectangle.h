#pragma once
#include <string>
#include "figure.h"
class Rectangle : public Figure {
    Point a, b, c, d;

public:
    Rectangle(Point a, Point b, Point c, Point d)
        : a(a), b(b), c(c), d(d) {}

    double calc_area() override {
        return abs((b.x - a.x) * (d.y - a.y));
    }

    double calc_perimeter() override {
        return 2 * (abs(b.x - a.x) + abs(d.y - a.y));
    }

    std::string name() override {
        return "Rectangle";
    }
};