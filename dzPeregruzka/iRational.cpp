#include "headers/Rational.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;
Rational::Rational()
{
    num=0;
    denom=1;
}

Rational :: Rational(long long n)
{
    num=n;
    denom=1;
}
Rational :: Rational(long long n, long long d)
{
    num=n;
    denom=d;
}   

Rational& Rational::operator += (const Rational& r)
{
    num=num*r.denom+denom*r.num;
    denom=denom*r.denom;
    return *this;
}
istream& operator >>(istream& in, Rational& r)
{
in>>r.num>>r.denom;
return in;
}
ostream& operator <<(ostream& out, const Rational& r)
{
out<<r.num<<"/"<<r.denom;
return out;
}
Rational Rational::operator +(const Rational& r) const{
    Rational res(*this);
    res += r;
    return res;
}
Rational Rational::operator -() const{
    Rational r(- num, denom);
    return r;
}
Rational Rational::operator -(const Rational& r) const{
    Rational res(*this);
    res += -r;
    return res;
}
Rational& Rational::operator -= (const Rational& r){
    *this += -r;
    return *this;
}
Rational& Rational::operator ++(){
    *this += Rational(1,1);
    return *this;
}
Rational Rational :: operator ++(int){
    Rational res(*this);
    *this += Rational(1,1);
    return res;
}
Rational::operator int() const{
    return num/denom;
}
Rational::operator double() const{
    return (double)num/denom;
}
Rational& Rational::operator *= (const Rational& r){
    num=num*r.num;
    denom=denom*r.denom;
    return *this;
}
Rational Rational::operator * (const Rational& r) const{
    Rational res(*this);
    res *=r;
    return res;
}
Rational& Rational ::operator/=(const Rational& r){
    num = num*r.denom;
    denom = denom*r.num;
    return *this;
}
Rational Rational :: operator / (const Rational& r) const{
    Rational res(*this);
    res /= r;
    return res;
}
bool Rational :: operator!=(const Rational&r) const{
    return num*r.denom != denom*r.num;
}
bool Rational :: operator<(const Rational&r) const{
    return num*r.denom < denom*r.num;
}
bool Rational :: operator >(const Rational& r) const{
    return num*r.denom > denom*r.num;

}
bool Rational :: operator <=(const Rational& r) const{
    return num*r.denom <= denom*r.num;
}
bool Rational :: operator >=(const Rational& r) const{
    return num*r.denom >= denom*r.num;
}
bool Rational :: operator ==(const Rational& r) const{
    return num*r.denom == denom*r.num;
}   

Rational& simplify(Rational& r) {
    long long a = r.num;
    long long b = r.denom;

    if (a == 0) { r.denom = 1; return r; }
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    long long g = (a == 0) ? 1 : a;

    r.num   /= g;
    r.denom /= g;
    if (r.denom < 0) { r.denom = -r.denom; r.num = -r.num; }
    return r;
}



Rational fromDouble(double d) {
    uint64_t bits = *(uint64_t*)&d;

    int sign = (bits >> 63) & 1;
    int exp  = (bits >> 52) & 0x7FF;
    uint64_t mantisa = bits & 0xFFFFFFFFFFFFFULL;

    int k = exp - 1023;
    long long sgn = sign ? -1LL : 1LL;

    long long num   = (1ULL << 52) | mantisa; // скрытая единица
    long long denom = 1ULL << 52;

    if (k > 0)      num   <<= k;
    else            denom <<= (-k);

    num *= sgn;

    Rational r(num, denom);
    simplify(r);
    return r;
}



