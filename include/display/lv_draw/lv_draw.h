/**
 * Rendering primitives for shapes, text, and images.
 * Widgets use these functions to draw into the active display buffer.
 * Use the widget APIs for interactive controls and layout.
 * The sections retain their original LVGL 5.3 declarations.
 */
#ifndef PROS_DISPLAY_LV_DRAW_H
#define PROS_DISPLAY_LV_DRAW_H

/* lv_draw.h
 * Defines the shared drawing API and rendering support types.
 */
/**
 * @file lv_draw.h
 *
 */

#ifndef LV_DRAW_H
#define LV_DRAW_H

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

#include "display/lv_core/lv_core.h"
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/
/*If image pixels contains alpha we need to know how much byte is a pixel*/
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
# define LV_IMG_PX_SIZE_ALPHA_BYTE   2
#elif LV_COLOR_DEPTH == 16
# define LV_IMG_PX_SIZE_ALPHA_BYTE   3
#elif LV_COLOR_DEPTH == 32
# define LV_IMG_PX_SIZE_ALPHA_BYTE   4
#endif

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LV_IMG_SRC_VARIABLE,
    LV_IMG_SRC_FILE,
    LV_IMG_SRC_SYMBOL,
    LV_IMG_SRC_UNKNOWN,
};
typedef uint8_t lv_img_src_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

#if LV_ANTIALIAS != 0

/**
 * Get the opacity of a pixel based it's position in a line segment
 * @param seg segment length
 * @param px_id position of  of a pixel which opacity should be get [0..seg-1]
 * @param base_opa the base opacity
 * @return the opacity of the given pixel
 */
lv_opa_t lv_draw_aa_get_opa(lv_coord_t seg, lv_coord_t px_id, lv_opa_t base_opa);

/**
 * Add a vertical  anti-aliasing segment (pixels with decreasing opacity)
 * @param x start point x coordinate
 * @param y start point y coordinate
 * @param length length of segment (negative value to start from 0 opacity)
 * @param mask draw only in this area
 * @param color color of pixels
 * @param opa maximum opacity
 */
void lv_draw_aa_ver_seg(lv_coord_t x, lv_coord_t y, lv_coord_t length, const lv_area_t * mask, lv_color_t color, lv_opa_t opa);

/**
 * Add a horizontal anti-aliasing segment (pixels with decreasing opacity)
 * @param x start point x coordinate
 * @param y start point y coordinate
 * @param length length of segment (negative value to start from 0 opacity)
 * @param mask draw only in this area
 * @param color color of pixels
 * @param opa maximum opacity
 */
void lv_draw_aa_hor_seg(lv_coord_t x, lv_coord_t y, lv_coord_t length, const lv_area_t * mask, lv_color_t color, lv_opa_t opa);
#endif

/**********************
 *  GLOBAL VARIABLES
 **********************/
extern void (*const px_fp)(lv_coord_t x, lv_coord_t y, const lv_area_t * mask, lv_color_t color, lv_opa_t opa);
extern void (*const fill_fp)(const lv_area_t * coords, const lv_area_t * mask, lv_color_t color, lv_opa_t opa);
extern void (*const letter_fp)(const lv_point_t * pos_p, const lv_area_t * mask, const lv_font_t * font_p, uint32_t letter, lv_color_t color, lv_opa_t opa);
extern void (*const map_fp)(const lv_area_t * cords_p, const lv_area_t * mask_p,
                            const uint8_t * map_p, lv_opa_t opa, bool chroma_key, bool alpha_byte,
                            lv_color_t recolor, lv_opa_t recolor_opa);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_DRAW_H*/

/* lv_draw_arc.h
 * Renders curved arc segments into a clipped drawing region.
 */
/**
 * @file lv_draw_arc.h
 *
 */

#ifndef LV_DRAW_ARC_H
#define LV_DRAW_ARC_H

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

/**
 * Draw an arc. (Can draw pie too with great thickness.)
 * @param center_x the x coordinate of the center of the arc
 * @param center_y the y coordinate of the center of the arc
 * @param radius the radius of the arc
 * @param mask the arc will be drawn only in this mask
 * @param start_angle the start angle of the arc (0 deg on the bottom, 90 deg on the right)
 * @param end_angle the end angle of the arc
 * @param style style of the arc (`body.thickness`, `body.main_color`, `body.opa` is used)
 * @param opa_scale scale down all opacities by the factor
 */
void lv_draw_arc(lv_coord_t center_x, lv_coord_t center_y, uint16_t radius, const lv_area_t * mask,
                 uint16_t start_angle, uint16_t end_angle, const lv_style_t * style, lv_opa_t opa_scale);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DRAW_ARC*/

/* lv_draw_img.h
 * Defines image data and decoders and draws images from supported sources.
 */
