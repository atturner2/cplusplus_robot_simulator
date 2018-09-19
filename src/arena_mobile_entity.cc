/**
 * @file arena_mobile_entity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity.h"
#include "src/robot_motion_behavior.h"
#include "src/home_base_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void ArenaMobileEntity::TimestepUpdate(uint dt) {
  RobotMotionBehavior h;
  HomeBaseMotionBehavior hb;
  h.UpdatePosition(this, dt);
  hb.UpdatePosition(this, dt);
} /* TimestepUpdate() */

NAMESPACE_END(csci3081);
