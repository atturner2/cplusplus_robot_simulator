#ifndef PROJECT_ITERATION1_SRC_MAINPAGE_H_
#define PROJECT_ITERATION1_SRC_MAINPAGE_H_
/*! PROJECT1_ITERATION1_SRC_MAINPAGE_H_
\mainpage CSCI3081 Robot Simulator Project
 * Note this is not cpplint compliant, but this assignment was before lab6, and   *this from lab 6, so it shouldn't be graded as part of lab5.
 * \section intro_sec Introduction
 * Copyright2017 Alex Turner
 * This code document creates an arena in which robots interact with obstacles, walls, and a charging station.  All of the entities in the arena are defined in a base class, and then separated into mobile and immobile. Each individual entity has it’s own class, and it’s own set of parameters through composition.   All of the events are taking place inside of the arena, which is translated to graphics using a graphics_arena_viewer class that utilizes nanoguii to show the different objects interacting on the screen.  Robots also have their own composed battery class, with it’s own set of parameters.  In the arena there are both obstacles, and a charging station for the robots, which triggers the batteries in the robot to recharge.

I am seperating my design description out by requirement, as that makes it easiest for me
to outline all of my necessary changes to the document.
Priority Level 1:
    Robot Command Arrowkey changes:
    The arrowkey changes first reuqired a change to be made to the event_commands.h file to add the SLOW_DOWN command.  THe appropriate switch statement also had to be added so that
    the appropriate command would be selected when the command is keyed in by the user.  The commands then need to be defined in a switch statement in robot_motion_handler so that the
    motion handler can adjust the heading and speed. THe commands are passed in using the event_commands class, and are taken in by the robots AcceptCommand function.

    Bounce Robot off of other entites at angle of incidence:
    This is by far the hardest, and currently, the most problematic functionality because of the "jitter"
    problem.  I find the angle between the the two entities and define that as the "angle of contact" and then pass that into the event.  The event is then handled by the motion handler, using the equation
    -180 + (point of contact - heading angle). It does work proerly when it bounces, the problem is that is almost always jitters and throws off the bounce.  The few times it hits the object and redirects away without any overlap,
    thus causing no extra collisions, it does reflect at the proper angle for both the home base and the robot.

    Deplete robot battery as it moves:
    FOr each timestep in the robot, I calculate this distance traveled from the old timestep to the new timestep.  I then multiply this distance by
    an arbitrary constant .01, and call the Deplete functino which depletes the battery, first checking to make sure the battery is not zero. It will not deplete the battery below zero.

    Recharge battery when robot collides with recharge station:
    There is already a function in arena.cc that checks to see if they have collided, so in that function, if they have, I call the robot battery's recharge function.
    This recharge funciton sets the battery charge to max_charge, which is set to 100.

    HomeBase Mobile:  Home base is now defined as an arena_mobile_entity, and it's params inherit from mobile_entity_params.  It has it's own motionhandler and motionbehavior classes, which have both .cc and .h files.
    I basically made it into a robot that does not take commands and does not have a bettery. That said, it still has an eventRecharge function that is defined by blank brackets like this {}.  THis was necessary because
    if it did not have that function, it was considered an abstract class and could not be insstantiated.
    Priority Level 2:

    Implement functionality for pause and restart buttons:
    The pause button worked in the base code, so all we had to do was the restart. The restart capability does the following:  The speed, position, battery, and heading_angle of
    the robot is set to it's original values.  Private vars had to be added to store these values, and the Reset function itself calls the appropriate getters with the proper vals.




    Implement functionality for win and lose.
    I believe very strongly in "Keep it simple, stupid."  All I modified for this wwas before the Assert(0) call, I print "YOU WIN" or "YOU LOSE" messages to the terminal,
    ad the program exits.  If I wanted it to be more robust I would give them the oppurtunity to restart the game, because my current implementation requires restart from the terminal once it
    has been won or lost.
    Fix bounce behavior off of left and right walls (it should reflect at angle of incidence.)
    The left and right walls were easier then the obstsables because they are not round, and they are not moving, which means that, with my implementation, I can treat the angle of contact
    as zero because the heading angle is equal to the angle of contact, so all I need to do is change the heading by 180 - the heading angle, which is already done in my motion handler for both the robot and the homebase.
    THe left and right walls are the least jiterry, but they still have issues, especially for the home base.  That said, when it bounces without jittering, the angles are correct.

    Visualize battery level (can be through GUI or something on the robot)
    I did something different with this that I thought was more fun:  The robot is green if it's battery level is above 65, yellow if between 65 and 30, and red below.  I checked the battery levels on the robot
    every timestep in robot.cc. and reset the color paramters every time.  I get this is iniefficient but I felt this was the most robust way to do it.
    Replace all nanogui::Color types in Arena to separate graphics from robots. Devise a system that will convert Arena color to nanogui color:
    Sam The Man did this for us, we just had to use the Meld tool on his changes.

Priority Level 3

    Limit the working dimensions inside which the robots can move (so GUI is not in arena):
    Shana said we didnt have to use this one.
    Create a Sensor base class and make SensorTouch a subclass.
    THis I did very lamely:  I made a sensor class with no members or vars and just changed the sensortouch inhereit from it, there were no actual changes to the code itself.
    Deplete battery when robot bumps into obstacles.
    I checked in the CheckForEntityCollision function in arena.cc for the entity collisions to see if ent1 was the robot and ent2 was the obstacle.  Note this is inthe section where we already know they have collided.  IF the were, I decremented both the speed and the battery
    of the robot, the robot speed by %10 and the battery by 3.  NOte that this makes it die when it jitters because it losees battery every timestep that is registers the collision.
    Slow the robot down when it bumps into obstacles:
    See above.
    Home base randomly changes direction at random times.
    THe Home base only needs positon and heading angle reset, because it's speed is never changed.
    The random time interval is handled by an int stored that is set to rand()%200.  THis is not as safe as rand_r(), but I coudlnt get rand_r() to compile and I did run the unittests with rand and nothing exploded, nobody died so I called it good.
    It is decremented once every time step, and if it is zero, this triggers the call to the reset function, and the value is reassigned to a new random value using rand(). It changes heading angle by some number between 1 and 50,
    all you do is put 50 as the mod to rand if you want it between 1 and 50.
    Create a total of 5 obstacles in the environment.
    I just changed the n_obstacles variable in main.cc and then made 5 new obstacles, see lines 53-75 in main.cc.  THis is fairly straightforward you just make them at whatver positions you choose.


 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */
#endif  // PROJECT_ITERATION1_SRC_MAINPAGE_H_
