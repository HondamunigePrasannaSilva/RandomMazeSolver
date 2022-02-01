


all: clean mainTest mainParallel mainSequential

mainTest:
	g++ -fopenmp test.cpp -o mainTest

mainParallel:
	g++ -fopenmp RandomMazeSolver.cpp -o mainParallel

mainSequential:
	g++ RandomMazeSolverSeq.cpp -o mainSequential

clean: 
	-rm mainSequential mainParallel mainTest