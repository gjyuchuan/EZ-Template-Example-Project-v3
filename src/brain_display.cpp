#include "brain_display.hpp"

#include "brain_telemetry.hpp"

#include "autons.hpp"
#include "pros/misc.hpp"

namespace {
  // The happy touchscreen updates this while the autonomous task can read it.
  std::atomic<int> sidePos{1}; // 0 = Left, 1 = Right.
  std::atomic<int> selectedPins{0}; // 0 = Low, 1 = High. 
  std::atomic<int> pinP{1};
  std::atomic<int> pinA0{1};
  std::atomic<int> pinA1{1};
  std::atomic<int> pinA2{1};
  std::atomic<int> pinA3{1};
  std::atomic<int> pinA4{1};
  std::atomic<int> pinA5{1};
  std::atomic<int> pinB5{1};
  std::atomic<int> pinC5{1};
  std::atomic<int> pinD5{1};
}

namespace brain_display {
  void brainDisplay(lv_obj_t *screen) {
    // rectangle(length, width, border_width, border_color, color, on_click, z, x, y)
    // text(label, size, color, on_click, z, x, y)
    // text(reader, size, color, on_click, z, x, y, auto_update)
    // slider(length, min, max, track_border_width, track_border_color, track_color, dot_border_width, dot_border_color, dot_color, assigned_variable, z, x, y)
    // button(min_amount, max_amount, length, width, border_width, border_color, color, set_var, z, x, y)
    rectangle(171, 42, 2, 0xFFFF00, 0x000000, &sidePos, 0, 6, 6);
    text("Left/Right", 24, 0xFFFFFF, &sidePos, 2, 20, 18);
    slider(36, 0, 1, 2, 0xFFFF00, 0x000000, 0, 0x000000, 0xFFFFFF, sidePos, 1, 122, 18);

    rectangle(171, 42, 2, 0xFFFF00, 0x000000, &selectedPins, 0, 182, 6);
    text("a1-2, c-d5", 24, 0xFFFFFF, &selectedPins, 2, 196, 18);
    slider(36, 0, 1, 2, 0xFFFF00, 0x000000, 0, 0x000000, 0xFFFFFF, selectedPins, 1, 300, 18);

    text([] {
      return "Battery: " + std::to_string(int(pros::battery::get_capacity())) + "%";
      }, 14, 0xFFFFFF, nullptr, 2, 360, 6, true);
    text([] {
      pros::Controller controller(pros::E_CONTROLLER_MASTER);
      const auto connection = controller.is_connected();
      const auto capacity = connection == 1 || connection == 2 ? controller.get_battery_capacity() : PROS_ERR;
      return capacity != PROS_ERR ? "Controller: " + std::to_string(capacity) + "%" : std::string("Controller: N/A");
    }, 14, 0xFFFFFF, nullptr, 2, 360, 20, true);
    text(read_connection_label, 12, 0xFFFFFF, nullptr, 2, 360, 34, true);
    text([] {
      return "Current: " + std::to_string(pros::battery::get_current() / 1000.0) + " A";
    }, 14, 0xFFFFFF, nullptr, 2, 6, 50, true);
    text([] {
      return "Voltage: " + std::to_string(pros::battery::get_voltage() / 1000.0) + " V";
    }, 14, 0xFFFFFF, nullptr, 2, 170, 50, true);
    text([] {
      return "Power: " + std::to_string((pros::battery::get_current() / 1000.0) * (pros::battery::get_voltage() / 1000.0)) + " W";
    }, 14, 0xFFFFFF, nullptr, 2, 340, 50, true);

    create_telemetry(screen);
  }

  void run_selected_auton() {
    const int side = sidePos.load() == 1 ? 1 : -1;
    pre(side, selectedPins.load()/2+1);
  }
}