/**
 * @file lv_draw_img.h
 *
 */

#ifndef LV_DRAW_IMG_H
#define LV_DRAW_IMG_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display/lv_core/lv_core.h"

/*********************
 *      DEFINES
 *********************/
#define LV_IMG_DECODER_OPEN_FAIL    ((void*)(-1))

/**********************
 *      TYPEDEFS
 **********************/
struct _lv_img_t;

typedef struct {

    /* The first 8 bit is very important to distinguish the different source types.
     * For more info see `lv_img_get_src_type()` in lv_img.c */
    uint32_t cf           :5;    /* Color format: See `lv_img_color_format_t`*/
    uint32_t always_zero  :3;    /*It the upper bits of the first byte. Always zero to look like a non-printable character*/

    uint32_t reserved     :2;   /*Reserved to be used later*/

    uint32_t w:11;              /*Width of the image map*/
    uint32_t h:11;              /*Height of the image map*/
} lv_img_header_t;

/*Image color format*/
enum {
    LV_IMG_CF_UNKOWN = 0,

    LV_IMG_CF_RAW,                  /*Contains the file as it is. Needs custom decoder function*/
    LV_IMG_CF_RAW_ALPHA,            /*Contains the file as it is. The image has alpha. Needs custom decoder function*/
    LV_IMG_CF_RAW_CHROMA_KEYED,     /*Contains the file as it is. The image is chroma keyed. Needs custom decoder function*/

    LV_IMG_CF_TRUE_COLOR,           /*Color format and depth should match with LV_COLOR settings*/
    LV_IMG_CF_TRUE_COLOR_ALPHA,     /*Same as `LV_IMG_CF_TRUE_COLOR` but every pixel has an alpha byte*/
    LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED,  /*Same as `LV_IMG_CF_TRUE_COLOR` but LV_COLOR_TRANSP pixels will be transparent*/

    LV_IMG_CF_INDEXED_1BIT,         /*Can have 2 different colors in a palette (always chroma keyed)*/
    LV_IMG_CF_INDEXED_2BIT,         /*Can have 4 different colors in a palette (always chroma keyed)*/
    LV_IMG_CF_INDEXED_4BIT,         /*Can have 16 different colors in a palette (always chroma keyed)*/
    LV_IMG_CF_INDEXED_8BIT,         /*Can have 256 different colors in a palette (always chroma keyed)*/

    LV_IMG_CF_ALPHA_1BIT,           /*Can have one color and it can be drawn or not*/
    LV_IMG_CF_ALPHA_2BIT,           /*Can have one color but 4 different alpha value*/
    LV_IMG_CF_ALPHA_4BIT,           /*Can have one color but 16 different alpha value*/
    LV_IMG_CF_ALPHA_8BIT,           /*Can have one color but 256 different alpha value*/
};
typedef uint8_t lv_img_cf_t;

/* Image header it is compatible with
 * the result image converter utility*/
typedef struct
{
    lv_img_header_t header;
    uint32_t data_size;
    const uint8_t * data;
} lv_img_dsc_t;

/* Decoder function definitions */


/**
 * Get info from an image and store in the `header`
 * @param src the image source. Can be a pointer to a C array or a file name (Use `lv_img_src_get_type` to determine the type)
 * @param header store the info here
 * @return LV_RES_OK: info written correctly; LV_RES_INV: failed
 */
typedef lv_res_t (*lv_img_decoder_info_f_t)(const void * src, lv_img_header_t * header);

/**
 * Open an image for decoding. Prepare it as it is required to read it later
 * @param src the image source. Can be a pointer to a C array or a file name (Use `lv_img_src_get_type` to determine the type)
 * @param style the style of image (maybe it will be required to determine a color or something)
 * @return there are 3 possible return values:
 *    1) buffer with the decoded image
 *    2) if can decode the whole image NULL. decoder_read_line will be called to read the image line-by-line
 *    3) LV_IMG_DECODER_OPEN_FAIL if the image format is unknown to the decoder or an error occurred
 */
typedef const uint8_t * (*lv_img_decoder_open_f_t)(const void * src, const lv_style_t * style);

/**
 * Decode `len` pixels starting from the given `x`, `y` coordinates and store them in `buf`.
 * Required only if the "open" function can't return with the whole decoded pixel array.
 * @param x start x coordinate
 * @param y startt y coordinate
 * @param len number of pixels to decode
 * @param buf a buffer to store the decoded pixels
 * @return LV_RES_OK: ok; LV_RES_INV: failed
 */
typedef lv_res_t (*lv_img_decoder_read_line_f_t)(lv_coord_t x, lv_coord_t y, lv_coord_t len, uint8_t * buf);

/**
 * Close the pending decoding. Free resources etc.
 */
