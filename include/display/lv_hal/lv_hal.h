/**
 * Hardware interfaces for displays, input devices, and the LVGL clock.
 * Drivers register callbacks that transfer pixels or report touch and
 * button input. The clock gives LVGL elapsed time for updates.
 * The sections retain their original LVGL 5.3 declarations.
 */
#ifndef PROS_DISPLAY_LV_HAL_H
#define PROS_DISPLAY_LV_HAL_H

/* lv_hal_disp.h
 * Registers a display driver and defines how it accepts rendered pixels.
 */
/**
 * @file hal_disp.h
 *
 * @description Display Driver HAL interface header file
 *
 */

#ifndef HAL_DISP_H
#define HAL_DISP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdbool.h>
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Display Driver structure to be registered by HAL
 */
typedef struct _disp_drv_t {
    /*Write the internal buffer (VDB) to the display. 'lv_flush_ready()' has to be called when finished*/
    void (*disp_flush)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);

    /*Fill an area with a color on the display*/
    void (*disp_fill)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);

    /*Write pixel map (e.g. image) to the display*/
    void (*disp_map)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);

    /*Optional interface functions to use GPU*/
#if USE_LV_GPU
    /*Blend two memories using opacity (GPU only)*/
    void (*mem_blend)(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);

    /*Fill a memory with a color (GPU only)*/
    void (*mem_fill)(lv_color_t * dest, uint32_t length, lv_color_t color);
#endif

#if LV_VDB_SIZE
    /*Optional: Set a pixel in a buffer according to the requirements of the display*/
    void (*vdb_wr)(uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
#endif
} lv_disp_drv_t;

typedef struct _disp_t {
    lv_disp_drv_t driver;
    struct _disp_t *next;
} lv_disp_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize a display driver with default values.
 * It is used to surly have known values in the fields ant not memory junk.
 * After it you can set the fields.
 * @param driver pointer to driver variable to initialize
 */
void lv_disp_drv_init(lv_disp_drv_t *driver);

/**
 * Register an initialized display driver.
 * Automatically set the first display as active.
 * @param driver pointer to an initialized 'lv_disp_drv_t' variable (can be local variable)
 * @return pointer to the new display or NULL on error
 */
lv_disp_t * lv_disp_drv_register(lv_disp_drv_t *driver);

/**
 * Set the active display
 * @param disp pointer to a display (return value of 'lv_disp_register')
 */
void lv_disp_set_active(lv_disp_t * disp);

/**
 * Get a pointer to the active display
 * @return pointer to the active display
 */
lv_disp_t * lv_disp_get_active(void);

/**
 * Get the next display.
 * @param disp pointer to the current display. NULL to initialize.
 * @return the next display or NULL if no more. Give the first display when the parameter is NULL
 */
lv_disp_t * lv_disp_next(lv_disp_t * disp);

/**
 * Fill a rectangular area with a color on the active display
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color_p pointer to an array of colors
 */
void lv_disp_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t *color_p);

/**
 * Fill a rectangular area with a color on the active display
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color fill color
 */
void lv_disp_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);

/**
 * Put a color map to a rectangular area on the active display
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color_map pointer to an array of colors
 */
void lv_disp_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_map);

#if USE_LV_GPU
/**
 * Blend pixels to a destination memory from a source memory
 * In 'lv_disp_drv_t' 'mem_blend' is optional. (NULL if not available)
 * @param dest a memory address. Blend 'src' here.
 * @param src pointer to pixel map. Blend it to 'dest'.
 * @param length number of pixels in 'src'
 * @param opa opacity (0, LV_OPA_TRANSP: transparent ... 255, LV_OPA_COVER, fully cover)
 */
void lv_disp_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);

/**
 * Fill a memory with a color (GPUs may support it)
 * In 'lv_disp_drv_t' 'mem_fill' is optional. (NULL if not available)
 * @param dest a memory address. Copy 'src' here.
 * @param src pointer to pixel map. Copy it to 'dest'.
 * @param length number of pixels in 'src'
 * @param opa opacity (0, LV_OPA_TRANSP: transparent ... 255, LV_OPA_COVER, fully cover)
 */
void lv_disp_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color);
/**
 * Shows if memory blending (by GPU) is supported or not
 * @return false: 'mem_blend' is not supported in the driver; true: 'mem_blend' is supported in the driver
 */
bool lv_disp_is_mem_blend_supported(void);

/**
 * Shows if memory fill (by GPU) is supported or not
 * @return false: 'mem_fill' is not supported in the drover; true: 'mem_fill' is supported in the driver
 */
bool lv_disp_is_mem_fill_supported(void);
#endif
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

/* lv_hal_indev.h
 * Registers input drivers and defines touch, keyboard, and encoder reports.
 */
/**
 * @file hal_indev.h
 *
 * @description Input Device HAL interface layer header file
 *
 */

#ifndef HAL_INDEV_H
#define HAL_INDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include <stdint.h>
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Possible input device types*/
enum {
    LV_INDEV_TYPE_NONE,        /*Show uninitialized state*/
    LV_INDEV_TYPE_POINTER,     /*Touch pad, mouse, external button*/
    LV_INDEV_TYPE_KEYPAD,      /*Keypad or keyboard*/
    LV_INDEV_TYPE_BUTTON,      /*External (hardware button) which is assinged to a specific point of the screen*/
    LV_INDEV_TYPE_ENCODER,     /*Encoder with only Left, Right turn and a Button*/
};
typedef uint8_t lv_hal_indev_type_t;

/*States for input devices*/
enum {
    LV_INDEV_STATE_REL = 0,
    LV_INDEV_STATE_PR
};
typedef uint8_t lv_indev_state_t;

