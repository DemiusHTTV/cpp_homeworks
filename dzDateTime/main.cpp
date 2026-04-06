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
    return ok ? 0 : 1;
}