typedef void (*lv_img_decoder_close_f_t)(void);

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Draw an image
 * @param coords the coordinates of the image
 * @param mask the image will be drawn only in this area
 * @param src pointer to a lv_color_t array which contains the pixels of the image
 * @param style style of the image
 * @param opa_scale scale down all opacities by the factor
 */
void lv_draw_img(const lv_area_t * coords, const lv_area_t * mask,
                 const void * src, const lv_style_t * style, lv_opa_t opa_scale);


/**
 * Get the type of an image source
 * @param src pointer to an image source:
 *  - pointer to an 'lv_img_t' variable (image stored internally and compiled into the code)
 *  - a path to a file (e.g. "S:/folder/image.bin")
 *  - or a symbol (e.g. SYMBOL_CLOSE)
 * @return type of the image source LV_IMG_SRC_VARIABLE/FILE/SYMBOL/UNKOWN
 */
lv_img_src_t lv_img_src_get_type(const void * src);

/**
 * Set custom decoder functions. See the typdefs of the function typed above for more info about them
 * @param info_fp info get function
 * @param open_fp open function
 * @param read_fp read line function
 * @param close_fp clode function
 */
void lv_img_decoder_set_custom(lv_img_decoder_info_f_t  info_fp, lv_img_decoder_open_f_t  open_fp,
                               lv_img_decoder_read_line_f_t read_fp, lv_img_decoder_close_f_t close_fp);

lv_res_t lv_img_dsc_get_info(const char * src, lv_img_header_t * header);

uint8_t lv_img_color_format_get_px_size(lv_img_cf_t cf);

bool lv_img_color_format_is_chroma_keyed(lv_img_cf_t cf);

bool lv_img_color_format_has_alpha(lv_img_cf_t cf);


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TEMPL_H*/

/* lv_draw_label.h
 * Draws formatted glyphs and text within a clipped region.
 */
/**
 * @file lv_draw_label.h
 *
 */

#ifndef LV_DRAW_LABEL_H
#define LV_DRAW_LABEL_H

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

/**
 * Write a text
 * @param coords coordinates of the label
 * @param mask the label will be drawn only in this area
 * @param style pointer to a style
 * @param opa_scale scale down all opacities by the factor
 * @param txt 0 terminated text to write
 * @param flag settings for the text from 'txt_flag_t' enum
 * @param offset text offset in x and y direction (NULL if unused)
 *
 */
void lv_draw_label(const lv_area_t * coords,const lv_area_t * mask, const lv_style_t * style, lv_opa_t opa_scale,
                   const char * txt, lv_txt_flag_t flag, lv_point_t * offset);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DRAW_LABEL_H*/

/* lv_draw_line.h
 * Draws line segments with the requested style.
 */
/**
 * @file lv_draw_line.h
 *
 */

#ifndef LV_DRAW_LINE_H
#define LV_DRAW_LINE_H

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

/**
 * Draw a line
 * @param point1 first point of the line
 * @param point2 second point of the line
 * @param mask the line will be drawn only on this area
 * @param style pointer to a line's style
 * @param opa_scale scale down all opacities by the factor
 */
void lv_draw_line(const lv_point_t * point1, const lv_point_t * point2, const lv_area_t * mask,
                  const lv_style_t * style, lv_opa_t opa_scale);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DRAW_LINE_H*/

/* lv_draw_rbasic.h
 * Provides low-level drawing operations for the real display buffer.
 */
/**
 * @file lv_draw_rbasic..h
 *
 */

#ifndef LV_DRAW_RBASIC_H
#define LV_DRAW_RBASIC_H

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

#if USE_LV_REAL_DRAW != 0

#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_rpx(lv_coord_t x, lv_coord_t y, const lv_area_t * mask_p, lv_color_t color, lv_opa_t opa);

/**
 * Fill an area on the display
 * @param cords_p coordinates of the area to fill
 * @param mask_p fill only o this mask
 * @param color fill color
 * @param opa opacity (ignored, only for compatibility with lv_vfill)
 */
void lv_rfill(const lv_area_t * cords_p, const lv_area_t * mask_p,
              lv_color_t color, lv_opa_t opa);

/**
 * Draw a letter to the display
 * @param pos_p left-top coordinate of the latter
 * @param mask_p the letter will be drawn only on this area
 * @param font_p pointer to font
 * @param letter a letter to draw
 * @param color color of letter
 * @param opa opacity of letter (ignored, only for compatibility with lv_vletter)
 */
void lv_rletter(const lv_point_t * pos_p, const lv_area_t * mask_p,
                const lv_font_t * font_p, uint32_t letter,
                lv_color_t color, lv_opa_t opa);

/**
 * When the letter is ant-aliased it needs to know the background color
 * @param bg_color the background color of the currently drawn letter
 */
