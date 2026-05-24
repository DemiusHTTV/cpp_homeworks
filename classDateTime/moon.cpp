#include "MoonData.h"
#include <iostream>

using namespace std;

MoonData::MoonData()
    : time(), elevation(0) {}

MoonData::MoonData(DateTime t, double el)
    : time(t), elevation(el) {}

void MoonData::printTime() const {
    int h = time.getHour();
    int m = time.getMinute();
    int s = time.getSecond();

    if (h < 10) cout << "0";
    cout << h << ":";

    if (m < 10) cout << "0";
    cout << m << ":";

    if (s < 10) cout << "0";
    cout << s;
}

void MoonData::printElevation() const {
    cout << elevation;
}