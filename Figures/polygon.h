#pragma once

#include <cmath>
#include <string>
#include <vector>
#include "figure.h"

class Polygon : public Figure {
private:
    std::vector<Point> points;

    double dist(Point p1, Point p2) const {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                         (p1.y - p2.y) * (p1.y - p2.y));
    }

public:
    Polygon(const std::vector<Point>& points) : points(points) {}

    const std::vector<Point>& getPoints() const {
        return points;
    }

    double calc_perimeter() const override {
        if (points.size() < 2) {
            return 0;
        }

        double perimeter = 0;
        for (size_t i = 0; i < points.size(); ++i) {
            perimeter += dist(points[i], points[(i + 1) % points.size()]);
        }
        return perimeter;
    }

    std::string name() const override {
        return "Polygon";
    }
};
