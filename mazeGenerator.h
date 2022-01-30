#include<iostream>
#include"cell.h"
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


vector<std::string> MazeGenerator(int &row, int &column)
{
    
    srand (time(NULL));
    vector<Cell> maze = initMaze(row,column);
  
    vector<std::string> finalMaze = createMaze(maze, row, column);
     
    row = 2*row+1;
    column = 2*column+1;
    return finalMaze;
}
vector<Cell> initMaze(int row, int column)
{
    vector<Cell> maze ;
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            Cell *cella = new Cell(i,j);
            maze.push_back(*cella);            
        }    
    }
    return maze;
}
vector<std::string> createMaze(vector<Cell> &maze, int row, int column)
{
    //scegliere la cella iniziare da cui inziare, cella(0,0) 
    int init_position = rand() % maze.size();

    int position, random_neighbor;
    // creazione dello stack per inserire le celle vistate
    vector<Cell> visited_cell;
    // vettore per inserire i vicini non visitati
    vector<Cell> neighbors;
    // inserimento della cella selezionata al passo iniziale 
    maze[init_position].setVisited(true);
    visited_cell.push_back(maze[init_position]);
    while(visited_cell.empty() == false)
    {
        // seleziono un elemento dello stack visited
        Cell current_cell = visited_cell.back();
        visited_cell.pop_back();

        // seleziono i vicini della cella appena selezionata
        position = current_cell.getRow()*column+current_cell.getColumn();
        neighbors.clear();
        neighbors  = checkVisitedNeighbors(maze, column, position);
    
        if(neighbors.empty() == false)
        {
         
            // ri inserisco la cella corrente
            visited_cell.push_back(current_cell);
           
            // seleziono a caso un vicino non visitato 
            random_neighbor = rand() % neighbors.size();
            Cell selected_neighbor = neighbors[random_neighbor];
 
            // segno come visitato la cella
            maze[selected_neighbor.getRow()*column+selected_neighbor.getColumn()].setVisited(true);

            // rimuovere il muro tra la cella currente_cell e selected_neighbor

            int s_position = selected_neighbor.getRow()*column+selected_neighbor.getColumn();

            if(current_cell.getColumn() == selected_neighbor.getColumn())
            {
              
                if(current_cell.getRow()>selected_neighbor.getRow())
                {
                    maze[s_position].setwallDown(true);
                    maze[position].setwallUp(true);
                }
                else
                {
                     maze[s_position].setwallUp(true);
                    maze[position].setwallDown(true);
                }
            }
            if(current_cell.getRow() == selected_neighbor.getRow())
            {
                if(current_cell.getColumn()>selected_neighbor.getColumn())
                {
                    maze[s_position].setwallRight(true);
                    maze[position].setwallLeft(true);
                }
                else
                {
                    maze[s_position].setwallLeft(true);
                    maze[position].setwallRight(true);
                }
            }
            visited_cell.push_back(selected_neighbor);
        }
    }
    // creazione di una griglia con le mura
    vector<std::string> finalMaze = insertWalls(maze, row, column);
     
    return finalMaze;

}
vector<std::string> insertWalls(vector<Cell> &maze, int row, int column)
{
    int height = 2*row + 1;
    int width = 2*column + 1;
    std::string s = " ";
    vector<std::string> finalMaze(height*width, "#");
    int index = 0;
    for(int i = 1; i < height-1; i = i + 2)
    {
        for (int j = 1; j < width - 1 ; j = j +2)
        {
            // controllo con cella a destra
           
            if(maze[index].getWallRight())
            { 
                finalMaze[i*width+j] = s;
                finalMaze[i*width+j + 1] = s;
                finalMaze[i*width+j + 2] = s; 
            }
            //controllo con la cella sinistra
            if(maze[index].getWallLeft())
            { 
                finalMaze[i*width+j] = s;
                finalMaze[i*width+j - 1] = s;
                finalMaze[i*width+j - 2] = s; 
            }
            //controllo con la cella su
            if(maze[index].getWallUp())
            { 
                finalMaze[i*width+j] = s;
                finalMaze[i*width+j - width] = s;
                finalMaze[i*width+j - 2*width] = s; 
            }
             //controllo con la cella giu
            if(maze[index].getWallDown())
            { 
                finalMaze[i*width+j] = s;
                finalMaze[i*width+j + width] = s;
                finalMaze[i*width+j + 2*width] = s; 
            }
            
            
            index++;
        }
        
    }
    return finalMaze;
}
void drawMaze(vector<std::string> maze, int row, int column)
{
     
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout.setf(ios::left);
            cout.width(2);
            cout << maze[(i)*column + j];
            cout.unsetf(ios::left);
        }
        cout << endl;
    }
}
vector<Cell> checkVisitedNeighbors(vector<Cell> maze, int column, int pos)
{
    vector<Cell> notvisitedNeighbors;
    //controllo il vicino a sx
    if((pos)%column != 0 && pos-1 >= 0)
    {
        if(maze[pos-1].getVisited() == false)
            notvisitedNeighbors.push_back(maze[pos-1]);
    }
    // controllo il vicino a dx
    if((pos+1)%column != 0 && pos+1 < maze.size() )
    {   
        if(maze[pos+1].getVisited() == false)
            notvisitedNeighbors.push_back(maze[pos+1]);
    }
    //controllo vicino down
    if(pos+column < maze.size())
    {
        if(maze[pos+column].getVisited() == false)
            notvisitedNeighbors.push_back(maze[pos+column]);
    }
    //controllo vicino su
    if(pos-column > 0)
    {
        if(maze[pos-column].getVisited() == false)
            notvisitedNeighbors.push_back(maze[pos-column]);
    }
    return notvisitedNeighbors;
}
