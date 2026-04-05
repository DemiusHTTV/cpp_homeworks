#include <cassert>
#include <iostream>
#include "Header.h"

static void test_addition_over_leap_day() {
    DateTime dt(2024, 2, 28, 23, 0, 0);
    DateTime next = dt + 2;  // should cross leap day into March 1, 2024
    assert(next == DateTime(2024, 3, 1, 23, 0, 0));
}

static void test_day_of_week() {
    // 2024-03-01 is Friday => ISO 5
    DateTime dt(2024, 3, 1);
    assert(dt.dayOfWeek() == 5);

    // 2000-01-01 was Saturday => ISO 6
    DateTime dt2(2000, 1, 1);
    assert(dt2.dayOfWeek() == 6);
}

int main() {
    test_addition_over_leap_day();
    test_day_of_week();
    std::cout << "All tests passed" << std::endl;
    return 0;
}
