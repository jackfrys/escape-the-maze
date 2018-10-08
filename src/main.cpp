/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
//#include <SDL.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "Maze.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] ) {
	
	Maze maze;
	maze.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	while (maze.running()) {

		maze.handleInput();
		maze.update();
		maze.render();
	
	} 

	maze.clean();

	return 0;
}
