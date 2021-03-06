#include "Maze.h"
#include "Cell.h"
#include "Util.h"
#include "Key.h"
#include "Guard.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// audio stuff
#define KEY_SOUND_PATH "./src/audio/key.wav"
Mix_Music *gKey = NULL;

/* 
 * 0 = up
 * 1 = down
 * 2 = left
 * 3 = right
 */
int DIRECTIONS[4] = { 0, 1, 2, 3 };

using namespace std;

int randInt(int min, int max) {
  return min + (rand() % static_cast<int>(max - min + 1));
}

Posn startingPosition() {
  Posn p = Posn();
  p.x = 0;
  p.y = 0;
  return p;
}

Maze::Maze() {
  privateInit(DEFAULT_MAZE_SIZE);
}

Maze::Maze(int difficulty) {
  int newSize;

  switch (difficulty) {
    case 1:
      newSize = DEFAULT_MAZE_SIZE;
      num_guards = 1;
      health = 5;
      canShuffle = false;
      break;
    case 2:
      newSize = MED_MAZE_SIZE;
      num_guards = 2;
      health = 4;
      canShuffle = true;
      break;
    case 3:
      newSize = HARD_MAZE_SIZE;
      num_guards = 3;
      health = 3;
      canShuffle = true;
      break;
    default:
      newSize = DEFAULT_MAZE_SIZE;
      num_guards = 1;
      health = 5;
      canShuffle = false;
      break;
  }

  privateInit(newSize);
}

Maze::~Maze() {
  // Free up space
  for(int i = 0; i < size; i++) {
    delete [] cells[i];
  }
  delete [] cells;
  delete [] keys;
  delete [] guards;
}

void Maze::generateMaze(int sx, int sy) {
  // Randomly shuffle the directions
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(begin(DIRECTIONS), end(DIRECTIONS), default_random_engine(seed));

  for (int i = 0; i < 4; i++) {
    // Generate the new coords for the next cell
    int nx = sx + DX[DIRECTIONS[i]];
    int ny = sy + DY[DIRECTIONS[i]];

    // If it's a valid cell then break the walls and recurse
    if ((ny < size && ny >= 0) && (nx < size && nx >= 0) && cells[nx][ny].notVisited()) {
      cells[nx][ny].breakWall(DIRECTIONS[i]);
      cells[nx][ny].setVisited();
      cells[sx][sy].breakOppWall(DIRECTIONS[i]);
      cells[sx][sy].setVisited();
      generateMaze(nx, ny);
    }
  }
}

void Maze::init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) != 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    gKey = Mix_LoadMUS( "./src/audio/key.wav" );
    if( gKey == NULL )
    {
        printf( "Failed to load key sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    int width = size * CELL_SIZE;
    int height = size * CELL_SIZE + 20;

    // initialize the SDL2 Window
    maze = SDL_CreateWindow("MAZE ESCAPE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    // Initialize the SDL2 Renderer
    renderer = SDL_CreateRenderer(maze, -1, 0);

    generateMaze(0, 0);

    for (int i = 0; i < KEY_COUNT; i++) {
      Posn p = Posn();
      p.x = rand() % size;
      p.y = rand() % size;
      Key k = Key();
      k.p = p;
      k.found = false;
      keys[i] = k;
    }

    for (int i = 0; i < num_guards; i++) {
      Posn p = Posn();
      p.x = rand() % size;
      p.y = rand() % size;
      Guard g = Guard();
      g.p = p;
      guards[i] = g;
    }

    isRunning = true;
  } else {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
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
          if (player.x > 0 && cells[player.x][player.y].canMove(2)) player.x--;
          break;
        case SDLK_RIGHT:
          if (player.x < size - 1 && cells[player.x][player.y].canMove(3)) player.x++;
          break;
        case SDLK_UP:
          if (player.y > 0 && cells[player.x][player.y].canMove(0)) player.y--;
          break;
        case SDLK_DOWN:
          if (player.y < size - 1 && cells[player.x][player.y].canMove(1)) player.y++;
          break;
        case SDLK_RETURN:
          if (isWon || isLost) isRunning = false;
          break;
      }
      break;
    default:
      break;
  }

  updateKeys();
  if (player.x == size - 1 && player.y == size -1 && remainingKeys == 0) {
    isWon = true;
  }
}

bool keyFound(Key k, Posn p) {
  return k.p.x == p.x && k.p.y == p.y;
}

bool guardCollide(Guard g, Posn p) {
  //Mix_PlayMusic( gHurt, 1);
  return g.p.x == p.x && g.p.y == p.y;
}

