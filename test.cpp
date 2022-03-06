#include<iostream>
#include"MazeGenerator/mazeGenerator.h"
#include <chrono>
#include <omp.h>
#include "mazeSolver.h"



#define ROW    50
#define COLUMN 50


#define TEST 50

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

void foo();

int main()
{
   

    int s[2] = {45, 50};
    int t[4] = {4,8, 16,32};

    for(int q = 0; q < 2 ; q++)
    {
        int row    = s[q];
        int column = s[q];
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
        
        cout << "Labritino: " << s[q] << "x"<< s[q] << endl;
        
        //drawMaze(maze, row, column); 
        

        for (int h = 0; h < 4; h++)
        {
                /* code */
            int th = t[h];
            cout << "TEST CON "<< t[h] << " THREAD" << endl;
            for(int i = 0 ; i < TEST; i++)
            {
                auto start = high_resolution_clock::now();
                bool found = false;

                #pragma omp parallel shared(maze, start_position, finish_position, column, row, found) num_threads(th)
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
                auto duration = duration_cast<std::chrono::microseconds>(stop - start);

                //cout << "Tempo parallel: "<<duration.count()<<"ms"<<endl;  
                tempi.push_back(duration.count());
            }

            sum = 0;
            for (int i = 0; i < TEST; i++)
                sum += tempi[i];
                
            cout << "[Parallel] Tempo medio del test  e' : "<< sum/TEST <<" ms"<< endl;
            
            tempi.clear();
        }
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
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            //cout << "Tempo: "<<duration.count()<<"ms"<<endl;
            tempi.push_back(duration.count());
        }
    
        sum = 0;
        for (int i = 0; i < TEST; i++)
            sum += tempi[i];
            
        tempi.clear();
        cout << "[Sequenziale] Tempo medio  del test e' : "<<sum/TEST << " ms"<<endl;
    
        
    } 
}
