#include "main.h"
#include "subsystems.hpp"
/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const double DRIVE_SPEED = 1; 
const double CLAW_SPEED = 1;
const double LIFT_SPEED = 1;
const double SPIN_SPEED = 1;
const double TURN_SPEED = 1;
const double SWING_SPEED = 1;
const double TOGGLE_SPEED = 1;
const double WAIT_TIME = 1;

void lRight(){
  pros::Task([]{
    clawB.move(-64*CLAW_SPEED); //holds pin at start
    spin.move(64*SPIN_SPEED);  //spins the spin motor to hold the pin
    toggle.move(64*TOGGLE_SPEED); //spins the toggle
    pros::delay(600/TOGGLE_SPEED);
    toggle.move(0);
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD); //sets the dr4b to hold position
    lift.move(100*LIFT_SPEED); //lifts the dr4b  
    pros::delay(300/LIFT_SPEED);
    lift.move(0); 
    return 0;
  });

  pros::delay(800/WAIT_TIME);
  spin.move(0);
  chassis.pid_swing_set(ez::e_swing::LEFT_SWING, 62_deg, 64*SWING_SPEED, 0, false); //swings to left to drive to pin holder
  chassis.pid_wait();
  chassis.pid_drive_set(16, 64*DRIVE_SPEED, false, true); //drives to pin holder
  chassis.pid_wait();
  pros::delay(150/WAIT_TIME);
  pros::Task([]{
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD); //sets the dr4b to hold position
    lift.move(-32*LIFT_SPEED); //lowers the dr4b  
    pros::delay(200/LIFT_SPEED);
    lift.move(0);
    pros::delay(200/WAIT_TIME);
    spin.move(-12*SPIN_SPEED); //spins the spin motor to let go of the pin
    clawB.move(32*CLAW_SPEED); //releases the pin
    pros::delay(400/WAIT_TIME);
    return 0;
  });

  // //approach pin stop before it turn again to the right angle and then another drive to slow
  // pros::delay(400/WAIT_TIME);

  // ///
  // chassis.pid_drive_set(-5, 32*DRIVE_SPEED, false, true); //backs up to get ready to turn to the other pin
  // chassis.pid_turn_set(70, 36*TURN_SPEED, false); //idk
  // chassis.pid_wait();
  // pros::delay(400/WAIT_TIME);
  // chassis.pid_drive_set(-10, 32*DRIVE_SPEED, false, true); //backs up to get ready to turn to the other pin
  // ///

  // chassis.pid_wait();
  // chassis.pid_turn_set(31, 64*TURN_SPEED, false); //turns to the right to get ready to drive to the other pin
  // lift.move(-32*LIFT_SPEED); //lowers the dr4b
  // pros::delay(200/WAIT_TIME);
  // lift.move(0);
  // chassis.pid_wait();
  // chassis.pid_drive_set(29, 64*DRIVE_SPEED, false, true); //drives to the other pin
  // chassis.pid_wait();
  // spin.move(32*SPIN_SPEED); //spins the spin motor to get ready to hold the pin
  // chassis.pid_drive_set(6, 15*DRIVE_SPEED, false, true); //drive to pin
  // chassis.pid_wait();
  // pros::delay(200/WAIT_TIME);
  // clawB.move(-64*CLAW_SPEED); //holds the pin
  // pros::delay(600/WAIT_TIME);
  // chassis.pid_drive_set(4, 32*DRIVE_SPEED, false, true); //drives a little extra to make sure the pin is held
  // lift.move(64*LIFT_SPEED); //lifts the dr4b
  // pros::delay(500/WAIT_TIME);
  // lift.move(0);
  // pros::delay(400/WAIT_TIME);
  // spin.move(0);
  // chassis.pid_turn_set(165, 64*TURN_SPEED, false); //turns to the right to drive to the other pin holder
  // chassis.pid_wait();
  // chassis.pid_drive_set(31, 48*DRIVE_SPEED, false, true); //drives to the other pin holder
  // lift.move(82*LIFT_SPEED); //lifts the dr4b 
  // pros::delay(600/WAIT_TIME);
  // lift.move(0);
  // chassis.pid_wait();
  // pros::delay(200/WAIT_TIME);
  // lift.move(-64*LIFT_SPEED); //lowers the dr4b
  // pros::delay(400/WAIT_TIME);
  // lift.move(0);
  // clawB.move(32*CLAW_SPEED); //releases the pin
  // pros::delay(300/WAIT_TIME);
  // chassis.pid_drive_set(-15, 48*DRIVE_SPEED, false, true); //backs up to get ready to turn to the other pin
  // chassis.pid_wait();
  // chassis.pid_turn_set(130, 36*TURN_SPEED, false); //turns to the right to get ready to drive to the other pin
  // lift.move(-64*LIFT_SPEED); //lowers the dr4b
  // pros::delay(400/WAIT_TIME);
  // lift.move(0);
  // chassis.pid_wait();
  // chassis.pid_drive_set(24, 48*DRIVE_SPEED, false, true); //drives close to pin
  // chassis.pid_wait();
  // spin.move(32*SPIN_SPEED); //spins the spin motor to get ready to hold the pin
  // chassis.pid_drive_set(13, 15*DRIVE_SPEED, false, true); //drive to pin
  // chassis.pid_wait();
  // pros::delay(300/WAIT_TIME);
  // clawB.move(64*CLAW_SPEED); //holds the pin
  // pros::delay(200/WAIT_TIME);
  // chassis.pid_drive_set(2, 15*DRIVE_SPEED, false, true); //drives a little extra to make sure the pin is held
  // lift.move(64*LIFT_SPEED); //lifts the dr4b
  // pros::delay(400/WAIT_TIME);
  // spin.move(0); //stops spin motor from continously running
  // pros::delay(400/WAIT_TIME);
  // lift.move(0);
  // chassis.pid_turn_set(-100, 64*TURN_SPEED, false); //turns to the right to drive to the other pin holder
  // chassis.pid_wait();
  // chassis.pid_drive_set(30, 64*DRIVE_SPEED, false, true); //drives to the other pin holder
  // chassis.pid_wait();
}

