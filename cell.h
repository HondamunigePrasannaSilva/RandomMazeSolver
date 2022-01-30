#include<iostream>


/*
    creazione dell'oggetto Cella per la creazione
    del labirinto tramite l'algoritmo depth-first search

*/


class Cell
{
    int coordinate_row;
    int coordinate_column;
    bool visited;
    bool wallRight, wallLeft, wallUp, wallDown;

public:
    Cell(int, int);
    int getRow()   { return coordinate_row; };
    int getColumn(){ return coordinate_column; };
    bool getVisited(){ return visited; };
    bool getWallRight();
    bool getWallLeft();
    bool getWallUp() ;
    bool getWallDown();
    void setwallRight(bool x);
    void setwallLeft(bool x);
    void setwallDown(bool x);
    void setwallUp(bool x);    
    void setVisited(bool x);

};

Cell::Cell(int row, int column)
{
    coordinate_row = row;
    coordinate_column = column;
    visited = false;
    wallRight = wallUp = wallLeft = wallDown = false;
}

bool Cell::getWallRight() { return wallRight; }
bool Cell::getWallLeft() { return wallLeft; }
bool Cell::getWallUp() { return wallUp; }
bool Cell::getWallDown() { return wallDown; }
void Cell::setwallDown(bool x) { wallDown = x;}
void Cell::setwallUp(bool x) { wallUp = x;}
void Cell::setwallRight(bool x) { wallRight = x;}
void Cell::setwallLeft(bool x) { wallLeft = x;}
void Cell::setVisited(bool x){ visited = x; }
