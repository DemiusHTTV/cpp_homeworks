#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include "SudokuBoard.h"

class SudokuSolver {
public:
    bool solveBoard(int board[SudokuBoard::SIZE][SudokuBoard::SIZE], const SudokuBoard& rules) const;
    int countSolutions(int board[SudokuBoard::SIZE][SudokuBoard::SIZE], const SudokuBoard& rules, int limit) const;
};

#endif
