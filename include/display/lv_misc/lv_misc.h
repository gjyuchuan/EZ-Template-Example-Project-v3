/**
 * Shared data types and utilities used throughout LVGL.
 * Includes colors, coordinates, fonts, encoded text, memory, file access,
 * logging, animations, and the scheduler for LVGL callbacks.
 * The sections retain their original LVGL 5.3 declarations.
 */
#ifndef PROS_DISPLAY_LV_MISC_H
#define PROS_DISPLAY_LV_MISC_H

/* lv_anim.h
 * Interpolates values over time and runs animation callbacks.
 */
/**
 * @file anim.h
 *
 */

#ifndef ANIM_H
#define ANIM_H

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

#if USE_LV_ANIMATION

#include <stdint.h>
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

struct _lv_anim_t;

typedef int32_t(*lv_anim_path_t)(const struct _lv_anim_t*);

typedef void (*lv_anim_fp_t)(void *, int32_t);
typedef void (*lv_anim_cb_t)(void *);

typedef struct _lv_anim_t
{
    void * var;                     /*Variable to animate*/
    lv_anim_fp_t fp;                /*Animator function*/
    lv_anim_cb_t end_cb;            /*Call it when the animation is ready*/
    lv_anim_path_t path;            /*An array with the steps of animations*/
    int32_t start;                  /*Start value*/
    int32_t end;                    /*End value*/
    uint16_t time;                  /*Animation time in ms*/
    int16_t act_time;               /*Current time in animation. Set to negative to make delay.*/
    uint16_t playback_pause;        /*Wait before play back*/
    uint16_t repeat_pause;          /*Wait before repeat*/
    uint8_t playback :1;            /*When the animation is ready play it back*/
    uint8_t repeat :1;              /*Repeat the animation infinitely*/
    /*Animation system use these - user shouldn't set*/
    uint8_t playback_now :1;        /*Play back is in progress*/
    uint32_t has_run     :1;        /*Indicates the animation has run it this round*/
} lv_anim_t;

/*Example initialization
lv_anim_t a;
a.var = obj;
a.start = lv_obj_get_height(obj);
a.end = new_height;
a.fp = (lv_anim_fp_t)lv_obj_set_height;
a.path = lv_anim_path_linear;
a.end_cb = NULL;
a.act_time = 0;
a.time = 200;
a.playback = 0;
a.playback_pause = 0;
a.repeat = 0;
a.repeat_pause = 0;
lv_anim_create(&a);
 */
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Init. the animation module
 */
void lv_anim_init(void);

/**
 * Create an animation
 * @param anim_p an initialized 'anim_t' variable. Not required after call.
 */
void lv_anim_create(lv_anim_t * anim_p);

/**
 * Delete an animation for a variable with a given animatior function
 * @param var pointer to variable
 * @param fp a function pointer which is animating 'var',
 *           or NULL to ignore it and delete all animation with 'var
 * @return true: at least 1 animation is deleted, false: no animation is deleted
 */
bool lv_anim_del(void * var, lv_anim_fp_t fp);

/**
 * Get the number of currently running animations
 * @return the number of running animations
 */
uint16_t lv_anim_count_running(void);

/**
 * Calculate the time of an animation with a given speed and the start and end values
 * @param speed speed of animation in unit/sec
 * @param start start value of the animation
 * @param end end value of the animation
 * @return the required time [ms] for the animation with the given parameters
 */
uint16_t lv_anim_speed_to_time(uint16_t speed, int32_t start, int32_t end);

/**
 * Calculate the current value of an animation applying linear characteristic
 * @param a pointer to an animation
 * @return the current value to set
 */
int32_t lv_anim_path_linear(const lv_anim_t *a);

/**
 * Calculate the current value of an animation slowing down the start phase
 * @param a pointer to an animation
 * @return the current value to set
 */
int32_t lv_anim_path_ease_in(const lv_anim_t * a);

/**
 * Calculate the current value of an animation slowing down the end phase
 * @param a pointer to an animation
 * @return the current value to set
 */
int32_t lv_anim_path_ease_out(const lv_anim_t * a);

/**
 * Calculate the current value of an animation applying an "S" characteristic (cosine)
 * @param a pointer to an animation
 * @return the current value to set
 */
int32_t lv_anim_path_ease_in_out(const lv_anim_t *a);

/**
 * Calculate the current value of an animation with overshoot at the end
 * @param a pointer to an animation
 * @return the current value to set
 */
int32_t lv_anim_path_overshoot(const lv_anim_t * a);

/**
 * Calculate the current value of an animation with 3 bounces
 * @param a pointer to an animation
 * @return the current value to set
 */
int32_t lv_anim_path_bounce(const lv_anim_t * a);

/**
 * Calculate the current value of an animation applying step characteristic.
 * (Set end value on the end of the animation)
 * @param a pointer to an animation
 * @return the current value to set
 */
int32_t lv_anim_path_step(const lv_anim_t *a);
/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_ANIMATION == 0*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_ANIM_H*/

/* lv_area.h
 * Defines points, coordinates, and rectangular area math.
 */
/**
 * @file lv_area.h
 *
 */

#ifndef LV_AREA_H
#define LV_AREA_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/
#define LV_COORD_MAX     (16383)    /*To avoid overflow don't let the max [-32,32k] range */
#define LV_COORD_MIN     (-16384)

/**********************
 *      TYPEDEFS
 **********************/
typedef int16_t lv_coord_t;

typedef struct
{
    lv_coord_t x;
    lv_coord_t y;
} lv_point_t;

typedef struct
{
    lv_coord_t x1;
    lv_coord_t y1;
    lv_coord_t x2;
    lv_coord_t y2;
} lv_area_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize an area
 * @param area_p pointer to an area
 * @param x1 left coordinate of the area
 * @param y1 top coordinate of the area
 * @param x2 right coordinate of the area
 * @param y2 bottom coordinate of the area
 */
void lv_area_set(lv_area_t * area_p, lv_coord_t x1, lv_coord_t y1, lv_coord_t x2, lv_coord_t y2);

/**
 * Copy an area
 * @param dest pointer to the destination area
 * @param src pointer to the source area
 */
inline static void lv_area_copy(lv_area_t * dest, const lv_area_t * src)
{
    memcpy(dest, src, sizeof(lv_area_t));
}

/**
 * Get the width of an area
 * @param area_p pointer to an area
 * @return the width of the area (if x1 == x2 -> width = 1)
 */
static inline lv_coord_t lv_area_get_width(const lv_area_t * area_p)
{
    return area_p->x2 - area_p->x1 + 1;
}

/**
 * Get the height of an area
 * @param area_p pointer to an area
 * @return the height of the area (if y1 == y2 -> height = 1)
 */
static inline lv_coord_t lv_area_get_height(const lv_area_t * area_p)
{
    return area_p->y2 - area_p->y1 + 1;
}

/**
 * Set the width of an area
 * @param area_p pointer to an area
 * @param w the new width of the area (w == 1 makes x1 == x2)
 */
void lv_area_set_width(lv_area_t * area_p, lv_coord_t w);

/**
 * Set the height of an area
 * @param area_p pointer to an area
 * @param h the new height of the area (h == 1 makes y1 == y2)
 */
void lv_area_set_height(lv_area_t * area_p, lv_coord_t h);

/**
 * Set the position of an area (width and height will be kept)
 * @param area_p pointer to an area
 * @param x the new x coordinate of the area
 * @param y the new y coordinate of the area
 */
void lv_area_set_pos(lv_area_t * area_p, lv_coord_t x, lv_coord_t y);

/**
 * Return with area of an area (x * y)
 * @param area_p pointer to an area
 * @return size of area
 */
uint32_t lv_area_get_size(const lv_area_t * area_p);

/**
 * Get the common parts of two areas
 * @param res_p pointer to an area, the result will be stored her
 * @param a1_p pointer to the first area
 * @param a2_p pointer to the second area
 * @return false: the two area has NO common parts, res_p is invalid
 */
bool lv_area_intersect(lv_area_t * res_p, const lv_area_t * a1_p, const lv_area_t * a2_p);

/**
 * Join two areas into a third which involves the other two
 * @param res_p pointer to an area, the result will be stored here
 * @param a1_p pointer to the first area
 * @param a2_p pointer to the second area
 */
void lv_area_join(lv_area_t * a_res_p, const lv_area_t * a1_p, const lv_area_t * a2_p);

/**
 * Check if a point is on an area
 * @param a_p pointer to an area
 * @param p_p pointer to a point
 * @return false:the point is out of the area
 */
bool lv_area_is_point_on(const lv_area_t * a_p, const lv_point_t * p_p);

/**
 * Check if two area has common parts
 * @param a1_p pointer to an area.
 * @param a2_p pointer to an other area
 * @return false: a1_p and a2_p has no common parts
 */
bool lv_area_is_on(const lv_area_t * a1_p, const lv_area_t * a2_p);

/**
 * Check if an area is fully on an other
 * @param ain_p pointer to an area which could be on aholder_p
 * @param aholder pointer to an area which could involve ain_p
 * @return
 */
bool lv_area_is_in(const lv_area_t * ain_p, const lv_area_t * aholder_p);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif

/* lv_circ.h
 * Provides helpers for stepping through points on a circle.
 */
/**
 * @file lv_circ.h
 *
 */

#ifndef LV_CIRC_H
#define LV_CIRC_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
#include <stddef.h>

/*********************
 *      DEFINES
 *********************/
#define LV_CIRC_OCT1_X(p) (p.x)
#define LV_CIRC_OCT1_Y(p) (p.y)
#define LV_CIRC_OCT2_X(p) (p.y)
#define LV_CIRC_OCT2_Y(p) (p.x)
#define LV_CIRC_OCT3_X(p) (-p.y)
#define LV_CIRC_OCT3_Y(p) (p.x)
#define LV_CIRC_OCT4_X(p) (-p.x)
#define LV_CIRC_OCT4_Y(p) (p.y)
#define LV_CIRC_OCT5_X(p) (-p.x)
#define LV_CIRC_OCT5_Y(p) (-p.y)
#define LV_CIRC_OCT6_X(p) (-p.y)
#define LV_CIRC_OCT6_Y(p) (-p.x)
#define LV_CIRC_OCT7_X(p) (p.y)
#define LV_CIRC_OCT7_Y(p) (-p.x)
#define LV_CIRC_OCT8_X(p) (p.x)
#define LV_CIRC_OCT8_Y(p) (-p.y)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the circle drawing
 * @param c pointer to a point. The coordinates will be calculated here
 * @param tmp point to a variable. It will store temporary data
 * @param radius radius of the circle
 */
