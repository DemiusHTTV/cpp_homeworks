#pragma once

#include <cmath>
#include <string>
#include "figure.h"

class Rectangle : public Figure {
private:
    Point a, b, c, d;

public:
    Rectangle(Point a, Point b, Point c, Point d)
        : a(a), b(b), c(c), d(d) {}

    Point getA() const { return a; }
    Point getB() const { return b; }
    Point getC() const { return c; }
    Point getD() const { return d; }

    double calc_perimeter() const override {
        double width = std::sqrt((b.x - a.x) * (b.x - a.x) +
                                 (b.y - a.y) * (b.y - a.y));
        double height = std::sqrt((d.x - a.x) * (d.x - a.x) +
                                  (d.y - a.y) * (d.y - a.y));
        return 2 * (width + height);
    }

    std::string name() const override {
        return "Rectangle";
    }
};
