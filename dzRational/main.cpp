#include <iostream>
#include "headers/Rational.h"
using namespace std;


int main() {
    Rational a, b, c;
    cout << "a (num denom): "; cin >> a.num >> a.denom;
    cout << "b (num denom): "; cin >> b.num >> b.denom;
    cout << "c (num denom): "; cin >> c.num >> c.denom;

    a = Rational(a.num, a.denom);
    b = Rational(b.num, b.denom);
    c = Rational(c.num, c.denom);

    squareEquation(a, b, c);
    return 0;
}