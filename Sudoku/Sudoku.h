#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku {
private:
    static const int SIZE = 9;
    static const int EMPTY = 0;

    int field[SIZE][SIZE];       // поле, которое видит игрок
    int solution[SIZE][SIZE];    // полное правильное решение
    bool fixedCells[SIZE][SIZE]; // клетки, которые были даны изначально

    bool canPlaceInBoard(int board[SIZE][SIZE], int row, int col, int value) const;
    bool fillBoard(int board[SIZE][SIZE], int row, int col);
    bool solveBoard(int board[SIZE][SIZE]);
    int countSolutions(int board[SIZE][SIZE], int limit);

    void copyBoard(int from[SIZE][SIZE], int to[SIZE][SIZE]);
    void clearBoard(int board[SIZE][SIZE]);
    void shuffleArray(int arr[], int size);

    void generateFullSolution();
    void removeCells(int cellsToRemove);
    void markFixedCells();

public:
    Sudoku();

    void generateNewGame(int cellsToRemove = 45);
    void print() const;

    bool makeMove(int row, int col, int value);
    bool clearCell(int row, int col);
    bool isFull() const;
    bool isSolved() const;
    bool isFixedCell(int row, int col) const;
};

#endif
