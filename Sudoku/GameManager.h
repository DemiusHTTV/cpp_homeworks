#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "SudokuBoard.h"
#include "SudokuGenerator.h"

class GameManager {
private:
    SudokuBoard board;
    SudokuGenerator generator;

    void printRules() const;
    void processMove(int row, int col, int value);

public:
    GameManager();
    void startGame();
};

#endif
