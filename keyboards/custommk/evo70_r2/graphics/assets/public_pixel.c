/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/


#include "lvgl.h"

#ifndef PUBLIC_PIXEL
#define PUBLIC_PIXEL 1
#endif

#if PUBLIC_PIXEL

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x6f, 0xff, 0x60, 0x60,

    /* U+0022 "\"" */
    0xde, 0xd3, 0x20,

    /* U+0023 "#" */
    0x6d, 0xfd, 0xb3, 0x66, 0xdf, 0xdb, 0x0,

    /* U+0024 "$" */
    0x10, 0xff, 0x43, 0xe1, 0x7f, 0x84, 0x0,

    /* U+0025 "%" */
    0x43, 0x4d, 0x30, 0xc3, 0x4d, 0x71, 0x0,

    /* U+0026 "&" */
    0x71, 0xb1, 0xc6, 0xdc, 0xf8, 0xdf, 0x0,

    /* U+0027 "'" */
    0xf6,

    /* U+0028 "(" */
    0x3b, 0x31, 0x8c, 0x30, 0xe0,

    /* U+0029 ")" */
    0xe1, 0x86, 0x31, 0x9b, 0x80,

    /* U+002A "*" */
    0xdb, 0xb6,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0xf6,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x4, 0x31, 0x8c, 0x63, 0x8, 0x0,

    /* U+0030 "0" */
    0x7d, 0x9f, 0x1e, 0x3c, 0x7c, 0xdf, 0x0,

    /* U+0031 "1" */
    0xf0, 0xc3, 0xc, 0x30, 0xcf, 0xc0,

    /* U+0032 "2" */
    0x7d, 0x8c, 0x31, 0xc6, 0x18, 0x3f, 0x80,

    /* U+0033 "3" */
    0x7d, 0x8c, 0x19, 0xe0, 0x78, 0xdf, 0x0,

    /* U+0034 "4" */
    0x1e, 0x6d, 0x9e, 0x3f, 0xe0, 0xc1, 0x80,

    /* U+0035 "5" */
    0xff, 0x83, 0xf0, 0x30, 0x78, 0xdf, 0x0,

    /* U+0036 "6" */
    0x7d, 0x8f, 0x7, 0xec, 0x78, 0xdf, 0x0,

    /* U+0037 "7" */
    0xff, 0x8c, 0x30, 0xc3, 0xc, 0x30, 0x0,

    /* U+0038 "8" */
    0x7d, 0x8f, 0x1b, 0xec, 0x78, 0xdf, 0x0,

    /* U+0039 "9" */
    0x7d, 0x8f, 0x1b, 0xf0, 0x78, 0xdf, 0x0,

    /* U+003A ":" */
    0xf3, 0xc0,

    /* U+003B ";" */
    0xf3, 0x40,

    /* U+003C "<" */
    0x3b, 0xb8, 0xe3, 0x80,

    /* U+003D "=" */
    0xf8, 0x3e,

    /* U+003E ">" */
    0xe3, 0x8e, 0xee, 0x0,

    /* U+003F "?" */
    0x7d, 0x8c, 0x19, 0xe3, 0x0, 0xc, 0x0,

    /* U+0040 "@" */
    0x7d, 0x8f, 0x5e, 0xbd, 0xd8, 0x1f, 0x0,

    /* U+0041 "A" */
    0x38, 0xdb, 0x1e, 0x3f, 0xf8, 0xf1, 0x80,

    /* U+0042 "B" */
    0xfd, 0x8f, 0x1f, 0xec, 0x78, 0xff, 0x0,

    /* U+0043 "C" */
    0x7d, 0x8f, 0x6, 0xc, 0x18, 0xdf, 0x0,

    /* U+0044 "D" */
    0xf9, 0x9b, 0x1e, 0x3c, 0x79, 0xbe, 0x0,

    /* U+0045 "E" */
    0xff, 0x83, 0x7, 0xcc, 0x18, 0x3f, 0x80,

    /* U+0046 "F" */
    0xff, 0x83, 0x7, 0xcc, 0x18, 0x30, 0x0,

    /* U+0047 "G" */
    0x7f, 0x83, 0x6, 0xfc, 0x78, 0xdf, 0x80,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1f, 0xfc, 0x78, 0xf1, 0x80,

    /* U+0049 "I" */
    //0xfc, 0xc3, 0xc, 0x30, 0xcf, 0xc0,
    0xfe, 0x70, 0xe1, 0xc3, 0x87, 0x3f, 0x80,

    /* U+004A "J" */
    0x1e, 0xc, 0x18, 0x3c, 0x78, 0xdf, 0x0,

    /* U+004B "K" */
    0xc7, 0x9b, 0x67, 0x8d, 0x99, 0xb1, 0x80,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x3f, 0x80,

    /* U+004D "M" */
    0xc7, 0xdf, 0xfe, 0xbc, 0x78, 0xf1, 0x80,

    /* U+004E "N" */
    0xc7, 0xcf, 0xde, 0xfc, 0xf8, 0xf1, 0x80,

    /* U+004F "O" */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x0,

    /* U+0050 "P" */
    0xfd, 0x8f, 0x1f, 0xec, 0x18, 0x30, 0x0,

    /* U+0051 "Q" */
    0x7d, 0x8f, 0x1e, 0x3d, 0xf9, 0x9e, 0x80,

    /* U+0052 "R" */
    0xfd, 0x8f, 0x1f, 0xed, 0x99, 0xb1, 0x80,

    /* U+0053 "S" */
    0x7d, 0x8f, 0x3, 0xe0, 0x78, 0xdf, 0x0,

    /* U+0054 "T" */
    //0xfc, 0xc3, 0xc, 0x30, 0xc3, 0x0,
    0xfe, 0x70, 0xe1, 0xc3, 0x87, 0x0E, 0x0,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x0,

    /* U+0056 "V" */
    0xc7, 0x8f, 0x1e, 0x36, 0xc7, 0x4, 0x0,

    /* U+0057 "W" */
    0xc7, 0x8f, 0x5f, 0xfe, 0xf8, 0xf1, 0x80,

    /* U+0058 "X" */
    0xc7, 0xdd, 0xf1, 0xc7, 0xdd, 0xf1, 0x80,

    /* U+0059 "Y" */
