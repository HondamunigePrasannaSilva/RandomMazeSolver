
#include<iostream>
#include<vector>
#include <string>

using std::vector;

struct cellCoordinate
{
    int x;
    int y;
};


bool MazeSolver(vector<std::string> _maze, vector<int> &path, cellCoordinate sPos, cellCoordinate fPos, int colomn, int row, bool &found);
void PathDisplay(vector<std::string> &_maze, vector<int> _path);

vector<int> NeighborsWithWalls(vector<std::string> _maze, int pos, int colomn, vector<int> _path);


bool MazeSolver(vector<std::string> _maze, vector<int> &path, cellCoordinate sPos, cellCoordinate fPos, int colomn, int row, bool &found)
{
    int current_cell = sPos.x*colomn+sPos.y;
    
    path.push_back(current_cell);

    vector<int> currentNeighbor = NeighborsWithWalls(_maze, sPos.x*colomn+sPos.y, colomn, path);
  
 
    int random_pos;

    while(current_cell != fPos.x*colomn+fPos.y)
    {
        // se un altro thread ha trovato il path, non c'è bisogno di continuare
        if(found == true) break;

        random_pos = rand()%currentNeighbor.size(); 

        current_cell = currentNeighbor[random_pos];
        if(_maze[current_cell].compare("#") != 0)
        { 
            path.push_back(current_cell);
       
            currentNeighbor.clear();
            currentNeighbor = NeighborsWithWalls(_maze, current_cell, colomn, path);
        }
    }


    if(current_cell == fPos.x*colomn+fPos.y)
        return true;
    
    if(found == true) return false;

    return false;

}
void PathDisplay(vector<std::string> &_maze, vector<int> _path)
{
    for (int i = 0; i < _path.size(); i++)
    {
        _maze[_path[i]] = "-";
    }
}
vector<int> NeighborsWithWalls(vector<std::string> _maze, int pos, int colomn, vector<int> _path)
{
    // ottengo un vector di interi che rapprestano 
    // le posizioni dei vicini della cella in posizione 'pos'
    vector<int> neighbors;
        
    //controllo il vicino a sx
    if(pos-1 >= 0) { neighbors.push_back(pos-1); }
    // controllo il vicino a dx
    if( pos+1 < _maze.size()) { neighbors.push_back(pos+1); }
    //controllo vicino down
    if(pos+colomn < _maze.size()) { neighbors.push_back(pos+colomn); }
    //controllo vicino su
    if(pos-colomn > 0) { neighbors.push_back(pos-colomn); }

    return neighbors;
}