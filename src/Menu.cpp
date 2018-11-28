#include "Menu.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <cstdlib>
#include <unistd.h>

using namespace std;

Menu::Menu() {
    choice = 0;
    isRunning = true;
}

void Menu::init() {
  // Initialize the SDL2 stuff
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

    int width = 20 * CELL_SIZE;
    int height = 20 * CELL_SIZE;

    // initialize the SDL2 Window
    maze = SDL_CreateWindow("MAZE ESCAPE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    // Initialize the SDL2 Renderer
    renderer = SDL_CreateRenderer(maze, -1, 0);
    isRunning = true;
  } else {
    isRunning = false;
  }
}

void Menu::handleInput() {
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
        case SDLK_UP:
          choice--;
          if (choice == -1) {
            choice = 2;
          }
          break;
        case SDLK_DOWN:
          choice++;
          choice %= 3;
          break;
        case SDLK_RETURN:
          isRunning = false;
          break;
      }
      break;
    default:
      break;
  }
}

void Menu::render() {
  // Set draw color to black
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  // This function colors in the whole window
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_Rect top = {180, 50, 30, 30};
  drawRect(choice == 0, top);

  SDL_Rect middle1 = {165, 150, 30, 30};
  drawRect(choice == 1, middle1);

  SDL_Rect middle2 = {195, 150, 30, 30};
  drawRect(choice == 1, middle2);

  SDL_Rect rect = {150, 250, 30, 30};
  drawRect(choice == 2, rect);

  SDL_Rect rect2 = {180, 250, 30, 30};
  drawRect(choice == 2, rect2);

  SDL_Rect rect3 = {210, 250, 30, 30};
  drawRect(choice == 2, rect3);

  SDL_RenderPresent(renderer);
}

void Menu::drawRect(bool filled, SDL_Rect rect) {
    if (filled) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Menu::clean() {
  SDL_DestroyWindow(maze);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

bool Menu::running() {
  return isRunning;
}

int Menu::getChoice() {
    return choice;
}