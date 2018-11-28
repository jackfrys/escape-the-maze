#ifndef MENU_CXXTEST_H
#define MENU_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../src/Menu.h"

class MenuTestSuite : public CxxTest::TestSuite
{
public:

  void test_newMenuRunning() {
    Menu m;
    TS_ASSERT(m.running());
  }

};

#endif
