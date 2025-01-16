using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

// VEXcode devices
extern motor leftMotorA;
extern motor leftMotorB;
extern motor leftMotorC;
extern motor rightMotorA;
extern motor rightMotorB;
extern motor rightMotorC;
extern controller Controller1;
extern inertial DrivetrainInertial;
extern digital_out grab;
extern motor inveyor;
extern motor lift;
extern optical Optical;
extern potV2 Switcher;
extern rotation Rotation;

extern digital_out intakeLift; //pneumatics intake
extern digital_out doink;


void  vexcodeInit( void );