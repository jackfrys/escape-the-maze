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
    showStart = true;
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
          if (showStart) {
            showStart = false;
          } else {
            isRunning = false;
          }
          break;
      }
      break;
    default:
      break;
  }
}

void Menu::render() {
  if (showStart) {
    // Set draw color to black
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, 0, 210, 400, 210);
    SDL_RenderDrawLine(renderer, 165, 180, 160, 225);
    SDL_RenderDrawLine(renderer, 165, 180, 170, 225);
    SDL_RenderDrawLine(renderer, 175, 180, 175, 225);
    SDL_RenderDrawLine(renderer, 175, 180, 180, 199);
    SDL_RenderDrawLine(renderer, 180, 199, 185, 180);
    SDL_RenderDrawLine(renderer, 185, 180, 185, 225);
    SDL_RenderDrawLine(renderer, 195, 180, 190, 225);
    SDL_RenderDrawLine(renderer, 195, 180, 200, 225);
    SDL_RenderDrawLine(renderer, 205, 180, 215, 180);
    SDL_RenderDrawLine(renderer, 215, 180, 205, 225);
    SDL_RenderDrawLine(renderer, 205, 225, 215, 225);
    SDL_RenderDrawLine(renderer, 220, 180, 220, 225);
    SDL_RenderDrawLine(renderer, 220, 180, 230, 180);
    SDL_RenderDrawLine(renderer, 220, 225, 230, 225);
    

    SDL_RenderPresent(renderer);
  } else {
    // Set draw color to black
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // This function colors in the whole window
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_Rect top = {180, 100, 30, 30};
    drawRect(choice == 0, top);

    SDL_Rect middle1 = {165, 200, 30, 30};
    drawRect(choice == 1, middle1);

    SDL_Rect middle2 = {195, 200, 30, 30};
    drawRect(choice == 1, middle2);

    SDL_Rect rect = {150, 300, 30, 30};
    drawRect(choice == 2, rect);

    SDL_Rect rect2 = {180, 300, 30, 30};
    drawRect(choice == 2, rect2);

    SDL_Rect rect3 = {210, 300, 30, 30};
    drawRect(choice == 2, rect3);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 160, 35, 170, 35);
    SDL_RenderDrawLine(renderer, 160, 55, 170, 55);
    SDL_RenderDrawLine(renderer, 160, 45, 170, 45);
    SDL_RenderDrawLine(renderer, 160, 35, 160, 45);
    SDL_RenderDrawLine(renderer, 170, 45, 170, 55);

    SDL_RenderDrawLine(renderer, 180, 35, 180, 55);

    SDL_RenderDrawLine(renderer, 190, 35, 200, 35);
    SDL_RenderDrawLine(renderer, 190, 55, 200, 55);
    SDL_RenderDrawLine(renderer, 200, 35, 190, 55);

    SDL_RenderDrawLine(renderer, 210, 35, 220, 35);
    SDL_RenderDrawLine(renderer, 210, 55, 220, 55);
    SDL_RenderDrawLine(renderer, 210, 45, 220, 45);
    SDL_RenderDrawLine(renderer, 210, 35, 210, 45);
    SDL_RenderDrawLine(renderer, 210, 45, 210, 55);

    SDL_RenderPresent(renderer);
  }
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