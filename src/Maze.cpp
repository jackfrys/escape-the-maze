#include "Maze.h"
#include "Cell.h"

// Cell size constraint
const int CELL_SIZE = 25;

using namespace std;

Maze::Maze() {
  // Dynamically generate the 2D array
  // Eventually this constructor will take a difficulty and change the size
  size = 10;
  playerX = 0;
  playerY = 0;
  cells = new Cell*[size];
  for(int i = 0; i < size; ++i) {
    cells[i] = new Cell[size];
  }
}

Maze::~Maze() {
  // Free up space
  for(int i = 0; i < size; i++) {
    delete[] cells[i];
  }
  delete cells;
}

void Maze::init() {
  // Initialize the SDL2 stuff
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

    int width = size * CELL_SIZE;
    int height = size * CELL_SIZE;

    // initialize the SDL2 Window
    maze = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    // Initialize the SDL2 Renderer
    renderer = SDL_CreateRenderer(maze, -1, 0);
    
    isRunning = true;
  } else {
    isRunning = false;
  }
}

void Maze::handleInput() {
  // This SDL2 event keeps track of inputs
  SDL_Event event;
  SDL_PollEvent(&event);

  // This switch statement will actually figure out what to do with the event
  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
      {
          case SDLK_LEFT:
            if (playerX > 0) playerX--;
            break;
          case SDLK_RIGHT:
            if (playerX < size - 1) playerX++;
            break;
          case SDLK_UP:
            if (playerY > 0) playerY--;
            break;
          case SDLK_DOWN:
            if (playerY < size - 1) playerY++;
            break;
      }
      break;
    default:
      break;
  }
}

// TODO no clue yet
void Maze::update() {}

void Maze::render() {
  // Set draw color to black
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  // This function colors in the whole window
  SDL_RenderClear(renderer);
  
  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      if (playerX == x && playerY == y) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        int xPos = x * CELL_SIZE;
        int yPos = y * CELL_SIZE + 1;
        SDL_Rect player = { xPos, yPos, CELL_SIZE, CELL_SIZE - 1 };
        SDL_RenderFillRect(renderer, &player);
      }
      cells[x][y].renderCell(renderer, x, y);
    }
  }

  SDL_RenderPresent(renderer);
}

void Maze::clean() {
  SDL_DestroyWindow(maze);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

bool Maze::running() {
  return isRunning;
}