#ifndef SUDOKU_GENERATOR_H
#define SUDOKU_GENERATOR_H

#include "SudokuBoard.h"
#include "SudokuSolver.h"

class SudokuGenerator {
private:
    SudokuSolver solver;

    void shuffleArray(int arr[], int size);
    bool fillBoard(int board[SudokuBoard::SIZE][SudokuBoard::SIZE], int row, int col, const SudokuBoard& rules);
    void removeCells(SudokuBoard& board, int cellsToRemove);

public:
    void generate(SudokuBoard& board, int cellsToRemove = 45);
};

#endif