void lv_circ_init(lv_point_t * c, lv_coord_t * tmp, lv_coord_t radius);

/**
 * Test the circle drawing is ready or not
 * @param c same as in circ_init
 * @return true if the circle is not ready yet
 */
bool lv_circ_cont(lv_point_t * c);

/**
 * Get the next point from the circle
 * @param c same as in circ_init. The next point stored here.
 * @param tmp same as in circ_init.
 */
void lv_circ_next(lv_point_t * c, lv_coord_t * tmp);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif

/* lv_color.h
 * Defines pixel color types, RGB conversion, opacity, and named colors.
 */
/**
 * @file lv_color.h
 *
 */

#ifndef LV_COLOR_H
#define LV_COLOR_H

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

/*Error checking*/
#if LV_COLOR_DEPTH == 24
#error "LV_COLOR_DEPTH  24 is deprecated. Use LV_COLOR_DEPTH  32 instead (lv_conf.h)"
#endif

#if LV_COLOR_DEPTH != 32 && LV_COLOR_SCREEN_TRANSP != 0
#error "LV_COLOR_SCREEN_TRANSP requires LV_COLOR_DEPTH == 32. Set it in lv_conf.h"
#endif

#if LV_COLOR_DEPTH != 16 && LV_COLOR_16_SWAP != 0
#error "LV_COLOR_16_SWAP requires LV_COLOR_DEPTH == 16. Set it in lv_conf.h"
#endif


#include <stdint.h>

/*********************
 *      DEFINES
 *********************/
#define LV_COLOR_WHITE   LV_COLOR_MAKE(0xFF,0xFF,0xFF)
#define LV_COLOR_SILVER  LV_COLOR_MAKE(0xC0,0xC0,0xC0)
#define LV_COLOR_GRAY    LV_COLOR_MAKE(0x80,0x80,0x80)
#define LV_COLOR_BLACK   LV_COLOR_MAKE(0x00,0x00,0x00)
#define LV_COLOR_RED     LV_COLOR_MAKE(0xFF,0x00,0x00)
#define LV_COLOR_MAROON  LV_COLOR_MAKE(0x80,0x00,0x00)
#define LV_COLOR_YELLOW  LV_COLOR_MAKE(0xFF,0xFF,0x00)
#define LV_COLOR_OLIVE   LV_COLOR_MAKE(0x80,0x80,0x00)
#define LV_COLOR_LIME    LV_COLOR_MAKE(0x00,0xFF,0x00)
#define LV_COLOR_GREEN   LV_COLOR_MAKE(0x00,0x80,0x00)
#define LV_COLOR_CYAN    LV_COLOR_MAKE(0x00,0xFF,0xFF)
#define LV_COLOR_AQUA    LV_COLOR_CYAN
#define LV_COLOR_TEAL    LV_COLOR_MAKE(0x00,0x80,0x80)
#define LV_COLOR_BLUE    LV_COLOR_MAKE(0x00,0x00,0xFF)
#define LV_COLOR_NAVY    LV_COLOR_MAKE(0x00,0x00,0x80)
#define LV_COLOR_MAGENTA LV_COLOR_MAKE(0xFF,0x00,0xFF)
#define LV_COLOR_PURPLE  LV_COLOR_MAKE(0x80,0x00,0x80)
#define LV_COLOR_ORANGE  LV_COLOR_MAKE(0xFF,0xA5,0x00)

enum {
    LV_OPA_TRANSP =  0,
    LV_OPA_0      =  0,
    LV_OPA_10     =  25,
    LV_OPA_20     =  51,
    LV_OPA_30     =  76,
    LV_OPA_40     =  102,
    LV_OPA_50     =  127,
    LV_OPA_60     =  153,
    LV_OPA_70     =  178,
    LV_OPA_80     =  204,
    LV_OPA_90     =  229,
    LV_OPA_100    =  255,
    LV_OPA_COVER  =  255,
};

#define LV_OPA_MIN      16      /*Opacities below this will be transparent*/
#define LV_OPA_MAX      251     /*Opacities above this will fully cover*/

#if LV_COLOR_DEPTH == 1
#define LV_COLOR_SIZE           8
#elif LV_COLOR_DEPTH == 8
#define LV_COLOR_SIZE           8
#elif LV_COLOR_DEPTH == 16
#define LV_COLOR_SIZE           16
#elif LV_COLOR_DEPTH == 32
#define LV_COLOR_SIZE           32
#else
#error "Invalid LV_COLOR_DEPTH in lv_conf.h! Set it to 1, 8, 16 or 32!"
#endif

/**********************
 *      TYPEDEFS
 **********************/

typedef union
{
    uint8_t blue  :1;
    uint8_t green :1;
    uint8_t red   :1;
    uint8_t full  :1;
} lv_color1_t;

typedef union
{
    struct
    {
        uint8_t blue  :2;
        uint8_t green :3;
        uint8_t red   :3;
    };
    uint8_t full;
} lv_color8_t;

typedef union
{
    struct
    {
#if LV_COLOR_16_SWAP == 0
        uint16_t blue  :5;
        uint16_t green :6;
        uint16_t red   :5;
#else
        uint16_t green_h :3;
        uint16_t red   :5;
        uint16_t blue  :5;
        uint16_t green_l :3;
#endif
    };
    uint16_t full;
} lv_color16_t;

typedef union
{
    struct
    {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t alpha;
    };
    uint32_t full;
} lv_color32_t;

#if LV_COLOR_DEPTH == 1
typedef uint8_t lv_color_int_t;
typedef lv_color1_t lv_color_t;
#elif LV_COLOR_DEPTH == 8
typedef uint8_t lv_color_int_t;
typedef lv_color8_t lv_color_t;
#elif LV_COLOR_DEPTH == 16
typedef uint16_t lv_color_int_t;
typedef lv_color16_t lv_color_t;
#elif LV_COLOR_DEPTH == 32
typedef uint32_t lv_color_int_t;
typedef lv_color32_t lv_color_t;
#else
#error "Invalid LV_COLOR_DEPTH in lv_conf.h! Set it to 1, 8, 16 or 32!"
#endif

typedef uint8_t lv_opa_t;

typedef struct
{
    uint16_t h;
    uint8_t s;
    uint8_t v;
} lv_color_hsv_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*In color conversations:
 * - When converting to bigger color type the LSB weight of 1 LSB is calculated
 *   E.g. 16 bit Red has 5 bits
 *         8 bit Red has 2 bits
 *        ----------------------
 *        8 bit red LSB = (2^5 - 1) / (2^2 - 1) = 31 / 3 = 10
 *
 * - When calculating to smaller color type simply shift out the LSBs
 *   E.g.  8 bit Red has 2 bits
 *        16 bit Red has 5 bits
 *        ----------------------
 *         Shift right with 5 - 3 = 2
 */

