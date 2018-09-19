/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_ROBOT_H_
#define PROJECT_ITERATION1_SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/robot_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Robot : public ArenaMobileEntity {
 public:
  explicit Robot(const struct robot_params* const params);

  void ResetBattery(void);
  void Reset(void);
  void HeadingAngleInc(void) { heading_angle_ += angle_delta_; }
  void HeadingAngleDec(void) { heading_angle_ -= angle_delta_; }
  void TimestepUpdate(unsigned int dt);
  void Accept(EventRecharge * e);
  void Accept(EventCollision * e);
  void EventCmd(enum event_commands cmd);


  ///< Deplete depletes thebattery
  void Deplete(void) { battery_.Deplete(); }
  double get_battery_level(void) { return battery_.get_level(); }
  double get_heading_angle(void) const { return motion_handler_.get_heading_angle(); }
  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }
  double get_speed(void) { return motion_handler_.get_speed(); }
  void set_speed(double sp) { motion_handler_.set_speed(sp); }
  int id(void) const { return id_; }
  std::string name(void) const {
    return "Robot" + std::to_string(id());
  }
  ///< ResetPos resets the positon to the positon p
  ///< Resetspeed resets the heading angle to the starting heading angle
  void resetpos(Position p);
  void resetspeed();

 private:
  static unsigned int next_id_;
  ///<  <adding my start_pos variable and start_heading angle variable>
  ///<  <ans startspeed too>
  Position start_pos;
  double startspeed = 5;
  double startheadingangle = 37.0;
  ///<  <add the initialization in the constructor>
  int id_;
  double heading_angle_;
  double angle_delta_;
  RobotBattery battery_;
  RobotMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_ROBOT_H_