//    0xcf, 0x3c, 0xde, 0x30, 0xc3, 0x0,
    0xc7, 0x8f, 0x1b, 0xe3, 0x87, 0x0e, 0x0,

    /* U+005A "Z" */
    0xfe, 0x1c, 0x71, 0xc7, 0x1c, 0x3f, 0x80,

    /* U+005B "[" */
    0xfe, 0x31, 0x8c, 0x63, 0xe0,

    /* U+005C "\\" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x40,

    /* U+005D "]" */
    0xf8, 0xc6, 0x31, 0x8f, 0xe0,

    /* U+005E "^" */
    0x10, 0x71, 0xb6, 0x30,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
//    0x90,
    0xcc,

    /* U+0061 "a" */
    0x7c, 0xd, 0xfe, 0x37, 0xe0,

    /* U+0062 "b" */
    0xc1, 0x83, 0xf6, 0x3c, 0x78, 0xff, 0x0,

    /* U+0063 "c" */
    0x7d, 0x8f, 0x6, 0x37, 0xc0,

    /* U+0064 "d" */
    0x6, 0xd, 0xfe, 0x3c, 0x78, 0xdf, 0x80,

    /* U+0065 "e" */
    0x7d, 0x8f, 0xfe, 0x7, 0xc0,

    /* U+0066 "f" */
    0x3c, 0x63, 0xf9, 0x83, 0x6, 0xc, 0x0,

    /* U+0067 "g" */
    0x7f, 0x8d, 0xf8, 0x37, 0xc0,

    /* U+0068 "h" */
    0xc1, 0x83, 0xf6, 0x3c, 0x78, 0xf1, 0x80,

    /* U+0069 "i" */
    0x18, 0x1, 0xe0, 0xc1, 0x83, 0x3f, 0x80,

    /* U+006A "j" */
    0x6, 0x0, 0x18, 0x30, 0x78, 0xdf, 0x0,

    /* U+006B "k" */
    0xc1, 0x83, 0x1e, 0x6f, 0x99, 0xb1, 0x80,

    /* U+006C "l" */
    0xc1, 0x83, 0x6, 0xc, 0xe, 0x7, 0x80,

    /* U+006D "m" */
    0xfd, 0xaf, 0x5e, 0xbd, 0x60,

    /* U+006E "n" */
    0xfd, 0x8f, 0x1e, 0x3c, 0x60,

    /* U+006F "o" */
    0x7d, 0x8f, 0x1e, 0x37, 0xc0,

    /* U+0070 "p" */
    0xfd, 0x8f, 0xf6, 0xc, 0x0,

    /* U+0071 "q" */
    0x7f, 0x8d, 0xf8, 0x30, 0x60,

    /* U+0072 "r" */
    0xdd, 0xcf, 0x6, 0xc, 0x0,

    /* U+0073 "s" */
    0x7f, 0x83, 0xf8, 0x3f, 0xc0,

    /* U+0074 "t" */
    0x30, 0x63, 0xf9, 0x83, 0x6, 0xf, 0x80,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x37, 0xc0,

    /* U+0076 "v" */
    0xc7, 0x8d, 0xb1, 0xc1, 0x0,

    /* U+0077 "w" */
    0xc7, 0xaf, 0x5f, 0xf6, 0xc0,

    /* U+0078 "x" */
    0xee, 0xf8, 0xe3, 0xee, 0xe0,

    /* U+0079 "y" */
    0xc7, 0x8d, 0xb1, 0xcf, 0x0,

    /* U+007A "z" */
    0xfe, 0x38, 0xe3, 0x8f, 0xe0,

    /* U+007B "{" */
    0x3b, 0x19, 0xc6, 0x30, 0xe0,

    /* U+007C "|" */
    0xff, 0xfc,

    /* U+007D "}" */
    0xe1, 0x8c, 0x73, 0x1b, 0x80,

    /* U+007E "~" */
    0x77, 0xaf, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0}, // null
    {.bitmap_index = 1, .adv_w = 128, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0}, // !
    {.bitmap_index = 5, .adv_w = 128, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 3}, // "
    {.bitmap_index = 8, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // #
    {.bitmap_index = 15, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // $
    {.bitmap_index = 22, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // %
    {.bitmap_index = 29, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // &
    {.bitmap_index = 36, .adv_w = 128, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = 3}, // '
    {.bitmap_index = 37, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0}, // (
    {.bitmap_index = 42, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0}, // )
    {.bitmap_index = 47, .adv_w = 128, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 4}, // *
    {.bitmap_index = 49, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0}, // +
    {.bitmap_index = 53, .adv_w = 128, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = 0}, // ,
    {.bitmap_index = 54, .adv_w = 128, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 2}, // -
    {.bitmap_index = 55, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 0}, // .
    {.bitmap_index = 56, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // /
    {.bitmap_index = 62, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // 0
    {.bitmap_index = 69, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0}, // 1
    {.bitmap_index = 75, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // 8
    {.bitmap_index = 124, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // 9
    {.bitmap_index = 131, .adv_w = 128, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = 0}, // :
    {.bitmap_index = 133, .adv_w = 128, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = 0}, // ;
    {.bitmap_index = 135, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0}, // <
    {.bitmap_index = 139, .adv_w = 128, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 1}, // =
    {.bitmap_index = 141, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0}, // >
    {.bitmap_index = 145, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // ?
    {.bitmap_index = 152, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // @
    {.bitmap_index = 159, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // A
    {.bitmap_index = 166, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
//    {.bitmap_index = 215, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0}, // I
    {.bitmap_index = 215, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // I
    {.bitmap_index = 222, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
//    {.bitmap_index = 292, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0}, //T
    {.bitmap_index = 292, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, //T
    {.bitmap_index = 299, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
//    {.bitmap_index = 327, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0}, // Y
    {.bitmap_index = 327, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // Y
    {.bitmap_index = 334, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}, // Z
    {.bitmap_index = 341, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 361, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 0}, // _
    {.bitmap_index = 362, .adv_w = 128, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 363, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0}, // a
    {.bitmap_index = 368, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0}, // m
    {.bitmap_index = 444, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 128, .box_w = 2, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t public_pixel = {
#else
lv_font_t public_pixel = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 7,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if PUBLIC_PIXEL*/

