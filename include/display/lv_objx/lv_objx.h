/**
 * Widgets for building interactive screens.
 * Every widget is an LVGL object. Its create function accepts a parent
 * and optionally copies another widget. The remaining APIs configure
 * content, appearance, and interactions. The auton toggle uses lv_sw.
 * The sections retain their original LVGL 5.3 declarations.
 */
#ifndef PROS_DISPLAY_LV_OBJX_H
#define PROS_DISPLAY_LV_OBJX_H

/* lv_arc.h
 * Creates a stylable arc with configurable start and end angles.
 */
/**
 * @file lv_arc.h
 *
 */


#ifndef LV_ARC_H
#define LV_ARC_H

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

#if USE_LV_ARC != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of arc*/
typedef struct {
    /*New data for this type */
    lv_coord_t angle_start;
    lv_coord_t angle_end;
} lv_arc_ext_t;


/*Styles*/
enum {
    LV_ARC_STYLE_MAIN,
};
typedef uint8_t lv_arc_style_t;



/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a arc objects
 * @param par pointer to an object, it will be the parent of the new arc
 * @param copy pointer to a arc object, if not NULL then the new object will be copied from it
 * @return pointer to the created arc
 */
lv_obj_t * lv_arc_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/


/*=====================
 * Setter functions
 *====================*/

/**
 * Set the start and end angles of an arc. 0 deg: bottom, 90 deg: right etc.
 * @param arc pointer to an arc object
 * @param start the start angle [0..360]
 * @param end the end angle [0..360]
 */
void lv_arc_set_angles(lv_obj_t * arc, uint16_t start, uint16_t end);

/**
 * Set a style of a arc.
 * @param arc pointer to arc object
 * @param type which style should be set
 * @param style pointer to a style
 *  */
