#pragma once

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

    DateTime operator+(int daysToAdd) const;

    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;

    bool isValid() const;
    static bool isLeapYear(int y);
    static int daysInMonth(int m, int y);

    int dayOfWeek() const;

    // Returns ordinal day of Easter Sunday within the given year (1..365/366)
    int calculateEasterDate(int y) const;
};
