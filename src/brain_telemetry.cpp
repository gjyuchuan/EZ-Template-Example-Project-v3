#include "brain_telemetry.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <optional>
#include <string>

#include "brain_display.hpp"
#include "display/lv_draw/lv_draw.h"
#include "pros/apix.h"
#include "pros/error.h"
#include "pros/misc.hpp"
#include "pros/rtos.h"

namespace {
  constexpr unsigned sample_ms = 200;
  constexpr unsigned recent_drop_ms = 10000;
  constexpr unsigned history_points = 15 * 60 * 1000 / sample_ms + 1;
  constexpr unsigned plot_points = 91;
  constexpr unsigned auton_seconds = 15;
  constexpr unsigned windows_ms[] = {5000, 15000, 30000, 60000, 180000, 300000, 600000};
  constexpr const char *window_names[] = {"5 sec", "15 sec", "30 sec", "1 min", "3 min", "5 min", "10 min"};
  constexpr lv_coord_t plot_x = 34;
  constexpr lv_coord_t plot_y = 114;
  constexpr lv_coord_t plot_width = 440;
  constexpr lv_coord_t plot_height = 90;

  std::atomic<int> window{0};
  std::atomic<int> show_last{1};
  std::atomic<int> height_step{3};
  constexpr std::uint32_t colors[] = {0xFFE031, 0xFF8C24, 0xFF4141};

  enum Event : std::uint8_t {
    motor_disconnected = 1 << 0,
    motor_reconnected = 1 << 1,
    radio_disconnected = 1 << 2
  };
  constexpr Event event_types[] = {motor_disconnected, motor_reconnected, radio_disconnected};
  constexpr std::uint32_t event_colors[] = {colors[1], colors[0], colors[2]};

  struct Sample {
    std::uint32_t time_ms;
    std::array<float, 3> values;
    bool valid;
    std::uint8_t events;
  };

  struct Telemetry {
    std::array<Sample, history_points> history;
    std::array<bool, 21> connected_motors{};
    std::array<bool, 21> seen_motors{};
    std::array<bool, 21> connected_radios{};
    int controller_connection = 0;
    std::optional<std::uint32_t> last_wireless_drop;
    std::array<std::uint8_t, plot_width> event_columns{};
    lv_obj_t *chart = nullptr;
    std::array<lv_chart_series_t *, 3> series{};
    lv_obj_t *scale_top = nullptr;
    lv_obj_t *scale_middle = nullptr;
    unsigned next = 0;
    unsigned count = 0;
    std::uint32_t started = 0;
    std::array<lv_obj_t *, 3> time_ticks{};
    lv_obj_t *prediction = nullptr;
    bool was_auton = false;
    double auton_watt_ms = 0;
    unsigned auton_sample_ms = 0;
    double last_auton_watts = 0;
    bool has_auton = false;

    const Sample &at(unsigned index) const {
      return history[(next + history_points - count + index) % history_points];
    }
  };

  Telemetry telemetry{};
  lv_style_t chart_style;
  std::array<lv_style_t, 3> event_styles;
  lv_design_func_t chart_design;

  std::uint8_t read_connection_events(Telemetry &data, std::uint32_t now) {
    std::uint8_t events = 0;
    for (unsigned port = 0; port < data.connected_motors.size(); ++port) {
      const auto type = pros::c::registry_get_plugged_type(port);
      if (type == pros::c::E_DEVICE_UNDEFINED) {
        continue;
      }
      const bool radio_connected = type == pros::c::E_DEVICE_RADIO;
      if (data.connected_radios[port] && !radio_connected) {
        events |= radio_disconnected;
      }
      data.connected_radios[port] = radio_connected;

      const bool connected = type == pros::c::E_DEVICE_MOTOR;
      if (data.seen_motors[port] && connected != data.connected_motors[port]) {
        events |= connected ? motor_reconnected : motor_disconnected;
      }
      data.connected_motors[port] = connected;
      data.seen_motors[port] = data.seen_motors[port] || connected;
    }

    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    const int connection = controller.is_connected();
    if (connection >= 0 && connection <= 2) {
      if (data.controller_connection == 2 && connection != 2) {
        data.last_wireless_drop = now;
        events |= radio_disconnected;
      }
      data.controller_connection = connection;
    }
    return events;
  }

  bool draw_chart(lv_obj_t *chart, const lv_area_t *mask, lv_design_mode_t mode) {
    const bool result = chart_design(chart, mask, mode);
    if (mode != LV_DESIGN_DRAW_POST) {
      return result;
    }

    lv_area_t area;
    lv_obj_get_coords(chart, &area);
    for (unsigned col = 0; col < telemetry.event_columns.size(); ++col) {
      const auto events = telemetry.event_columns[col];
      const auto x = static_cast<lv_coord_t>(area.x1 + col);
      if (events == 0 || x < mask->x1 || x > mask->x2) {
        continue;
      }
      // Share the column when multiple events map to the same pixel.
      const int sections = ((events & motor_disconnected) != 0) + ((events & motor_reconnected) != 0) + ((events & radio_disconnected) != 0);
      int section = 0;
      for (unsigned i = 0; i < event_styles.size(); ++i) {
        if ((events & event_types[i]) == 0) {
          continue;
        }
        const lv_point_t from{x, static_cast<lv_coord_t>(area.y1 + 1 + (plot_height - 1) * section / sections)};
        ++section;
        const lv_point_t to{x, static_cast<lv_coord_t>(area.y1 + (plot_height - 1) * section / sections)};
        lv_draw_line(&from, &to, mask, &event_styles[i], LV_OPA_COVER);
      }
    }
    return result;
  }