static inline uint8_t lv_color_to1(lv_color_t color)
{
#if LV_COLOR_DEPTH == 1
    return color.full;
#elif LV_COLOR_DEPTH == 8
    if((color.red   & 0x4) ||
            (color.green & 0x4) ||
            (color.blue  & 0x2)) {
        return 1;
    } else {
        return 0;
    }
#elif LV_COLOR_DEPTH == 16
#  if LV_COLOR_16_SWAP == 0
    if((color.red   & 0x10) ||
            (color.green & 0x20) ||
            (color.blue  & 0x10)) {
        return 1;
#  else
    if((color.red   & 0x10) ||
            (color.green_h & 0x20) ||
            (color.blue  & 0x10)) {
        return 1;
#  endif
    } else {
        return 0;
    }
#elif LV_COLOR_DEPTH == 32
    if((color.red   & 0x80) ||
            (color.green & 0x80) ||
            (color.blue  & 0x80)) {
        return 1;
    } else {
        return 0;
    }
#endif
}

static inline uint8_t lv_color_to8(lv_color_t color)
{
#if LV_COLOR_DEPTH == 1
    if(color.full == 0) return 0;
    else return 0xFF;
#elif LV_COLOR_DEPTH == 8
    return color.full;
#elif LV_COLOR_DEPTH == 16

#  if LV_COLOR_16_SWAP == 0
    lv_color8_t ret;
    ret.red = color.red >> 2;       /* 5 - 3  = 2*/
    ret.green = color.green >> 3;   /* 6 - 3  = 3*/
    ret.blue = color.blue >> 3;     /* 5 - 2  = 3*/
    return ret.full;
#  else
    lv_color8_t ret;
    ret.red = color.red >> 2;       /* 5 - 3  = 2*/
    ret.green = color.green_h;      /* 6 - 3  = 3*/
    ret.blue = color.blue >> 3;     /* 5 - 2  = 3*/
    return ret.full;
#  endif
#elif LV_COLOR_DEPTH == 32
    lv_color8_t ret;
    ret.red = color.red >> 5;       /* 8 - 3  = 5*/
    ret.green = color.green >> 5;   /* 8 - 3  = 5*/
    ret.blue = color.blue >> 6;     /* 8 - 2  = 6*/
    return ret.full;
#endif
}

static inline uint16_t lv_color_to16(lv_color_t color)
{
#if LV_COLOR_DEPTH == 1
    if(color.full == 0) return 0;
    else return 0xFFFF;
#elif LV_COLOR_DEPTH == 8
    lv_color16_t ret;
#  if LV_COLOR_16_SWAP == 0
    ret.red = color.red * 4;       /*(2^5 - 1)/(2^3 - 1) = 31/7 = 4*/
    ret.green = color.green * 9;   /*(2^6 - 1)/(2^3 - 1) = 63/7 = 9*/
    ret.blue = color.blue * 10;    /*(2^5 - 1)/(2^2 - 1) = 31/3 = 10*/
#  else
    ret.red = color.red * 4;
    uint8_t g_tmp = color.green * 9;
    ret.green_h = (g_tmp & 0x1F) >> 3;
    ret.green_l = g_tmp & 0x07;
    ret.blue = color.blue * 10;
#  endif
    return ret.full;
#elif LV_COLOR_DEPTH == 16
    return color.full;
#elif LV_COLOR_DEPTH == 32
    lv_color16_t ret;
#  if LV_COLOR_16_SWAP == 0
    ret.red = color.red >> 3;       /* 8 - 5  = 3*/
    ret.green = color.green >> 2;   /* 8 - 6  = 2*/
    ret.blue = color.blue >> 3;     /* 8 - 5  = 3*/
#  else
    ret.red = color.red >> 3;
    ret.green_h = (color.green & 0xE0) >> 5;
    ret.green_l = (color.green & 0x1C) >> 2;
    ret.blue = color.blue >> 3;
#  endif
    return ret.full;
#endif
}

static inline uint32_t lv_color_to32(lv_color_t color)
{
#if LV_COLOR_DEPTH == 1
    if(color.full == 0) return 0;
    else return 0xFFFFFFFF;
#elif LV_COLOR_DEPTH == 8
    lv_color32_t ret;
    ret.red = color.red * 36;        /*(2^8 - 1)/(2^3 - 1) = 255/7 = 36*/
    ret.green = color.green * 36;    /*(2^8 - 1)/(2^3 - 1) = 255/7 = 36*/
    ret.blue = color.blue * 85;      /*(2^8 - 1)/(2^2 - 1) = 255/3 = 85*/
    ret.alpha = 0xFF;
    return ret.full;
#elif LV_COLOR_DEPTH == 16
#  if LV_COLOR_16_SWAP == 0
    lv_color32_t ret;
    ret.red = color.red * 8;       /*(2^8 - 1)/(2^5 - 1) = 255/31 = 8*/
    ret.green = color.green * 4;   /*(2^8 - 1)/(2^6 - 1) = 255/63 = 4*/
    ret.blue = color.blue * 8;     /*(2^8 - 1)/(2^5 - 1) = 255/31 = 8*/
    ret.alpha = 0xFF;
    return ret.full;
#  else
    lv_color32_t ret;
    ret.red = color.red * 8;                                    /*(2^8 - 1)/(2^5 - 1) = 255/31 = 8*/
    ret.green = ((color.green_h << 3) + color.green_l) * 4;     /*(2^8 - 1)/(2^6 - 1) = 255/63 = 4*/
    ret.blue = color.blue * 8;                                   /*(2^8 - 1)/(2^5 - 1) = 255/31 = 8*/
    ret.alpha = 0xFF;
    return ret.full;
#  endif
#elif LV_COLOR_DEPTH == 32
    return color.full;
#endif
}

static inline lv_color_t lv_color_mix(lv_color_t c1, lv_color_t c2, uint8_t mix)
{
    lv_color_t ret;
#if LV_COLOR_DEPTH != 1
    /*LV_COLOR_DEPTH == 8, 16 or 32*/
    ret.red =   (uint16_t)((uint16_t) c1.red * mix + (c2.red * (255 - mix))) >> 8;
#  if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP
    /*If swapped Green is in 2 parts*/
    uint16_t g_1 = (c1.green_h << 3) + c1.green_l;
    uint16_t g_2 = (c2.green_h << 3) + c2.green_l;
    uint16_t g_out = (uint16_t)((uint16_t) g_1 * mix + (g_2 * (255 - mix))) >> 8;
    ret.green_h = g_out >> 3;
    ret.green_l = g_out & 0x7;
#  else
    ret.green = (uint16_t)((uint16_t) c1.green * mix + (c2.green * (255 - mix))) >> 8;
#  endif
    ret.blue =  (uint16_t)((uint16_t) c1.blue * mix + (c2.blue * (255 - mix))) >> 8;
# if LV_COLOR_DEPTH == 32
    ret.alpha = 0xFF;
# endif
#else
    /*LV_COLOR_DEPTH == 1*/
    ret.full = mix > LV_OPA_50 ? c1.full : c2.full;
#endif

    return ret;
}

/**
 * Get the brightness of a color
 * @param color a color
 * @return the brightness [0..255]
 */
static inline uint8_t lv_color_brightness(lv_color_t color)
{
    lv_color32_t c32;
    c32.full = lv_color_to32(color);
    uint16_t bright = 3 * c32.red + c32.blue + 4 * c32.green;
    return (uint16_t) bright >> 3;
}

/* The most simple macro to create a color from R,G and B values
 * The order of bit field is different on Big-endian and Little-endian machines*/
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#if LV_COLOR_DEPTH == 1
#define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){(b8 >> 7 | g8 >> 7 | r8 >> 7)})
#elif LV_COLOR_DEPTH == 8
#define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){{b8 >> 6, g8 >> 5, r8 >> 5}})
#elif LV_COLOR_DEPTH == 16
#  if LV_COLOR_16_SWAP == 0
#    define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){{b8 >> 3, g8 >> 2, r8 >> 3}})
#  else
#    define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){{g8 >> 5, r8 >> 3, b8 >> 3, (g8 >> 2) & 0x7}})
#  endif
#elif LV_COLOR_DEPTH == 32
#ifdef __cplusplus
#  define LV_COLOR_MAKE(r8, g8, b8) lv_color_t{b8, g8, r8, 0xff}
#else
#  define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){{b8, g8, r8, 0xff}})            /*Fix 0xff alpha*/
#endif
#endif
#else
#if LV_COLOR_DEPTH == 1
#define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){(r8 >> 7 | g8 >> 7 | b8 >> 7)})
#elif LV_COLOR_DEPTH == 8
#define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){{r8 >> 6, g8 >> 5, b8 >> 5}})
#elif LV_COLOR_DEPTH == 16
#define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){{r8 >> 3, g8 >> 2, b8 >> 3}})
#elif LV_COLOR_DEPTH == 32
#define LV_COLOR_MAKE(r8, g8, b8) ((lv_color_t){{0xff, r8, g8, b8}})            /*Fix 0xff alpha*/
#endif
#endif


#define LV_COLOR_HEX(c) LV_COLOR_MAKE((uint8_t) ((uint32_t)((uint32_t)c >> 16) & 0xFF), \
                                (uint8_t) ((uint32_t)((uint32_t)c >> 8) & 0xFF), \
                                (uint8_t) ((uint32_t) c & 0xFF))

/*Usage LV_COLOR_HEX3(0x16C) which means LV_COLOR_HEX(0x1166CC)*/
#define LV_COLOR_HEX3(c) LV_COLOR_MAKE((uint8_t) (((c >> 4) & 0xF0) | ((c >> 8) & 0xF)),   \
                                (uint8_t) ((uint32_t)(c & 0xF0)     | ((c & 0xF0) >> 4)), \
                                (uint8_t) ((uint32_t)(c & 0xF)      | ((c & 0xF) << 4)))

static inline lv_color_t lv_color_hex(uint32_t c){
    return LV_COLOR_HEX(c);
}

static inline lv_color_t lv_color_hex3(uint32_t c){
    return LV_COLOR_HEX3(c);
}


/**
 * Convert a HSV color to RGB
 * @param h hue [0..359]
 * @param s saturation [0..100]
 * @param v value [0..100]
 * @return the given RGB color in RGB (with LV_COLOR_DEPTH depth)
 */
lv_color_t lv_color_hsv_to_rgb(uint16_t h, uint8_t s, uint8_t v);

/**
 * Convert an RGB color to HSV
 * @param r red
 * @param g green
 * @param b blue
 * @return the given RGB color n HSV
 */
lv_color_hsv_t lv_color_rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*USE_COLOR*/

/* lv_symbol_def.h
 * Maps named UI symbols to character sequences stored in symbol fonts.
 */
#ifndef LV_SYMBOL_DEF_H
#define LV_SYMBOL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_conf.h"
#else
#include "display/lv_conf.h"
#endif

/*
 * With no UTF-8 support (192- 255) (192..241 is used)
 *
 * With UTF-8 support (in Supplemental Private Use Area-A): 0xF800 .. 0xF831
 * - Basic symbols:     0xE000..0xE01F
 * - File symbols:      0xE020..0xE03F
 * - Feedback symbols:  0xE040..0xE05F
 * - Reserved:          0xE060..0xE07F
 */

#if LV_TXT_UTF8 == 0
#define LV_SYMBOL_GLYPH_FIRST  0xC0
#define SYMBOL_AUDIO           _SYMBOL_VALUE1(C0)
#define SYMBOL_VIDEO           _SYMBOL_VALUE1(C1)
#define SYMBOL_LIST            _SYMBOL_VALUE1(C2)
#define SYMBOL_OK              _SYMBOL_VALUE1(C3)
#define SYMBOL_CLOSE           _SYMBOL_VALUE1(C4)
#define SYMBOL_POWER           _SYMBOL_VALUE1(C5)
#define SYMBOL_SETTINGS        _SYMBOL_VALUE1(C6)
#define SYMBOL_TRASH           _SYMBOL_VALUE1(C7)
#define SYMBOL_HOME            _SYMBOL_VALUE1(C8)
#define SYMBOL_DOWNLOAD        _SYMBOL_VALUE1(C9)
#define SYMBOL_DRIVE           _SYMBOL_VALUE1(CA)
#define SYMBOL_REFRESH         _SYMBOL_VALUE1(CB)
#define SYMBOL_MUTE            _SYMBOL_VALUE1(CC)
#define SYMBOL_VOLUME_MID      _SYMBOL_VALUE1(CD)
#define SYMBOL_VOLUME_MAX      _SYMBOL_VALUE1(CE)
#define SYMBOL_IMAGE           _SYMBOL_VALUE1(CF)
#define SYMBOL_EDIT            _SYMBOL_VALUE1(D0)
#define SYMBOL_PREV            _SYMBOL_VALUE1(D1)
#define SYMBOL_PLAY            _SYMBOL_VALUE1(D2)
#define SYMBOL_PAUSE           _SYMBOL_VALUE1(D3)
#define SYMBOL_STOP            _SYMBOL_VALUE1(D4)
#define SYMBOL_NEXT            _SYMBOL_VALUE1(D5)
#define SYMBOL_EJECT           _SYMBOL_VALUE1(D6)
#define SYMBOL_LEFT            _SYMBOL_VALUE1(D7)
#define SYMBOL_RIGHT           _SYMBOL_VALUE1(D8)
#define SYMBOL_PLUS            _SYMBOL_VALUE1(D9)
#define SYMBOL_MINUS           _SYMBOL_VALUE1(DA)
#define SYMBOL_WARNING         _SYMBOL_VALUE1(DB)
#define SYMBOL_SHUFFLE         _SYMBOL_VALUE1(DC)
#define SYMBOL_UP              _SYMBOL_VALUE1(DD)
#define SYMBOL_DOWN            _SYMBOL_VALUE1(DE)
#define SYMBOL_LOOP            _SYMBOL_VALUE1(DF)
#define SYMBOL_DIRECTORY       _SYMBOL_VALUE1(E0)
#define SYMBOL_UPLOAD          _SYMBOL_VALUE1(E1)
#define SYMBOL_CALL            _SYMBOL_VALUE1(E2)
#define SYMBOL_CUT             _SYMBOL_VALUE1(E3)
#define SYMBOL_COPY            _SYMBOL_VALUE1(E4)
#define SYMBOL_SAVE            _SYMBOL_VALUE1(E5)
#define SYMBOL_CHARGE          _SYMBOL_VALUE1(E6)
#define SYMBOL_BELL            _SYMBOL_VALUE1(E7)
#define SYMBOL_KEYBOARD        _SYMBOL_VALUE1(E8)
#define SYMBOL_GPS             _SYMBOL_VALUE1(E9)
#define SYMBOL_FILE            _SYMBOL_VALUE1(EA)
#define SYMBOL_WIFI            _SYMBOL_VALUE1(EB)
#define SYMBOL_BATTERY_FULL    _SYMBOL_VALUE1(EC)
#define SYMBOL_BATTERY_3       _SYMBOL_VALUE1(ED)
#define SYMBOL_BATTERY_2       _SYMBOL_VALUE1(EE)
#define SYMBOL_BATTERY_1       _SYMBOL_VALUE1(EF)
#define SYMBOL_BATTERY_EMPTY   _SYMBOL_VALUE1(F0)
#define SYMBOL_BLUETOOTH       _SYMBOL_VALUE1(F1)
#define LV_SYMBOL_GLYPH_LAST   0xF1
#define SYMBOL_DUMMY           _SYMBOL_VALUE1(FF)       /*Invalid symbol. If written before a string then `lv_img` will show it as a label*/

