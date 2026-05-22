#pragma once
#include <string>
#include "figure.h"

class Triangle : public Figure {

    Point a, b, c;

    double dist(Point p1, Point p2) {
        return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                    (p1.y - p2.y)*(p1.y - p2.y));
    }

public:
    Triangle(Point a, Point b, Point c)
        : a(a), b(b), c(c) {}

    double calc_area() override {
        return abs(
            (a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y)) / 2.0
        );
    }

    double calc_perimeter() override {
        return dist(a,b) + dist(b,c) + dist(c,a);
    }

    std::string name() override {
        return "Triangle";
    }
};