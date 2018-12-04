#ifndef GUARD_CXXTEST_H
#define GUARD_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../src/Guard.h"
#include "../src/Util.h"

class GuardTestSuite : public CxxTest::TestSuite
{
public:

  void test_guardPosition() {
    Guard g;
    Posn pos = Posn();
    pos.x = 1;
    pos.y = 2;
    g.p = pos;

    TS_ASSERT(g.p.x == 1);
    TS_ASSERT(g.p.y == 2);
  }

};

#endif