#else
#define LV_SYMBOL_GLYPH_FIRST  0xF800
#define SYMBOL_AUDIO           _SYMBOL_VALUE3(EF,A0,80)
#define SYMBOL_VIDEO           _SYMBOL_VALUE3(EF,A0,81)
#define SYMBOL_LIST            _SYMBOL_VALUE3(EF,A0,82)
#define SYMBOL_OK              _SYMBOL_VALUE3(EF,A0,83)
#define SYMBOL_CLOSE           _SYMBOL_VALUE3(EF,A0,84)
#define SYMBOL_POWER           _SYMBOL_VALUE3(EF,A0,85)
#define SYMBOL_SETTINGS        _SYMBOL_VALUE3(EF,A0,86)
#define SYMBOL_TRASH           _SYMBOL_VALUE3(EF,A0,87)
#define SYMBOL_HOME            _SYMBOL_VALUE3(EF,A0,88)
#define SYMBOL_DOWNLOAD        _SYMBOL_VALUE3(EF,A0,89)
#define SYMBOL_DRIVE           _SYMBOL_VALUE3(EF,A0,8A)
#define SYMBOL_REFRESH         _SYMBOL_VALUE3(EF,A0,8B)
#define SYMBOL_MUTE            _SYMBOL_VALUE3(EF,A0,8C)
#define SYMBOL_VOLUME_MID      _SYMBOL_VALUE3(EF,A0,8D)
#define SYMBOL_VOLUME_MAX      _SYMBOL_VALUE3(EF,A0,8E)
#define SYMBOL_IMAGE           _SYMBOL_VALUE3(EF,A0,8F)
#define SYMBOL_EDIT            _SYMBOL_VALUE3(EF,A0,90)
#define SYMBOL_PREV            _SYMBOL_VALUE3(EF,A0,91)
#define SYMBOL_PLAY            _SYMBOL_VALUE3(EF,A0,92)
#define SYMBOL_PAUSE           _SYMBOL_VALUE3(EF,A0,93)
#define SYMBOL_STOP            _SYMBOL_VALUE3(EF,A0,94)
#define SYMBOL_NEXT            _SYMBOL_VALUE3(EF,A0,95)
#define SYMBOL_EJECT           _SYMBOL_VALUE3(EF,A0,96)
#define SYMBOL_LEFT            _SYMBOL_VALUE3(EF,A0,97)
#define SYMBOL_RIGHT           _SYMBOL_VALUE3(EF,A0,98)
#define SYMBOL_PLUS            _SYMBOL_VALUE3(EF,A0,99)
#define SYMBOL_MINUS           _SYMBOL_VALUE3(EF,A0,9A)
#define SYMBOL_WARNING         _SYMBOL_VALUE3(EF,A0,9B)
#define SYMBOL_SHUFFLE         _SYMBOL_VALUE3(EF,A0,9C)
#define SYMBOL_UP              _SYMBOL_VALUE3(EF,A0,9D)
#define SYMBOL_DOWN            _SYMBOL_VALUE3(EF,A0,9E)
#define SYMBOL_LOOP            _SYMBOL_VALUE3(EF,A0,9F)
#define SYMBOL_DIRECTORY       _SYMBOL_VALUE3(EF,A0,A0)
#define SYMBOL_UPLOAD          _SYMBOL_VALUE3(EF,A0,A1)
#define SYMBOL_CALL            _SYMBOL_VALUE3(EF,A0,A2)
#define SYMBOL_CUT             _SYMBOL_VALUE3(EF,A0,A3)
#define SYMBOL_COPY            _SYMBOL_VALUE3(EF,A0,A4)
#define SYMBOL_SAVE            _SYMBOL_VALUE3(EF,A0,A5)
#define SYMBOL_CHARGE          _SYMBOL_VALUE3(EF,A0,A6)
#define SYMBOL_BELL            _SYMBOL_VALUE3(EF,A0,A7)
#define SYMBOL_KEYBOARD        _SYMBOL_VALUE3(EF,A0,A8)
#define SYMBOL_GPS             _SYMBOL_VALUE3(EF,A0,A9)
#define SYMBOL_FILE            _SYMBOL_VALUE3(EF,A0,AA)
#define SYMBOL_WIFI            _SYMBOL_VALUE3(EF,A0,AB)
#define SYMBOL_BATTERY_FULL    _SYMBOL_VALUE3(EF,A0,AC)
#define SYMBOL_BATTERY_3       _SYMBOL_VALUE3(EF,A0,AD)
#define SYMBOL_BATTERY_2       _SYMBOL_VALUE3(EF,A0,AE)
#define SYMBOL_BATTERY_1       _SYMBOL_VALUE3(EF,A0,AF)
#define SYMBOL_BATTERY_EMPTY   _SYMBOL_VALUE3(EF,A0,B0)
#define SYMBOL_BLUETOOTH       _SYMBOL_VALUE3(EF,A0,B1)
#define LV_SYMBOL_GLYPH_LAST   0xF831
#define SYMBOL_DUMMY           _SYMBOL_VALUE3(EF,A3,BF)       /*Invalid symbol at (U+F831). If written before a string then `lv_img` will show it as a label*/
#endif

#define _SYMBOL_VALUE1(x) (0x ## x)
#define _SYMBOL_VALUE3(x, y, z) (0x ## z ## y ## x)
#define _SYMBOL_NUMSTR(sym) LV_ ## sym ## _NUMSTR = sym

enum
{
    _SYMBOL_NUMSTR(SYMBOL_AUDIO),
    _SYMBOL_NUMSTR(SYMBOL_VIDEO),
    _SYMBOL_NUMSTR(SYMBOL_LIST),
    _SYMBOL_NUMSTR(SYMBOL_OK),
    _SYMBOL_NUMSTR(SYMBOL_CLOSE),
    _SYMBOL_NUMSTR(SYMBOL_POWER),
    _SYMBOL_NUMSTR(SYMBOL_SETTINGS),
    _SYMBOL_NUMSTR(SYMBOL_TRASH),
    _SYMBOL_NUMSTR(SYMBOL_HOME),
    _SYMBOL_NUMSTR(SYMBOL_DOWNLOAD),
    _SYMBOL_NUMSTR(SYMBOL_DRIVE),
    _SYMBOL_NUMSTR(SYMBOL_REFRESH),
    _SYMBOL_NUMSTR(SYMBOL_MUTE),
    _SYMBOL_NUMSTR(SYMBOL_VOLUME_MID),
    _SYMBOL_NUMSTR(SYMBOL_VOLUME_MAX),
    _SYMBOL_NUMSTR(SYMBOL_IMAGE),
    _SYMBOL_NUMSTR(SYMBOL_EDIT),
    _SYMBOL_NUMSTR(SYMBOL_PREV),
    _SYMBOL_NUMSTR(SYMBOL_PLAY),
    _SYMBOL_NUMSTR(SYMBOL_PAUSE),
    _SYMBOL_NUMSTR(SYMBOL_STOP),
    _SYMBOL_NUMSTR(SYMBOL_NEXT),
    _SYMBOL_NUMSTR(SYMBOL_EJECT),
    _SYMBOL_NUMSTR(SYMBOL_LEFT),
    _SYMBOL_NUMSTR(SYMBOL_RIGHT),
    _SYMBOL_NUMSTR(SYMBOL_PLUS),
    _SYMBOL_NUMSTR(SYMBOL_MINUS),
    _SYMBOL_NUMSTR(SYMBOL_WARNING),
    _SYMBOL_NUMSTR(SYMBOL_SHUFFLE),
    _SYMBOL_NUMSTR(SYMBOL_UP),
    _SYMBOL_NUMSTR(SYMBOL_DOWN),
    _SYMBOL_NUMSTR(SYMBOL_LOOP),
    _SYMBOL_NUMSTR(SYMBOL_DIRECTORY),
    _SYMBOL_NUMSTR(SYMBOL_UPLOAD),
    _SYMBOL_NUMSTR(SYMBOL_CALL),
    _SYMBOL_NUMSTR(SYMBOL_CUT),
    _SYMBOL_NUMSTR(SYMBOL_COPY),
    _SYMBOL_NUMSTR(SYMBOL_SAVE),
    _SYMBOL_NUMSTR(SYMBOL_CHARGE),
    _SYMBOL_NUMSTR(SYMBOL_BELL),
    _SYMBOL_NUMSTR(SYMBOL_KEYBOARD),
    _SYMBOL_NUMSTR(SYMBOL_GPS),
    _SYMBOL_NUMSTR(SYMBOL_FILE),
    _SYMBOL_NUMSTR(SYMBOL_WIFI),
    _SYMBOL_NUMSTR(SYMBOL_BATTERY_FULL),
    _SYMBOL_NUMSTR(SYMBOL_BATTERY_3),
    _SYMBOL_NUMSTR(SYMBOL_BATTERY_2),
    _SYMBOL_NUMSTR(SYMBOL_BATTERY_1),
    _SYMBOL_NUMSTR(SYMBOL_BATTERY_EMPTY),
    _SYMBOL_NUMSTR(SYMBOL_BLUETOOTH),
    _SYMBOL_NUMSTR(SYMBOL_DUMMY),
};

