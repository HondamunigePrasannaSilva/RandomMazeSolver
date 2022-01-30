#include<iostream>
#include"mazeGenerator.h"
#include <chrono>
#include <omp.h>
#include "mazeSolver.h"


#define ROW    20
#define COLOMN 20

#define START_X  0
#define START_Y  0
#define FINISH_X ROW-1
#define FINISH_y COLOMN-1



using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;



int main()
{
    int row    = ROW;
    int column = COLOMN;

    cellCoordinate start_position, finish_position;
    
    vector<std::string> maze = MazeGenerator(row, column);
    vector<int> path;
    
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

    #pragma omp parallel shared(maze, start_position, finish_position, column, row, found) private(path) num_threads(8)
    { 
        
        bool resolved = false;
        int id = omp_get_thread_num();

        resolved = MazeSolver(maze, path, start_position, finish_position, column, row, found);

        #pragma omp critical
        {
            if(resolved && !found)
            {       
                found = true;
                cout << "Thread "<<id<<" found the path"<<endl;
                PathDisplay(maze, path);
                drawMaze(maze, row, column);       
            }
        }    
    }
   
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);

    cout << "Tempo parallel: "<<duration.count()<<"ms"<<endl;  
    
}
