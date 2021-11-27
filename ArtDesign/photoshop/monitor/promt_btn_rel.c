#include "lvgl/lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_PROMT_BTN_REL
#define LV_ATTRIBUTE_IMG_PROMT_BTN_REL
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_PROMT_BTN_REL uint8_t promt_btn_rel_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x00, 0x0b, 0x24, 0x7b, 0x49, 0xe4, 0x49, 0xf0, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xec, 0x49, 0xf0, 0x49, 0xe3, 0x24, 0x83, 0x00, 0x1c, 
  0x24, 0x7c, 0x92, 0xd0, 0xdb, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x49, 0xdb, 0x24, 0x93, 
  0x49, 0xeb, 0xdb, 0xff, 0xff, 0xff, 0xb7, 0xff, 0xb7, 0xff, 0xb7, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb7, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xb7, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb7, 0xff, 0xb7, 0xff, 0xdb, 0xff, 0xb7, 0xff, 0x6e, 0xff, 0x25, 0xf4, 
  0x49, 0xf8, 0xb6, 0xff, 0xb7, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x49, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x25, 0xf4, 
  0x49, 0xef, 0x92, 0xff, 0xb7, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb6, 0xff, 0x6e, 0xff, 0x25, 0xef, 
  0x49, 0xec, 0x92, 0xff, 0xb7, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x49, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0x92, 0xff, 0x92, 0xff, 0x49, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x49, 0xff, 0x49, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x49, 0xff, 0x49, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x49, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0x92, 0xff, 0xb7, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0xb6, 0xff, 0xdb, 0xff, 0x92, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x6e, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0xb6, 0xff, 0xdb, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x6e, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0x92, 0xff, 0xb7, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x49, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0x92, 0xff, 0xb6, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x49, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x25, 0xec, 
  0x49, 0xec, 0x92, 0xff, 0xb7, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x25, 0xec, 
  0x49, 0xef, 0xb6, 0xff, 0xdb, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x6e, 0xff, 0x25, 0xef, 
  0x49, 0xf8, 0xb6, 0xff, 0xdb, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x6e, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x6e, 0xff, 0x25, 0xf3, 
  0x49, 0xe8, 0x92, 0xff, 0xb7, 0xff, 0x92, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0x92, 0xff, 0xb6, 0xff, 0xb6, 0xff, 0x92, 0xff, 0x6d, 0xff, 0x25, 0xf4, 
  0x24, 0x84, 0x49, 0xdb, 0x6e, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x49, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6d, 0xff, 0x6e, 0xff, 0x6e, 0xff, 0x6d, 0xff, 0x49, 0xe7, 0x24, 0xa0, 
  0x00, 0x1b, 0x00, 0x8f, 0x25, 0xef, 0x25, 0xef, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xec, 0x25, 0xef, 0x25, 0xeb, 0x24, 0x9c, 0x00, 0x3c, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x00, 0x00, 0x0b, 0xe3, 0x18, 0x7b, 0xe8, 0x41, 0xe4, 0x49, 0x4a, 0xf0, 0x29, 0x4a, 0xec, 0x29, 0x4a, 0xec, 0x49, 0x4a, 0xec, 0x49, 0x4a, 0xec, 0x29, 0x4a, 0xec, 0x29, 0x4a, 0xec, 0x29, 0x4a, 0xec, 0x29, 0x4a, 0xec, 0x49, 0x4a, 0xec, 0x49, 0x4a, 0xec, 0x29, 0x4a, 0xec, 0x29, 0x4a, 0xec, 0x49, 0x4a, 0xf0, 0x08, 0x42, 0xe3, 0xe4, 0x20, 0x83, 0x00, 0x00, 0x1c, 
  0xe4, 0x20, 0x7c, 0xf0, 0x83, 0xd0, 0xd7, 0xbd, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x10, 0x84, 0xff, 0xcf, 0x7b, 0xff, 0x72, 0x94, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x10, 0x84, 0xff, 0x31, 0x8c, 0xff, 0x72, 0x94, 0xff, 0x92, 0x94, 0xff, 0xb2, 0x94, 0xff, 0x71, 0x8c, 0xff, 0x8a, 0x52, 0xdb, 0x82, 0x10, 0x93, 
  0x08, 0x42, 0xeb, 0xd7, 0xbd, 0xff, 0x7e, 0xf7, 0xff, 0x75, 0xad, 0xff, 0x76, 0xb5, 0xff, 0x76, 0xb5, 0xff, 0x92, 0x94, 0xff, 0xef, 0x7b, 0xff, 0x55, 0xad, 0xff, 0x96, 0xb5, 0xff, 0x96, 0xb5, 0xff, 0x76, 0xb5, 0xff, 0x72, 0x94, 0xff, 0xd3, 0x9c, 0xff, 0x55, 0xad, 0xff, 0x96, 0xb5, 0xff, 0x96, 0xb5, 0xff, 0x96, 0xb5, 0xff, 0x6e, 0x73, 0xff, 0x25, 0x29, 0xf4, 
  0x49, 0x4a, 0xf8, 0xb3, 0x9c, 0xff, 0x76, 0xb5, 0xff, 0xf0, 0x83, 0xff, 0x31, 0x8c, 0xff, 0x30, 0x84, 0xff, 0x0c, 0x63, 0xff, 0x69, 0x4a, 0xff, 0x10, 0x84, 0xff, 0x51, 0x8c, 0xff, 0x51, 0x8c, 0xff, 0x30, 0x84, 0xff, 0x0c, 0x63, 0xff, 0x4d, 0x6b, 0xff, 0x10, 0x84, 0xff, 0x51, 0x8c, 0xff, 0x51, 0x8c, 0xff, 0x71, 0x8c, 0xff, 0x0c, 0x63, 0xff, 0x65, 0x29, 0xf4, 
  0x29, 0x4a, 0xef, 0x92, 0x94, 0xff, 0x96, 0xb5, 0xff, 0x31, 0x8c, 0xff, 0x72, 0x94, 0xff, 0x71, 0x8c, 0xff, 0x6d, 0x6b, 0xff, 0xab, 0x5a, 0xff, 0x51, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x71, 0x8c, 0xff, 0x4d, 0x6b, 0xff, 0xae, 0x73, 0xff, 0x51, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x0c, 0x63, 0xff, 0x45, 0x29, 0xef, 
  0x29, 0x4a, 0xec, 0x92, 0x94, 0xff, 0x75, 0xad, 0xff, 0x30, 0x84, 0xff, 0x71, 0x8c, 0xff, 0x71, 0x8c, 0xff, 0x6d, 0x6b, 0xff, 0xab, 0x5a, 0xff, 0x31, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x51, 0x8c, 0xff, 0x4d, 0x6b, 0xff, 0xae, 0x73, 0xff, 0x51, 0x8c, 0xff, 0x72, 0x94, 0xff, 0x72, 0x94, 0xff, 0x92, 0x94, 0xff, 0x0c, 0x63, 0xff, 0x45, 0x29, 0xec, 
  0x49, 0x4a, 0xec, 0x10, 0x84, 0xff, 0x92, 0x94, 0xff, 0x0c, 0x63, 0xff, 0x6d, 0x6b, 0xff, 0x6d, 0x6b, 0xff, 0xcb, 0x5a, 0xff, 0x49, 0x4a, 0xff, 0x4d, 0x6b, 0xff, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xff, 0x6d, 0x6b, 0xff, 0xab, 0x5a, 0xff, 0xeb, 0x5a, 0xff, 0x4d, 0x6b, 0xff, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xff, 0xae, 0x73, 0xff, 0xaa, 0x52, 0xff, 0x45, 0x29, 0xec, 
  0x49, 0x4a, 0xec, 0xcf, 0x7b, 0xff, 0xef, 0x7b, 0xff, 0x69, 0x4a, 0xff, 0xab, 0x5a, 0xff, 0xab, 0x5a, 0xff, 0x49, 0x4a, 0xff, 0x08, 0x42, 0xff, 0xaa, 0x52, 0xff, 0xcb, 0x5a, 0xff, 0xcb, 0x5a, 0xff, 0xab, 0x5a, 0xff, 0x49, 0x4a, 0xff, 0x6a, 0x52, 0xff, 0xaa, 0x52, 0xff, 0xab, 0x5a, 0xff, 0xab, 0x5a, 0xff, 0xec, 0x62, 0xff, 0x49, 0x4a, 0xff, 0x45, 0x29, 0xec, 
  0x29, 0x4a, 0xec, 0x72, 0x94, 0xff, 0x55, 0xad, 0xff, 0x10, 0x84, 0xff, 0x51, 0x8c, 0xff, 0x31, 0x8c, 0xff, 0x4d, 0x6b, 0xff, 0xaa, 0x52, 0xff, 0x10, 0x84, 0xff, 0x51, 0x8c, 0xff, 0x51, 0x8c, 0xff, 0x31, 0x8c, 0xff, 0x2d, 0x6b, 0xff, 0x8e, 0x73, 0xff, 0x10, 0x84, 0xff, 0x51, 0x8c, 0xff, 0x51, 0x8c, 0xff, 0x71, 0x8c, 0xff, 0x0c, 0x63, 0xff, 0x45, 0x29, 0xec, 
  0x29, 0x4a, 0xec, 0x92, 0x94, 0xff, 0x96, 0xb5, 0xff, 0x51, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x6e, 0x73, 0xff, 0xcb, 0x5a, 0xff, 0x51, 0x8c, 0xff, 0xb2, 0x94, 0xff, 0xb2, 0x94, 0xff, 0x92, 0x94, 0xff, 0x6d, 0x6b, 0xff, 0xaf, 0x7b, 0xff, 0x71, 0x8c, 0xff, 0x92, 0x94, 0xff, 0xb2, 0x94, 0xff, 0xb2, 0x94, 0xff, 0x2c, 0x63, 0xff, 0x45, 0x29, 0xec, 
  0x29, 0x4a, 0xec, 0x92, 0x94, 0xff, 0x96, 0xb5, 0xff, 0x51, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x6e, 0x73, 0xff, 0xcb, 0x5a, 0xff, 0x51, 0x8c, 0xff, 0xb2, 0x94, 0xff, 0xb2, 0x94, 0xff, 0x92, 0x94, 0xff, 0x6d, 0x6b, 0xff, 0xaf, 0x7b, 0xff, 0x71, 0x8c, 0xff, 0x92, 0x94, 0xff, 0xb2, 0x94, 0xff, 0xb2, 0x94, 0xff, 0x2c, 0x63, 0xff, 0x45, 0x29, 0xec, 
  0x29, 0x4a, 0xec, 0x92, 0x94, 0xff, 0x76, 0xb5, 0xff, 0x30, 0x84, 0xff, 0x71, 0x8c, 0xff, 0x51, 0x8c, 0xff, 0x6d, 0x6b, 0xff, 0xab, 0x5a, 0xff, 0x31, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x51, 0x8c, 0xff, 0x4d, 0x6b, 0xff, 0x8e, 0x73, 0xff, 0x51, 0x8c, 0xff, 0x72, 0x94, 0xff, 0x72, 0x94, 0xff, 0x92, 0x94, 0xff, 0x0c, 0x63, 0xff, 0x45, 0x29, 0xec, 
  0x49, 0x4a, 0xec, 0x10, 0x84, 0xff, 0x72, 0x94, 0xff, 0x0c, 0x63, 0xff, 0x4d, 0x6b, 0xff, 0x4d, 0x6b, 0xff, 0xab, 0x5a, 0xff, 0x49, 0x4a, 0xff, 0x2d, 0x6b, 0xff, 0x6d, 0x6b, 0xff, 0x6d, 0x6b, 0xff, 0x4d, 0x6b, 0xff, 0xab, 0x5a, 0xff, 0xeb, 0x5a, 0xff, 0x4d, 0x6b, 0xff, 0x6d, 0x6b, 0xff, 0x4d, 0x6b, 0xff, 0x8e, 0x73, 0xff, 0xaa, 0x52, 0xff, 0x45, 0x29, 0xec, 
  0x49, 0x4a, 0xec, 0x31, 0x8c, 0xff, 0xd3, 0x9c, 0xff, 0x4d, 0x6b, 0xff, 0xae, 0x73, 0xff, 0xae, 0x73, 0xff, 0xeb, 0x5a, 0xff, 0x6a, 0x52, 0xff, 0x8e, 0x73, 0xff, 0xaf, 0x7b, 0xff, 0xaf, 0x7b, 0xff, 0x8e, 0x73, 0xff, 0xeb, 0x5a, 0xff, 0x0c, 0x63, 0xff, 0x8e, 0x73, 0xff, 0xaf, 0x7b, 0xff, 0xae, 0x73, 0xff, 0xcf, 0x7b, 0xff, 0xcb, 0x5a, 0xff, 0x45, 0x29, 0xec, 
  0x29, 0x4a, 0xec, 0x72, 0x94, 0xff, 0x55, 0xad, 0xff, 0x10, 0x84, 0xff, 0x51, 0x8c, 0xff, 0x51, 0x8c, 0xff, 0x4d, 0x6b, 0xff, 0xaa, 0x52, 0xff, 0x10, 0x84, 0xff, 0x71, 0x8c, 0xff, 0x71, 0x8c, 0xff, 0x51, 0x8c, 0xff, 0x4d, 0x6b, 0xff, 0x8e, 0x73, 0xff, 0x30, 0x84, 0xff, 0x51, 0x8c, 0xff, 0x51, 0x8c, 0xff, 0x72, 0x94, 0xff, 0x0c, 0x63, 0xff, 0x45, 0x29, 0xec, 
  0x29, 0x4a, 0xef, 0x92, 0x94, 0xff, 0x96, 0xb5, 0xff, 0x51, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x72, 0x94, 0xff, 0x6e, 0x73, 0xff, 0xab, 0x5a, 0xff, 0x51, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0x72, 0x94, 0xff, 0x6d, 0x6b, 0xff, 0xaf, 0x7b, 0xff, 0x51, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0xb2, 0x94, 0xff, 0x0c, 0x63, 0xff, 0x45, 0x29, 0xef, 
  0x49, 0x4a, 0xf8, 0xd3, 0x9c, 0xff, 0xb6, 0xb5, 0xff, 0x31, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x72, 0x94, 0xff, 0x6e, 0x73, 0xff, 0xab, 0x5a, 0xff, 0x51, 0x8c, 0xff, 0xb2, 0x94, 0xff, 0xb2, 0x94, 0xff, 0x72, 0x94, 0xff, 0x4d, 0x6b, 0xff, 0xae, 0x73, 0xff, 0x51, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0xb3, 0x9c, 0xff, 0x2d, 0x6b, 0xff, 0x65, 0x29, 0xf3, 
  0x08, 0x42, 0xe8, 0x72, 0x94, 0xff, 0x96, 0xb5, 0xff, 0x71, 0x8c, 0xff, 0x92, 0x94, 0xff, 0x92, 0x94, 0xff, 0xae, 0x73, 0xff, 0xec, 0x62, 0xff, 0x71, 0x8c, 0xff, 0xb2, 0x94, 0xff, 0xb2, 0x94, 0xff, 0x92, 0x94, 0xff, 0x8e, 0x73, 0xff, 0xcf, 0x7b, 0xff, 0x72, 0x94, 0xff, 0xb2, 0x94, 0xff, 0xb3, 0x9c, 0xff, 0x72, 0x94, 0xff, 0xcb, 0x5a, 0xff, 0x25, 0x29, 0xf4, 
  0x04, 0x21, 0x84, 0x6a, 0x52, 0xdb, 0x6e, 0x73, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0xaa, 0x52, 0xff, 0x49, 0x4a, 0xff, 0x0c, 0x63, 0xff, 0x2c, 0x63, 0xff, 0x2c, 0x63, 0xff, 0x0c, 0x63, 0xff, 0xaa, 0x52, 0xff, 0xab, 0x5a, 0xff, 0x0c, 0x63, 0xff, 0x2c, 0x63, 0xff, 0x2d, 0x6b, 0xff, 0xcb, 0x5a, 0xff, 0xa6, 0x31, 0xe7, 0x82, 0x10, 0xa0, 
  0x00, 0x00, 0x1b, 0x82, 0x10, 0x8f, 0x24, 0x21, 0xef, 0x65, 0x29, 0xef, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x45, 0x29, 0xec, 0x65, 0x29, 0xef, 0x25, 0x29, 0xeb, 0x82, 0x10, 0x9c, 0x00, 0x00, 0x3c, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x00, 0x00, 0x0b, 0x18, 0xe3, 0x7b, 0x41, 0xe8, 0xe4, 0x4a, 0x49, 0xf0, 0x4a, 0x29, 0xec, 0x4a, 0x29, 0xec, 0x4a, 0x49, 0xec, 0x4a, 0x49, 0xec, 0x4a, 0x29, 0xec, 0x4a, 0x29, 0xec, 0x4a, 0x29, 0xec, 0x4a, 0x29, 0xec, 0x4a, 0x49, 0xec, 0x4a, 0x49, 0xec, 0x4a, 0x29, 0xec, 0x4a, 0x29, 0xec, 0x4a, 0x49, 0xf0, 0x42, 0x08, 0xe3, 0x20, 0xe4, 0x83, 0x00, 0x00, 0x1c, 
  0x20, 0xe4, 0x7c, 0x83, 0xf0, 0xd0, 0xbd, 0xd7, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x84, 0x10, 0xff, 0x7b, 0xcf, 0xff, 0x94, 0x72, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x84, 0x10, 0xff, 0x8c, 0x31, 0xff, 0x94, 0x72, 0xff, 0x94, 0x92, 0xff, 0x94, 0xb2, 0xff, 0x8c, 0x71, 0xff, 0x52, 0x8a, 0xdb, 0x10, 0x82, 0x93, 
  0x42, 0x08, 0xeb, 0xbd, 0xd7, 0xff, 0xf7, 0x7e, 0xff, 0xad, 0x75, 0xff, 0xb5, 0x76, 0xff, 0xb5, 0x76, 0xff, 0x94, 0x92, 0xff, 0x7b, 0xef, 0xff, 0xad, 0x55, 0xff, 0xb5, 0x96, 0xff, 0xb5, 0x96, 0xff, 0xb5, 0x76, 0xff, 0x94, 0x72, 0xff, 0x9c, 0xd3, 0xff, 0xad, 0x55, 0xff, 0xb5, 0x96, 0xff, 0xb5, 0x96, 0xff, 0xb5, 0x96, 0xff, 0x73, 0x6e, 0xff, 0x29, 0x25, 0xf4, 
  0x4a, 0x49, 0xf8, 0x9c, 0xb3, 0xff, 0xb5, 0x76, 0xff, 0x83, 0xf0, 0xff, 0x8c, 0x31, 0xff, 0x84, 0x30, 0xff, 0x63, 0x0c, 0xff, 0x4a, 0x69, 0xff, 0x84, 0x10, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x51, 0xff, 0x84, 0x30, 0xff, 0x63, 0x0c, 0xff, 0x6b, 0x4d, 0xff, 0x84, 0x10, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x71, 0xff, 0x63, 0x0c, 0xff, 0x29, 0x65, 0xf4, 
  0x4a, 0x29, 0xef, 0x94, 0x92, 0xff, 0xb5, 0x96, 0xff, 0x8c, 0x31, 0xff, 0x94, 0x72, 0xff, 0x8c, 0x71, 0xff, 0x6b, 0x6d, 0xff, 0x5a, 0xab, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x8c, 0x71, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0xae, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x63, 0x0c, 0xff, 0x29, 0x45, 0xef, 
  0x4a, 0x29, 0xec, 0x94, 0x92, 0xff, 0xad, 0x75, 0xff, 0x84, 0x30, 0xff, 0x8c, 0x71, 0xff, 0x8c, 0x71, 0xff, 0x6b, 0x6d, 0xff, 0x5a, 0xab, 0xff, 0x8c, 0x31, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x8c, 0x51, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0xae, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x72, 0xff, 0x94, 0x72, 0xff, 0x94, 0x92, 0xff, 0x63, 0x0c, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x49, 0xec, 0x84, 0x10, 0xff, 0x94, 0x92, 0xff, 0x63, 0x0c, 0xff, 0x6b, 0x6d, 0xff, 0x6b, 0x6d, 0xff, 0x5a, 0xcb, 0xff, 0x4a, 0x49, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xff, 0x6b, 0x6d, 0xff, 0x5a, 0xab, 0xff, 0x5a, 0xeb, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xff, 0x73, 0xae, 0xff, 0x52, 0xaa, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x49, 0xec, 0x7b, 0xcf, 0xff, 0x7b, 0xef, 0xff, 0x4a, 0x69, 0xff, 0x5a, 0xab, 0xff, 0x5a, 0xab, 0xff, 0x4a, 0x49, 0xff, 0x42, 0x08, 0xff, 0x52, 0xaa, 0xff, 0x5a, 0xcb, 0xff, 0x5a, 0xcb, 0xff, 0x5a, 0xab, 0xff, 0x4a, 0x49, 0xff, 0x52, 0x6a, 0xff, 0x52, 0xaa, 0xff, 0x5a, 0xab, 0xff, 0x5a, 0xab, 0xff, 0x62, 0xec, 0xff, 0x4a, 0x49, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x29, 0xec, 0x94, 0x72, 0xff, 0xad, 0x55, 0xff, 0x84, 0x10, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x31, 0xff, 0x6b, 0x4d, 0xff, 0x52, 0xaa, 0xff, 0x84, 0x10, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x31, 0xff, 0x6b, 0x2d, 0xff, 0x73, 0x8e, 0xff, 0x84, 0x10, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x71, 0xff, 0x63, 0x0c, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x29, 0xec, 0x94, 0x92, 0xff, 0xb5, 0x96, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x73, 0x6e, 0xff, 0x5a, 0xcb, 0xff, 0x8c, 0x51, 0xff, 0x94, 0xb2, 0xff, 0x94, 0xb2, 0xff, 0x94, 0x92, 0xff, 0x6b, 0x6d, 0xff, 0x7b, 0xaf, 0xff, 0x8c, 0x71, 0xff, 0x94, 0x92, 0xff, 0x94, 0xb2, 0xff, 0x94, 0xb2, 0xff, 0x63, 0x2c, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x29, 0xec, 0x94, 0x92, 0xff, 0xb5, 0x96, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x73, 0x6e, 0xff, 0x5a, 0xcb, 0xff, 0x8c, 0x51, 0xff, 0x94, 0xb2, 0xff, 0x94, 0xb2, 0xff, 0x94, 0x92, 0xff, 0x6b, 0x6d, 0xff, 0x7b, 0xaf, 0xff, 0x8c, 0x71, 0xff, 0x94, 0x92, 0xff, 0x94, 0xb2, 0xff, 0x94, 0xb2, 0xff, 0x63, 0x2c, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x29, 0xec, 0x94, 0x92, 0xff, 0xb5, 0x76, 0xff, 0x84, 0x30, 0xff, 0x8c, 0x71, 0xff, 0x8c, 0x51, 0xff, 0x6b, 0x6d, 0xff, 0x5a, 0xab, 0xff, 0x8c, 0x31, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x8c, 0x51, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0x8e, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x72, 0xff, 0x94, 0x72, 0xff, 0x94, 0x92, 0xff, 0x63, 0x0c, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x49, 0xec, 0x84, 0x10, 0xff, 0x94, 0x72, 0xff, 0x63, 0x0c, 0xff, 0x6b, 0x4d, 0xff, 0x6b, 0x4d, 0xff, 0x5a, 0xab, 0xff, 0x4a, 0x49, 0xff, 0x6b, 0x2d, 0xff, 0x6b, 0x6d, 0xff, 0x6b, 0x6d, 0xff, 0x6b, 0x4d, 0xff, 0x5a, 0xab, 0xff, 0x5a, 0xeb, 0xff, 0x6b, 0x4d, 0xff, 0x6b, 0x6d, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0x8e, 0xff, 0x52, 0xaa, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x49, 0xec, 0x8c, 0x31, 0xff, 0x9c, 0xd3, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0xae, 0xff, 0x73, 0xae, 0xff, 0x5a, 0xeb, 0xff, 0x52, 0x6a, 0xff, 0x73, 0x8e, 0xff, 0x7b, 0xaf, 0xff, 0x7b, 0xaf, 0xff, 0x73, 0x8e, 0xff, 0x5a, 0xeb, 0xff, 0x63, 0x0c, 0xff, 0x73, 0x8e, 0xff, 0x7b, 0xaf, 0xff, 0x73, 0xae, 0xff, 0x7b, 0xcf, 0xff, 0x5a, 0xcb, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x29, 0xec, 0x94, 0x72, 0xff, 0xad, 0x55, 0xff, 0x84, 0x10, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x51, 0xff, 0x6b, 0x4d, 0xff, 0x52, 0xaa, 0xff, 0x84, 0x10, 0xff, 0x8c, 0x71, 0xff, 0x8c, 0x71, 0xff, 0x8c, 0x51, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0x8e, 0xff, 0x84, 0x30, 0xff, 0x8c, 0x51, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x72, 0xff, 0x63, 0x0c, 0xff, 0x29, 0x45, 0xec, 
  0x4a, 0x29, 0xef, 0x94, 0x92, 0xff, 0xb5, 0x96, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x92, 0xff, 0x94, 0x72, 0xff, 0x73, 0x6e, 0xff, 0x5a, 0xab, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x94, 0x72, 0xff, 0x6b, 0x6d, 0xff, 0x7b, 0xaf, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x94, 0xb2, 0xff, 0x63, 0x0c, 0xff, 0x29, 0x45, 0xef, 
  0x4a, 0x49, 0xf8, 0x9c, 0xd3, 0xff, 0xb5, 0xb6, 0xff, 0x8c, 0x31, 0xff, 0x94, 0x92, 0xff, 0x94, 0x72, 0xff, 0x73, 0x6e, 0xff, 0x5a, 0xab, 0xff, 0x8c, 0x51, 0xff, 0x94, 0xb2, 0xff, 0x94, 0xb2, 0xff, 0x94, 0x72, 0xff, 0x6b, 0x4d, 0xff, 0x73, 0xae, 0xff, 0x8c, 0x51, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x9c, 0xb3, 0xff, 0x6b, 0x2d, 0xff, 0x29, 0x65, 0xf3, 
  0x42, 0x08, 0xe8, 0x94, 0x72, 0xff, 0xb5, 0x96, 0xff, 0x8c, 0x71, 0xff, 0x94, 0x92, 0xff, 0x94, 0x92, 0xff, 0x73, 0xae, 0xff, 0x62, 0xec, 0xff, 0x8c, 0x71, 0xff, 0x94, 0xb2, 0xff, 0x94, 0xb2, 0xff, 0x94, 0x92, 0xff, 0x73, 0x8e, 0xff, 0x7b, 0xcf, 0xff, 0x94, 0x72, 0xff, 0x94, 0xb2, 0xff, 0x9c, 0xb3, 0xff, 0x94, 0x72, 0xff, 0x5a, 0xcb, 0xff, 0x29, 0x25, 0xf4, 
  0x21, 0x04, 0x84, 0x52, 0x6a, 0xdb, 0x73, 0x6e, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x0c, 0xff, 0x52, 0xaa, 0xff, 0x4a, 0x49, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x2c, 0xff, 0x63, 0x2c, 0xff, 0x63, 0x0c, 0xff, 0x52, 0xaa, 0xff, 0x5a, 0xab, 0xff, 0x63, 0x0c, 0xff, 0x63, 0x2c, 0xff, 0x6b, 0x2d, 0xff, 0x5a, 0xcb, 0xff, 0x31, 0xa6, 0xe7, 0x10, 0x82, 0xa0, 
  0x00, 0x00, 0x1b, 0x10, 0x82, 0x8f, 0x21, 0x24, 0xef, 0x29, 0x65, 0xef, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x45, 0xec, 0x29, 0x65, 0xef, 0x29, 0x25, 0xeb, 0x10, 0x82, 0x9c, 0x00, 0x00, 0x3c, 
