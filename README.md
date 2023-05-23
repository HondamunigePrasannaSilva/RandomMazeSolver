# Random Maze Solver - Parallel Programming - 

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Maze Generator](#maze-generating)
* [Maze solver](#maze-solver)
* [Test](#Test)

## General info
> the dumbest way to solve a maze? simulate a gas of thousands of particles diffusing from the start point, until one particle reaches the exit. 

link: https://twitter.com/matthen2/status/1440443280827699206

This project aims to parallelize a maze solver that do not use any maze-solving algorithm but instead search the path randomly.

## Maze Generator
The maze is generated using Randomized depth-first search algorithm, more specifically the iterative implementation. 
```
- Choose the initial cell, mark it as visited and push it to the stack
- While the stack is not empty
	- Pop a cell from the stack and make it a current cell
	- If the current cell has any neighbours which have not been visited
        	- Push the current cell to the stack
        	- Choose one of the unvisited neighbours
        	- Remove the wall between the current cell and the chosen cell
        	- Mark the chosen cell as visited and push it to the stack
```
link:https://en.wikipedia.org/wiki/Maze_generation_algorithm

file: mazeGenerator.h

## Maze Solver
The maze solver is a random labyrinth solver algorithm, the meaning of random in this case means that at each point in the maze the algorithm will randomly choose one of the four directions[up, down, left, right]. 
If the algorithm chooses a direction that is a wall, it will bounce and remain in the same spot and repeat the random choice of the direction.
This algorithm will repeat until reaching the target spot of the maze.
```
1. while(particle find target spot)
2. choose direction
3. if(direction is a wall) go to 2
4. else update path
5. Go to 2
```
The sequential solver has only one 'particle' that search the path randomly, on the other hand, the parallel solver has multiple particles that randomly search the path. Once a particle finds the target spot, the algorithm stops.

Sequential solver: RandomMazedSolverSeq.cpp
Parallel solver:   RandomMazedSolver.cpp

## Test
Due to the maze being generated randomly, is it not possible to test the two solvers with the same maze independently. The 'test. cpp' is a test code in which the solvers are used to solve the same maze multiple times, in this way we obtain more accurate statistics.
file: test.cpp

## Technologies
* OpenMP 
