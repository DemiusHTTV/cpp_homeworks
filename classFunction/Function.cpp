#include "Function.h"

bool Function::integrate(double a, double b, int n, double& outResult) const
{
    if (n <= 0)
        return false;

    const double step = (b - a) / n;

    double sum = 0.5 * (calc(a) + calc(b));
    for (int i = 1; i < n; i++)
    {
        const double x = a + step * i;
        sum += calc(x);
    }
    outResult = sum * step;
    return true;
}

bool Function::derivative(double x, double h, double& outResult) const
{
    if (h == 0.0)
        return false;

    
    outResult = (calc(x + h) - calc(x - h)) / (2.0 * h);
    return true;
}
