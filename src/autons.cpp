#include "vex.h"
#include "cmath"


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
  chassis.set_heading_constants(12, 0.37, 0.5, 1, 0); //controls drive to pose
  chassis.set_turn_constants(12, .4, 0.02, 3.25, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(0.5, 300, 1200);

  chassis.set_turn_exit_conditions(0.5, 300, 800);
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
  chassis.heading_max_voltage = 5;
  chassis.drive_max_voltage = 12;
  chassis.drive_settle_error = 1;
  chassis.boomerang_lead = 0.1;
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
intake.setVelocity(100,percent);
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
  intake.stop();
  lift.spinTo(-400,deg,true);
  chill(1);
  lift.spinTo(0,deg,true);

}


 if (Optical.hue() <= 20 || Optical.hue() >= 320) {
  lift.spinTo(-140,deg,true);
  intake.setVelocity(20,percent);
  chill(430);
  intake.stop();
lift.spinTo(-800,deg,true);
chill(1);
lift.spinTo(0,deg,true);
 }

}
 };

void testDrive() {
  //vex::task::skibidiMcgee(opticalDetect);

  odom_constants();
  intake.setVelocity(100, percent);
  chassis.set_coordinates(0,0,0);
  //setback is just offset
  //chain with voltage 4w
  intakeLift.set(true);
  chassis.drive_max_voltage = 12;
  chassis.drive_min_voltage = 9;
  chassis.drive_distance(40);
  chassis.drive_stop(coast);

 
  //waitUntil(intake.spin)
  //test using drive_stop after movements

}


/**
 * @brief scores 6 rings and prepares to rush opposite corner
 */

 //altered
void red_minus_elims_rush() {
  odom_constants();
  intake.setVelocity(85,percent);
  chassis.set_coordinates(-51,24,-90);
  chassis.drive_timeout = 800;
  chassis.drive_to_point(-31,24);
  default_constants();
  chill(200);
  grab.set(true);
  chill(50);
  conveyor.spin(fwd);
  intakeLift.set(true);
  intake.spin(reverse);
  chassis.drive_to_point(-24,24);
  chassis.drive_min_voltage = 4;
  chassis.turn_timeout = 800;
  chassis.turn_to_angle(-0);
  default_constants();
  chassis.drive_distance(20);

  //ring pile
  chassis.drive_min_voltage = 3;
  chassis.turn_timeout = 600;
  chassis.turn_to_angle(-270, chassis.turn_max_voltage );
  chassis.drive_distance(15);
  chassis.drive_distance(-13, -305, 12, 4, chassis.drive_settle_error, chassis.drive_settle_time, 700);
  chill(100);
  chassis.drive_distance(15.5,-309);
  chassis.drive_timeout = 700;
  chassis.drive_distance(-10);
  intakeLift.set(false);
  chassis.drive_timeout = 1500;
  chassis.drive_distance(-35,-170,12,8);
  chassis.drive_stop(hold);
  chassis.drive_timeout = 1000;
  intake.stop();
  chassis.drive_max_voltage = 10;
  chassis.drive_distance(38.5,-175);
  chassis.drive_stop(hold);
  conveyor.stop();
  intakeLift.set(true);
  wait(0.2,sec);
  //intake.spin(reverse);
  chill(1400);
  chassis.turn_timeout = 400;
  chassis.turn_to_angle(-135);
  chassis.drive_timeout = 600;
  chassis.drive_distance(-23);
  chassis.turn_to_angle(-45);
  chassis.drive_max_voltage = 12;
  chassis.drive_min_voltage = 12;
  chassis.drive_distance(-20);
  chassis.drive_stop(hold);


}


