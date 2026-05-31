#include "Sudoku.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Sudoku::Sudoku() {
    generateNewGame();
}

void Sudoku::clearBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void Sudoku::copyBoard(int from[SIZE][SIZE], int to[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            to[i][j] = from[i][j];
        }
    }
}

void Sudoku::shuffleArray(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

bool Sudoku::canPlaceInBoard(int board[SIZE][SIZE], int row, int col, int value) const {
    for (int j = 0; j < SIZE; j++) {
        if (board[row][j] == value) return false;
    }

    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == value) return false;
    }

    int startRow = row / 3 * 3;
    int startCol = col / 3 * 3;

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == value) return false;
        }
    }

    return true;
}

bool Sudoku::fillBoard(int board[SIZE][SIZE], int row, int col) {
    if (row == SIZE) {
        return true;
    }

    int nextRow = row;
    int nextCol = col + 1;

    if (nextCol == SIZE) {
        nextRow++;
        nextCol = 0;
    }

    if (board[row][col] != EMPTY) {
        return fillBoard(board, nextRow, nextCol);
    }

    int numbers[SIZE] = {1,2,3,4,5,6,7,8,9};
    shuffleArray(numbers, SIZE);

    for (int i = 0; i < SIZE; i++) {
        int value = numbers[i];

        if (canPlaceInBoard(board, row, col, value)) {
            board[row][col] = value;

            if (fillBoard(board, nextRow, nextCol)) {
                return true;
            }

            board[row][col] = EMPTY;
        }
    }

    return false;
}

bool Sudoku::solveBoard(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == EMPTY) {
                for (int value = 1; value <= 9; value++) {
                    if (canPlaceInBoard(board, row, col, value)) {
                        board[row][col] = value;

                        if (solveBoard(board)) {
                            return true;
                        }

                        board[row][col] = EMPTY;
                    }
                }
                return false;
            }
        }
    }

    return true;
}

int Sudoku::countSolutions(int board[SIZE][SIZE], int limit) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == EMPTY) {
                int count = 0;

                for (int value = 1; value <= 9; value++) {
                    if (canPlaceInBoard(board, row, col, value)) {
                        board[row][col] = value;
                        count += countSolutions(board, limit);
                        board[row][col] = EMPTY;

                        if (count >= limit) {
                            return count;
                        }
                    }
                }

                return count;
            }
        }
    }

    return 1;
}

void Sudoku::generateFullSolution() {
    clearBoard(solution);
    fillBoard(solution, 0, 0);
    copyBoard(solution, field);
}

void Sudoku::removeCells(int cellsToRemove) {
    int removed = 0;
    int attempts = 0;

    while (removed < cellsToRemove && attempts < 1000) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (field[row][col] == EMPTY) {
            attempts++;
            continue;
        }

        int backup = field[row][col];
        field[row][col] = EMPTY;

        int temp[SIZE][SIZE];
        copyBoard(field, temp);

        int solutionsCount = countSolutions(temp, 2);

        if (solutionsCount == 1) {
            removed++;
        } else {
            field[row][col] = backup;
        }

        attempts++;
    }
}

void Sudoku::markFixedCells() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fixedCells[i][j] = field[i][j] != EMPTY;
        }
    }
}

void Sudoku::generateNewGame(int cellsToRemove) {
    if (cellsToRemove < 20) cellsToRemove = 20;
    if (cellsToRemove > 60) cellsToRemove = 60;

    generateFullSolution();
    removeCells(cellsToRemove);
    markFixedCells();
}

void Sudoku::print() const {
    cout << "\n    1 2 3   4 5 6   7 8 9\n";
    cout << "  -------------------------\n";

    for (int i = 0; i < SIZE; i++) {
        cout << i + 1 << " | ";

        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == EMPTY) {
                cout << ". ";
            } else {
                cout << field[i][j] << " ";
            }

            if ((j + 1) % 3 == 0) {
                cout << "| ";
            }
        }

        cout << endl;

        if ((i + 1) % 3 == 0) {
            cout << "  -------------------------\n";
        }
    }
}

bool Sudoku::isFixedCell(int row, int col) const {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return false;
    }

    return fixedCells[row][col];
}

bool Sudoku::makeMove(int row, int col, int value) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return false;
    }

    if (value < 1 || value > 9) {
        return false;
    }

    if (fixedCells[row][col]) {
        return false;
    }

    if (field[row][col] != EMPTY) {
        return false;
    }

    if (!canPlaceInBoard(field, row, col, value)) {
        return false;
    }

    field[row][col] = value;
    return true;
}

bool Sudoku::clearCell(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return false;
    }

    if (fixedCells[row][col]) {
        return false;
    }

    field[row][col] = EMPTY;
    return true;
}

bool Sudoku::isFull() const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == EMPTY) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::isSolved() const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] != solution[i][j]) {
                return false;
            }
        }
    }

    return true;
}
