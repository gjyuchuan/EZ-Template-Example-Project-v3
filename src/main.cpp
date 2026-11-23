#include "main.h"
#include "subsystems.hpp"

#include <atomic>

namespace {
pros::Motor clawB(15, pros::MotorGears::blue, pros::MotorUnits::degrees);
std::atomic<int> clawB_request{0};
constexpr std::uint32_t clawB_open_pulse_ms = 250;
constexpr std::uint32_t clawB_close_pulse_ms = 300;

void run_claw_b() {
  bool moving = false;
  bool closing = false;
  bool holding = false;
  std::uint32_t started_at = 0;
  while (true) {
    const int power = clawB_request.exchange(0);
    const auto now = pros::millis();
    if (pros::competition::is_disabled()) {
      if (moving || holding) {
        clawB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        clawB.brake();
        moving = false;
        holding = false;
      }
    } else if (power != 0) {
      clawB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      clawB.move(power);
      started_at = now;
      closing = power == static_cast<int>(ClawBAction::Close);
      moving = true;
      holding = false;
    } else if (moving && now - started_at >=
                             (closing ? clawB_close_pulse_ms : clawB_open_pulse_ms)) {
      if (closing) {
        clawB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      }
      clawB.brake();
      moving = false;
      holding = closing;
    }
    pros::delay(10);
  }
}
}  // namespace

void move_claw_b(ClawBAction action) {
  clawB_request.store(static_cast<int>(action));
}

void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  clawB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  static pros::Task clawB_task(run_claw_b);

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0); // Sets the active brake kP. We recommend 2.
  chassis.opcontrol_curve_default_set(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU

  ez::as::auton_selector.autons_add({
    Auton("lRight", lRight),
    Auton("lLeft", lLeft),
    Auton("hRight", hRight),
    Auton("quadrentTop", hLeft),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call(); // Calls selected auton from autonomous selector
  
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
  bool kewinMode = true;
  bool claw_was_closed = false;
  bool claw_commanded = false;
  while (true) {

    //chassis.opcontrol_tank(); // Tank control
       chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE); // Flipped single arcade
    
    //lift
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      //up
      lift.move(96);
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      //down
      lift.move(-64);
    } else {
      lift.move(0);
    }

    //spin
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      spin.move(0);
    } else {
      spin.move(32);
    }
    
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      kewinMode = !kewinMode;
    }

    const bool claw_closed = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) != kewinMode;
    if (!claw_commanded || claw_closed != claw_was_closed) {
      move_claw_b(claw_closed ? ClawBAction::Close : ClawBAction::Open);
      claw_was_closed = claw_closed;
      claw_commanded = true;
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
      toggle.move(127);
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
      toggle.move(-127);
    } else {
      toggle.move(0);
    }

    //up a bit
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
      pros::delay(200);
      lift.move(64);
      pros::delay(300);
    }

    //auton
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
      autonomous();
      claw_commanded = false;
    }
    
    // double battery_level = pros::battery::get_capacity();
    // master.print(0, 0, "Batt: %d%%   ", (int)battery_level); 

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME

  }
}

