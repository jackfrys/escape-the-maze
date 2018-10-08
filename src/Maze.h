#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"
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

private:
  bool isRunning;
  int size;
  char** cells;
  SDL_Window *maze;
  SDL_Renderer *renderer;
};

#endif