void lv_arc_set_style(lv_obj_t * arc, lv_arc_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the start angle of an arc.
 * @param arc pointer to an arc object
 * @return the start angle [0..360]
 */
uint16_t lv_arc_get_angle_start(lv_obj_t * arc);

/**
 * Get the end angle of an arc.
 * @param arc pointer to an arc object
 * @return the end angle [0..360]
 */
uint16_t lv_arc_get_angle_end(lv_obj_t * arc);

/**
 * Get style of a arc.
 * @param arc pointer to arc object
 * @param type which style should be get
 * @return style pointer to the style
 *  */
lv_style_t * lv_arc_get_style(const lv_obj_t * arc, lv_arc_style_t type);

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_ARC*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_ARC_H*/

/* lv_cont.h
 * Arranges child widgets with layout and fitting rules.
 */
/**
 * @file lv_cont.h
 *
 */

#ifndef LV_CONT_H
#define LV_CONT_H

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

#if USE_LV_CONT != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Layout options*/
enum
{
    LV_LAYOUT_OFF = 0,
    LV_LAYOUT_CENTER,
    LV_LAYOUT_COL_L,    /*Column left align*/
    LV_LAYOUT_COL_M,    /*Column middle align*/
    LV_LAYOUT_COL_R,    /*Column right align*/
    LV_LAYOUT_ROW_T,    /*Row top align*/
    LV_LAYOUT_ROW_M,    /*Row middle align*/
    LV_LAYOUT_ROW_B,    /*Row bottom align*/
    LV_LAYOUT_PRETTY,   /*Put as many object as possible in row and begin a new row*/
    LV_LAYOUT_GRID,     /*Align same-sized object into a grid*/
};
typedef uint8_t lv_layout_t;

typedef struct
{
    /*Inherited from 'base_obj' so no inherited ext. */ /*Ext. of ancestor*/
    /*New data for this type */
    uint8_t layout  :4;     /*A layout from 'lv_cont_layout_t' enum*/
    uint8_t hor_fit :1;     /*1: Enable horizontal fit to involve all children*/
    uint8_t ver_fit :1;     /*1: Enable horizontal fit to involve all children*/
} lv_cont_ext_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a container objects
 * @param par pointer to an object, it will be the parent of the new container
 * @param copy pointer to a container object, if not NULL then the new object will be copied from it
 * @return pointer to the created container
 */
lv_obj_t * lv_cont_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a layout on a container
 * @param cont pointer to a container object
 * @param layout a layout from 'lv_cont_layout_t'
 */
void lv_cont_set_layout(lv_obj_t * cont, lv_layout_t layout);


/**
 * Enable the horizontal or vertical fit.
 * The container size will be set to involve the children horizontally or vertically.
 * @param cont pointer to a container object
 * @param hor_en true: enable the horizontal fit
 * @param ver_en true: enable the vertical fit
 */
void lv_cont_set_fit(lv_obj_t * cont, bool hor_en, bool ver_en);

/**
 * Set the style of a container
 * @param cont pointer to a container object
 * @param style pointer to the new style
 */
static inline void lv_cont_set_style(lv_obj_t *cont, lv_style_t * style)
{
    lv_obj_set_style(cont, style);
}

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the layout of a container
 * @param cont pointer to container object
 * @return the layout from 'lv_cont_layout_t'
 */
lv_layout_t lv_cont_get_layout(const lv_obj_t * cont);

/**
 * Get horizontal fit enable attribute of a container
 * @param cont pointer to a container object
 * @return true: horizontal fit is enabled; false: disabled
 */
bool lv_cont_get_hor_fit(const lv_obj_t * cont);

/**
 * Get vertical fit enable attribute of a container
 * @param cont pointer to a container object
 * @return true: vertical fit is enabled; false: disabled
 */
bool lv_cont_get_ver_fit(const lv_obj_t * cont);


/**
 * Get that width reduced by the horizontal padding. Useful if a layout is used.
 * @param cont pointer to a container object
 * @return the width which still fits into the container
 */
lv_coord_t lv_cont_get_fit_width(lv_obj_t * cont);

/**
 * Get that height reduced by the vertical padding. Useful if a layout is used.
 * @param cont pointer to a container object
 * @return the height which still fits into the container
 */
lv_coord_t lv_cont_get_fit_height(lv_obj_t * cont);

/**
 * Get the style of a container
 * @param cont pointer to a container object
 * @return pointer to the container's style
 */
static inline lv_style_t * lv_cont_get_style(const lv_obj_t *cont)
{
    return lv_obj_get_style(cont);
}

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_CONT*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_CONT_H*/

/* lv_btn.h
 * Creates a pressable button with styles and actions for its states.
 */
/**
 * @file lv_btn.h
 *
 */

#ifndef LV_BTN_H
#define LV_BTN_H

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

#if USE_LV_BTN != 0

/*Testing of dependencies*/
#if USE_LV_CONT == 0
#error "lv_btn: lv_cont is required. Enable it in lv_conf.h (USE_LV_CONT  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* Button states
 * It can be used not only by buttons but other button-like objects too*/
enum
{
    LV_BTN_STATE_REL,
    LV_BTN_STATE_PR,
    LV_BTN_STATE_TGL_REL,
    LV_BTN_STATE_TGL_PR,
    LV_BTN_STATE_INA,
    LV_BTN_STATE_NUM,
};
typedef uint8_t lv_btn_state_t;

enum
{
    LV_BTN_ACTION_CLICK,
    LV_BTN_ACTION_PR,
    LV_BTN_ACTION_LONG_PR,
    LV_BTN_ACTION_LONG_PR_REPEAT,
    LV_BTN_ACTION_NUM,
};
typedef uint8_t lv_btn_action_t;


/*Data of button*/
typedef struct
{
    lv_cont_ext_t cont; /*Ext. of ancestor*/
    /*New data for this type */
    lv_action_t actions[LV_BTN_ACTION_NUM];
    lv_style_t * styles[LV_BTN_STATE_NUM];        /*Styles in each state*/
    lv_btn_state_t state;                         /*Current state of the button from 'lv_btn_state_t' enum*/
#if LV_BTN_INK_EFFECT
    uint16_t ink_in_time;                         /*[ms] Time of ink fill effect (0: disable ink effect)*/
    uint16_t ink_wait_time;                       /*[ms] Wait before the ink disappears */
    uint16_t ink_out_time;                        /*[ms] Time of ink disappearing*/
#endif
    uint8_t toggle :1;                            /*1: Toggle enabled*/
    uint8_t long_pr_action_executed :1;           /*1: Long press action executed (Handled by the library)*/
} lv_btn_ext_t;

/*Styles*/
enum {
    LV_BTN_STYLE_REL,
    LV_BTN_STYLE_PR,
    LV_BTN_STYLE_TGL_REL,
    LV_BTN_STYLE_TGL_PR,
    LV_BTN_STYLE_INA,
};
typedef uint8_t lv_btn_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a button objects
 * @param par pointer to an object, it will be the parent of the new button
 * @param copy pointer to a button object, if not NULL then the new object will be copied from it
 * @return pointer to the created button
 */
lv_obj_t * lv_btn_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Enable the toggled states. On release the button will change from/to toggled state.
 * @param btn pointer to a button object
 * @param tgl true: enable toggled states, false: disable
 */
void lv_btn_set_toggle(lv_obj_t * btn, bool tgl);

/**
 * Set the state of the button
 * @param btn pointer to a button object
 * @param state the new state of the button (from lv_btn_state_t enum)
 */
void lv_btn_set_state(lv_obj_t * btn, lv_btn_state_t state);

/**
 * Toggle the state of the button (ON->OFF, OFF->ON)
 * @param btn pointer to a button object
 */
void lv_btn_toggle(lv_obj_t * btn);

/**
 * Set a function to call when a button event happens
 * @param btn pointer to a button object
 * @param action type of event form 'lv_action_t' (press, release, long press, long press repeat)
 */
void lv_btn_set_action(lv_obj_t * btn, lv_btn_action_t type, lv_action_t action);

/**
 * Set the layout on a button
 * @param btn pointer to a button object
 * @param layout a layout from 'lv_cont_layout_t'
 */
static inline void lv_btn_set_layout(lv_obj_t * btn, lv_layout_t layout)
{
    lv_cont_set_layout(btn, layout);
}

/**
 * Enable the horizontal or vertical fit.
 * The button size will be set to involve the children horizontally or vertically.
 * @param btn pointer to a button object
 * @param hor_en true: enable the horizontal fit
 * @param ver_en true: enable the vertical fit
 */
static inline void lv_btn_set_fit(lv_obj_t * btn, bool hor_en, bool ver_en)
{
    lv_cont_set_fit(btn, hor_en, ver_en);
}

/**
 * Set time of the ink effect (draw a circle on click to animate in the new state)
 * @param btn pointer to a button object
 * @param time the time of the ink animation
 */
void lv_btn_set_ink_in_time(lv_obj_t * btn, uint16_t time);

/**
 * Set the wait time before the ink disappears
 * @param btn pointer to a button object
 * @param time the time of the ink animation
 */
void lv_btn_set_ink_wait_time(lv_obj_t * btn, uint16_t time);

/**
 * Set time of the ink out effect (animate to the released state)
 * @param btn pointer to a button object
 * @param time the time of the ink animation
 */
void lv_btn_set_ink_out_time(lv_obj_t * btn, uint16_t time);

/**
 * Set a style of a button.
 * @param btn pointer to button object
 * @param type which style should be set
 * @param style pointer to a style
 *  */
void lv_btn_set_style(lv_obj_t * btn, lv_btn_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the current state of the button
 * @param btn pointer to a button object
 * @return the state of the button (from lv_btn_state_t enum)
 */
lv_btn_state_t lv_btn_get_state(const lv_obj_t * btn);

/**
 * Get the toggle enable attribute of the button
 * @param btn pointer to a button object
 * @return ture: toggle enabled, false: disabled
 */
bool lv_btn_get_toggle(const lv_obj_t * btn);

/**
 * Get the release action of a button
 * @param btn pointer to a button object
 * @return pointer to the release action function
 */
lv_action_t lv_btn_get_action(const lv_obj_t * btn, lv_btn_action_t type);

/**
 * Get the layout of a button
 * @param btn pointer to button object
 * @return the layout from 'lv_cont_layout_t'
 */
static inline lv_layout_t lv_btn_get_layout(const lv_obj_t * btn)
{
    return lv_cont_get_layout(btn);
}

/**
 * Get horizontal fit enable attribute of a button
 * @param btn pointer to a button object
 * @return true: horizontal fit is enabled; false: disabled
 */
static inline bool lv_btn_get_hor_fit(const lv_obj_t * btn)
{
    return lv_cont_get_hor_fit(btn);
}

/**
 * Get vertical fit enable attribute of a container
 * @param btn pointer to a button object
 * @return true: vertical fit is enabled; false: disabled
 */
static inline bool lv_btn_get_ver_fit(const lv_obj_t * btn)
{
    return lv_cont_get_ver_fit(btn);
}

/**
 * Get time of the ink in effect (draw a circle on click to animate in the new state)
 * @param btn pointer to a button object
 * @return the time of the ink animation
 */
uint16_t lv_btn_get_ink_in_time(const lv_obj_t * btn);

/**
 * Get the wait time before the ink disappears
 * @param btn pointer to a button object
 * @return the time of the ink animation
 */
uint16_t lv_btn_get_ink_wait_time(const lv_obj_t * btn);

/**
 * Get time of the ink out effect (animate to the releases state)
 * @param btn pointer to a button object
 * @return the time of the ink animation
 */
uint16_t lv_btn_get_ink_out_time(const lv_obj_t * btn);

/**
 * Get style of a button.
 * @param btn pointer to button object
 * @param type which style should be get
 * @return style pointer to the style
 *  */
lv_style_t * lv_btn_get_style(const lv_obj_t * btn, lv_btn_style_t type);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_BUTTON*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_BTN_H*/

/* lv_label.h
 * Displays text and controls its alignment and long-text behavior.
 */
/**
 * @file lv_rect.h
 *
 */

#ifndef LV_LABEL_H
#define LV_LABEL_H

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

#if USE_LV_LABEL != 0

#include "display/lv_core/lv_core.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/
#define LV_LABEL_DOT_NUM    3
#define LV_LABEL_POS_LAST   0xFFFF

/**********************
 *      TYPEDEFS
 **********************/

/*Long mode behaviors. Used in 'lv_label_ext_t' */
enum
{
    LV_LABEL_LONG_EXPAND,   /*Expand the object size to the text size*/
    LV_LABEL_LONG_BREAK,    /*Keep the object width, break the too long lines and expand the object height*/
    LV_LABEL_LONG_SCROLL,   /*Expand the object size and scroll the text on the parent (move the label object)*/
    LV_LABEL_LONG_DOT,      /*Keep the size and write dots at the end if the text is too long*/
    LV_LABEL_LONG_ROLL,     /*Keep the size and roll the text infinitely*/
    LV_LABEL_LONG_CROP,     /*Keep the size and crop the text out of it*/
};
typedef uint8_t lv_label_long_mode_t;

/*Label align policy*/
enum {
    LV_LABEL_ALIGN_LEFT,
    LV_LABEL_ALIGN_CENTER,
    LV_LABEL_ALIGN_RIGHT,
};
typedef uint8_t lv_label_align_t;

/*Data of label*/
typedef struct
{
    /*Inherited from 'base_obj' so no inherited ext.*/  /*Ext. of ancestor*/
    /*New data for this type */
    char * text;                            /*Text of the label*/
    lv_label_long_mode_t long_mode;         /*Determinate what to do with the long texts*/
#if LV_TXT_UTF8 == 0
    char dot_tmp[LV_LABEL_DOT_NUM + 1];     /*Store the character which are replaced by dots (Handled by the library)*/
#else
    char dot_tmp[LV_LABEL_DOT_NUM * 4 + 1]; /*Store the character which are replaced by dots (Handled by the library)*/
#endif

#if USE_LV_MULTI_LANG
    uint16_t lang_txt_id;            /*The ID of the text to display*/
#endif
    uint16_t dot_end;               /*The text end position in dot mode (Handled by the library)*/
    uint16_t anim_speed;            /*Speed of scroll and roll animation in px/sec unit*/
    lv_point_t offset;              /*Text draw position offset*/
    uint8_t static_txt  :1;         /*Flag to indicate the text is static*/
    uint8_t align       :2;         /*Align type from 'lv_label_align_t'*/
    uint8_t recolor     :1;         /*Enable in-line letter re-coloring*/
    uint8_t expand      :1;         /*Ignore real width (used by the library with LV_LABEL_LONG_ROLL)*/
    uint8_t body_draw   :1;         /*Draw background body*/
} lv_label_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**
 * Create a label objects
 * @param par pointer to an object, it will be the parent of the new label
 * @param copy pointer to a button object, if not NULL then the new object will be copied from it
 * @return pointer to the created button
 */
lv_obj_t * lv_label_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a new text for a label. Memory will be allocated to store the text by the label.
 * @param label pointer to a label object
 * @param text '\0' terminated character string. NULL to refresh with the current text.
 */
void lv_label_set_text(lv_obj_t * label, const char * text);

/**
 * Set a new text for a label from a character array. The array don't has to be '\0' terminated.
 * Memory will be allocated to store the array by the label.
 * @param label pointer to a label object
 * @param array array of characters or NULL to refresh the label
 * @param size the size of 'array' in bytes
 */
void lv_label_set_array_text(lv_obj_t * label, const char * array, uint16_t size);

/**
 * Set a static text. It will not be saved by the label so the 'text' variable
 * has to be 'alive' while the label exist.
 * @param label pointer to a label object
 * @param text pointer to a text. NULL to refresh with the current text.
 */
void lv_label_set_static_text(lv_obj_t * label, const char * text);

/**
 *Set a text ID which means a the same text but on different languages
 * @param label pointer to a label object
 * @param txt_id ID of the text
 */
#if USE_LV_MULTI_LANG
void lv_label_set_text_id(lv_obj_t * label, uint32_t txt_id);
#endif

/**
 * Set the behavior of the label with longer text then the object size
 * @param label pointer to a label object
 * @param long_mode the new mode from 'lv_label_long_mode' enum.
 *                  In LV_LONG_BREAK/LONG/ROLL the size of the label should be set AFTER this function
 */
void lv_label_set_long_mode(lv_obj_t * label, lv_label_long_mode_t long_mode);

/**
 * Set the align of the label (left or center)
 * @param label pointer to a label object
 * @param align 'LV_LABEL_ALIGN_LEFT' or 'LV_LABEL_ALIGN_LEFT'
 */
void lv_label_set_align(lv_obj_t *label, lv_label_align_t align);

/**
 * Enable the recoloring by in-line commands
 * @param label pointer to a label object
 * @param en true: enable recoloring, false: disable
 */
void lv_label_set_recolor(lv_obj_t * label, bool en);

/**
 * Set the label to draw (or not draw) background specified in its style's body
 * @param label pointer to a label object
 * @param en true: draw body; false: don't draw body
 */
void lv_label_set_body_draw(lv_obj_t *label, bool en);

/**
 * Set the label's animation speed in LV_LABEL_LONG_ROLL and SCROLL modes
 * @param label pointer to a label object
 * @param anim_speed speed of animation in px/sec unit
 */
void lv_label_set_anim_speed(lv_obj_t *label, uint16_t anim_speed);

/**
 * Set the style of an label
 * @param label pointer to an label object
 * @param style pointer to a style
 */
static inline void lv_label_set_style(lv_obj_t *label, lv_style_t *style)
{
    lv_obj_set_style(label, style);
}
/*=====================
 * Getter functions
 *====================*/

/**
 * Get the text of a label
 * @param label pointer to a label object
 * @return the text of the label
 */
char * lv_label_get_text(const lv_obj_t * label);

#if USE_LV_MULTI_LANG
/**
 * Get the text ID of the label. (Used by the multi-language feature)
 * @param label pointer to a label object
 * @return ID of the text
 */
uint16_t lv_label_get_text_id(lv_obj_t * label);
#endif

/**
 * Get the long mode of a label
 * @param label pointer to a label object
 * @return the long mode
 */
lv_label_long_mode_t lv_label_get_long_mode(const lv_obj_t * label);

/**
 * Get the align attribute
 * @param label pointer to a label object
 * @return LV_LABEL_ALIGN_LEFT or LV_LABEL_ALIGN_CENTER
 */
lv_label_align_t lv_label_get_align(const lv_obj_t * label);

/**
 * Get the recoloring attribute
 * @param label pointer to a label object
 * @return true: recoloring is enabled, false: disable
 */
bool lv_label_get_recolor(const lv_obj_t * label);

/**
 * Get the body draw attribute
 * @param label pointer to a label object
 * @return true: draw body; false: don't draw body
 */
bool lv_label_get_body_draw(const lv_obj_t *label);

/**
 * Get the label's animation speed in LV_LABEL_LONG_ROLL and SCROLL modes
 * @param label pointer to a label object
 * @return speed of animation in px/sec unit
 */
uint16_t lv_label_get_anim_speed(const lv_obj_t *label);

/**
 * Get the relative x and y coordinates of a letter
 * @param label pointer to a label object
 * @param index index of the letter [0 ... text length]. Expressed in character index, not byte index (different in UTF-8)
 * @param pos store the result here (E.g. index = 0 gives 0;0 coordinates)
 */
void lv_label_get_letter_pos(const lv_obj_t * label, uint16_t index, lv_point_t * pos);

/**
 * Get the index of letter on a relative point of a label
 * @param label pointer to label object
 * @param pos pointer to point with coordinates on a the label
 * @return the index of the letter on the 'pos_p' point (E.g. on 0;0 is the 0. letter)
 * Expressed in character index and not byte index (different in UTF-8)
 */
uint16_t lv_label_get_letter_on(const lv_obj_t * label, lv_point_t * pos);

/**
 * Get the style of an label object
 * @param label pointer to an label object
 * @return pointer to the label's style
 */
static inline lv_style_t* lv_label_get_style(const lv_obj_t *label)
{
    return lv_obj_get_style(label);
}

/*=====================
 * Other functions
 *====================*/

/**
 * Insert a text to the label. The label text can not be static.
 * @param label pointer to a label object
 * @param pos character index to insert. Expressed in character index and not byte index (Different in UTF-8)
 *            0: before first char.
 *            LV_LABEL_POS_LAST: after last char.
 * @param txt pointer to the text to insert
 */
void lv_label_ins_text(lv_obj_t * label, uint32_t pos,  const char * txt);

/**
 * Delete characters from a label. The label text can not be static.
 * @param label pointer to a label object
 * @param pos character index to insert. Expressed in character index and not byte index (Different in UTF-8)
 *            0: before first char.
 * @param cnt number of characters to cut
 */
void lv_label_cut_text(lv_obj_t * label, uint32_t pos,  uint32_t cnt);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_LABEL*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_LABEL_H*/

/* lv_bar.h
 * Displays a value as a filled portion of a track.
 */
/**
 * @file lv_bar.h
 *
 */

#ifndef LV_BAR_H
#define LV_BAR_H

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

#if USE_LV_BAR != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of bar*/
typedef struct
{
    /*No inherited ext*/            /*Ext. of ancestor*/
    /*New data for this type */
    int16_t cur_value;              /*Current value of the bar*/
    int16_t min_value;              /*Minimum value of the bar*/
    int16_t max_value;              /*Maximum value of the bar*/
    uint8_t sym    :1;              /*Symmetric: means the center is around zero value*/
    lv_style_t *style_indic;        /*Style of the indicator*/
} lv_bar_ext_t;

enum {
    LV_BAR_STYLE_BG,
    LV_BAR_STYLE_INDIC,
};
typedef uint8_t lv_bar_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a bar objects
 * @param par pointer to an object, it will be the parent of the new bar
 * @param copy pointer to a bar object, if not NULL then the new object will be copied from it
 * @return pointer to the created bar
 */
lv_obj_t * lv_bar_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a new value on the bar
 * @param bar pointer to a bar object
 * @param value new value
 */
void lv_bar_set_value(lv_obj_t * bar, int16_t value);

/**
 * Set a new value with animation on the bar
 * @param bar pointer to a bar object
 * @param value new value
 * @param anim_time animation time in milliseconds
 */
void lv_bar_set_value_anim(lv_obj_t * bar, int16_t value, uint16_t anim_time);


/**
 * Set minimum and the maximum values of a bar
 * @param bar pointer to the bar object
 * @param min minimum value
 * @param max maximum value
 */
void lv_bar_set_range(lv_obj_t * bar, int16_t min, int16_t max);

/**
 * Make the bar symmetric to zero. The indicator will grow from zero instead of the minimum position.
 * @param bar pointer to a bar object
 * @param en true: enable disable symmetric behavior; false: disable
 */
void lv_bar_set_sym(lv_obj_t * bar, bool en);

/**
 * Set a style of a bar
 * @param bar pointer to a bar object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_bar_set_style(lv_obj_t *bar, lv_bar_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the value of a bar
 * @param bar pointer to a bar object
 * @return the value of the bar
 */
int16_t lv_bar_get_value(const lv_obj_t * bar);

/**
 * Get the minimum value of a bar
 * @param bar pointer to a bar object
 * @return the minimum value of the bar
 */
int16_t lv_bar_get_min_value(const lv_obj_t * bar);

/**
 * Get the maximum value of a bar
 * @param bar pointer to a bar object
 * @return the maximum value of the bar
 */
int16_t lv_bar_get_max_value(const lv_obj_t * bar);

/**
 * Get whether the bar is symmetric or not.
 * @param bar pointer to a bar object
 * @return true: symmetric is enabled; false: disable
 */
bool lv_bar_get_sym(lv_obj_t * bar);

/**
 * Get a style of a bar
 * @param bar pointer to a bar object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_bar_get_style(const lv_obj_t *bar, lv_bar_style_t type);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_BAR*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_BAR_H*/

/* lv_btnm.h
 * Lays out multiple buttons from a string map in one widget.
 */
/**
 * @file lv_btnm.h
 *
 */


#ifndef LV_BTNM_H
#define LV_BTNM_H

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

#if USE_LV_BTNM != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/*Control byte*/
#define LV_BTNM_CTRL_CODE       0x80    /*The control byte has to begin (if present) with 0b10xxxxxx*/
#define LV_BTNM_CTRL_MASK       0xC0
#define LV_BTNM_WIDTH_MASK      0x07
#define LV_BTNM_HIDE_MASK       0x08
#define LV_BTNM_REPEAT_DISABLE_MASK     0x10
#define LV_BTNM_INACTIVE_MASK   0x20


#define LV_BTNM_PR_NONE         0xFFFF
/**********************
 *      TYPEDEFS
 **********************/

/* Type of callback function which is called when a button is released or long pressed on the button matrix
 * Parameters: button matrix, text of the released button
 * return LV_ACTION_RES_INV if  the button matrix is deleted else LV_ACTION_RES_OK*/
typedef lv_res_t (*lv_btnm_action_t) (lv_obj_t *, const char *txt);

/*Data of button matrix*/
typedef struct
{
    /*No inherited ext.*/ /*Ext. of ancestor*/
    /*New data for this type */
    const char ** map_p;                        /*Pointer to the current map*/
    lv_area_t *button_areas;                    /*Array of areas of buttons*/
    lv_btnm_action_t action;                    /*A function to call when a button is releases*/
    lv_style_t *styles_btn[LV_BTN_STATE_NUM];   /*Styles of buttons in each state*/
    uint16_t btn_cnt;                           /*Number of button in 'map_p'(Handled by the library)*/
    uint16_t btn_id_pr;                         /*Index of the currently pressed button (in `button_areas`) or LV_BTNM_PR_NONE*/
    uint16_t btn_id_tgl;                        /*Index of the currently toggled button (in `button_areas`) or LV_BTNM_PR_NONE */
    uint8_t toggle     :1;                      /*Enable toggling*/
    uint8_t	recolor    :1;                      /*Enable button recoloring*/
} lv_btnm_ext_t;

enum {
    LV_BTNM_STYLE_BG,
    LV_BTNM_STYLE_BTN_REL,
    LV_BTNM_STYLE_BTN_PR,
    LV_BTNM_STYLE_BTN_TGL_REL,
    LV_BTNM_STYLE_BTN_TGL_PR,
    LV_BTNM_STYLE_BTN_INA,
};
typedef uint8_t lv_btnm_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a button matrix objects
 * @param par pointer to an object, it will be the parent of the new button matrix
 * @param copy pointer to a button matrix object, if not NULL then the new object will be copied from it
 * @return pointer to the created button matrix
 */
lv_obj_t * lv_btnm_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a new map. Buttons will be created/deleted according to the map.
 * @param btnm pointer to a button matrix object
 * @param map pointer a string array. The last string has to be: "".
 *            Use "\n" to begin a new line.
 *            The first byte can be a control data:
 *             - bit 7: always 1
 *             - bit 6: always 0
 *             - bit 5: inactive (disabled)
 *             - bit 4: no repeat (on long press)
 *             - bit 3: hidden
 *             - bit 2..0: button relative width
 *             Example (practically use octal numbers): "\224abc": "abc" text with 4 width and no long press
 */
void lv_btnm_set_map(lv_obj_t * btnm, const char ** map);

/**
 * Set a new callback function for the buttons (It will be called when a button is released)
 * @param btnm: pointer to button matrix object
 * @param action pointer to a callback function
 */
void lv_btnm_set_action(lv_obj_t * btnm, lv_btnm_action_t action);

/**
 * Enable or disable button toggling
 * @param btnm pointer to button matrix object
 * @param en true: enable toggling; false: disable toggling
 * @param id index of the currently toggled button (ignored if 'en' == false)
 */
void lv_btnm_set_toggle(lv_obj_t * btnm, bool en, uint16_t id);

/**
 * Set a style of a button matrix
 * @param btnm pointer to a button matrix object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_btnm_set_style(lv_obj_t *btnm, lv_btnm_style_t type, lv_style_t *style);

/**
 * Set whether recoloring is enabled
 * @param btnm pointer to button matrix object
 * @param en whether recoloring is enabled
 */
void lv_btnm_set_recolor(const lv_obj_t * btnm, bool en);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the current map of a button matrix
 * @param btnm pointer to a button matrix object
 * @return the current map
 */
const char ** lv_btnm_get_map(const lv_obj_t * btnm);

/**
 * Get a the callback function of the buttons on a button matrix
 * @param btnm: pointer to button matrix object
 * @return pointer to the callback function
 */
lv_btnm_action_t lv_btnm_get_action(const lv_obj_t * btnm);

/**
 * Get the pressed button
 * @param btnm pointer to button matrix object
 * @return  index of the currently pressed button (LV_BTNM_PR_NONE: if unset)
 */
uint16_t lv_btnm_get_pressed(const lv_obj_t * btnm);

/**
 * Get the toggled button
 * @param btnm pointer to button matrix object
 * @return  index of the currently toggled button (LV_BTNM_PR_NONE: if unset)
 */
uint16_t lv_btnm_get_toggled(const lv_obj_t * btnm);

/**
 * Get a style of a button matrix
 * @param btnm pointer to a button matrix object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_btnm_get_style(const lv_obj_t *btnm, lv_btnm_style_t type);

/**
 * Find whether recoloring is enabled
 * @param btnm pointer to button matrix object
 * @return whether recoloring is enabled
 */
bool lv_btnm_get_recolor(const lv_obj_t * btnm);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_BTNM*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_BTNM_H*/

/* lv_calendar.h
 * Displays a calendar and lets the user pick a date.
 */
/**
 * @file lv_calendar.h
 *
 */

#ifndef LV_CALENDAR_H
#define LV_CALENDAR_H

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

#if USE_LV_CALENDAR != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    uint16_t year;
    int8_t month;
    int8_t day;
} lv_calendar_date_t;

enum
{
    LV_CALENDAR_ACTION_CLICK,
    LV_CALENDAR_ACTION_PR,
    LV_CALENDAR_ACTION_LONG_PR,
    LV_CALENDAR_ACTION_LONG_PR_REPEAT,
    LV_CALENDAR_ACTION_NUM,
};
typedef uint8_t lv_calendar_action_t;

/*Data of calendar*/
typedef struct {
    /*None*/ /*Ext. of ancestor*/
    /*New data for this type */
    lv_calendar_date_t today;          /*Date of today*/
    lv_calendar_date_t showed_date;   /*Currently visible month (day is ignored)*/
    lv_calendar_date_t * highlighted_dates;  /*Apply different style on these days (pointer to an array defined by the user)*/
    uint8_t highlighted_dates_num;           /*Number of elements in `highlighted_days`*/
    int8_t btn_pressing;                    /*-1: prev month pressing, +1 next month pressing on the header*/
    lv_calendar_date_t pressed_date;
    const char ** day_names;            /*Pointer to an array with the name of the days (NULL: use default names)*/
    const char ** month_names;          /*Pointer to an array with the name of the month (NULL. use default names)*/
    lv_action_t actions[LV_CALENDAR_ACTION_NUM];

    /*Styles*/
    lv_style_t * style_header;
    lv_style_t * style_header_pr;
    lv_style_t * style_day_names;
    lv_style_t * style_highlighted_days;
    lv_style_t * style_inactive_days;
    lv_style_t * style_week_box;
    lv_style_t * style_today_box;
} lv_calendar_ext_t;

/*Styles*/
enum {
    LV_CALENDAR_STYLE_BG,       /*Also the style of the "normal" date numbers*/
    LV_CALENDAR_STYLE_HEADER,
    LV_CALENDAR_STYLE_HEADER_PR,
    LV_CALENDAR_STYLE_DAY_NAMES,
    LV_CALENDAR_STYLE_HIGHLIGHTED_DAYS,
    LV_CALENDAR_STYLE_INACTIVE_DAYS,
    LV_CALENDAR_STYLE_WEEK_BOX,
    LV_CALENDAR_STYLE_TODAY_BOX,
};
typedef uint8_t lv_calendar_style_t;




/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a calendar objects
 * @param par pointer to an object, it will be the parent of the new calendar
 * @param copy pointer to a calendar object, if not NULL then the new object will be copied from it
 * @return pointer to the created calendar
 */
lv_obj_t * lv_calendar_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/


/*=====================
 * Setter functions
 *====================*/
/**
 * Set a function to call when a calendar event happens
 * @param calendar pointer to a calendar object
 * @param action type of event form 'lv_action_t' (press, release, long press, long press repeat)
 */
void lv_calendar_set_action(lv_obj_t * calendar, lv_calendar_action_t type, lv_action_t action);

/**
 * Set the today's date
 * @param calendar pointer to a calendar object
 * @param today pointer to an `lv_calendar_date_t` variable containing the date of today. The value will be saved it can be local variable too.
 */
void lv_calendar_set_today_date(lv_obj_t * calendar, lv_calendar_date_t * today);

/**
 * Set the currently showed
 * @param calendar pointer to a calendar object
 * @param showed pointer to an `lv_calendar_date_t` variable containing the date to show. The value will be saved it can be local variable too.
 */
void lv_calendar_set_showed_date(lv_obj_t * calendar, lv_calendar_date_t * showed);

/**
 * Set the the highlighted dates
 * @param calendar pointer to a calendar object
 * @param highlighted pointer to an `lv_calendar_date_t` array containing the dates. ONLY A POINTER WILL BE SAVED! CAN'T BE LOCAL ARRAY.
 * @param date_num number of dates in the array
 */
void lv_calendar_set_highlighted_dates(lv_obj_t * calendar, lv_calendar_date_t * highlighted, uint16_t date_num);


/**
 * Set the name of the days
 * @param calendar pointer to a calendar object
 * @param day_names pointer to an array with the names. E.g. `const char * days[7] = {"Sun", "Mon", ...}`
 *                  Only the pointer will be saved so this variable can't be local which will be destroyed later.
 */
void lv_calendar_set_day_names(lv_obj_t * calendar, const char ** day_names);

/**
 * Set the name of the month
 * @param calendar pointer to a calendar object
 * @param day_names pointer to an array with the names. E.g. `const char * days[12] = {"Jan", "Feb", ...}`
 *                  Only the pointer will be saved so this variable can't be local which will be destroyed later.
 */
void lv_calendar_set_month_names(lv_obj_t * calendar, const char ** day_names);

/**
 * Set a style of a calendar.
 * @param calendar pointer to calendar object
 * @param type which style should be set
 * @param style pointer to a style
 *  */
void lv_calendar_set_style(lv_obj_t * calendar, lv_calendar_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/
/**
 * Get the action of a calendar
 * @param calendar pointer to a calendar object
 * @return pointer to the action function
 */
lv_action_t lv_calendar_get_action(const lv_obj_t * calendar, lv_calendar_action_t type);

/**
 * Get the today's date
 * @param calendar pointer to a calendar object
 * @return return pointer to an `lv_calendar_date_t` variable containing the date of today.
 */
lv_calendar_date_t * lv_calendar_get_today_date(const lv_obj_t * calendar);

/**
 * Get the currently showed
 * @param calendar pointer to a calendar object
 * @return pointer to an `lv_calendar_date_t` variable containing the date is being shown.
 */
lv_calendar_date_t * lv_calendar_get_showed_date(const lv_obj_t * calendar);

/**
 * Get the the pressed date.
 * @param calendar pointer to a calendar object
 * @return pointer to an `lv_calendar_date_t` variable containing the pressed date.
 */
lv_calendar_date_t * lv_calendar_get_pressed_date(const lv_obj_t * calendar);

/**
 * Get the the highlighted dates
 * @param calendar pointer to a calendar object
 * @return pointer to an `lv_calendar_date_t` array containing the dates.
 */
lv_calendar_date_t * lv_calendar_get_highlighted_dates(const lv_obj_t * calendar);

/**
 * Get the number of the highlighted dates
 * @param calendar pointer to a calendar object
 * @return number of highlighted days
 */
uint16_t lv_calendar_get_highlighted_dates_num(const lv_obj_t * calendar);


/**
 * Get the name of the days
 * @param calendar pointer to a calendar object
 * @return pointer to the array of day names
 */
const char ** lv_calendar_get_day_names(const lv_obj_t * calendar);

/**
 * Get the name of the month
 * @param calendar pointer to a calendar object
 * @return pointer to the array of month names
 */
const char ** lv_calendar_get_month_names(const lv_obj_t * calendar);

/**
 * Get style of a calendar.
 * @param calendar pointer to calendar object
 * @param type which style should be get
 * @return style pointer to the style
 *  */
lv_style_t * lv_calendar_get_style(const lv_obj_t * calendar, lv_calendar_style_t type);

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_CALENDAR*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_CALENDAR_H*/

/* lv_img.h
 * Displays image data, image files, or supported symbols.
 */
/**
 * @file lv_img.h
 *
 */

#ifndef LV_IMG_H
#define LV_IMG_H

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

#if USE_LV_IMG != 0

#include "display/lv_core/lv_core.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_draw/lv_draw.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of image*/
typedef struct
{
    /*No inherited ext. because inherited from the base object*/ /*Ext. of ancestor*/
    /*New data for this type */
    const void * src;             /*Image source: Pointer to an array or a file or a symbol*/

    lv_coord_t w;               /*Width of the image (Handled by the library)*/
    lv_coord_t h;               /*Height of the image (Handled by the library)*/
#if USE_LV_MULTI_LANG
    uint16_t lang_txt_id;       /*The ID of the image to display. */
#endif
    uint8_t src_type  :2;       /*See: lv_img_src_t*/
    uint8_t auto_size :1;       /*1: automatically set the object size to the image size*/
    uint8_t cf :5;              /*Color format from `lv_img_color_format_t`*/
} lv_img_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create an image objects
 * @param par pointer to an object, it will be the parent of the new button
 * @param copy pointer to a image object, if not NULL then the new object will be copied from it
 * @return pointer to the created image
 */
lv_obj_t * lv_img_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the pixel map to display by the image
 * @param img pointer to an image object
 * @param data the image data
 */
void lv_img_set_src(lv_obj_t * img, const void * src_img);

#if USE_LV_MULTI_LANG
/**
 * Set an ID which means a the same source but on different languages
 * @param img pointer to an image object
 * @param src_id ID of the source
 */
void lv_img_set_src_id(lv_obj_t * img, uint32_t txt_id);
#endif

/**
 * Obsolete since v5.1. Just for compatibility with v5.0. Will be removed in v6.0.
 * Use 'lv_img_set_src()' instead.
 * @param img -
 * @param fn -
 */
static inline void lv_img_set_file(lv_obj_t * img, const char * fn)
{
    (void) img;
    (void) fn;
}

/**
 * Enable the auto size feature.
 * If enabled the object size will be same as the picture size.
 * @param img pointer to an image
 * @param en true: auto size enable, false: auto size disable
 */
void lv_img_set_auto_size(lv_obj_t * img, bool autosize_en);

/**
 * Set the style of an image
 * @param img pointer to an image object
 * @param style pointer to a style
 */
static inline void lv_img_set_style(lv_obj_t *img, lv_style_t *style)
{
    lv_obj_set_style(img, style);
}

/**
 * Obsolete since v5.1. Just for compatibility with v5.0. Will be removed in v6.0
 * @param img -
 * @param upscale -
 */
static inline void lv_img_set_upscale(lv_obj_t * img, bool upcale)
{
    (void) img;
    (void) upcale;
}

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the source of the image
 * @param img pointer to an image object
 * @return the image source (symbol, file name or C array)
 */
const void * lv_img_get_src(lv_obj_t * img);

/**
 * Get the name of the file set for an image
 * @param img pointer to an image
 * @return file name
 */
const char * lv_img_get_file_name(const lv_obj_t * img);

#if USE_LV_MULTI_LANG
/**
 * Get the source ID of the image. (Used by the multi-language feature)
 * @param img pointer to an image
 * @return ID of the source
 */
uint16_t lv_img_get_src_id(lv_obj_t * img);
#endif

/**
 * Get the auto size enable attribute
 * @param img pointer to an image
 * @return true: auto size is enabled, false: auto size is disabled
 */
bool lv_img_get_auto_size(const lv_obj_t * img);

/**
 * Get the style of an image object
 * @param img pointer to an image object
 * @return pointer to the image's style
 */
static inline lv_style_t* lv_img_get_style(const lv_obj_t *img)
{
    return lv_obj_get_style(img);
}

/**
 * Obsolete since v5.1. Just for compatibility with v5.0. Will be removed in v6.0
 * @param img -
 * @return false
 */
static inline bool lv_img_get_upscale(const lv_obj_t * img)
{
    (void)img;
    return false;
}

/**********************
 *      MACROS
 **********************/

/*Use this macro to declare an image in a c file*/
#define LV_IMG_DECLARE(var_name) extern const lv_img_dsc_t var_name;

#endif  /*USE_LV_IMG*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_IMG_H*/

/* lv_canvas.h
 * Draws into an image buffer supplied by the application.
 */
/**
 * @file lv_canvas.h
 *
 */

#ifndef LV_CANVAS_H
#define LV_CANVAS_H

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

#if USE_LV_CANVAS != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of canvas*/
typedef struct {
    lv_img_ext_t img; /*Ext. of ancestor*/
    /*New data for this type */
    lv_img_dsc_t dsc;
} lv_canvas_ext_t;


/*Styles*/
enum {
    LV_CANVAS_STYLE_MAIN,
};
typedef uint8_t lv_canvas_style_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a canvas object
 * @param par pointer to an object, it will be the parent of the new canvas
 * @param copy pointer to a canvas object, if not NULL then the new object will be copied from it
 * @return pointer to the created canvas
 */
lv_obj_t * lv_canvas_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a buffer for the canvas.
 * @param buf a buffer where the content of the canvas will be.
 * The required size is (lv_img_color_format_get_px_size(cf) * w * h) / 8)
 * It can be allocated with `lv_mem_alloc()` or
 * it can be statically allocated array (e.g. static lv_color_t buf[100*50]) or
 * it can be an address in RAM or external SRAM
 * @param canvas pointer to a canvas object
 * @param w width of the canvas
 * @param h height of the canvas
 * @param cf color format. The following formats are supported:
 *      LV_IMG_CF_TRUE_COLOR, LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED, LV_IMG_CF_INDEXES_1/2/4/8BIT
 */
void lv_canvas_set_buffer(lv_obj_t * canvas, void * buf, lv_coord_t w, lv_coord_t h, lv_img_cf_t cf);

/**
 * Set the color of a pixel on the canvas
 * @param canvas
 * @param x x coordinate of the point to set
 * @param y x coordinate of the point to set
 * @param c color of the point
 */
void lv_canvas_set_px(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y, lv_color_t c);

/**
 * Set a style of a canvas.
 * @param canvas pointer to canvas object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_canvas_set_style(lv_obj_t * canvas, lv_canvas_style_t type, lv_style_t * style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the color of a pixel on the canvas
 * @param canvas
 * @param x x coordinate of the point to set
 * @param y x coordinate of the point to set
 * @return color of the point
 */
lv_color_t lv_canvas_get_px(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y);

/**
 * Get style of a canvas.
 * @param canvas pointer to canvas object
 * @param type which style should be get
 * @return style pointer to the style
 */
lv_style_t * lv_canvas_get_style(const lv_obj_t * canvas, lv_canvas_style_t type);

/*=====================
 * Other functions
 *====================*/

/**
 * Copy a buffer to the canvas
 * @param canvas pointer to a canvas object
 * @param to_copy buffer to copy. The color format has to match with the canvas's buffer color format
 * @param w width of the buffer to copy
 * @param h height of the buffer to copy
 * @param x left side of the destination position
 * @param y top side of the destination position
 */
void lv_canvas_copy_buf(lv_obj_t * canvas, const void * to_copy, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y);

/**
 * Multiply a buffer with the canvas
 * @param canvas pointer to a canvas object
 * @param to_copy buffer to copy (multiply). LV_IMG_CF_TRUE_COLOR_ALPHA is not supported
 * @param w width of the buffer to copy
 * @param h height of the buffer to copy
 * @param x left side of the destination position
 * @param y top side of the destination position
 */
void lv_canvas_mult_buf(lv_obj_t * canvas, void * to_copy, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y);

/**
 * Draw circle function of the canvas
 * @param canvas pointer to a canvas object
 * @param x0 x coordinate of the circle
 * @param y0 y coordinate of the circle
 * @param radius radius of the circle
 * @param color border color of the circle
 */
void lv_canvas_draw_circle(lv_obj_t * canvas, lv_coord_t x0, lv_coord_t y0, lv_coord_t radius, lv_color_t color);

/**
 * Draw line function of the canvas
 * @param canvas pointer to a canvas object
 * @param point1 start point of the line
 * @param point2 end point of the line
 * @param color color of the line
 *
 * NOTE: The lv_canvas_draw_line function originates from https://github.com/jb55/bresenham-line.c.
 */
void lv_canvas_draw_line(lv_obj_t * canvas, lv_point_t point1, lv_point_t point2, lv_color_t color);

/**
 * Draw triangle function of the canvas
 * @param canvas pointer to a canvas object
 * @param points edge points of the triangle
 * @param color line color of the triangle
 */
void lv_canvas_draw_triangle(lv_obj_t * canvas, lv_point_t * points, lv_color_t color);

/**
 * Draw rectangle function of the canvas
 * @param canvas pointer to a canvas object
 * @param points edge points of the rectangle
 * @param color line color of the rectangle
 */
void lv_canvas_draw_rect(lv_obj_t * canvas, lv_point_t * points, lv_color_t color);

/**
 * Draw polygon function of the canvas
 * @param canvas pointer to a canvas object
 * @param points edge points of the polygon
 * @param size edge count of the polygon
 * @param color line color of the polygon
 */
void lv_canvas_draw_polygon(lv_obj_t * canvas, lv_point_t * points, size_t size, lv_color_t color);

/**
 * Fill polygon function of the canvas
 * @param canvas pointer to a canvas object
 * @param points edge points of the polygon
 * @param size edge count of the polygon
 * @param boundary_color line color of the polygon
 * @param fill_color fill color of the polygon
 */
void lv_canvas_fill_polygon(lv_obj_t * canvas, lv_point_t * points, size_t size, lv_color_t boundary_color, lv_color_t fill_color);
/**
 * Boundary fill function of the canvas
 * @param canvas pointer to a canvas object
 * @param x x coordinate of the start position (seed)
 * @param y y coordinate of the start position (seed)
 * @param boundary_color edge/boundary color of the area
 * @param fill_color fill color of the area
 */
void lv_canvas_boundary_fill4(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y, lv_color_t boundary_color, lv_color_t fill_color);

/**
 * Flood fill function of the canvas
 * @param canvas pointer to a canvas object
 * @param x x coordinate of the start position (seed)
 * @param y y coordinate of the start position (seed)
 * @param fill_color fill color of the area
 * @param bg_color background color of the area
 */
void lv_canvas_flood_fill(lv_obj_t * canvas, lv_coord_t x, lv_coord_t y, lv_color_t fill_color, lv_color_t bg_color);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_CANVAS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_CANVAS_H*/

/* lv_cb.h
 * Creates a checkbox with a label and checked state.
 */
/**
 * @file lv_cb.h
 *
 */

#ifndef LV_CB_H
#define LV_CB_H

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

#if USE_LV_CB != 0

/*Testing of dependencies*/
#if USE_LV_BTN == 0
#error "lv_cb: lv_btn is required. Enable it in lv_conf.h (USE_LV_BTN  1) "
#endif

#if USE_LV_LABEL == 0
#error "lv_cb: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of check box*/
typedef struct
{
    lv_btn_ext_t bg_btn; /*Ext. of ancestor*/
    /*New data for this type */
    lv_obj_t * bullet;  /*Pointer to button*/
    lv_obj_t * label;   /*Pointer to label*/
} lv_cb_ext_t;

enum {
    LV_CB_STYLE_BG,
    LV_CB_STYLE_BOX_REL,
    LV_CB_STYLE_BOX_PR,
    LV_CB_STYLE_BOX_TGL_REL,
    LV_CB_STYLE_BOX_TGL_PR,
    LV_CB_STYLE_BOX_INA,
};
typedef uint8_t lv_cb_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a check box objects
 * @param par pointer to an object, it will be the parent of the new check box
 * @param copy pointer to a check box object, if not NULL then the new object will be copied from it
 * @return pointer to the created check box
 */
lv_obj_t * lv_cb_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the text of a check box
 * @param cb pointer to a check box
 * @param txt the text of the check box
 */
void lv_cb_set_text(lv_obj_t * cb, const char * txt);

/**
 * Set the state of the check box
 * @param cb pointer to a check box object
 * @param checked true: make the check box checked; false: make it unchecked
 */
static inline void lv_cb_set_checked(lv_obj_t * cb, bool checked)
{
    lv_btn_set_state(cb, checked ? LV_BTN_STATE_TGL_REL : LV_BTN_STATE_REL);
}

/**
 * Make the check box inactive (disabled)
 * @param cb pointer to a check box object
 */
static inline void lv_cb_set_inactive(lv_obj_t * cb)
{
    lv_btn_set_state(cb, LV_BTN_STATE_INA);
}

/**
 * Set a function to call when the check box is clicked
 * @param cb pointer to a check box object
 */
static inline void lv_cb_set_action(lv_obj_t * cb, lv_action_t action)
{
    lv_btn_set_action(cb, LV_BTN_ACTION_CLICK, action);
}


/**
 * Set a style of a check box
 * @param cb pointer to check box object
 * @param type which style should be set
 * @param style pointer to a style
 *  */
void lv_cb_set_style(lv_obj_t * cb, lv_cb_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the text of a check box
 * @param cb pointer to check box object
 * @return pointer to the text of the check box
 */
const char * lv_cb_get_text(const lv_obj_t * cb);

/**
 * Get the current state of the check box
 * @param cb pointer to a check box object
 * @return true: checked; false: not checked
 */
static inline bool lv_cb_is_checked(const lv_obj_t * cb)
{
    return lv_btn_get_state(cb) == LV_BTN_STATE_REL ? false : true;
}

/**
 * Get the action of a check box
 * @param cb pointer to a button object
 * @return pointer to the action function
 */
static inline lv_action_t lv_cb_get_action(const lv_obj_t * cb)
{
    return lv_btn_get_action(cb, LV_BTN_ACTION_CLICK);
}


/**
 * Get a style of a button
 * @param cb pointer to check box object
 * @param type which style should be get
 * @return style pointer to the style
 *  */
lv_style_t * lv_cb_get_style(const lv_obj_t * cb, lv_cb_style_t type);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_CB*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_CB_H*/

/* lv_line.h
 * Displays connected points as line segments.
 */
/**
 * @file lv_line.h
 *
 */

#ifndef LV_LINE_H
#define LV_LINE_H

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

#if USE_LV_LINE != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of line*/
typedef struct
{
    /*Inherited from 'base_obj' so no inherited ext.*/  /*Ext. of ancestor*/
    const lv_point_t * point_array;    /*Pointer to an array with the points of the line*/
    uint16_t  point_num;            /*Number of points in 'point_array' */
    uint8_t  auto_size  :1;         /*1: set obj. width to x max and obj. height to y max */
    uint8_t  y_inv      :1;         /*1: y == 0 will be on the bottom*/
} lv_line_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**
 * Create a line objects
 * @param par pointer to an object, it will be the parent of the new line
 * @return pointer to the created line
 */
lv_obj_t * lv_line_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set an array of points. The line object will connect these points.
 * @param line pointer to a line object
 * @param point_a an array of points. Only the address is saved,
 * so the array can NOT be a local variable which will be destroyed
 * @param point_num number of points in 'point_a'
 */
void lv_line_set_points(lv_obj_t * line, const lv_point_t * point_a, uint16_t point_num);

/**
 * Enable (or disable) the auto-size option. The size of the object will fit to its points.
 * (set width to x max and height to y max)
 * @param line pointer to a line object
 * @param en true: auto size is enabled, false: auto size is disabled
 */
void lv_line_set_auto_size(lv_obj_t * line, bool en);

/**
 * Enable (or disable) the y coordinate inversion.
 * If enabled then y will be subtracted from the height of the object,
 * therefore the y=0 coordinate will be on the bottom.
 * @param line pointer to a line object
 * @param en true: enable the y inversion, false:disable the y inversion
 */
void lv_line_set_y_invert(lv_obj_t * line, bool en);

#define lv_line_set_y_inv lv_line_set_y_invert      /*The name was inconsistent. In v.6.0 only `lv_line_set_y_invert`will work */

/**
 * Set the style of a line
 * @param line pointer to a line object
 * @param style pointer to a style
 */
static inline void lv_line_set_style(lv_obj_t *line, lv_style_t *style)
{
    lv_obj_set_style(line, style);
}

/**
 * Obsolete since v5.1. Just for compatibility with v5.0. Will be removed in v6.0
 * @param line -
 * @param upscale -
 */
static inline void lv_line_set_upscale(lv_obj_t * line, bool upcale)
{
    (void) line;
    (void) upcale;
}
/*=====================
 * Getter functions
 *====================*/

/**
 * Get the auto size attribute
 * @param line pointer to a line object
 * @return true: auto size is enabled, false: disabled
 */
bool lv_line_get_auto_size(const lv_obj_t * line);

/**
 * Get the y inversion attribute
 * @param line pointer to a line object
 * @return true: y inversion is enabled, false: disabled
 */
bool lv_line_get_y_invert(const lv_obj_t * line);

/**
 * Get the style of an line object
 * @param line pointer to an line object
 * @return pointer to the line's style
 */
static inline lv_style_t* lv_line_get_style(const lv_obj_t *line)
{
    return lv_obj_get_style(line);
}

/**
 * Obsolete since v5.1. Just for compatibility with v5.0. Will be removed in v6.0
 * @param line -
 * @return false
 */
static inline bool lv_line_get_upscale(const lv_obj_t * line)
{
    (void) line;
    return false;
}


/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_LINE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_LINE_H*/

/* lv_chart.h
 * Plots one or more sets of data points.
 */
/**
 * @file lv_chart.h
 *
 */

#ifndef LV_CHART_H
#define LV_CHART_H

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

#if USE_LV_CHART != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/
#define LV_CHART_POINT_DEF  (LV_COORD_MIN)

/**********************
 *      TYPEDEFS
 **********************/
typedef struct
{
    lv_coord_t * points;
    lv_color_t color;
    uint16_t start_point;
} lv_chart_series_t;

/*Data of chart */
typedef struct
{
    /*No inherited ext*/ /*Ext. of ancestor*/
    /*New data for this type */
    lv_ll_t series_ll;       /*Linked list for the data line pointers (stores lv_chart_dl_t)*/
    lv_coord_t ymin;          /*y min value (used to scale the data)*/
    lv_coord_t ymax;          /*y max value (used to scale the data)*/
    uint8_t hdiv_cnt;     /*Number of horizontal division lines*/
    uint8_t vdiv_cnt;     /*Number of vertical division lines*/
    uint16_t point_cnt;   /*Point number in a data line*/
    uint8_t type    :4;   /*Line, column or point chart (from 'lv_chart_type_t')*/
    struct {
        lv_coord_t width;  /*Line width or point radius*/
        uint8_t num;       /*Number of data lines in dl_ll*/
        lv_opa_t opa;      /*Opacity of data lines*/
        lv_opa_t dark;     /*Dark level of the point/column bottoms*/
    } series;
} lv_chart_ext_t;

/*Chart types*/
enum
{
    LV_CHART_TYPE_LINE = 0x01,              /*Connect the points with lines*/
    LV_CHART_TYPE_COLUMN = 0x02,            /*Draw columns*/
    LV_CHART_TYPE_POINT = 0x04,             /*Draw circles on the points*/
    LV_CHART_TYPE_VERTICAL_LINE = 0x08,     /*Draw vertical lines on points (useful when chart width == point count)*/
};
typedef uint8_t lv_chart_type_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a chart background objects
 * @param par pointer to an object, it will be the parent of the new chart background
 * @param copy pointer to a chart background object, if not NULL then the new object will be copied from it
 * @return pointer to the created chart background
 */
lv_obj_t * lv_chart_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/

/**
 * Allocate and add a data series to the chart
 * @param chart pointer to a chart object
 * @param color color of the data series
 * @return pointer to the allocated data series
 */
lv_chart_series_t * lv_chart_add_series(lv_obj_t * chart, lv_color_t color);

/**
 * Clear the point of a serie
 * @param chart pointer to a chart object
 * @param serie pointer to the chart's serie to clear
 */
void lv_chart_clear_serie(lv_obj_t * chart, lv_chart_series_t * serie);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the number of horizontal and vertical division lines
 * @param chart pointer to a graph background object
 * @param hdiv number of horizontal division lines
 * @param vdiv number of vertical division lines
 */
void lv_chart_set_div_line_count(lv_obj_t * chart, uint8_t hdiv, uint8_t vdiv);

/**
 * Set the minimal and maximal y values
 * @param chart pointer to a graph background object
 * @param ymin y minimum value
 * @param ymax y maximum value
 */
void lv_chart_set_range(lv_obj_t * chart, lv_coord_t ymin, lv_coord_t ymax);

/**
 * Set a new type for a chart
 * @param chart pointer to a chart object
 * @param type new type of the chart (from 'lv_chart_type_t' enum)
 */
void lv_chart_set_type(lv_obj_t * chart, lv_chart_type_t type);

/**
 * Set the number of points on a data line on a chart
 * @param chart pointer r to chart object
 * @param point_cnt new number of points on the data lines
 */
void lv_chart_set_point_count(lv_obj_t * chart, uint16_t point_cnt);

/**
 * Set the opacity of the data series
 * @param chart pointer to a chart object
 * @param opa opacity of the data series
 */
void lv_chart_set_series_opa(lv_obj_t * chart, lv_opa_t opa);

/**
 * Set the line width or point radius of the data series
 * @param chart pointer to a chart object
 * @param width the new width
 */
void lv_chart_set_series_width(lv_obj_t * chart, lv_coord_t width);

/**
 * Set the dark effect on the bottom of the points or columns
 * @param chart pointer to a chart object
 * @param dark_eff dark effect level (LV_OPA_TRANSP to turn off)
 */
void lv_chart_set_series_darking(lv_obj_t * chart, lv_opa_t dark_eff);

/**
 * Initialize all data points with a value
 * @param chart pointer to chart object
 * @param ser pointer to a data series on 'chart'
 * @param y the new value  for all points
 */
void lv_chart_init_points(lv_obj_t * chart, lv_chart_series_t * ser, lv_coord_t y);

/**
 * Set the value s of points from an array
 * @param chart pointer to chart object
 * @param ser pointer to a data series on 'chart'
 * @param y_array array of 'lv_coord_t' points (with 'points count' elements )
 */
void lv_chart_set_points(lv_obj_t * chart, lv_chart_series_t * ser, lv_coord_t * y_array);

/**
 * Shift all data right and set the most right data on a data line
 * @param chart pointer to chart object
 * @param ser pointer to a data series on 'chart'
 * @param y the new value of the most right data
 */
void lv_chart_set_next(lv_obj_t * chart, lv_chart_series_t * ser, lv_coord_t y);

/**
 * Set the style of a chart
 * @param chart pointer to a chart object
 * @param style pointer to a style
 */
static inline void lv_chart_set_style(lv_obj_t *chart, lv_style_t *style)
{
    lv_obj_set_style(chart, style);
}

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the type of a chart
 * @param chart pointer to chart object
 * @return type of the chart (from 'lv_chart_t' enum)
 */
lv_chart_type_t lv_chart_get_type(const lv_obj_t * chart);

/**
 * Get the data point number per data line on chart
 * @param chart pointer to chart object
 * @return point number on each data line
 */
uint16_t lv_chart_get_point_cnt(const lv_obj_t * chart);

/**
 * Get the opacity of the data series
 * @param chart pointer to chart object
 * @return the opacity of the data series
 */
lv_opa_t lv_chart_get_series_opa(const lv_obj_t * chart);

/**
 * Get the data series width
 * @param chart pointer to chart object
 * @return the width the data series (lines or points)
 */
lv_coord_t lv_chart_get_series_width(const lv_obj_t * chart);

/**
 * Get the dark effect level on the bottom of the points or columns
 * @param chart pointer to chart object
 * @return dark effect level (LV_OPA_TRANSP to turn off)
 */
lv_opa_t lv_chart_get_series_darking(const lv_obj_t * chart);

/**
 * Get the style of an chart object
 * @param chart pointer to an chart object
 * @return pointer to the chart's style
 */
static inline lv_style_t* lv_chart_get_style(const lv_obj_t *chart)
{
    return lv_obj_get_style(chart);
}

/*=====================
 * Other functions
 *====================*/

/**
 * Refresh a chart if its data line has changed
 * @param chart pointer to chart object
 */
void lv_chart_refresh(lv_obj_t * chart);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_CHART*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_CHART_H*/

/* lv_page.h
 * Provides a container with a scrollable child area.
 */
/**
 * @file lv_page.h
 *
 */

#ifndef LV_PAGE_H
#define LV_PAGE_H

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

#if USE_LV_PAGE != 0

/*Testing of dependencies*/
#if USE_LV_CONT == 0
#error "lv_page: lv_cont is required. Enable it in lv_conf.h (USE_LV_CONT  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Scrollbar modes: shows when should the scrollbars be visible*/
enum
{
    LV_SB_MODE_OFF  = 0x0,      /*Never show scrollbars*/
    LV_SB_MODE_ON   = 0x1,      /*Always show scrollbars*/
    LV_SB_MODE_DRAG = 0x2,      /*Show scrollbars when page is being dragged*/
    LV_SB_MODE_AUTO = 0x3,      /*Show scrollbars when the scrollable container is large enough to be scrolled*/
    LV_SB_MODE_HIDE = 0x4,      /*Hide the scroll bar temporally*/
    LV_SB_MODE_UNHIDE = 0x5,    /*Unhide the previously hidden scrollbar. Recover it's type too*/
};
typedef uint8_t lv_sb_mode_t;

/*Data of page*/
typedef struct
{
    lv_cont_ext_t bg; /*Ext. of ancestor*/
    /*New data for this type */
    lv_obj_t * scrl;            /*The scrollable object on the background*/
    lv_action_t rel_action;     /*Function to call when the page is released*/
    lv_action_t pr_action;      /*Function to call when the page is pressed*/
    struct {
        lv_style_t *style;          /*Style of scrollbars*/
        lv_area_t hor_area;            /*Horizontal scrollbar area relative to the page. (Handled by the library) */
        lv_area_t ver_area;            /*Vertical scrollbar area relative to the page (Handled by the library)*/
        uint8_t hor_draw :1;        /*1: horizontal scrollbar is visible now (Handled by the library)*/
        uint8_t ver_draw :1;        /*1: vertical scrollbar is visible now (Handled by the library)*/
        lv_sb_mode_t mode:3;        /*Scrollbar visibility from 'lv_page_sb_mode_t'*/
    } sb;
    struct {
        uint16_t state;  /*Store the current size of the edge flash effect*/
        lv_style_t *style;    /*Style of edge flash effect (usually homogeneous circle)*/
        uint8_t enabled    :1;     /*1: Show a flash animation on the edge*/
        uint8_t top_ip     :1;     /*Used internally to show that top most position is reached (flash is In Progress)*/
        uint8_t bottom_ip  :1;     /*Used internally to show that bottom most position is reached (flash is In Progress)*/
        uint8_t right_ip   :1;     /*Used internally to show that right most position is reached (flash is In Progress)*/
        uint8_t left_ip    :1;     /*Used internally to show that left most position is reached (flash is In Progress)*/
    }edge_flash;

    uint8_t arrow_scroll   :1;        /*1: Enable scrolling with LV_GROUP_KEY_LEFT/RIGHT/UP/DOWN*/
    uint8_t scroll_prop    :1;        /*1: Propagate the scrolling the the parent if the edge is reached*/
    uint8_t scroll_prop_ip :1;        /*1: Scroll propagation is in progress (used by the library)*/
} lv_page_ext_t;

enum {
    LV_PAGE_STYLE_BG,
    LV_PAGE_STYLE_SCRL,
    LV_PAGE_STYLE_SB,
    LV_PAGE_STYLE_EDGE_FLASH,
};
typedef uint8_t lv_page_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a page objects
 * @param par pointer to an object, it will be the parent of the new page
 * @param copy pointer to a page object, if not NULL then the new object will be copied from it
 * @return pointer to the created page
 */
lv_obj_t * lv_page_create(lv_obj_t * par, const lv_obj_t * copy);

/**
 * Delete all children of the scrl object, without deleting scrl child.
 * @param obj pointer to an object
 */
void lv_page_clean(lv_obj_t *obj);

/**
 * Get the press action of the page
 * @param page pointer to a page object
 * @return a function to call when the page is pressed
 */
lv_action_t lv_page_get_pr_action(lv_obj_t * page);

/**
 * Get the release action of the page
 * @param page pointer to a page object
 * @return a function to call when the page is released
 */
lv_action_t lv_page_get_rel_action(lv_obj_t * page);

/**
 * Get the scrollable object of a page
 * @param page pointer to a page object
 * @return pointer to a container which is the scrollable part of the page
 */
lv_obj_t * lv_page_get_scrl(const lv_obj_t * page);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a release action for the page
 * @param page pointer to a page object
 * @param rel_action a function to call when the page is released
 */
void lv_page_set_rel_action(lv_obj_t * page, lv_action_t rel_action);

/**
 * Set a press action for the page
 * @param page pointer to a page object
 * @param pr_action a function to call when the page is pressed
 */
void lv_page_set_pr_action(lv_obj_t * page, lv_action_t pr_action);

/**
 * Set the scroll bar mode on a page
 * @param page pointer to a page object
 * @param sb_mode the new mode from 'lv_page_sb.mode_t' enum
 */
void lv_page_set_sb_mode(lv_obj_t * page, lv_sb_mode_t sb_mode);

/**
 * Enable/Disable scrolling with arrows if the page is in group (arrows: LV_GROUP_KEY_LEFT/RIGHT/UP/DOWN)
 * @param page pointer to a page object
 * @param en true: enable scrolling with arrows
 */
void lv_page_set_arrow_scroll(lv_obj_t * page, bool en);

/**
 * Enable the scroll propagation feature. If enabled then the page will move its parent if there is no more space to scroll.
 * @param page pointer to a Page
 * @param en true or false to enable/disable scroll propagation
 */
void lv_page_set_scroll_propagation(lv_obj_t * page, bool en);

/**
 * Enable the edge flash effect. (Show an arc when the an edge is reached)
 * @param page pointer to a Page
 * @param en true or false to enable/disable end flash
 */
void lv_page_set_edge_flash(lv_obj_t * page, bool en);

/**
 * Set the fit attribute of the scrollable part of a page.
 * It means it can set its size automatically to involve all children.
 * (Can be set separately horizontally and vertically)
 * @param page pointer to a page object
 * @param hor_en true: enable horizontal fit
 * @param ver_en true: enable vertical fit
 */
static inline void lv_page_set_scrl_fit(lv_obj_t *page, bool hor_en, bool ver_en)
{
    lv_cont_set_fit(lv_page_get_scrl(page), hor_en, ver_en);
}

/**
 * Set width of the scrollable part of a page
 * @param page pointer to a page object
 * @param w the new width of the scrollable (it ha no effect is horizontal fit is enabled)
 */
static inline void lv_page_set_scrl_width(lv_obj_t *page, lv_coord_t w)
{
    lv_obj_set_width(lv_page_get_scrl(page), w);
}

/**
 * Set height of the scrollable part of a page
 * @param page pointer to a page object
 * @param h the new height of the scrollable (it ha no effect is vertical fit is enabled)
 */
static inline void lv_page_set_scrl_height(lv_obj_t *page, lv_coord_t h)
{
    lv_obj_set_height(lv_page_get_scrl(page), h);

}

/**
* Set the layout of the scrollable part of the page
* @param page pointer to a page object
* @param layout a layout from 'lv_cont_layout_t'
*/
static inline void lv_page_set_scrl_layout(lv_obj_t * page, lv_layout_t layout)
{
    lv_cont_set_layout(lv_page_get_scrl(page), layout);
}

/**
 * Set a style of a page
 * @param page pointer to a page object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_page_set_style(lv_obj_t *page, lv_page_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Set the scroll bar mode on a page
 * @param page pointer to a page object
 * @return the mode from 'lv_page_sb.mode_t' enum
 */
lv_sb_mode_t lv_page_get_sb_mode(const lv_obj_t * page);


/**
 * Get the the scrolling with arrows (LV_GROUP_KEY_LEFT/RIGHT/UP/DOWN) is enabled or not
 * @param page pointer to a page object
 * @return true: scrolling with arrows is enabled
 */
bool lv_page_get_arrow_scroll(const lv_obj_t * page);

/**
 * Get the scroll propagation property
 * @param page pointer to a Page
 * @return true or false
 */
bool lv_page_get_scroll_propagation(lv_obj_t * page);

/**
 * Get the edge flash effect property.
 * @param page pointer to a Page
 * return true or false
 */
bool lv_page_get_edge_flash(lv_obj_t * page);

/**
 * Get that width which can be set to the children to still not cause overflow (show scrollbars)
 * @param page pointer to a page object
 * @return the width which still fits into the page
 */
lv_coord_t lv_page_get_fit_width(lv_obj_t * page);

/**
 * Get that height which can be set to the children to still not cause overflow (show scrollbars)
 * @param page pointer to a page object
 * @return the height which still fits into the page
 */
lv_coord_t lv_page_get_fit_height(lv_obj_t * page);

/**
 * Get width of the scrollable part of a page
 * @param page pointer to a page object
 * @return the width of the scrollable
 */
static inline lv_coord_t lv_page_get_scrl_width(const lv_obj_t *page)
{
    return lv_obj_get_width(lv_page_get_scrl(page));
}

/**
 * Get height of the scrollable part of a page
 * @param page pointer to a page object
 * @return the height of the scrollable
 */
static inline lv_coord_t lv_page_get_scrl_height(const lv_obj_t *page)
{
    return lv_obj_get_height(lv_page_get_scrl(page));
}

/**
* Get the layout of the scrollable part of a page
* @param page pointer to page object
* @return the layout from 'lv_cont_layout_t'
*/
static inline lv_layout_t lv_page_get_scrl_layout(const lv_obj_t * page)
{
    return lv_cont_get_layout(lv_page_get_scrl(page));
}

/**
* Get horizontal fit attribute of the scrollable part of a page
* @param page pointer to a page object
* @return true: horizontal fit is enabled; false: disabled
*/
static inline bool lv_page_get_scrl_hor_fit(const lv_obj_t * page)
{
    return lv_cont_get_hor_fit(lv_page_get_scrl(page));
}

/**
* Get vertical fit attribute of the scrollable part of a page
* @param page pointer to a page object
* @return true: vertical fit is enabled; false: disabled
*/
static inline bool lv_page_get_scrl_fit_ver(const lv_obj_t * page)
{
    return lv_cont_get_ver_fit(lv_page_get_scrl(page));
}

/**
 * Get a style of a page
 * @param page pointer to page object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_page_get_style(const lv_obj_t *page, lv_page_style_t type);

/*=====================
 * Other functions
 *====================*/

/**
 * Glue the object to the page. After it the page can be moved (dragged) with this object too.
 * @param obj pointer to an object on a page
 * @param glue true: enable glue, false: disable glue
 */
void lv_page_glue_obj(lv_obj_t * obj, bool glue);

/**
 * Focus on an object. It ensures that the object will be visible on the page.
 * @param page pointer to a page object
 * @param obj pointer to an object to focus (must be on the page)
 * @param anim_time scroll animation time in milliseconds (0: no animation)
 */
void lv_page_focus(lv_obj_t * page, const lv_obj_t * obj, uint16_t anim_time);

/**
 * Scroll the page horizontally
 * @param page pointer to a page object
 * @param dist the distance to scroll (< 0: scroll left; > 0 scroll right)
 */
void lv_page_scroll_hor(lv_obj_t * page, lv_coord_t dist);

/**
 * Scroll the page vertically
 * @param page pointer to a page object
 * @param dist the distance to scroll (< 0: scroll down; > 0 scroll up)
 */
void lv_page_scroll_ver(lv_obj_t * page, lv_coord_t dist);

/**
 * Not intended to use directly by the user but by other object types internally.
 * Start an edge flash animation. Exactly one `ext->edge_flash.xxx_ip` should be set
 * @param page
 */
void lv_page_start_edge_flash(lv_obj_t * page);
/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_PAGE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_PAGE_H*/

/* lv_ddlist.h
 * Presents a list of options that expands when selected.
 */
/**
 * @file lv_ddlist.h
 *
 */

#ifndef LV_DDLIST_H
#define LV_DDLIST_H

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

#if USE_LV_DDLIST != 0

/*Testing of dependencies*/
#if USE_LV_PAGE == 0
#error "lv_ddlist: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#if USE_LV_LABEL == 0
#error "lv_ddlist: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of drop down list*/
typedef struct
{
    lv_page_ext_t page; /*Ext. of ancestor*/
    /*New data for this type */
    lv_obj_t *label;                     /*Label for the options*/
    lv_style_t * sel_style;              /*Style of the selected option*/
    lv_action_t action;                  /*Pointer to function to call when an option is selected*/
    uint16_t option_cnt;                 /*Number of options*/
    uint16_t sel_opt_id;                 /*Index of the current option*/
    uint16_t sel_opt_id_ori;             /*Store the original index on focus*/
    uint16_t anim_time;                  /*Open/Close animation time [ms]*/
    uint8_t opened :1;                   /*1: The list is opened (handled by the library)*/
    uint8_t draw_arrow :1;               /*1: Draw arrow*/

    lv_coord_t fix_height;               /*Height of the ddlist when opened. (0: auto-size)*/
} lv_ddlist_ext_t;

enum {
    LV_DDLIST_STYLE_BG,
    LV_DDLIST_STYLE_SEL,
    LV_DDLIST_STYLE_SB,
};
typedef uint8_t lv_ddlist_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * Create a drop down list objects
 * @param par pointer to an object, it will be the parent of the new drop down list
 * @param copy pointer to a drop down list object, if not NULL then the new object will be copied from it
 * @return pointer to the created drop down list
 */
lv_obj_t * lv_ddlist_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set arrow draw in a drop down list
 * @param ddlist pointer to drop down list object
 * @param en enable/disable a arrow draw. E.g. "true" for draw.
 */
void lv_ddlist_set_draw_arrow(lv_obj_t * ddlist, bool en);

/**
 * Set the options in a drop down list from a string
 * @param ddlist pointer to drop down list object
 * @param options a string with '\n' separated options. E.g. "One\nTwo\nThree"
 */
void lv_ddlist_set_options(lv_obj_t * ddlist, const char * options);

/**
 * Set the selected option
 * @param ddlist pointer to drop down list object
 * @param sel_opt id of the selected option (0 ... number of option - 1);
 */
void lv_ddlist_set_selected(lv_obj_t * ddlist, uint16_t sel_opt);

/**
 * Set a function to call when a new option is chosen
 * @param ddlist pointer to a drop down list
 * @param action pointer to a call back function
 */
void lv_ddlist_set_action(lv_obj_t * ddlist, lv_action_t action);

/**
 * Set the fix height for the drop down list
 * If 0 then the opened ddlist will be auto. sized else the set height will be applied.
 * @param ddlist pointer to a drop down list
 * @param h the height when the list is opened (0: auto size)
 */
void lv_ddlist_set_fix_height(lv_obj_t * ddlist, lv_coord_t h);

/**
 * Enable or disable the horizontal fit to the content
 * @param ddlist pointer to a drop down list
 * @param en true: enable auto fit; false: disable auto fit
 */
void lv_ddlist_set_hor_fit(lv_obj_t * ddlist, bool en);

/**
 * Set the scroll bar mode of a drop down list
 * @param ddlist pointer to a drop down list object
 * @param sb_mode the new mode from 'lv_page_sb_mode_t' enum
 */
static inline void lv_ddlist_set_sb_mode(lv_obj_t * ddlist, lv_sb_mode_t mode)
{
    lv_page_set_sb_mode(ddlist, mode);
}

/**
 * Set the open/close animation time.
 * @param ddlist pointer to a drop down list
 * @param anim_time: open/close animation time [ms]
 */
void lv_ddlist_set_anim_time(lv_obj_t * ddlist, uint16_t anim_time);


/**
 * Set a style of a drop down list
 * @param ddlist pointer to a drop down list object
 * @param type which style should be set
 * @param style pointer to a style
 *  */
void lv_ddlist_set_style(lv_obj_t *ddlist, lv_ddlist_style_t type, lv_style_t *style);

/**
 * Set the alignment of the labels in a drop down list
 * @param ddlist pointer to a drop down list object
 * @param align alignment of labels
 */
void lv_ddlist_set_align(lv_obj_t *ddlist, lv_label_align_t align);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get arrow draw in a drop down list
 * @param ddlist pointer to drop down list object
 */
bool lv_ddlist_get_draw_arrow(lv_obj_t * ddlist);

/**
 * Get the options of a drop down list
 * @param ddlist pointer to drop down list object
 * @return the options separated by '\n'-s (E.g. "Option1\nOption2\nOption3")
 */
const char * lv_ddlist_get_options(const lv_obj_t * ddlist);

/**
 * Get the selected option
 * @param ddlist pointer to drop down list object
 * @return id of the selected option (0 ... number of option - 1);
 */
uint16_t lv_ddlist_get_selected(const lv_obj_t * ddlist);

/**
 * Get the current selected option as a string
 * @param ddlist pointer to ddlist object
 * @param buf pointer to an array to store the string
 */
void lv_ddlist_get_selected_str(const lv_obj_t * ddlist, char * buf);

/**
 * Get the "option selected" callback function
 * @param ddlist pointer to a drop down list
 * @return  pointer to the call back function
 */
lv_action_t lv_ddlist_get_action(const lv_obj_t * ddlist);

/**
 * Get the fix height value.
 * @param ddlist pointer to a drop down list object
 * @return the height if the ddlist is opened (0: auto size)
 */
lv_coord_t lv_ddlist_get_fix_height(const lv_obj_t * ddlist);

/**
 * Get the scroll bar mode of a drop down list
 * @param ddlist pointer to a  drop down list object
 * @return scrollbar mode from 'lv_page_sb_mode_t' enum
 */
static inline lv_sb_mode_t lv_ddlist_get_sb_mode(const lv_obj_t * ddlist)
{
    return lv_page_get_sb_mode(ddlist);
}

/**
 * Get the open/close animation time.
 * @param ddlist pointer to a drop down list
 * @return open/close animation time [ms]
 */
uint16_t lv_ddlist_get_anim_time(const lv_obj_t * ddlist);

/**
 * Get a style of a drop down list
 * @param ddlist pointer to a drop down list object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_ddlist_get_style(const lv_obj_t *ddlist, lv_ddlist_style_t type);

/**
 * Get the alignment of the labels in a drop down list
 * @param ddlist pointer to a drop down list object
 * @return alignment of labels
 */
lv_label_align_t lv_ddlist_get_align(const lv_obj_t *ddlist);

/*=====================
 * Other functions
 *====================*/

/**
 * Open the drop down list with or without animation
 * @param ddlist pointer to drop down list object
 * @param anim_en true: use animation; false: not use animations
 */
void lv_ddlist_open(lv_obj_t * ddlist, bool anim_en);

/**
 * Close (Collapse) the drop down list
 * @param ddlist pointer to drop down list object
 * @param anim_en true: use animation; false: not use animations
 */
void lv_ddlist_close(lv_obj_t * ddlist, bool anim_en);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_DDLIST*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_DDLIST_H*/

/* lv_lmeter.h
 * Displays values using marks around a circular scale.
 */
/**
 * @file lv_lmeter.h
 *
 */

#ifndef LV_LMETER_H
#define LV_LMETER_H

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

#if USE_LV_LMETER != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of line meter*/
typedef struct
{
    /*No inherited ext.*/            /*Ext. of ancestor*/
    /*New data for this type */
    uint16_t scale_angle;        /*Angle of the scale in deg. (0..360)*/
    uint8_t line_cnt;            /*Count of lines */
    int16_t cur_value;
    int16_t min_value;
    int16_t max_value;
} lv_lmeter_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a line meter objects
 * @param par pointer to an object, it will be the parent of the new line meter
 * @param copy pointer to a line meter object, if not NULL then the new object will be copied from it
 * @return pointer to the created line meter
 */
lv_obj_t * lv_lmeter_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a new value on the line meter
 * @param lmeter pointer to a line meter object
 * @param value new value
 */
void lv_lmeter_set_value(lv_obj_t *lmeter, int16_t value);

/**
 * Set minimum and the maximum values of a line meter
 * @param lmeter pointer to he line meter object
 * @param min minimum value
 * @param max maximum value
 */
void lv_lmeter_set_range(lv_obj_t *lmeter, int16_t min, int16_t max);

/**
 * Set the scale settings of a line meter
 * @param lmeter pointer to a line meter object
 * @param angle angle of the scale (0..360)
 * @param line_cnt number of lines
 */
void lv_lmeter_set_scale(lv_obj_t * lmeter, uint16_t angle, uint8_t line_cnt);

/**
 * Set the styles of a line meter
 * @param lmeter pointer to a line meter object
 * @param bg set the style of the line meter
 */
static inline void lv_lmeter_set_style(lv_obj_t *lmeter, lv_style_t *bg)
{
    lv_obj_set_style(lmeter, bg);
}

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the value of a line meter
 * @param lmeter pointer to a line meter object
 * @return the value of the line meter
 */
int16_t lv_lmeter_get_value(const lv_obj_t *lmeter);

/**
 * Get the minimum value of a line meter
 * @param lmeter pointer to a line meter object
 * @return the minimum value of the line meter
 */
int16_t lv_lmeter_get_min_value(const lv_obj_t * lmeter);

/**
 * Get the maximum value of a line meter
 * @param lmeter pointer to a line meter object
 * @return the maximum value of the line meter
 */
int16_t lv_lmeter_get_max_value(const lv_obj_t * lmeter);

/**
 * Get the scale number of a line meter
 * @param lmeter pointer to a line meter object
 * @return number of the scale units
 */
uint8_t lv_lmeter_get_line_count(const lv_obj_t * lmeter);

/**
 * Get the scale angle of a line meter
 * @param lmeter pointer to a line meter object
 * @return angle of the scale
 */
uint16_t lv_lmeter_get_scale_angle(const lv_obj_t * lmeter);

/**
 * Get the style of a line meter
 * @param lmeter pointer to a line meter object
 * @return pointer to the line meter's style
 */
static inline lv_style_t * lv_lmeter_get_style(const lv_obj_t * lmeter)
{
    return lv_obj_get_style(lmeter);
}

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_LMETER*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_LMETER_H*/

/* lv_gauge.h
 * Displays values with needles on a dial.
 */
/**
 * @file lv_gauge.h
 *
 */

#ifndef LV_GAUGE_H
#define LV_GAUGE_H

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

#if USE_LV_GAUGE != 0

/*Testing of dependencies*/
#if USE_LV_LMETER == 0
#error "lv_gauge: lv_lmeter is required. Enable it in lv_conf.h (USE_LV_LMETER  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of gauge*/
typedef struct
{
    lv_lmeter_ext_t lmeter;     /*Ext. of ancestor*/
    /*New data for this type */
    int16_t * values;               /*Array of the set values (for needles) */
    const lv_color_t * needle_colors;        /*Color of the needles (lv_color_t my_colors[needle_num])*/
    uint8_t needle_count;             /*Number of needles*/
    uint8_t label_count;              /*Number of labels on the scale*/
} lv_gauge_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a gauge objects
 * @param par pointer to an object, it will be the parent of the new gauge
 * @param copy pointer to a gauge object, if not NULL then the new object will be copied from it
 * @return pointer to the created gauge
 */
lv_obj_t * lv_gauge_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the number of needles
 * @param gauge pointer to gauge object
 * @param needle_cnt new count of needles
 * @param colors an array of colors for needles (with 'num' elements)
 */
void lv_gauge_set_needle_count(lv_obj_t * gauge, uint8_t needle_cnt, const lv_color_t * colors);

/**
 * Set the value of a needle
 * @param gauge pointer to a gauge
 * @param needle_id the id of the needle
 * @param value the new value
 */
void lv_gauge_set_value(lv_obj_t * gauge, uint8_t needle_id, int16_t value);

/**
 * Set minimum and the maximum values of a gauge
 * @param gauge pointer to he gauge object
 * @param min minimum value
 * @param max maximum value
 */
static inline void lv_gauge_set_range(lv_obj_t *gauge, int16_t min, int16_t max)
{
    lv_lmeter_set_range(gauge, min, max);
}

/**
 * Set a critical value on the scale. After this value 'line.color' scale lines will be drawn
 * @param gauge pointer to a gauge object
 * @param value the critical value
 */
static inline void lv_gauge_set_critical_value(lv_obj_t * gauge, int16_t value)
{
    lv_lmeter_set_value(gauge, value);
}

/**
 * Set the scale settings of a gauge
 * @param gauge pointer to a gauge object
 * @param angle angle of the scale (0..360)
 * @param line_cnt count of scale lines.
 * The get a given "subdivision" lines between label, `line_cnt` = (sub_div + 1) * (label_cnt - 1) + 1
 * @param label_cnt count of scale labels.
 */
void lv_gauge_set_scale(lv_obj_t * gauge, uint16_t angle, uint8_t line_cnt, uint8_t label_cnt);

/**
 * Set the styles of a gauge
 * @param gauge pointer to a gauge object
 * @param bg set the style of the gauge
 *  */
static inline void lv_gauge_set_style(lv_obj_t *gauge, lv_style_t *bg)
{
    lv_obj_set_style(gauge, bg);
}

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the value of a needle
 * @param gauge pointer to gauge object
 * @param needle the id of the needle
 * @return the value of the needle [min,max]
 */
int16_t lv_gauge_get_value(const lv_obj_t * gauge,  uint8_t needle);

/**
 * Get the count of needles on a gauge
 * @param gauge pointer to gauge
 * @return count of needles
 */
uint8_t lv_gauge_get_needle_count(const lv_obj_t * gauge);

/**
 * Get the minimum value of a gauge
 * @param gauge pointer to a gauge object
 * @return the minimum value of the gauge
 */
static inline int16_t lv_gauge_get_min_value(const lv_obj_t * lmeter)
{
    return lv_lmeter_get_min_value(lmeter);
}

/**
 * Get the maximum value of a gauge
 * @param gauge pointer to a gauge object
 * @return the maximum value of the gauge
 */
static inline int16_t lv_gauge_get_max_value(const lv_obj_t * lmeter)
{
    return lv_lmeter_get_max_value(lmeter);
}

/**
 * Get a critical value on the scale.
 * @param gauge pointer to a gauge object
 * @return the critical value
 */
static inline int16_t lv_gauge_get_critical_value(const lv_obj_t * gauge)
{
    return lv_lmeter_get_value(gauge);
}

/**
 * Set the number of labels (and the thicker lines too)
 * @param gauge pointer to a gauge object
 * @return count of labels
 */
uint8_t lv_gauge_get_label_count(const lv_obj_t * gauge);

/**
 * Get the scale number of a gauge
 * @param gauge pointer to a gauge object
 * @return number of the scale units
 */
static inline uint8_t lv_gauge_get_line_count(const lv_obj_t * gauge)
{
    return lv_lmeter_get_line_count(gauge);
}

/**
 * Get the scale angle of a gauge
 * @param gauge pointer to a gauge object
 * @return angle of the scale
 */
static inline uint16_t lv_gauge_get_scale_angle(const lv_obj_t * gauge)
{
    return lv_lmeter_get_scale_angle(gauge);
}

/**
 * Get the style of a gauge
 * @param gauge pointer to a gauge object
 * @return pointer to the gauge's style
 */
static inline lv_style_t * lv_gauge_get_style(const lv_obj_t *gauge)
{
    return lv_obj_get_style(gauge);
}

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_GAUGE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_GAUGE_H*/

/* lv_imgbtn.h
 * Uses different images for different states of a button.
 */
/**
 * @file lv_imgbtn.h
 *
 */

#ifndef LV_IMGBTN_H
#define LV_IMGBTN_H

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

#if USE_LV_IMGBTN != 0

/*Testing of dependencies*/
#if USE_LV_BTN == 0
#error "lv_imgbtn: lv_btn is required. Enable it in lv_conf.h (USE_LV_BTN  1) "
#endif

#include "display/lv_core/lv_core.h"
#include "display/lv_draw/lv_draw.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of image button*/
typedef struct {
    lv_btn_ext_t btn; /*Ext. of ancestor*/
    /*New data for this type */
#if LV_IMGBTN_TILED == 0
    const void * img_src[LV_BTN_STATE_NUM];       /*Store images to each state*/
#else
    const void * img_src_left[LV_BTN_STATE_NUM];       /*Store left side images to each state*/
    const void * img_src_mid[LV_BTN_STATE_NUM];        /*Store center images to each state*/
    const void * img_src_right[LV_BTN_STATE_NUM];      /*Store right side images to each state*/
#endif
    lv_img_cf_t act_cf;           /*Color format of the currently active image*/
} lv_imgbtn_ext_t;


/*Styles*/
enum {
    LV_IMGBTN_STYLE_REL,
    LV_IMGBTN_STYLE_PR,
    LV_IMGBTN_STYLE_TGL_REL,
    LV_IMGBTN_STYLE_TGL_PR,
    LV_IMGBTN_STYLE_INA,
};
typedef uint8_t lv_imgbtn_style_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a image button objects
 * @param par pointer to an object, it will be the parent of the new image button
 * @param copy pointer to a image button object, if not NULL then the new object will be copied from it
 * @return pointer to the created image button
 */
lv_obj_t * lv_imgbtn_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/


/*=====================
 * Setter functions
 *====================*/

#if LV_IMGBTN_TILED == 0
/**
 * Set images for a state of the image button
 * @param imgbtn pointer to an image button object
 * @param state for which state set the new image (from `lv_btn_state_t`) `
 * @param src pointer to an image source (a C array or path to a file)
 */
void lv_imgbtn_set_src(lv_obj_t * imgbtn, lv_btn_state_t state, const void * src);
#else
/**
 * Set images for a state of the image button
 * @param imgbtn pointer to an image button object
 * @param state for which state set the new image (from `lv_btn_state_t`) `
 * @param src_left pointer to an image source for the left side of the button (a C array or path to a file)
 * @param src_mid pointer to an image source for the middle of the button (ideally 1px wide) (a C array or path to a file)
 * @param src_right pointer to an image source for the right side of the button (a C array or path to a file)
 */
void lv_imgbtn_set_src(lv_obj_t * imgbtn, lv_btn_state_t state, const void * src_left, const void * src_mid, const void * src_right);

#endif

/**
 * Enable the toggled states. On release the button will change from/to toggled state.
 * @param imgbtn pointer to an image button object
 * @param tgl true: enable toggled states, false: disable
 */
static inline void lv_imgbtn_set_toggle(lv_obj_t * imgbtn, bool tgl)
{
    lv_btn_set_toggle(imgbtn, tgl);
}

/**
 * Set the state of the image button
 * @param imgbtn pointer to an image button object
 * @param state the new state of the button (from lv_btn_state_t enum)
 */
static inline void lv_imgbtn_set_state(lv_obj_t * imgbtn, lv_btn_state_t state)
{
    lv_btn_set_state(imgbtn, state);
}

/**
 * Toggle the state of the image button (ON->OFF, OFF->ON)
 * @param imgbtn pointer to a image button object
 */
static inline void lv_imgbtn_toggle(lv_obj_t * imgbtn)
{
    lv_btn_toggle(imgbtn);
}

/**
 * Set a function to call when a button event happens
 * @param imgbtn pointer to an image button object
 * @param action type of event form 'lv_action_t' (press, release, long press, long press repeat)
 */
static inline void lv_imgbtn_set_action(lv_obj_t * imgbtn, lv_btn_action_t type, lv_action_t action)
{
    lv_btn_set_action(imgbtn, type, action);
}

/**
 * Set a style of a image button.
 * @param imgbtn pointer to image button object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_imgbtn_set_style(lv_obj_t * imgbtn, lv_imgbtn_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/


#if LV_IMGBTN_TILED == 0
/**
 * Get the images in a  given state
 * @param imgbtn pointer to an image button object
 * @param state the state where to get the image (from `lv_btn_state_t`) `
 * @return pointer to an image source (a C array or path to a file)
 */
const void * lv_imgbtn_get_src(lv_obj_t * imgbtn, lv_btn_state_t state);

#else

/**
 * Get the left image in a given state
 * @param imgbtn pointer to an image button object
 * @param state the state where to get the image (from `lv_btn_state_t`) `
 * @return pointer to the left image source (a C array or path to a file)
 */
const void * lv_imgbtn_get_src_left(lv_obj_t * imgbtn, lv_btn_state_t state);

/**
 * Get the middle image in a given state
 * @param imgbtn pointer to an image button object
 * @param state the state where to get the image (from `lv_btn_state_t`) `
 * @return pointer to the middle image source (a C array or path to a file)
 */
const void * lv_imgbtn_get_src_middle(lv_obj_t * imgbtn, lv_btn_state_t state);

/**
 * Get the right image in a given state
 * @param imgbtn pointer to an image button object
 * @param state the state where to get the image (from `lv_btn_state_t`) `
 * @return pointer to the left image source (a C array or path to a file)
 */
const void * lv_imgbtn_get_src_right(lv_obj_t * imgbtn, lv_btn_state_t state);

#endif
/**
 * Get the current state of the image button
 * @param imgbtn pointer to a image button object
 * @return the state of the button (from lv_btn_state_t enum)
 */
static inline lv_btn_state_t lv_imgbtn_get_state(const lv_obj_t * imgbtn)
{
    return lv_btn_get_state(imgbtn);
}

/**
 * Get the toggle enable attribute of the image button
 * @param imgbtn pointer to a image button object
 * @return ture: toggle enabled, false: disabled
 */
static inline bool lv_imgbtn_get_toggle(const lv_obj_t * imgbtn)
{
    return lv_btn_get_toggle(imgbtn);
}

/**
 * Get the release action of a image button
 * @param imgbtn pointer to a image button object
 * @return pointer to the release action function
 */
static inline lv_action_t lv_imgbtn_get_action(const lv_obj_t * imgbtn, lv_btn_action_t type)
{
    return lv_btn_get_action(imgbtn, type);
}

/**
 * Get style of a image button.
 * @param imgbtn pointer to image button object
 * @param type which style should be get
 * @return style pointer to the style
 */
lv_style_t * lv_imgbtn_get_style(const lv_obj_t * imgbtn, lv_imgbtn_style_t type);

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_IMGBTN*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_IMGBTN_H*/

/* lv_kb.h
 * Displays an on-screen keyboard linked to a text area.
 */
/**
 * @file lv_kb.h
 *
 */

#ifndef LV_KB_H
#define LV_KB_H

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

#if USE_LV_KB != 0

/*Testing of dependencies*/
#if USE_LV_BTNM == 0
#error "lv_kb: lv_btnm is required. Enable it in lv_conf.h (USE_LV_BTNM  1) "
#endif

#if USE_LV_TA == 0
#error "lv_kb: lv_ta is required. Enable it in lv_conf.h (USE_LV_TA  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LV_KB_MODE_TEXT,
    LV_KB_MODE_NUM,
};
typedef uint8_t lv_kb_mode_t;

/*Data of keyboard*/
typedef struct {
    lv_btnm_ext_t btnm;     /*Ext. of ancestor*/
    /*New data for this type */
    lv_obj_t *ta;               /*Pointer to the assigned text area*/
    lv_kb_mode_t mode;          /*Key map type*/
    uint8_t cursor_mng      :1; /*1: automatically show/hide cursor when a text area is assigned or left*/
    lv_action_t  ok_action;     /*Called when the "Ok" button is clicked*/
    lv_action_t  hide_action;  /*Called when the "Hide" button is clicked*/
} lv_kb_ext_t;

enum {
    LV_KB_STYLE_BG,
    LV_KB_STYLE_BTN_REL,
    LV_KB_STYLE_BTN_PR,
    LV_KB_STYLE_BTN_TGL_REL,
    LV_KB_STYLE_BTN_TGL_PR,
    LV_KB_STYLE_BTN_INA,
};
typedef uint8_t lv_kb_style_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a keyboard objects
 * @param par pointer to an object, it will be the parent of the new keyboard
 * @param copy pointer to a keyboard object, if not NULL then the new object will be copied from it
 * @return pointer to the created keyboard
 */
lv_obj_t * lv_kb_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Assign a Text Area to the Keyboard. The pressed characters will be put there.
 * @param kb pointer to a Keyboard object
 * @param ta pointer to a Text Area object to write there
 */
void lv_kb_set_ta(lv_obj_t * kb, lv_obj_t * ta);

/**
 * Set a new a mode (text or number map)
 * @param kb pointer to a Keyboard object
 * @param mode the mode from 'lv_kb_mode_t'
 */
void lv_kb_set_mode(lv_obj_t * kb, lv_kb_mode_t mode);

/**
 * Automatically hide or show the cursor of the current Text Area
 * @param kb pointer to a Keyboard object
 * @param en true: show cursor on the current text area, false: hide cursor
 */
void lv_kb_set_cursor_manage(lv_obj_t * kb, bool en);

/**
 * Set call back to call when the "Ok" button is pressed
 * @param kb pointer to Keyboard object
 * @param action a callback with 'lv_action_t' type
 */
void lv_kb_set_ok_action(lv_obj_t * kb, lv_action_t action);

/**
 * Set call back to call when the "Hide" button is pressed
 * @param kb pointer to Keyboard object
 * @param action a callback with 'lv_action_t' type
 */
void lv_kb_set_hide_action(lv_obj_t * kb, lv_action_t action);

/**
 * Set a new map for the keyboard
 * @param kb pointer to a Keyboard object
 * @param map pointer to a string array to describe the map.
 *            See 'lv_btnm_set_map()' for more info.
 */
static inline void lv_kb_set_map(lv_obj_t *kb, const char ** map)
{
    lv_btnm_set_map(kb, map);
}

/**
 * Set a style of a keyboard
 * @param kb pointer to a keyboard object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_kb_set_style(lv_obj_t *kb, lv_kb_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Assign a Text Area to the Keyboard. The pressed characters will be put there.
 * @param kb pointer to a Keyboard object
 * @return pointer to the assigned Text Area object
 */
lv_obj_t * lv_kb_get_ta(const lv_obj_t * kb);

/**
 * Set a new a mode (text or number map)
 * @param kb pointer to a Keyboard object
 * @return the current mode from 'lv_kb_mode_t'
 */
lv_kb_mode_t lv_kb_get_mode(const lv_obj_t * kb);

/**
 * Get the current cursor manage mode.
 * @param kb pointer to a Keyboard object
 * @return true: show cursor on the current text area, false: hide cursor
 */
bool lv_kb_get_cursor_manage(const lv_obj_t * kb);

/**
 * Get the callback to call when the "Ok" button is pressed
 * @param kb pointer to Keyboard object
 * @return the ok callback
 */
lv_action_t lv_kb_get_ok_action(const lv_obj_t * kb);

/**
 * Get the callback to call when the "Hide" button is pressed
 * @param kb pointer to Keyboard object
 * @return the close callback
 */
lv_action_t lv_kb_get_hide_action(const lv_obj_t * kb);

/**
 * Get a style of a keyboard
 * @param kb pointer to a keyboard object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_kb_get_style(const lv_obj_t *kb, lv_kb_style_t type);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_KB*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_KB_H*/

/* lv_led.h
 * Displays an LED-like indicator with adjustable brightness.
 */
/**
 * @file lv_led.h
 *
 */

#ifndef LV_LED_H
#define LV_LED_H

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

#if USE_LV_LED != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of led*/
typedef struct
{
    /*No inherited ext.*/
    /*New data for this type */
    uint8_t bright;         /*Current brightness of the LED (0..255)*/
} lv_led_ext_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a led objects
 * @param par pointer to an object, it will be the parent of the new led
 * @param copy pointer to a led object, if not NULL then the new object will be copied from it
 * @return pointer to the created led
 */
lv_obj_t * lv_led_create(lv_obj_t * par, const lv_obj_t * copy);

/**
 * Set the brightness of a LED object
 * @param led pointer to a LED object
 * @param bright 0 (max. dark) ... 255 (max. light)
 */
void lv_led_set_bright(lv_obj_t * led, uint8_t bright);

/**
 * Light on a LED
 * @param led pointer to a LED object
 */
void lv_led_on(lv_obj_t * led);

/**
 * Light off a LED
 * @param led pointer to a LED object
 */
void lv_led_off(lv_obj_t * led);

/**
 * Toggle the state of a LED
 * @param led pointer to a LED object
 */
void lv_led_toggle(lv_obj_t * led);

/**
 * Set the style of a led
 * @param led pointer to a led object
 * @param style pointer to a style
 */
static inline void lv_led_set_style(lv_obj_t *led, lv_style_t *style)
{
    lv_obj_set_style(led, style);
}

/**
 * Get the brightness of a LEd object
 * @param led pointer to LED object
 * @return bright 0 (max. dark) ... 255 (max. light)
 */
uint8_t lv_led_get_bright(const lv_obj_t * led);

/**
 * Get the style of an led object
 * @param led pointer to an led object
 * @return pointer to the led's style
 */
static inline lv_style_t* lv_led_get_style(const lv_obj_t *led)
{
    return lv_obj_get_style(led);
}

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_LED*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_LED_H*/

/* lv_list.h
 * Displays a scrollable list of labeled buttons.
 */
/**
 * @file lv_list.h
 *
 */

#ifndef LV_LIST_H
#define LV_LIST_H

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

#if USE_LV_LIST != 0

/*Testing of dependencies*/
#if USE_LV_PAGE == 0
#error "lv_list: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#if USE_LV_BTN == 0
#error "lv_list: lv_btn is required. Enable it in lv_conf.h (USE_LV_BTN  1) "
#endif

#if USE_LV_LABEL == 0
#error "lv_list: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif


#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of list*/
typedef struct
{
    lv_page_ext_t page; /*Ext. of ancestor*/
    /*New data for this type */
    uint16_t anim_time;                          /*Scroll animation time*/
    lv_style_t *styles_btn[LV_BTN_STATE_NUM];    /*Styles of the list element buttons*/
    lv_style_t *style_img;                       /*Style of the list element images on buttons*/
    uint32_t size; /*the number of items(buttons) in the list*/
    bool single_mode; /* whether single selected mode is enabled */
#if USE_LV_GROUP
    lv_obj_t * last_sel;                          /* The last selected button. It will be reverted when the list is focused again */
    lv_obj_t * selected_btn;                      /* The button is currently being selected*/
#endif
} lv_list_ext_t;

enum {
    LV_LIST_STYLE_BG,
    LV_LIST_STYLE_SCRL,
    LV_LIST_STYLE_SB,
    LV_LIST_STYLE_EDGE_FLASH,
    LV_LIST_STYLE_BTN_REL,
    LV_LIST_STYLE_BTN_PR,
    LV_LIST_STYLE_BTN_TGL_REL,
    LV_LIST_STYLE_BTN_TGL_PR,
    LV_LIST_STYLE_BTN_INA,
};
typedef uint8_t lv_list_style_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a list objects
 * @param par pointer to an object, it will be the parent of the new list
 * @param copy pointer to a list object, if not NULL then the new object will be copied from it
 * @return pointer to the created list
 */
lv_obj_t * lv_list_create(lv_obj_t * par, const lv_obj_t * copy);

/**
 * Delete all children of the scrl object, without deleting scrl child.
 * @param obj pointer to an object
 */
void lv_list_clean(lv_obj_t *obj);

/*======================
 * Add/remove functions
 *=====================*/

/**
 * Add a list element to the list
 * @param list pointer to list object
 * @param img_fn file name of an image before the text (NULL if unused)
 * @param txt text of the list element (NULL if unused)
 * @param rel_action pointer to release action function (like with lv_btn)
 * @return pointer to the new list element which can be customized (a button)
 */
lv_obj_t * lv_list_add(lv_obj_t * list, const void * img_src, const char * txt, lv_action_t rel_action);

/**
 * Remove the index of the button in the list
 * @param list pointer to a list object
 * @param index pointer to a the button's index in the list, index must be 0 <= index < lv_list_ext_t.size
 * @return true: successfully deleted
 */
bool lv_list_remove(const lv_obj_t * list, uint32_t index);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set single button selected mode, only one button will be selected if enabled.
 * @param list pointer to the currently pressed list object
 * @param mode, enable(true)/disable(false) single selected mode.
 */
void lv_list_set_single_mode(lv_obj_t *list, bool mode);

#if USE_LV_GROUP

/**
 * Make a button selected. Can be used while navigating in the list with a keypad.
 * @param list pointer to a list object
 * @param btn pointer to a button to select
 */
void lv_list_set_btn_selected(lv_obj_t * list, lv_obj_t * btn);
#endif

/**
 * Set scroll animation duration on 'list_up()' 'list_down()' 'list_focus()'
 * @param list pointer to a list object
 * @param anim_time duration of animation [ms]
 */
void lv_list_set_anim_time(lv_obj_t *list, uint16_t anim_time);

/**
 * Set the scroll bar mode of a list
 * @param list pointer to a list object
 * @param sb_mode the new mode from 'lv_page_sb_mode_t' enum
 */
static inline void lv_list_set_sb_mode(lv_obj_t * list, lv_sb_mode_t mode)
{
    lv_page_set_sb_mode(list, mode);
}

/**
 * Enable the scroll propagation feature. If enabled then the List will move its parent if there is no more space to scroll.
 * @param list pointer to a List
 * @param en true or false to enable/disable scroll propagation
 */
static inline void lv_list_set_scroll_propagation(lv_obj_t * list, bool en)
{
    lv_page_set_scroll_propagation(list, en);
}

/**
 * Enable the edge flash effect. (Show an arc when the an edge is reached)
 * @param list pointer to a List
 * @param en true or false to enable/disable end flash
 */
static inline void lv_list_set_edge_flash(lv_obj_t * list, bool en)
{
    lv_page_set_edge_flash(list, en);
}

/**
 * Set a style of a list
 * @param list pointer to a list object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_list_set_style(lv_obj_t *list, lv_list_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get single button selected mode.
 * @param list pointer to the currently pressed list object.
 */
bool lv_list_get_single_mode(lv_obj_t *list);

/**
 * Get the text of a list element
 * @param btn pointer to list element
 * @return pointer to the text
 */
const char * lv_list_get_btn_text(const lv_obj_t * btn);
/**
 * Get the label object from a list element
 * @param btn pointer to a list element (button)
 * @return pointer to the label from the list element or NULL if not found
 */
lv_obj_t * lv_list_get_btn_label(const lv_obj_t * btn);

/**
 * Get the image object from a list element
 * @param btn pointer to a list element (button)
 * @return pointer to the image from the list element or NULL if not found
 */
lv_obj_t * lv_list_get_btn_img(const lv_obj_t * btn);

/**
 * Get the next button from list. (Starts from the bottom button)
 * @param list pointer to a list object
 * @param prev_btn pointer to button. Search the next after it.
 * @return pointer to the next button or NULL when no more buttons
 */
lv_obj_t * lv_list_get_prev_btn(const lv_obj_t * list, lv_obj_t * prev_btn);

/**
 * Get the previous button from list. (Starts from the top button)
 * @param list pointer to a list object
 * @param prev_btn pointer to button. Search the previous before it.
 * @return pointer to the previous button or NULL when no more buttons
 */
lv_obj_t * lv_list_get_next_btn(const lv_obj_t * list, lv_obj_t * prev_btn);

/**
 * Get the index of the button in the list
 * @param list pointer to a list object. If NULL, assumes btn is part of a list.
 * @param btn pointer to a list element (button)
 * @return the index of the button in the list, or -1 of the button not in this list
 */
int32_t lv_list_get_btn_index(const lv_obj_t * list, const lv_obj_t * btn);

/**
 * Get the number of buttons in the list
 * @param list pointer to a list object
 * @return the number of buttons in the list
 */
uint32_t lv_list_get_size(const lv_obj_t * list);

#if USE_LV_GROUP
/**
 * Get the currently selected button. Can be used while navigating in the list with a keypad.
 * @param list pointer to a list object
 * @return pointer to the selected button
 */
lv_obj_t * lv_list_get_btn_selected(const lv_obj_t * list);
#endif


/**
 * Get scroll animation duration
 * @param list pointer to a list object
 * @return duration of animation [ms]
 */
uint16_t lv_list_get_anim_time(const lv_obj_t *list);


/**
 * Get the scroll bar mode of a list
 * @param list pointer to a list object
 * @return scrollbar mode from 'lv_page_sb_mode_t' enum
 */
static inline lv_sb_mode_t lv_list_get_sb_mode(const lv_obj_t * list)
{
    return lv_page_get_sb_mode(list);
}

/**
 * Get the scroll propagation property
 * @param list pointer to a List
 * @return true or false
 */
static inline bool lv_list_get_scroll_propagation(lv_obj_t * list)
{
    return lv_page_get_scroll_propagation(list);
}

/**
 * Get the scroll propagation property
 * @param list pointer to a List
 * @return true or false
 */
static inline bool lv_list_get_edge_flash(lv_obj_t * list)
{
    return lv_page_get_edge_flash(list);
}

/**
 * Get a style of a list
 * @param list pointer to a list object
 * @param type which style should be get
 * @return style pointer to a style
 *  */
lv_style_t * lv_list_get_style(const lv_obj_t *list, lv_list_style_t type);

/*=====================
 * Other functions
 *====================*/

/**
 * Move the list elements up by one
 * @param list pointer a to list object
 */
void lv_list_up(const lv_obj_t * list);
/**
 * Move the list elements down by one
 * @param list pointer to a list object
 */
void lv_list_down(const lv_obj_t * list);

/**
 * Focus on a list button. It ensures that the button will be visible on the list.
 * @param btn pointer to a list button to focus
 * @param anim_en true: scroll with animation, false: without animation
 */
void lv_list_focus(const lv_obj_t *btn, bool anim_en);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_LIST*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_LIST_H*/

/* lv_mbox.h
 * Displays a message with optional action buttons.
 */
/**
 * @file lv_mbox.h
 *
 */

#ifndef LV_MBOX_H
#define LV_MBOX_H

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

#if USE_LV_MBOX != 0

/*Testing of dependencies*/
#if USE_LV_CONT == 0
#error "lv_mbox: lv_cont is required. Enable it in lv_conf.h (USE_LV_CONT  1) "
#endif

#if USE_LV_BTNM == 0
#error "lv_mbox: lv_btnm is required. Enable it in lv_conf.h (USE_LV_BTNM  1) "
#endif

#if USE_LV_LABEL == 0
#error "lv_mbox: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif


#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of message box*/
typedef struct
{
    lv_cont_ext_t bg; /*Ext. of ancestor*/
    /*New data for this type */
    lv_obj_t *text;             /*Text of the message box*/
    lv_obj_t *btnm;            /*Button matrix for the buttons*/
    uint16_t anim_time;         /*Duration of close animation [ms] (0: no animation)*/
} lv_mbox_ext_t;

enum {
    LV_MBOX_STYLE_BG,
    LV_MBOX_STYLE_BTN_BG,
    LV_MBOX_STYLE_BTN_REL,
    LV_MBOX_STYLE_BTN_PR,
    LV_MBOX_STYLE_BTN_TGL_REL,
    LV_MBOX_STYLE_BTN_TGL_PR,
    LV_MBOX_STYLE_BTN_INA,
};
typedef uint8_t lv_mbox_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a message box objects
 * @param par pointer to an object, it will be the parent of the new message box
 * @param copy pointer to a message box object, if not NULL then the new object will be copied from it
 * @return pointer to the created message box
 */
lv_obj_t * lv_mbox_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/

/**
 * Add button to the message box
 * @param mbox pointer to message box object
 * @param btn_map button descriptor (button matrix map).
 *                E.g.  a const char *txt[] = {"ok", "close", ""} (Can not be local variable)
 * @param action a function which will be called when a button is released
 */
void lv_mbox_add_btns(lv_obj_t * mbox, const char **btn_map, lv_btnm_action_t action);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the text of the message box
 * @param mbox pointer to a message box
 * @param txt a '\0' terminated character string which will be the message box text
 */
void lv_mbox_set_text(lv_obj_t * mbox, const char * txt);

/**
 * Stop the action to call when button is released
 * @param mbox pointer to a message box object
 * @param pointer to an 'lv_btnm_action_t' action. In the action you need to use `lv_mbox_get_from_btn()` to get the `mbox`.
 */
void lv_mbox_set_action(lv_obj_t * mbox, lv_btnm_action_t action);

/**
 * Set animation duration
 * @param mbox pointer to a message box object
 * @param anim_time animation length in  milliseconds (0: no animation)
 */
void lv_mbox_set_anim_time(lv_obj_t * mbox, uint16_t anim_time);

/**
 * Automatically delete the message box after a given time
 * @param mbox pointer to a message box object
 * @param delay a time (in milliseconds) to wait before delete the message box
 */
void lv_mbox_start_auto_close(lv_obj_t * mbox, uint16_t delay);

/**
 * Stop the auto. closing of message box
 * @param mbox pointer to a message box object
 */
void lv_mbox_stop_auto_close(lv_obj_t * mbox);

/**
 * Set a style of a message box
 * @param mbox pointer to a message box object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_mbox_set_style(lv_obj_t *mbox, lv_mbox_style_t type, lv_style_t *style);

/**
 * Set whether recoloring is enabled. Must be called after `lv_mbox_add_btns`.
 * @param btnm pointer to button matrix object
 * @param en whether recoloring is enabled
 */
void lv_mbox_set_recolor(lv_obj_t * mbox, bool en);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the text of the message box
 * @param mbox pointer to a message box object
 * @return pointer to the text of the message box
 */
const char * lv_mbox_get_text(const lv_obj_t * mbox);

/**
 * Get the message box object from one of its button.
 * It is useful in the button release actions where only the button is known
 * @param btn pointer to a button of a message box
 * @return pointer to the button's message box
 */
lv_obj_t * lv_mbox_get_from_btn(const lv_obj_t * btn);

/**
 * Get the animation duration (close animation time)
 * @param mbox pointer to a message box object
 * @return animation length in  milliseconds (0: no animation)
 */
uint16_t lv_mbox_get_anim_time(const lv_obj_t * mbox);


/**
 * Get a style of a message box
 * @param mbox pointer to a message box object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_mbox_get_style(const lv_obj_t *mbox, lv_mbox_style_t type);

/**
 * Get whether recoloring is enabled
 * @param btnm pointer to button matrix object
 * @return whether recoloring is enabled
 */
bool lv_mbox_get_recolor(const lv_obj_t * mbox);

/**********************
 *      MACROS
 **********************/


#endif  /*USE_LV_MBOX*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_MBOX_H*/

/* lv_objx_templ.h
 * Skeleton for implementing another widget.
 */
/**
 * @file lv_templ.h
 *
 */


/* TODO Remove these instructions
 * Search an replace: template -> object normal name with lower case (e.g. button, label etc.)
 *                    templ -> object short name with lower case(e.g. btn, label etc)
 *                    TEMPL -> object short name with upper case (e.g. BTN, LABEL etc.)
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
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_conf.h"
#else
#include "display/lv_conf.h"
#endif

#if USE_LV_TEMPL != 0

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of template*/
typedef struct {
    lv_ANCESTOR_ext_t ANCESTOR; /*Ext. of ancestor*/
    /*New data for this type */
} lv_templ_ext_t;


/*Styles*/
enum {
    LV_TEMPL_STYLE_X,
    LV_TEMPL_STYLE_Y,
};
typedef uint8_t lv_templ_style_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a template objects
 * @param par pointer to an object, it will be the parent of the new template
 * @param copy pointer to a template object, if not NULL then the new object will be copied from it
 * @return pointer to the created template
 */
lv_obj_t * lv_templ_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/


/*=====================
 * Setter functions
 *====================*/

/**
 * Set a style of a template.
 * @param templ pointer to template object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_templ_set_style(lv_obj_t * templ, lv_templ_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get style of a template.
 * @param templ pointer to template object
 * @param type which style should be get
 * @return style pointer to the style
 */
lv_style_t * lv_templ_get_style(const lv_obj_t * templ, lv_templ_style_t type);

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_TEMPL*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_TEMPL_H*/

/* lv_preload.h
 * Displays an animated loading indicator.
 */
/**
 * @file lv_preload.h
 *
 */

#ifndef LV_PRELOAD_H
#define LV_PRELOAD_H

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

#if USE_LV_PRELOAD != 0

/*Testing of dependencies*/
#if USE_LV_ARC == 0
#error "lv_preload: lv_arc is required. Enable it in lv_conf.h (USE_LV_ARC  1) "
#endif

#if USE_LV_ANIMATION == 0
#error "lv_preload: animations are required. Enable it in lv_conf.h (USE_LV_ANIMATION  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LV_PRELOAD_TYPE_SPINNING_ARC,
    LV_PRELOAD_TYPE_FILLSPIN_ARC,
};
typedef uint8_t lv_preloader_type_t;

