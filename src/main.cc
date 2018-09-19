/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/color.h"
#include "src/position.h"
/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int, char **) {
  ///< Essential call to initiate the graphics window
  csci3081::InitGraphics();

  ///< Initialize default start values for various arena entities
  csci3081::robot_params rparams;
  csci3081::home_base_params hbparams;

  rparams.battery_max_charge = 100.0;
  rparams.angle_delta = 10;
  rparams.collision_delta = 1;
  rparams.radius = 20.0;
  rparams.pos = csci3081::Position(500.0, 500.0);
  ///<  <Note Robot starts green and changes color as battery dies>
  rparams.color = csci3081::Color(0, 128, 128, 255);

  hbparams.angle_delta_ = 10;
  hbparams.radius = 20.0;
  hbparams.pos = csci3081::Position(700.0, 300.0);
  hbparams.color = csci3081::Color(255, 0, 0, 255);
  hbparams.collision_delta = 1;

  csci3081::arena_params aparams;
  ///<  <These lines initlaize my new mobile home base>
  aparams.robot = rparams;
  aparams.home_base = hbparams;
  aparams.recharge_station.radius = 20.0;
  aparams.recharge_station.pos = {500.0, 300.0};
  aparams.recharge_station.color = csci3081::Color(0, 128, 128, 255);





  ///<  <Here I make all my obstacles>

  aparams.obstacles[0].radius = 30.0;
  aparams.obstacles[0].pos = {200.0, 200.0};
  aparams.obstacles[0].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[1].radius = 30.0;
  aparams.obstacles[1].pos = {300.0, 300.0};
  aparams.obstacles[1].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[2].radius = 30.0;
  aparams.obstacles[2].pos = {200.0, 500.0};
  aparams.obstacles[2].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[3].radius = 30.0;
  aparams.obstacles[3].pos = {500.0, 650.0};
  aparams.obstacles[3].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.obstacles[4].radius = 30.0;
  aparams.obstacles[4].pos = {900.0, 100.0};
  aparams.obstacles[4].color = csci3081::Color(255, 255, 255, 255); /* white */

  aparams.n_obstacles = 5;
  aparams.x_dim = 1024;
  aparams.y_dim = 768;

  ///< Start up the graphics (which creates the arena).
  ///< Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
    new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
