/**
 * Base objects, screen management, input processing, styling, and refresh.
 * A widget starts as an object with a parent and a style. The core also
 * handles focus, input dispatch, and redrawing invalidated screen areas.
 * The sections retain their original LVGL 5.3 declarations.
 */
#ifndef PROS_DISPLAY_LV_CORE_H
#define PROS_DISPLAY_LV_CORE_H

/* lv_style.h
 * Defines reusable appearance settings such as color, padding, border, and font.
 */
/**
 * @file lv_style.h
 *
 */

#ifndef LV_STYLE_H
#define LV_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_fonts/lv_fonts.h"
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/
#define LV_RADIUS_CIRCLE  (LV_COORD_MAX)    /*A very big radius to always draw as circle*/

/**********************
 *      TYPEDEFS
 **********************/

/*Border types (Use 'OR'ed values)*/
enum
{
    LV_BORDER_NONE =     0x00,
    LV_BORDER_BOTTOM =   0x01,
    LV_BORDER_TOP =      0x02,
    LV_BORDER_LEFT =     0x04,
    LV_BORDER_RIGHT =    0x08,
    LV_BORDER_FULL =     0x0F,
    LV_BORDER_INTERNAL = 0x10,    /*FOR matrix-like objects (e.g. Button matrix)*/
};
typedef uint8_t lv_border_part_t;

/*Shadow types*/
enum
{
    LV_SHADOW_BOTTOM = 0,
    LV_SHADOW_FULL,
};
typedef uint8_t lv_shadow_type_t;

typedef struct
{
    uint8_t glass :1;           /*1: Do not inherit this style*/

    struct {
        lv_color_t main_color;
        lv_color_t grad_color;      /*`grad_color` will be removed in v6.0, use `aux_color` instead*/
        lv_coord_t radius;
        lv_opa_t opa;

        struct {
            lv_color_t color;
            lv_coord_t width;
            lv_border_part_t part;
            lv_opa_t opa;
        } border;

        struct {
            lv_color_t color;
            lv_coord_t width;
            lv_shadow_type_t type;
        } shadow;

        struct {
            lv_coord_t ver;
            lv_coord_t hor;
            lv_coord_t inner;
        } padding;

        uint8_t empty :1;   /*Transparent background (border still drawn)*/
    } body;


    struct {
        lv_color_t color;
        const lv_font_t * font;
        lv_coord_t letter_space;
        lv_coord_t line_space;
        lv_opa_t opa;
    } text;

    struct {
        lv_color_t color;
        lv_opa_t intense;
        lv_opa_t opa;
    } image;

    struct {
        lv_color_t color;
        lv_coord_t width;
        lv_opa_t opa;
        uint8_t rounded :1;     /*1: rounded line endings*/
    } line;
} lv_style_t;

#if USE_LV_ANIMATION
typedef struct {
    const lv_style_t * style_start; /*Pointer to the starting style*/
    const lv_style_t * style_end;   /*Pointer to the destination style*/
    lv_style_t * style_anim;        /*Pointer to a style to animate*/
    lv_anim_cb_t end_cb;            /*Call it when the animation is ready (NULL if unused)*/
    int16_t time;                   /*Animation time in ms*/
    int16_t act_time;               /*Current time in animation. Set to negative to make delay.*/
    uint16_t playback_pause;        /*Wait before play back*/
    uint16_t repeat_pause;          /*Wait before repeat*/
    uint8_t playback :1;            /*When the animation is ready play it back*/
    uint8_t repeat :1;              /*Repeat the animation infinitely*/
} lv_style_anim_t;

/* Example initialization
lv_style_anim_t a;
a.style_anim = &style_to_anim;
a.style_start = &style_1;
a.style_end = &style_2;
a.act_time = 0;
a.time = 1000;
a.playback = 0;
a.playback_pause = 0;
a.repeat = 0;
a.repeat_pause = 0;
a.end_cb = NULL;
lv_style_anim_create(&a);
 */
#endif

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 *  Init the basic styles
 */
void lv_style_init (void);

/**
 * Copy a style to an other
 * @param dest pointer to the destination style
 * @param src pointer to the source style
 */
void lv_style_copy(lv_style_t * dest, const lv_style_t * src);


/**
 * Mix two styles according to a given ratio
 * @param start start style
 * @param end end style
 * @param res store the result style here
 * @param ratio the ratio of mix [0..256]; 0: `start` style; 256: `end` style
 */
void lv_style_mix(const lv_style_t * start, const lv_style_t * end, lv_style_t * res, uint16_t ratio);

#if USE_LV_ANIMATION

/**
 * Create an animation from a pre-configured 'lv_style_anim_t' variable
 * @param anim pointer to a pre-configured 'lv_style_anim_t' variable (will be copied)
 * @return pointer to a descriptor. Really this variable will be animated. (Can be used in `lv_anim_del(dsc, NULL)`)
 */
void * lv_style_anim_create(lv_style_anim_t * anim);
#endif

/*************************
 *    GLOBAL VARIABLES
 *************************/
extern lv_style_t lv_style_scr;
extern lv_style_t lv_style_transp;
extern lv_style_t lv_style_transp_fit;
extern lv_style_t lv_style_transp_tight;
extern lv_style_t lv_style_plain;
extern lv_style_t lv_style_plain_color;
extern lv_style_t lv_style_pretty;
extern lv_style_t lv_style_pretty_color;
extern lv_style_t lv_style_btn_rel;
extern lv_style_t lv_style_btn_pr;
extern lv_style_t lv_style_btn_tgl_rel;
extern lv_style_t lv_style_btn_tgl_pr;
extern lv_style_t lv_style_btn_ina;

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_STYLE_H*/

/* lv_obj.h
 * Defines the base object, screen lifecycle, hierarchy, layout, signals, and callbacks.
 */
/**
 * @file lv_obj.h
 *
 */

#ifndef LV_OBJ_H
#define LV_OBJ_H

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

#include <stddef.h>
#include <stdbool.h>
#include "display/lv_hal/lv_hal.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/

/*Error check of lv_conf.h*/
#if LV_HOR_RES == 0 || LV_VER_RES == 0
#error "LittlevGL: LV_HOR_RES and LV_VER_RES must be greater than 0"
#endif

#if LV_ANTIALIAS > 1
#error "LittlevGL: LV_ANTIALIAS can be only 0 or 1"
#endif