void Maze::updateKeys() {
  for (int i = 0; i < KEY_COUNT; i++) {
    if (!keys[i].found && keyFound(keys[i], player)) {
      keys[i].found = true;
      remainingKeys--;
      Mix_PlayMusic( gKey, 1);

      if (canShuffle) {
        cells = new Cell*[size];
        for(int i = 0; i < size; ++i) {
          cells[i] = new Cell[size];
        }
        generateMaze(0, 0);
      }
    }
  }
}

void Maze::updateGuards() {
  for (int i = 0; i < num_guards; i++) {
    int x = guards[i].p.x;
    int y = guards[i].p.y;
    if (guardCollide(guards[i], player)) {
      if (health <= 1) {
        isLost = true;
      } else {
        health--;
      }
    }
    int rand = randInt(1, 4);
    switch (rand) {
      case 1:
        if (x > 0 && cells[x][y].canMove(2)) guards[i].p.x--;
        break;
      case 2:
        if (x < size - 1 && cells[x][y].canMove(3)) guards[i].p.x++;
        break;
      case 3:
        if (y > 0 && cells[x][y].canMove(0)) guards[i].p.y--;
        break;
      case 4:
        if (y < size - 1 && cells[x][y].canMove(1)) guards[i].p.y++;
        break;
      default:
        break;
    }
  }
}

// TODO no clue yet
void Maze::update() {
  if (time%150 == 0) {
    updateGuards();
  }
  time++;
}

