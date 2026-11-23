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

void lRight(){
  pros::Task([]{
    move_claw_b(ClawBAction::Close);
    spin.move(127); //spins the spin motor to get ready to spin the toggle
    toggle.move(127);
    pros::delay(1100);
    toggle.move(0);
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(110); //lifts the dr4b  
    pros::delay(300);
    lift.move(0);
    return 0;
  });
  
  pros::delay(1000);
  spin.move(0);
  chassis.pid_swing_set(ez::e_swing::LEFT_SWING, 62_deg, 100, 0, false);
  chassis.pid_wait();
  chassis.pid_drive_set(16, 80, false, true);
  chassis.pid_wait();
  pros::delay(150);
  pros::Task([]{
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(-70); //lowers the dr4b  
    pros::delay(500);
    lift.move(0);
    pros::delay(100);
    spin.move(-20);
    move_claw_b(ClawBAction::AutonRelease);
    return 0;
  });
  pros::delay(300);
  chassis.pid_turn_set(70, 80, false);
  chassis.pid_wait();
  chassis.pid_drive_set(-15, 100, false, true);
  chassis.pid_wait();
}

void lLeft(){
  pros::Task([]{
    move_claw_b(ClawBAction::Close);
    spin.move(127); //spins the spin motor to get ready to spin the toggle
    toggle.move(127);
    pros::delay(1100);
    toggle.move(0);
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(110); //lifts the dr4b  
    pros::delay(300);
    lift.move(0);
    return 0;
  });
  
  pros::delay(1000);
  spin.move(0);
  chassis.pid_swing_set(ez::e_swing::RIGHT_SWING, -62_deg, 100, 0, false);
  chassis.pid_wait();
  chassis.pid_drive_set(16, 80, false, true);
  chassis.pid_wait();
  pros::delay(150);
  pros::Task([]{
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(-70); //lifts the dr4b  
    pros::delay(500);
    lift.move(0);
    pros::delay(100);
    spin.move(-20);
    move_claw_b(ClawBAction::AutonRelease);
    return 0;
  });
  pros::delay(300);
  chassis.pid_turn_set(-70, 80, false);
  chassis.pid_wait();
  chassis.pid_drive_set(-15, 100, false, true);
  chassis.pid_wait();
}

void hRight(){
  pros::Task([]{
    move_claw_b(ClawBAction::Close);
    spin.move(127); //spins the spin motor to get ready to spin the toggle
    toggle.move(127);
    pros::delay(1100);
    toggle.move(0);
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(110); //lifts the dr4b  
    pros::delay(400);
    lift.move(0);
    return 0;
  });
  
  pros::delay(1000);
  spin.move(0);
  chassis.pid_swing_set(ez::e_swing::RIGHT_SWING, -62_deg, 100, 0, false);
  chassis.pid_wait();
  chassis.pid_drive_set(16, 80, false, true);
  chassis.pid_wait();
  pros::delay(150);
  pros::Task([]{
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(-70); //lifts the dr4b  
    pros::delay(500);
    lift.move(0);
    pros::delay(100);
    spin.move(-20);
    move_claw_b(ClawBAction::AutonRelease);
    return 0;
  });
  pros::delay(300);
  chassis.pid_turn_set(-70, 80, false);
  chassis.pid_wait();
  chassis.pid_drive_set(-15, 100, false, true);
  chassis.pid_wait();
}
void hLeft(){
  pros::Task([]{
    move_claw_b(ClawBAction::Close);
    spin.move(127); //spins the spin motor to get ready to spin the toggle
    toggle.move(127);
    pros::delay(1100);
    toggle.move(0);
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(110); //lifts the dr4b  
    pros::delay(400);
    lift.move(0);
    return 0;
  });
  
  pros::delay(1000);
  spin.move(0);
  chassis.pid_swing_set(ez::e_swing::RIGHT_SWING, -62_deg, 100, 0, false);
  chassis.pid_wait();
  chassis.pid_drive_set(16, 80, false, true);
  chassis.pid_wait();
  pros::delay(150);
  pros::Task([]{
    lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(-70); //lifts the dr4b  
    pros::delay(500);
    lift.move(0);
    pros::delay(100);
    spin.move(-20);
    move_claw_b(ClawBAction::AutonRelease);
    return 0;
  });
  pros::delay(300);
  chassis.pid_turn_set(-70, 80, false);
  chassis.pid_wait();
  chassis.pid_drive_set(-15, 100, false, true);
  chassis.pid_wait();
  // chassis.pid_drive_set(-2, 20, false, true);
  // chassis.pid_wait();
  
  // pros::delay(100);
  // chassis.pid_drive_set(-8, 100, false, true);
  // chassis.pid_wait();
   //stops motor from continously running
  // chassis.pid_drive_set(-4, 100, false, true); //moves back at the start
  // chassis.pid_wait();
  // chassis.pid_turn_set(0_deg, 127);
  // chassis.pid_wait();
  //  //stops dr4b from continously running
  // chassis.pid_drive_set(18, 80, false, true);// moves robot forward
  // chassis.pid_wait(); //waits for previous line of code to finish before continuing
  // chassis.pid_turn_set(90_deg, 127, false); //turns to the right 88 degrees 
  // chassis.pid_wait(); 
  // chassis.pid_drive_set(17, 127, false, true);  //moves to pin holder
  // chassis.pid_wait();
  // chassis.pid_turn_set(90_deg, 127, false); //turns to the right 88 degrees 
  // chassis.pid_wait(); 
  // lift.move(-64);
  // pros::delay(300);
  // lift.move(0);
  // spin.move(-32);
  // chassis.pid_drive_set(-10, 50, true); //backs up to get out of the way of the pin holder
  // chassis.pid_wait_until(9);
  // chassis.pid_wait();

}
///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(13, 0, 100);
  chassis.pid_turn_constants_set(6, 0, 20);
  chassis.pid_swing_constants_set(8, 0, 30);

  chassis.pid_turn_exit_condition_set(100_ms, 3_deg, 200_ms, 7_deg, 300_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(30_ms, 1_in, 50_ms, 3_in, 100_ms, 500_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}