#if LV_VDB_SIZE == 0 && LV_ANTIALIAS != 0
#error "LittlevGL: If LV_VDB_SIZE == 0 the anti-aliasing must be disabled"
#endif

#if LV_VDB_SIZE > 0 && LV_VDB_SIZE < LV_HOR_RES
#error "LittlevGL: Small Virtual Display Buffer (lv_conf.h: LV_VDB_SIZE >= LV_HOR_RES)"
#endif

#if LV_VDB_SIZE == 0 && USE_LV_REAL_DRAW == 0
#error "LittlevGL: If LV_VDB_SIZE = 0 Real drawing function are required (lv_conf.h: USE_LV_REAL_DRAW 1)"
#endif


#define LV_ANIM_IN              0x00    /*Animation to show an object. 'OR' it with lv_anim_builtin_t*/
#define LV_ANIM_OUT             0x80    /*Animation to hide an object. 'OR' it with lv_anim_builtin_t*/
#define LV_ANIM_DIR_MASK        0x80    /*ANIM_IN/ANIM_OUT mask*/

#define LV_MAX_ANCESTOR_NUM     8

/**********************
 *      TYPEDEFS
 **********************/

struct _lv_obj_t;

enum
{
    LV_DESIGN_DRAW_MAIN,
    LV_DESIGN_DRAW_POST,
    LV_DESIGN_COVER_CHK,
};
typedef uint8_t lv_design_mode_t;

typedef bool (* lv_design_func_t) (struct _lv_obj_t * obj, const lv_area_t * mask_p, lv_design_mode_t mode);

enum
{
    LV_RES_INV = 0,      /*Typically indicates that the object is deleted (become invalid) in the action function or an operation was failed*/
    LV_RES_OK,           /*The object is valid (no deleted) after the action*/
};
typedef uint8_t lv_res_t;

enum
{
    /*General signals*/
    LV_SIGNAL_CLEANUP,
    LV_SIGNAL_CHILD_CHG,
    LV_SIGNAL_CORD_CHG,
    LV_SIGNAL_STYLE_CHG,
    LV_SIGNAL_REFR_EXT_SIZE,
    LV_SIGNAL_LANG_CHG,
    LV_SIGNAL_GET_TYPE,

	_LV_SIGNAL_FEEDBACK_SECTION_START,
    /*Input device related*/
    LV_SIGNAL_PRESSED,
    LV_SIGNAL_PRESSING,
    LV_SIGNAL_PRESS_LOST,
    LV_SIGNAL_RELEASED,
    LV_SIGNAL_LONG_PRESS,
    LV_SIGNAL_LONG_PRESS_REP,
    LV_SIGNAL_DRAG_BEGIN,
    LV_SIGNAL_DRAG_END,

    /*Group related*/
    LV_SIGNAL_FOCUS,
    LV_SIGNAL_DEFOCUS,
    LV_SIGNAL_CONTROLL,
    _LV_SIGNAL_FEEDBACK_SECTION_END,
    LV_SIGNAL_GET_EDITABLE,
};

typedef lv_res_t (* lv_signal_func_t) (struct _lv_obj_t * obj, lv_signal_t sign, void * param);

enum
{
    LV_ALIGN_CENTER = 0,
    LV_ALIGN_IN_TOP_LEFT,
    LV_ALIGN_IN_TOP_MID,
    LV_ALIGN_IN_TOP_RIGHT,
    LV_ALIGN_IN_BOTTOM_LEFT,
    LV_ALIGN_IN_BOTTOM_MID,
    LV_ALIGN_IN_BOTTOM_RIGHT,
    LV_ALIGN_IN_LEFT_MID,
    LV_ALIGN_IN_RIGHT_MID,
    LV_ALIGN_OUT_TOP_LEFT,
    LV_ALIGN_OUT_TOP_MID,
    LV_ALIGN_OUT_TOP_RIGHT,
    LV_ALIGN_OUT_BOTTOM_LEFT,
    LV_ALIGN_OUT_BOTTOM_MID,
    LV_ALIGN_OUT_BOTTOM_RIGHT,
    LV_ALIGN_OUT_LEFT_TOP,
    LV_ALIGN_OUT_LEFT_MID,
    LV_ALIGN_OUT_LEFT_BOTTOM,
    LV_ALIGN_OUT_RIGHT_TOP,
    LV_ALIGN_OUT_RIGHT_MID,
    LV_ALIGN_OUT_RIGHT_BOTTOM,
};
typedef uint8_t lv_align_t;

#if LV_OBJ_REALIGN
typedef struct {
    const struct _lv_obj_t * base;
    lv_coord_t xofs;
    lv_coord_t yofs;
    lv_align_t align;
    uint8_t auto_realign :1;
    uint8_t origo_align  :1;        /*1: the oigo (center of the object) was aligned with `lv_obj_align_origo`*/
}lv_reailgn_t;
#endif


typedef struct _lv_obj_t
{
    struct _lv_obj_t * par;    /*Pointer to the parent object*/
    lv_ll_t child_ll;          /*Linked list to store the children objects*/

    lv_area_t coords;               /*Coordinates of the object (x1, y1, x2, y2)*/

    lv_signal_func_t signal_func;     /*Object type specific signal function*/
    lv_design_func_t design_func;     /*Object type specific design function*/

    void * ext_attr;                 /*Object type specific extended data*/
    lv_style_t * style_p;       /*Pointer to the object's style*/

#if LV_OBJ_FREE_PTR != 0
    void * free_ptr;              /*Application specific pointer (set it freely)*/
#endif

#if USE_LV_GROUP != 0
    void * group_p;                 /*Pointer to the group of the object*/
#endif
    /*Attributes and states*/
    uint8_t click         :1;    /*1: Can be pressed by an input device*/
    uint8_t drag          :1;    /*1: Enable the dragging*/
    uint8_t drag_throw    :1;    /*1: Enable throwing with drag*/
    uint8_t drag_parent   :1;    /*1: Parent will be dragged instead*/
    uint8_t hidden        :1;    /*1: Object is hidden*/
    uint8_t top           :1;    /*1: If the object or its children is clicked it goes to the foreground*/
    uint8_t opa_scale_en  :1;    /*1: opa_scale is set*/
    uint8_t protect;            /*Automatically happening actions can be prevented. 'OR'ed values from `lv_protect_t`*/
    lv_opa_t opa_scale;         /*Scale down the opacity by this factor. Effects all children as well*/

    lv_coord_t ext_size;        /*EXTtend the size of the object in every direction. E.g. for shadow drawing*/
#if LV_OBJ_REALIGN
    lv_reailgn_t realign;
#endif

#ifdef LV_OBJ_FREE_NUM_TYPE
    LV_OBJ_FREE_NUM_TYPE free_num;          /*Application specific identifier (set it freely)*/
#endif
} lv_obj_t;

