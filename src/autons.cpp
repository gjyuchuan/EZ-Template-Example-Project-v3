#include "main.h"
#include "subsystems.hpp"
/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const double driveSpeed = 1; 
const double clawSpeed = 1;
const double liftSpeed = 1;
const double spinSpeed = 1;
const double turnSpeed = 1;
const double swingSpeed = 1;
const double toggleSpeed = 1;
const double waitTime = 1;

void pre(int inversed, double higher){
  pros::Task([higher]{
    clawB.move(-64*clawSpeed); //holds pin at start
    spin.move(64*spinSpeed);  //spins the spin motor to hold the pin
    toggle.move(64*toggleSpeed); //spins the toggle
    pros::delay(600/toggleSpeed);
    toggle.move(0);
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD); //sets the dr4b to hold position
    lift.move(100*liftSpeed); //lifts the dr4b
    pros::delay(300/liftSpeed*higher);
    lift.move(0);
    return 0;
  });

  pros::delay(800/waitTime);
  spin.move(0);
  chassis.pid_swing_set(ez::e_swing::LEFT_SWING, inversed*62_deg, 64*swingSpeed, 0, false); //swings to drive to pin holder
  chassis.pid_wait();
  chassis.pid_drive_set(16, 64*driveSpeed, false, true); //drives to pin holder
  chassis.pid_wait();
  pros::delay(150/waitTime);
  pros::Task([]{
    lift.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD); //sets the dr4b to hold position
    lift.move(-62*liftSpeed); //lowers the dr4b  
    pros::delay(300/liftSpeed);
    lift.move(0);
    pros::delay(200/waitTime);
    spin.move(-12*spinSpeed); //spins the spin motor to let go of the pin
    clawB.move(32*clawSpeed); //releases the pin
    pros::delay(400/waitTime);
    return 0;
  });
  //approach pin stop before it turn again to the right angle and then another drive to slow
  pros::delay(400/waitTime);

  chassis.pid_drive_set(-10, 32*driveSpeed, false, true); //backs up to get ready to turn to the other pin
  chassis.pid_turn_set(70, 36*turnSpeed*inversed, false); //idk
  chassis.pid_wait();
  pros::delay(400/waitTime);
  chassis.pid_drive_set(-5, 32*driveSpeed, false, true); //backs up to get ready to turn to the other pin
  spin.move(0); //stops spin motor from continously running
  chassis.pid_wait();
}


//in progress
void return_pre_B1(int inversed){
  chassis.pid_turn_set(-30, 36*turnSpeed*inversed, false); //turns to the right to drive to the other pin holder
  chassis.pid_wait();
  chassis.pid_turn_set(80, 48*driveSpeed*inversed, false); //drives to the other pin holder
  chassis.pid_wait();
}

void other(int inversed, double higher){  
  chassis.pid_wait();
  chassis.pid_turn_set(33, 64*turnSpeed*inversed, false); //turns to the right to get ready to drive to the other pin
  lift.move(-32*liftSpeed); //lowers the dr4b
  pros::delay(200/waitTime);
  lift.move(0);
  chassis.pid_wait();
  chassis.pid_drive_set(30, 64*driveSpeed, false, true); //drives to the other pin
  chassis.pid_wait();
  spin.move(32*spinSpeed); //spins the spin motor to get ready to hold the pin
  chassis.pid_drive_set(6, 15*driveSpeed, false, true); //drive to pin
  chassis.pid_wait();
  pros::delay(200/waitTime);
  clawB.move(-64*clawSpeed); //holds the pin
  pros::delay(600/waitTime);
  chassis.pid_drive_set(4, 32*driveSpeed, false, true); //drives a little extra to make sure the pin is held
  lift.move(64*liftSpeed); //lifts the dr4b
  pros::delay(500/waitTime);
  lift.move(0);
  pros::delay(400/waitTime);
  spin.move(0);
  chassis.pid_turn_set(165, 64*turnSpeed*inversed, false); //turns to the right to drive to the other pin holder
  chassis.pid_wait();
  chassis.pid_drive_set(31, 48*driveSpeed, false, true); //drives to the other pin holder
  lift.move(82*liftSpeed); //lifts the dr4b
  pros::delay(600/waitTime);
  lift.move(0);
  chassis.pid_wait();
  pros::delay(200/waitTime);
  lift.move(-64*liftSpeed); //lowers the dr4b
  pros::delay(400/waitTime);
  lift.move(0);
  clawB.move(32*clawSpeed); //releases the pin
  pros::delay(300/waitTime);
  chassis.pid_drive_set(-15, 48*driveSpeed, false, true); //backs up to get ready to turn to the other pin
  chassis.pid_wait();
  chassis.pid_turn_set(128, 36*turnSpeed*inversed, false); //turns to the right to get ready to drive to the other pin
  lift.move(-64*liftSpeed); //lowers the dr4b
  pros::delay(400/waitTime);
  lift.move(0);
  chassis.pid_wait();
  chassis.pid_drive_set(24, 48*driveSpeed, false, true); //drives close to pin
  chassis.pid_wait();
  spin.move(32*spinSpeed); //spins the spin motor to get ready to hold the pin
  chassis.pid_drive_set(13, 15*driveSpeed, false, true); //drive to pin
  chassis.pid_wait();
  pros::delay(300/waitTime);
  clawB.move(64*clawSpeed); //holds the pin
  pros::delay(200/waitTime);
  chassis.pid_drive_set(2, 15*driveSpeed, false, true); //drives a little extra to make sure the pin is held
  lift.move(64*liftSpeed); //lifts the dr4b
  pros::delay(400/waitTime);
  spin.move(0); //stops spin motor from continously running
  pros::delay(400/waitTime);
  lift.move(0);
  chassis.pid_turn_set(-100, 64*turnSpeed*inversed, false); //turns to the right to drive to the other pin holder
  chassis.pid_wait();
  chassis.pid_drive_set(30, 64*driveSpeed, false, true); //drives to the other pin holder
  chassis.pid_wait();
}

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

