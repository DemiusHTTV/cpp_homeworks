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

Rational :: Rational(int n)
{
    num=n;
    denom=1;
}
Rational :: Rational(int n, int d)
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

Rational& simplify (Rational& r){
    int a =r.num;
    int b =r.denom;
    while(b!=0){
        int t=b;
        b=a%b;
        a=t;
    }
    int g =a;
    r.num /= g;
    r.denom /= g;
    if(r.denom<0){
        r.denom=-r.denom;
        r.num=-r.num;}
    return r;
}

Rational FromDouble(double d, double eps = 1e-6, int maxDenom = 1000) {
    int denom = 1;
    int num = 0;

    while (denom <= maxDenom) {
        num = round(d * denom);  
        if (abs(d - (double)num / denom) < eps) {
            break; 
        }
        denom++;
    }

    Rational r(num, denom);
    simplify(r); 
    return r;
}
bool isPerfectSquare(int n) {
    if (n < 0) return false;
    int r = (int)std::sqrt(n);
    return r*r == n;
}
Rational sqrtRational(const Rational&r){
 if (!isPerfectSquare(r.num) || !isPerfectSquare(r.denom)) {
        throw std::runtime_error("Дискриминант не является квадратом рационального числа");
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