typedef lv_res_t (*lv_action_t) (struct _lv_obj_t * obj);

/*Protect some attributes (max. 8 bit)*/
enum
{
    LV_PROTECT_NONE      = 0x00,
    LV_PROTECT_CHILD_CHG = 0x01, /*Disable the child change signal. Used by the library*/
    LV_PROTECT_PARENT    = 0x02, /*Prevent automatic parent change (e.g. in lv_page)*/
    LV_PROTECT_POS       = 0x04, /*Prevent automatic positioning (e.g. in lv_cont layout)*/
    LV_PROTECT_FOLLOW    = 0x08, /*Prevent the object be followed in automatic ordering (e.g. in lv_cont PRETTY layout)*/
    LV_PROTECT_PRESS_LOST= 0x10, /*If the `indev` was pressing this object but swiped out while pressing do not search other object.*/
    LV_PROTECT_CLICK_FOCUS= 0x20,/*Prevent focusing the object by clicking on it*/
};
typedef uint8_t lv_protect_t;


/*Used by `lv_obj_get_type()`. The object's and its ancestor types are stored here*/
typedef struct {
    const char * type[LV_MAX_ANCESTOR_NUM];   /*[0]: the actual type, [1]: ancestor, [2] #1's ancestor ... [x]: "lv_obj" */
} lv_obj_type_t;

enum
{
    LV_ANIM_NONE = 0,
    LV_ANIM_FLOAT_TOP,      /*Float from/to the top*/
    LV_ANIM_FLOAT_LEFT,     /*Float from/to the left*/
    LV_ANIM_FLOAT_BOTTOM,   /*Float from/to the bottom*/
    LV_ANIM_FLOAT_RIGHT,    /*Float from/to the right*/
    LV_ANIM_GROW_H,         /*Grow/shrink  horizontally*/
    LV_ANIM_GROW_V,         /*Grow/shrink  vertically*/
};
typedef uint8_t lv_anim_builtin_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Init. the 'lv' library.
 */
void lv_init(void);

/*--------------------
 * Create and delete
 *-------------------*/

/**
 * Create a basic object
 * @param parent pointer to a parent object.
 *                  If NULL then a screen will be created
 * @param copy pointer to a base object, if not NULL then the new object will be copied from it
 * @return pointer to the new object
 */
lv_obj_t * lv_obj_create(lv_obj_t * parent,const  lv_obj_t * copy);

/**
 * Delete 'obj' and all of its children
 * @param obj pointer to an object to delete
 * @return LV_RES_INV because the object is deleted
 */
lv_res_t lv_obj_del(lv_obj_t * obj);

/**
 * Delete all children of an object
 * @param obj pointer to an object
 */
void lv_obj_clean(lv_obj_t *obj);

/**
 * Mark the object as invalid therefore its current position will be redrawn by 'lv_refr_task'
 * @param obj pointer to an object
 */
void lv_obj_invalidate(const lv_obj_t * obj);

/*=====================
 * Setter functions
 *====================*/

/*--------------
 * Screen set
 *--------------*/

/**
 * Load a new screen
 * @param scr pointer to a screen
 */
void lv_scr_load(lv_obj_t * scr);

/*--------------------
 * Parent/children set
 *--------------------*/

/**
 * Set a new parent for an object. Its relative position will be the same.
 * @param obj pointer to an object. Can't be a screen.
 * @param parent pointer to the new parent object. (Can't be NULL)
 */
void lv_obj_set_parent(lv_obj_t * obj, lv_obj_t * parent);

/*--------------------
 * Coordinate set
 * ------------------*/

/**
 * Set relative the position of an object (relative to the parent)
 * @param obj pointer to an object
 * @param x new distance from the left side of the parent
 * @param y new distance from the top of the parent
 */
void lv_obj_set_pos(lv_obj_t * obj, lv_coord_t x, lv_coord_t y);

/**
 * Set the x coordinate of a object
 * @param obj pointer to an object
 * @param x new distance from the left side from the parent
 */
void lv_obj_set_x(lv_obj_t * obj, lv_coord_t x);

/**
 * Set the y coordinate of a object
 * @param obj pointer to an object
 * @param y new distance from the top of the parent
 */
void lv_obj_set_y(lv_obj_t * obj, lv_coord_t y);

/**
 * Set the size of an object
 * @param obj pointer to an object
 * @param w new width
 * @param h new height
 */
void lv_obj_set_size(lv_obj_t * obj, lv_coord_t w, lv_coord_t h);

/**
 * Set the width of an object
 * @param obj pointer to an object
 * @param w new width
 */
void lv_obj_set_width(lv_obj_t * obj, lv_coord_t w);

/**
 * Set the height of an object
 * @param obj pointer to an object
 * @param h new height
 */
void lv_obj_set_height(lv_obj_t * obj, lv_coord_t h);

/**
 * Align an object to an other object.
 * @param obj pointer to an object to align
 * @param base pointer to an object (if NULL the parent is used). 'obj' will be aligned to it.
 * @param align type of alignment (see 'lv_align_t' enum)
 * @param x_mod x coordinate shift after alignment
 * @param y_mod y coordinate shift after alignment
 */
void lv_obj_align(lv_obj_t * obj,const lv_obj_t * base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod);

/**
 * Align an object to an other object.
 * @param obj pointer to an object to align
 * @param base pointer to an object (if NULL the parent is used). 'obj' will be aligned to it.
 * @param align type of alignment (see 'lv_align_t' enum)
 * @param x_mod x coordinate shift after alignment
 * @param y_mod y coordinate shift after alignment
 */
void lv_obj_align_origo(lv_obj_t * obj, const lv_obj_t * base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod);

/**
 * Realign the object based on the last `lv_obj_align` parameters.
 * @param obj pointer to an object
 */
void lv_obj_realign(lv_obj_t * obj);

/**
 * Enable the automatic realign of the object when its size has changed based on the last `lv_obj_align` parameters.
 * @param obj pointer to an object
 * @param en true: enable auto realign; false: disable auto realign
 */
void lv_obj_set_auto_realign(lv_obj_t * obj, bool en);

/*---------------------
 * Appearance set
 *--------------------*/

