#include<iostream>
#include"../Cell/cell.h"
#include<vector>
#include <string>
#include <time.h>

using std::vector;
using std::cout;
using std::endl;
using std::ios;



vector<Cell> initMaze(int row, int column);
void drawMaze(vector<std::string> maze, int row, int column);
vector<std::string> createMaze(vector<Cell> &maze, int row, int column);
vector<Cell> checkVisitedNeighbors(vector<Cell> maze, int column, int pos);
vector<std::string> insertWalls(vector<Cell> &maze, int row, int column);
vector<std::string> MazeGenerator(int &row, int &column);

 