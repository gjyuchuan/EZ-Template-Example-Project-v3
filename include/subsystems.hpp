#include "main.h"


inline ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-2,-1}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{7,8}

  // IMU Port
  ,9

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,2.75

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,1.3333333
);

inline pros::Motor intake_motor(3, pros::MotorGears::blue, pros::MotorUnits::degrees);
inline pros::Motor toggle(16, pros::MotorGears::blue, pros::MotorUnits::degrees);
inline pros::Motor liftL(12, pros::MotorGears::blue, pros::MotorUnits::degrees);
inline pros::Motor liftR(-20, pros::MotorGears::blue, pros::MotorUnits::degrees);
inline pros::Motor clawL(18);
inline pros::Motor clawR(-17);
enum class ClawBAction {
  Close = -90,
  Open = 16,
  AutonRelease = 64,
};

void move_claw_b(ClawBAction action);
inline pros::Motor gps(-9, pros::MotorGears::blue, pros::MotorUnits::degrees);
// inline pros::Motor driveRF(8, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
// inline pros::Motor driveRB(7, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
// inline pros::Motor DriveLF(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
// inline pros::Motor driveLB(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

inline pros::MotorGroup lift({12, -20}, pros::MotorGears::blue, pros::MotorUnits::degrees);
inline pros::MotorGroup spin({18, -17});
// inline pros::Motor_Group drive({driveRF, driveRB, driveLf, driveLB})
