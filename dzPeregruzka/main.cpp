#include <iostream>
#include "headers/Rational.h"
using namespace std;



void squareEquation(const Rational& a, const Rational& b, const Rational& c){
   double aDouble=double(a);
   double bDouble= double(b);
   double cDouble=double(c);
    
    if(aDouble==0.0){
        if(bDouble == 0.0){
            cout<<"нет решения"<<endl;
            return;;
        }
        double x = -(bDouble / cDouble);
        cout<<"x= "<<x;
        return;
    }
    double D = bDouble *bDouble - 4.0 *aDouble*cDouble;
    if(D <0.0) {cout<< "Нет вещественных корней";}
    double sqrtD = sqrt(D);
       Rational x1 = fromDouble((-bDouble + sqrtD) / (2.0 * aDouble));
       Rational x2 = fromDouble((-bDouble - sqrtD) / (2.0 * aDouble));
       cout << "x1 ≈ " << x1 << ", x2 ≈ " << x2 << "\n";
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

    double tw =0.75;
   
    cout<<"tw = "<<fromDouble(tw)<<endl;
squareEquation(a, b, c);

    return 0;
}
