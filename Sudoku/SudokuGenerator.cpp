#include "SudokuGenerator.h"
#include <cstdlib>

void SudokuGenerator::shuffleArray(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

bool SudokuGenerator::fillBoard(int board[SudokuBoard::SIZE][SudokuBoard::SIZE], int row, int col, const SudokuBoard& rules) {
    if (row == SudokuBoard::SIZE) return true;

    int nextRow = row;
    int nextCol = col + 1;

    if (nextCol == SudokuBoard::SIZE) {
        nextRow++;
        nextCol = 0;
    }

    if (board[row][col] != SudokuBoard::EMPTY) {
        return fillBoard(board, nextRow, nextCol, rules);
    }

    int numbers[SudokuBoard::SIZE] = {1,2,3,4,5,6,7,8,9};
    shuffleArray(numbers, SudokuBoard::SIZE);

    for (int i = 0; i < SudokuBoard::SIZE; i++) {
        int value = numbers[i];

        if (rules.canPlace(board, row, col, value)) {
            board[row][col] = value;

            if (fillBoard(board, nextRow, nextCol, rules)) return true;

            board[row][col] = SudokuBoard::EMPTY;
        }
    }

    return false;
}

void SudokuGenerator::removeCells(SudokuBoard& board, int cellsToRemove) {
    int removed = 0;
    int attempts = 0;

    while (removed < cellsToRemove && attempts < 2000) {
        int row = rand() % SudokuBoard::SIZE;
        int col = rand() % SudokuBoard::SIZE;

        if (board.getCell(row, col) == SudokuBoard::EMPTY) {
            attempts++;
            continue;
        }

        int backup = board.getCell(row, col);
        board.setCell(row, col, SudokuBoard::EMPTY);

        int temp[SudokuBoard::SIZE][SudokuBoard::SIZE];
        board.copyArray(board.getField(), temp);

        int solutionsCount = solver.countSolutions(temp, board, 2);

        if (solutionsCount == 1) {
            removed++;
        } else {
            board.setCell(row, col, backup);
        }

        attempts++;
    }
}

void SudokuGenerator::generate(SudokuBoard& board, int cellsToRemove) {
    if (cellsToRemove < 20) cellsToRemove = 20;
    if (cellsToRemove > 60) cellsToRemove = 60;

    board.clear();
    fillBoard(board.getSolution(), 0, 0, board);
    board.copySolutionToField();
    removeCells(board, cellsToRemove);
    board.markFixedCells();
}
