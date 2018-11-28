#include "Maze.h"
#include "Cell.h"
#include "Util.h"
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <SDL2/SDL_image.h>

// audio stuff
#define KEY_SOUND_PATH "./src/audio/key.wav"
#define HURT_SOUND_PATH "./src/audio/hurt.wav"
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
void my_audio_callback(void *userdata, Uint8 *stream, int len) {
  
  if (audio_len == 0)
    return;
  
  len = ( len > audio_len ? audio_len : len );
  //SDL_memcpy (stream, audio_pos, len);          // simply copy from one buffer into the other
  SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another
  
  audio_pos += len;
  audio_len -= len;
}

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
      break;
    case 2:
      newSize = MEDIUM_MAZE_SIZE;
      break;
    case 3:
      newSize = HARD_MAZE_SIZE;
      break;
    default:
      newSize = DEFAULT_MAZE_SIZE;
      break;
  }

  privateInit(newSize);
}

Maze::~Maze() {
  IMG_Quit();
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

  for (int i = 0; i < KEY_COUNT; i++) {
    Posn p = Posn();
    p.x = rand() % size;
    p.y = rand() % size;
    Key k = Key();
    k.p = p;
    k.found = false;
    keys[i] = k;
  }

  for (int i = 0; i < GUARD_COUNT; i++) {
    Posn p = Posn();
    p.x = rand() % size;
    p.y = rand() % size;
    Guard g = Guard();
    g.p = p;
    guards[i] = g;
  }
}

void Maze::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

    int width = size * CELL_SIZE;
    int height = size * CELL_SIZE;

    // initialize the SDL2 Window
    maze = SDL_CreateWindow("MAZE ESCAPE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    // Initialize the SDL2 Renderer
    renderer = SDL_CreateRenderer(maze, -1, 0);

    generateMaze(0, 0);

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
      }
      break;
    default:
      break;
  }

  updateKeys();
  if (player.x == size - 1 && player.y == size -1 && remainingKeys == 0) {
    isRunning = false;
  }
}

bool keyFound(Key k, Posn p) {
  return k.p.x == p.x && k.p.y == p.y;
}

bool guardCollide(Guard g, Posn p) {
  return g.p.x == p.x && g.p.y == p.y;
}

void Maze::updateKeys() {
  for (int i = 0; i < KEY_COUNT; i++) {
    if (!keys[i].found && keyFound(keys[i], player)) {
      keys[i].found = true;
      remainingKeys--;
      playSound(KEY_SOUND_PATH);
    }
  }
}

void Maze::updateGuards() {
  for (int i = 0; i < GUARD_COUNT; i++) {
    int x = guards[i].p.x;
    int y = guards[i].p.y;
    if (guardCollide(guards[i], player)) {
      isRunning = false;
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

  // This function colors in the whole window
  SDL_RenderClear(renderer);

  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
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

      for (int i = 0; i < GUARD_COUNT; i++) {
        Guard g = guards[i];
        if (g.p.x == x && g.p.y == y) {
          SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
          int modifier = 4;
          int xPos = x * CELL_SIZE + modifier;
          int yPos = y * CELL_SIZE + modifier;
          int size = CELL_SIZE - (modifier * 2);
          SDL_Rect key = { xPos, yPos, size, size };
          SDL_RenderFillRect(renderer, &key);
          // std::string path = "./src/img/guard.png";
          // SDL_Surface* loadedSurface = IMG_Load(path.c_str());
          // if (loadedSurface == NULL) {
          //   std::cout <<  "Unable to load image %s! SDL_image Error: %s\n" << path.c_str() << IMG_GetError() << std::endl;
          // } else {
          //   SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface); 
          // //  SDL_FreeSurface(loadedSurface);
          // //   SDL_Rect destination;
          // //   destination.x = x * CELL_SIZE + 4;
          // //   destination.y = y * CELL_SIZE + 4;
          // //   destination.w = 12;
          // //   destination.h = 12;

          // //   SDL_RenderCopy(renderer, texture, NULL, &destination);
          // }
        }
      }
      cells[x][y].renderCell(renderer, x, y);
    }
  }

  SDL_RenderPresent(renderer);
}

void Maze::playSound(const char * sound) {
  static Uint32 wav_length; // length of our sample
  static Uint8 *wav_buffer; // buffer containing our audio file
  static SDL_AudioSpec wav_spec; // the specs of our piece of music
  /* Load the WAV */
  // the specs, length and buffer of our wav are filled
  if( SDL_LoadWAV(sound, &wav_spec, &wav_buffer, &wav_length) == NULL) {
    return;
  }
  // set the callback function
  wav_spec.callback = my_audio_callback;
  wav_spec.userdata = NULL;
  // set our global static variables
  audio_pos = wav_buffer; // copy sound buffer
  audio_len = wav_length; // copy file length
  
  /* Open the audio device */
  if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    exit(-1);
  }
  
  /* Start playing */
  SDL_PauseAudio(0);

  // wait until we're don't playing
  while ( audio_len > 0 ) {
    SDL_Delay(100); 
  }
  
  // shut everything down
  SDL_CloseAudio();
  SDL_FreeWAV(wav_buffer);
}

void Maze::clean() {
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
  guards = new Guard[GUARD_COUNT];
  time = 0;
  isRunning = true;
}