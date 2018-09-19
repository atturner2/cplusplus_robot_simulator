/**
 * @file robot_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "src/robot_battery.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
double RobotBattery::Deplete(__unused Position old_pos,
  __unused Position new_pos, __unused double dt) {
  /* @todo deplete battery by some value based on movement and speed */
int opp = abs(new_pos.y - old_pos.y);
int adj = abs(new_pos.x - old_pos.y);
///<  <ADDED CHECKER HERE TO MAKE SURE THAT IT DEOSNT GO BELOW ZERO>
int dist = sqrt((opp*opp) + (adj*adj));
///<  charge_ -= dist * .001;
if (charge_ > (charge_ - dist * .001)) {
return charge_;
} else {
  charge_ = 0;
  return charge_;
}
} /* deplete() */

void Accept(__unused EventCollision * e) {
  /* @todo deplete battery by some value -- arbitrary selected for bumping */
}

NAMESPACE_END(csci3081);
