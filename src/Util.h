#ifndef UTIL_H
#define UTIL_H

// Cell size constraint
const int CELL_SIZE = 20;

const int DEFAULT_MAZE_SIZE = 20;

const int DX[4] = { 0, 0, 1, -1};
const int DY[4] = { 1, -1, 0, 0};

struct Posn {
    int x;
    int y;
};

#endif