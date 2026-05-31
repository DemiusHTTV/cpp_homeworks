#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sudoku.h"
using namespace std;

int main() {
    srand(time(0));

    Sudoku game;

    int row, col, value;

    cout << "Игра Судоку" << endl;
    cout << "Поле генерируется случайно с помощью алгоритма backtracking." << endl;
    cout << "Введите строку, столбец и число." << endl;
    cout << "Пример: 1 3 5" << endl;
    cout << "Введите 0 0 0, чтобы выйти." << endl;
    cout << "Введите строку, столбец и 0, чтобы очистить свою клетку." << endl;

    while (!game.isFull()) {
        game.print();

        cout << "\nВаш ход: ";
        cin >> row >> col >> value;

        if (!cin) {
            cout << "Ошибка ввода. Нужно вводить числа." << endl;
            return 0;
        }

        if (row == 0 && col == 0 && value == 0) {
            cout << "Вы вышли из игры." << endl;
            return 0;
        }

        row--;
        col--;

        if (value == 0) {
            if (game.clearCell(row, col)) {
                cout << "Клетка очищена." << endl;
            } else {
                cout << "Эту клетку нельзя очистить." << endl;
            }
        } else {
            if (game.makeMove(row, col, value)) {
                cout << "Ход сделан." << endl;
            } else {
                cout << "Такой ход невозможен." << endl;
            }
        }
    }

    game.print();

    if (game.isSolved()) {
        cout << "Поздравляем! Судоку решено правильно." << endl;
    } else {
        cout << "Поле заполнено, но решение неправильное." << endl;
    }

    return 0;
}
