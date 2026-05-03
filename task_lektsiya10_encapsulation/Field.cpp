#include "Field.h"

#include <iostream>

Field::Field(bool isRedFirst)
{
    clear(isRedFirst);
}

void Field::clear(bool isRedFirst)
{
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

bool Field::makeTurn(int column)
{
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;

    int i = column - 1;
    for (int j = 0; j < FIELD_HEIGHT; j++)
        if (cells[i][j] == EMPTY)
        {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner();
            isRedTurn = !isRedTurn;
            return true;
        }
    return false;
}

bool Field::isWon(bool red) const
{
    return winner == (red ? RED : YELLOW);
}

bool Field::isOver() const
{
    if (winner != EMPTY)
        return true;

    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            if (cells[i][j] == EMPTY)
                return false;
    return true;
}

Cell Field::getCell(int i, int j) const
{
    return cells[i][j];
}

bool Field::isRedTurnNow() const
{
    return isRedTurn;
}

void Field::checkWinner()
{
    // вправо , вниз, диагонали
    const int DIR_NUMBER = 4;
    const int di[] = {1, 0, 1, 1};
    const int dj[] = {0, 1, -1, 1};
    const int WIN_LENGTH = 4;

    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            Cell start = cells[i][j];
            if (start == EMPTY)
                continue;

            for (int dir = 0; dir < DIR_NUMBER; dir++)
            {
                int length = 0, iline = i, jline = j;
                while (++length < WIN_LENGTH)
                {
                    iline += di[dir];
                    jline += dj[dir];
                    if (iline < 0 || iline >= FIELD_WIDTH || jline < 0 || jline >= FIELD_HEIGHT)
                        break;
                    if (cells[iline][jline] != start)
                        break;
                }
                if (length == WIN_LENGTH)
                {
                    winner = start;
                    return;
                }
            }
        }
}

void Field::print() const
{
    using std::cout;

    cout << "\n";
   
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--)
    {
        cout << "|";
        for (int i = 0; i < FIELD_WIDTH; i++)
        {
            char ch = '.';
            if (cells[i][j] == RED)
                ch = 'R';
            else if (cells[i][j] == YELLOW)
                ch = 'Y';
            cout << ch << "|";
        }
        cout << "\n";
    }
    cout << " ";
    for (int col = 1; col <= FIELD_WIDTH; col++)
        cout << col << " ";
    cout << "\n\n";
}

void Field::printResult() const
{
    using std::cout;

    print();
    if (winner == RED)
        cout << "Победил красный игрок.\n";
    else if (winner == YELLOW)
        cout << "Победил желтый игрок.\n";
    else
        cout << "Ничья.\n";
}