/*Data type when an input device is read */
typedef struct {
    union {
        lv_point_t point;      /*For LV_INDEV_TYPE_POINTER the currently pressed point*/
        uint32_t key;          /*For LV_INDEV_TYPE_KEYPAD the currently pressed key*/
        uint32_t btn;          /*For LV_INDEV_TYPE_BUTTON the currently pressed button*/
        int16_t enc_diff;      /*For LV_INDEV_TYPE_ENCODER number of steps since the previous read*/
    };
    void *user_data;           /*'lv_indev_drv_t.priv' for this driver*/
    lv_indev_state_t state;    /*LV_INDEV_STATE_REL or LV_INDEV_STATE_PR*/
} lv_indev_data_t;

/*Initialized by the user and registered by 'lv_indev_add()'*/
typedef struct {
    lv_hal_indev_type_t type;                   /*Input device type*/
    bool (*read)(lv_indev_data_t *data);        /*Function pointer to read data. Return 'true' if there is still data to be read (buffered)*/
    void *user_data;                            /*Pointer to user defined data, passed in 'lv_indev_data_t' on read*/
} lv_indev_drv_t;

struct _lv_obj_t;

/*Run time data of input devices*/
typedef struct _lv_indev_proc_t {
    lv_indev_state_t state;
    union {
        struct {    /*Pointer and button data*/
            lv_point_t act_point;
            lv_point_t last_point;
            lv_point_t vect;
            lv_point_t drag_sum;                /*Count the dragged pixels to check LV_INDEV_DRAG_LIMIT*/
            struct _lv_obj_t * act_obj;
            struct _lv_obj_t * last_obj;

            /*Flags*/
            uint8_t drag_range_out      :1;
            uint8_t drag_in_prog        :1;
            uint8_t wait_unil_release   :1;
        };
        struct {    /*Keypad data*/
            lv_indev_state_t last_state;
            uint32_t last_key;
        };
    };

    uint32_t pr_timestamp;          /*Pressed time stamp*/
    uint32_t longpr_rep_timestamp;  /*Long press repeat time stamp*/

    /*Flags*/
    uint8_t long_pr_sent        :1;
    uint8_t reset_query         :1;
    uint8_t disabled            :1;
} lv_indev_proc_t;

struct _lv_indev_t;

/* Object signals use an 8-bit ID. The LV_SIGNAL_* values are defined in lv_core.h. */
typedef uint8_t lv_signal_t;

typedef void (*lv_indev_feedback_t)(struct _lv_indev_t *, lv_signal_t);

struct _lv_obj_t;
struct _lv_group_t;

/*The main input device descriptor with driver, runtime data ('proc') and some additional information*/
typedef struct _lv_indev_t {
    lv_indev_drv_t driver;
    lv_indev_proc_t proc;
    lv_indev_feedback_t feedback;
    uint32_t last_activity_time;
    union {
        struct _lv_obj_t *cursor;       /*Cursor for LV_INPUT_TYPE_POINTER*/
        struct _lv_group_t *group;      /*Keypad destination group*/
        const lv_point_t * btn_points;      /*Array points assigned to the button ()screen will be pressed here by the buttons*/

    };
    struct _lv_indev_t *next;
} lv_indev_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize an input device driver with default values.
 * It is used to surly have known values in the fields ant not memory junk.
 * After it you can set the fields.
 * @param driver pointer to driver variable to initialize
 */
void lv_indev_drv_init(lv_indev_drv_t *driver);

/**
 * Register an initialized input device driver.
 * @param driver pointer to an initialized 'lv_indev_drv_t' variable (can be local variable)
 * @return pointer to the new input device or NULL on error
 */
lv_indev_t * lv_indev_drv_register(lv_indev_drv_t *driver);

/**
 * Get the next input device.
 * @param indev pointer to the current input device. NULL to initialize.
 * @return the next input devise or NULL if no more. Gives the first input device when the parameter is NULL
 */
lv_indev_t * lv_indev_next(lv_indev_t * indev);

/**
 * Read data from an input device.
 * @param indev pointer to an input device
 * @param data input device will write its data here
 * @return false: no more data; true: there more data to read (buffered)
 */
bool lv_indev_read(lv_indev_t * indev, lv_indev_data_t *data);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

/* lv_hal_tick.h
 * Defines the time source used for delays, animation, and scheduling.
 */
/**
 * @file lv_hal_tick.h
 * Provide access to the system tick with 1 millisecond resolution
 */

#ifndef LV_HAL_TICK_H
#define LV_HAL_TICK_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_conf.h"
#else
#include "display/lv_conf.h"
#endif
#include <stdint.h>
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/
#ifndef LV_ATTRIBUTE_TICK_INC
#define LV_ATTRIBUTE_TICK_INC
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * You have to call this function periodically
 * @param tick_period the call period of this function in milliseconds
 */
LV_ATTRIBUTE_TICK_INC void lv_tick_inc(uint32_t tick_period);

/**
 * Get the elapsed milliseconds since start up
 * @return the elapsed milliseconds
 */
uint32_t lv_tick_get(void);

/**
 * Get the elapsed milliseconds since a previous time stamp
 * @param prev_tick a previous time stamp (return value of systick_get() )
 * @return the elapsed milliseconds since 'prev_tick'
 */
uint32_t lv_tick_elaps(uint32_t prev_tick);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_HAL_TICK_H*/

/* lv_hal.h
 * Collects the display, input, and tick driver interfaces.
 */
/**
 * @file hal.h
 *
 */

#ifndef HAL_H
#define HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

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
} /* extern "C" */
#endif

#endif

#endif /* PROS_DISPLAY_LV_HAL_H */
