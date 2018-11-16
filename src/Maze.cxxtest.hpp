#ifndef MAZE_CXXTEST_H
#define MAZE_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Maze.hpp"

class MazeTestSuite : public CxxTest::TestSuite
{
public:

  void test_newMazeRunning() {
    Maze m;
    TS_ASSERT(m.running());
  }

};

#endif
