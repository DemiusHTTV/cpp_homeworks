#include <iostream>
#include<Header.h>

DateTime::DateTime(int y, int mm, int dd, int hh, int min, int ss)
    : year(y), month(mm), day(dd), hour(hh), minute(min), second(ss) {
    if (!isValid()) {
        std::cout << "Неправильно введена дата!\n";
      
    }
}
bool DateTime::isValid() const{
if(year < 0) return false;
if(mounth<1 || mounth>12) return false;
if (day<1 || day>dayInMounth(day,mounth)) return false;
if (hh<0 || hh >23) return false;
if(mm<0 ||mm>59) return false;
if (ss<0 || ss>59) return false;
return true
}
DateTime::DateTime(int y, int mm, int dd)
    : year(y), month(mm), day(dd) {
    if (!isValid()) {
            cout << "Неправильно введена дата!\n";
      
    }
}

bool DateTime::isValid() const{
if(year < 0) return false;
if(mounth<1 || mounth>12) return false;
if (day<1 || day>dayInMounth(day,mounth)) return false;
return true
}

DateTime::DateTime( int hh, int min, int ss)
    : hour(hh), minute(min), second(ss) {
    if (!isValid()) {
        std::cout << "Неправильно введена дата!\n";
      
    }
}
bool DateTime::isValid() const{
if (hh<0 || hh >23) return false;
if(mm<0 ||mm>59) return false;
if (ss<0 || ss>59) return false;
return true
}

bool DateTime::isLeapYear(int y) const{
    if(y%4==0) return true
    return false
}
int DateTime::dayInMounth(int m , int y){
    int[] arrayDayM = {31,28,31,30,31,30,31,31,30,31,30,31}
    if(m==2 and isLeapYear(y)) return 29;
    return arrayDayM[m-1];
}

DateTime DateTime::operator+(int daysToAdd) const {
    DateTime result = *this;
    while (daysToAdd > 0) {
        int daysInCurrentMonth = result.daysInMonth(result.month, result.year);
        int remainingDaysInMonth = daysInCurrentMonth - result.day;

        if (daysToAdd <= remainingDaysInMonth) {
            result.day += daysToAdd;
            daysToAdd = 0;
        } else {
            daysToAdd -= (remainingDaysInMonth + 1); 
            result.day = 1;
            result.month++;

            if (result.month > 12) {
                result.month = 1;
                result.year++;
            }
        }
    }

    return result;
}