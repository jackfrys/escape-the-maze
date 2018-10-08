#ifndef CELL_H
#define CELL_H

#include "SDL2/SDL.h"
#include <iostream>

class Cell {

public:
  Cell();
  ~Cell();

private:
  bool up;
  bool down;
  bool left;
  bool right;
};

#endif