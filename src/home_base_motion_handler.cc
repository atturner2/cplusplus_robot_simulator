/**
* @file home_base_motion_handler.cc
*
* @copyright 2017 3081 Staff, All rights reserved.
*/
///<  Includes
#include "src/home_base_motion_handler.h"

///<  <AS you can see this is a blatant copy of robot>

NAMESPACE_BEGIN(csci3081);
///<  Constructor
HomeBaseMotionHandler::HomeBaseMotionHandler() :
heading_angle_(0.0) {
}
///<  Member Functions

void HomeBaseMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    heading_angle_ = - 180.0 + ((2*(st.get_angle_of_contact()*M_PI/180.0)) -
    heading_angle_);
  }
}
NAMESPACE_END(csci3081);
