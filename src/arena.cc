/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena.h"
#include "src/robot.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim), y_dim_(params->y_dim),
  robot_(new Robot(&params->robot)),
  n_robots_(1),
  n_obstacles_(params->n_obstacles),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  robot_->set_heading_angle(37);
  entities_.push_back(robot_);
  entities_.push_back(home_base_);
  mobile_entities_.push_back(robot_);
  ///<  <need dmobile push back for homebase>
  mobile_entities_.push_back(home_base_);
  entities_.push_back(recharge_station_);



  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::Reset(void) {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

void Arena::AdvanceTime(void) {
  //  std::cout << "Advancing simulation time by 1 timestep\n";
  UpdateEntitiesTimestep();
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  } /* for(ent..) */

  /*
   * Next, check if the robot has run out of battery
   */
   //  <this is where I implement losing>
  if (robot_->get_battery_level() <=0) {
    std::cout << "YOU HAVE LOST THE ROBOT GAME" << std::endl;
    assert(0); /* not implemented yet */
  }

  /*
   * Next, check if the robot has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * robot away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;
  ///<  <This is where I impement winning>
  CheckForEntityCollision(robot_, home_base_, &ec, robot_->collision_delta());
  if (ec.collided()) {
       std::cout << "YOU HAVE WON THE ROBOT GAME" << std::endl;
       assert(0); /* not implemented yet */
  }

  CheckForEntityCollision(robot_, recharge_station_,
    &ec, robot_->collision_delta());
  if (ec.collided()) {
    EventRecharge er;
    robot_->Accept(&er);
  }

  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */
  for (auto ent : mobile_entities_) {
    ///< Check if it is out of bounds. If so, use that as point of contact.
    assert(ent->is_mobile());
    ///< <std::cout << ent->name() << std::endl;>
    CheckForEntityOutOfBounds(ent, &ec);


    ///< If not at wall, check if colliding with any other entities (not itself)
    if (!ec.collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec, ent->collision_delta());
        if (ec.collided()) {
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */
///<  <I changed the values that go to the angle of contact for the apporopriate collision events>
void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
  EventCollision * event) {
  if (ent->get_pos().x+ ent->radius() >= x_dim_) {
    //  Right Wall
    event->collided(true);
    event->set_point_of_contact(Position(x_dim_, ent->get_pos().y));

    event->set_angle_of_contact(0.0);
    std::cout << ent->name() << "has left the arena!!" << std::endl;
    //  Left Wall
  } else if (ent->get_pos().x- ent->radius() <= 0) {
    event->collided(true);
    event->set_point_of_contact(Position(0.0, ent->get_pos().y));
    //  event->angle_of_contact(-180 + ent->heading_angle());
    event->set_angle_of_contact(0.0);
  } else if (ent->get_pos().y+ ent->radius() >= y_dim_) {
    // Bottom Wall
    event->collided(true);
    event->set_point_of_contact(Position(ent->get_pos().x, y_dim_));
    event->set_angle_of_contact(180.0 - ent->get_heading_angle());
  } else if (ent->get_pos().y - ent->radius() <= 0.0) {
    // Top Wall
    event->collided(true);
    event->set_point_of_contact(Position(0.0, y_dim_));
    event->set_angle_of_contact(180.0 - ent->get_heading_angle());
  } else {
    event->collided(false);
  }
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaEntity* const ent1,
  const ArenaEntity* const ent2,
  EventCollision * event,
  double collision_delta) {
  /* Note: this assumes circular entities */
  double ent1_x = ent1->get_pos().x;
  double ent1_y = ent1->get_pos().y;
  double ent2_x = ent2->get_pos().x;
  double ent2_y = ent2->get_pos().y;
  double dist = std::sqrt(
    std::pow(ent2_x - ent1_x, 2) + std::pow(ent2_y - ent1_y, 2));
  if (dist > ent1->radius() + ent2->radius() + collision_delta) {
    event->collided(false);
  } else {
    ///< <This checks to see if it hit an obstacle, decrement speed and battery>
    if (((ent2->name().find("Obstacle")) == 0) &&
    ((ent1->name().find("Robot")) == 0)) {
      robot_->Deplete();
      double speed = robot_->get_speed();
      if (speed > 5) {
      speed = speed * 0.9;
      robot_->set_speed(speed);
      }
    }
    ///<  Populate the collision event.
    ///<  Collided is true
    ///<  Point of contact is point along perimeter of ent1
    ///<  Angle of contact is angle to that point of contact
    ///< <here I compute the point of contact, covert it to degrees, and send it to the event>
    double theta;
    theta =  (atan((ent1_y - ent2_y) / (ent1_x - ent2_x)))*180.0/3.14;
    event->set_angle_of_contact(theta);
    Position point;
    point.x = 20.0*sin(theta);
    point.y = 20.0*cos(theta);
    event->set_point_of_contact(point);
    ///< <switched this to true>
    event->collided(true);
    ///< >>>>>>> FILL THIS IN
  }
} /* entities_have_collided() */

void Arena::Accept(__unused EventKeypress * e) {
  robot_->EventCmd(e->get_key_cmd());
}

NAMESPACE_END(csci3081);