void lLeft(){
  //   pros::Task([]{
  //   clawB.move(-64*CLAW_SPEED); //holds pin at start
  //   spin.move(64*SPIN_SPEED);  //spins the spin motor to hold the pin
  //   toggle.move(64*TOGGLE_SPEED); //spins the toggle
  //   pros::delay(600/TOGGLE_SPEED);
  //   toggle.move(0);
  //   lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD); //sets the dr4b to hold position
  //   lift.move(100*LIFT_SPEED); //lifts the dr4b  
  //   pros::delay(300/LIFT_SPEED);
  //   lift.move(0); 
  //   return 0;
  // });
  // pros::delay(400/WAIT_TIME);
  // spin.move(0);
  // chassis.pid_swing_set(ez::e_swing::RIGHT_SWING, 62_deg, 64*SWING_SPEED, 0, false); //swings to right to drive to pin holder
  // chassis.pid_wait();
  // chassis.pid_drive_set(16, 64*DRIVE_SPEED, false, true); //drives to pin holder
  // chassis.pid_wait();
  // pros::delay(150/WAIT_TIME);
  // pros::Task([]{
  //   lift.move(-32*LIFT_SPEED); //lowers the dr4b  
  //   pros::delay(200/LIFT_SPEED);
  //   lift.move(0);
  //   pros::delay(200/WAIT_TIME);
  //   spin.move(-12*SPIN_SPEED); //spins the spin motor to let go of the pin
  //   clawB.move(32*CLAW_SPEED); //releases the pin
  //   pros::delay(400/WAIT_TIME);
  //   return 0;
  // });
  // //approach pin stop before it turn again to the right angle and then another drive to slow
  // pros::delay(400/WAIT_TIME);
  // chassis.pid_turn_set(-70, 36*TURN_SPEED, false); //idk
  // chassis.pid_wait();
  // pros::delay(400/WAIT_TIME);
  // chassis.pid_drive_set(-15, 32*DRIVE_SPEED, false, true); //backs up to get ready to turn to the other pin
  // chassis.pid_wait();
  // chassis.pid_turn_set(-33, 64*TURN_SPEED, false); //turns to the left to get ready to drive to the other pin
  // lift.move(-32*LIFT_SPEED); //lowers the dr4b
  // pros::delay(200/WAIT_TIME);
  // lift.move(0);
  // chassis.pid_wait();
  // chassis.pid_drive_set(30, 64*DRIVE_SPEED, false, true); //drives to the other pin
  // chassis.pid_wait();
  // spin.move(32*SPIN_SPEED); //spins the spin motor to get ready to hold the pin
  // chassis.pid_drive_set(6, 15*DRIVE_SPEED, false, true); //drive to pin
  // chassis.pid_wait();
  // pros::delay(200/WAIT_TIME);
  // clawB.move(-64*CLAW_SPEED); //holds the pin
  // pros::delay(600/WAIT_TIME);
  // chassis.pid_drive_set(4, 32*DRIVE_SPEED, false, true); //drives a little extra to make sure the pin is held
  // lift.move(64*LIFT_SPEED); //lifts the dr4b
  // pros::delay(500/WAIT_TIME);
  // lift.move(0);
  // pros::delay(400/WAIT_TIME);
  // spin.move(0);
  // chassis.pid_turn_set(-165, 64*TURN_SPEED, false); //turns to the right to drive to the other pin holder
  // chassis.pid_wait();
  // chassis.pid_drive_set(-31, 48*DRIVE_SPEED, false, true); //drives to the other pin holder
  // lift.move(82*LIFT_SPEED); //lifts the dr4b
  // pros::delay(600/WAIT_TIME);
  // lift.move(0);
  // chassis.pid_wait();
  // pros::delay(200/WAIT_TIME);
  // lift.move(-64*LIFT_SPEED); //lowers the dr4b
  // pros::delay(400/WAIT_TIME);
  // lift.move(0);
  // clawB.move(32*CLAW_SPEED); //releases the pin
  // pros::delay(300/WAIT_TIME);
  // chassis.pid_drive_set(-15, 48*DRIVE_SPEED, false, true); //backs up to get ready to turn to the other pin
  // chassis.pid_wait();
  // chassis.pid_turn_set(-128, 36*TURN_SPEED, false); //turns to the right to get ready to drive to the other pin
  // lift.move(-64*LIFT_SPEED); //lowers the dr4b
  // pros::delay(400/WAIT_TIME);
  // lift.move(0);
  // chassis.pid_wait();
  // chassis.pid_drive_set(24, 48*DRIVE_SPEED, false, true); //drives close to pin
  // chassis.pid_wait();
  // spin.move(32*SPIN_SPEED); //spins the spin motor to get ready to hold the pin
  // chassis.pid_drive_set(13, 15*DRIVE_SPEED, false, true); //drive to pin
  // chassis.pid_wait();
  // pros::delay(300/WAIT_TIME);
  // clawB.move(64*CLAW_SPEED); //holds the pin
  // pros::delay(200/WAIT_TIME);
  // chassis.pid_drive_set(2, 15*DRIVE_SPEED, false, true); //drives a little extra to make sure the pin is held
  // lift.move(64*LIFT_SPEED); //lifts the dr4b
  // pros::delay(400/WAIT_TIME);
  // spin.move(0); //stops spin motor from continously running
  // pros::delay(400/WAIT_TIME);
  // lift.move(0);
  // chassis.pid_turn_set(100, 64*TURN_SPEED, false); //turns to the right to drive to the other pin holder
  // chassis.pid_wait();
  // chassis.pid_drive_set(30, 64*DRIVE_SPEED, false, true); //drives to the other pin holder
  // chassis.pid_wait();
  pros::Task([]{
    clawB.move(-64*CLAW_SPEED); //holds pin at start
    spin.move(127*SPIN_SPEED); //spins the spin motor to get ready to spin the toggle
    toggle.move(127*TOGGLE_SPEED);
    pros::delay(600/TOGGLE_SPEED);
    toggle.move(0);
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(127*LIFT_SPEED); //lifts the dr4b
    pros::delay(300/LIFT_SPEED);
    lift.move(0);
    pros::delay(400/WAIT_TIME);
    return 0;
  });
  pros::delay(500/WAIT_TIME);
  spin.move(0);
  chassis.pid_swing_set(ez::e_swing::RIGHT_SWING, -62_deg, 64*SWING_SPEED, 0, false);
  chassis.pid_wait();
  chassis.pid_drive_set(16, 64*DRIVE_SPEED, false, true);
  chassis.pid_wait();
  pros::delay(150/WAIT_TIME);
  pros::Task([]{
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(-64*LIFT_SPEED); //lifts the dr4b
    pros::delay(500/LIFT_SPEED);
    lift.move(0);
    pros::delay(100/WAIT_TIME);
    spin.move(-12*SPIN_SPEED);
    clawB.move(64*CLAW_SPEED);
    pros::delay(400/WAIT_TIME);
    return 0;
  });
  pros::delay(300/WAIT_TIME);
  chassis.pid_turn_set(-70, 36*TURN_SPEED, false);
  chassis.pid_wait();
  pros::delay(400/WAIT_TIME);
  chassis.pid_drive_set(-15, 48*DRIVE_SPEED, false, true);
  chassis.pid_wait();
}

void hRight(){
  pros::Task([]{
    clawB.move(-64*CLAW_SPEED); //holds pin at start
    spin.move(127*SPIN_SPEED); //spins the spin motor to get ready to spin the toggle
    toggle.move(127*TOGGLE_SPEED);
    pros::delay(1100/TOGGLE_SPEED);
    toggle.move(0);
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(127*LIFT_SPEED); //lifts the dr4b
    pros::delay(300/WAIT_TIME);
    lift.move(0);
    pros::delay(400/WAIT_TIME);
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
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(-70); //lifts the dr4b  
    pros::delay(500);
    lift.move(0);
    pros::delay(100);
    spin.move(-20);
    clawB.move(64);
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
    clawB.move(-64); //holds pin at start
    spin.move(127); //spins the spin motor to get ready to spin the toggle
    toggle.move(127);
    pros::delay(1100);
    toggle.move(0);
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
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
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    lift.move(-70); //lifts the dr4b  
    pros::delay(500);
    lift.move(0);
    pros::delay(100);
    spin.move(-20);
    clawB.move(64);
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
  // clawB.move(32); //releases pin
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

