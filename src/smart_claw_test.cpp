#include "main.h"
#include "subsystems.hpp"

// =========================================================
// SMART CLAW AUTON TEST (Tests Distance Sensor Pin Pickup)
// =========================================================
// Setup: Place a Pin ~8 to 10 inches straight in front of the robot.
// The robot will drive forward slowly, spot the Pin with its distance
// sensors, stop immediately, and clamp it!
// =========================================================

// Change this number (in millimeters) to match what you measured in Step 1!
const int GRAB_DISTANCE_MM = 55;

// Helper function: Returns true while the robot is still driving
bool chassis_is_driving() {
  return chassis.drive_mode_get() != ez::DISABLE && !chassis.interfered;
}

void smart_claw_test() {
  // 1. Open claw and start spinning flex wheels to pull the Pin in
  clawB.move(32);
  spin.move(40);

  // 2. Drive forward slowly (up to 14 inches max safety limit)
  chassis.pid_drive_set(14_in, 35);

  // 3. Keep driving UNTIL either sensor sees the Pin (< 55 mm) OR the drive finishes
  while (distLeft.get() > GRAB_DISTANCE_MM && distRight.get() > GRAB_DISTANCE_MM && chassis_is_driving()) {
    pros::delay(10);
  }

  // 4. Stop driving immediately and clamp the Pin!
  chassis.drive_set(0, 0);
  clawB.move(-64);
  pros::delay(250); // Brief pause so the claw grips tightly
  spin.move(0);     // Stop the spin motor

  // 5. Lift slightly to verify the Pin is securely held!
  lift.move(80);
  pros::delay(300);
  lift.move(0);
}