void Maze::render() {
  // Set draw color to black
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  if (isWon) {
    // Set draw color to black
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, 170, 180, 170, 225);
    SDL_RenderDrawLine(renderer, 170, 225, 175, 225);
    SDL_RenderDrawLine(renderer, 175, 210, 175, 225);
    SDL_RenderDrawLine(renderer, 175, 225, 180, 225);
    SDL_RenderDrawLine(renderer, 180, 225, 180, 180);

    SDL_RenderDrawLine(renderer, 190, 225, 190, 180);

    SDL_RenderDrawLine(renderer, 200, 225, 200, 180);
    SDL_RenderDrawLine(renderer, 200, 180, 210, 225);
    SDL_RenderDrawLine(renderer, 210, 225, 210, 180);
    
    SDL_RenderPresent(renderer);
  } else if (isLost) {
    // Set draw color to black
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, 160, 185, 160, 225);
    SDL_RenderDrawLine(renderer, 160, 225, 170, 225);

    SDL_RenderDrawLine(renderer, 175, 225, 185, 225);
    SDL_RenderDrawLine(renderer, 175, 185, 185, 185);
    SDL_RenderDrawLine(renderer, 175, 185, 175, 225);
    SDL_RenderDrawLine(renderer, 185, 185, 185, 225);

    SDL_RenderDrawLine(renderer, 190, 185, 200, 185);
    SDL_RenderDrawLine(renderer, 190, 185, 190, 205);
    SDL_RenderDrawLine(renderer, 190, 205, 200, 205);
    SDL_RenderDrawLine(renderer, 200, 205, 200, 225);
    SDL_RenderDrawLine(renderer, 200, 225, 190, 225);

    SDL_RenderDrawLine(renderer, 205, 185, 215, 185);
    SDL_RenderDrawLine(renderer, 210, 185, 210, 225);
    
    SDL_RenderPresent(renderer);
  } else {
    if (alternate) {
      SDL_SetRenderDrawColor(renderer, 152, 251, 152, 255);
    }

    // This function colors in the whole window
    SDL_RenderClear(renderer);

    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        if (x == size - 1 && y == size - 1) {
          int modifier = 4;
          SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
          int xPos = x * CELL_SIZE + modifier;
          int yPos = y * CELL_SIZE + modifier;
          int size = CELL_SIZE - (modifier * 2);
          SDL_Rect door = { xPos, yPos, size, size };
          SDL_RenderFillRect(renderer, &door);
        }

        if (player.x == x && player.y == y) {
          SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
          int modifier = 4;
          int xPos = x * CELL_SIZE + modifier;
          int yPos = y * CELL_SIZE + modifier;
          int size = CELL_SIZE - (modifier * 2);
          SDL_Rect player = { xPos, yPos, size, size };
          SDL_RenderFillRect(renderer, &player);
        }

        for (int i = 0; i < KEY_COUNT; i++) {
          Key k = keys[i];
          if (!k.found && k.p.x == x && k.p.y == y) {
            SDL_SetRenderDrawColor(renderer, 255, 185, 0, 0);
            int modifier = 4;
            int xPos = x * CELL_SIZE + modifier;
            int yPos = y * CELL_SIZE + modifier;
            int size = CELL_SIZE - (modifier * 2);
            SDL_Rect key = { xPos, yPos, size, size };
            SDL_RenderFillRect(renderer, &key);
          }
        }

        for (int i = 0; i < num_guards; i++) {
          Guard g = guards[i];
          if (g.p.x == x && g.p.y == y) {
            SDL_SetRenderDrawColor(renderer, 0, 185, 0, 0);
            int modifier = 4;
            int xPos = x * CELL_SIZE + modifier;
            int yPos = y * CELL_SIZE + modifier;
            int size = CELL_SIZE - (modifier * 2);
            SDL_Rect guard = { xPos, yPos, size, size };
            SDL_RenderFillRect(renderer, &guard);
          }
        }

        cells[x][y].renderCell(renderer, x, y, alternate);
      }
    }

    int bottomCell = size * CELL_SIZE + 5;
    
    switch (health) {
      case 10:
        SDL_RenderDrawLine(renderer, 10, bottomCell, 10, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 15, bottomCell, 20, bottomCell);
        SDL_RenderDrawLine(renderer, 15, bottomCell, 15, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 15, bottomCell + 10, 20, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 20, bottomCell, 20, bottomCell + 10);
        break;
      case 9:
        SDL_RenderDrawLine(renderer, 15, bottomCell, 15, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 10, bottomCell, 10, bottomCell + 5);
        SDL_RenderDrawLine(renderer, 10, bottomCell, 15, bottomCell);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 15, bottomCell + 5);
        break;
      case 8:
        SDL_RenderDrawLine(renderer, 15, bottomCell, 15, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 10, bottomCell, 10, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 10, bottomCell, 15, bottomCell);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 15, bottomCell + 5);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 10, 15, bottomCell + 10);
        break;
      case 7:
        SDL_RenderDrawLine(renderer, 15, bottomCell, 15, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 10, bottomCell, 15, bottomCell);
        break;
      case 6:
        SDL_RenderDrawLine(renderer, 10, bottomCell + 10, 10, bottomCell);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 15, bottomCell + 5);
        SDL_RenderDrawLine(renderer, 15, bottomCell + 5, 15, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 10, 15, bottomCell + 10);
        break;
      case 5:
        SDL_RenderDrawLine(renderer, 10, bottomCell, 15, bottomCell);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 10, bottomCell);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 15, bottomCell + 5);
        SDL_RenderDrawLine(renderer, 15, bottomCell + 5, 15, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 10, 15, bottomCell + 10);
        break;
      case 4:
        SDL_RenderDrawLine(renderer, 10, bottomCell, 10, bottomCell + 5);
        SDL_RenderDrawLine(renderer, 15, bottomCell + 5, 15, bottomCell);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 15, bottomCell + 5);
        SDL_RenderDrawLine(renderer, 15, bottomCell + 5, 15, bottomCell + 10);
        break;
      case 3:
        SDL_RenderDrawLine(renderer, 10, bottomCell, 15, bottomCell);
        SDL_RenderDrawLine(renderer, 15, bottomCell + 5, 15, bottomCell);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 15, bottomCell + 5);
        SDL_RenderDrawLine(renderer, 15, bottomCell + 5, 15, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 10, 15, bottomCell + 10);
        break;
      case 2:
        SDL_RenderDrawLine(renderer, 10, bottomCell, 15, bottomCell);
        SDL_RenderDrawLine(renderer, 15, bottomCell + 5, 15, bottomCell);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 15, bottomCell + 5);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 5, 10, bottomCell + 10);
        SDL_RenderDrawLine(renderer, 10, bottomCell + 10, 15, bottomCell + 10);
        break;
      case 1:
        SDL_RenderDrawLine(renderer, 10, bottomCell, 10, bottomCell + 10);
        break;
      default:
        SDL_RenderDrawLine(renderer, 10, bottomCell, 10, bottomCell + 10);
        break;
    }

    SDL_RenderPresent(renderer);
  }
}

void Maze::clean() {
  Mix_FreeMusic(gKey);
  SDL_DestroyWindow(maze);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

bool Maze::running() {
  return isRunning;
}

void Maze::privateInit(int newSize) {
  // Dynamically generate the 2D array
  // Eventually this constructor will take a difficulty and change the size
  size = newSize;
  player = startingPosition();
  cells = new Cell*[size];
  for(int i = 0; i < size; ++i) {
    cells[i] = new Cell[size];
  }
  keys = new Key[KEY_COUNT];
  remainingKeys = KEY_COUNT;
  guards = new Guard[num_guards];
  time = 0;
  isRunning = true;
  isWon = false;
  isLost = false;
  alternate = false;
}

void Maze::changeColorScheme() {
  alternate = true;
}