#pragma once

#include <atomic>
#include <cstdint>
#include <optional>
#include <string>

#include "display/lvgl.h"

namespace brain_display {
  void initialize();
  void run_selected_auton();
  struct Diagnostics {
    std::optional<double> battery_percent;
    std::optional<int> controller_battery_percent;
    std::string connection = "Unavailable";
    std::string vexos_version;
    std::optional<std::string> radio_version;
    std::optional<std::string> radio;
    std::optional<std::string> controller_version;
    std::optional<std::string> controller_radio_version;
    std::optional<int> signal_dbm;
    std::optional<int> cable_errors;
    std::optional<double> current_amps;
    std::optional<double> power_watts;
  };

  Diagnostics read_diagnostics();

  // Length is horizontal and width is vertical. x and y place the top-left
  // corner in pixels. Colors use 0xRRGGBB.
  // Higher z layers are in front. On the same layer, later calls are in front.
  // Pass &assigned_variable to toggle a linked 0-to-1 slider on tap.
  lv_obj_t *rectangle(int length, int width, int border_width,
                      std::uint32_t border_color, std::uint32_t color,
                      std::atomic<int> *on_click, std::uint32_t z, int x, int y);

  // Each tap advances set_var from min_amount through max_amount, then wraps.
  // If the bounds are reversed, the button uses them in ascending order.
  // Keep set_var alive for as long as the button exists.
  lv_obj_t *button(int min_amount, int max_amount, int length, int width, int border_width,
                   std::uint32_t border_color, std::uint32_t color,
                   std::atomic<int> &set_var, std::uint32_t z, int x, int y);

  // The assigned variable supplies the starting value and receives touch updates.
  // Keep it alive for as long as the slider exists. Use min < max.
  // Length changes the track in pixels. The dot size stays fixed.
  lv_obj_t *slider(int length, int min, int max, int track_border_width,
                   std::uint32_t track_border_color, std::uint32_t track_color,
                   int dot_border_width, std::uint32_t dot_border_color,
                   std::uint32_t dot_color, std::atomic<int> &assigned_variable,
                   std::uint32_t z, int x, int y);

  // Available font heights are 10 through 20, plus 30 and 40 pixels. Other sizes use the nearest one.
  // Pass &assigned_variable to toggle a linked 0-to-1 slider on tap.
  // Pass a value to append it to the label. Keep it alive while the label exists.
  // auto_update refreshes the label every 50 ms when enabled.
  lv_obj_t *text(const char *label, int size, std::uint32_t color,
                 std::atomic<int> *on_click, std::uint32_t z, int x, int y,
                 const std::atomic<int> *value = nullptr, bool auto_update = true);
  // The reader returns the whole label. With auto_update false, it runs once.
  lv_obj_t *text(std::string (*read)(), int size, std::uint32_t color,
                 std::atomic<int> *on_click, std::uint32_t z, int x, int y,
                 bool auto_update);
}
