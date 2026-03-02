#include "headers/Rational.h"
#include <climits>
#include <iostream>

using namespace std;
static bool mulFits(int x, int y) {
    if (x == 0 || y == 0)
        return true;
    int ax = x < 0 ? -x : x;
    int ay = y < 0 ? -y : y;
    return ax <= INT_MAX / ay;
}

Rational::Rational() : num(1), denom(1) {}
Rational::Rational(int n) : num(n), denom(1) {}
Rational::Rational(int n, int d) : num(n), denom(d == 0 ? 1 : d) {}



Rational& Rational::operator += (const Rational& r) {
     num = (numer*r.denom+denom*r.numer);
    denom *= r.denom;

    return *this;
}
Rational Rational::operator + (const Rational& r) const {
    Rational tmp(*this);
    tmp += r;
    return tmp;
}

Rational& Rational::operator -= (const Rational& r) {

    return (*this += (-r)) ;
}
Rational Rational::operator - () const {
    return Rational(-num, denom);
}

Rational& Rational::operator *= (const Rational& r) {
    long long n = 1LL * num * r.num;
    long long d = 1LL * denom * r.denom;
    num = static_cast<int>(n);
    denom = static_cast<int>(d);
 
    return *this;
}
Rational Rational::operator * (const Rational& r) const {
    Rational tmp(*this);
    tmp *= r;
    return tmp;
}

Rational& Rational::operator /= (const Rational& r) {
    long long n = 1LL * num * r.denom;
    long long d = 1LL * denom * r.num;
    if (d == 0) d = 1;
    num = static_cast<int>(n);
    denom = static_cast<int>(d);
   
    return *this;
}
Rational Rational::operator / (const Rational& r) const {
    Rational tmp(*this);
    tmp /= r;
    return tmp;
}

bool Rational::operator == (const Rational& r) const {
    return 1LL * num * r.denom == 1LL * r.num * denom;
}
bool Rational::operator !=(const Rational& r) const {
    return !(*this == r);
}

void printR(const Rational& r) {
    if (r.denom == 1) std::cout << r.num;
    else std::cout << r.num << "/" << r.denom;
}

void squareEquation(const Rational& a, const Rational& b, const Rational& c) {
    if (a.num == 0) {
        std::cout << "Это не квадратное уравнение\n";
        return;
    }
    if (!mulFits(b.num, b.num) || !mulFits(4, a.num) || !mulFits(a.num, c.num)) {
        std::cout << "Переполнение при вычислении дискриминанта\n";
        return;
    }
    Rational D = b * b - Rational(4, 1) * a * c;
    if (D.num < 0) {
        std::cout << "Действительных корней нет\n";
        return;
    }
    Rational x = (D.num >= D.denom) ? D : Rational(1, 1);
    Rational eps(1, 10000);
    for (int i = 0; i < 80; ++i) {
        if (!mulFits(x.num, D.denom) || !mulFits(D.num, x.denom)) break;
        Rational next = (x + D / x) / Rational(2, 1);
        Rational diff = next - x;
        if (diff.num < 0) diff = -diff;
        long long left = 1LL * diff.num * eps.denom;
        long long right = 1LL * eps.num * diff.denom;
        if (left < right) {
            x = next;
            break;
        }
        x = next;
    }
    Rational sqrtD = x;
    if (!mulFits(2, a.num)) {
        std::cout << "Переполнение при делителе\n";
        return;
    }
    Rational twoA = Rational(2, 1) * a;
    Rational x1 = (-b + sqrtD) / twoA;
    Rational x2 = (-b - sqrtD) / twoA;
    if (x1 == x2) {
        printR(x1);
        std::cout << "\n";
    } else {
        cout << "x1 = "; printR(x1); cout << "\n";
        cout << "x2 = "; printR(x2); cout << "\n";
    }
}