#undef _SYMBOL_VALUE1
#undef _SYMBOL_VALUE3

#define _SYMBOL_STR_(x) #x
#define _SYMBOL_STR(x) _SYMBOL_STR_(x)
#define _SYMBOL_CHAR(c) \x ## c
#define _SYMBOL_VALUE1(x) _SYMBOL_STR(_SYMBOL_CHAR(x))
#define _SYMBOL_VALUE3(x, y, z) _SYMBOL_STR(_SYMBOL_CHAR(x)_SYMBOL_CHAR(y)_SYMBOL_CHAR(z))

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*LV_SYMBOL_DEF_H*/

/* lv_font.h
 * Defines font metadata and glyph lookup used when measuring and drawing text.
 */
/**
 * @file lv_font.h
 *
 */

#ifndef LV_FONT_H
#define LV_FONT_H

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
#include <stddef.h>
#include <stdbool.h>


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct
{
    uint32_t w_px         :8;
    uint32_t glyph_index  :24;
} lv_font_glyph_dsc_t;

typedef struct
{
    uint32_t unicode         :21;
    uint32_t glyph_dsc_index :11;
} lv_font_unicode_map_t;

typedef struct _lv_font_struct
{
    uint32_t unicode_first;
    uint32_t unicode_last;
    const uint8_t * glyph_bitmap;
    const lv_font_glyph_dsc_t * glyph_dsc;
    const uint32_t * unicode_list;
    const uint8_t * (*get_bitmap)(const struct _lv_font_struct *,uint32_t);     /*Get a glyph's  bitmap from a font*/
    int16_t (*get_width)(const struct _lv_font_struct *,uint32_t);        /*Get a glyph's with with a given font*/
    struct _lv_font_struct * next_page;    /*Pointer to a font extension*/
    uint32_t h_px       :8;
    uint32_t bpp        :4;                /*Bit per pixel: 1, 2 or 4*/
    uint32_t monospace  :8;                /*Fix width (0: normal width)*/
    uint16_t glyph_cnt;                    /*Number of glyphs (letters) in the font*/
} lv_font_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the fonts
 */
void lv_font_init(void);

/**
 * Add a font to an other to extend the character set.
 * @param child the font to add
 * @param parent this font will be extended. Using it later will contain the characters from `child`
 */
void lv_font_add(lv_font_t *child, lv_font_t *parent);

/**
 * Remove a font from a character set.
 * @param child the font to remove
 * @param parent remove `child` from here
 */
void lv_font_remove(lv_font_t * child, lv_font_t * parent);

/**
 * Tells if font which contains `letter` is monospace or not
 * @param font_p point to font
 * @param letter an UNICODE character code
 * @return true: the letter is monospace; false not monospace
 */
bool lv_font_is_monospace(const lv_font_t * font_p, uint32_t letter);

/**
 * Return with the bitmap of a font.
 * @param font_p pointer to a font
 * @param letter an UNICODE character code
 * @return  pointer to the bitmap of the letter
 */
const uint8_t * lv_font_get_bitmap(const lv_font_t * font_p, uint32_t letter);

/**
 * Get the width of a letter in a font. If `monospace` is set then return with it.
 * @param font_p pointer to a font
 * @param letter an UNICODE character code
 * @return the width of a letter
 */
uint8_t lv_font_get_width(const lv_font_t * font_p, uint32_t letter);


/**
 * Get the width of the letter without overwriting it with the `monospace` attribute
 * @param font_p pointer to a font
 * @param letter an UNICODE character code
 * @return the width of a letter
 */
uint8_t lv_font_get_real_width(const lv_font_t * font_p, uint32_t letter);

/**
 * Get the height of a font
 * @param font_p pointer to a font
 * @return the height of a font
 */
static inline uint8_t lv_font_get_height(const lv_font_t * font_p)
{
    return font_p->h_px;
}

/**
 * Get the bit-per-pixel of font
 * @param font pointer to font
 * @param letter a letter from font (font extensions can have different bpp)
 * @return bpp of the font (or font extension)
 */
uint8_t lv_font_get_bpp(const lv_font_t * font, uint32_t letter);

/**
 * Generic bitmap get function used in 'font->get_bitmap' when the font contains all characters in the range
 * @param font pointer to font
 * @param unicode_letter an unicode letter which bitmap should be get
 * @return pointer to the bitmap or NULL if not found
 */
const uint8_t * lv_font_get_bitmap_continuous(const lv_font_t * font, uint32_t unicode_letter);

/**
 * Generic bitmap get function used in 'font->get_bitmap' when the font NOT contains all characters in the range (sparse)
 * @param font pointer to font
 * @param unicode_letter an unicode letter which bitmap should be get
 * @return pointer to the bitmap or NULL if not found
 */
const uint8_t * lv_font_get_bitmap_sparse(const lv_font_t * font, uint32_t unicode_letter);
/**
 * Generic glyph width get function used in 'font->get_width' when the font contains all characters in the range
 * @param font pointer to font
 * @param unicode_letter an unicode letter which width should be get
 * @return width of the gylph or -1 if not found
 */
int16_t lv_font_get_width_continuous(const lv_font_t * font, uint32_t unicode_letter);

/**
 * Generic glyph width get function used in 'font->get_bitmap' when the font NOT contains all characters in the range (sparse)
 * @param font pointer to font
 * @param unicode_letter an unicode letter which width should be get
 * @return width of the glyph or -1 if not found
 */
int16_t lv_font_get_width_sparse(const lv_font_t * font, uint32_t unicode_letter);

/**********************
 *      MACROS
 **********************/

#define LV_FONT_DECLARE(font_name) extern lv_font_t font_name


/**********************
 * ADD BUILT IN FONTS
 **********************/

/*Declare the custom (user defined) fonts*/
#ifdef LV_FONT_CUSTOM_DECLARE
LV_FONT_CUSTOM_DECLARE
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*USE_FONT*/

/* lv_log.h
 * Defines diagnostic logging levels and callbacks.
 */
/**
 * @file lv_log.h
 *
 */

#ifndef LV_LOG_H
#define LV_LOG_H

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

/*********************
 *      DEFINES
 *********************/

/*Possible log level. For compatibility declare it independently from `USE_LV_LOG`*/

#define LV_LOG_LEVEL_TRACE 0     /*A lot of logs to give detailed information*/
#define LV_LOG_LEVEL_INFO  1     /*Log important events*/
#define LV_LOG_LEVEL_WARN  2     /*Log if something unwanted happened but didn't caused problem*/
#define LV_LOG_LEVEL_ERROR 3     /*Only critical issue, when the system may fail*/
#define _LV_LOG_LEVEL_NUM  4

typedef int8_t lv_log_level_t;

#if USE_LV_LOG
/**********************
 *      TYPEDEFS
 **********************/


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Register custom print (or anything else) function to call when log is added
 * @param f a function pointer:
 *          `void my_print (lv_log_level_t level, const char * file, uint32_t line, const char * dsc)`
 */
void lv_log_register_print(void f(lv_log_level_t, const char *, uint32_t,  const char *));

/**
 * Add a log
 * @param level the level of log. (From `lv_log_level_t` enum)
 * @param file name of the file when the log added
 * @param line line number in the source code where the log added
 * @param dsc description of the log
 */
void lv_log_add(lv_log_level_t level, const char * file, int line, const char * dsc);

/**********************
 *      MACROS
 **********************/

#define LV_LOG_TRACE(dsc)   lv_log_add(LV_LOG_LEVEL_TRACE, __FILE__, __LINE__, dsc);
#define LV_LOG_INFO(dsc)    lv_log_add(LV_LOG_LEVEL_INFO, __FILE__, __LINE__, dsc);
#define LV_LOG_WARN(dsc)    lv_log_add(LV_LOG_LEVEL_WARN, __FILE__, __LINE__, dsc);
#define LV_LOG_ERROR(dsc)   lv_log_add(LV_LOG_LEVEL_ERROR, __FILE__, __LINE__, dsc);

#else /*USE_LV_LOG*/

/*Do nothing if `USE_LV_LOG  0`*/
#define lv_log_add(level, file, line, dsc) {;}
#define LV_LOG_TRACE(dsc) {;}
#define LV_LOG_INFO(dsc) {;}
#define LV_LOG_WARN(dsc) {;}
#define LV_LOG_ERROR(dsc) {;}
#endif /*USE_LV_LOG*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_LOG_H*/

/* lv_mem.h
 * Provides LVGL memory allocation and bookkeeping.
 */
/**
 * @file lv_mem.h
 *
 */

#ifndef LV_MEM_H
#define LV_MEM_H

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
#include <stddef.h>

/*********************
 *      DEFINES
 *********************/
// Check windows
#ifdef __WIN64
# define LV_MEM_ENV64
#endif

// Check GCC
#ifdef __GNUC__
# if defined(__x86_64__) || defined(__ppc64__)
#   define LV_MEM_ENV64
# endif
#endif

/**********************
 *      TYPEDEFS
 **********************/

typedef struct
{
    uint32_t total_size;
    uint32_t free_cnt;
    uint32_t free_size;
    uint32_t free_biggest_size;
    uint32_t used_cnt;
    uint8_t used_pct;
    uint8_t frag_pct;
} lv_mem_monitor_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**
 * Initiaize the dyn_mem module (work memory and other variables)
 */
void lv_mem_init(void);

/**
 * Allocate a memory dynamically
 * @param size size of the memory to allocate in bytes
 * @return pointer to the allocated memory
 */
void * lv_mem_alloc(uint32_t size);

