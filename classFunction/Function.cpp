#include "Function.h"

double Function::integrate(double a, double b, int n) const
{
    if (n <= 0)
        throw std::invalid_argument("n must be positive");

    const double step = (b - a) / n;

    double sum = 0.5 * (calc(a) + calc(b));
    for (int i = 1; i < n; i++)
    {
        const double x = a + step * i;
        sum += calc(x);
    }
    return sum * step;
}

double Function::derivative(double x, double h) const
{
    if (h == 0.0)
        throw std::invalid_argument("h must be non-zero");

    // Центральная разностная производная.
    return (calc(x + h) - calc(x - h)) / (2.0 * h);
}

