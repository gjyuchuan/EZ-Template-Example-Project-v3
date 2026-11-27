#include "brain_display.hpp"

#include <algorithm>
#include <atomic>
#include <functional>
#include <list>
#include <string>
#include <utility>

extern "C" {
  extern lv_font_t lv_font_dejavu_11;
  extern lv_font_t lv_font_dejavu_12;
  extern lv_font_t lv_font_dejavu_13;
  extern lv_font_t lv_font_dejavu_14;
  extern lv_font_t lv_font_dejavu_15;
  extern lv_font_t lv_font_dejavu_16;
  extern lv_font_t lv_font_dejavu_17;
  extern lv_font_t lv_font_dejavu_18;
  extern lv_font_t lv_font_dejavu_19;
  extern lv_font_t lv_font_dejavu_30;
  extern lv_font_t lv_font_dejavu_40;
}

namespace {
  lv_obj_t *screen = nullptr;

  // LVGL keeps pointers to these styles for as long as the controls exist.
  lv_style_t screen_style;
  std::list<lv_style_t> widget_styles;

  struct ButtonSettings {
    int min_amount;
    int max_amount;
    std::atomic<int> &set_var;
  };
  std::list<ButtonSettings> button_settings;

  struct BinarySlider {
    std::atomic<int> *assigned_variable;
    lv_obj_t *widget;
  };
  std::list<BinarySlider> binary_sliders;

  void place_widget(lv_obj_t *widget, std::uint32_t z, int x, int y) {
    lv_obj_set_pos(widget, x, y);
    lv_obj_set_free_num(widget, z);

    // LVGL draws its newest child in front. Move past siblings on higher layers.
    lv_obj_t *sibling = lv_obj_get_child(screen, widget);
    while (sibling != nullptr && lv_obj_get_free_num(sibling) > z) {
      sibling = lv_obj_get_child(screen, sibling);
    }
    lv_ll_move_before(&screen->child_ll, widget, sibling);
    lv_obj_invalidate(widget);
  }

  void connect_toggle(lv_obj_t *button, std::atomic<int> *assigned_variable) {
    lv_obj_set_free_ptr(button, assigned_variable);
    lv_btn_set_action(button, LV_BTN_ACTION_CLICK, [](lv_obj_t *widget) -> lv_res_t {
      std::atomic<int> *output = static_cast<std::atomic<int> *>(lv_obj_get_free_ptr(widget));
      const int value = output->load() == 0 ? 1 : 0;
      output->store(value);
      for (const BinarySlider &slider : binary_sliders) {
        if (slider.assigned_variable == output) {
          lv_slider_set_value(slider.widget, value);
        }
      }
      return LV_RES_OK;
    });
  }

  // Set both colors to give the shape a solid fill.
  void set_fill(lv_style_t &style, lv_color_t color, int radius = 0) {
    lv_style_copy(&style, &lv_style_plain);
    style.body.main_color = color;
    style.body.grad_color = color;
    style.body.radius = radius;
    style.body.opa = LV_OPA_COVER;
    style.body.empty = 0;
  }

  // Give each widget its own style at an address that stays fixed as we add widgets.
  lv_style_t &make_style(std::uint32_t color, int radius = 0, int border_width = 0, std::uint32_t border_color = 0x000000) {
    widget_styles.emplace_back();
    lv_style_t &style = widget_styles.back();
    set_fill(style, lv_color_hex(color), radius);
    style.body.border.width = border_width;
    style.body.border.color = lv_color_hex(border_color);
    style.body.border.part = LV_BORDER_FULL;
    style.body.border.opa = LV_OPA_COVER;
    return style;
  }

}

namespace brain_display {
  void brainDisplay(lv_obj_t *screen);

  lv_obj_t *rectangle(int length, int width, int border_width, std::uint32_t border_color, std::uint32_t color, std::atomic<int> *on_click, std::uint32_t z, int x, int y) {
    lv_style_t &style = make_style(color, 0, border_width, border_color);
    lv_obj_t *shape;
    if (on_click != nullptr) {
      shape = lv_btn_create(screen, nullptr);
      lv_btn_set_style(shape, LV_BTN_STYLE_REL, &style);
      lv_btn_set_style(shape, LV_BTN_STYLE_PR, &style);
      lv_btn_set_fit(shape, false, false);
      connect_toggle(shape, on_click);
    } else {
      shape = lv_obj_create(screen, nullptr);
      lv_obj_set_style(shape, &style);
      lv_obj_set_click(shape, false);
    }
    lv_obj_set_size(shape, length, width);
    place_widget(shape, z, x, y);
    return shape;
  }