  std::string read_window() {
    return window_names[window.load()];
  }

  std::string read_height() {
    return "Max " + std::to_string(height_step.load() * 10);
  }

  std::string read_history_position() {
    return show_last.load() ? "Last" : "First";
  }

  void update_telemetry(void *) {
    auto &data = telemetry;
    const auto now = pros::c::millis() - data.started;
    const auto voltage_mv = pros::battery::get_voltage();
    const auto current_ma = pros::battery::get_current();
    const bool valid = voltage_mv != PROS_ERR && current_ma != PROS_ERR && voltage_mv >= 0 && current_ma >= 0;
    const float volts = valid ? voltage_mv / 1000.0f : 0;
    const float amps = valid ? current_ma / 1000.0f : 0;
    const float watts = volts * amps;

    const bool is_auton = pros::competition::is_autonomous() && !pros::competition::is_disabled();
    if (data.was_auton && data.count != 0) {
      const auto &previous = data.at(data.count - 1);
      const auto elapsed = now - previous.time_ms;
      if (previous.valid && elapsed <= 2 * sample_ms) {
        data.auton_watt_ms += previous.values[1] * static_cast<double>(elapsed);
        data.auton_sample_ms += elapsed;
      }
      if (!is_auton && data.auton_sample_ms != 0) {
        data.last_auton_watts = data.auton_watt_ms / data.auton_sample_ms;
        data.has_auton = true;
      }
    }
    if (is_auton && !data.was_auton) {
      data.auton_watt_ms = 0;
      data.auton_sample_ms = 0;
    }
    data.was_auton = is_auton;

    data.history[data.next] = {now, {volts, watts, amps}, valid, read_connection_events(data, now)};
    data.next = (data.next + 1) % history_points;
    data.count = std::min(data.count + 1, history_points);

    const auto duration = windows_ms[window.load()];
    const auto oldest = data.at(0).time_ms;
    const auto latest_start = std::max(oldest, now > duration ? now - duration : 0U);
    const auto start = show_last.load() ? latest_start : oldest;
    data.event_columns.fill(0);
    for (unsigned i = 0; i < data.count; ++i) {
      const auto &sample = data.at(i);
      if (sample.events != 0 && sample.time_ms >= start && sample.time_ms - start <= duration) {
        const auto x = (sample.time_ms - start) * (plot_width - 1) / duration;
        data.event_columns[x] |= sample.events;
      }
    }
    std::array<std::array<lv_coord_t, plot_points>, 3> points;
    unsigned sample_index = 0;
    for (unsigned i = 0; i < plot_points; ++i) {
      const auto time = start + duration * i / (plot_points - 1);
      while (sample_index + 1 < data.count && data.at(sample_index + 1).time_ms <= time) {
        ++sample_index;
      }
      const auto &sample = data.at(sample_index);
      for (unsigned metric = 0; metric < points.size(); ++metric) {
        points[metric][i] = sample.valid && time <= now && time - sample.time_ms <= 2 * sample_ms ? static_cast<lv_coord_t>(std::clamp(std::lround(sample.values[metric] * 10), 0L, 30000L)) : LV_CHART_POINT_DEF;
      }
    }

    char label[80];
    const int top = height_step.load() * 10;
    lv_chart_set_range(data.chart, 0, top * 10);
    for (unsigned i = 0; i < data.series.size(); ++i) {
      lv_chart_set_points(data.chart, data.series[i], points[i].data());
    }
    std::snprintf(label, sizeof(label), "%d", top);
    lv_label_set_text(data.scale_top, label);
    std::snprintf(label, sizeof(label), "%d", top / 2);
    lv_label_set_text(data.scale_middle, label);
    const lv_coord_t tick_x[] = {plot_x + 1, plot_x + plot_width / 2, plot_x + plot_width - 1};
    for (unsigned i = 0; i < data.time_ticks.size(); ++i) {
      auto *tick = data.time_ticks[i];
      std::snprintf(label, sizeof(label), "%.1f s", (start + duration * i / 2) / 1000.0);
      lv_label_set_text(tick, label);
      lv_obj_set_x(tick, tick_x[i] - lv_obj_get_width(tick) * i / 2);
    }

    double mean_watts = 0;
    const char *basis = nullptr;
    if (is_auton && data.auton_sample_ms != 0) {
      mean_watts = data.auton_watt_ms / data.auton_sample_ms;
      basis = "current auton";
    } else if (data.has_auton) {
      mean_watts = data.last_auton_watts;
      basis = "last auton";
    } else {
      unsigned samples = 0;
      for (unsigned i = data.count; i > 0 && now - data.at(i - 1).time_ms <= 5000; --i) {
        const auto &sample = data.at(i - 1);
        if (sample.valid) {
          mean_watts += sample.values[1];
          ++samples;
        }
      }
      if (samples != 0) {
        mean_watts /= samples;
        basis = "recent draw";
      }
    }
    if (basis != nullptr) {
      std::snprintf(label, sizeof(label), "%u s auton estimate: %.1f J / %.3f Wh (%s)", auton_seconds, mean_watts * auton_seconds, mean_watts * auton_seconds / 3600.0, basis);
    } else {
      std::snprintf(label, sizeof(label), "%u s auton estimate: waiting for battery data", auton_seconds);
    }
    lv_label_set_text(data.prediction, label);
  }
}

