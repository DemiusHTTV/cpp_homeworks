#include <iostream>
#include "Header.h"

// функция проверка 
bool check(bool cond, const char* msg) {
    if (!cond) {
        std::cout << "FAIL: " << msg << '\n';
        return false;
    }
    return true;
}

static bool test_addition_over_leap_day() {
    DateTime dt(2024, 2, 28, 23, 0, 0);
    DateTime next = dt + 2;
    return check(next == DateTime(2024, 3, 1, 23, 0, 0),
                 "add over leap day");
}

static bool test_day_of_week() {
    bool ok = true;
    ok &= check(DateTime(2024, 3, 1).dayOfWeek() == 5, "dow 2024-03-01");
    ok &= check(DateTime(2000, 1, 1).dayOfWeek() == 6, "dow 2000-01-01");
    return ok;
}

int main() {
    bool ok = true;
    ok &= test_addition_over_leap_day();
    ok &= test_day_of_week();
    if (ok) std::cout << "All tests passed\n";
    std::cout<< ok = ? 0 : 1;

    int y, m, d;
    char sep;

    cin >> y >> sep >> m >> sep >> d;

    DateTime target(y, m, d);

    string filename1 = "Moon 2/moon" + to_string(y) + ".dat";
    string filename2 = "Moon/moon" + to_string(y) + ".dat";

    ifstream file(filename1);

    if (!file.is_open()) {
        file.open(filename2);
    }

    if (!file.is_open()) {
        cerr << "Cannot open file" << endl;
        return 1;
    }

    file.ignore(1000, '\n');

    bool hasRise = false;
    bool hasCulmination = false;
    bool hasSet = false;

    MoonData rise;
    MoonData culmination;
    MoonData set;

    double prevEl = -999;
    double maxEl = -999;

    int ymd, hms;
    double t, r, el, az, fi, lg;

    while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg) {
        int fy = ymd / 10000;
        int fm = (ymd / 100) % 100;
        int fd = ymd % 100;

        DateTime cur(fy, fm, fd);

        if (cur < target) {
            continue;
        }

        if (cur > target) {
            break;
        }

        int fh = hms / 10000;
        int fmin = (hms / 100) % 100;
        int fsec = hms % 100;

        DateTime dt(fy, fm, fd, fh, fmin, fsec);

        if (el > maxEl) {
            maxEl = el;
            culmination = MoonData(dt, el);
            hasCulmination = true;
        }

        if (prevEl < 0 && el > 0 && prevEl != -999) {
            rise = MoonData(dt, el);
            hasRise = true;
        }

        if (prevEl >= 0 && el < 0 && prevEl != -999) {
            set = MoonData(dt, el);
            hasSet = true;
        }

        prevEl = el;
    }

    cout << "Date: ";
    printDate(target);
    cout << endl;

    cout << "Rise: ";
    if (hasRise) {
        rise.printTime();
    } else {
        cout << "not found";
    }
    cout << endl;

    cout << "Culmination: ";
    if (hasCulmination) {
        culmination.printTime();
        cout << " Max elevation: ";
        culmination.printElevation();
    } else {
        cout << "not found";
    }
    cout << endl;

    cout << "Set: ";
    if (hasSet) {
        set.printTime();
    } else {
        cout << "not found";
    }
    cout << endl;

    file.close();

    return 0 

}
