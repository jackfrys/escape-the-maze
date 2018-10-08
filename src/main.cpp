#include <stdio.h>
#include <SDL2/SDL.h>
#include "Maze.h"

int main( int argc, char* args[] ) {
	
	Maze maze;
	maze.init();

	while (maze.running()) {

		maze.handleInput();
		maze.update();
		maze.render();
	
	} 

	maze.clean();

	return 0;
}