/**
 * Set a new style for an object
 * @param obj pointer to an object
 * @param style_p pointer to the new style
 */
void lv_obj_set_style(lv_obj_t * obj, lv_style_t * style);

/**
 * Notify an object about its style is modified
 * @param obj pointer to an object
 */
void lv_obj_refresh_style(lv_obj_t * obj);

/**
 * Notify all object if a style is modified
 * @param style pointer to a style. Only the objects with this style will be notified
 *               (NULL to notify all objects)
 */
void lv_obj_report_style_mod(lv_style_t * style);

/*-----------------
 * Attribute set
 *----------------*/

/**
 * Hide an object. It won't be visible and clickable.
 * @param obj pointer to an object
 * @param en true: hide the object
 */
void lv_obj_set_hidden(lv_obj_t * obj, bool en);

/**
 * Enable or disable the clicking of an object
 * @param obj pointer to an object
 * @param en true: make the object clickable
 */
void lv_obj_set_click(lv_obj_t * obj, bool en);

/**
 * Enable to bring this object to the foreground if it
 * or any of its children is clicked
 * @param obj pointer to an object
 * @param en true: enable the auto top feature
 */
void lv_obj_set_top(lv_obj_t * obj, bool en);

/**
 * Enable the dragging of an object
 * @param obj pointer to an object
 * @param en true: make the object dragable
 */
void lv_obj_set_drag(lv_obj_t * obj, bool en);

/**
 * Enable the throwing of an object after is is dragged
 * @param obj pointer to an object
 * @param en true: enable the drag throw
 */
void lv_obj_set_drag_throw(lv_obj_t * obj, bool en);

/**
 * Enable to use parent for drag related operations.
 * If trying to drag the object the parent will be moved instead
 * @param obj pointer to an object
 * @param en true: enable the 'drag parent' for the object
 */
void lv_obj_set_drag_parent(lv_obj_t * obj, bool en);

/**
 * Set editable parameter Used by groups and keyboard/encoder control.
 * Editable object has something inside to choose (the elements of a list)
 * @param obj pointer to an object
 * @param en true: enable editing
 */
//void lv_obj_set_editable(lv_obj_t * obj, bool en);

/**
 * Set the opa scale enable parameter (required to set opa_scale with `lv_obj_set_opa_scale()`)
 * @param obj pointer to an object
 * @param en true: opa scaling is enabled for this object and all children; false: no opa scaling
 */
void lv_obj_set_opa_scale_enable(lv_obj_t * obj, bool en);

/**
 * Set the opa scale of an object
 * @param obj pointer to an object
 * @param opa_scale a factor to scale down opacity [0..255]
 */
void lv_obj_set_opa_scale(lv_obj_t * obj, lv_opa_t opa_scale);

/**
 * Set a bit or bits in the protect filed
 * @param obj pointer to an object
 * @param prot 'OR'-ed values from `lv_protect_t`
 */
void lv_obj_set_protect(lv_obj_t * obj, uint8_t prot);

/**
 * Clear a bit or bits in the protect filed
 * @param obj pointer to an object
 * @param prot 'OR'-ed values from `lv_protect_t`
 */
void lv_obj_clear_protect(lv_obj_t * obj, uint8_t prot);

/**
 * Set the signal function of an object.
 * Always call the previous signal function in the new.
 * @param obj pointer to an object
 * @param fp the new signal function
 */
void lv_obj_set_signal_func(lv_obj_t * obj, lv_signal_func_t fp);

/**
 * Set a new design function for an object
 * @param obj pointer to an object
 * @param fp the new design function
 */
void lv_obj_set_design_func(lv_obj_t * obj, lv_design_func_t fp);

/*----------------
 * Other set
 *--------------*/

/**
 * Allocate a new ext. data for an object
 * @param obj pointer to an object
 * @param ext_size the size of the new ext. data
 * @return pointer to the allocated ext
 */
void * lv_obj_allocate_ext_attr(lv_obj_t * obj, uint16_t ext_size);

/**
 * Send a 'LV_SIGNAL_REFR_EXT_SIZE' signal to the object
 * @param obj pointer to an object
 */
void lv_obj_refresh_ext_size(lv_obj_t * obj);

#ifdef LV_OBJ_FREE_NUM_TYPE
/**
 * Set an application specific number for an object.
 * It can help to identify objects in the application.
 * @param obj pointer to an object
 * @param free_num the new free number
 */
void lv_obj_set_free_num(lv_obj_t * obj, LV_OBJ_FREE_NUM_TYPE free_num);
#endif

#if LV_OBJ_FREE_PTR != 0
/**
 * Set an application specific  pointer for an object.
 * It can help to identify objects in the application.
 * @param obj pointer to an object
 * @param free_p the new free pinter
 */
void lv_obj_set_free_ptr(lv_obj_t * obj, void * free_p);
#endif

#if USE_LV_ANIMATION
/**
 * Animate an object
 * @param obj pointer to an object to animate
 * @param type type of animation from 'lv_anim_builtin_t'. 'OR' it with ANIM_IN or ANIM_OUT
 * @param time time of animation in milliseconds
 * @param delay delay before the animation in milliseconds
 * @param cb a function to call when the animation is ready
 */
void lv_obj_animate(lv_obj_t * obj, lv_anim_builtin_t type, uint16_t time, uint16_t delay, void (*cb) (lv_obj_t *));
#endif

/*=======================
 * Getter functions
 *======================*/

/*------------------
 * Screen get
 *-----------------*/

/**
 * Return with a pointer to the active screen
 * @return pointer to the active screen object (loaded by 'lv_scr_load()')
 */
lv_obj_t * lv_scr_act(void);

/**
 * Return with the top layer. (Same on every screen and it is above the normal screen layer)
 * @return pointer to the top layer object  (transparent screen sized lv_obj)
 */
lv_obj_t * lv_layer_top(void);

/**
 * Return with the system layer. (Same on every screen and it is above the all other layers)
 * It is used for example by the cursor
 * @return pointer to the system layer object (transparent screen sized lv_obj)
 */
lv_obj_t * lv_layer_sys(void);

/**
 * Return with the screen of an object
 * @param obj pointer to an object
 * @return pointer to a screen
 */
lv_obj_t * lv_obj_get_screen(const lv_obj_t * obj);

/*---------------------
 * Parent/children get
 *--------------------*/

/**
 * Returns with the parent of an object
 * @param obj pointer to an object
 * @return pointer to the parent of  'obj'
 */
