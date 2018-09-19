/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
///<  <changed max speed of robot>
RobotMotionHandler::RobotMotionHandler() :
  heading_angle_(0.0),
  speed_(0.0),
  max_speed_(50) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  double heading;
  switch (cmd) {
  case COM_TURN_LEFT:
  heading = get_heading_angle();
  set_heading_angle(heading - angle_delta);
  break;
  case COM_TURN_RIGHT:
  heading = get_heading_angle();
  set_heading_angle(heading + angle_delta);
  break;
  case COM_SPEED_UP:
  if (speed_ < max_speed_) {
    double current = get_speed();
    set_speed(current + speed_delta);
  } else {
    std::cout << "Speed is already maxed out" << std::endl;
  }
  break;
  case COM_SLOW_DOWN:
  if (speed_ > 0) {
    double current = get_speed();
    set_speed(current - speed_delta);
  } else {
    std::cout << "Speed is already zeroed out" << std::endl;
  }
  break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    //  <here I set the angle using my calculations>
    heading_angle_ =  -180.0 + ((2*(st.get_angle_of_contact())) - heading_angle_);
  }
}

NAMESPACE_END(csci3081);
