#pragma once

class Rational {
private:
   

public:
    int num;
    int denom;
    
    Rational();
    Rational(int n);
    Rational(int n, int d);

    Rational& operator += (const Rational& r);
    Rational operator + (const Rational& r) const;
    Rational operator -() const;
    Rational operator - (const Rational& r) const;
    Rational& operator -= (const Rational& r);
    Rational& operator ++();
    Rational operator ++(int);
    bool operator == (const Rational& r) const;
    bool operator != (const Rational& r) const;
    operator int() const;
    operator double() const;
    Rational& operator *= (const Rational& r);
    Rational operator * (const Rational& r) const;
    Rational& operator /= (const Rational& r);
    Rational operator / (const Rational& r) const;
};

void printR(const Rational& r);
void squareEquation(const Rational& a, const Rational& b, const Rational& c);