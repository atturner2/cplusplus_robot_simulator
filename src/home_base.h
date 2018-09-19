/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_HOME_BASE_H_
#define PROJECT_ITERATION1_SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/home_base_params.h"
#include "src/arena_mobile_entity.h"
#include "src/home_base_motion_handler.h"
#include "src/home_base_motion_behavior.h"
#include "src/event_collision.h"
#include "src/sensor_touch.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
///<  <changed to a mobile entity>
class HomeBase: public ArenaMobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params);
  std::string name(void) const { return "Home Base"; }
  void Reset(void);

  void Accept(EventCollision * e);
  void TimestepUpdate(unsigned int dt);
  double get_heading_angle(void) const { return motion_handler_.get_heading_angle(); }
  void set_heading_angle(double heading_angle) {
  motion_handler_.set_heading_angle(heading_angle); }
  double get_speed(void) { return speed_; }
  void set_speed(double sp) { speed_ = sp; }
///<  void Accept(EventCollision * e);
  void Accept(EventRecharge * e) {}
  int id(void) { return id_; }
  void resetpos(Position p);
  ///<  <Reseting the random after I have used it in the timestep>
  void decrementrandom() { random = random - 1; }
  void assignnewrandom() {
    random = rand() % 100; }

 private:
  static unsigned int next_id_;
  ///<  <Adding my start_pos and start_headingangle variables for the reset>
  Position start_pos;
  ///<  <Adding my reset value for heading angle>
  double start_headingangle = 235.0;
  ///<  <add my random int for when I have to make it change directions/speed>
  int random;
  int id_;
  double heading_angle_;
  double angle_delta_;
  double speed_ = 10.0;
  HomeBaseMotionHandler motion_handler_;
  HomeBaseMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif  //  PROJECT_ITERATION1_SRC_HOME_BASE_H_
