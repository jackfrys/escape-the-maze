#ifndef CELL_H
#define CELL_H

#include "SDL2/SDL.h"
#include <iostream>

class Cell {
public:
  Cell();
  ~Cell();
  void renderCell(SDL_Renderer *renderer, int x, int y);
  bool canMove(int direction);
  void breakWall(int direction);
  void breakOppWall(int direction);
  bool notVisited();
  void setVisited();

private:
  int up;
  int down;
  int left;
  int right;
  bool visited;
};

#endif