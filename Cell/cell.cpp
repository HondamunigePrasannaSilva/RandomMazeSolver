#include"cell.h"


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
