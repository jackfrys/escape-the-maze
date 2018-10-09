#include "Cell.h"

// Cell size constraint
// TODO move to util file
const int CELL_SIZE = 50;

Cell::Cell() {
  up = false;
  down = false;
  left = true;
  right = true;
}

Cell::~Cell() {

}

void Cell::renderCell(SDL_Renderer *renderer, int x, int y) {
  // Change color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  
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