/**
 * Free an allocated data
 * @param data pointer to an allocated memory
 */
void lv_mem_free(const void * data);

/**
 * Reallocate a memory with a new size. The old content will be kept.
 * @param data pointer to an allocated memory.
 * Its content will be copied to the new memory block and freed
 * @param new_size the desired new size in byte
 * @return pointer to the new memory
 */
void * lv_mem_realloc(void * data_p, uint32_t new_size);

/**
 * Join the adjacent free memory blocks
 */
void lv_mem_defrag(void);

/**
 * Give information about the work memory of dynamic allocation
 * @param mon_p pointer to a dm_mon_p variable,
 *              the result of the analysis will be stored here
 */
void lv_mem_monitor(lv_mem_monitor_t * mon_p);

/**
 * Give the size of an allocated memory
 * @param data pointer to an allocated memory
 * @return the size of data memory in bytes
 */
uint32_t lv_mem_get_size(const void * data);


/**********************
 *      MACROS
 **********************/

/**
 * Halt on NULL pointer
 * p pointer to a memory
 */
#if USE_LV_LOG == 0
# define  lv_mem_assert(p) {if(p == NULL) while(1); }
#else
# define  lv_mem_assert(p) {if(p == NULL) {LV_LOG_ERROR("Out of memory!"); while(1); }}
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_MEM_H*/

/* lv_fs.h
 * Defines file and directory operations through registered filesystem drivers.
 */
/**
 * @file lv_fs.h
 *
 */

#ifndef LV_FS_H
#define LV_FS_H

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

#if USE_LV_FILESYSTEM

#include <stdint.h>
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/
#define LV_FS_MAX_FN_LENGTH  64

/**********************
 *      TYPEDEFS
 **********************/
enum
{
    LV_FS_RES_OK = 0,
    LV_FS_RES_HW_ERR,      /*Low level hardware error*/
    LV_FS_RES_FS_ERR,      /*Error in the file system structure */
    LV_FS_RES_NOT_EX,      /*Driver, file or directory is not exists*/
    LV_FS_RES_FULL,        /*Disk full*/
    LV_FS_RES_LOCKED,      /*The file is already opened*/
    LV_FS_RES_DENIED,      /*Access denied. Check 'fs_open' modes and write protect*/
    LV_FS_RES_BUSY,        /*The file system now can't handle it, try later*/
    LV_FS_RES_TOUT,        /*Process time outed*/
    LV_FS_RES_NOT_IMP,     /*Requested function is not implemented*/
    LV_FS_RES_OUT_OF_MEM,  /*Not enough memory for an internal operation*/
    LV_FS_RES_INV_PARAM,   /*Invalid parameter among arguments*/
    LV_FS_RES_UNKNOWN,     /*Other unknown error*/
};
typedef uint8_t lv_fs_res_t;

struct __lv_fs_drv_t;

typedef struct
{
    void * file_d;
    struct __lv_fs_drv_t* drv;
} lv_fs_file_t;


typedef struct
{
    void * dir_d;
    struct __lv_fs_drv_t * drv;
} lv_fs_dir_t;

enum
{
    LV_FS_MODE_WR = 0x01,
    LV_FS_MODE_RD = 0x02,
};
typedef uint8_t lv_fs_mode_t;