void red_pos_goal_rush() {
  odom_constants();
  intake.setVelocity(100,percent);
  conveyor.setVelocity(85,percent);
  chassis.set_coordinates(14,8,252);

  //goal rush
  chassis.drive_timeout = 1100;
  chassis.drive_distance(-46.5);
  grab.set(true);
  chassis.turn_timeout = 300;
  chassis.turn_to_angle(270);
  chassis.drive_timeout = 700;
  chassis.drive_distance(33);
  grab.set(false);
  chassis.drive_min_voltage = 3;
  chassis.drive_distance(10);

  //goal 2
  chassis.turn_timeout = 600;
  chassis.turn_to_angle(210);
  chassis.drive_distance(-27);
  chill(200);
  grab.set(true);
  conveyor.spin(fwd);
  chill(300);

  //ring
  chassis.turn_to_angle(310);
  conveyor.stop();
  chassis.drive_min_voltage = 0;
  chassis.drive_timeout = 800;
  chassis.drive_distance(25);
  chassis.drive_stop(coast);
  intakeLift.set(true);
  chill(200);
  intake.spin(reverse);
  conveyor.spin(fwd);
  chill(1400);

  ///ladder
  chassis.drive_distance(-20);
  chassis.turn_to_angle(0);
  chassis.drive_distance(13);

}

void blue_minus_elims_rush() {
  // note for drive to pose
  // faster voltage equals more linear path
  // perhaps tune heading pid
  odom_constants();
  intake.setVelocity(75,percent);
  chassis.set_coordinates(51,24,90);
  chassis.drive_timeout = 800;
  chassis.drive_to_point(31,24);
  default_constants();
  chill(200);
  grab.set(true);
  chill(50);
  intakeLift.set(true);
  intake.spin(reverse);
  conveyor.spin(fwd);
  chassis.drive_to_point(24,24);
  chassis.drive_min_voltage = 4;
  chassis.turn_timeout = 800;
  chassis.turn_to_angle(0);
  default_constants();
  chassis.drive_distance(20);

  //ring pile
  chassis.drive_min_voltage = 3;
  chassis.turn_timeout = 600;
  chassis.turn_to_angle(270, chassis.turn_max_voltage );
  chassis.drive_distance(15);
  chassis.drive_distance(-13, 305, 12, 4, chassis.drive_settle_error, chassis.drive_settle_time, 700);
  chill(100);
  //chassis.drive_distance(15.5,309);
  chassis.drive_distance(15.5,309);
  chassis.drive_timeout = 700;
  chassis.drive_distance(-10);
  intakeLift.set(false);
  chassis.drive_timeout = 1500;
  chassis.drive_distance(-35,170,12,8);
  chassis.drive_timeout = 1000;
  intake.stop();
  chassis.drive_max_voltage = 10;
  chassis.drive_distance(35,175);
  chassis.drive_stop(hold);
  conveyor.stop();
  intakeLift.set(true);
  wait(0.2,sec);
  intake.spin(reverse);
  chill(1200);
  chassis.turn_timeout = 400;
  chassis.turn_to_angle(135);
  chassis.drive_timeout = 600;
  chassis.drive_distance(-23);
  chassis.turn_to_angle(45);
  chassis.drive_max_voltage = 12;
  chassis.drive_min_voltage = 12;
  chassis.drive_distance(-20);
  chassis.drive_stop(hold);

}

void blue_pos_goal_rush() {
  odom_constants();
  intake.setVelocity(75,percent);
  chassis.set_coordinates(-14,8,-252);

  //goal rush
  chassis.drive_timeout = 1100;
  chassis.drive_distance(-46.5);
  grab.set(true);
  chassis.turn_timeout = 300;
  chassis.turn_to_angle(-270);
  chassis.drive_timeout = 700;
  chassis.drive_distance(33);
  grab.set(false);
  chassis.drive_min_voltage = 3;
  chassis.drive_distance(10);

  //goal 2
  chassis.turn_timeout = 600;
  chassis.turn_to_angle(-210);
  chassis.drive_distance(-27);
  chill(200);
  grab.set(true);
  conveyor.spin(fwd);
  intake.spin(reverse);
  chill(300);

  //ring
  chassis.turn_to_angle(-310);
  intake.stop();
  chassis.drive_min_voltage = 0;
  chassis.drive_timeout = 800;
  chassis.drive_distance(25);
  chassis.drive_stop(coast);
  intakeLift.set(true);
  chill(200);
  conveyor.spin(fwd);
  intake.spin(reverse);
  chill(1400);

  ///ladder
  chassis.drive_distance(-20);
  chassis.turn_to_angle(0);
  chassis.drive_distance(13);

}