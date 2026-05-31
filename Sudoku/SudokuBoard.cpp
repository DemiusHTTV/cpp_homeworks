#include "SudokuBoard.h"
#include <iostream>
using namespace std;

SudokuBoard::SudokuBoard() {
    clear();
}

void SudokuBoard::clear() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = EMPTY;
            solution[i][j] = EMPTY;
            fixedCells[i][j] = false;
        }
    }
}

void SudokuBoard::copyArray(int from[SIZE][SIZE], int to[SIZE][SIZE]) const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            to[i][j] = from[i][j];
        }
    }
}

int SudokuBoard::getCell(int row, int col) const {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return EMPTY;
    }
    return field[row][col];
}

void SudokuBoard::setCell(int row, int col, int value) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        field[row][col] = value;
    }
}

int (*SudokuBoard::getField())[SIZE] {
    return field;
}

int (*SudokuBoard::getSolution())[SIZE] {
    return solution;
}

void SudokuBoard::setSolutionFromField() {
    copyArray(field, solution);
}

void SudokuBoard::copySolutionToField() {
    copyArray(solution, field);
}

void SudokuBoard::markFixedCells() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fixedCells[i][j] = field[i][j] != EMPTY;
        }
    }
}

bool SudokuBoard::canPlace(int board[SIZE][SIZE], int row, int col, int value) const {
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

bool SudokuBoard::makeMove(int row, int col, int value) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false;
    if (value < 1 || value > 9) return false;
    if (fixedCells[row][col]) return false;
    if (field[row][col] != EMPTY) return false;
    if (!canPlace(field, row, col, value)) return false;

    field[row][col] = value;
    return true;
}

bool SudokuBoard::clearCell(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false;
    if (fixedCells[row][col]) return false;

    field[row][col] = EMPTY;
    return true;
}

bool SudokuBoard::isFixedCell(int row, int col) const {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false;
    return fixedCells[row][col];
}

bool SudokuBoard::isFull() const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == EMPTY) return false;
        }
    }
    return true;
}

bool SudokuBoard::isSolved() const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] != solution[i][j]) return false;
        }
    }
    return true;
}

void SudokuBoard::print() const {
    cout << "\n    1 2 3   4 5 6   7 8 9\n";
    cout << "  -------------------------\n";

    for (int i = 0; i < SIZE; i++) {
        cout << i + 1 << " | ";

        for (int j = 0; j < SIZE; j++) {
            if (field[i][j] == EMPTY) cout << ". ";
            else cout << field[i][j] << " ";

            if ((j + 1) % 3 == 0) cout << "| ";
        }

        cout << endl;

        if ((i + 1) % 3 == 0) {
            cout << "  -------------------------\n";
        }
    }
}
