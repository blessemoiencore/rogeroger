#include "vex.h"
#include <cmath>

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(),

//Right Motors:
motor_group(),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT1,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.6,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;
bool optical_auton_on = true;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void opticalDetect() 
{
  while(optical_auton_on) 
  {
      if (Optical.hue() > 10 && Optical.hue() < 20) 
      {
        task::sleep(160);
          inveyor.stop();
          lift.spinTo(-700,deg,true);
          task::sleep(1000);
          lift.spinTo(-140,deg,true);
      }
      task::sleep(20);
  }
};

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  while(!auto_started){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
    Brain.Screen.printAt(5, 40, "Battery Percentage:");
    Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
    Brain.Screen.printAt(5, 80, "Chassis Heading Reading:");
    Brain.Screen.printAt(5, 100, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 120, "Selected Auton:");

    double angle = Switcher.angle(degrees);
    Brain.Screen.setCursor(15, 20);
    Brain.Screen.print(angle);

    int total_autons = 5;
    double deg_per_auton = 359/total_autons;
    if(Switcher.angle(degrees) < deg_per_auton) {
      current_auton_selection = 0;
    }
    else if (Switcher.angle(degrees) < 2 * deg_per_auton) {
      current_auton_selection = 1;
    }
    else if (Switcher.angle(degrees) < 3 * deg_per_auton) {
      current_auton_selection = 2;
    }
    else if (Switcher.angle(degrees) < 4 * deg_per_auton) {
      current_auton_selection = 3;
    }
    else if (Switcher.angle(degrees) < 5 * deg_per_auton) {
      current_auton_selection = 4;
    }

    switch(current_auton_selection){
      case 0:
         Brain.Screen.printAt(5, 140, "test drive");
         break;
      case 1:
         Brain.Screen.printAt(5, 140, "odom_test");
         break;
      case 2:
         Brain.Screen.printAt(5, 140, "optical test");
         break;
      case 3:
          Brain.Screen.printAt(5, 140, "red minus ring rush for elims");
          break;
      case 4: 
          Brain.Screen.printAt(5, 140, "red pos goal rush elims");
          break;       
    }
    task::sleep(10);
  }
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){ 
    case 0:         
      testDrive();
      break;
   
    case 1:
      odom_test();
      break;
   
    case 2:
      OpticalTest();
      break;

    case 3:
      red_minus_elims_rush();
      break;
    
    case 4:
      red_pos_goal_rush();
      break;
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {


  if(Controller1.ButtonR1.pressing()) {
      inveyor.spin(forward,100,percent);
    } else if(Controller1.ButtonR2.pressing()) {
      inveyor.spin(reverse,100,percent);
    } else {
      inveyor.stop();
    }

  //brake test
  if(Controller1.ButtonB.pressing()) {
    chassis.drive_stop(hold);
  }
    
  Controller1.ButtonLeft.pressed([] {
    lift.spinToPosition(-140, degrees);

  });

   Controller1.ButtonUp.pressed([] {
    lift.spinToPosition(-775, degrees);

  });

  Controller1.ButtonRight.pressed([] {
    lift.spinToPosition(-0, degrees);

  });

    Controller1.ButtonDown.pressed([] {
    lift.spinToPosition(-250, degrees);

  });
  

  Controller1.ButtonA.pressed([]{
  grab.set(!grab.value());
  });

    chassis.control_arcade();

    wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

  inveyor.setVelocity(100,percent);

  if(current_auton_selection == 6) {
  opticalDetect();
  }
  
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
