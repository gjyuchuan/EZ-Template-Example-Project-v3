/**
 * @file lvgl.h
 * Include all LittleV GL related headers
 */

#ifndef LVGL_H
#define LVGL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include "lv_version.h"

#include "lv_core/lv_core.h"
#include "lv_draw/lv_draw.h"
#include "lv_fonts/lv_fonts.h"
#include "lv_hal/lv_hal.h"
#include "lv_misc/lv_misc.h"
#include "lv_objx/lv_objx.h"
#include "lv_themes/lv_themes.h"
#pragma GCC diagnostic pop

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
}
#endif

#endif /*LVGL_H*/
