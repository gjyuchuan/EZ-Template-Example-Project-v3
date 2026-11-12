#include "main.h"
#include "subsystems.hpp"
/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

void new_auton(){
  //turn example
  chassis.pid_turn_set(90_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(270_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(0_deg, TURN_SPEED, true);
  chassis.pid_wait();
  //drive example

  //combine all 3 movements
}
///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(100_ms, 3_deg, 200_ms, 7_deg, 300_ms, 300_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(30_ms, 1_in, 50_ms, 3_in, 100_ms, 300_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}

