#include "vex.h"
#include <cmath>

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:

motor leftMotorA = motor(PORT3, ratio6_1, true);
motor leftMotorB = motor(PORT2, ratio6_1, true);
motor leftMotorC = motor(PORT10, ratio6_1,false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT13, ratio6_1, false);
motor rightMotorB = motor(PORT12, ratio6_1, true);
motor rightMotorC = motor(PORT19, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
inertial DrivetrainInertial = inertial(PORT17);
controller Controller1 = controller(primary);
motor intake = motor(PORT16, ratio18_1, true);
motor conveyor = motor(PORT20, ratio6_1);
motor lift = motor(PORT11,ratio18_1, false );
digital_out grab = digital_out(Brain.ThreeWirePort.A);
optical Optical = optical(PORT1);
potV2 Switcher = potV2(Brain.ThreeWirePort.B);
rotation Rotation = rotation(PORT14);

digital_out intakeLift = digital_out(Brain.ThreeWirePort.H); 
digital_out doink = digital_out(Brain.ThreeWirePort.C);



//try without pid
double tolerance = 2;
void move_lift(float angle) {
  Rotation.setPosition(0,deg);
  while ((fabs(angle - Rotation.angle(degrees)) > tolerance)) {
    /*
    float kp = 0.2;
    float error = angle - Rotation.angle(degrees);
    float voltage = kp * error;
    voltage = clamp(voltage, -12, 12); //multiply by -1?????
    */
    lift.spin(fwd, 2, volt); //try changing rvs or fwd in the motor declaration
    vex::task::sleep(100000000);
  }
  lift.stop(hold);

  
}


void vexcodeInit( void ) {
  // nothing to initialize
}