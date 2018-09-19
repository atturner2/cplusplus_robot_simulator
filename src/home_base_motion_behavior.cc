/**
* @file home_base_motion_behavior.cc
*
* @copyright 2017 3081 Staff, All rights reserved.
*/
//  Includes
#include "src/home_base_motion_behavior.h"
#include "src/arena_mobile_entity.h"
///<  <AS you can see this is a blatant copy of robot>

NAMESPACE_BEGIN(csci3081);
///<  Member Functions
void HomeBaseMotionBehavior::UpdatePosition(ArenaMobileEntity * const ent,
  unsigned int dt) {
  ///< save positon for debuggin purposes
  Position new_pos = ent->get_pos();
  Position old_pos = ent->get_pos();

  ///<  Movement is always along the heading_angle (i.e. the hypotenuse)
  new_pos.x += cos(ent->get_heading_angle()*M_PI/180.0)*ent->get_speed()*dt;
  new_pos.y += sin(ent->get_heading_angle()*M_PI/180.0)*ent->get_speed()*dt;
  ent->set_pos(new_pos);
  ///<  Print stuff here if it's not working
}
NAMESPACE_END(csci3081)
