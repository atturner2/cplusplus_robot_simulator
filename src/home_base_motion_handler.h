/**
* @file actuator_handler.h
*
* @copyright 2017 3081 Staff, All rights reserved.
*/
///  <AS you can see this is a blatant copy of robot>
#ifndef PROJECT_ITERATION1_SRC_HOME_BASE_MOTION_HANDLER_H_
///  Includes
#include "src/event_commands.h"
#include "src/home_base_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"

NAMESPACE_BEGIN(csci3081);

class HomeBaseMotionHandler {
 public:
  HomeBaseMotionHandler();
  ///<  <Reset the home base>
  void Reset(void) {}

  ///<  <I am NOT including the AcceptCommand capability>

  void UpdateVelocity(SensorTouch st);

  double get_speed() { return speed_; }
  ///<  <c++ gets cranky if I don't include a getter for speed>
  void set_speed(double speed) { speed_ = speed; }
  double get_heading_angle() const { return heading_angle_; }
  void set_heading_angle(double ha) { heading_angle_ = ha; }

 private:
  double angle_delta = 5.0;
  double heading_angle_;
  double speed_ = 10.0;
};

NAMESPACE_END(csci3081);

#endif  //  PROJECT_ITERATION1_SRC_HOME_BASE_MOTION_HANDLER_H_
