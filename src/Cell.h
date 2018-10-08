#ifndef CELL_H
#define CELL_H

#include "SDL2/SDL.h"
#include <iostream>

class Cell {

public:
  Cell();
  ~Cell();
  void renderCell(SDL_Renderer *renderer, int x, int y);

private:
  bool up;
  bool down;
  bool left;
  bool right;
};

#endif