typedef struct __lv_fs_drv_t
{
    char letter;
    uint16_t file_size;
    uint16_t rddir_size;
    bool (*ready) (void);

    lv_fs_res_t (*open) (void * file_p, const char * path, lv_fs_mode_t mode);
    lv_fs_res_t (*close) (void * file_p);
    lv_fs_res_t (*remove) (const char * fn);
    lv_fs_res_t (*read) (void * file_p, void * buf, uint32_t btr, uint32_t * br);
    lv_fs_res_t (*write) (void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
    lv_fs_res_t (*seek) (void * file_p, uint32_t pos);
    lv_fs_res_t (*tell) (void * file_p, uint32_t * pos_p);
    lv_fs_res_t (*trunc) (void * file_p);
    lv_fs_res_t (*size) (void * file_p, uint32_t * size_p);
    lv_fs_res_t (*rename) (const char * oldname, const char * newname);
    lv_fs_res_t (*free) (uint32_t * total_p, uint32_t * free_p);

    lv_fs_res_t (*dir_open) (void * rddir_p, const char * path);
    lv_fs_res_t (*dir_read) (void * rddir_p, char * fn);
    lv_fs_res_t (*dir_close) (void * rddir_p);
} lv_fs_drv_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the File system interface
 */
void lv_fs_init(void);

/**
 * Add a new drive
 * @param drv_p pointer to an lv_fs_drv_t structure which is inited with the
 * corresponding function pointers. The data will be copied so the variable can be local.
 */
void lv_fs_add_drv(lv_fs_drv_t * drv_p);

/**
 * Test if a drive is rady or not. If the `ready` function was not initialized `true` will be returned.
 * @param letter letter of the drive
 * @return true: drive is ready; false: drive is not ready
 */
bool lv_fs_is_ready(char letter);

/**
 * Open a file
 * @param file_p pointer to a lv_fs_file_t variable
 * @param path path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_open (lv_fs_file_t * file_p, const char * path, lv_fs_mode_t mode);

/**
 * Close an already opened file
 * @param file_p pointer to a lv_fs_file_t variable
 * @return  LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_close (lv_fs_file_t * file_p);

/**
 * Delete a file
 * @param path path of the file to delete
 * @return  LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_remove (const char * path);

/**
 * Read from a file
 * @param file_p pointer to a lv_fs_file_t variable
 * @param buf pointer to a buffer where the read bytes are stored
 * @param btr Bytes To Read
 * @param br the number of real read bytes (Bytes Read). NULL if unused.
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_read (lv_fs_file_t * file_p, void * buf, uint32_t btr, uint32_t * br);

/**
 * Write into a file
 * @param file_p pointer to a lv_fs_file_t variable
 * @param buf pointer to a buffer with the bytes to write
 * @param btr Bytes To Write
 * @param br the number of real written bytes (Bytes Written). NULL if unused.
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_write (lv_fs_file_t * file_p, const void * buf, uint32_t btw, uint32_t * bw);

/**
 * Set the position of the 'cursor' (read write pointer) in a file
 * @param file_p pointer to a lv_fs_file_t variable
 * @param pos the new position expressed in bytes index (0: start of file)
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_seek (lv_fs_file_t * file_p, uint32_t pos);

/**
 * Give the position of the read write pointer
 * @param file_p pointer to a lv_fs_file_t variable
 * @param pos_p pointer to store the position of the read write pointer
 * @return LV_FS_RES_OK or any error from 'fs_res_t'
 */
lv_fs_res_t lv_fs_tell (lv_fs_file_t * file_p, uint32_t  * pos);

/**
 * Truncate the file size to the current position of the read write pointer
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_fs_open )
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_trunc (lv_fs_file_t * file_p);

/**
 * Give the size of a file bytes
 * @param file_p pointer to a lv_fs_file_t variable
 * @param size pointer to a variable to store the size
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_size (lv_fs_file_t * file_p, uint32_t * size);

/**
 * Rename a file
 * @param oldname path to the file
 * @param newname path with the new name
 * @return LV_FS_RES_OK or any error from 'fs_res_t'
 */
lv_fs_res_t lv_fs_rename (const char * oldname, const char * newname);

/**
 * Initialize a 'fs_dir_t' variable for directory reading
 * @param rddir_p pointer to a 'fs_read_dir_t' variable
 * @param path path to a directory
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_dir_open(lv_fs_dir_t * rddir_p, const char * path);

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param rddir_p pointer to an initialized 'fs_rdir_t' variable
 * @param fn pointer to a buffer to store the filename
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_dir_read (lv_fs_dir_t * rddir_p, char * fn);

/**
 * Close the directory reading
 * @param rddir_p pointer to an initialized 'fs_dir_t' variable
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_dir_close (lv_fs_dir_t * rddir_p);

/**
 * Get the free and total size of a driver in kB
 * @param letter the driver letter
 * @param total_p pointer to store the total size [kB]
 * @param free_p pointer to store the free size [kB]
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_fs_free (char letter, uint32_t * total_p, uint32_t * free_p);

/**
 * Fill a buffer with the letters of existing drivers
 * @param buf buffer to store the letters ('\0' added after the last letter)
 * @return the buffer
 */
char *  lv_fs_get_letters(char * buf);

/**
 * Return with the extension of the filename
 * @param fn string with a filename
 * @return pointer to the beginning extension or empty string if no extension
 */
const char * lv_fs_get_ext(const char * fn);

/**
 * Step up one level
 * @param path pointer to a file name
 * @return the truncated file name
 */
char * lv_fs_up(char * path);

/**
 * Get the last element of a path (e.g. U:/folder/file -> file)
 * @param buf buffer to store the letters ('\0' added after the last letter)
 * @return pointer to the beginning of the last element in the path
 */
const char * lv_fs_get_last(const char * path);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_FILESYSTEM*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_FS_H*/

/* lv_ll.h
 * Defines doubly linked lists used in LVGL internals.
 */
/**
 * @file lv_ll.c
 * Handle linked lists. The nodes are dynamically allocated by the 'lv_mem' module.
 */

#ifndef LV_LL_H
#define LV_LL_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stddef.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Dummy type to make handling easier*/
typedef uint8_t lv_ll_node_t;

/*Description of a linked list*/
typedef struct
{
    uint32_t n_size;
    lv_ll_node_t* head;
    lv_ll_node_t* tail;
} lv_ll_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize linked list
 * @param ll_dsc pointer to ll_dsc variable
 * @param node_size the size of 1 node in bytes
 */
void lv_ll_init(lv_ll_t * ll_p, uint32_t node_size);

/**
 * Add a new head to a linked list
 * @param ll_p pointer to linked list
 * @return pointer to the new head
 */
void * lv_ll_ins_head(lv_ll_t * ll_p);

/**
 * Insert a new node in front of the n_act node
 * @param ll_p pointer to linked list
 * @param n_act pointer a node
 * @return pointer to the new head
 */
void * lv_ll_ins_prev(lv_ll_t * ll_p, void * n_act);

/**
 * Add a new tail to a linked list
 * @param ll_p pointer to linked list
 * @return pointer to the new tail
 */
void * lv_ll_ins_tail(lv_ll_t * ll_p);

/**
 * Remove the node 'node_p' from 'll_p' linked list.
 * It does not free the the memory of node.
 * @param ll_p pointer to the linked list of 'node_p'
 * @param node_p pointer to node in 'll_p' linked list
 */
void lv_ll_rem(lv_ll_t  * ll_p, void * node_p);

/**
 * Remove and free all elements from a linked list. The list remain valid but become empty.
 * @param ll_p pointer to linked list
 */
void lv_ll_clear(lv_ll_t * ll_p);

/**
 * Move a node to a new linked list
 * @param ll_ori_p pointer to the original (old) linked list
 * @param ll_new_p pointer to the new linked list
 * @param node pointer to a node
 */
void lv_ll_chg_list(lv_ll_t * ll_ori_p, lv_ll_t * ll_new_p, void * node);

/**
 * Return with head node of the linked list
 * @param ll_p pointer to linked list
 * @return pointer to the head of 'll_p'
 */
void * lv_ll_get_head(const lv_ll_t * ll_p);

/**
 * Return with tail node of the linked list
 * @param ll_p pointer to linked list
 * @return pointer to the head of 'll_p'
 */
void * lv_ll_get_tail(const lv_ll_t * ll_p);

/**
 * Return with the pointer of the next node after 'n_act'
 * @param ll_p pointer to linked list
 * @param n_act pointer a node
 * @return pointer to the next node
 */
void * lv_ll_get_next(const lv_ll_t * ll_p, const void * n_act);

/**
 * Return with the pointer of the previous node after 'n_act'
 * @param ll_p pointer to linked list
 * @param n_act pointer a node
 * @return pointer to the previous node
 */
void * lv_ll_get_prev(const lv_ll_t * ll_p, const void * n_act);

/**
 * Move a nodw before an other node in the same linked list
 * @param ll_p pointer to a linked list
 * @param n_act pointer to node to move
 * @param n_after pointer to a node which should be after `n_act`
 */
void lv_ll_move_before(lv_ll_t * ll_p, void * n_act, void * n_after);

/**********************
 *      MACROS
 **********************/

#define LL_READ(list, i) for(i = lv_ll_get_head(&list); i != NULL; i = lv_ll_get_next(&list, i))

#define LL_READ_BACK(list, i) for(i = lv_ll_get_tail(&list); i != NULL; i = lv_ll_get_prev(&list, i))

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

/* lv_gc.h
 * Supports runtimes that track LVGL allocations with garbage collection.
 */
/**
 * @file lv_gc.h
 *
 */

#ifndef LV_GC_H
#define LV_GC_H

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

#define LV_GC_ROOTS(prefix) \
    prefix lv_ll_t _lv_task_ll;      /*Linked list to store the lv_tasks*/ \
    prefix lv_ll_t _lv_scr_ll;          /*Linked list of screens*/ \
    prefix lv_ll_t _lv_drv_ll;\
    prefix lv_ll_t _lv_file_ll;\
    prefix lv_ll_t _lv_anim_ll;\
    prefix void * _lv_def_scr;\
    prefix void * _lv_act_scr;\
    prefix void * _lv_top_layer;\
    prefix void * _lv_sys_layer;\
    prefix void * _lv_task_act;\
    prefix void * _lv_indev_list;\
    prefix void * _lv_disp_list;\


#define LV_NO_PREFIX
#define LV_ROOTS LV_GC_ROOTS(LV_NO_PREFIX)

#if LV_ENABLE_GC == 1
#   if LV_MEM_CUSTOM != 1
#       error "GC requires CUSTOM_MEM"
#   endif /* LV_MEM_CUSTOM */
#else /* LV_ENABLE_GC */
#   define LV_GC_ROOT(x) x
    LV_GC_ROOTS(extern)
#endif /* LV_ENABLE_GC */


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

#endif /*LV_GC_H*/

/* lv_math.h
 * Provides integer math and trigonometry helpers.
 */
/**
 * @file math_base.h
 *
 */

#ifndef LV_MATH_H
#define LV_MATH_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/
#define LV_MATH_MIN(a,b) ((a) < (b) ? (a) : (b))
#define LV_MATH_MAX(a,b) ((a) > (b) ? (a) : (b))
#define LV_MATH_ABS(x) ((x) > 0 ? (x) : (-(x)))

#define LV_TRIGO_SIN_MAX    32767
#define LV_TRIGO_SHIFT      15      /* >> LV_TRIGO_SHIFT to normalize*/

#define LV_BEZIER_VAL_MAX       1024    /*Max time in Bezier functions (not [0..1] to use integers) */
#define LV_BEZIER_VAL_SHIFT     10      /*log2(LV_BEZIER_VAL_MAX): used to normalize up scaled values*/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * Convert a number to string
 * @param num a number
 * @param buf pointer to a `char` buffer. The result will be stored here (max 10 elements)
 * @return same as `buf` (just for convenience)
 */
char * lv_math_num_to_str(int32_t num, char * buf);

/**
 * Return with sinus of an angle
 * @param angle
 * @return sinus of 'angle'. sin(-90) = -32767, sin(90) = 32767
 */
int16_t lv_trigo_sin(int16_t angle);

/**
 * Calculate a value of a Cubic Bezier function.
 * @param t time in range of [0..LV_BEZIER_VAL_MAX]
 * @param u0 start values in range of [0..LV_BEZIER_VAL_MAX]
 * @param u1 control value 1 values in range of [0..LV_BEZIER_VAL_MAX]
 * @param u2 control value 2 in range of [0..LV_BEZIER_VAL_MAX]
 * @param u3 end values in range of [0..LV_BEZIER_VAL_MAX]
 * @return the value calculated from the given parameters in range of [0..LV_BEZIER_VAL_MAX]
 */
int32_t lv_bezier3(uint32_t t, int32_t u0, int32_t u1, int32_t u2, int32_t u3);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

/* lv_task.h
 * Schedules recurring LVGL callbacks with priorities and periods.
 */
/**
 * @file lv_task.c
 * An 'lv_task'  is a void (*fp) (void* param) type function which will be called periodically.
 * A priority (5 levels + disable) can be assigned to lv_tasks.
 */

#ifndef LV_TASK_H
#define LV_TASK_H

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
#ifndef LV_ATTRIBUTE_TASK_HANDLER
#define LV_ATTRIBUTE_TASK_HANDLER
#endif
/**********************
 *      TYPEDEFS
 **********************/
/**
 * Possible priorities for lv_tasks
 */
enum
{
    LV_TASK_PRIO_OFF = 0,
    LV_TASK_PRIO_LOWEST,
    LV_TASK_PRIO_LOW,
    LV_TASK_PRIO_MID,
    LV_TASK_PRIO_HIGH,
    LV_TASK_PRIO_HIGHEST,
    LV_TASK_PRIO_NUM,
};
typedef uint8_t lv_task_prio_t;

/**
 * Descriptor of a lv_task
 */
typedef struct
{
    uint32_t period;
    uint32_t last_run;
    void (*task) (void*);
    void * param;
    uint8_t prio:3;
    uint8_t once:1;
} lv_task_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Init the lv_task module
 */
void lv_task_init(void);

/**
 * Call it  periodically to handle lv_tasks.
 */
LV_ATTRIBUTE_TASK_HANDLER void lv_task_handler(void);

/**
 * Create a new lv_task
 * @param task a function which is the task itself
 * @param period call period in ms unit
 * @param prio priority of the task (LV_TASK_PRIO_OFF means the task is stopped)
 * @param param free parameter
 * @return pointer to the new task
 */
lv_task_t* lv_task_create(void (*task) (void *), uint32_t period, lv_task_prio_t prio, void * param);

/**
 * Delete a lv_task
 * @param lv_task_p pointer to task created by lv_task_p
 */
void lv_task_del(lv_task_t* lv_task_p);

/**
 * Set new priority for a lv_task
 * @param lv_task_p pointer to a lv_task
 * @param prio the new priority
 */
void lv_task_set_prio(lv_task_t* lv_task_p, lv_task_prio_t prio);

/**
 * Set new period for a lv_task
 * @param lv_task_p pointer to a lv_task
 * @param period the new period
 */
void lv_task_set_period(lv_task_t* lv_task_p, uint32_t period);

/**
 * Make a lv_task ready. It will not wait its period.
 * @param lv_task_p pointer to a lv_task.
 */
void lv_task_ready(lv_task_t* lv_task_p);


/**
 * Delete the lv_task after one call
 * @param lv_task_p pointer to a lv_task.
 */
void lv_task_once(lv_task_t * lv_task_p);

/**
 * Reset a lv_task.
 * It will be called the previously set period milliseconds later.
 * @param lv_task_p pointer to a lv_task.
 */
void lv_task_reset(lv_task_t* lv_task_p);

/**
 * Enable or disable the whole  lv_task handling
 * @param en: true: lv_task handling is running, false: lv_task handling is suspended
 */
void lv_task_enable(bool en);

/**
 * Get idle percentage
 * @return the lv_task idle in percentage
 */
uint8_t lv_task_get_idle(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

/* lv_templ.h
 * Skeleton for adding a new LVGL utility header.
 */
/**
 * @file lv_templ.h
 *
 */

#ifndef LV_TEMPL_H
#define LV_TEMPL_H

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

#endif /*LV_TEMPL_H*/

/* lv_txt.h
 * Measures, breaks, and decodes text for labels and editable widgets.
 */
/**
 * @file lv_text.h
 *
 */

#ifndef LV_TXT_H
#define LV_TXT_H

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

#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/
#define LV_TXT_COLOR_CMD  "#"

/**********************
 *      TYPEDEFS
 **********************/
enum
{
    LV_TXT_FLAG_NONE =     0x00,
    LV_TXT_FLAG_RECOLOR =  0x01,   /*Enable parsing of recolor command*/
    LV_TXT_FLAG_EXPAND =   0x02,   /*Ignore width to avoid automatic word wrapping*/
    LV_TXT_FLAG_CENTER =   0x04,   /*Align the text to the middle*/
    LV_TXT_FLAG_RIGHT  =   0x08,   /*Align the text to the right*/
};
typedef uint8_t lv_txt_flag_t;

enum
{
    LV_TXT_CMD_STATE_WAIT,      /*Waiting for command*/
    LV_TXT_CMD_STATE_PAR,       /*Processing the parameter*/
    LV_TXT_CMD_STATE_IN,        /*Processing the command*/
};
typedef uint8_t lv_txt_cmd_state_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Get size of a text
 * @param size_res pointer to a 'point_t' variable to store the result
 * @param text pointer to a text
 * @param font pinter to font of the text
 * @param letter_space letter space of the text
 * @param line_space line space of the text
 * @param flags settings for the text from 'txt_flag_t' enum
 * @param max_width max with of the text (break the lines to fit this size) Set CORD_MAX to avoid line breaks
 */
void lv_txt_get_size(lv_point_t * size_res, const char * text, const lv_font_t * font,
                     lv_coord_t letter_space, lv_coord_t line_space, lv_coord_t max_width, lv_txt_flag_t flag);

/**
 * Get the next line of text. Check line length and break chars too.
 * @param txt a '\0' terminated string
 * @param font pointer to a font
 * @param letter_space letter space
 * @param max_width max with of the text (break the lines to fit this size) Set CORD_MAX to avoid line breaks
 * @param flags settings for the text from 'txt_flag_type' enum
 * @return the index of the first char of the new line (in byte index not letter index. With UTF-8 they are different)
 */
uint16_t lv_txt_get_next_line(const char * txt, const lv_font_t * font,
                              lv_coord_t letter_space, lv_coord_t max_width, lv_txt_flag_t flag);

/**
 * Give the length of a text with a given font
 * @param txt a '\0' terminate string
 * @param length length of 'txt' in byte count and not characters (Á is 1 character but 2 bytes in UTF-8)
 * @param font pointer to a font
 * @param letter_space letter space
 * @param flags settings for the text from 'txt_flag_t' enum
 * @return length of a char_num long text
 */
lv_coord_t lv_txt_get_width(const char * txt, uint16_t length,
                            const lv_font_t * font, lv_coord_t letter_space, lv_txt_flag_t flag);


/**
 * Check next character in a string and decide if te character is part of the command or not
 * @param state pointer to a txt_cmd_state_t variable which stores the current state of command processing
 * @param c the current character
 * @return true: the character is part of a command and should not be written,
 *         false: the character should be written
 */
bool lv_txt_is_cmd(lv_txt_cmd_state_t * state, uint32_t c);

/**
 * Insert a string into an other
 * @param txt_buf the original text (must be big enough for the result text)
 * @param pos position to insert (0: before the original text, 1: after the first char etc.)
 * @param ins_txt text to insert
 */
void lv_txt_ins(char * txt_buf, uint32_t pos, const char * ins_txt);

/**
 * Delete a part of a string
 * @param txt string to modify
 * @param pos position where to start the deleting (0: before the first char, 1: after the first char etc.)
 * @param len number of characters to delete
 */
void lv_txt_cut(char * txt, uint32_t pos, uint32_t len);

/***************************************************************
 *  GLOBAL FUNCTION POINTERS FOR CAHRACTER ENCODING INTERFACE
 ***************************************************************/

/**
 * Give the size of an encoded character
 * @param str pointer to a character in a string
 * @return length of the encoded character (1,2,3 ...). O in invalid
 */
extern uint8_t (*lv_txt_encoded_size)(const char *);


/**
 * Convert an Unicode letter to encoded
 * @param letter_uni an Unicode letter
 * @return Encoded character in Little Endian to be compatible with C chars (e.g. 'Á', 'Ü')
 */
extern uint32_t (*lv_txt_unicode_to_encoded)(uint32_t );

/**
 * Convert a wide character, e.g. 'Á' little endian to be compatible with the encoded format.
 * @param c a wide character
 * @return `c` in the encoded format
 */
extern uint32_t (*lv_txt_encoded_conv_wc) (uint32_t c);

/**
 * Decode the next encoded character from a string.
 * @param txt pointer to '\0' terminated string
 * @param i start index in 'txt' where to start.
 *                After the call it will point to the next encoded char in 'txt'.
 *                NULL to use txt[0] as index
 * @return the decoded Unicode character or 0 on invalid data code
 */
extern uint32_t (*lv_txt_encoded_next)(const char *, uint32_t * );

/**
 * Get the previous encoded character form a string.
 * @param txt pointer to '\0' terminated string
 * @param i_start index in 'txt' where to start. After the call it will point to the previous encoded char in 'txt'.
 * @return the decoded Unicode character or 0 on invalid data
 */
extern uint32_t (*lv_txt_encoded_prev)(const char *, uint32_t *);

/**
 * Convert a letter index (in an the encoded text) to byte index.
 * E.g. in UTF-8 "AÁRT" index of 'R' is 2 but start at byte 3 because 'Á' is 2 bytes long
 * @param txt a '\0' terminated UTF-8 string
 * @param enc_id letter index
 * @return byte index of the 'enc_id'th letter
 */
extern uint32_t (*lv_txt_encoded_get_byte_id)(const char *, uint32_t);

/**
 * Convert a byte index (in an encoded text) to character index.
 * E.g. in UTF-8 "AÁRT" index of 'R' is 2 but start at byte 3 because 'Á' is 2 bytes long
 * @param txt a '\0' terminated UTF-8 string
 * @param byte_id byte index
 * @return character index of the letter at 'byte_id'th position
 */
extern uint32_t (*lv_encoded_get_char_id)(const char *, uint32_t);

/**
 * Get the number of characters (and NOT bytes) in a string.
 * E.g. in UTF-8 "ÁBC" is 3 characters (but 4 bytes)
 * @param txt a '\0' terminated char string
 * @return number of characters
 */
extern uint32_t (*lv_txt_get_encoded_length)(const char *);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*USE_TXT*/

/* lv_ufs.h
 * Implements LVGL filesystem operations for files held in memory.
 */
/**
 * @file lv_ufs.h
 * Implementation of RAM file system which do NOT support directories.
 * The API is compatible with the lv_fs_int module.
 */

#ifndef LV_UFS_H
#define LV_UFS_H

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

#if USE_LV_FILESYSTEM

#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/
#define UFS_LETTER 'U'

/**********************
 *      TYPEDEFS
 **********************/
/*Description of a file entry */
typedef struct
{
    char * fn_d;
    void * data_d;
    uint32_t size;  /*Data length in bytes*/
    uint16_t oc;    /*Open Count*/
    uint8_t const_data :1;
} lv_ufs_ent_t;

/*File descriptor, used to handle opening an entry more times simultaneously
 Contains unique informations about the specific opening*/
typedef struct
{
    lv_ufs_ent_t* ent; /*Pointer to the entry*/
    uint32_t rwp;   /*Read Write Pointer*/
    uint8_t ar :1;  /*1: Access for read is enabled */
    uint8_t aw :1;  /*1: Access for write is enabled */
} lv_ufs_file_t;

/* Read directory descriptor.
 * It is used to to iterate through the entries in a directory*/
typedef struct
{
    lv_ufs_ent_t * last_ent;
} lv_ufs_dir_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a driver for ufs and initialize it.
 */
void lv_ufs_init(void);

/**
 * Give the state of the ufs
 * @return true if ufs is initialized and can be used else false
 */
bool lv_ufs_ready(void);

/**
 * Open a file in ufs
 * @param file_p pointer to a lv_ufs_file_t variable
 * @param fn name of the file. There are no directories so e.g. "myfile.txt"
 * @param mode element of 'fs_mode_t' enum or its 'OR' connection (e.g. FS_MODE_WR | FS_MODE_RD)
 * @return LV_FS_RES_OK: no error, the file is opened
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_open (void * file_p, const char * fn, lv_fs_mode_t mode);

/**
 * Create a file with a constant data
 * @param fn name of the file (directories are not supported)
 * @param const_p pointer to a constant data
 * @param len length of the data pointed by 'const_p' in bytes
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_create_const(const char * fn, const void * const_p, uint32_t len);

/**
 * Close an opened file
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_ufs_open)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_close (void * file_p);

/**
 * Remove a file. The file can not be opened.
 * @param fn '\0' terminated string
 * @return LV_FS_RES_OK: no error, the file is removed
 *         LV_FS_RES_DENIED: the file was opened, remove failed
 */
lv_fs_res_t lv_ufs_remove(const char * fn);

/**
 * Read data from an opened file
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_ufs_open )
 * @param buf pointer to a memory block where to store the read data
 * @param btr number of Bytes To Read
 * @param br the real number of read bytes (Byte Read)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_read (void * file_p, void * buf, uint32_t btr, uint32_t * br);

/**
 * Write data to an opened file
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_ufs_open)
 * @param buf pointer to a memory block which content will be written
 * @param btw the number Bytes To Write
 * @param bw The real number of written bytes (Byte Written)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_write (void * file_p, const void * buf, uint32_t btw, uint32_t * bw);

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_ufs_open )
 * @param pos the new position of read write pointer
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_seek (void * file_p, uint32_t pos);

/**
 * Give the position of the read write pointer
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_ufs_open )
 * @param pos_p pointer to to store the result
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_tell (void * file_p, uint32_t * pos_p);

/**
 * Truncate the file size to the current position of the read write pointer
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_ufs_open )
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_trunc (void * file_p);

/**
 * Give the size of the file in bytes
 * @param file_p file_p pointer to an 'ufs_file_t' variable. (opened with lv_ufs_open )
 * @param size_p pointer to store the size
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_size (void * file_p, uint32_t * size_p);

/**
 * Initialize a lv_ufs_read_dir_t variable to directory reading
 * @param rddir_p pointer to a 'ufs_read_dir_t' variable
 * @param path uFS doesn't support folders so it has to be ""
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_dir_open(void * rddir_p, const char * path);

/**
 * Read the next file name
 * @param dir_p pointer to an initialized 'ufs_read_dir_t' variable
 * @param fn pointer to buffer to sore the file name
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_dir_read(void * dir_p, char * fn);

/**
 * Close the directory reading
 * @param rddir_p pointer to an initialized 'ufs_read_dir_t' variable
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
lv_fs_res_t lv_ufs_dir_close(void * rddir_p);

/**
 * Give the size of a drive
 * @param total_p pointer to store the total size [kB]
 * @param free_p pointer to store the free site [kB]
 * @return LV_FS_RES_OK or any error from 'fs_res_t'
 */
lv_fs_res_t lv_ufs_free (uint32_t * total_p, uint32_t * free_p);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_FILESYSTEM*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

#endif /* PROS_DISPLAY_LV_MISC_H */
