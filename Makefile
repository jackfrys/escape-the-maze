all: maze
	
maze: main.o Maze.o Cell.o
	g++ -std=c++11 -Wall -o $@ $^ -lSDL2

main.o: src/main.cpp src/Maze.h
	g++ -c -std=c++11 -Wall -O2 -o $@ $<

Maze.o: src/Maze.cpp src/Maze.h src/Cell.h
	g++ -c -std=c++11 -Wall -O2 -o $@ $<

Cell.o: src/Cell.cpp src/Cell.h
	g++ -c -std=c++11 -Wall -O2 -o $@ $<

clean:
	rm -f maze main.o Maze.o Cell.o
