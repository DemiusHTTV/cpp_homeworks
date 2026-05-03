#include "Field.h"

#include <clocale>
#include <iostream>

int main()
{
    std::setlocale(LC_ALL, "Russian");

    Field field(true);
    while (!field.isOver())
    {
        field.print();
        std::cout << "Ходит " << (field.isRedTurnNow() ? "красный" : "желтый")
                  << " игрок, введите ход (1-" << FIELD_WIDTH << "):\n";

        int column;
        if (!(std::cin >> column))
            return 0;

        if (!field.makeTurn(column))
            std::cout << "Некорректный ход. Повторите ввод.\n";
    }

    field.printResult();
    return 0;
}

