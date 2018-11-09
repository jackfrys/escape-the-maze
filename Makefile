all: main
	
main: main.o Maze.o Cell.o
	g++ -std=c++11 -Wall -o $@ $^ -lSDL2

main.o: src/main.cpp src/Maze.hpp src/Util.hpp
	g++ -c -std=c++11 -Wall -O2 -o $@ $<

Maze.o: src/Maze.cpp src/Maze.hpp src/Cell.hpp
	g++ -c -std=c++11 -Wall -O2 -o $@ $<

Cell.o: src/Cell.cpp src/Cell.hpp src/Util.hpp
	g++ -c -std=c++11 -Wall -O2 -o $@ $<

clean:
	rm -f main main.o Maze.o Cell.o