void lv_rletter_set_background(lv_color_t color);


/**
 * Draw a color map to the display (image)
 * @param cords_p coordinates the color map
 * @param mask_p the map will drawn only on this area
 * @param map_p pointer to a lv_color_t array
 * @param opa opacity of the map (ignored, only for compatibility with 'lv_vmap')
 * @param chroma_keyed true: enable transparency of LV_IMG_LV_COLOR_TRANSP color pixels
 * @param alpha_byte true: extra alpha byte is inserted for every pixel (not supported, only l'v_vmap' can draw it)
 * @param recolor mix the pixels with this color
 * @param recolor_opa the intense of recoloring
 */
void lv_rmap(const lv_area_t * cords_p, const lv_area_t * mask_p,
             const uint8_t * map_p, lv_opa_t opa, bool chroma_key, bool alpha_byte,
             lv_color_t recolor, lv_opa_t recolor_opa);
/**********************
 *      MACROS
 **********************/

#endif  /*USE_LV_REAL_DRAW*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_DRAW_RBASIC_H*/

/* lv_draw_rect.h
 * Draws styled rectangles including backgrounds and borders.
 */
/**
 * @file lv_draw_rect.h
 *
 */

#ifndef LV_DRAW_RECT_H
#define LV_DRAW_RECT_H

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

/**
 * Draw a rectangle
 * @param coords the coordinates of the rectangle
 * @param mask the rectangle will be drawn only in this mask
 * @param style pointer to a style
 * @param opa_scale scale down all opacities by the factor
 */
void lv_draw_rect(const lv_area_t * coords, const lv_area_t * mask, const lv_style_t * style, lv_opa_t opa_scale);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DRAW_RECT_H*/

/* lv_draw_triangle.h
 * Fills triangles used by other drawing primitives.
 */
/**
 * @file lv_draw_triangle.h
 *
 */

#ifndef LV_DRAW_TRIANGLE_H
#define LV_DRAW_TRIANGLE_H

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
/*Experimental use for 3D modeling*/
#define USE_LV_TRIANGLE 1

#if USE_LV_TRIANGLE != 0
/**
 *
 * @param points pointer to an array with 3 points
 * @param mask the triangle will be drawn only in this mask
 * @param color color of the triangle
 */
void lv_draw_triangle(const lv_point_t * points, const lv_area_t * mask, lv_color_t color);
#endif

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DRAW_TRIANGLE_H*/

/* lv_draw_vbasic.h
 * Provides low-level drawing operations for the virtual display buffer.
 */
/**
 * @file lv_draw_vbasic.h
 *
 */

#ifndef LV_DRAW_VBASIC_H
#define LV_DRAW_VBASIC_H

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
#include "display/lv_misc/lv_misc.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_vpx(lv_coord_t x, lv_coord_t y, const lv_area_t * mask_p, lv_color_t color, lv_opa_t opa);
/**
 * Fill an area in the Virtual Display Buffer
 * @param cords_p coordinates of the area to fill
 * @param mask_p fill only o this mask
 * @param color fill color
 * @param opa opacity of the area (0..255)
 */
void lv_vfill(const lv_area_t * cords_p, const lv_area_t * mask_p,
              lv_color_t color, lv_opa_t opa);

/**
 * Draw a letter in the Virtual Display Buffer
 * @param pos_p left-top coordinate of the latter
 * @param mask_p the letter will be drawn only on this area
 * @param font_p pointer to font
 * @param letter a letter to draw
 * @param color color of letter
 * @param opa opacity of letter (0..255)
 */
void lv_vletter(const lv_point_t * pos_p, const lv_area_t * mask_p,
                const lv_font_t * font_p, uint32_t letter,
                lv_color_t color, lv_opa_t opa);

/**
 * Draw a color map to the display (image)
 * @param cords_p coordinates the color map
 * @param mask_p the map will drawn only on this area  (truncated to VDB area)
 * @param map_p pointer to a lv_color_t array
 * @param opa opacity of the map
 * @param chroma_keyed true: enable transparency of LV_IMG_LV_COLOR_TRANSP color pixels
 * @param alpha_byte true: extra alpha byte is inserted for every pixel
 * @param recolor mix the pixels with this color
 * @param recolor_opa the intense of recoloring
 */
void lv_vmap(const lv_area_t * cords_p, const lv_area_t * mask_p,
             const uint8_t * map_p, lv_opa_t opa, bool chroma_key, bool alpha_byte,
             lv_color_t recolor, lv_opa_t recolor_opa);

/**********************
 *      MACROS
 **********************/

#endif  /*LV_VDB_SIZE != 0*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /*LV_DRAW_RBASIC_H*/

#endif /* PROS_DISPLAY_LV_DRAW_H */
