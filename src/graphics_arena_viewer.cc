/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include <iostream>
#include <string>
#include <vector>

#include "src/robot.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/arena_params.h"
#include "src/event_keypress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
  const struct arena_params* const params)
    : csci3081::GraphicsApp(params->x_dim, params->y_dim, "Robot Simulation"),
      arena_(new Arena(params)),
      paused_(false),
      pause_btn_(nullptr) {
  nanogui::FormHelper *gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10),
                                                       "Simulation Controls");
  gui->addButton("Restart",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  pause_btn_ = gui->addButton("Pause",
    std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));

  performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
///< this checks to see if thing has collided with the robot
///< <THis functino will check to see if the robot has collidid with an entity>
///< <It will check to see if the robot has collided with the entity at pos>
///< <p and radius radius.>
///< @param Position P position of the entity we want to check for collision
///< @param double radius radius of the entity we check for collision
///< <EDIT:: MADE THIS BEFORE I KNEW WHAT WAS GOING ON, NEVER USED IT AT ALL>
bool GraphicsArenaViewer::HasRobotCollided(Position  p, double radius) {
  // declare the variables used to check the distance between the radius here
  double robotxpos, robotypos;
  double entityxpos, entityypos;
  // set the values for the robot here
  Position robotpos = arena_->robot()->get_pos();
  robotxpos = robotpos.x;
  robotypos = robotpos.y;
  // set the values for the entity here
  entityxpos = p.x;
  entityypos = p.y;

  double adj = abs(robotxpos - entityxpos);
  double opp = abs(robotypos - entityypos);
  // now use the Pythagorean THeorem to find the distance
  double dist = sqrt((opp*opp) + (adj*adj));
  double robotrad = arena_->robot()->radius();
  // see if they are touching
  if (dist < (robotrad + radius)) {
    std::cout << "THEY HAVE COLLIDED" << std::endl;
    return true;
  } else {
    return false;
  }
}
// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    last_dt += dt;
    while (last_dt > 0.05) {
      arena_->AdvanceTime();
      last_dt -= 0.05;
    }
    // EventCollision e();

    // CheckForEntityCollision(arena_->robot(), arena_->home_base(), e, 1.0);
    // CheckForEntityCollision
    /*
    // CHECK FOR COLLISION WITH HOME BASE
    bool collided_with_home_base;
    Position home_base_pos = arena_->home_base()->get_pos();
    double home_base_radius = arena_->home_base()->radius();

    collided_with_home_base = HasRobotCollided(home_base_pos, home_base_radius);
    if(collided_with_home_base == true){
      std::cout << "COLLISION WITH HOME BASE" << std::endl;
    }
    // NOW CHECK FOR COLLISION WITH RECHARGE STATION
    bool collided_with_recharge_station;
    Position recharge_station_pos = arena_->recharge_station()->get_pos();
    double recharge_station_radius = arena_->recharge_station()->radius();

    collided_with_recharge_station = HasRobotCollided(recharge_station_pos, recharge_station_radius);
    if(collided_with_recharge_station == true){
      std::cout << "COLLISION WITH REACHARGE STATION" << std::endl;

    }
    // NOW CHECK FOR COLLISION WITH OBSTACLE(S)
*/
  }
}


/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnRestartBtnPressed() {
  arena_->Reset();
}

void GraphicsArenaViewer::OnPauseBtnPressed() {
  paused_ = !paused_;
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}

void GraphicsArenaViewer::OnMouseMove(int x, int y) {
  std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseDown(int x, int y) {
  std::cout << "Left mouse button DOWN (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseUp(int x, int y) {
  std::cout << "Left mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnRightMouseDown(int x, int y) {
  std::cout << "Right mouse button DOWN (" << x << ", " << y << ")\n";
}

void GraphicsArenaViewer::OnRightMouseUp(int x, int y) {
  std::cout << "Right mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnKeyDown(const char *c, int modifiers) {
  std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnKeyUp(const char *c, int modifiers) {
  std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
}



void GraphicsArenaViewer::OnSpecialKeyDown(int key, int scancode,
  int modifiers) {
  EventKeypress e(key);
  arena_->Accept(&e);
  std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyUp(int key, int scancode, int modifiers) {
  EventKeypress e(key);
  arena_->Accept(&e);
  std::cout << "Special Key UP key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx, const Robot* const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading for this robot
  nvgSave(ctx);
  nvgTranslate(ctx, robot->get_pos().x, robot->get_pos().y);
  nvgRotate(ctx, robot->get_heading_angle());

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, robot->radius());
  nvgFillColor(ctx, nvgRGBA(robot->color().r,
                            robot->color().g,
                            robot->color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, robot->name().c_str(), NULL);
  nvgRestore(ctx);
  nvgRestore(ctx);
}

void GraphicsArenaViewer::DrawObstacle(NVGcontext *ctx,
                                       const Obstacle* const obstacle) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
    obstacle->radius());
  nvgFillColor(ctx, nvgRGBA(obstacle->color().r,
                            obstacle->color().g,
                            obstacle->color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
          obstacle->name().c_str(), NULL);
}

void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx,
                               const HomeBase* const home) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, home->get_pos().x, home->get_pos().y, home->radius());
  nvgFillColor(ctx, nvgRGBA(home->color().r,
                            home->color().g,
                            home->color().b,
                            255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, home->get_pos().x, home->get_pos().y, home->name().c_str(),
    NULL);
}

// This is the primary driver for drawing all entities in the arena.
// It is called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  std::vector<Obstacle*> obstacles = arena_->obstacles();
  for (size_t i = 0; i < obstacles.size(); i++) {
    DrawObstacle(ctx, obstacles[i]);
  } /* for(i..) */

  DrawRobot(ctx, arena_->robot());
  DrawHomeBase(ctx, arena_->home_base());
}

NAMESPACE_END(csci3081);
