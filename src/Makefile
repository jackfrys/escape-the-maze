all: maze
	
maze: main.o Maze.o Cell.o
	g++ -std=c++11 -Wall -o $@ $^ -lSDL2

main.o: main.cpp Maze.h
	g++ -c -std=c++11 -Wall -O2 -o $@ $< -lSDL2

Maze.o: Maze.cpp Maze.h Cell.h
	g++ -c -std=c++11 -Wall -O2 -o $@ $< -lSDL2

Cell.o: Cell.cpp Cell.h
	g++ -c -std=c++11 -Wall -O2 -o $@ $< -lSDL2

clean:
	rm -f maze main.o Maze.o Cell.o
