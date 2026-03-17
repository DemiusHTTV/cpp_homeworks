#include <iostream>
#include "headers/Rational.h"
using namespace std;

bool isPerfectSquare(int n) {
    if (n < 0) return false;
    int r = (int)std::sqrt(n);
    return r*r == n;
}
Rational sqrtRational(const Rational&r){
 if (!isPerfectSquare(r.num) || !isPerfectSquare(r.denom)) {
        throw runtime_error("Дискриминант не является квадратом рационального числа");
    }
    return Rational((int)sqrt(r.num), (int)sqrt(r.denom));
}
void squareEquation(const Rational& a, const Rational& b, const Rational& c){
    if (a.num == Rational(0).num) {
        if (b.num ==Rational(0).num) {
            cout<<"нет решения"<<endl;
            return;
        }
        double x = - (double)b.num / b.denom / ((double)c.num / c.denom);
        cout << "x = " << x << "\n";
        return;
        cout << "Not a quadratic equation." << endl;
        return;
        
    }
    Rational four(4,1);
    Rational two(2,1);

    Rational D = b*b - four*a*c;
     if (D.num < 0) {
        cout << "Нет вещественных рациональных корней\n";
        return;
    }
     try {
  Rational sqrtD = sqrtRational(D);
        Rational x1 = (-b + sqrtD) / (a*two);
        Rational x2 = (-b - sqrtD) / (a*two);
        cout << "x1 = " << x1 << ", x2 = " << x2 << "\n";
    } catch (runtime_error& e) {
        cout << "Error: " << "\n";
    }
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
cout << "8/12 simplified = " << r1 << "\n";

// FromDouble
double x = 0.75;
Rational r2 = FromDouble(x);
cout << "FromDouble(0.75) = " << r2 << "\n";

squareEquation(a, b, c);
    return 0;
}