namespace brain_display {
  std::string read_connection_label() {
    if (telemetry.controller_connection == 0) {
      return "Connection: Bad";
    }
    const auto now = pros::c::millis() - telemetry.started;
    if (telemetry.controller_connection == 2 && telemetry.last_wireless_drop &&
        now - *telemetry.last_wireless_drop < recent_drop_ms) {
      return "Connection: Moderate";
    }
    return "Connection: Good";
  }

  void create_telemetry(lv_obj_t *screen) {
    button(0, 1, 73, 24, 1, 0x808080, 0x202020, show_last, 1, 6, 69);
    text(read_history_position, 14, 0xFFFFFF, nullptr, 2, 16, 73, true);
    slider(135, 0, sizeof(windows_ms) / sizeof(windows_ms[0]) - 1, 1, 0x808080, 0x303030, 0, 0xFFFFFF, 0xFFFFFF, window, 1, 92, 71);
    text(read_window, 14, 0xFFFFFF, nullptr, 2, 234, 73, true);
    slider(112, 1, 9, 1, 0x808080, 0x303030, 0, 0xFFFFFF, 0xFFFFFF, height_step, 1, 294, 71);
    text(read_height, 14, 0xFFFFFF, nullptr, 2, 414, 73, true);

    lv_style_copy(&chart_style, &lv_style_plain);
    chart_style.body.opa = LV_OPA_TRANSP;
    chart_style.body.border.width = 0;

    constexpr std::uint32_t grid_color = 0x444444;
    rectangle(plot_width, plot_height, 0, 0, 0x171717, nullptr, 0, plot_x, plot_y);
    for (int i = 0; i < 5; ++i) {
      const int x = plot_x + 1 + (plot_width - 2) * i / 4;
      rectangle(1, plot_height - 1, 0, 0, grid_color, nullptr, 0, x, plot_y + 1);
    }
    for (int i = 0; i < 3; ++i) {
      const int y = plot_y + (plot_height - 1) * i / 2;
      rectangle(plot_width - 1, 1, 0, 0, grid_color, nullptr, 0, plot_x + 1, y);
    }

    text("Volts (V)", 12, colors[0], nullptr, 2, 70, 98);
    text("Watts (W)", 12, colors[1], nullptr, 2, 191, 98);
    text("Amps (A)", 12, colors[2], nullptr, 2, 312, 98);

    telemetry.chart = lv_chart_create(screen, nullptr);
    auto *chart = telemetry.chart;
    lv_obj_set_pos(chart, plot_x, plot_y);
    lv_obj_set_size(chart, plot_width, plot_height);
    lv_obj_set_click(chart, false);
    lv_chart_set_style(chart, &chart_style);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(chart, plot_points);
    lv_chart_set_div_line_count(chart, 0, 0);
    lv_chart_set_series_width(chart, 2);
    for (unsigned i = 0; i < event_styles.size(); ++i) {
      lv_style_copy(&event_styles[i], &lv_style_plain);
      event_styles[i].line.color = lv_color_hex(event_colors[i]);
      event_styles[i].line.width = 1;
      event_styles[i].line.opa = LV_OPA_COVER;
    }
    chart_design = lv_obj_get_design_func(chart);
    lv_obj_set_design_func(chart, draw_chart);
    for (unsigned i = 0; i < telemetry.series.size(); ++i) {
      telemetry.series[i] = lv_chart_add_series(chart, lv_color_hex(colors[i]));
    }
    telemetry.scale_top = text("", 12, 0xFFFFFF, nullptr, 2, 7, 111);
    telemetry.scale_middle = text("", 12, 0xFFFFFF, nullptr, 2, 7, 153);
    text("0", 12, 0xFFFFFF, nullptr, 2, 7, 193);
    for (auto &tick : telemetry.time_ticks) {
      tick = text("", 12, 0xFFFFFF, nullptr, 2, plot_x, 206);
    }
    telemetry.prediction = text("", 12, 0xFFFFFF, nullptr, 2, 6, 223);
    telemetry.started = pros::c::millis();
    update_telemetry(nullptr);
    lv_task_create(update_telemetry, sample_ms, LV_TASK_PRIO_LOW, nullptr);
  }
}