/*Data of pre loader*/
typedef struct {
    lv_arc_ext_t arc; /*Ext. of ancestor*/
    /*New data for this type */
    uint16_t arc_length;            /*Length of the spinning indicator in degree*/
    uint16_t time;                  /*Time of one round*/
    lv_preloader_type_t anim_type;  /*Type of the arc animation*/
} lv_preload_ext_t;


/*Styles*/
enum {
    LV_PRELOAD_STYLE_MAIN,
};
typedef uint8_t lv_preload_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a pre loader objects
 * @param par pointer to an object, it will be the parent of the new pre loader
 * @param copy pointer to a pre loader object, if not NULL then the new object will be copied from it
 * @return pointer to the created pre loader
 */
lv_obj_t * lv_preload_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/

/**
 * Set the length of the spinning  arc in degrees
 * @param preload pointer to a preload object
 * @param deg length of the arc
 */
void lv_preload_set_arc_length(lv_obj_t * preload, uint16_t deg);

/**
 * Set the spin time of the arc
 * @param preload pointer to a preload object
 * @param time time of one round in milliseconds
 */
void lv_preload_set_spin_time(lv_obj_t * preload, uint16_t time);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a style of a pre loader.
 * @param preload pointer to pre loader object
 * @param type which style should be set
 * @param style pointer to a style
 *  */
