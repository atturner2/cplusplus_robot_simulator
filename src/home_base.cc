/**
* @file home_base.cc
*
* @copyright 2017 3081 Staff, All rights reserved.
*/
/*******************************************************************************
  * Includes
******************************************************************************/
#include "src/home_base.h"
#include "src/robot_motion_behavior.h"
//  namespaces
NAMESPACE_BEGIN(csci3081);
///<  Constructor:
///<  <AS you can see this is a blatant copy of robot>

HomeBase::HomeBase(const struct home_base_params* const params) :
ArenaMobileEntity(params->radius, params->collision_delta, params->pos,
params->color),
heading_angle_(0),
angle_delta_(params->angle_delta_),
motion_handler_(),
motion_behavior_(),
sensor_touch_(), id_(-1) {
motion_handler_.set_heading_angle(235.0);
motion_handler_.set_speed(10);
start_pos.x = 700.0;
start_pos.y = 300.0;
///<  <Rand will be 1-100, and I will also change the heading by same value.>
random = rand() % 200;
}
///<  Member Functions
void HomeBase::TimestepUpdate(uint dt) {
  ///<  <decrement random every time, and then when it's zero, change heading>
  ///<  <by a random amount and then reset the random.>>
  random--;
  if (random == 0) {
    ///<  <assign random heading angle>
    double randheading = rand() % 50 + get_heading_angle();
    set_heading_angle(randheading);
    ///<  <reset random for next time>
    assignnewrandom();
  }

  Position old_pos = get_pos();
  ///<  update heading and speed as indicated by the touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  ///<  Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
  ///<  No need to deplete battery, this doesn't have one
  std::cout << "Current Homebase Kinematics"
  << get_pos().x << " " << get_pos().y << " " << get_heading_angle() << std::endl;
}

///<  pass along collision event to the touch sensor
void HomeBase::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}
//<  I added the calls= to reset_pos here>
void HomeBase::Reset(void) {
  set_heading_angle(start_headingangle);
  resetpos(start_pos);
  motion_handler_.Reset();
  sensor_touch_.Reset();
}
void HomeBase::resetpos(Position p) {
  set_pos(p);
}
///<  No user input commands to use

NAMESPACE_END(csci3081);