#endif
#if LV_COLOR_DEPTH == 32
  0x00, 0x00, 0x00, 0x0b, 0x1c, 0x1c, 0x1c, 0x7b, 0x3d, 0x3d, 0x3d, 0xe4, 0x48, 0x48, 0x48, 0xf0, 0x46, 0x46, 0x46, 0xec, 0x46, 0x46, 0x46, 0xec, 0x47, 0x47, 0x47, 0xec, 0x48, 0x48, 0x48, 0xec, 0x46, 0x46, 0x46, 0xec, 0x46, 0x46, 0x46, 0xec, 0x46, 0x46, 0x46, 0xec, 0x46, 0x46, 0x46, 0xec, 0x47, 0x47, 0x47, 0xec, 0x47, 0x47, 0x47, 0xec, 0x46, 0x46, 0x46, 0xec, 0x46, 0x46, 0x46, 0xec, 0x47, 0x47, 0x47, 0xf0, 0x3f, 0x3f, 0x3f, 0xe3, 0x1e, 0x1e, 0x1e, 0x83, 0x00, 0x00, 0x00, 0x1c, 
  0x1e, 0x1e, 0x1e, 0x7c, 0x7e, 0x7e, 0x7e, 0xd0, 0xb7, 0xb7, 0xb7, 0xff, 0x92, 0x92, 0x92, 0xff, 0x90, 0x90, 0x90, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x82, 0x82, 0x82, 0xff, 0x79, 0x79, 0x79, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x92, 0x92, 0x92, 0xff, 0x92, 0x92, 0x92, 0xff, 0x90, 0x90, 0x90, 0xff, 0x82, 0x82, 0x82, 0xff, 0x86, 0x86, 0x86, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x91, 0x91, 0x91, 0xff, 0x93, 0x93, 0x93, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0x4f, 0x4f, 0x4f, 0xdb, 0x12, 0x12, 0x12, 0x93, 
  0x40, 0x40, 0x40, 0xeb, 0xb9, 0xb9, 0xb9, 0xff, 0xee, 0xee, 0xee, 0xff, 0xac, 0xac, 0xac, 0xff, 0xae, 0xae, 0xae, 0xff, 0xad, 0xad, 0xad, 0xff, 0x90, 0x90, 0x90, 0xff, 0x7b, 0x7b, 0x7b, 0xff, 0xa9, 0xa9, 0xa9, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0xad, 0xad, 0xad, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x97, 0x97, 0x97, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xb0, 0xb0, 0xb0, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0xaf, 0xaf, 0xaf, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x26, 0x26, 0x26, 0xf4, 
  0x4a, 0x4a, 0x4a, 0xf8, 0x95, 0x95, 0x95, 0xff, 0xae, 0xae, 0xae, 0xff, 0x7d, 0x7d, 0x7d, 0xff, 0x85, 0x85, 0x85, 0xff, 0x84, 0x84, 0x84, 0xff, 0x62, 0x62, 0x62, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0x88, 0x88, 0x88, 0xff, 0x88, 0x88, 0x88, 0xff, 0x84, 0x84, 0x84, 0xff, 0x60, 0x60, 0x60, 0xff, 0x6a, 0x6a, 0x6a, 0xff, 0x80, 0x80, 0x80, 0xff, 0x87, 0x87, 0x87, 0xff, 0x87, 0x87, 0x87, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0x60, 0x60, 0x60, 0xff, 0x2b, 0x2b, 0x2b, 0xf4, 
  0x46, 0x46, 0x46, 0xef, 0x90, 0x90, 0x90, 0xff, 0xaf, 0xaf, 0xaf, 0xff, 0x85, 0x85, 0x85, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0x6c, 0x6c, 0x6c, 0xff, 0x55, 0x55, 0x55, 0xff, 0x87, 0x87, 0x87, 0xff, 0x91, 0x91, 0x91, 0xff, 0x90, 0x90, 0x90, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0x6a, 0x6a, 0x6a, 0xff, 0x73, 0x73, 0x73, 0xff, 0x88, 0x88, 0x88, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x90, 0x90, 0x90, 0xff, 0x92, 0x92, 0x92, 0xff, 0x62, 0x62, 0x62, 0xff, 0x29, 0x29, 0x29, 0xef, 
  0x46, 0x46, 0x46, 0xec, 0x8f, 0x8f, 0x8f, 0xff, 0xac, 0xac, 0xac, 0xff, 0x84, 0x84, 0x84, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x56, 0x56, 0x56, 0xff, 0x86, 0x86, 0x86, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x69, 0x69, 0x69, 0xff, 0x73, 0x73, 0x73, 0xff, 0x87, 0x87, 0x87, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x90, 0x90, 0x90, 0xff, 0x61, 0x61, 0x61, 0xff, 0x28, 0x28, 0x28, 0xec, 
  0x47, 0x47, 0x47, 0xec, 0x82, 0x82, 0x82, 0xff, 0x90, 0x90, 0x90, 0xff, 0x62, 0x62, 0x62, 0xff, 0x6c, 0x6c, 0x6c, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x58, 0x58, 0x58, 0xff, 0x4a, 0x4a, 0x4a, 0xff, 0x68, 0x68, 0x68, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x56, 0x56, 0x56, 0xff, 0x5c, 0x5c, 0x5c, 0xff, 0x69, 0x69, 0x69, 0xff, 0x6d, 0x6d, 0x6d, 0xff, 0x6d, 0x6d, 0x6d, 0xff, 0x73, 0x73, 0x73, 0xff, 0x53, 0x53, 0x53, 0xff, 0x2a, 0x2a, 0x2a, 0xec, 
  0x48, 0x48, 0x48, 0xec, 0x79, 0x79, 0x79, 0xff, 0x7b, 0x7b, 0x7b, 0xff, 0x4b, 0x4b, 0x4b, 0xff, 0x55, 0x55, 0x55, 0xff, 0x56, 0x56, 0x56, 0xff, 0x4a, 0x4a, 0x4a, 0xff, 0x42, 0x42, 0x42, 0xff, 0x54, 0x54, 0x54, 0xff, 0x57, 0x57, 0x57, 0xff, 0x57, 0x57, 0x57, 0xff, 0x55, 0x55, 0x55, 0xff, 0x49, 0x49, 0x49, 0xff, 0x4d, 0x4d, 0x4d, 0xff, 0x54, 0x54, 0x54, 0xff, 0x56, 0x56, 0x56, 0xff, 0x55, 0x55, 0x55, 0xff, 0x5e, 0x5e, 0x5e, 0xff, 0x4a, 0x4a, 0x4a, 0xff, 0x2a, 0x2a, 0x2a, 0xec, 
  0x46, 0x46, 0x46, 0xec, 0x8e, 0x8e, 0x8e, 0xff, 0xa9, 0xa9, 0xa9, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0x87, 0x87, 0x87, 0xff, 0x86, 0x86, 0x86, 0xff, 0x68, 0x68, 0x68, 0xff, 0x54, 0x54, 0x54, 0xff, 0x81, 0x81, 0x81, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x86, 0x86, 0x86, 0xff, 0x66, 0x66, 0x66, 0xff, 0x6f, 0x6f, 0x6f, 0xff, 0x82, 0x82, 0x82, 0xff, 0x89, 0x89, 0x89, 0xff, 0x89, 0x89, 0x89, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0x5f, 0x5f, 0x5f, 0xff, 0x29, 0x29, 0x29, 0xec, 
  0x46, 0x46, 0x46, 0xec, 0x92, 0x92, 0x92, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0x88, 0x88, 0x88, 0xff, 0x91, 0x91, 0x91, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x57, 0x57, 0x57, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x93, 0x93, 0x93, 0xff, 0x93, 0x93, 0x93, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x6c, 0x6c, 0x6c, 0xff, 0x76, 0x76, 0x76, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0x92, 0x92, 0x92, 0xff, 0x93, 0x93, 0x93, 0xff, 0x94, 0x94, 0x94, 0xff, 0x63, 0x63, 0x63, 0xff, 0x28, 0x28, 0x28, 0xec, 
  0x46, 0x46, 0x46, 0xec, 0x92, 0x92, 0x92, 0xff, 0xb2, 0xb2, 0xb2, 0xff, 0x88, 0x88, 0x88, 0xff, 0x90, 0x90, 0x90, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x57, 0x57, 0x57, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x93, 0x93, 0x93, 0xff, 0x93, 0x93, 0x93, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x6c, 0x6c, 0x6c, 0xff, 0x76, 0x76, 0x76, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0x92, 0x92, 0x92, 0xff, 0x93, 0x93, 0x93, 0xff, 0x94, 0x94, 0x94, 0xff, 0x63, 0x63, 0x63, 0xff, 0x28, 0x28, 0x28, 0xec, 
  0x46, 0x46, 0x46, 0xec, 0x90, 0x90, 0x90, 0xff, 0xad, 0xad, 0xad, 0xff, 0x84, 0x84, 0x84, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x55, 0x55, 0x55, 0xff, 0x86, 0x86, 0x86, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x69, 0x69, 0x69, 0xff, 0x72, 0x72, 0x72, 0xff, 0x87, 0x87, 0x87, 0xff, 0x8d, 0x8d, 0x8d, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x90, 0x90, 0x90, 0xff, 0x61, 0x61, 0x61, 0xff, 0x29, 0x29, 0x29, 0xec, 
  0x47, 0x47, 0x47, 0xec, 0x82, 0x82, 0x82, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x60, 0x60, 0x60, 0xff, 0x6a, 0x6a, 0x6a, 0xff, 0x6a, 0x6a, 0x6a, 0xff, 0x56, 0x56, 0x56, 0xff, 0x49, 0x49, 0x49, 0xff, 0x66, 0x66, 0x66, 0xff, 0x6c, 0x6c, 0x6c, 0xff, 0x6c, 0x6c, 0x6c, 0xff, 0x69, 0x69, 0x69, 0xff, 0x55, 0x55, 0x55, 0xff, 0x5b, 0x5b, 0x5b, 0xff, 0x67, 0x67, 0x67, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6a, 0x6a, 0x6a, 0xff, 0x71, 0x71, 0x71, 0xff, 0x53, 0x53, 0x53, 0xff, 0x2a, 0x2a, 0x2a, 0xec, 
  0x47, 0x47, 0x47, 0xec, 0x86, 0x86, 0x86, 0xff, 0x97, 0x97, 0x97, 0xff, 0x6a, 0x6a, 0x6a, 0xff, 0x73, 0x73, 0x73, 0xff, 0x73, 0x73, 0x73, 0xff, 0x5c, 0x5c, 0x5c, 0xff, 0x4d, 0x4d, 0x4d, 0xff, 0x6f, 0x6f, 0x6f, 0xff, 0x76, 0x76, 0x76, 0xff, 0x76, 0x76, 0x76, 0xff, 0x72, 0x72, 0x72, 0xff, 0x5b, 0x5b, 0x5b, 0xff, 0x61, 0x61, 0x61, 0xff, 0x70, 0x70, 0x70, 0xff, 0x75, 0x75, 0x75, 0xff, 0x74, 0x74, 0x74, 0xff, 0x7a, 0x7a, 0x7a, 0xff, 0x57, 0x57, 0x57, 0xff, 0x29, 0x29, 0x29, 0xec, 
  0x46, 0x46, 0x46, 0xec, 0x8e, 0x8e, 0x8e, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0x80, 0x80, 0x80, 0xff, 0x88, 0x88, 0x88, 0xff, 0x87, 0x87, 0x87, 0xff, 0x69, 0x69, 0x69, 0xff, 0x54, 0x54, 0x54, 0xff, 0x82, 0x82, 0x82, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0x87, 0x87, 0x87, 0xff, 0x67, 0x67, 0x67, 0xff, 0x70, 0x70, 0x70, 0xff, 0x83, 0x83, 0x83, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x8d, 0x8d, 0x8d, 0xff, 0x5f, 0x5f, 0x5f, 0xff, 0x29, 0x29, 0x29, 0xec, 
  0x46, 0x46, 0x46, 0xef, 0x92, 0x92, 0x92, 0xff, 0xb1, 0xb1, 0xb1, 0xff, 0x87, 0x87, 0x87, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x6d, 0x6d, 0x6d, 0xff, 0x56, 0x56, 0x56, 0xff, 0x89, 0x89, 0x89, 0xff, 0x92, 0x92, 0x92, 0xff, 0x92, 0x92, 0x92, 0xff, 0x8d, 0x8d, 0x8d, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x75, 0x75, 0x75, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x91, 0x91, 0x91, 0xff, 0x91, 0x91, 0x91, 0xff, 0x93, 0x93, 0x93, 0xff, 0x62, 0x62, 0x62, 0xff, 0x29, 0x29, 0x29, 0xef, 
  0x4a, 0x4a, 0x4a, 0xf8, 0x97, 0x97, 0x97, 0xff, 0xb4, 0xb4, 0xb4, 0xff, 0x86, 0x86, 0x86, 0xff, 0x90, 0x90, 0x90, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x6d, 0x6d, 0x6d, 0xff, 0x55, 0x55, 0x55, 0xff, 0x89, 0x89, 0x89, 0xff, 0x93, 0x93, 0x93, 0xff, 0x93, 0x93, 0x93, 0xff, 0x8e, 0x8e, 0x8e, 0xff, 0x6a, 0x6a, 0x6a, 0xff, 0x74, 0x74, 0x74, 0xff, 0x8a, 0x8a, 0x8a, 0xff, 0x91, 0x91, 0x91, 0xff, 0x92, 0x92, 0x92, 0xff, 0x95, 0x95, 0x95, 0xff, 0x65, 0x65, 0x65, 0xff, 0x2b, 0x2b, 0x2b, 0xf3, 
  0x42, 0x42, 0x42, 0xe8, 0x8d, 0x8d, 0x8d, 0xff, 0xb0, 0xb0, 0xb0, 0xff, 0x8b, 0x8b, 0x8b, 0xff, 0x92, 0x92, 0x92, 0xff, 0x90, 0x90, 0x90, 0xff, 0x73, 0x73, 0x73, 0xff, 0x5e, 0x5e, 0x5e, 0xff, 0x8c, 0x8c, 0x8c, 0xff, 0x94, 0x94, 0x94, 0xff, 0x94, 0x94, 0x94, 0xff, 0x90, 0x90, 0x90, 0xff, 0x71, 0x71, 0x71, 0xff, 0x7a, 0x7a, 0x7a, 0xff, 0x8d, 0x8d, 0x8d, 0xff, 0x93, 0x93, 0x93, 0xff, 0x95, 0x95, 0x95, 0xff, 0x8d, 0x8d, 0x8d, 0xff, 0x5a, 0x5a, 0x5a, 0xff, 0x26, 0x26, 0x26, 0xf4, 
  0x1f, 0x1f, 0x1f, 0x84, 0x4e, 0x4e, 0x4e, 0xdb, 0x6d, 0x6d, 0x6d, 0xff, 0x60, 0x60, 0x60, 0xff, 0x62, 0x62, 0x62, 0xff, 0x61, 0x61, 0x61, 0xff, 0x53, 0x53, 0x53, 0xff, 0x4a, 0x4a, 0x4a, 0xff, 0x5f, 0x5f, 0x5f, 0xff, 0x63, 0x63, 0x63, 0xff, 0x63, 0x63, 0x63, 0xff, 0x61, 0x61, 0x61, 0xff, 0x53, 0x53, 0x53, 0xff, 0x56, 0x56, 0x56, 0xff, 0x5f, 0x5f, 0x5f, 0xff, 0x63, 0x63, 0x63, 0xff, 0x65, 0x65, 0x65, 0xff, 0x5a, 0x5a, 0x5a, 0xff, 0x33, 0x33, 0x33, 0xe7, 0x12, 0x12, 0x12, 0xa0, 
  0x00, 0x00, 0x00, 0x1b, 0x10, 0x10, 0x10, 0x8f, 0x24, 0x24, 0x24, 0xef, 0x2c, 0x2c, 0x2c, 0xef, 0x29, 0x29, 0x29, 0xec, 0x28, 0x28, 0x28, 0xec, 0x2a, 0x2a, 0x2a, 0xec, 0x2a, 0x2a, 0x2a, 0xec, 0x29, 0x29, 0x29, 0xec, 0x28, 0x28, 0x28, 0xec, 0x28, 0x28, 0x28, 0xec, 0x29, 0x29, 0x29, 0xec, 0x2a, 0x2a, 0x2a, 0xec, 0x29, 0x29, 0x29, 0xec, 0x29, 0x29, 0x29, 0xec, 0x29, 0x29, 0x29, 0xec, 0x2b, 0x2b, 0x2b, 0xef, 0x25, 0x25, 0x25, 0xeb, 0x11, 0x11, 0x11, 0x9c, 0x00, 0x00, 0x00, 0x3c, 
#endif
};

const lv_img_dsc_t promt_btn_rel = {
  .header.always_zero = 0,
  .header.w = 20,
  .header.h = 20,
  .data_size = 400 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = promt_btn_rel_map,
};