void lv_preload_set_style(lv_obj_t * preload, lv_preload_style_t type, lv_style_t *style);

/**
 * Set the animation type of a preloadeer.
 * @param preload pointer to pre loader object
 * @param type animation type of the preload
 *  */
void lv_preload_set_animation_type(lv_obj_t * preload, lv_preloader_type_t type);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the arc length [degree] of the a pre loader
 * @param preload pointer to a pre loader object
 */
uint16_t lv_preload_get_arc_length(const lv_obj_t * preload);

/**
 * Get the spin time of the arc
 * @param preload pointer to a pre loader object [milliseconds]
 */
uint16_t lv_preload_get_spin_time(const lv_obj_t * preload);

/**
 * Get style of a pre loader.
 * @param preload pointer to pre loader object
 * @param type which style should be get
 * @return style pointer to the style
 *  */
lv_style_t * lv_preload_get_style(const lv_obj_t * preload, lv_preload_style_t type);

/**
 * Get the animation type of a preloadeer.
 * @param preload pointer to pre loader object
 * @return animation type
 *  */
lv_preloader_type_t lv_preload_get_animation_type(lv_obj_t * preload);

/*=====================
 * Other functions
 *====================*/

/**
 * Get style of a pre loader.
 * @param preload pointer to pre loader object
 * @param type which style should be get
 * @return style pointer to the style
 *  */
