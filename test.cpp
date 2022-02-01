#include<iostream>
#include"mazeGenerator.h"
#include <chrono>
#include <omp.h>
#include "mazeSolver.h"


#define ROW    25
#define COLUMN 25


#define TEST 10

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

void foo();

int main()
{
    int row    = ROW;
    int column = COLUMN;

    vector<int> tempi;
    int sum = 0;
    cellCoordinate start_position, finish_position;
     
    start_position.x = 1;
    start_position.y = 2;
    finish_position.x = row-2;
    finish_position.y = column-2;

    srand (time(NULL));
    vector<std::string> maze;
    maze = MazeGenerator(row, column);
    
    cout << "Labritino: " << ROW << "x"<< COLUMN << endl;
    
    drawMaze(maze, row, column); 
    cout << "Risultati dei test ripetuti per: "<< TEST << endl;


    for(int i = 0 ; i < TEST; i++)
    {
        auto start = high_resolution_clock::now();
        bool found = false;

        #pragma omp parallel shared(maze, start_position, finish_position, column, row, found) num_threads(8)
        { 
            vector<int> path;
            bool resolved = false;
            int id = omp_get_thread_num();
            resolved = MazeSolver(maze, path, start_position, finish_position, column, row, found);
            #pragma omp critical
            {
                if(resolved && !found) 
                    found = true;
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);

        cout << "Tempo parallel: "<<duration.count()<<"ms"<<endl;  
        tempi.push_back(duration.count());
    }

    sum = 0;
    for (int i = 0; i < TEST; i++)
        sum += tempi[i];
        
    cout << "[Parallel] Tempo medio del test  e' : "<< sum/TEST <<" ms"<< endl;
    //cout << sum/TEST << ";";
    tempi.clear();

    // parte sequenziale

    vector<int> path;
    for(int i = 0 ; i < TEST; i++)
    {
        path.clear();
        bool find = false;
        bool f = false;

        auto start = high_resolution_clock::now();       

        find = MazeSolver(maze, path, start_position, finish_position, column, row, f);
            
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
        cout << "Tempo: "<<duration.count()<<"ms"<<endl;
        tempi.push_back(duration.count());
    }
  
    sum = 0;
    for (int i = 0; i < TEST; i++)
        sum += tempi[i];
        
    tempi.clear();
    cout << "[Sequenziale] Tempo medio  del test e' : "<<sum/TEST << " ms"<<endl;
    //cout << sum/TEST <<endl;  
}
