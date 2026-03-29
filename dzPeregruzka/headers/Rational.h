//#pragma once
#ifndef RATIONAL_H
#define RATIONAL_H  
#include <iostream>
using namespace std;

class Rational {
private:
   

public:
    long long num;
    long long  denom;
    
    Rational();
    Rational(long long n);
    Rational(long long n, long long d);

    Rational& operator += (const Rational& r);
    Rational operator + (const Rational& r) const;
    Rational operator -() const;
    Rational operator - (const Rational& r) const;
    Rational& operator -= (const Rational& r);
    Rational& operator ++();
    Rational operator ++(int);
    operator int() const;
    operator double() const;
    Rational& operator *= (const Rational& r);
    Rational operator * (const Rational& r) const;
    Rational& operator /= (const Rational& r);
    Rational operator / (const Rational& r) const;
    bool operator != (const Rational& r) const;
    bool operator < (const Rational& r) const;
    bool operator > (const Rational& r) const;
    bool operator <= (const Rational& r) const;
    bool operator >= (const Rational& r) const; 
    bool operator == (const Rational& r) const;
   
    friend istream& operator >>(istream& in, Rational& r);
friend ostream& operator <<(ostream& out, const Rational& r);
};

void printR(const Rational& r);
Rational fromDouble(double d);
 Rational& simplify(Rational& r);
#endif
