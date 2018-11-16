#include <stdio.h>
#include <SDL2/SDL.h>
#include "Maze.h"

using namespace std;

int main( int argc, char* args[] ) {
	int difficulty;

	cout << "1. Easy" << endl;
	cout << "2. Medium" << endl;
	cout << "3. Hard" << endl;
	cout << "Which difficulty would you like to play at? " << endl;
	cin >> difficulty;

	Maze maze(difficulty);
	maze.init();

	while (maze.running()) {
		maze.handleInput();
		maze.update();
		maze.render();
	} 

	maze.clean();

	return 0;
}
