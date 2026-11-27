#pragma once

#include <string>

#include "display/lvgl.h"

namespace brain_display {
  std::string read_connection_label();
  void create_telemetry(lv_obj_t *screen);
}
