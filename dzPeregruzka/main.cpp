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

  cout << "\n--- Тестирование арифметики ---\n";

// сложение
Rational sum = a + b;
cout << "a + b = " << sum << "\n";

// вычитание
Rational diff = a - b;
cout << "a - b = " << diff << "\n";

// умножение
Rational prod = a * b;
cout << "a * b = " << prod << "\n";

// деление
Rational quot = a / b;
cout << "a / b = " << quot << "\n";

// унарный минус
Rational negA = -a;
cout << "-a = " << negA << "\n";

// сравнения
cout << "a == b? " << (a == b ? "true" : "false") << "\n";
cout << "a < b? " << (a < b ? "true" : "false") << "\n";

// упрощение
Rational r1(8,12); 
simplify(r1);
cout << "8/12 simplified = " << r1 << "\n";

// FromDouble
double x = 0.75;
Rational r2 = FromDouble(x);
cout << "FromDouble(0.75) = " << r2 << "\n";

squareEquation(a, b, c);
    return 0;
}