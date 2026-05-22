#include <iostream>
#include "Function.h"
#include "Parabola.h"
#include "Exponenta.h"
#include "Hiperbola.h"
#include "Polinom.h"
#include <cmath>
#include <iomanip>
#include <vector>

static bool approxEqual(double a, double b, double eps)
{
    return std::abs(a - b) <= eps;
}

static void printCheck(const char* title, double got, double expected, double eps)
{
    std::cout << title << "\n";
    std::cout << "  got      = " << std::setprecision(15) << got << "\n";
    std::cout << "  expected = " << std::setprecision(15) << expected << "\n";
    std::cout << "  |diff|   = " << std::setprecision(15) << std::abs(got - expected) << "\n";
    std::cout << "  ok?      = " << (approxEqual(got, expected, eps) ? "YES" : "NO") << "\n\n";
}

int main(){
    std::vector<Function*> functions;
    functions.push_back(new Parabola()); 
    functions.push_back(new Exponenta());
    functions.push_back(new Hiperbola()); 
    functions.push_back(new Polinom(1, -2, 1)); 
    for (Function* f : functions) {
        double integral;
        double derivative;

        std::cout << "f(2) = " << f->calc(2) << "\n";

        if (f->integrate(1, 3, 1000, integral)) {
            std::cout << "Integral [1;3] = " << integral << "\n";
        }

        if (f->derivative(2, 0.001, derivative)) {
            std::cout << "Derivative x=2 = " << derivative << "\n";
        }
        std::cout<< std::endl;
    }

    for (Function* f : functions) {
        delete f;
    }

    std::cout << "All checks printed above.\n";
    return 0;
}
    
