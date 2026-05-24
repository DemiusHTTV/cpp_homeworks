#pragma once
#include "Header.h"

struct MoonData {
    DateTime time;
    double elevation;

    MoonData();
    MoonData(DateTime t, double el);

    void printTime() const;
    void printElevation() const;
};