void lv_preload_spinner_animation(void * ptr, int32_t val);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_PRELOAD*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_PRELOAD_H*/

/* lv_roller.h
 * Lets the user scroll through a list and select a value.
 */
/**
 * @file lv_roller.h
 *
 */

#ifndef LV_ROLLER_H
#define LV_ROLLER_H

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

#if USE_LV_ROLLER != 0

/*Testing of dependencies*/
#if USE_LV_DDLIST == 0
#error "lv_roller: lv_ddlist is required. Enable it in lv_conf.h (USE_LV_DDLIST  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of roller*/
typedef struct {
    lv_ddlist_ext_t ddlist; /*Ext. of ancestor*/
    /*New data for this type */
} lv_roller_ext_t;

enum {
    LV_ROLLER_STYLE_BG,
    LV_ROLLER_STYLE_SEL,
};
typedef uint8_t lv_roller_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a roller object
 * @param par pointer to an object, it will be the parent of the new roller
 * @param copy pointer to a roller object, if not NULL then the new object will be copied from it
 * @return pointer to the created roller
 */
lv_obj_t * lv_roller_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the align of the roller's options (left, right or center[default])
 * @param roller - pointer to a roller object
 * @param align - one of lv_label_align_t values (left, right, center)
 */
void lv_roller_set_align(lv_obj_t * roller, lv_label_align_t align);

