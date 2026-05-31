#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

class SudokuBoard {
public:
    static const int SIZE = 9;
    static const int EMPTY = 0;

private:
    int field[SIZE][SIZE];
    int solution[SIZE][SIZE];
    bool fixedCells[SIZE][SIZE];

public:
    SudokuBoard();

    void clear();
    void copyArray(int from[SIZE][SIZE], int to[SIZE][SIZE]) const;

    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);

    int (*getField())[SIZE];
    int (*getSolution())[SIZE];

    void setSolutionFromField();
    void copySolutionToField();
    void markFixedCells();

    bool canPlace(int board[SIZE][SIZE], int row, int col, int value) const;
    bool makeMove(int row, int col, int value);
    bool clearCell(int row, int col);

    bool isFixedCell(int row, int col) const;
    bool isFull() const;
    bool isSolved() const;

    void print() const;
};

#endif
