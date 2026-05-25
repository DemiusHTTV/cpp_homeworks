#include "maze.h"

using namespace std;

int main() {
    lairint lab;

    if (!lab.loadFromBMP("maze.bmp")) {
        return 1;
    }

    cout << "Точка старта: X=" << lab.getStart().x << ", Y=" << lab.getStart().y << endl;
    cout << "Точка финиша: X=" << lab.getFinish().x << ", Y=" << lab.getFinish().y << endl;

    lab.waveAlgorithm();
    lab.saveToBMP("solved_maze.bmp");

    return 0;
}

