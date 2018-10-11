#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"
#include "Cell.h"
#include <iostream>

class Maze {

public:
  Maze();
  ~Maze();

  void init();
  
  // TODO have this actually do something
  void handleInput();
  // TODO have this actually do something
  void update();

  void render();
  void clean();
  bool running();
  void generateMaze(int sx, int sy);

private:
  bool isRunning;
  int size;
  int playerX;
  int playerY;
  Cell** cells;
  SDL_Window *maze;
  SDL_Renderer *renderer;
};

#endif