lv_obj_t * lv_obj_get_parent(const lv_obj_t * obj);

/**
 * Iterate through the children of an object (start from the "youngest, lastly created")
 * @param obj pointer to an object
 * @param child NULL at first call to get the next children
 *                  and the previous return value later
 * @return the child after 'act_child' or NULL if no more child
 */
lv_obj_t * lv_obj_get_child(const lv_obj_t * obj, const lv_obj_t * child);

/**
 * Iterate through the children of an object (start from the "oldest", firstly created)
 * @param obj pointer to an object
 * @param child NULL at first call to get the next children
 *                  and the previous return value later
 * @return the child after 'act_child' or NULL if no more child
 */
lv_obj_t * lv_obj_get_child_back(const lv_obj_t * obj, const lv_obj_t * child);

/**
 * Count the children of an object (only children directly on 'obj')
 * @param obj pointer to an object
 * @return children number of 'obj'
 */
uint16_t lv_obj_count_children(const lv_obj_t * obj);

/*---------------------
 * Coordinate get
 *--------------------*/

/**
 * Copy the coordinates of an object to an area
 * @param obj pointer to an object
 * @param cords_p pointer to an area to store the coordinates
 */
void lv_obj_get_coords(const lv_obj_t * obj, lv_area_t * cords_p);

/**
 * Get the x coordinate of object
 * @param obj pointer to an object
 * @return distance of 'obj' from the left side of its parent
 */
lv_coord_t lv_obj_get_x(const lv_obj_t * obj);

/**
 * Get the y coordinate of object
 * @param obj pointer to an object
 * @return distance of 'obj' from the top of its parent
 */
lv_coord_t lv_obj_get_y(const lv_obj_t * obj);

/**
 * Get the width of an object
 * @param obj pointer to an object
 * @return the width
 */
lv_coord_t lv_obj_get_width(const lv_obj_t * obj);

/**
 * Get the height of an object
 * @param obj pointer to an object
 * @return the height
 */
lv_coord_t lv_obj_get_height(const lv_obj_t * obj);

/**
 * Get the extended size attribute of an object
 * @param obj pointer to an object
 * @return the extended size attribute
 */
lv_coord_t lv_obj_get_ext_size(const lv_obj_t * obj);

/**
 * Get the automatic realign property of the object.
 * @param obj pointer to an object
 * @return  true: auto realign is enabled; false: auto realign is disabled
 */
bool lv_obj_get_auto_realign(lv_obj_t * obj);

/*-----------------
 * Appearance get
 *---------------*/

/**
 * Get the style pointer of an object (if NULL get style of the parent)
 * @param obj pointer to an object
 * @return pointer to a style
 */
lv_style_t * lv_obj_get_style(const lv_obj_t * obj);

/*-----------------
 * Attribute get
 *----------------*/

/**
 * Get the hidden attribute of an object
 * @param obj pointer to an object
 * @return true: the object is hidden
 */
bool lv_obj_get_hidden(const lv_obj_t * obj);

/**
 * Get the click enable attribute of an object
 * @param obj pointer to an object
 * @return true: the object is clickable
 */
bool lv_obj_get_click(const lv_obj_t * obj);

/**
 * Get the top enable attribute of an object
 * @param obj pointer to an object
 * @return true: the auto top feature is enabled
 */
bool lv_obj_get_top(const lv_obj_t * obj);

/**
 * Get the drag enable attribute of an object
 * @param obj pointer to an object
 * @return true: the object is dragable
 */
bool lv_obj_get_drag(const lv_obj_t * obj);

/**
 * Get the drag throw enable attribute of an object
 * @param obj pointer to an object
 * @return true: drag throw is enabled
 */
bool lv_obj_get_drag_throw(const lv_obj_t * obj);

/**
 * Get the drag parent attribute of an object
 * @param obj pointer to an object
 * @return true: drag parent is enabled
 */
bool lv_obj_get_drag_parent(const lv_obj_t * obj);


/**
 * Get the opa scale enable parameter
 * @param obj pointer to an object
 * @return true: opa scaling is enabled for this object and all children; false: no opa scaling
 */
lv_opa_t lv_obj_get_opa_scale_enable(const lv_obj_t * obj);

/**
 * Get the opa scale parameter of an object
 * @param obj pointer to an object
 * @return opa scale [0..255]
 */
lv_opa_t lv_obj_get_opa_scale(const lv_obj_t * obj);

/**
 * Get the protect field of an object
 * @param obj pointer to an object
 * @return protect field ('OR'ed values of `lv_protect_t`)
 */
uint8_t lv_obj_get_protect(const lv_obj_t * obj);

/**
 * Check at least one bit of a given protect bitfield is set
 * @param obj pointer to an object
 * @param prot protect bits to test ('OR'ed values of `lv_protect_t`)
 * @return false: none of the given bits are set, true: at least one bit is set
 */
bool lv_obj_is_protected(const lv_obj_t * obj, uint8_t prot);

/**
 * Get the signal function of an object
 * @param obj pointer to an object
 * @return the signal function
 */
lv_signal_func_t lv_obj_get_signal_func(const lv_obj_t * obj);

/**
 * Get the design function of an object
 * @param obj pointer to an object
 * @return the design function
 */
lv_design_func_t lv_obj_get_design_func(const lv_obj_t * obj);

/*------------------
 * Other get
 *-----------------*/

/**
 * Get the ext pointer
 * @param obj pointer to an object
 * @return the ext pointer but not the dynamic version
 *         Use it as ext->data1, and NOT da(ext)->data1
 */
void * lv_obj_get_ext_attr(const lv_obj_t * obj);

/**
 * Get object's and its ancestors type. Put their name in `type_buf` starting with the current type.
 * E.g. buf.type[0]="lv_btn", buf.type[1]="lv_cont", buf.type[2]="lv_obj"
 * @param obj pointer to an object which type should be get
 * @param buf pointer to an `lv_obj_type_t` buffer to store the types
 */
void lv_obj_get_type(lv_obj_t * obj, lv_obj_type_t * buf);

#ifdef LV_OBJ_FREE_NUM_TYPE
/**
 * Get the free number
 * @param obj pointer to an object
 * @return the free number
 */
LV_OBJ_FREE_NUM_TYPE lv_obj_get_free_num(const lv_obj_t * obj);
#endif

#if LV_OBJ_FREE_PTR != 0
/**
 * Get the free pointer
 * @param obj pointer to an object
 * @return the free pointer
 */
