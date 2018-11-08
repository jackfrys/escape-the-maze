#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"
#include "Cell.h"
#include "Util.h"
#include <iostream>

class Maze {

public:
  Maze();
  Maze(int newSize);
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
  void privateInit(int newSize);
  bool isRunning;
  int size;
  Posn player;
  Cell** cells;
  SDL_Window *maze;
  SDL_Renderer *renderer;
};

#endif