/**
 * Set the options on a roller
 * @param roller pointer to roller object
 * @param options a string with '\n' separated options. E.g. "One\nTwo\nThree"
 */
static inline void lv_roller_set_options(lv_obj_t * roller, const char * options)
{
    lv_ddlist_set_options(roller, options);
}

/**
 * Set the selected option
 * @param roller pointer to a roller object
 * @param sel_opt id of the selected option (0 ... number of option - 1);
 * @param anim_en true: set with animation; false set immediately
 */
void lv_roller_set_selected(lv_obj_t *roller, uint16_t sel_opt, bool anim_en);

/**
 * Set a function to call when a new option is chosen
 * @param roller pointer to a roller
 * @param action pointer to a callback function
 */
static inline void lv_roller_set_action(lv_obj_t * roller, lv_action_t action)
{
    lv_ddlist_set_action(roller, action);
}

/**
 * Set the height to show the given number of rows (options)
 * @param roller pointer to a roller object
 * @param row_cnt number of desired visible rows
 */
void lv_roller_set_visible_row_count(lv_obj_t *roller, uint8_t row_cnt);

/**
 * Enable or disable the horizontal fit to the content
 * @param roller pointer to a roller
 * @param en true: enable auto fit; false: disable auto fit
 */
static inline void lv_roller_set_hor_fit(lv_obj_t * roller, bool en)
{
    lv_ddlist_set_hor_fit(roller, en);
}

/**
 * Set the open/close animation time.
 * @param roller pointer to a roller object
 * @param anim_time: open/close animation time [ms]
 */
static inline void lv_roller_set_anim_time(lv_obj_t *roller, uint16_t anim_time)
{
    lv_ddlist_set_anim_time(roller, anim_time);
}

/**
 * Set a style of a roller
 * @param roller pointer to a roller object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_roller_set_style(lv_obj_t *roller, lv_roller_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the align attribute. Default alignment after _create is LV_LABEL_ALIGN_CENTER
 * @param roller pointer to a roller object
 * @return LV_LABEL_ALIGN_LEFT, LV_LABEL_ALIGN_RIGHT or LV_LABEL_ALIGN_CENTER
 */
lv_label_align_t lv_roller_get_align(const lv_obj_t * roller);

/**
 * Get the options of a roller
 * @param roller pointer to roller object
 * @return the options separated by '\n'-s (E.g. "Option1\nOption2\nOption3")
 */
static inline const char * lv_roller_get_options(const lv_obj_t *roller)
{
    return lv_ddlist_get_options(roller);
}

/**
 * Get the id of the selected option
 * @param roller pointer to a roller object
 * @return id of the selected option (0 ... number of option - 1);
 */
static inline uint16_t lv_roller_get_selected(const lv_obj_t *roller)
{
    return lv_ddlist_get_selected(roller);
}

/**
 * Get the current selected option as a string
 * @param roller pointer to roller object
 * @param buf pointer to an array to store the string
 */
static inline void lv_roller_get_selected_str(const lv_obj_t * roller, char * buf)
{
    lv_ddlist_get_selected_str(roller, buf);
}

/**
 * Get the "option selected" callback function
 * @param roller pointer to a roller
 * @return  pointer to the call back function
 */
static inline lv_action_t lv_roller_get_action(const lv_obj_t * roller)
{
    return lv_ddlist_get_action(roller);
}

/**
 * Get the open/close animation time.
 * @param roller pointer to a roller
 * @return open/close animation time [ms]
 */
static inline uint16_t lv_roller_get_anim_time(const lv_obj_t * roller)
{
    return lv_ddlist_get_anim_time(roller);
}

/**
 * Get the auto width set attribute
 * @param roller pointer to a roller object
 * @return true: auto size enabled; false: manual width settings enabled
 */
bool lv_roller_get_hor_fit(const lv_obj_t *roller);

/**
 * Get a style of a roller
 * @param roller pointer to a roller object
 * @param type which style should be get
 * @return style pointer to a style
 *  */
lv_style_t * lv_roller_get_style(const lv_obj_t *roller, lv_roller_style_t type);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_ROLLER*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_ROLLER_H*/

/* lv_slider.h
 * Lets the user drag a knob to set a value in a range.
 */
/**
 * @file lv_slider.h
 *
 */

#ifndef LV_SLIDER_H
#define LV_SLIDER_H

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

#if USE_LV_SLIDER != 0

/*Testing of dependencies*/
#if USE_LV_BAR == 0
#error "lv_slider: lv_bar is required. Enable it in lv_conf.h (USE_LV_BAR  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of slider*/
typedef struct
{
    lv_bar_ext_t bar;       /*Ext. of ancestor*/
    /*New data for this type */
    lv_action_t action;             /*Function to call when a new value is set*/
    lv_style_t *style_knob;    /*Style of the knob*/
    int16_t drag_value;          /*Store a temporal value during press until release (Handled by the library)*/
    uint8_t knob_in     :1;     /*1: Draw the knob inside the bar*/
} lv_slider_ext_t;

/*Built-in styles of slider*/
enum
{
    LV_SLIDER_STYLE_BG,
    LV_SLIDER_STYLE_INDIC,
    LV_SLIDER_STYLE_KNOB,
};
typedef uint8_t lv_slider_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a slider objects
 * @param par pointer to an object, it will be the parent of the new slider
 * @param copy pointer to a slider object, if not NULL then the new object will be copied from it
 * @return pointer to the created slider
 */
lv_obj_t * lv_slider_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a new value on the slider
 * @param slider pointer to a slider object
 * @param value new value
 */
static inline void lv_slider_set_value(lv_obj_t * slider, int16_t value)
{
    lv_bar_set_value(slider, value);
}

/**
 * Set a new value with animation on a slider
 * @param slider pointer to a slider object
 * @param value new value
 * @param anim_time animation time in milliseconds
 */
static inline void lv_slider_set_value_anim(lv_obj_t * slider, int16_t value, uint16_t anim_time)
{
    lv_bar_set_value_anim(slider, value, anim_time);
}

/**
 * Set minimum and the maximum values of a bar
 * @param slider pointer to the slider object
 * @param min minimum value
 * @param max maximum value
 */
static inline void lv_slider_set_range(lv_obj_t *slider, int16_t min, int16_t max)
{
    lv_bar_set_range(slider, min, max);
}

/**
 * Set a function which will be called when a new value is set on the slider
 * @param slider pointer to slider object
 * @param action a callback function
 */
void lv_slider_set_action(lv_obj_t * slider, lv_action_t action);

/**
 * Set the 'knob in' attribute of a slider
 * @param slider pointer to slider object
 * @param in true: the knob is drawn always in the slider;
 *           false: the knob can be out on the edges
 */
void lv_slider_set_knob_in(lv_obj_t * slider, bool in);

/**
 * Set a style of a slider
 * @param slider pointer to a slider object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_slider_set_style(lv_obj_t *slider, lv_slider_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the value of a slider
 * @param slider pointer to a slider object
 * @return the value of the slider
 */
int16_t lv_slider_get_value(const lv_obj_t * slider);

/**
 * Get the minimum value of a slider
 * @param slider pointer to a slider object
 * @return the minimum value of the slider
 */
static inline int16_t lv_slider_get_min_value(const lv_obj_t * slider)
{
    return lv_bar_get_min_value(slider);
}

/**
 * Get the maximum value of a slider
 * @param slider pointer to a slider object
 * @return the maximum value of the slider
 */
static inline int16_t lv_slider_get_max_value(const lv_obj_t * slider)
{
    return lv_bar_get_max_value(slider);
}

/**
 * Get the slider action function
 * @param slider pointer to slider object
 * @return the callback function
 */
lv_action_t lv_slider_get_action(const lv_obj_t * slider);

/**
 * Give the slider is being dragged or not
 * @param slider pointer to a slider object
 * @return true: drag in progress false: not dragged
 */
bool lv_slider_is_dragged(const lv_obj_t * slider);

/**
 * Get the 'knob in' attribute of a slider
 * @param slider pointer to slider object
 * @return true: the knob is drawn always in the slider;
 *         false: the knob can be out on the edges
 */
