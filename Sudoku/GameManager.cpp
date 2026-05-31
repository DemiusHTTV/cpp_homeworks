#include "GameManager.h"
#include <iostream>
using namespace std;

GameManager::GameManager() {
    generator.generate(board, 45);
}

void GameManager::printRules() const {
    cout << "Игра Судоку\n";
    cout << "Введите строку, столбец и число от 1 до 9.\n";
    cout << "Введите 0 0 0, чтобы выйти.\n";
    cout << "Введите строку, столбец и 0, чтобы очистить свою клетку.\n";
}

void GameManager::processMove(int row, int col, int value) {
    row--;
    col--;

    if (value == 0) {
        if (board.clearCell(row, col)) cout << "Клетка очищена.\n";
        else cout << "Эту клетку нельзя очистить.\n";
        return;
    }

    if (board.makeMove(row, col, value)) {
        cout << "Ход сделан!\n";
    } else {
        cout << "Такой ход невозможен!\n";
    }
}

void GameManager::startGame() {
    int row, col, value;

    printRules();

    while (!board.isSolved()) {
        board.print();

        cout << "\nВведите строку, столбец и число: ";
        cin >> row >> col >> value;

        if (!cin) {
            cout << "Ошибка ввода.\n";
            return;
        }

        if (row == 0 && col == 0 && value == 0) {
            cout << "Вы вышли из игры.\n";
            return;
        }

        processMove(row, col, value);
    }

    board.print();
    cout << "Поздравляем! Судоку решено правильно!\n";
}
