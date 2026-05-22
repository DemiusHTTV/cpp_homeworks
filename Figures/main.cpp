#include <iostream>
#include <vector>

#include "figure.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"

using namespace std;

int main() {

    vector<Figure*> figures;

    // Rectangle
    figures.push_back(
        new Rectangle(
            {0,0},
            {4,0},
            {4,3},
            {0,3}
        )
    );

    // Circle
    figures.push_back(
        new Circle(
            {0,0},
            5
        )
    );

    // Triangle
    figures.push_back(
        new Triangle(
            {0,0},
            {4,0},
            {0,3}
        )
    );

    // Вывод через полиморфизм
    for (Figure* f : figures) {
        cout << "Figure: " << f->name() << endl;
        cout << "Area: " << f->calc_area() << endl;
        cout << "Perimeter: " << f->calc_perimeter() << endl;
     
    }

    for (Figure* f : figures) {
        delete f;
    }

    return 0;
}