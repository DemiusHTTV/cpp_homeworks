#include <iostream>
#include "Header.h"

DateTime::DateTime()
    : year(0), month(1), day(1), hour(0), minute(0), second(0) {}

DateTime::DateTime(int y, int m, int d, int h, int min, int s)
    : year(y), month(m), day(d), hour(h), minute(min), second(s) {
    if (!isValid()) {
        std::cout << "Неправильно введена дата!\n";
    }
}

DateTime::DateTime(int y, int m, int d)
    : year(y), month(m), day(d), hour(0), minute(0), second(0) {
    if (!isValid()) {
        std::cout << "Неправильно введена дата!\n";
    }
}

bool DateTime::isValid() const {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, year)) return false;
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;
    if (second < 0 || second > 59) return false;
    return true;
}

bool DateTime::isLeapYear(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return y % 4 == 0;
}

int DateTime::daysInMonth(int m, int y) {
    static const int kMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(y)) return 29;
    return kMonthDays[m - 1];
}

int DateTime::dayOfWeek() const {
    static const int monthOffsets[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int y = year;
    int m = month;
    if (m < 3) y -= 1;
    int w = (y + y/4 - y/100 + y/400 + monthOffsets[m-1] + day) % 7; // 0=Sunday
    if (w == 0) return 7;
    return w;
}

DateTime DateTime::operator+(int daysToAdd) const {
    DateTime result = *this;
    while (daysToAdd > 0) {
        int daysInCurrentMonth = daysInMonth(result.month, result.year);
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

DateTime DateTime::operator-(int daysToSub) const {
    DateTime result = *this;
    int days = daysToSub;
    while (days > 0) {
        if (result.day > 1) {
            int move = std::min(result.day - 1, days);
            result.day -= move;
            days -= move;
        } else {
            result.month--;
            if (result.month == 0) {
                result.month = 12;
                result.year--;
            }
            result.day = daysInMonth(result.month, result.year);
            days -= 1;
        }
    }
    return result;
}

int DateTime::operator-(const DateTime& other) const {
    long long j1 = gregorianToJulian(year, month, day);
    long long j2 = gregorianToJulian(other.year, other.month, other.day);
    return static_cast<int>(j1 - j2);
}
long long DateTime::gregorianToJulian(int y, int m, int d) {
    if (m <= 2) {
        y--;
        m += 12;
    }
    return 365LL * y + y / 4 - y / 100 + y / 400 + (153LL * (m - 3) + 2) / 5 + d - 1;
}

int DateTime::calculateEasterDate(int year) const {
    int a = year % 19;
    int b = year / 100;
    int c = year % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    int month = (h + l - 7 * m + 114) / 31;
    int day = ((h + l - 7 * m + 114) % 31) + 1;
    
    int dayOfYear = day;
    for (int m = 1; m < month; m++) {
        int daysInM = 31;
        if (m == 4 || m == 6 || m == 9 || m == 11) daysInM = 30;
        else if (m == 2) daysInM = isLeapYear(year) ? 29 : 28;
        dayOfYear += daysInM;
    }
    return dayOfYear;
}
bool DateTime::operator==(const DateTime& other) const {
    return year == other.year && month == other.month && day == other.day &&
           hour == other.hour && minute == other.minute && second == other.second;
}

bool DateTime::operator!=(const DateTime& other) const { return !(*this == other); }

bool DateTime::operator<(const DateTime& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    if (day != other.day) return day < other.day;
    if (hour != other.hour) return hour < other.hour;
    if (minute != other.minute) return minute < other.minute;
    return second < other.second;
}

bool DateTime::operator<=(const DateTime& other) const { return *this < other || *this == other; }

bool DateTime::operator>(const DateTime& other) const { return other < *this; }

bool DateTime::operator>=(const DateTime& other) const { return other <= *this; }
