#include <iostream>
#include "headers/Rational.h"

using namespace std;

void squareEquation(const Rational& a, const Rational& b, const Rational& c) {
    if (a == 0) {
        if (b == 0) {
            cout << "Нет решения\n";
            return;
        }

        Rational x = -c / b;
        simplify(x);
        cout << "x = " << x << endl;
        return;
    }

    Rational D = b * b - a * 4 * c;
    simplify(D);

    cout << "D = " << D << endl;

    if (D < 0) {
        cout << "Нет вещественных корней\n";
        return;
    }

    Rational sqrtD = squareVavilon(D, 10);

    Rational x1 = (-b + sqrtD) / (a * 2);
    Rational x2 = (-b - sqrtD) / (a * 2);

    simplify(x1);
    simplify(x2);

    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
}

int main() {
    Rational a, b, c;

    cout << "a (num denom): ";
    cin >> a;

    cout << "b (num denom): ";
    cin >> b;

    cout << "c (num denom): ";
    cin >> c;

    simplify(a);
    simplify(b);
    simplify(c);

    cout << "\n--- Тестирование арифметики ---\n";

    Rational sum = a + b;
    cout << "a + b = " << sum << "\n";

    Rational diff = a - b;
    cout << "a - b = " << diff << "\n";

    Rational prod = a * b;
    cout << "a * b = " << prod << "\n";

    Rational quot = a / b;
    cout << "a / b = " << quot << "\n";

    Rational negA = -a;
    cout << "-a = " << negA << "\n";

    cout << "a == b? " << (a == b ? "true" : "false") << "\n";
    cout << "a < b? " << (a < b ? "true" : "false") << "\n";

    Rational r1(8, 12);
    simplify(r1);
    cout << "8/12 simplified = " << r1 << "\n";

    cout << "\n--- Квадратное уравнение ---\n";
    squareEquation(a, b, c);

    return 0;
}