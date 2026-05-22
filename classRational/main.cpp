#include <iostream>
#include "headers/Rational.h"
using namespace std;


void squareEquation(const Rational& a, const Rational& b, const Rational& c) {
    if (a == Rational(0)) {
        if (b == Rational(0)) {
            cout << "Нет решения\n";
            return;
        }

        Rational x = -c / b;
        simplify(x);
        cout << "x = " << x << endl;
        return;
    }

    Rational four(4);
    Rational two(2);

    Rational D = b * b - four * a * c;
    simplify(D);

    cout << "D = " << D << endl;

    if (D < Rational(0)) {
        cout << "Нет вещественных корней\n";
        return;
    }

    Rational sqrtD = squareVavilon(D, 10);

    Rational x1 = (-b + sqrtD) / (two * a);
    Rational x2 = (-b - sqrtD) / (two * a);

    simplify(x1);
    simplify(x2);

    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
}

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
cout << "a (num denom): ";
cin >> a;

cout << "b (num denom): ";
cin >> b;

cout << "c (num denom): ";
cin >> c;

    simplify(a);
    simplify(b);
    simplify(c);

    squareEquation(a, b, c);

    return 0;
}