void * lv_obj_get_free_ptr(const lv_obj_t * obj);
#endif

#if USE_LV_GROUP
/**
 * Get the group of the object
 * @param obj pointer to an object
 * @return the pointer to group of the object
 */
void * lv_obj_get_group(const lv_obj_t * obj);


/**
 * Tell whether the object is the focused object of a group or not.
 * @param obj pointer to an object
 * @return true: the object is focused, false: the object is not focused or not in a group
 */
bool lv_obj_is_focused(const lv_obj_t * obj);

#endif


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_OBJ_H*/

/* lv_group.h
 * Groups focusable widgets for keyboard or controller navigation.
 */
/**
 * @file lv_group.h
 *
 */

#ifndef LV_GROUP_H
#define LV_GROUP_H

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


/*********************
 *      DEFINES
 *********************/
/*Predefined keys to control the focused object via lv_group_send(group, c)*/
/*For compatibility in signal function define the keys regardless to LV_GROUP*/
#define LV_GROUP_KEY_UP             17      /*0x11*/
#define LV_GROUP_KEY_DOWN           18      /*0x12*/
#define LV_GROUP_KEY_RIGHT          19      /*0x13*/
#define LV_GROUP_KEY_LEFT           20      /*0x14*/
#define LV_GROUP_KEY_ESC            27      /*0x1B*/
#define LV_GROUP_KEY_DEL            127     /*0x7F*/
#define LV_GROUP_KEY_BACKSPACE      8       /*0x08*/
#define LV_GROUP_KEY_ENTER          10      /*0x0A, '\n'*/
#define LV_GROUP_KEY_NEXT           9       /*0x09, '\t'*/
#define LV_GROUP_KEY_PREV           11      /*0x0B, '*/

#if USE_LV_GROUP  != 0
/**********************
 *      TYPEDEFS
 **********************/
struct _lv_group_t;

typedef void (*lv_group_style_mod_func_t)(lv_style_t *);
typedef void (*lv_group_focus_cb_t)(struct _lv_group_t *);

typedef struct _lv_group_t
{
    lv_ll_t obj_ll;                         /*Linked list to store the objects in the group */
    lv_obj_t ** obj_focus;                  /*The object in focus*/
    lv_group_style_mod_func_t style_mod;    /*A function which modifies the style of the focused object*/
    lv_group_style_mod_func_t style_mod_edit;/*A function which modifies the style of the focused object*/
    lv_group_focus_cb_t focus_cb;           /*A function to call when a new object is focused (optional)*/
    lv_style_t style_tmp;                   /*Stores the modified style of the focused object */
    uint8_t frozen          :1;             /*1: can't focus to new object*/
    uint8_t editing         :1;             /*1: Edit mode, 0: Navigate mode*/
    uint8_t click_focus     :1;             /*1: If an object in a group is clicked by an indev then it will be focused */
    uint8_t refocus_policy  :1;             /*1: Focus prev if focused on deletion. 0: Focus prev if focused on deletion.*/
    uint8_t wrap            :1;             /*1: Focus next/prev can wrap at end of list. 0: Focus next/prev stops at end of list.*/
} lv_group_t;

typedef enum _lv_group_refocus_policy_t {
    LV_GROUP_REFOCUS_POLICY_NEXT = 0,
    LV_GROUP_REFOCUS_POLICY_PREV = 1
} lv_group_refocus_policy_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a new object group
 * @return pointer to the new object group
 */
lv_group_t * lv_group_create(void);

/**
 * Delete a group object
 * @param group pointer to a group
 */
void lv_group_del(lv_group_t * group);

/**
 * Add an object to a group
 * @param group pointer to a group
 * @param obj pointer to an object to add
 */
void lv_group_add_obj(lv_group_t * group, lv_obj_t * obj);

/**
 * Remove an object from its group
 * @param obj pointer to an object to remove
 */
void lv_group_remove_obj(lv_obj_t * obj);

/**
 * Focus on an object (defocus the current)
 * @param obj pointer to an object to focus on
 */
void lv_group_focus_obj(lv_obj_t * obj);

/**
 * Focus the next object in a group (defocus the current)
 * @param group pointer to a group
 */
void lv_group_focus_next(lv_group_t * group);

/**
 * Focus the previous object in a group (defocus the current)
 * @param group pointer to a group
 */
void lv_group_focus_prev(lv_group_t * group);

/**
 * Do not let to change the focus from the current object
 * @param group pointer to a group
 * @param en true: freeze, false: release freezing (normal mode)
 */
void lv_group_focus_freeze(lv_group_t * group, bool en);

/**
 * Send a control character to the focuses object of a group
 * @param group pointer to a group
 * @param c a character (use LV_GROUP_KEY_.. to navigate)
 * @return result of focused object in group.
 */
lv_res_t lv_group_send_data(lv_group_t * group, uint32_t c);

/**
 * Set a function for a group which will modify the object's style if it is in focus
 * @param group pointer to a group
 * @param style_mod_func the style modifier function pointer
 */
void lv_group_set_style_mod_cb(lv_group_t * group, lv_group_style_mod_func_t style_mod_func);

/**
 * Set a function for a group which will modify the object's style if it is in focus in edit mode
 * @param group pointer to a group
 * @param style_mod_func the style modifier function pointer
 */
void lv_group_set_style_mod_edit_cb(lv_group_t * group, lv_group_style_mod_func_t style_mod_func);

/**
 * Set a function for a group which will be called when a new object is focused
 * @param group pointer to a group
 * @param focus_cb the call back function or NULL if unused
 */
void lv_group_set_focus_cb(lv_group_t * group, lv_group_focus_cb_t focus_cb);

/**
 * Set whether the next or previous item in a group is focused if the currently focussed obj is deleted.
 * @param group pointer to a group
 * @param new refocus policy enum
 */
void lv_group_set_refocus_policy(lv_group_t * group, lv_group_refocus_policy_t policy);

/**
 * Manually set the current mode (edit or navigate).
 * @param group pointer to group
 * @param edit: true: edit mode; false: navigate mode
 */
void lv_group_set_editing(lv_group_t * group, bool edit);

/**
 * Set the `click_focus` attribute. If enabled then the object will be focused then it is clicked.
 * @param group pointer to group
 * @param en: true: enable `click_focus`
 */
void lv_group_set_click_focus(lv_group_t * group, bool en);

/**
 * Set whether focus next/prev will allow wrapping from first->last or last->first object.
 * @param group pointer to group
 * @param en: true: wrapping enabled; false: wrapping disabled
 */