bool lv_slider_get_knob_in(const lv_obj_t * slider);


/**
 * Get a style of a slider
 * @param slider pointer to a slider object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_slider_get_style(const lv_obj_t *slider, lv_slider_style_t type);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_SLIDER*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_SLIDER_H*/

/* lv_ta.h
 * Provides editable text, cursor movement, and input limits.
 */
/**
 * @file lv_ta.h
 *
 */

#ifndef LV_TA_H
#define LV_TA_H

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

#if USE_LV_TA != 0

/*Testing of dependencies*/
#if USE_LV_PAGE == 0
#error "lv_ta: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#if USE_LV_LABEL == 0
#error "lv_ta: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/
#define LV_TA_CURSOR_LAST (0x7FFF) /*Put the cursor after the last character*/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LV_CURSOR_NONE,
    LV_CURSOR_LINE,
    LV_CURSOR_BLOCK,
    LV_CURSOR_OUTLINE,
    LV_CURSOR_UNDERLINE,
    LV_CURSOR_HIDDEN = 0x08,    /*Or it to any value to hide the cursor temporally*/
};
typedef uint8_t lv_cursor_type_t;

/*Data of text area*/
typedef struct
{
    lv_page_ext_t page; /*Ext. of ancestor*/
    /*New data for this type */
    lv_obj_t * label;           /*Label of the text area*/
    char * pwd_tmp;             /*Used to store the original text in password mode*/
    const char * accapted_chars;/*Only these characters will be accepted. NULL: accept all*/
    uint16_t max_length;        /*The max. number of characters. 0: no limit*/
    uint8_t pwd_mode :1;        /*Replace characters with '*' */
    uint8_t one_line :1;        /*One line mode (ignore line breaks)*/
    struct {
        lv_style_t *style;      /*Style of the cursor (NULL to use label's style)*/
        lv_coord_t valid_x;     /*Used when stepping up/down in text area when stepping to a shorter line. (Handled by the library)*/
        uint16_t pos;           /*The current cursor position (0: before 1. letter; 1: before 2. letter etc.)*/
        lv_area_t area;         /*Cursor area relative to the Text Area*/
        uint16_t txt_byte_pos;  /*Byte index of the letter after (on) the cursor*/
        lv_cursor_type_t type:4;  /*Shape of the cursor*/
        uint8_t state :1;       /*Indicates that the cursor is visible now or not (Handled by the library)*/
    } cursor;
} lv_ta_ext_t;

enum {
    LV_TA_STYLE_BG,
    LV_TA_STYLE_SB,
    LV_TA_STYLE_EDGE_FLASH,
    LV_TA_STYLE_CURSOR,
};
typedef uint8_t lv_ta_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**
 * Create a text area objects
 * @param par pointer to an object, it will be the parent of the new text area
 * @param copy pointer to a text area object, if not NULL then the new object will be copied from it
 * @return pointer to the created text area
 */
lv_obj_t * lv_ta_create(lv_obj_t * par, const lv_obj_t * copy);


/*======================
 * Add/remove functions
 *=====================*/

/**
 * Insert a character to the current cursor position.
 * To add a wide char, e.g. 'Á' use `lv_txt_encoded_conv_wc('Á')`
 * @param ta pointer to a text area object
 * @param c a character (e.g. 'a')
 */
void lv_ta_add_char(lv_obj_t * ta, uint32_t c);

/**
 * Insert a text to the current cursor position
 * @param ta pointer to a text area object
 * @param txt a '\0' terminated string to insert
 */
void lv_ta_add_text(lv_obj_t * ta, const char * txt);

/**
 * Delete a the left character from the current cursor position
 * @param ta pointer to a text area object
 */
void lv_ta_del_char(lv_obj_t * ta);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the text of a text area
 * @param ta pointer to a text area
 * @param txt pointer to the text
 */
void lv_ta_set_text(lv_obj_t * ta, const char * txt);

/**
 * Set the cursor position
 * @param obj pointer to a text area object
 * @param pos the new cursor position in character index
 *             < 0 : index from the end of the text
 *             LV_TA_CURSOR_LAST: go after the last character
 */
void lv_ta_set_cursor_pos(lv_obj_t * ta, int16_t pos);

/**
 * Set the cursor type.
 * @param ta pointer to a text area object
 * @param cur_type: element of 'lv_cursor_type_t'
 */
void lv_ta_set_cursor_type(lv_obj_t * ta, lv_cursor_type_t cur_type);

/**
 * Enable/Disable password mode
 * @param ta pointer to a text area object
 * @param en true: enable, false: disable
 */
void lv_ta_set_pwd_mode(lv_obj_t * ta, bool en);

/**
 * Configure the text area to one line or back to normal
 * @param ta pointer to a Text area object
 * @param en true: one line, false: normal
 */
void lv_ta_set_one_line(lv_obj_t * ta, bool en);

/**
 * Set the alignment of the text area.
 * In one line mode the text can be scrolled only with `LV_LABEL_ALIGN_LEFT`.
 * This function should be called if the size of text area changes.
 * @param ta pointer to a text are object
 * @param align the desired alignment from `lv_label_align_t`. (LV_LABEL_ALIGN_LEFT/CENTER/RIGHT)
 */
void lv_ta_set_text_align(lv_obj_t * ta, lv_label_align_t align);

/**
 * Set a list of characters. Only these characters will be accepted by the text area
 * @param ta pointer to  Text Area
 * @param list list of characters. Only the pointer is saved. E.g. "+-.,0123456789"
 */
void lv_ta_set_accepted_chars(lv_obj_t * ta, const char * list);

/**
 * Set max length of a Text Area.
 * @param ta pointer to  Text Area
 * @param num the maximal number of characters can be added (`lv_ta_set_text` ignores it)
 */
void lv_ta_set_max_length(lv_obj_t * ta, uint16_t num);

/**
 * Set an action to call when the Text area is clicked
 * @param ta pointer to a Text area
 * @param action a function pointer
 */
static inline void lv_ta_set_action(lv_obj_t * ta, lv_action_t action)
{
    lv_page_set_rel_action(ta, action);
}

/**
 * Set the scroll bar mode of a text area
 * @param ta pointer to a text area object
 * @param sb_mode the new mode from 'lv_page_sb_mode_t' enum
 */
static inline void lv_ta_set_sb_mode(lv_obj_t * ta, lv_sb_mode_t mode)
{
    lv_page_set_sb_mode(ta, mode);
}

/**
 * Enable the scroll propagation feature. If enabled then the Text area will move its parent if there is no more space to scroll.
 * @param ta pointer to a Text area
 * @param en true or false to enable/disable scroll propagation
 */
static inline void lv_ta_set_scroll_propagation(lv_obj_t * ta, bool en)
{
    lv_page_set_scroll_propagation(ta, en);
}

/**
 * Enable the edge flash effect. (Show an arc when the an edge is reached)
 * @param page pointer to a Text Area
 * @param en true or false to enable/disable end flash
 */
static inline void lv_ta_set_edge_flash(lv_obj_t * ta, bool en)
{
    lv_page_set_edge_flash(ta, en);
}

/**
 * Set a style of a text area
 * @param ta pointer to a text area object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_ta_set_style(lv_obj_t *ta, lv_ta_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the text of a text area. In password mode it gives the real text (not '*'s).
 * @param ta pointer to a text area object
 * @return pointer to the text
 */
const char * lv_ta_get_text(const lv_obj_t * ta);

/**
 * Get the label of a text area
 * @param ta pointer to a text area object
 * @return pointer to the label object
 */
lv_obj_t * lv_ta_get_label(const lv_obj_t * ta);

/**
 * Get the current cursor position in character index
 * @param ta pointer to a text area object
 * @return the cursor position
 */
uint16_t lv_ta_get_cursor_pos(const lv_obj_t * ta);

/**
 * Get the current cursor visibility.
 * @param ta pointer to a text area object
 * @return true: the cursor is drawn, false: the cursor is hidden
 */
//bool lv_ta_get_cursor_show(const lv_obj_t * ta);

/**
 * Get the current cursor type.
 * @param ta pointer to a text area object
 * @return element of 'lv_cursor_type_t'
 */
lv_cursor_type_t lv_ta_get_cursor_type(const lv_obj_t * ta);

/**
 * Get the password mode attribute
 * @param ta pointer to a text area object
 * @return true: password mode is enabled, false: disabled
 */
bool lv_ta_get_pwd_mode(const lv_obj_t * ta);

/**
 * Get the one line configuration attribute
 * @param ta pointer to a text area object
 * @return true: one line configuration is enabled, false: disabled
 */
bool lv_ta_get_one_line(const lv_obj_t * ta);

/**
 * Get a list of accepted characters.
 * @param ta pointer to  Text Area
 * @return list of accented characters.
 */
const char * lv_ta_get_accepted_chars(lv_obj_t * ta);

/**
 * Set max length of a Text Area.
 * @param ta pointer to  Text Area
 * @return the maximal number of characters to be add
 */
uint16_t lv_ta_get_max_length(lv_obj_t * ta);

/**
 * Set an action to call when the Text area is clicked
 * @param ta pointer to a Text area
 * @param action a function pointer
 */
static inline lv_action_t lv_ta_get_action(lv_obj_t * ta)
{
    return lv_page_get_rel_action(ta);
}

/**
 * Get the scroll bar mode of a text area
 * @param ta pointer to a text area object
 * @return scrollbar mode from 'lv_page_sb_mode_t' enum
 */
static inline lv_sb_mode_t lv_ta_get_sb_mode(const lv_obj_t * ta)
{
    return lv_page_get_sb_mode(ta);
}

/**
 * Get the scroll propagation property
 * @param ta pointer to a Text area
 * @return true or false
 */
static inline bool lv_ta_get_scroll_propagation(lv_obj_t * ta)
{
    return lv_page_get_scroll_propagation(ta);
}

/**
 * Get the scroll propagation property
 * @param ta pointer to a Text area
 * @return true or false
 */
static inline bool lv_ta_get_edge_flash(lv_obj_t * ta)
{
    return lv_page_get_edge_flash(ta);
}

/**
 * Get a style of a text area
 * @param ta pointer to a text area object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_ta_get_style(const lv_obj_t *ta, lv_ta_style_t type);

/*=====================
 * Other functions
 *====================*/

/**
 * Move the cursor one character right
 * @param ta pointer to a text area object
 */
void lv_ta_cursor_right(lv_obj_t * ta);

/**
 * Move the cursor one character left
 * @param ta pointer to a text area object
 */
void lv_ta_cursor_left(lv_obj_t * ta);

/**
 * Move the cursor one line down
 * @param ta pointer to a text area object
 */
void lv_ta_cursor_down(lv_obj_t * ta);

/**
 * Move the cursor one line up
 * @param ta pointer to a text area object
 */
void lv_ta_cursor_up(lv_obj_t * ta);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_TA_H*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_TA_H*/

/* lv_spinbox.h
 * Provides numeric entry with a configurable number of digits.
 */
/**
 * @file lv_spinbox.h
 *
 */


#ifndef LV_SPINBOX_H
#define LV_SPINBOX_H

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

#if USE_LV_SPINBOX != 0

/*Testing of dependencies*/
#if USE_LV_TA == 0
#error "lv_spinbox: lv_ta is required. Enable it in lv_conf.h (USE_LV_TA  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/
#define LV_SPINBOX_MAX_DIGIT_COUNT	16

/**********************
 *      TYPEDEFS
 **********************/

/*callback on value change*/
typedef void (*lv_spinbox_value_changed_cb_t)(lv_obj_t * spinbox, int32_t new_value);

/*Data of spinbox*/
typedef struct {
    lv_ta_ext_t ta; /*Ext. of ancestor*/
    /*New data for this type */
    int32_t value;
    int32_t range_max;
    int32_t range_min;
    int32_t step;
    uint16_t digit_count:4;
    uint16_t dec_point_pos:4;      /*if 0, there is no separator and the number is an integer*/
    uint16_t digit_padding_left:4;
    lv_spinbox_value_changed_cb_t value_changed_cb;
} lv_spinbox_ext_t;


/*Styles*/
enum {
    LV_SPINBOX_STYLE_BG,
    LV_SPINBOX_STYLE_SB,
    LV_SPINBOX_STYLE_CURSOR,
};
typedef uint8_t lv_spinbox_style_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a spinbox objects
 * @param par pointer to an object, it will be the parent of the new spinbox
 * @param copy pointer to a spinbox object, if not NULL then the new object will be copied from it
 * @return pointer to the created spinbox
 */
lv_obj_t * lv_spinbox_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a style of a spinbox.
 * @param templ pointer to template object
 * @param type which style should be set
 * @param style pointer to a style
 */
static inline void lv_spinbox_set_style(lv_obj_t * spinbox, lv_spinbox_style_t type, lv_style_t *style)
{
    lv_ta_set_style(spinbox, type, style);
}

/**
 * Set spinbox value
 * @param spinbox pointer to spinbox
 * @param i value to be set
 */
void lv_spinbox_set_value(lv_obj_t * spinbox, int32_t i);

/**
 * Set spinbox digit format (digit count and decimal format)
 * @param spinbox pointer to spinbox
 * @param digit_count number of digit excluding the decimal separator and the sign
 * @param separator_position number of digit before the decimal point. If 0, decimal point is not shown
 */
void lv_spinbox_set_digit_format(lv_obj_t * spinbox, uint8_t digit_count, uint8_t separator_position);

/**
 * Set spinbox step
 * @param spinbox pointer to spinbox
 * @param step steps on increment/decrement
 */
void lv_spinbox_set_step(lv_obj_t * spinbox, uint32_t step);

/**
 * Set spinbox value range
 * @param spinbox pointer to spinbox
 * @param range_min maximum value, inclusive
 * @param range_max minimum value, inclusive
 */
void lv_spinbox_set_range(lv_obj_t * spinbox, int32_t range_min, int32_t range_max);

/**
 * Set spinbox callback on calue change
 * @param spinbox pointer to spinbox
 * @param cb Callback function called on value change event
 */
void lv_spinbox_set_value_changed_cb(lv_obj_t * spinbox, lv_spinbox_value_changed_cb_t cb);

/**
 * Set spinbox left padding in digits count (added between sign and first digit)
 * @param spinbox pointer to spinbox
 * @param cb Callback function called on value change event
 */
void lv_spinbox_set_padding_left(lv_obj_t * spinbox, uint8_t padding);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get style of a spinbox.
 * @param templ pointer to template object
 * @param type which style should be get
 * @return style pointer to the style
 */
static inline lv_style_t * lv_spinbox_get_style(lv_obj_t * spinbox, lv_spinbox_style_t type)
{
    return lv_ta_get_style(spinbox, type);
}

/**
 * Get the spinbox numeral value (user has to convert to float according to its digit format)
 * @param spinbox pointer to spinbox
 * @return value integer value of the spinbox
 */
int32_t lv_spinbox_get_value(lv_obj_t * spinbox);

/*=====================
 * Other functions
 *====================*/

/**
 * Select next lower digit for edition by dividing the step by 10
 * @param spinbox pointer to spinbox
 */
void lv_spinbox_step_next(lv_obj_t * spinbox);

/**
 * Select next higher digit for edition by multiplying the step by 10
 * @param spinbox pointer to spinbox
 */
void lv_spinbox_step_previous(lv_obj_t * spinbox);

/**
 * Increment spinbox value by one step
 * @param spinbox pointer to spinbox
 */
void lv_spinbox_increment(lv_obj_t * spinbox);

/**
 * Decrement spinbox value by one step
 * @param spinbox pointer to spinbox
 */
void lv_spinbox_decrement(lv_obj_t * spinbox);


/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_SPINBOX*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_SPINBOX_H*/

/* lv_sw.h
 * Provides an on/off switch with separate track and knob styles.
 */
/**
 * @file lv_sw.h
 *
 */

#ifndef LV_SW_H
#define LV_SW_H

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

#if USE_LV_SW != 0

/*Testing of dependencies*/
#if USE_LV_SLIDER == 0
#error "lv_sw: lv_slider is required. Enable it in lv_conf.h (USE_LV_SLIDER  1)"
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/
#define LV_SWITCH_SLIDER_ANIM_MAX 1000

/**********************
 *      TYPEDEFS
 **********************/
/*Data of switch*/
typedef struct
{
    lv_slider_ext_t slider;         /*Ext. of ancestor*/
    /*New data for this type */
    lv_style_t *style_knob_off;     /*Style of the knob when the switch is OFF*/
    lv_style_t *style_knob_on;      /*Style of the knob when the switch is ON (NULL to use the same as OFF)*/
    lv_coord_t start_x;
    uint8_t changed   :1;           /*Indicates the switch state explicitly changed by drag*/
    uint8_t slided  :1;
#if USE_LV_ANIMATION
    uint16_t anim_time;				/*switch animation time */
#endif
} lv_sw_ext_t;

enum {
    LV_SW_STYLE_BG,
    LV_SW_STYLE_INDIC,
    LV_SW_STYLE_KNOB_OFF,
    LV_SW_STYLE_KNOB_ON,
};
typedef uint8_t lv_sw_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a switch objects
 * @param par pointer to an object, it will be the parent of the new switch
 * @param copy pointer to a switch object, if not NULL then the new object will be copied from it
 * @return pointer to the created switch
 */
lv_obj_t * lv_sw_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Turn ON the switch
 * @param sw pointer to a switch object
 */
void lv_sw_on(lv_obj_t *sw);

/**
 * Turn OFF the switch
 * @param sw pointer to a switch object
 */
void lv_sw_off(lv_obj_t *sw);

/**
 * Toggle the position of the switch
 * @param sw pointer to a switch object
 * @return resulting state of the switch.
 */
bool lv_sw_toggle(lv_obj_t *sw);

/**
 * Turn ON the switch with an animation
 * @param sw pointer to a switch object
 */
void lv_sw_on_anim(lv_obj_t * sw);

/**
 * Turn OFF the switch with an animation
 * @param sw pointer to a switch object
 */
void lv_sw_off_anim(lv_obj_t * sw);

/**
 * Toggle the position of the switch with an animation
 * @param sw pointer to a switch object
 * @return resulting state of the switch.
 */
bool lv_sw_toggle_anim(lv_obj_t *sw);

/**
 * Set a function which will be called when the switch is toggled by the user
 * @param sw pointer to switch object
 * @param action a callback function
 */
static inline void lv_sw_set_action(lv_obj_t * sw, lv_action_t action)
{
    lv_slider_set_action(sw, action);
}

/**
 * Set a style of a switch
 * @param sw pointer to a switch object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_sw_set_style(lv_obj_t *sw, lv_sw_style_t type, lv_style_t *style);

#if USE_LV_ANIMATION
/**
 * Set the animation time of the switch
 * @param sw pointer to a  switch object
 * @param anim_time animation time
 * @return style pointer to a style
 */
void lv_sw_set_anim_time(lv_obj_t *sw, uint16_t anim_time);
#endif

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the state of a switch
 * @param sw pointer to a switch object
 * @return false: OFF; true: ON
 */
static inline bool lv_sw_get_state(const lv_obj_t *sw)
{
    return lv_bar_get_value(sw) < LV_SWITCH_SLIDER_ANIM_MAX / 2 ? false : true;
}

/**
 * Get the switch action function
 * @param slider pointer to a switch object
 * @return the callback function
 */
static inline lv_action_t lv_sw_get_action(const lv_obj_t * slider)
{
    return lv_slider_get_action(slider);
}

/**
 * Get a style of a switch
 * @param sw pointer to a  switch object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_sw_get_style(const lv_obj_t *sw, lv_sw_style_t type);

/**
 * Get the animation time of the switch
 * @param sw pointer to a  switch object
 * @return style pointer to a style
 */
uint16_t lv_sw_get_anim_time(const lv_obj_t *sw);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_SW*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_SW_H*/

/* lv_table.h
 * Displays data in rows and columns with per-cell formatting.
 */
/**
 * @file lv_table.h
 *
 */

#ifndef LV_TABLE_H
#define LV_TABLE_H

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

#if USE_LV_TABLE != 0

/*Testing of dependencies*/
#if USE_LV_LABEL == 0
#error "lv_table: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/
#ifndef LV_TABLE_COL_MAX
#define LV_TABLE_COL_MAX    12
#endif

#define LV_TABLE_CELL_STYLE_CNT 4
/**********************
 *      TYPEDEFS
 **********************/

typedef union {
    struct {
        uint8_t align:2;
        uint8_t right_merge:1;
        uint8_t type:2;
        uint8_t crop:1;
    };
    uint8_t format_byte;
}lv_table_cell_format_t;

/*Data of table*/
typedef struct {
    /*New data for this type */
    uint16_t col_cnt;
    uint16_t row_cnt;
    char ** cell_data;
    lv_style_t * cell_style[LV_TABLE_CELL_STYLE_CNT];
    lv_coord_t col_w[LV_TABLE_COL_MAX];
} lv_table_ext_t;


/*Styles*/
enum {
    LV_TABLE_STYLE_BG,
    LV_TABLE_STYLE_CELL1,
    LV_TABLE_STYLE_CELL2,
    LV_TABLE_STYLE_CELL3,
    LV_TABLE_STYLE_CELL4,
};
typedef uint8_t lv_table_style_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a table object
 * @param par pointer to an object, it will be the parent of the new table
 * @param copy pointer to a table object, if not NULL then the new object will be copied from it
 * @return pointer to the created table
 */
lv_obj_t * lv_table_create(lv_obj_t * par, const lv_obj_t * copy);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the value of a cell.
 * @param table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @param txt text to display in the cell. It will be copied and saved so this variable is not required after this function call.
 */
void lv_table_set_cell_value(lv_obj_t * table, uint16_t row, uint16_t col, const char * txt);

/**
 * Set the number of rows
 * @param table table pointer to a Table object
 * @param row_cnt number of rows
 */
void lv_table_set_row_cnt(lv_obj_t * table, uint16_t row_cnt);

