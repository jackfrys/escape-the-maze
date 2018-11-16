#ifndef CELL_CXXTEST_H
#define CELL_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Cell.hpp"

class CellTestSuite : public CxxTest::TestSuite
{
public:

  void test_visiting() {
    Cell c;
    TS_ASSERT(c.notVisited());
    c.setVisited();
    TS_ASSERT(!c.notVisited());
  }

};

#endif
