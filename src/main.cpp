#include <stdio.h>
#include <SDL2/SDL.h>
#include "Maze.h"

using namespace std;

int main( int argc, char* args[] ) {
	Maze maze;
	maze.init();

	while (maze.running()) {
		maze.handleInput();
		maze.update();
		maze.render();
	} 

	cout << "YOU WIN!" << endl;
	maze.clean();

	return 0;
}
