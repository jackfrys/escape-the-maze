all: maze

maze: main.o Maze.o
	g++ -std=c++11 -Wall -lSDL2 -o $@ $^

main.o: main.cpp Maze.h
	g++ -c -std=c++11 -Wall -lSDL2 -O2 -o $@ $<

Maze.o: Maze.cpp Maze.h
	g++ -c -std=c++11 -Wall -lSDL2 -O2 -o $@ $<

clean:
	rm -f maze main.o Maze.o
