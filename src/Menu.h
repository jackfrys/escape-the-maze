#ifndef MENU_H
#define MENU_H

#include "SDL2/SDL.h"
#include "Cell.h"
#include "Util.h"
#include <iostream>

class Menu {

public:
  Menu();
  // TODO have this actually do something
  void handleInput();

  void init();
  void render();
  void clean();
  bool running();
  int getChoice();

private:
  void drawRect(bool filled, SDL_Rect rect);
  bool isRunning;
  int choice;
  SDL_Window *maze;
  SDL_Renderer *renderer;
};

#endif