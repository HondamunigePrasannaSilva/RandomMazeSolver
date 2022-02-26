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

