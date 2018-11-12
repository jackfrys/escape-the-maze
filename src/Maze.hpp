#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"
#include "Cell.hpp"
#include "Util.hpp"
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
  void updateKeys();
  void updateGuards();
  bool isRunning;
  int size;
  int remainingKeys;
  unsigned long int time;
  Posn player;
  Cell** cells;
  Key *keys;
  Guard *guards;
  SDL_Window *maze;
  SDL_Renderer *renderer;
};

#endif