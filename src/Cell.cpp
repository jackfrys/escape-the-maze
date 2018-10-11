#include "Cell.h"

// Cell size constraint
// TODO move to util file
const int CELL_SIZE = 25;

Cell::Cell() {
  up = 0;
  down = 0;
  left = 0;
  right = 0;
  visited = false;
}

Cell::~Cell() {

}

/*
 * direction can be one of:
 *  0 = up
 *  1 = down
 *  2 = left
 *  3 = right
 */
bool Cell::canMove(int direction) {
  switch(direction) {
    case 0:
      return up;
    case 1:
      return down;
    case 2:
      return left;
    case 3:
      return right;
    default:
      return false;
  }
}

void Cell::renderCell(SDL_Renderer *renderer, int x, int y) {
  // Change color to white
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  if (!up) {
    int xPos1 = x * CELL_SIZE;
    int xPos2 = xPos1 + CELL_SIZE;
    int yPos1 = y * CELL_SIZE;
    int yPos2 = y * CELL_SIZE;

    SDL_RenderDrawLine(renderer, xPos1, yPos1, xPos2, yPos2);
  }

  if (!down) {
    int xPos1 = x * CELL_SIZE;
    int xPos2 = xPos1 + CELL_SIZE;
    int yPos1 = (y + 1) * CELL_SIZE;
    int yPos2 = (y + 1) * CELL_SIZE;

    SDL_RenderDrawLine(renderer, xPos1, yPos1, xPos2, yPos2);
  }

  if (!left) {
    int xPos1 = x * CELL_SIZE;
    int xPos2 = x * CELL_SIZE;
    int yPos1 = y * CELL_SIZE;
    int yPos2 = yPos1 + CELL_SIZE;

    SDL_RenderDrawLine(renderer, xPos1, yPos1, xPos2, yPos2);
  }

  if (!right) {
    int xPos1 = (x + 1) * CELL_SIZE;
    int xPos2 = (x + 1) * CELL_SIZE;
    int yPos1 = y * CELL_SIZE;
    int yPos2 = yPos1 + CELL_SIZE;

    SDL_RenderDrawLine(renderer, xPos1, yPos1, xPos2, yPos2);
  }
}

void Cell::breakWall(int direction) {
  switch (direction) {
    case 0:
      up = 1;
      break;
    case 1:
      down = 1;
      break;
    case 2:
      left = 1;
      break;
    case 3:
      right = 1;
      break;
  }
}

void Cell::breakOppWall(int direction) {
  switch (direction) {
    case 0:
      down = 1;
      break;
    case 1:
      up = 1;
      break;
    case 2:
      right = 1;
      break;
    case 3:
      left = 1;
      break;
  }
}

bool Cell::notVisited() {
  return !visited;
}

void Cell::setVisited() {
  visited = true;
}
