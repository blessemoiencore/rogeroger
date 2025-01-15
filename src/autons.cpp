#include "vex.h"
#include <cmath>
/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).

   //chassis.set_drive_constants(12, 0.525, 5, 1, 0);  works 48 in
   chassis.set_drive_constants(12, 0.6, 5, 3, 0); 
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, 0.02, 3.25, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(0.5, 300, 1500);

  chassis.set_turn_exit_conditions(0.5, 300, 1000);
  chassis.set_swing_exit_conditions(1, 300, 1500);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

inline void chill(int ms) {
  vex::task::sleep(ms);
}

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 12;
  chassis.drive_max_voltage = 12;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}


void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

 void OpticalTest() {
odom_constants();
inveyor.setVelocity(100,percent);
chassis.set_coordinates(0,0,0);
//ColorTest(Optical1.hue());
//Optical.setLight(ledState::on);
lift.spinTo(-140,deg,true);
//conveyor.spin(fwd);

//do this intead of a task
//works optical sensor just isnt registering in the code
while (true) {
 if (Optical.hue() > 230 && Optical.hue() < 240) {
  chill(200);
  inveyor.stop();
  lift.spinTo(-400,deg,true);
  chill(1);
  lift.spinTo(0,deg,true);
}


 if (Optical.hue() <= 20 || Optical.hue() >= 320) {
  lift.spinTo(-140,deg,true);
  inveyor.setVelocity(20,percent);
  chill(430);
  inveyor.stop();
lift.spinTo(-800,deg,true);
chill(1);
lift.spinTo(0,deg,true);
 }

}
 };

void testDrive() {
  //vex::task::skibidiMcgee(opticalDetect);

  odom_constants();
  inveyor.setVelocity(100, percent);
  chassis.set_coordinates(48,0,270);

  //try out "lead"; lower lead means less curve; high lead big curve
  //check for imu vibration
  //setback is just offset
  //chain with voltage 4w
  chassis.drive_timeout = 100000;
  chassis.drive_to_point(0,0);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(10, 20);
  Brain.Screen.print(chassis.get_absolute_heading());
  chill(2000000000);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(10, 20);
  Brain.Screen.print(chassis.get_absolute_heading());
  
 
  //waitUntil(intake.spin)

  //distance chaining?
  //test using drive_stop after movements
  //test brake button

}


/**
 * @brief scores 6 rings and prepares to rush opposite corner
 */

 
void red_minus_elims_rush() {
  odom_constants();
  inveyor.setVelocity(100,percent);
  //position robot as far away from line as possible
  chassis.set_coordinates(-60, 24, 270);

  //grabbing clamp
  chassis.drive_to_point(-37, 24);
  chassis.drive_stop(coast);
  chill(200);
  grab.set(true);
  inveyor.spin(fwd);

  //ring rush
  chassis.turn_to_angle(70);
  inveyor.stop();
  chill(200);
  chassis.drive_to_pose(-8, 33, 0, 0.7); //adjust
  chassis.drive_stop(coast);
  inveyor.spin(fwd);
  chill(1);
  chassis.drive_to_point(-8, 56, 0, 5, chassis.heading_max_voltage);
  chassis.drive_stop(coast);

  //center ring
  chassis.turn_to_angle(240);
  chassis.drive_to_point(-15, 52);
  chassis.drive_stop(coast);
  chill(200);

  //corner ring
  chassis.drive_to_pose(-57, 57, 315, 0.5);
  chassis.drive_stop(coast);


  //use swing to angle here to move blue ring 
  //score alliance
  chassis.turn_to_angle(180);
  chill(200);
  grab.set(false);
  chassis.drive_to_pose(-60, 12.5, 180);
  chassis.drive_stop(coast);
  intakeLift.set(true);
  chassis.turn_to_angle(135);
  chill(200);
  chassis.drive_to_point(-57, 10);
  chassis.drive_stop(coast);
  intakeLift.set(false);
  inveyor.spinFor(fwd,1,sec);
  chassis.drive_to_point(-47, 0);
  chassis.drive_stop(coast);
  chassis.turn_to_angle(270);
  chassis.drive_to_point(-57, 0);
  chassis.drive_stop(coast);
  inveyor.spin(fwd);

  //ladder and rush
  chassis.turn_to_angle(45);
  inveyor.setVelocity(40, percent);
  chassis.drive_to_pose(-16, 16, 135, .9);
  chassis.drive_stop(coast);
  chill(2000);

}


void red_pos_goal_rush() {
  odom_constants();
  inveyor.setVelocity(100,percent);
  chassis.set_coordinates(-57,-60,90);
  intakeLift.set(true);
}