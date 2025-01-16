#include "vex.h"

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
motor inveyor = motor(PORT20, ratio6_1, true);
motor lift = motor(PORT1,ratio36_1, false );
digital_out grab = digital_out(Brain.ThreeWirePort.A);
optical Optical = optical(PORT1);
potV2 Switcher = potV2(Brain.ThreeWirePort.B);
rotation Rotation = rotation(PORT14);

digital_out intakeLift = digital_out(Brain.ThreeWirePort.H); //subject to change
digital_out doink = digital_out(Brain.ThreeWirePort.C);


void vexcodeInit( void ) {
  // nothing to initialize
}