  lv_obj_t *button(int min_amount, int max_amount, int length, int width, int border_width, std::uint32_t border_color, std::uint32_t color, std::atomic<int> &set_var, std::uint32_t z, int x, int y) {
    lv_obj_t *widget = lv_btn_create(screen, nullptr);
    lv_style_t &style = make_style(color, 0, border_width, border_color);
    lv_btn_set_style(widget, LV_BTN_STYLE_REL, &style);
    lv_btn_set_style(widget, LV_BTN_STYLE_PR, &style);
    lv_btn_set_fit(widget, false, false);
    lv_obj_set_size(widget, length, width);
    place_widget(widget, z, x, y);

    button_settings.push_back({std::min(min_amount, max_amount), std::max(min_amount, max_amount), set_var});
    ButtonSettings &settings = button_settings.back();
    set_var.store(std::clamp(set_var.load(), settings.min_amount, settings.max_amount));
    lv_obj_set_free_ptr(widget, &settings);
    lv_btn_set_action(widget, LV_BTN_ACTION_CLICK, [](lv_obj_t *control) -> lv_res_t {
      ButtonSettings &settings = *static_cast<ButtonSettings *>(lv_obj_get_free_ptr(control));
      const int value = settings.set_var.load();
      settings.set_var.store(value >= settings.min_amount && value < settings.max_amount
                                 ? value + 1 : settings.min_amount);
      return LV_RES_OK;
    });
    return widget;
  }

  lv_obj_t *slider(int length, int min, int max, int track_border_width, std::uint32_t track_border_color, std::uint32_t track_color, int dot_border_width, std::uint32_t dot_border_color, std::uint32_t dot_color, std::atomic<int> &assigned_variable, std::uint32_t z, int x, int y) {
    lv_obj_t *control = lv_slider_create(screen, nullptr);
    lv_style_t &track_style = make_style(track_color, LV_RADIUS_CIRCLE, track_border_width, track_border_color);
    // LVGL uses the background padding to inset the track when the knob is inside.
    // The inherited padding squeezes a 20 px track until almost only the border shows.
    track_style.body.padding.hor = 0;
    track_style.body.padding.ver = 0;
    lv_slider_set_style(control, LV_SLIDER_STYLE_BG, &track_style);
    lv_slider_set_style(control, LV_SLIDER_STYLE_INDIC, &lv_style_transp_tight);
    lv_slider_set_style(control, LV_SLIDER_STYLE_KNOB, &make_style(dot_color, LV_RADIUS_CIRCLE, dot_border_width, dot_border_color));
    lv_slider_set_knob_in(control, true);
    // Keep the slider horizontal and the dot size tied to the fixed thickness.
    lv_obj_set_size(control, std::max(length, 21), 20);
    place_widget(control, z, x, y);
    lv_slider_set_range(control, min, max);
    lv_slider_set_value(control, std::clamp(assigned_variable.load(), min, max));
    lv_obj_set_free_ptr(control, &assigned_variable);
    assigned_variable.store(lv_slider_get_value(control));
    if (min == 0 && max == 1) {
      binary_sliders.push_back({&assigned_variable, control});
    }
    lv_slider_set_action(control, [](lv_obj_t *widget) -> lv_res_t {
      std::atomic<int> *output = static_cast<std::atomic<int> *>(lv_obj_get_free_ptr(widget));
      output->store(lv_slider_get_value(widget));
      return LV_RES_OK;
    });
    return control;
  }

