#pragma once

class DateTime {
private:
		int year;
	int mounth;
	int day;
	int hours;
	int minutes;
	int seconds;
	

public:
	DateTime();
	DateTime(int y, int mm, int dd,int hh, int mm, int ss);
	DateTime(int year, int mounth, int day);
	DateTime(int hh, int mm, int ss);
	DateTime::operator+(int daysToAdd);
 	bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;

	bool isValid() const;
	bool isLeapYear(int y) const;
	int dayInMounth(int m,int y) const;


}