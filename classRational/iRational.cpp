#include "headers/Rational.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

Rational::Rational() {
    num = 0;
    denom = 1;
}

Rational::Rational(long long n) {
    num = n;
    denom = 1;
}

Rational::Rational(long long n, long long d) {
    if (d == 0) {
        throw invalid_argument("Rational: denominator is zero");
    }

    num = n;
    denom = d;
    simplify(*this);
}

Rational& Rational::operator+=(const Rational& r) {
    long long firstPart;
    long long secondPart;
    long long newNum;
    long long newDenom;

    try {
        if (__builtin_mul_overflow(num, r.denom, &firstPart)) {
            throw overflow_error("overflow in += numerator");
        }

        if (__builtin_mul_overflow(denom, r.num, &secondPart)) {
            throw overflow_error("overflow in += numerator");
        }

        if (__builtin_add_overflow(firstPart, secondPart, &newNum)) {
            throw overflow_error("overflow in += addition");
        }

        if (__builtin_mul_overflow(denom, r.denom, &newDenom)) {
            throw overflow_error("overflow in += denominator");
        }

        num = newNum;
        denom = newDenom;
        simplify(*this);
    }
    catch (const overflow_error& e) {
        cout << "Ошибка переполнения в operator+=: " << e.what() << endl;
        throw;
    }

    return *this;
}

istream& operator>>(istream& in, Rational& r) {
    in >> r.num >> r.denom;

    if (r.denom == 0) {
        throw invalid_argument("Rational: denominator is zero");
    }

    simplify(r);
    return in;
}

ostream& operator<<(ostream& out, const Rational& r) {
    out << r.num << "/" << r.denom;
    return out;
}

Rational Rational::operator+(const Rational& r) const {
    Rational res(*this);
    res += r;
    return res;
}

Rational Rational::operator-() const {
    return Rational(-num, denom);
}

Rational Rational::operator-(const Rational& r) const {
    Rational res(*this);
    res += -r;
    return res;
}

Rational& Rational::operator-=(const Rational& r) {
    *this += -r;
    return *this;
}

Rational& Rational::operator++() {
    *this += Rational(1);
    return *this;
}

Rational Rational::operator++(int) {
    Rational res(*this);
    *this += Rational(1);
    return res;
}

Rational::operator int() const {
    return num / denom;
}

Rational::operator double() const {
    return (double)num / denom;
}

Rational& Rational::operator*=(const Rational& r) {
    num = num * r.num;
    denom = denom * r.denom;
    simplify(*this);
    return *this;
}

Rational Rational::operator*(const Rational& r) const {
    Rational res(*this);
    res *= r;
    return res;
}

Rational& Rational::operator/=(const Rational& r) {
    if (r.num == 0) {
        throw invalid_argument("Rational: division by zero");
    }

    num = num * r.denom;
    denom = denom * r.num;
    simplify(*this);
    return *this;
}

Rational Rational::operator/(const Rational& r) const {
    Rational res(*this);
    res /= r;
    return res;
}

// операции с int справа

Rational& Rational::operator+=(int n) {
    *this += Rational(n);
    return *this;
}

Rational& Rational::operator-=(int n) {
    *this -= Rational(n);
    return *this;
}

Rational& Rational::operator*=(int n) {
    *this *= Rational(n);
    return *this;
}

Rational& Rational::operator/=(int n) {
    if (n == 0) {
        throw invalid_argument("Rational: division by zero");
    }

    *this /= Rational(n);
    return *this;
}

Rational Rational::operator+(int n) const {
    return *this + Rational(n);
}

Rational Rational::operator-(int n) const {
    return *this - Rational(n);
}

Rational Rational::operator*(int n) const {
    return *this * Rational(n);
}

Rational Rational::operator/(int n) const {
    if (n == 0) {
        throw invalid_argument("Rational: division by zero");
    }

    return *this / Rational(n);
}

// сравнения Rational с Rational

bool Rational::operator!=(const Rational& r) const {
    return num * r.denom != denom * r.num;
}

bool Rational::operator<(const Rational& r) const {
    return num * r.denom < denom * r.num;
}

bool Rational::operator>(const Rational& r) const {
    return num * r.denom > denom * r.num;
}

bool Rational::operator<=(const Rational& r) const {
    return num * r.denom <= denom * r.num;
}

bool Rational::operator>=(const Rational& r) const {
    return num * r.denom >= denom * r.num;
}

bool Rational::operator==(const Rational& r) const {
    return num * r.denom == denom * r.num;
}

// сравнения Rational с int

bool Rational::operator==(int n) const {
    return *this == Rational(n);
}

bool Rational::operator!=(int n) const {
    return *this != Rational(n);
}

bool Rational::operator<(int n) const {
    return *this < Rational(n);
}

bool Rational::operator>(int n) const {
    return *this > Rational(n);
}

bool Rational::operator<=(int n) const {
    return *this <= Rational(n);
}

bool Rational::operator>=(int n) const {
    return *this >= Rational(n);
}

// операции, где int слева

Rational operator+(int n, const Rational& r) {
    return Rational(n) + r;
}

Rational operator-(int n, const Rational& r) {
    return Rational(n) - r;
}

Rational operator*(int n, const Rational& r) {
    return Rational(n) * r;
}

Rational operator/(int n, const Rational& r) {
    return Rational(n) / r;
}

bool operator==(int n, const Rational& r) {
    return Rational(n) == r;
}

bool operator!=(int n, const Rational& r) {
    return Rational(n) != r;
}

bool operator<(int n, const Rational& r) {
    return Rational(n) < r;
}

bool operator>(int n, const Rational& r) {
    return Rational(n) > r;
}

bool operator<=(int n, const Rational& r) {
    return Rational(n) <= r;
}

bool operator>=(int n, const Rational& r) {
    return Rational(n) >= r;
}

Rational& simplify(Rational& r) {
    long long a = r.num;
    long long b = r.denom;

    if (a == 0) {
        r.denom = 1;
        return r;
    }

    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }

    long long g = a;

    r.num /= g;
    r.denom /= g;

    if (r.denom < 0) {
        r.denom = -r.denom;
        r.num = -r.num;
    }

    return r;
}

Rational fromDouble(double d) {
    uint64_t bits = *(uint64_t*)&d;

    int sign = (bits >> 63) & 1;
    int exp = (bits >> 52) & 0x7FF;
    uint64_t mantisa = bits & 0xFFFFFFFFFFFFFULL;

    int k = exp - 1023;
    long long sgn = sign ? -1LL : 1LL;

    long long num = (1ULL << 52) | mantisa;
    long long denom = 1ULL << 52;

    if (k > 0) {
        num <<= k;
    }
    else {
        denom <<= (-k);
    }

    num *= sgn;

    Rational r(num, denom);
    simplify(r);
    return r;
}

Rational squareVavilon(Rational& r, int iterations) {
    try {
        if (r < 0) {
            throw invalid_argument("sqrt from negative");
        }

        if (r == 0) {
            return Rational(0);
        }

        Rational cur = r;

        for (int i = 0; i < iterations; i++) {
            cur = cur + r / cur;
            cur /= 2;
            simplify(cur);
        }

        return cur;
    }
    catch (const exception& e) {
        cout << "Ошибка в Вавилонском алгоритме: " << e.what() << endl;
        return Rational(0);
    }
}