  static lv_obj_t *make_text(std::function<std::string()> read, int size, std::uint32_t color,
                             std::atomic<int> *on_click, std::uint32_t z, int x, int y, bool auto_update) {
    widget_styles.push_back(lv_style_plain);
    lv_style_t &style = widget_styles.back();
    style.text.color = lv_color_hex(color);
    static const lv_font_t *const fonts_10_to_20[] = {
      &lv_font_dejavu_10, &lv_font_dejavu_11, &lv_font_dejavu_12, &lv_font_dejavu_13,
      &lv_font_dejavu_14, &lv_font_dejavu_15, &lv_font_dejavu_16, &lv_font_dejavu_17,
      &lv_font_dejavu_18, &lv_font_dejavu_19, &lv_font_dejavu_20
    };
    if (size < 25) {
      style.text.font = fonts_10_to_20[std::clamp(size, 10, 20) - 10];
    } else if (size < 35) {
      style.text.font = &lv_font_dejavu_30;
    } else {
      style.text.font = &lv_font_dejavu_40;
    }

    lv_obj_t *parent = screen;
    if (on_click != nullptr) {
      parent = lv_btn_create(screen, nullptr);
      lv_btn_set_style(parent, LV_BTN_STYLE_REL, &lv_style_transp_tight);
      lv_btn_set_style(parent, LV_BTN_STYLE_PR, &lv_style_transp_tight);
      lv_btn_set_fit(parent, false, false);
      lv_btn_set_layout(parent, LV_LAYOUT_OFF);
      connect_toggle(parent, on_click);
    }
    lv_obj_t *widget = lv_label_create(parent, nullptr);
    lv_label_set_style(widget, &style);
    std::string initial = read();
    lv_label_set_text(widget, initial.c_str());
    if (auto_update) {
      struct LiveText {
        lv_obj_t *widget;
        lv_obj_t *button;
        std::function<std::string()> read;
        std::string displayed;
        lv_signal_func_t signal_handler;
        lv_task_t *task;
      };

      auto *live = new LiveText{widget, on_click != nullptr ? parent : nullptr,
                                std::move(read), std::move(initial), lv_obj_get_signal_func(widget), nullptr};
      live->task = lv_task_create([](void *data) {
        auto &live = *static_cast<LiveText *>(data);
        std::string current = live.read();
        if (current == live.displayed) {
          return;
        }
        live.displayed = std::move(current);
        lv_label_set_text(live.widget, live.displayed.c_str());
        if (live.button != nullptr) {
          lv_obj_set_size(live.button, lv_obj_get_width(live.widget), lv_obj_get_height(live.widget));
        }
      }, 50, LV_TASK_PRIO_LOW, live);

      if (live->task != nullptr) {
        lv_obj_set_free_ptr(widget, live);
        lv_obj_set_signal_func(widget, [](lv_obj_t *widget, lv_signal_t signal, void *parameter) -> lv_res_t {
          auto *live = static_cast<LiveText *>(lv_obj_get_free_ptr(widget));
          const lv_res_t result = live->signal_handler(widget, signal, parameter);
          if (signal == LV_SIGNAL_CLEANUP) {
            lv_task_del(live->task);
            delete live;
          }
          return result;
        });
      } else {
        delete live;
      }
    }
    lv_obj_set_click(widget, false);
    if (on_click != nullptr) {
      lv_obj_set_pos(widget, 0, 0);
      lv_obj_set_size(parent, lv_obj_get_width(widget), lv_obj_get_height(widget));
      place_widget(parent, z, x, y);
    } else {
      place_widget(widget, z, x, y);
    }
    return widget;
  }

  lv_obj_t *text(const char *label, int size, std::uint32_t color, std::atomic<int> *on_click,
                 std::uint32_t z, int x, int y, const std::atomic<int> *value, bool auto_update) {
    return make_text([label = std::string(label), value] {
      return value != nullptr ? label + std::to_string(value->load()) : label;
    }, size, color, on_click, z, x, y, auto_update && value != nullptr);
  }

  lv_obj_t *text(std::string (*read)(), int size, std::uint32_t color, std::atomic<int> *on_click,
                 std::uint32_t z, int x, int y, bool auto_update) {
    return make_text(read, size, color, on_click, z, x, y, auto_update);
  }

  void initialize() {
    set_fill(screen_style, LV_COLOR_BLACK);

    screen = lv_obj_create(nullptr, nullptr);
    lv_obj_set_style(screen, &screen_style);
    brainDisplay(screen);
    lv_scr_load(screen);
  }
}
