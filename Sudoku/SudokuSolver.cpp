#include "SudokuSolver.h"

bool SudokuSolver::solveBoard(int board[SudokuBoard::SIZE][SudokuBoard::SIZE], const SudokuBoard& rules) const {
    for (int row = 0; row < SudokuBoard::SIZE; row++) {
        for (int col = 0; col < SudokuBoard::SIZE; col++) {
            if (board[row][col] == SudokuBoard::EMPTY) {
                for (int value = 1; value <= 9; value++) {
                    if (rules.canPlace(board, row, col, value)) {
                        board[row][col] = value;

                        if (solveBoard(board, rules)) return true;

                        board[row][col] = SudokuBoard::EMPTY;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int SudokuSolver::countSolutions(int board[SudokuBoard::SIZE][SudokuBoard::SIZE], const SudokuBoard& rules, int limit) const {
    for (int row = 0; row < SudokuBoard::SIZE; row++) {
        for (int col = 0; col < SudokuBoard::SIZE; col++) {
            if (board[row][col] == SudokuBoard::EMPTY) {
                int count = 0;

                for (int value = 1; value <= 9; value++) {
                    if (rules.canPlace(board, row, col, value)) {
                        board[row][col] = value;
                        count += countSolutions(board, rules, limit);
                        board[row][col] = SudokuBoard::EMPTY;

                        if (count >= limit) return count;
                    }
                }

                return count;
            }
        }
    }
    return 1;
}
