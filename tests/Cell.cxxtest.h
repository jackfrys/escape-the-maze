#ifndef CELL_CXXTEST_H
#define CELL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../src/Cell.h"

class CellTestSuite : public CxxTest::TestSuite
{
public:

  void test_visiting() {
    Cell c;
    TS_ASSERT(c.notVisited());
    c.setVisited();
    TS_ASSERT(!c.notVisited());
  }

  void test_walls_and_move() {
  	Cell c;
  	TS_ASSERT_EQUALS(c.canMove(2), false);
  	TS_ASSERT_EQUALS(c.canMove(3), false);
  	c.breakWall(2);
  	TS_ASSERT_EQUALS(c.canMove(2), true);
  	TS_ASSERT_EQUALS(c.canMove(3), false);

  	TS_ASSERT_EQUALS(c.canMove(0), false);
  	TS_ASSERT_EQUALS(c.canMove(1), false);
  	c.breakOppWall(1);
  	TS_ASSERT_EQUALS(c.canMove(0), true);
  	TS_ASSERT_EQUALS(c.canMove(1), false);
  }

};

#endif
