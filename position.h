/**
 * @file color.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_POSITION_H_
#define PROJECT_ITERATION1_SRC_POSITION_H_

#include "src/common.h"

NAMESPACE_BEGIN(csci3081);

  struct Position {
  Position(void) : x(0), y(0) { }
  Position(int in_x, int in_y) : x(in_x), y(in_y) { }
    int x;
    int y;
  };
#endif  //  PROJECT_ITERATION1_SRC_POSITION_H_
