#pragma once

#include <iosfwd>

enum Cell
{
    EMPTY,
    RED,
    YELLOW
};

constexpr int FIELD_WIDTH = 7;
constexpr int FIELD_HEIGHT = 6;

class Field
{
public:
  
    explicit Field(bool isRedFirst);
    void clear(bool isRedFirst);

   

   
    bool isWon(bool red) const;

    
    bool isOver() const;

   
    Cell getCell(int i, int j) const;

   
    bool isRedTurnNow() const;

   
    void print() const;
    bool makeTurn(int column);
    void printResult() const;

private:
 
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];

    bool isRedTurn;

    Cell winner;

    
    void checkWinner();
};

