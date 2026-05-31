#include <cmath>
#include <iostream>
#include <vector>

#include "figure.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"
#include "polygon.h"

using namespace std;

const double PI = 3.1415;

double triangleArea(Point a, Point b, Point c) {
    return abs((a.x * (b.y - c.y) +
                b.x * (c.y - a.y) +
                c.x * (a.y - b.y)) / 2.0);
}

double polygonArea(const vector<Point>& points) {
    if (points.size() < 3) {
        return 0;
    }

    double sum = 0;
    for (size_t i = 0; i < points.size(); ++i) {
        const Point& current = points[i];
        const Point& next = points[(i + 1) % points.size()];
        sum += current.x * next.y - next.x * current.y;
    }
    return abs(sum) / 2.0;
}

// Площадь считается именно в main.cpp, а не в классах фигур.
double calcArea(const Figure* figure) {
    if (const Rectangle* rectangle = dynamic_cast<const Rectangle*>(figure)) {
        Point a = rectangle->getA();
        Point b = rectangle->getB();
        Point d = rectangle->getD();

        double width = sqrt((b.x - a.x) * (b.x - a.x) +
                            (b.y - a.y) * (b.y - a.y));
        double height = sqrt((d.x - a.x) * (d.x - a.x) +
                             (d.y - a.y) * (d.y - a.y));
        return width * height;
    }

    if (const Circle* circle = dynamic_cast<const Circle*>(figure)) {
        double r = circle->getRadius();
        return PI * r * r;
    }

    if (const Triangle* triangle = dynamic_cast<const Triangle*>(figure)) {
        return triangleArea(triangle->getA(), triangle->getB(), triangle->getC());
    }

    if (const Polygon* polygon = dynamic_cast<const Polygon*>(figure)) {
        return polygonArea(polygon->getPoints());
    }

    return 0;
}

int main() {
    vector<Figure*> figures;

    figures.push_back(new Rectangle({0, 0}, {4, 0}, {4, 3}, {0, 3}));
    figures.push_back(new Circle({0, 0}, 5));
    figures.push_back(new Triangle({0, 0}, {4, 0}, {0, 3}));
    figures.push_back(new Polygon({{0, 0}, {4, 0}, {4, 3}, {0, 3}}));

    for (Figure* figure : figures) {
        cout << "Figure: " << figure->name() << endl;
        cout << "Area: " << calcArea(figure) << endl;
        cout << "Perimeter: " << figure->calc_perimeter() << endl;
        cout << endl;
    }

    for (Figure* figure : figures) {
        delete figure;
    }

    return 0;
}