/**
 * Set the number of columns
 * @param table table pointer to a Table object
 * @param col_cnt number of columns. Must be < LV_TABLE_COL_MAX
 */
void lv_table_set_col_cnt(lv_obj_t * table, uint16_t col_cnt);

/**
 * Set the width of a column
 * @param table table pointer to a Table object
 * @param col_id id of the column [0 .. LV_TABLE_COL_MAX -1]
 * @param w width of the column
 */
void lv_table_set_col_width(lv_obj_t * table, uint16_t col_id, lv_coord_t w);

/**
 * Set the text align in a cell
 * @param table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @param align LV_LABEL_ALIGN_LEFT or LV_LABEL_ALIGN_CENTER or LV_LABEL_ALIGN_RIGHT
 */
void lv_table_set_cell_align(lv_obj_t * table, uint16_t row, uint16_t col, lv_label_align_t align);

/**
 * Set the type of a cell.
 * @param table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @param type 1,2,3 or 4. The cell style will be chosen accordingly.
 */
void lv_table_set_cell_type(lv_obj_t * table, uint16_t row, uint16_t col, uint8_t type);

/**
 * Set the cell crop. (Don't adjust the height of the cell according to its content)
 * @param table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @param crop true: crop the cell content; false: set the cell height to the content.
 */
void lv_table_set_cell_crop(lv_obj_t * table, uint16_t row, uint16_t col, bool crop);

/**
 * Merge a cell with the right neighbor. The value of the cell to the right won't be displayed.
 * @param table table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @param en true: merge right; false: don't merge right
 */
void lv_table_set_cell_merge_right(lv_obj_t * table, uint16_t row, uint16_t col, bool en);

/**
 * Set a style of a table.
 * @param table pointer to table object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_table_set_style(lv_obj_t * table, lv_table_style_t type, lv_style_t * style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the value of a cell.
 * @param table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @return text in the cell
 */
const char * lv_table_get_cell_value(lv_obj_t * table, uint16_t row, uint16_t col);

/**
 * Get the number of rows.
 * @param table table pointer to a Table object
 * @return number of rows.
 */
uint16_t lv_table_get_row_cnt(lv_obj_t * table);

/**
 * Get the number of columns.
 * @param table table pointer to a Table object
 * @return number of columns.
 */
uint16_t lv_table_get_col_cnt(lv_obj_t * table);

/**
 * Get the width of a column
 * @param table table pointer to a Table object
 * @param col_id id of the column [0 .. LV_TABLE_COL_MAX -1]
 * @return width of the column
 */
lv_coord_t lv_table_get_col_width(lv_obj_t * table, uint16_t col_id);

/**
 * Get the text align of a cell
 * @param table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @return LV_LABEL_ALIGN_LEFT (default in case of error) or LV_LABEL_ALIGN_CENTER or LV_LABEL_ALIGN_RIGHT
 */
lv_label_align_t lv_table_get_cell_align(lv_obj_t * table, uint16_t row, uint16_t col);

/**
 * Get the type of a cell
 * @param table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @return 1,2,3 or 4
 */
lv_label_align_t lv_table_get_cell_type(lv_obj_t * table, uint16_t row, uint16_t col);


/**
 * Get the crop property of a cell
 * @param table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @return true: text crop enabled; false: disabled
 */
lv_label_align_t lv_table_get_cell_crop(lv_obj_t * table, uint16_t row, uint16_t col);

/**
 * Get the cell merge attribute.
 * @param table table pointer to a Table object
 * @param row id of the row [0 .. row_cnt -1]
 * @param col id of the column [0 .. col_cnt -1]
 * @return true: merge right; false: don't merge right
 */
bool lv_table_get_cell_merge_right(lv_obj_t * table, uint16_t row, uint16_t col);

/**
 * Get style of a table.
 * @param table pointer to table object
 * @param type which style should be get
 * @return style pointer to the style
 */
lv_style_t * lv_table_get_style(const lv_obj_t * table, lv_table_style_t type);

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_TABLE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_TABLE_H*/

/* lv_win.h
 * Provides a window with a header, content, and controls.
 */
/**
 * @file lv_win.h
 *
 */

#ifndef LV_WIN_H
#define LV_WIN_H

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

#if USE_LV_WIN != 0

/*Testing of dependencies*/
#if USE_LV_BTN == 0
#error "lv_win: lv_btn is required. Enable it in lv_conf.h (USE_LV_BTN  1) "
#endif

#if USE_LV_LABEL == 0
#error "lv_win: lv_label is required. Enable it in lv_conf.h (USE_LV_LABEL  1) "
#endif

#if USE_LV_IMG == 0
#error "lv_win: lv_img is required. Enable it in lv_conf.h (USE_LV_IMG  1) "
#endif


#if USE_LV_PAGE == 0
#error "lv_win: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of window*/
typedef struct
{
    /*Ext. of ancestor*/
    /*New data for this type */
    lv_obj_t * page;                /*Pointer to a page which holds the content*/
    lv_obj_t * header;              /*Pointer to the header container of the window*/
    lv_obj_t * title;               /*Pointer to the title label of the window*/
    lv_style_t * style_header;      /*Style of the header container*/
    lv_style_t * style_btn_rel;    /*Control button releases style*/
    lv_style_t * style_btn_pr;     /*Control button pressed style*/
    lv_coord_t btn_size;               /*Size of the control buttons (square)*/
} lv_win_ext_t;

enum {
    LV_WIN_STYLE_BG,
    LV_WIN_STYLE_CONTENT_BG,
    LV_WIN_STYLE_CONTENT_SCRL,
    LV_WIN_STYLE_SB,
    LV_WIN_STYLE_HEADER,
    LV_WIN_STYLE_BTN_REL,
    LV_WIN_STYLE_BTN_PR,
};
typedef uint8_t lv_win_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a window objects
 * @param par pointer to an object, it will be the parent of the new window
 * @param copy pointer to a window object, if not NULL then the new object will be copied from it
 * @return pointer to the created window
 */
lv_obj_t * lv_win_create(lv_obj_t * par, const lv_obj_t * copy);

/**
 * Delete all children of the scrl object, without deleting scrl child.
 * @param obj pointer to an object
 */
void lv_win_clean(lv_obj_t *obj);

/*======================
 * Add/remove functions
 *=====================*/

/**
 * Add control button to the header of the window
 * @param win pointer to a window object
 * @param img_src an image source ('lv_img_t' variable, path to file or a symbol)
 * @param rel_action a function pointer to call when the button is released
 * @return pointer to the created button object
 */
lv_obj_t * lv_win_add_btn(lv_obj_t * win, const void * img_src, lv_action_t rel_action);

/*=====================
 * Setter functions
 *====================*/

/**
 * A release action which can be assigned to a window control button to close it
 * @param btn pointer to the released button
 * @return always LV_ACTION_RES_INV because the button is deleted with the window
 */
lv_res_t lv_win_close_action(lv_obj_t * btn);

/**
 * Set the title of a window
 * @param win pointer to a window object
 * @param title string of the new title
 */
void lv_win_set_title(lv_obj_t * win, const char * title);

/**
 * Set the control button size of a window
 * @param win pointer to a window object
 * @return control button size
 */
void lv_win_set_btn_size(lv_obj_t * win, lv_coord_t size);

/**
 * Set the layout of the window
 * @param win pointer to a window object
 * @param layout the layout from 'lv_layout_t'
 */
void lv_win_set_layout(lv_obj_t *win, lv_layout_t layout);

/**
 * Set the scroll bar mode of a window
 * @param win pointer to a window object
 * @param sb_mode the new scroll bar mode from  'lv_sb_mode_t'
 */
void lv_win_set_sb_mode(lv_obj_t *win, lv_sb_mode_t sb_mode);

/**
 * Set a style of a window
 * @param win pointer to a window object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_win_set_style(lv_obj_t *win, lv_win_style_t type, lv_style_t *style);

/**
 * Set drag status of a window. If set to 'true' window can be dragged like on a PC.
 * @param win pointer to a window object
 * @param en whether dragging is enabled
 */
void lv_win_set_drag(lv_obj_t *win, bool en);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the title of a window
 * @param win pointer to a window object
 * @return title string of the window
 */
const char * lv_win_get_title(const lv_obj_t * win);

/**
* Get the content holder object of window (`lv_page`) to allow additional customization
* @param win pointer to a window object
* @return the Page object where the window's content is
*/
lv_obj_t * lv_win_get_content(const lv_obj_t * win);

/**
 * Get the control button size of a window
 * @param win pointer to a window object
 * @return control button size
 */
lv_coord_t lv_win_get_btn_size(const lv_obj_t * win);

/**
 * Get the pointer of a widow from one of  its control button.
 * It is useful in the action of the control buttons where only button is known.
 * @param ctrl_btn pointer to a control button of a window
 * @return pointer to the window of 'ctrl_btn'
 */
lv_obj_t * lv_win_get_from_btn(const lv_obj_t * ctrl_btn);

/**
 * Get the layout of a window
 * @param win pointer to a window object
 * @return the layout of the window (from 'lv_layout_t')
 */
lv_layout_t lv_win_get_layout(lv_obj_t *win);

/**
 * Get the scroll bar mode of a window
 * @param win pointer to a window object
 * @return the scroll bar mode of the window (from 'lv_sb_mode_t')
 */
lv_sb_mode_t lv_win_get_sb_mode(lv_obj_t *win);

/**
 * Get width of the content area (page scrollable) of the window
 * @param win pointer to a window object
 * @return the width of the content area
 */
lv_coord_t lv_win_get_width(lv_obj_t * win);

/**
 * Get a style of a window
 * @param win pointer to a button object
 * @param type which style window be get
 * @return style pointer to a style
 */
lv_style_t * lv_win_get_style(const lv_obj_t *win, lv_win_style_t type);

/**
 * Get drag status of a window. If set to 'true' window can be dragged like on a PC.
 * @param win pointer to a window object
 * @return whether window is draggable
 */
static inline bool lv_win_get_drag(const lv_obj_t *win)
{
    return lv_obj_get_drag(win);
}

/*=====================
 * Other functions
 *====================*/

/**
 * Focus on an object. It ensures that the object will be visible in the window.
 * @param win pointer to a window object
 * @param obj pointer to an object to focus (must be in the window)
 * @param anim_time scroll animation time in milliseconds (0: no animation)
 */
void lv_win_focus(lv_obj_t * win, lv_obj_t * obj, uint16_t anim_time);

/**
 * Scroll the window horizontally
 * @param win pointer to a window object
 * @param dist the distance to scroll (< 0: scroll right; > 0 scroll left)
 */
static inline void lv_win_scroll_hor(lv_obj_t * win, lv_coord_t dist)
{
    lv_win_ext_t * ext = (lv_win_ext_t *)lv_obj_get_ext_attr(win);
    lv_page_scroll_hor(ext->page, dist);
}
/**
 * Scroll the window vertically
 * @param win pointer to a window object
 * @param dist the distance to scroll (< 0: scroll down; > 0 scroll up)
 */
static inline void lv_win_scroll_ver(lv_obj_t * win, lv_coord_t dist)
{
    lv_win_ext_t * ext = (lv_win_ext_t *)lv_obj_get_ext_attr(win);
    lv_page_scroll_ver(ext->page, dist);
}

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_WIN*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_WIN_H*/

/* lv_tabview.h
 * Organizes content into named tabs.
 */
/**
 * @file lv_tabview.h
 *
 */

#ifndef LV_TABVIEW_H
#define LV_TABVIEW_H

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

#if USE_LV_TABVIEW != 0

/*Testing of dependencies*/
#if USE_LV_BTNM == 0
#error "lv_tabview: lv_btnm is required. Enable it in lv_conf.h (USE_LV_BTNM  1) "
#endif

#if USE_LV_PAGE == 0
#error "lv_tabview: lv_page is required. Enable it in lv_conf.h (USE_LV_PAGE  1) "
#endif

#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* parametes: pointer to a tabview object, tab_id
 * return: LV_RES_INV: to prevent the loading of the tab;  LV_RES_OK: if everything is fine*/
typedef lv_res_t (*lv_tabview_action_t)(lv_obj_t *, uint16_t);


enum {
    LV_TABVIEW_BTNS_POS_TOP,
    LV_TABVIEW_BTNS_POS_BOTTOM,
};
typedef uint8_t lv_tabview_btns_pos_t;

/*Data of tab*/
typedef struct
{
    /*Ext. of ancestor*/
    /*New data for this type */
    lv_obj_t * btns;
    lv_obj_t * indic;
    lv_obj_t * content;   /*A rectangle to show the current tab*/
    const char ** tab_name_ptr;
    lv_point_t point_last;
    uint16_t tab_cur;
    uint16_t tab_cnt;
    uint16_t anim_time;
    uint8_t slide_enable :1;    /*1: enable horizontal sliding by touch pad*/
    uint8_t draging :1;
    uint8_t drag_hor :1;
    uint8_t btns_hide :1;
    lv_tabview_btns_pos_t btns_pos :1;
    lv_tabview_action_t tab_load_action;
} lv_tabview_ext_t;

enum {
    LV_TABVIEW_STYLE_BG,
    LV_TABVIEW_STYLE_INDIC,
    LV_TABVIEW_STYLE_BTN_BG,
    LV_TABVIEW_STYLE_BTN_REL,
    LV_TABVIEW_STYLE_BTN_PR,
    LV_TABVIEW_STYLE_BTN_TGL_REL,
    LV_TABVIEW_STYLE_BTN_TGL_PR,
};
typedef uint8_t lv_tabview_style_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**
 * Create a Tab view object
 * @param par pointer to an object, it will be the parent of the new tab
 * @param copy pointer to a tab object, if not NULL then the new object will be copied from it
 * @return pointer to the created tab
 */
lv_obj_t * lv_tabview_create(lv_obj_t * par, const lv_obj_t * copy);

/**
 * Delete all children of the scrl object, without deleting scrl child.
 * @param obj pointer to an object
 */
void lv_tabview_clean(lv_obj_t *obj);

/*======================
 * Add/remove functions
 *=====================*/

/**
 * Add a new tab with the given name
 * @param tabview pointer to Tab view object where to ass the new tab
 * @param name the text on the tab button
 * @return pointer to the created page object (lv_page). You can create your content here
 */
lv_obj_t * lv_tabview_add_tab(lv_obj_t * tabview, const char * name);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set a new tab
 * @param tabview pointer to Tab view object
 * @param id index of a tab to load
 * @param anim_en true: set with sliding animation; false: set immediately
 */
void lv_tabview_set_tab_act(lv_obj_t * tabview, uint16_t id, bool anim_en);

/**
 * Set an action to call when a tab is loaded (Good to create content only if required)
 * lv_tabview_get_act() still gives the current (old) tab (to remove content from here)
 * @param tabview pointer to a tabview object
 * @param action pointer to a function to call when a tab is loaded
 */
void lv_tabview_set_tab_load_action(lv_obj_t *tabview, lv_tabview_action_t action);

/**
 * Enable horizontal sliding with touch pad
 * @param tabview pointer to Tab view object
 * @param en true: enable sliding; false: disable sliding
 */
void lv_tabview_set_sliding(lv_obj_t * tabview, bool en);

/**
 * Set the animation time of tab view when a new tab is loaded
 * @param tabview pointer to Tab view object
 * @param anim_time time of animation in milliseconds
 */
void lv_tabview_set_anim_time(lv_obj_t * tabview, uint16_t anim_time);

/**
 * Set the style of a tab view
 * @param tabview pointer to a tan view object
 * @param type which style should be set
 * @param style pointer to the new style
 */
void lv_tabview_set_style(lv_obj_t *tabview, lv_tabview_style_t type, lv_style_t *style);

/**
 * Set the position of tab select buttons
 * @param tabview pointer to a tab view object
 * @param btns_pos which button position
 */
void lv_tabview_set_btns_pos(lv_obj_t *tabview, lv_tabview_btns_pos_t btns_pos);

/**
 * Set whether tab buttons are hidden
 * @param tabview pointer to a tab view object
 * @param en whether tab buttons are hidden
 */
void lv_tabview_set_btns_hidden(lv_obj_t *tabview, bool en);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the index of the currently active tab
 * @param tabview pointer to Tab view object
 * @return the active tab index
 */
uint16_t lv_tabview_get_tab_act(const lv_obj_t * tabview);

/**
 * Get the number of tabs
 * @param tabview pointer to Tab view object
 * @return tab count
 */
uint16_t lv_tabview_get_tab_count(const lv_obj_t * tabview);
/**
 * Get the page (content area) of a tab
 * @param tabview pointer to Tab view object
 * @param id index of the tab (>= 0)
 * @return pointer to page (lv_page) object
 */
lv_obj_t * lv_tabview_get_tab(const lv_obj_t * tabview, uint16_t id);

/**
 * Get the tab load action
 * @param tabview pointer to a tabview object
 * @param return the current tab load action
 */
lv_tabview_action_t lv_tabview_get_tab_load_action(const lv_obj_t *tabview);

/**
 * Get horizontal sliding is enabled or not
 * @param tabview pointer to Tab view object
 * @return true: enable sliding; false: disable sliding
 */
bool lv_tabview_get_sliding(const lv_obj_t * tabview);

/**
 * Get the animation time of tab view when a new tab is loaded
 * @param tabview pointer to Tab view object
 * @return time of animation in milliseconds
 */
uint16_t lv_tabview_get_anim_time(const lv_obj_t * tabview);

/**
 * Get a style of a tab view
 * @param tabview pointer to a ab view object
 * @param type which style should be get
 * @return style pointer to a style
 */
lv_style_t * lv_tabview_get_style(const lv_obj_t *tabview, lv_tabview_style_t type);

/**
 * Get position of tab select buttons
 * @param tabview pointer to a ab view object
 */
lv_tabview_btns_pos_t lv_tabview_get_btns_pos(const lv_obj_t *tabview);

/**
 * Get whether tab buttons are hidden
 * @param tabview pointer to a tab view object
 * @return whether tab buttons are hidden
 */
bool lv_tabview_get_btns_hidden(const lv_obj_t *tabview);

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_TABVIEW*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_TABVIEW_H*/

/* lv_tileview.h
 * Organizes content into tiles navigated with swipe gestures.
 */
/**
 * @file lv_tileview.h
 *
 */


#ifndef LV_TILEVIEW_H
#define LV_TILEVIEW_H

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

#if USE_LV_TILEVIEW != 0


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/



/* parametes: pointer to a tileview object, x, y (tile coordinates to load)
 * return: LV_RES_INV: to prevent the loading of the tab;  LV_RES_OK: if everything is fine*/
typedef lv_res_t (*lv_tileview_action_t)(lv_obj_t *, lv_coord_t, lv_coord_t);

/*Data of tileview*/
typedef struct {
    lv_page_ext_t page;
    /*New data for this type */
    const lv_point_t * valid_pos;
    uint16_t anim_time;
    lv_tileview_action_t action;
    lv_point_t act_id;
    uint8_t drag_top_en     :1;
    uint8_t drag_bottom_en  :1;
    uint8_t drag_left_en    :1;
    uint8_t drag_right_en   :1;
    uint8_t drag_hor   :1;
    uint8_t drag_ver   :1;
} lv_tileview_ext_t;


/*Styles*/
enum {
    LV_TILEVIEW_STYLE_BG,
};
typedef uint8_t lv_tileview_style_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a tileview objects
 * @param par pointer to an object, it will be the parent of the new tileview
 * @param copy pointer to a tileview object, if not NULL then the new object will be copied from it
 * @return pointer to the created tileview
 */
lv_obj_t * lv_tileview_create(lv_obj_t * par, const lv_obj_t * copy);

/*======================
 * Add/remove functions
 *=====================*/

/**
 * Register an object on the tileview. The register object will able to slide the tileview
 * @param element pointer to an object
 */
void lv_tileview_add_element(lv_obj_t * element);

/*=====================
 * Setter functions
 *====================*/


/**
 * Set the valid position's indices. The scrolling will be possible only to these positions.
 * @param tileview pointer to a Tileview object
 * @param valid_pos array width the indices. E.g. `lv_point_t p[] = {{0,0}, {1,0}, {1,1}, {LV_COORD_MIN, LV_COORD_MIN}};`
 * Must be closed with `{LV_COORD_MIN, LV_COORD_MIN}`. Only the pointer is saved so can't be a local variable.
 */
void lv_tileview_set_valid_positions(lv_obj_t * tileview, const lv_point_t * valid_pos);

/**
 * Set the tile to be shown
 * @param tileview pointer to a tileview object
 * @param x column id (0, 1, 2...)
 * @param y line id (0, 1, 2...)
 * @param anim_en true: move with animation
 */
void lv_tileview_set_tile_act(lv_obj_t * tileview, lv_coord_t x, lv_coord_t y, bool anim_en);

/**
 * Enable the edge flash effect. (Show an arc when the an edge is reached)
 * @param tileview pointer to a Tileview
 * @param en true or false to enable/disable end flash
 */
static inline void lv_tileview_set_edge_flash(lv_obj_t * tileview, bool en)
{
    lv_page_set_edge_flash(tileview, en);
}

/**
 * Set a style of a tileview.
 * @param tileview pointer to tileview object
 * @param type which style should be set
 * @param style pointer to a style
 */
void lv_tileview_set_style(lv_obj_t * tileview, lv_tileview_style_t type, lv_style_t *style);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the scroll propagation property
 * @param tileview pointer to a Tileview
 * @return true or false
 */
static inline bool lv_tileview_get_edge_flash(lv_obj_t * tileview)
{
    return lv_page_get_edge_flash(tileview);
}

/**
 * Get style of a tileview.
 * @param tileview pointer to tileview object
 * @param type which style should be get
 * @return style pointer to the style
 */
lv_style_t * lv_tileview_get_style(const lv_obj_t * tileview, lv_tileview_style_t type);

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_TILEVIEW*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_TILEVIEW_H*/

#endif /* PROS_DISPLAY_LV_OBJX_H */
