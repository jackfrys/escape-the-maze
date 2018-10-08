#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include <iostream>

class Maze {

public:
  Maze();
  ~Maze();

  void init(int width, int height);
  
  // TODO have this actually do something
  void handleInput();
  // TODO have this actually do something
  void update();

  void render();
  void clean();
  bool running();

private:
  bool isRunning;
  SDL_Window *maze;
  SDL_Renderer *renderer;

};

#endif