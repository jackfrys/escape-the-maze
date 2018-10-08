#include "Maze.h"

using namespace std;

Maze::Maze() {
}

Maze::~Maze() {

}

void Maze::init(int width, int height) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    
    maze = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    
    if (!maze) {
      cerr << "Window failed to create" << endl;
    }

    renderer = SDL_CreateRenderer(maze, -1, 0);

    if (!renderer) {
      cerr << "Failed to init renderer" << endl;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    isRunning = true;
  } else {
    isRunning = false;
  }
}

void Maze::handleInput() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    default:
      break;
  }
}

void Maze::update() {}

void Maze::render() {
  SDL_RenderClear(renderer);
  // TODO add stuff to render here
  SDL_RenderPresent(renderer);
}

void Maze::clean() {
  SDL_DestroyWindow(maze);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}