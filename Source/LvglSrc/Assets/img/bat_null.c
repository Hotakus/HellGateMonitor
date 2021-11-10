#include "lvgl/lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_BAT_NULL
#define LV_ATTRIBUTE_IMG_BAT_NULL
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_BAT_NULL uint8_t bat_null_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x6e, 0x00, 0x6e, 0x00, 0x6e, 0x0c, 0x6e, 0x93, 0x6e, 0xe3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xe0, 0x6e, 0x93, 0x6e, 0x0c, 
  0x6e, 0x00, 0x6e, 0x00, 0x6e, 0xa0, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xf3, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xec, 0x6e, 0xef, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0x9b, 
  0x6e, 0x00, 0x6e, 0x0f, 0x6e, 0xf7, 0x6e, 0xef, 0x6e, 0x33, 0x6e, 0x13, 0x6e, 0x13, 0x6e, 0x13, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x72, 0x24, 0x76, 0x30, 0x76, 0x2f, 0x72, 0x28, 0x6e, 0xf0, 0x6e, 0xef, 
  0x6e, 0x0f, 0x6e, 0x3f, 0x6e, 0xfc, 0x6e, 0xdb, 0x6e, 0x00, 0x6e, 0x00, 0x6e, 0x00, 0x72, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x10, 0xae, 0x08, 0xae, 0x00, 0x92, 0x18, 0x6e, 0xd7, 0x6e, 0xf7, 
  0x6e, 0xc7, 0x6e, 0xf8, 0x6e, 0xff, 0x6e, 0xe0, 0x6e, 0x07, 0x6e, 0x00, 0x72, 0x00, 0x75, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb2, 0x00, 0xae, 0x10, 0xae, 0x00, 0x92, 0x03, 0x6e, 0xd4, 0x6e, 0xf4, 
  0x6e, 0xf4, 0x6e, 0xff, 0x6e, 0xdc, 0x6e, 0xbb, 0x6e, 0x07, 0x6e, 0x00, 0x76, 0x00, 0x75, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb2, 0x07, 0xae, 0x0b, 0xae, 0x03, 0x92, 0x07, 0x6e, 0xd7, 0x6e, 0xf4, 
  0x6e, 0xf3, 0x6e, 0xe8, 0x6e, 0x13, 0x6e, 0x07, 0x6e, 0x00, 0x72, 0x00, 0x75, 0x00, 0x75, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb2, 0x1b, 0xae, 0x0c, 0xae, 0x00, 0x92, 0x08, 0x6e, 0xd7, 0x6e, 0xf4, 
  0x6e, 0xf3, 0x6e, 0xe8, 0x6e, 0x0b, 0x6e, 0x00, 0x6e, 0x00, 0x72, 0x00, 0x75, 0x00, 0x75, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb2, 0x0b, 0xae, 0x08, 0xae, 0x04, 0x92, 0x07, 0x6e, 0xd7, 0x6e, 0xf4, 
  0x6e, 0xf4, 0x6e, 0xe7, 0x6e, 0x00, 0x6e, 0x00, 0x6e, 0x00, 0x72, 0x00, 0x75, 0x00, 0x75, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb2, 0x07, 0xae, 0x04, 0xae, 0x03, 0x92, 0x08, 0x6e, 0xcf, 0x6e, 0xf4, 
  0x6e, 0xf3, 0x6e, 0xef, 0x6e, 0x57, 0x6e, 0x43, 0x6e, 0x03, 0x6e, 0x00, 0x76, 0x00, 0x75, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb2, 0x07, 0xae, 0x00, 0xae, 0x03, 0x92, 0x0c, 0x6e, 0xd0, 0x6e, 0xf4, 
  0x6e, 0xf7, 0x6e, 0xff, 0x6e, 0xff, 0x6e, 0xe3, 0x6e, 0x07, 0x6e, 0x00, 0x76, 0x00, 0x75, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb2, 0x04, 0xae, 0x07, 0xae, 0x08, 0x92, 0x0f, 0x6e, 0xd7, 0x6e, 0xf4, 
  0x6e, 0x70, 0x6e, 0xaf, 0x6e, 0xff, 0x6e, 0xdb, 0x6e, 0x07, 0x6e, 0x00, 0x72, 0x00, 0x76, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xb2, 0x00, 0xae, 0x00, 0xae, 0x03, 0x92, 0x13, 0x6e, 0xd4, 0x6e, 0xf4, 
  0x6e, 0x00, 0x6e, 0x10, 0x6e, 0xfc, 0x6e, 0xe0, 0x6e, 0x00, 0x6e, 0x00, 0x6e, 0x00, 0x72, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x92, 0x1c, 0x92, 0x1b, 0x92, 0x33, 0x76, 0x30, 0x6e, 0xe0, 0x6e, 0xf7, 
  0x6e, 0x00, 0x6e, 0x0b, 0x6e, 0xdf, 0x6e, 0xff, 0x6e, 0xa3, 0x6e, 0x84, 0x6e, 0x84, 0x6e, 0x84, 0x6e, 0x80, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x72, 0x77, 0x6e, 0x77, 0x6e, 0xa4, 0x6e, 0xff, 0x6e, 0xd7, 
  0x6e, 0x00, 0x6e, 0x00, 0x6e, 0x50, 0x6e, 0xe7, 0x6e, 0xfb, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfc, 0x6e, 0xfb, 0x6e, 0xe7, 0x6e, 0x4f, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0x0c, 0x6e, 0x73, 0x93, 0x6e, 0x73, 0xe3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xe0, 0x6e, 0x73, 0x93, 0x6e, 0x73, 0x0c, 
  0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0xa0, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xf3, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xec, 0x4e, 0x73, 0xef, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0x9b, 
  0x6e, 0x73, 0x00, 0x6e, 0x73, 0x0f, 0x6e, 0x73, 0xf7, 0x6e, 0x73, 0xef, 0x6e, 0x73, 0x33, 0x6e, 0x73, 0x13, 0x6e, 0x73, 0x13, 0x6e, 0x73, 0x13, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x6d, 0x64, 0x24, 0x8d, 0x64, 0x30, 0x8d, 0x64, 0x2f, 0x2d, 0x6c, 0x28, 0x6e, 0x73, 0xf0, 0x6e, 0x73, 0xef, 
  0x6e, 0x73, 0x0f, 0x6e, 0x73, 0x3f, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xdb, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0x8e, 0x73, 0x00, 0x4e, 0x6c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x10, 0x6d, 0xa3, 0x08, 0x6d, 0x9b, 0x00, 0xed, 0x8b, 0x18, 0x4e, 0x73, 0xd7, 0x6e, 0x73, 0xf7, 
  0x6e, 0x73, 0xc7, 0x6e, 0x73, 0xf8, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xe0, 0x6e, 0x73, 0x07, 0x6e, 0x73, 0x00, 0x8d, 0x64, 0x00, 0x2c, 0x5d, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x00, 0x6d, 0xa3, 0x10, 0x6d, 0xa3, 0x00, 0xed, 0x8b, 0x03, 0x4e, 0x73, 0xd4, 0x6e, 0x73, 0xf4, 
  0x6e, 0x73, 0xf4, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xdc, 0x6e, 0x73, 0xbb, 0x6e, 0x73, 0x07, 0x6e, 0x73, 0x00, 0xac, 0x5c, 0x00, 0x2c, 0x5d, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x07, 0x6d, 0xa3, 0x0b, 0x6d, 0xa3, 0x03, 0xed, 0x8b, 0x07, 0x4e, 0x73, 0xd7, 0x6e, 0x73, 0xf4, 
  0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xe8, 0x6e, 0x73, 0x13, 0x6e, 0x73, 0x07, 0x6e, 0x73, 0x00, 0xad, 0x6b, 0x00, 0x0c, 0x5d, 0x00, 0x2c, 0x5d, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x1b, 0x6d, 0xa3, 0x0c, 0x6d, 0xa3, 0x00, 0xed, 0x8b, 0x08, 0x4e, 0x73, 0xd7, 0x6e, 0x73, 0xf4, 
  0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xe8, 0x6e, 0x73, 0x0b, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0x4d, 0x64, 0x00, 0x4c, 0x55, 0x00, 0x0c, 0x5d, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x0b, 0x6d, 0xa3, 0x08, 0x6d, 0xa3, 0x04, 0xed, 0x8b, 0x07, 0x4e, 0x73, 0xd7, 0x6e, 0x73, 0xf4, 
  0x6e, 0x73, 0xf4, 0x6e, 0x73, 0xe7, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0x0d, 0x6c, 0x00, 0x2c, 0x5d, 0x00, 0x0c, 0x5d, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x07, 0x6d, 0xa3, 0x04, 0x6d, 0xa3, 0x03, 0xed, 0x8b, 0x08, 0x4e, 0x73, 0xcf, 0x6e, 0x73, 0xf4, 
  0x6e, 0x73, 0xf3, 0x6e, 0x73, 0xef, 0x6e, 0x73, 0x57, 0x6e, 0x73, 0x43, 0x6e, 0x73, 0x03, 0x6e, 0x73, 0x00, 0xcc, 0x5c, 0x00, 0x2c, 0x5d, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x07, 0x6d, 0xa3, 0x00, 0x6d, 0xa3, 0x03, 0xed, 0x8b, 0x0c, 0x4e, 0x73, 0xd0, 0x6e, 0x73, 0xf4, 
  0x6e, 0x73, 0xf7, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xe3, 0x6e, 0x73, 0x07, 0x6e, 0x73, 0x00, 0xac, 0x5c, 0x00, 0x2c, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x04, 0x6d, 0xa3, 0x07, 0x6d, 0xa3, 0x08, 0xed, 0x8b, 0x0f, 0x4e, 0x73, 0xd7, 0x6e, 0x73, 0xf4, 
  0x6e, 0x73, 0x70, 0x6e, 0x73, 0xaf, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xdb, 0x6e, 0x73, 0x07, 0x6e, 0x73, 0x00, 0x0d, 0x6c, 0x00, 0xed, 0x64, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xcd, 0x93, 0x00, 0x6d, 0xa3, 0x00, 0x6d, 0xa3, 0x03, 0xed, 0x8b, 0x13, 0x4e, 0x73, 0xd4, 0x6e, 0x73, 0xf4, 
  0x6e, 0x73, 0x00, 0x6e, 0x73, 0x10, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xe0, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0xae, 0x73, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x0d, 0x84, 0x1c, 0x0d, 0x8c, 0x1b, 0x0d, 0x8c, 0x33, 0xed, 0x64, 0x30, 0x6e, 0x73, 0xe0, 0x6e, 0x73, 0xf7, 
  0x6e, 0x73, 0x00, 0x6e, 0x73, 0x0b, 0x6e, 0x73, 0xdf, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xa3, 0x6e, 0x73, 0x84, 0x6e, 0x73, 0x84, 0x6e, 0x73, 0x84, 0x6e, 0x73, 0x80, 0x8e, 0x73, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x6b, 0x77, 0x8e, 0x73, 0x77, 0x6e, 0x73, 0xa4, 0x6e, 0x73, 0xff, 0x6e, 0x73, 0xd7, 
  0x6e, 0x73, 0x00, 0x6e, 0x73, 0x00, 0x6e, 0x73, 0x50, 0x6e, 0x73, 0xe7, 0x6e, 0x73, 0xfb, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfc, 0x6e, 0x73, 0xfb, 0x6e, 0x73, 0xe7, 0x6e, 0x73, 0x4f, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0x0c, 0x73, 0x6e, 0x93, 0x73, 0x6e, 0xe3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xe0, 0x73, 0x6e, 0x93, 0x73, 0x6e, 0x0c, 
  0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0xa0, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xf3, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xec, 0x73, 0x4e, 0xef, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0x9b, 
  0x73, 0x6e, 0x00, 0x73, 0x6e, 0x0f, 0x73, 0x6e, 0xf7, 0x73, 0x6e, 0xef, 0x73, 0x6e, 0x33, 0x73, 0x6e, 0x13, 0x73, 0x6e, 0x13, 0x73, 0x6e, 0x13, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x64, 0x6d, 0x24, 0x64, 0x8d, 0x30, 0x64, 0x8d, 0x2f, 0x6c, 0x2d, 0x28, 0x73, 0x6e, 0xf0, 0x73, 0x6e, 0xef, 
  0x73, 0x6e, 0x0f, 0x73, 0x6e, 0x3f, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xdb, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x73, 0x8e, 0x00, 0x6c, 0x4e, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x10, 0xa3, 0x6d, 0x08, 0x9b, 0x6d, 0x00, 0x8b, 0xed, 0x18, 0x73, 0x4e, 0xd7, 0x73, 0x6e, 0xf7, 
  0x73, 0x6e, 0xc7, 0x73, 0x6e, 0xf8, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xe0, 0x73, 0x6e, 0x07, 0x73, 0x6e, 0x00, 0x64, 0x8d, 0x00, 0x5d, 0x2c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x00, 0xa3, 0x6d, 0x10, 0xa3, 0x6d, 0x00, 0x8b, 0xed, 0x03, 0x73, 0x4e, 0xd4, 0x73, 0x6e, 0xf4, 
  0x73, 0x6e, 0xf4, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xdc, 0x73, 0x6e, 0xbb, 0x73, 0x6e, 0x07, 0x73, 0x6e, 0x00, 0x5c, 0xac, 0x00, 0x5d, 0x2c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x07, 0xa3, 0x6d, 0x0b, 0xa3, 0x6d, 0x03, 0x8b, 0xed, 0x07, 0x73, 0x4e, 0xd7, 0x73, 0x6e, 0xf4, 
  0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xe8, 0x73, 0x6e, 0x13, 0x73, 0x6e, 0x07, 0x73, 0x6e, 0x00, 0x6b, 0xad, 0x00, 0x5d, 0x0c, 0x00, 0x5d, 0x2c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x1b, 0xa3, 0x6d, 0x0c, 0xa3, 0x6d, 0x00, 0x8b, 0xed, 0x08, 0x73, 0x4e, 0xd7, 0x73, 0x6e, 0xf4, 
  0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xe8, 0x73, 0x6e, 0x0b, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x64, 0x4d, 0x00, 0x55, 0x4c, 0x00, 0x5d, 0x0c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x0b, 0xa3, 0x6d, 0x08, 0xa3, 0x6d, 0x04, 0x8b, 0xed, 0x07, 0x73, 0x4e, 0xd7, 0x73, 0x6e, 0xf4, 
  0x73, 0x6e, 0xf4, 0x73, 0x6e, 0xe7, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x6c, 0x0d, 0x00, 0x5d, 0x2c, 0x00, 0x5d, 0x0c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x07, 0xa3, 0x6d, 0x04, 0xa3, 0x6d, 0x03, 0x8b, 0xed, 0x08, 0x73, 0x4e, 0xcf, 0x73, 0x6e, 0xf4, 
  0x73, 0x6e, 0xf3, 0x73, 0x6e, 0xef, 0x73, 0x6e, 0x57, 0x73, 0x6e, 0x43, 0x73, 0x6e, 0x03, 0x73, 0x6e, 0x00, 0x5c, 0xcc, 0x00, 0x5d, 0x2c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x07, 0xa3, 0x6d, 0x00, 0xa3, 0x6d, 0x03, 0x8b, 0xed, 0x0c, 0x73, 0x4e, 0xd0, 0x73, 0x6e, 0xf4, 
  0x73, 0x6e, 0xf7, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xe3, 0x73, 0x6e, 0x07, 0x73, 0x6e, 0x00, 0x5c, 0xac, 0x00, 0x55, 0x2c, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x04, 0xa3, 0x6d, 0x07, 0xa3, 0x6d, 0x08, 0x8b, 0xed, 0x0f, 0x73, 0x4e, 0xd7, 0x73, 0x6e, 0xf4, 
  0x73, 0x6e, 0x70, 0x73, 0x6e, 0xaf, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xdb, 0x73, 0x6e, 0x07, 0x73, 0x6e, 0x00, 0x6c, 0x0d, 0x00, 0x64, 0xed, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x93, 0xcd, 0x00, 0xa3, 0x6d, 0x00, 0xa3, 0x6d, 0x03, 0x8b, 0xed, 0x13, 0x73, 0x4e, 0xd4, 0x73, 0x6e, 0xf4, 
  0x73, 0x6e, 0x00, 0x73, 0x6e, 0x10, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xe0, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x73, 0xae, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x84, 0x0d, 0x1c, 0x8c, 0x0d, 0x1b, 0x8c, 0x0d, 0x33, 0x64, 0xed, 0x30, 0x73, 0x6e, 0xe0, 0x73, 0x6e, 0xf7, 
  0x73, 0x6e, 0x00, 0x73, 0x6e, 0x0b, 0x73, 0x6e, 0xdf, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xa3, 0x73, 0x6e, 0x84, 0x73, 0x6e, 0x84, 0x73, 0x6e, 0x84, 0x73, 0x6e, 0x80, 0x73, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x6b, 0x8e, 0x77, 0x73, 0x8e, 0x77, 0x73, 0x6e, 0xa4, 0x73, 0x6e, 0xff, 0x73, 0x6e, 0xd7, 
  0x73, 0x6e, 0x00, 0x73, 0x6e, 0x00, 0x73, 0x6e, 0x50, 0x73, 0x6e, 0xe7, 0x73, 0x6e, 0xfb, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfc, 0x73, 0x6e, 0xfb, 0x73, 0x6e, 0xe7, 0x73, 0x6e, 0x4f, 
