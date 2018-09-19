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
  public:
  Position(void) : x(0.0), y(0.0) { }
  Position(double in_x, double in_y) : x(in_x), y(in_y) { }
    double x;
    double y;
  };

NAMESPACE_END(csci3081)

#endif  //  PROJECT_ITERATION1_SRC_POSITION_H_
