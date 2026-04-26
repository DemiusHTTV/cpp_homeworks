#pragma once
#include <iosfwd>

class DateTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    DateTime();
    DateTime(int y, int m, int d, int h, int min, int s);
    DateTime(int y, int m, int d);

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    DateTime operator+(int daysToAdd) const;
    DateTime operator-(int daysToSub) const;
    int operator-(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
    static long long gregorianToJulian(int y, int m, int d);
    bool isValid() const;
    static bool isLeapYear(int y);
    static int daysInMonth(int m, int y);
    int calculateEasterDate(int y) const;
    int dayOfWeek() const;

    void printFormat1(std::ostream& os) const;
};
