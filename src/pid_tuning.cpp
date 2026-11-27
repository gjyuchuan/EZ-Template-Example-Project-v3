#include "main.h"
#include "subsystems.hpp"

// =========================================================
// STEP 1: ADJUST THESE NUMBERS TO TUNE THE ROBOT
// =========================================================
void default_constants() {
  // ---------------------------------------------------------
  // 1. TURN CONSTANTS (Tune this first!)
  // Format: (kP, kI, kD)
  //   - kP (1st number) = GAS PEDAL: How hard the robot pushes to reach the angle.
  //   - kI (2nd number) = EXTRA PUSH: Leave at 0! (Not needed for basic tuning).
  //   - kD (3rd number) = BRAKES: Slows the robot down right before the target so it doesn't overshoot.
  //
  // HOW TO TUNE TURN:
  //   1. Start with kD = 0 -> example: (6, 0, 0)
  //   2. Run Test A (90_deg). Increase kP (+1 or +2) until the robot turns fast and goes JUST slightly past 90 degrees.
  //   3. Keep that kP, then increase kD (+5 or +10) until the overshoot disappears and it stops dead on 90 degrees.
  //   4. If the robot shakes/vibrates at the end, kD is too high -> lower kD by 5.
  // 
  // NOTE:  If you want to start with the values our auton code uses today, overwrite this function from:  src/autons.cpp at line 364.
  // ---------------------------------------------------------
  chassis.pid_turn_constants_set(6, 0, 20);

  // ---------------------------------------------------------
  // 2. DRIVE CONSTANTS (Tune this second!)
  // Format: (kP, kI, kD)
  //   - kP (1st number) = GAS PEDAL: How hard the robot drives toward the target distance.
  //   - kI (2nd number) = EXTRA PUSH: Leave at 0!
  //   - kD (3rd number) = BRAKES: Stops the robot cleanly on the target distance without bouncing.
  //
  // HOW TO TUNE DRIVE:
  //   1. Start with kD = 0 -> example: (13, 0, 0)
  //   2. Run Test B (24_in = 1 field tile). Increase kP (+2 or +3) until the robot drives briskly and goes ~1-2 inches past the seam.
  //   3. Keep that kP, then increase kD (+15 or +20) until it stops right on the 24-inch tile seam without bouncing.
  //   4. If the robot shutters/vibrates when stopping, kD is too high -> lower kD by 10.
  // ---------------------------------------------------------
  chassis.pid_drive_constants_set(13, 0, 100);

  // ---------------------------------------------------------
  // LEAVE THESE ALONE FOR NOW (Advanced / Secondary Settings)
  // ---------------------------------------------------------
  // Heading: Keeps the robot driving straight during Drive moves (kP, kI, kD)
  chassis.pid_heading_constants_set(3, 0, 20);
  
  // Swing: Used for 1-wheel arc turns (kP, kI, kD)
  chassis.pid_swing_constants_set(8, 0, 30);

  // Exit Conditions: Tells the robot when it is "close enough" to move on to the next line of code
  // Format: (small_time, small_error, big_time, big_error, velocity_time, timeout)
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  // Slew Rate: Prevents wheels from spinning out at the start of a drive
  // Format: (distance_to_ramp_up, starting_speed_out_of_127)
  chassis.slew_drive_constants_set(7_in, 80);
}

// =========================================================
// STEP 2: RUN THIS TEST AUTON ON THE FIELD TILES
// =========================================================
void pid_tuning_test() {
  // --- TEST A: 90-DEGREE TURN ---
  // Line the robot up along a tile seam. It should turn 90 degrees and land square on the cross seam.
  // Format: (target_angle, max_speed_out_of_127)
  chassis.pid_turn_set(90_deg, 80);
  chassis.pid_wait(); // Waits until the turn is completely finished

  // --- TEST B: 1-TILE DRIVE (24 INCHES) ---
  // Put "//" in front of the 2 lines above, and remove "//" from the 2 lines below to test driving.
  // Line the front wheels on a tile seam. One full VEX tile = 24 inches.
  // Format: (target_distance, max_speed_out_of_127)
  // chassis.pid_drive_set(24_in, 80);
  // chassis.pid_wait(); // Waits until the drive is completely finished
}
