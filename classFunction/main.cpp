#include <iostream>
#include "Function.h"
#include "Parabola.h"
#include "Exponenta.h"
#include "Hiperbola.h"
#include "Polinom.h"
#include <cmath>
#include <iomanip>

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
    std::cout << std::fixed;

    // ===== Parabola: f(x) = x^2 =====
    // Точная производная: f'(x) = 2x
    // Точный интеграл на [0,1]: ∫0..1 x^2 dx = 1/3
    Parabola parabola;

    {
        const double x = 3.0;
        const double h = 1e-6;
        double deriv = 0.0;
        if (!parabola.derivative(x, h, deriv))
        {
            std::cout << "Parabola derivative: invalid args\n";
            return 1;
        }
        printCheck("Parabola f(x)=x^2: derivative at x=3 (central difference)",
                   deriv,
                   2.0 * x,
                   1e-6);
    }

    {
        const double a = 0.0;
        const double b = 1.0;
        const int n = 100000; // чем больше n, тем точнее метод трапеций
        double integral = 0.0;
        if (!parabola.integrate(a, b, n, integral))
        {
            std::cout << "Parabola integrate: invalid args\n";
            return 1;
        }
        printCheck("Parabola f(x)=x^2: integral on [0,1] (trapezoid rule)",
                   integral,
                   1.0 / 3.0,
                   1e-6);
    }

    // ===== Exponenta: f(x) = e^x =====
    // Производная e^x равна e^x.
    Exponenta exponenta;
    {
        const double x = 1.0;
        const double h = 1e-6;
        double deriv = 0.0;
        if (!exponenta.derivative(x, h, deriv))
        {
            std::cout << "Exponenta derivative: invalid args\n";
            return 1;
        }
        printCheck("Exponenta f(x)=e^x: derivative at x=1 (central difference)",
                   deriv,
                   std::exp(x),
                   1e-6);
    }

    // ===== Polinom: P(x) = 1 + 2x + 3x^2 =====
    // Это такой же квадратичный полином, как и парабола, только с коэффициентами.
    Polinom p(1.0, 2.0, 3.0);
    {
        const double x = 2.0;
        const double got = p.calc(x);
        const double expected = 1.0 + 2.0 * x + 3.0 * x * x;
        printCheck("Polinom P(x)=1+2x+3x^2: value at x=2",
                   got,
                   expected,
                   0.0);
    }


    Hiperbola hiperbola;
    {
        const double x = 2.0;
        const double h = 1e-6;
        double deriv = 0.0;
        if (!hiperbola.derivative(x, h, deriv))
        {
            std::cout << "Hiperbola derivative: invalid args\n";
            return 1;
        }
        printCheck("Hiperbola f(x)=1/x: derivative at x=2 (central difference)",
                   deriv,
                   -1.0 / (x * x),
                   1e-6);
    }

    std::cout << "All checks printed above.\n";
    return 0;
}
    