#endif
#if LV_COLOR_DEPTH == 32
  0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x0c, 0x6e, 0x6e, 0x6e, 0x93, 0x6e, 0x6e, 0x6e, 0xe3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xe0, 0x6e, 0x6e, 0x6e, 0x93, 0x6e, 0x6e, 0x6e, 0x0c, 
  0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0xa0, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6c, 0x6e, 0xf3, 0x6f, 0x6a, 0x6f, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x70, 0xec, 0x6f, 0x6a, 0x6f, 0xef, 0x6e, 0x6d, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0x9b, 
  0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x0f, 0x6e, 0x6e, 0x6e, 0xf7, 0x6e, 0x6e, 0x6e, 0xef, 0x6e, 0x6e, 0x6e, 0x33, 0x6e, 0x6e, 0x6e, 0x13, 0x6e, 0x6d, 0x6e, 0x13, 0x6e, 0x6b, 0x6f, 0x13, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x67, 0x8c, 0x61, 0x24, 0x65, 0x91, 0x5f, 0x30, 0x65, 0x92, 0x5e, 0x2f, 0x6a, 0x85, 0x65, 0x28, 0x6e, 0x6d, 0x6e, 0xf0, 0x6e, 0x6e, 0x6e, 0xef, 
  0x6e, 0x6e, 0x6e, 0x0f, 0x6e, 0x6e, 0x6e, 0x3f, 0x6e, 0x6e, 0x6e, 0xfc, 0x6e, 0x6e, 0x6e, 0xdb, 0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6d, 0x6e, 0x00, 0x6e, 0x70, 0x6d, 0x00, 0x6d, 0x88, 0x69, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x79, 0x8e, 0x10, 0x6b, 0x6b, 0x9d, 0x08, 0x6b, 0x6c, 0x9c, 0x00, 0x69, 0x7d, 0x89, 0x18, 0x6f, 0x6a, 0x6f, 0xd7, 0x6e, 0x6e, 0x6e, 0xf7, 
  0x6e, 0x6e, 0x6e, 0xc7, 0x6e, 0x6e, 0x6e, 0xf8, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xe0, 0x6e, 0x6e, 0x6e, 0x07, 0x6f, 0x6c, 0x6f, 0x00, 0x65, 0x8f, 0x5f, 0x00, 0x60, 0xa6, 0x56, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x77, 0x91, 0x00, 0x6b, 0x6b, 0x9d, 0x10, 0x6b, 0x6b, 0x9d, 0x00, 0x69, 0x7b, 0x8c, 0x03, 0x6f, 0x6a, 0x6f, 0xd4, 0x6e, 0x6e, 0x6e, 0xf4, 
  0x6e, 0x6e, 0x6e, 0xf4, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xdc, 0x6e, 0x6e, 0x6e, 0xbb, 0x6e, 0x6e, 0x6e, 0x07, 0x6f, 0x6c, 0x6f, 0x00, 0x63, 0x96, 0x5c, 0x00, 0x5e, 0xa5, 0x55, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x77, 0x91, 0x07, 0x6b, 0x6b, 0x9d, 0x0b, 0x6b, 0x6b, 0x9d, 0x03, 0x69, 0x7b, 0x8b, 0x07, 0x6f, 0x6a, 0x6f, 0xd7, 0x6e, 0x6e, 0x6e, 0xf4, 
  0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xe8, 0x6e, 0x6e, 0x6e, 0x13, 0x6e, 0x6e, 0x6e, 0x07, 0x6e, 0x6d, 0x6f, 0x00, 0x6c, 0x73, 0x6c, 0x00, 0x60, 0x9f, 0x58, 0x00, 0x5f, 0xa3, 0x56, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x77, 0x91, 0x1b, 0x6b, 0x6b, 0x9d, 0x0c, 0x6b, 0x6b, 0x9d, 0x00, 0x69, 0x7b, 0x8b, 0x08, 0x6f, 0x6a, 0x6f, 0xd7, 0x6e, 0x6e, 0x6e, 0xf4, 
  0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xe8, 0x6e, 0x6e, 0x6e, 0x0b, 0x6e, 0x6e, 0x6e, 0x00, 0x6f, 0x6b, 0x6f, 0x00, 0x66, 0x89, 0x62, 0x00, 0x5e, 0xa7, 0x54, 0x00, 0x5f, 0xa2, 0x56, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x77, 0x91, 0x0b, 0x6b, 0x6b, 0x9d, 0x08, 0x6b, 0x6b, 0x9d, 0x04, 0x69, 0x7b, 0x8b, 0x07, 0x6f, 0x6a, 0x6f, 0xd7, 0x6e, 0x6e, 0x6e, 0xf4, 
  0x6e, 0x6e, 0x6e, 0xf4, 0x6e, 0x6e, 0x6e, 0xe7, 0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x00, 0x6f, 0x6b, 0x6f, 0x00, 0x69, 0x81, 0x66, 0x00, 0x5e, 0xa5, 0x55, 0x00, 0x5f, 0xa2, 0x56, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x77, 0x91, 0x07, 0x6b, 0x6b, 0x9d, 0x04, 0x6b, 0x6b, 0x9d, 0x03, 0x69, 0x7b, 0x8b, 0x08, 0x6f, 0x6a, 0x6f, 0xcf, 0x6e, 0x6e, 0x6e, 0xf4, 
  0x6e, 0x6e, 0x6e, 0xf3, 0x6e, 0x6e, 0x6e, 0xef, 0x6e, 0x6e, 0x6e, 0x57, 0x6e, 0x6e, 0x6e, 0x43, 0x6e, 0x6d, 0x6e, 0x03, 0x6e, 0x6e, 0x6e, 0x00, 0x62, 0x9a, 0x5a, 0x00, 0x5e, 0xa4, 0x55, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x77, 0x91, 0x07, 0x6b, 0x6b, 0x9d, 0x00, 0x6b, 0x6b, 0x9d, 0x03, 0x69, 0x7b, 0x8b, 0x0c, 0x6f, 0x6a, 0x6f, 0xd0, 0x6e, 0x6e, 0x6e, 0xf4, 
  0x6e, 0x6e, 0x6e, 0xf7, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xe3, 0x6e, 0x6e, 0x6e, 0x07, 0x6f, 0x6c, 0x6f, 0x00, 0x63, 0x96, 0x5c, 0x00, 0x5d, 0xa6, 0x54, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x77, 0x91, 0x04, 0x6b, 0x6b, 0x9d, 0x07, 0x6b, 0x6b, 0x9d, 0x08, 0x69, 0x7b, 0x8b, 0x0f, 0x6f, 0x6a, 0x6f, 0xd7, 0x6e, 0x6e, 0x6e, 0xf4, 
  0x6e, 0x6e, 0x6e, 0x70, 0x6e, 0x6e, 0x6e, 0xaf, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xdb, 0x6e, 0x6e, 0x6e, 0x07, 0x6e, 0x6c, 0x6f, 0x00, 0x69, 0x81, 0x66, 0x00, 0x66, 0x9e, 0x5e, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x69, 0x77, 0x91, 0x00, 0x6b, 0x6b, 0x9d, 0x00, 0x6b, 0x6b, 0x9d, 0x03, 0x69, 0x7b, 0x8b, 0x13, 0x6f, 0x6a, 0x6f, 0xd4, 0x6e, 0x6e, 0x6e, 0xf4, 
  0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x10, 0x6e, 0x6e, 0x6e, 0xfc, 0x6e, 0x6e, 0x6e, 0xe0, 0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x00, 0x6f, 0x6c, 0x6f, 0x00, 0x70, 0x74, 0x6f, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x68, 0x82, 0x83, 0x1c, 0x67, 0x80, 0x86, 0x1b, 0x67, 0x80, 0x86, 0x33, 0x65, 0x9c, 0x5d, 0x30, 0x6e, 0x6b, 0x6f, 0xe0, 0x6e, 0x6e, 0x6e, 0xf7, 
  0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x0b, 0x6e, 0x6e, 0x6e, 0xdf, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xa3, 0x6e, 0x6e, 0x6e, 0x84, 0x6e, 0x6e, 0x6e, 0x84, 0x6e, 0x6c, 0x6e, 0x84, 0x6e, 0x6c, 0x6f, 0x80, 0x6f, 0x71, 0x6e, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6d, 0x72, 0x6c, 0x77, 0x6e, 0x70, 0x6e, 0x77, 0x6e, 0x6d, 0x6e, 0xa4, 0x6e, 0x6e, 0x6e, 0xff, 0x6e, 0x6e, 0x6e, 0xd7, 
  0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x00, 0x6e, 0x6e, 0x6e, 0x50, 0x6e, 0x6e, 0x6e, 0xe7, 0x6e, 0x6e, 0x6e, 0xfb, 0x6e, 0x6e, 0x6e, 0xfc, 0x6e, 0x6e, 0x6e, 0xfc, 0x6e, 0x6e, 0x6e, 0xfc, 0x6e, 0x6e, 0x6e, 0xfc, 0x6e, 0x6d, 0x6e, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6f, 0xfc, 0x6e, 0x6d, 0x6e, 0xfc, 0x6e, 0x6e, 0x6e, 0xfb, 0x6e, 0x6e, 0x6e, 0xe7, 0x6e, 0x6e, 0x6e, 0x4f, 
#endif
};

const lv_img_dsc_t bat_null = {
  .header.always_zero = 0,
  .header.w = 25,
  .header.h = 15,
  .data_size = 375 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = bat_null_map,
};
