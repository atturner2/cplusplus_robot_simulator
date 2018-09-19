/**
* @file home_base_motion_handler.cc
*
* @copyright 2017 3081 Staff, All rights reserved.
*/
//  Includes
#ifndef PROJECT_ITERATION1_SRC_HOME_BASE_MOTION_BEHAVIOR_H_
#define PROJECT_ITERATION1_SRC_HOME_BASE_MOTION_BEHAVIOR_H_
///<  includes
///<  <AS you can see this is a blatant copy of robot>
#include <Eigen/Dense>
#include "src/common.h"
#include "src/position.h"
///<  namespaces
NAMESPACE_BEGIN(csci3081);
///<  Class Definitions
class HomeBaseMotionBehavior {
 public: HomeBaseMotionBehavior(void) {}
///<  <upfate the positon based on speed and collisions>
  void UpdatePosition(class ArenaMobileEntity * const ent, uint dt);
};
NAMESPACE_END(csci3081);
#endif  //  PROJECT_ITERATION1_SRC_HOME_BASE_MOTION_BEHAVIOR_H_
