#include <stdio.h>
#include <SDL2/SDL.h>
#include "Maze.h"
#include "Menu.h"

using namespace std;

int main( int argc, char* args[] ) {
	Menu menu;
	menu.init();
	while (menu.running()) {
		menu.handleInput();
		menu.render();
	}
	menu.clean();

	Maze maze(menu.getChoice() + 1);
	maze.init();

	while (maze.running()) {
		maze.handleInput();
		maze.update();
		maze.render();
	} 

	maze.clean();

	if (!maze.won()) {
		return 0;
	}

	Maze second(menu.getChoice() + 1);
	second.init();
	second.changeColorScheme();
	while (second.running()) {
		second.handleInput();
		second.update();
		second.render();
	}
	second.clean();

	return 0;
}
