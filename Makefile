CXXTEST_HOME ?= cxxtest-4.4
CXXTEST_GEN = $(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE = $(CXXTEST_HOME)

all: main
	
main: main.o Maze.o Cell.o
	g++ -std=c++11 -Wall -o $@ $^ -lSDL2

runner: Cell.o Cell.cxxtest.o Maze.o Maze.cxxtest.o runner.o
	g++ -std=c++11 $^ -Wall -O2 -I$(CXXTEST_INCLUDE) -o $@ -lSDL2

test: runner
	./runner

main.o: src/main.cpp src/Maze.hpp src/Util.hpp
	g++ -c -std=c++11 -Wall -O2 -I$(CXXTEST_INCLUDE) -o $@ $<

Maze.o: src/Maze.cpp src/Maze.hpp src/Cell.hpp
	g++ -c -std=c++11 -Wall -O2 -I$(CXXTEST_INCLUDE) -o $@ $<

Cell.o: src/Cell.cpp src/Cell.hpp src/Util.hpp
	g++ -c -std=c++11 -Wall -O2 -I$(CXXTEST_INCLUDE) -o $@ $<

%.cxxtest.o: %.cxxtest.cpp src/*.cxxtest.hpp
	g++ -c -std=c++11 -Wall -O2 $< -I$(CXXTEST_INCLUDE) -o $@

Cell.cxxtest.cpp: src/Cell.cxxtest.hpp
	$(CXXTEST_GEN) --part --error-printer $< -o $@

Maze.cxxtest.cpp: src/Maze.cxxtest.hpp
	$(CXXTEST_GEN) --part --error-printer $< -o $@

runner.cpp:
	$(CXXTEST_GEN) --root --error-printer -o $@

clean:
	rm -f main *.o runner runner.cpp *.cxxtest.cpp
