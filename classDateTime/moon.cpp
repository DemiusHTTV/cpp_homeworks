#include "Header.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <string>

using namespace std;


void printDate(const DateTime& dt) {
    dt.printFormat1(cout);
}

// Helper function to print time only
void printTime(const DateTime& dt) {
    int h = dt.getHour();
    int m = dt.getMinute();
    int s = dt.getSecond();
    
    if (h < 10) cout << "0";
    cout << h << ":";
    if (m < 10) cout << "0";
    cout << m << ":";
    if (s < 10) cout << "0";
    cout << s;
}

int main(){
    int y,m,d;
    char sep;
    cin >> y >> sep >> m >> sep >> d;

    DateTime target(y, m, d);

    string filename1 = "Moon 2/moon" + to_string(y) + ".dat";
    string filename2 = "Moon/moon" + to_string(y) + ".dat";

    ifstream file(filename1);
    if (!file.is_open()) file.open(filename2);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file. Tried: " << filename1 << " and " << filename2 << endl;
        return 1;
    }

    file.ignore(1000, '\n');

    bool hasRise = false, hasCulmination = false, hasSet = false;
    DateTime riseTime, culminationTime, setTime;
    double prevEl = -999;
    double maxEl = -999;

    int ymd, hms;
    double t, r, el, az, fi, lg;

    while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg){

        int fy = ymd/10000, fm = (ymd/100)%100, fd = ymd%100;
        DateTime cur(fy, fm, fd);

        if (cur < target) continue;
        else if (cur > target) break;

        int fh = hms/10000, fmin = (hms/100)%100, fsec = hms%100;
        DateTime dt(fy, fm, fd, fh, fmin, fsec);

        if (maxEl < el){
            maxEl = el;
            culminationTime = dt;
            hasCulmination = true;
        }

        if (prevEl < 0 && el > 0 && prevEl != -999){
            riseTime = dt;
            hasRise = true;
        }

        if (prevEl >= 0 && el < 0 && prevEl != -999){
            setTime = dt;
            hasSet = true;
        }

        prevEl = el;
    }

    cout << "Date: ";
    printDate(target);
    cout << endl;

    if (hasRise) {
        cout << "Rise: ";
        printTime(riseTime);
        cout << endl;
    } else {
        cout << "Rise: not found" << endl;
    }
    
    if (hasCulmination) {
        cout << "Culmination: ";
        printTime(culminationTime);
        cout << " (Max elevation: " << maxEl << "°)" << endl;
    } else {
        cout << "Culmination: not found" << endl;
    }
    
    if (hasSet) {
        cout << "Set: ";
        printTime(setTime);
        cout << endl;
    } else {
        cout << "Set: not found" << endl;
    }

    file.close();

    return 0;
}
