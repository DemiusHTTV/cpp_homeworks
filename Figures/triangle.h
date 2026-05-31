#pragma once

#include <cmath>
#include <string>
#include "figure.h"

class Triangle : public Figure {
private:
    Point a, b, c;

    double dist(Point p1, Point p2) const {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                         (p1.y - p2.y) * (p1.y - p2.y));
    }

public:
    Triangle(Point a, Point b, Point c)
        : a(a), b(b), c(c) {}

    Point getA() const { return a; }
    Point getB() const { return b; }
    Point getC() const { return c; }

    double calc_perimeter() const override {
        return dist(a, b) + dist(b, c) + dist(c, a);
    }

    std::string name() const override {
        return "Triangle";
    }
};
