


all: clean mainTest mainParallel mainSequential

mainTest:
	g++ -fopenmp test.cpp Cell/cell.cpp  MazeGenerator/mazeGenerator.cpp  -o mainTest

mainParallel:
	g++ -fopenmp RandomMazeSolver.cpp Cell/cell.cpp  MazeGenerator/mazeGenerator.cpp -o mainParallel

mainSequential:
	g++ RandomMazeSolverSeq.cpp Cell/cell.cpp MazeGenerator/mazeGenerator.cpp -o mainSequential

clean: 
	-rm mainSequential mainParallel mainTest