void lv_group_set_wrap(lv_group_t * group, bool en);

/**
 * Modify a style with the set 'style_mod' function. The input style remains unchanged.
 * @param group pointer to group
 * @param style pointer to a style to modify
 * @return a copy of the input style but modified with the 'style_mod' function
 */
lv_style_t * lv_group_mod_style(lv_group_t * group, const lv_style_t * style);

/**
 * Get the focused object or NULL if there isn't one
 * @param group pointer to a group
 * @return pointer to the focused object
 */
lv_obj_t * lv_group_get_focused(const lv_group_t * group);

/**
 * Get a the style modifier function of a group
 * @param group pointer to a group
 * @return pointer to the style modifier function
 */
lv_group_style_mod_func_t lv_group_get_style_mod_cb(const lv_group_t * group);

/**
 * Get a the style modifier function of a group in edit mode
 * @param group pointer to a group
 * @return pointer to the style modifier function
 */
lv_group_style_mod_func_t lv_group_get_style_mod_edit_cb(const lv_group_t * group);

/**
 * Get the focus callback function of a group
 * @param group pointer to a group
 * @return the call back function or NULL if not set
 */
lv_group_focus_cb_t lv_group_get_focus_cb(const lv_group_t * group);

/**
 * Get the current mode (edit or navigate).
 * @param group pointer to group
 * @return true: edit mode; false: navigate mode
 */
bool lv_group_get_editing(const lv_group_t * group);

/**
 * Get the `click_focus` attribute.
 * @param group pointer to group
 * @return true: `click_focus` is enabled; false: disabled
 */
bool lv_group_get_click_focus(const lv_group_t * group);

/**
 * Get whether focus next/prev will allow wrapping from first->last or last->first object.
 * @param group pointer to group
 * @param en: true: wrapping enabled; false: wrapping disabled
 */
bool lv_group_get_wrap(lv_group_t * group);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_GROUP != 0*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_GROUP_H*/

/* lv_indev.h
 * Processes driver events and sends touch, drag, and key actions to objects.
 */
/**
 * @file lv_indev_proc.h
 *
 */

#ifndef LV_INDEV_H
#define LV_INDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_hal/lv_hal.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the display input device subsystem
 */
void lv_indev_init(void);

/**
 * Get the currently processed input device. Can be used in action functions too.
 * @return pointer to the currently processed input device or NULL if no input device processing right now
 */
lv_indev_t * lv_indev_get_act(void);


/**
 * Get the type of an input device
 * @param indev pointer to an input device
 * @return the type of the input device from `lv_hal_indev_type_t` (`LV_INDEV_TYPE_...`)
 */
lv_hal_indev_type_t lv_indev_get_type(const lv_indev_t * indev);

/**
 * Reset one or all input devices
 * @param indev pointer to an input device to reset or NULL to reset all of them
 */
void lv_indev_reset(lv_indev_t * indev);

/**
 * Reset the long press state of an input device
 * @param indev_proc pointer to an input device
 */
void lv_indev_reset_lpr(lv_indev_t * indev);

/**
 * Enable input devices device by type
 * @param type Input device type
 * @param enable true: enable this type; false: disable this type
 */
void lv_indev_enable(lv_hal_indev_type_t type, bool enable);

/**
 * Set a cursor for a pointer input device (for LV_INPUT_TYPE_POINTER and LV_INPUT_TYPE_BUTTON)
 * @param indev pointer to an input device
 * @param cur_obj pointer to an object to be used as cursor
 */
void lv_indev_set_cursor(lv_indev_t *indev, lv_obj_t *cur_obj);

#if USE_LV_GROUP
/**
 * Set a destination group for a keypad input device (for LV_INDEV_TYPE_KEYPAD)
 * @param indev pointer to an input device
 * @param group point to a group
 */
void lv_indev_set_group(lv_indev_t *indev, lv_group_t *group);
#endif

/**
 * Set the an array of points for LV_INDEV_TYPE_BUTTON.
 * These points will be assigned to the buttons to press a specific point on the screen
 * @param indev pointer to an input device
 * @param group point to a group
 */
void lv_indev_set_button_points(lv_indev_t *indev, const lv_point_t *points);

/**
 * Set feedback callback for indev.
 * @param indev pointer to an input device
 * @param feedback feedback callback
 */
void lv_indev_set_feedback(lv_indev_t *indev, lv_indev_feedback_t feedback);

/**
 * Get the last point of an input device (for LV_INDEV_TYPE_POINTER and LV_INDEV_TYPE_BUTTON)
 * @param indev pointer to an input device
 * @param point pointer to a point to store the result
 */
void lv_indev_get_point(const lv_indev_t * indev, lv_point_t * point);

/**
 * Get the last key of an input device (for LV_INDEV_TYPE_KEYPAD)
 * @param indev pointer to an input device
 * @return the last pressed key (0 on error)
 */
uint32_t lv_indev_get_key(const lv_indev_t * indev);

/**
 * Check if there is dragging with an input device or not (for LV_INDEV_TYPE_POINTER and LV_INDEV_TYPE_BUTTON)
 * @param indev pointer to an input device
 * @return true: drag is in progress
 */
bool lv_indev_is_dragging(const lv_indev_t * indev);

/**
 * Get the vector of dragging of an input device (for LV_INDEV_TYPE_POINTER and LV_INDEV_TYPE_BUTTON)
 * @param indev pointer to an input device
 * @param point pointer to a point to store the vector
 */
void lv_indev_get_vect(const lv_indev_t * indev, lv_point_t * point);
/**
 * Get elapsed time since last press
 * @param indev pointer to an input device (NULL to get the overall smallest inactivity)
 * @return Elapsed ticks (milliseconds) since last press
 */
uint32_t lv_indev_get_inactive_time(const lv_indev_t * indev);

/**
 * Get feedback callback for indev.
 * @param indev pointer to an input device
 * @return feedback callback
 */
lv_indev_feedback_t lv_indev_get_feedback(const lv_indev_t *indev);

/**
 * Do nothing until the next release
 * @param indev pointer to an input device
 */
void lv_indev_wait_release(lv_indev_t * indev);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_INDEV_H*/

/* lv_lang.h
 * Stores the active UI language and exposes language-change support.
 */
/**
 * @file lv_lang.h
 *
 */

#ifndef LV_LANG_H
#define LV_LANG_H

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

#if USE_LV_MULTI_LANG

#include <stdint.h>

