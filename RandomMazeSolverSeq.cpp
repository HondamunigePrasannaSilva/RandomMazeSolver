#include<iostream>
#include"mazeGenerator.h"
#include <chrono>
#include <omp.h>
#include "mazeSolver.h"


#define ROW    10
#define COLOMN 10

#define START_X  0
#define START_Y  0
#define FINISH_X ROW-1
#define FINISH_y COLOMN-1

#define MAX_ITERATION 10


using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;



int main()
{
    int row    = ROW;
    int column = COLOMN;
    
    bool find = false;

    vector<int> path;
    cellCoordinate start_position, finish_position;
    
    vector<std::string> maze = MazeGenerator(row, column);
    
    

    start_position.x = 1;
    start_position.y = 2;
    finish_position.x = column-2;
    finish_position.y = column-2;

    cout <<"Start  position: ["<<start_position.x << ";"<<start_position.y<<"]"<<endl;
    cout <<"Finish position: ["<< finish_position.x << ";"<<finish_position.y<<"]"<<endl;
      
    maze[start_position.x*column+start_position.y] = "->";
    maze[finish_position.x*column+finish_position.y] = "@";
   

  
    drawMaze(maze, row, column);

    
    srand (time(NULL));

    auto start = high_resolution_clock::now();

    bool found = false;
    find = MazeSolver(maze, path, start_position, finish_position, column, row, found);

    if(find)
    {
        cout << "Trovato"<<endl;
        PathDisplay(maze, path);
        drawMaze(maze, row, column);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Tempo: "<<duration.count()<<"ms"<<endl;  
  
}

