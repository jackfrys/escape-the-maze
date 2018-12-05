#ifndef KEY_CXXTEST_H
#define KEY_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../src/Key.h"
#include "../src/Util.h"

class KeyTestSuite : public CxxTest::TestSuite
{
public:

  void test_guardPosition() {
    Posn pos = Posn();
    Key k = Key();
    pos.x = 1;
    pos.y = 2;
    k.p = pos;
    k.found = false;

    TS_ASSERT(k.p.x == 1);
    TS_ASSERT(k.p.y == 2);
    TS_ASSERT(!k.found);

    k.found = true;

    TS_ASSERT(k.found);
  }

};


#endif