/*********************
 *      DEFINES
 *********************/
#define LV_LANG_TXT_ID_NONE     0xFFFF /*Used to not assign any text IDs for a multi-language object.*/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Change the language
 * @param lang_id the id of the
 */
void lv_lang_set(uint8_t lang_id);

/**
 * Set a function to get the texts of the set languages from a `txt_id`
 * @param fp a function pointer to get the texts
 */
void lv_lang_set_text_func(const void * (*fp)(uint16_t));

/**
 * Use the function set by `lv_lang_set_text_func` to get the `txt_id` text in the set language
 * @param txt_id an ID of the text to get
 * @return the `txt_id` txt on the set language
 */
const void * lv_lang_get_text(uint16_t txt_id);

/**
 * Return with ID of the currently selected language
 * @return pointer to the active screen object (loaded by 'lv_scr_load()')
 */
uint8_t lv_lang_act(void);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_MULTI_LANG*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_LANG_H*/

/* lv_refr.h
 * Tracks dirty screen areas and schedules a redraw.
 */
/**
 * @file lv_refr.h
 *
 */

#ifndef LV_REFR_H
#define LV_REFR_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the screen refresh subsystem
 */
void lv_refr_init(void);

/**
 * Redraw the invalidated areas now.
 * Normally the redrawing is periodically executed in `lv_task_handler` but a long blocking process can
 * prevent the call of `lv_task_handler`. In this case if the the GUI is updated in the process (e.g. progress bar)
 * this function can be called when the screen should be updated.
 */
void lv_refr_now(void);

/**
 * Invalidate an area
 * @param area_p pointer to area which should be invalidated
 */
void lv_inv_area(const lv_area_t * area_p);

/**
 * Set a function to call after every refresh to announce the refresh time and the number of refreshed pixels
 * @param cb pointer to a callback function (void my_refr_cb(uint32_t time_ms, uint32_t px_num))
 */
void lv_refr_set_monitor_cb(void (*cb)(uint32_t, uint32_t));

/**
 * Called when an area is invalidated to modify the coordinates of the area.
 * Special display controllers may require special coordinate rounding
 * @param cb pointer to the a function which will modify the area
 */
void lv_refr_set_round_cb(void(*cb)(lv_area_t*));

/**
 * Get the number of areas in the buffer
 * @return number of invalid areas
 */
uint16_t lv_refr_get_buf_size(void);

/**
 * Pop (delete) the last 'num' invalidated areas from the buffer
 * @param num number of areas to delete
 */
void lv_refr_pop_from_buf(uint16_t num);
/**********************
 *   STATIC FUNCTIONS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_REFR_H*/

/* lv_vdb.h
 * Provides access to virtual display buffers used during rendering.
 */
/**
 * @file lv_vdb.h
 *
 */

#ifndef LV_VDB_H
#define LV_VDB_H

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

#if LV_VDB_SIZE != 0

#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/
/*Can be used in `lv_conf.h` the set an invalid address for the VDB. It should be replaced later by a valid address using `lv_vdb_set_adr()`*/
#define LV_VDB_ADR_INV  8       /*8 is still too small to be valid but it's aligned on 64 bit machines as well*/

#ifndef LV_VDB_PX_BPP
#define LV_VDB_PX_BPP LV_COLOR_SIZE     /* Default is LV_COLOR_SIZE */
#endif


#if LV_VDB_TRUE_DOUBLE_BUFFERED && (LV_VDB_SIZE != LV_HOR_RES * LV_VER_RES || LV_VDB_DOUBLE == 0)
#error "With LV_VDB_TRUE_DOUBLE_BUFFERED: (LV_VDB_SIZE = LV_HOR_RES * LV_VER_RES and LV_VDB_DOUBLE = 1 is required"
#endif


/* The size of VDB in bytes.
 * (LV_VDB_SIZE * LV_VDB_PX_BPP) >> 3): just divide by 8 to convert bits to bytes
 * (((LV_VDB_SIZE * LV_VDB_PX_BPP) & 0x7) ? 1 : 0): add an extra byte to round up.
 *    E.g. if LV_VDB_SIZE = 10 and LV_VDB_PX_BPP = 1 -> 10 bits -> 2 bytes*/
#define LV_VDB_SIZE_IN_BYTES ((LV_VDB_SIZE * LV_VDB_PX_BPP) >> 3) + (((LV_VDB_SIZE * LV_VDB_PX_BPP) & 0x7) ? 1 : 0)

/**********************
 *      TYPEDEFS
 **********************/

typedef struct
{
    lv_area_t area;
    lv_color_t *buf;
} lv_vdb_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Get the 'vdb' variable or allocate one in LV_VDB_DOUBLE mode
 * @return pointer to a 'vdb' variable
 */
lv_vdb_t * lv_vdb_get(void);

/**
 * Flush the content of the vdb
 */
void lv_vdb_flush(void);

/**
 * Set the address of VDB buffer(s) manually. To use this set `LV_VDB_ADR` (and `LV_VDB2_ADR`) to `LV_VDB_ADR_INV` in `lv_conf.h`.
 * It should be called before `lv_init()`. The size of the buffer should be: `LV_VDB_SIZE_IN_BYTES`
 * @param buf1 address of the VDB.
 * @param buf2 address of the second buffer. `NULL` if `LV_VDB_DOUBLE  0`
 */
void lv_vdb_set_adr(void * buf1, void * buf2);

/**
 * Call in the display driver's  'disp_flush' function when the flushing is finished
 */
void lv_flush_ready(void);

/**
 * Get currently active VDB, where the drawing happens. Used with `LV_VDB_DOUBLE  1`
 * @return pointer to the active VDB. If `LV_VDB_DOUBLE  0` give the single VDB
 */
lv_vdb_t * lv_vdb_get_active(void);

/**
 * Get currently inactive VDB, which is being displayed or being flushed. Used with `LV_VDB_DOUBLE  1`
 * @return pointer to the inactive VDB. If `LV_VDB_DOUBLE  0` give the single VDB
 */
lv_vdb_t * lv_vdb_get_inactive(void);

/**
 * Whether the flushing is in progress or not
 * @return true: flushing is in progress; false: flushing ready
 */
bool lv_vdb_is_flushing(void);

/**********************
 *      MACROS
 **********************/

#else /*LV_VDB_SIZE != 0*/

/*Just for compatibility*/
void lv_flush_ready(void);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_VDB_H*/

#endif /* PROS_DISPLAY_LV_CORE_H */
