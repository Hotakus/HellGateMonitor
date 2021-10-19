#include "lvgl/lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_W_900
#define LV_ATTRIBUTE_IMG_W_900
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_W_900 uint8_t w_900_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xdf, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0x00, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0x14, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe5, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xe9, 0xff, 0xc5, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xc9, 0xff, 0xc4, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xc9, 0xff, 0xc0, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xc9, 0xff, 0xc0, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xc9, 0xff, 0xa0, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xc9, 0xff, 0xa0, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0xbb, 0x00, 0xb7, 0x00, 
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xed, 0xff, 0xf2, 0xff, 0xee, 0xff, 0xee, 0xff, 0xdb, 0xff, 0xbb, 0xff, 0x6d, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xee, 0xff, 0xe9, 0xff, 0xed, 0xff, 0xee, 0xff, 0xee, 0xff, 0xee, 0xff, 0xbb, 0xff, 0xb7, 0xfc, 
  0xff, 0xff, 0xc5, 0xff, 0xe9, 0xff, 0xe9, 0xff, 0xe9, 0xff, 0xe9, 0xff, 0xe9, 0xff, 0xed, 0xff, 0xe5, 0xff, 0xb7, 0xff, 
  0xff, 0xff, 0xc4, 0xff, 0xc5, 0xff, 0xc5, 0xff, 0xe9, 0xff, 0xe9, 0xff, 0xe9, 0xff, 0xe9, 0xff, 0xe5, 0xff, 0xb7, 0xff, 
  0xff, 0xff, 0xc4, 0xff, 0xc4, 0xff, 0xc5, 0xff, 0xc5, 0xff, 0xc5, 0xff, 0xc9, 0xff, 0xc5, 0xff, 0xc5, 0xff, 0xb7, 0xff, 
  0xff, 0xff, 0xc0, 0xff, 0xc4, 0xff, 0xc4, 0xff, 0xc4, 0xff, 0xc4, 0xff, 0xc4, 0xff, 0xc4, 0xff, 0xc5, 0xff, 0xb7, 0xff, 
  0xff, 0xff, 0x8e, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0xc4, 0xff, 0xc4, 0xff, 0xc4, 0xff, 0x8d, 0xff, 0xb7, 0xff, 
  0x6d, 0x00, 0xff, 0xff, 0x89, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0x92, 0xff, 0xbb, 0xff, 0x6d, 0x00, 
  0x6d, 0x00, 0x6d, 0x00, 0xff, 0xff, 0xdf, 0xff, 0xb7, 0xff, 0xb7, 0xff, 0xdb, 0xff, 0xdb, 0xff, 0x6d, 0x00, 0x6d, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0x00, 0x9b, 0xd6, 0xff, 0x7a, 0xce, 0xff, 0x3a, 0xc6, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0x00, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x7a, 0xce, 0xff, 0x3a, 0xc6, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0x14, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x7a, 0xce, 0xff, 0x3a, 0xc6, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x7a, 0xce, 0xff, 0xb7, 0xc5, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x47, 0xe9, 0xff, 0x47, 0xe9, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x8c, 0xea, 0xff, 0x47, 0xe9, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x8c, 0xea, 0xff, 0x47, 0xe9, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x8c, 0xea, 0xff, 0x47, 0xe9, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x8c, 0xea, 0xff, 0x47, 0xe9, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x8c, 0xea, 0xff, 0x47, 0xe9, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x8b, 0xea, 0xff, 0x47, 0xe1, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x6b, 0xe2, 0xff, 0x26, 0xe1, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x4a, 0xda, 0xff, 0x06, 0xd9, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x09, 0xd2, 0xff, 0xe5, 0xc8, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0xe8, 0xc9, 0xff, 0xa3, 0xc0, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0xc7, 0xc1, 0xff, 0x82, 0xb8, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0xa7, 0xc1, 0xff, 0x62, 0xb0, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0xa7, 0xb9, 0xff, 0x41, 0xa8, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0x1d, 0xe7, 0x00, 0xfc, 0xde, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0xa7, 0xb9, 0xff, 0x41, 0xa8, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0x00, 0x77, 0xad, 0x00, 
  0xec, 0x5a, 0x00, 0xfc, 0xde, 0xff, 0xdc, 0xd6, 0xff, 0x8b, 0xe2, 0xff, 0x31, 0xec, 0xff, 0x4e, 0xeb, 0xff, 0x0d, 0xeb, 0xff, 0xd8, 0xb5, 0xff, 0xb7, 0xb5, 0xff, 0xec, 0x5a, 0x00, 
  0x1d, 0xe7, 0xff, 0xfc, 0xde, 0xff, 0x8f, 0xe3, 0xff, 0x6b, 0xda, 0xff, 0xac, 0xe2, 0xff, 0xcc, 0xe2, 0xff, 0x0d, 0xeb, 0xff, 0x2e, 0xeb, 0xff, 0xb7, 0xb5, 0xff, 0x77, 0xad, 0xfc, 
  0x1d, 0xe7, 0xff, 0xc4, 0xc8, 0xff, 0xa8, 0xd1, 0xff, 0xe9, 0xd9, 0xff, 0x09, 0xda, 0xff, 0x4a, 0xda, 0xff, 0x8b, 0xe2, 0xff, 0xac, 0xe2, 0xff, 0x26, 0xd9, 0xff, 0x77, 0xad, 0xff, 
  0x1d, 0xe7, 0xff, 0xa4, 0xc0, 0xff, 0x46, 0xc9, 0xff, 0x67, 0xd1, 0xff, 0xa7, 0xd1, 0xff, 0xc8, 0xd1, 0xff, 0x09, 0xda, 0xff, 0x4a, 0xda, 0xff, 0x06, 0xd9, 0xff, 0x77, 0xad, 0xff, 
  0x1d, 0xe7, 0xff, 0xa3, 0xc0, 0xff, 0xa4, 0xc0, 0xff, 0x05, 0xc9, 0xff, 0x26, 0xc9, 0xff, 0x66, 0xd1, 0xff, 0x87, 0xd1, 0xff, 0x05, 0xd1, 0xff, 0xe5, 0xd0, 0xff, 0x77, 0xad, 0xff, 
  0x1d, 0xe7, 0xff, 0x82, 0xb8, 0xff, 0x83, 0xb8, 0xff, 0x83, 0xc0, 0xff, 0xa3, 0xc0, 0xff, 0xa3, 0xc0, 0xff, 0xa4, 0xc0, 0xff, 0xc4, 0xc8, 0xff, 0xc4, 0xc8, 0xff, 0x77, 0xad, 0xff, 
  0x1d, 0xe7, 0xff, 0x0d, 0x8b, 0xff, 0x62, 0xb8, 0xff, 0x82, 0xb8, 0xff, 0x82, 0xb8, 0xff, 0x83, 0xb8, 0xff, 0xa3, 0xc0, 0xff, 0xa3, 0xc0, 0xff, 0x8b, 0x82, 0xff, 0x77, 0xad, 0xff, 
  0xec, 0x5a, 0x00, 0xfc, 0xde, 0xff, 0x09, 0x82, 0xff, 0x62, 0xb0, 0xff, 0x62, 0xb0, 0xff, 0x62, 0xb8, 0xff, 0x82, 0xb8, 0xff, 0xb0, 0x73, 0xff, 0xb7, 0xb5, 0xff, 0xec, 0x5a, 0x00, 
  0xec, 0x5a, 0x00, 0xec, 0x5a, 0x00, 0xdc, 0xd6, 0xff, 0x9b, 0xd6, 0xff, 0x36, 0xa5, 0xff, 0x15, 0x9d, 0xff, 0x19, 0xbe, 0xff, 0xd8, 0xb5, 0xff, 0xec, 0x5a, 0x00, 0xec, 0x5a, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0x00, 0xd6, 0x9b, 0xff, 0xce, 0x7a, 0xff, 0xc6, 0x3a, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0x00, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xce, 0x7a, 0xff, 0xc6, 0x3a, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0x14, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xce, 0x7a, 0xff, 0xc6, 0x3a, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xce, 0x7a, 0xff, 0xc5, 0xb7, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xe9, 0x47, 0xff, 0xe9, 0x47, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xea, 0x8c, 0xff, 0xe9, 0x47, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xea, 0x8c, 0xff, 0xe9, 0x47, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xea, 0x8c, 0xff, 0xe9, 0x47, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xea, 0x8c, 0xff, 0xe9, 0x47, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xea, 0x8c, 0xff, 0xe9, 0x47, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xea, 0x8b, 0xff, 0xe1, 0x47, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xe2, 0x6b, 0xff, 0xe1, 0x26, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xda, 0x4a, 0xff, 0xd9, 0x06, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xd2, 0x09, 0xff, 0xc8, 0xe5, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xc9, 0xe8, 0xff, 0xc0, 0xa3, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xc1, 0xc7, 0xff, 0xb8, 0x82, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xc1, 0xa7, 0xff, 0xb0, 0x62, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xb9, 0xa7, 0xff, 0xa8, 0x41, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0xe7, 0x1d, 0x00, 0xde, 0xfc, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xb9, 0xa7, 0xff, 0xa8, 0x41, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0x00, 0xad, 0x77, 0x00, 
  0x5a, 0xec, 0x00, 0xde, 0xfc, 0xff, 0xd6, 0xdc, 0xff, 0xe2, 0x8b, 0xff, 0xec, 0x31, 0xff, 0xeb, 0x4e, 0xff, 0xeb, 0x0d, 0xff, 0xb5, 0xd8, 0xff, 0xb5, 0xb7, 0xff, 0x5a, 0xec, 0x00, 
  0xe7, 0x1d, 0xff, 0xde, 0xfc, 0xff, 0xe3, 0x8f, 0xff, 0xda, 0x6b, 0xff, 0xe2, 0xac, 0xff, 0xe2, 0xcc, 0xff, 0xeb, 0x0d, 0xff, 0xeb, 0x2e, 0xff, 0xb5, 0xb7, 0xff, 0xad, 0x77, 0xfc, 
  0xe7, 0x1d, 0xff, 0xc8, 0xc4, 0xff, 0xd1, 0xa8, 0xff, 0xd9, 0xe9, 0xff, 0xda, 0x09, 0xff, 0xda, 0x4a, 0xff, 0xe2, 0x8b, 0xff, 0xe2, 0xac, 0xff, 0xd9, 0x26, 0xff, 0xad, 0x77, 0xff, 
  0xe7, 0x1d, 0xff, 0xc0, 0xa4, 0xff, 0xc9, 0x46, 0xff, 0xd1, 0x67, 0xff, 0xd1, 0xa7, 0xff, 0xd1, 0xc8, 0xff, 0xda, 0x09, 0xff, 0xda, 0x4a, 0xff, 0xd9, 0x06, 0xff, 0xad, 0x77, 0xff, 
  0xe7, 0x1d, 0xff, 0xc0, 0xa3, 0xff, 0xc0, 0xa4, 0xff, 0xc9, 0x05, 0xff, 0xc9, 0x26, 0xff, 0xd1, 0x66, 0xff, 0xd1, 0x87, 0xff, 0xd1, 0x05, 0xff, 0xd0, 0xe5, 0xff, 0xad, 0x77, 0xff, 
  0xe7, 0x1d, 0xff, 0xb8, 0x82, 0xff, 0xb8, 0x83, 0xff, 0xc0, 0x83, 0xff, 0xc0, 0xa3, 0xff, 0xc0, 0xa3, 0xff, 0xc0, 0xa4, 0xff, 0xc8, 0xc4, 0xff, 0xc8, 0xc4, 0xff, 0xad, 0x77, 0xff, 
  0xe7, 0x1d, 0xff, 0x8b, 0x0d, 0xff, 0xb8, 0x62, 0xff, 0xb8, 0x82, 0xff, 0xb8, 0x82, 0xff, 0xb8, 0x83, 0xff, 0xc0, 0xa3, 0xff, 0xc0, 0xa3, 0xff, 0x82, 0x8b, 0xff, 0xad, 0x77, 0xff, 
  0x5a, 0xec, 0x00, 0xde, 0xfc, 0xff, 0x82, 0x09, 0xff, 0xb0, 0x62, 0xff, 0xb0, 0x62, 0xff, 0xb8, 0x62, 0xff, 0xb8, 0x82, 0xff, 0x73, 0xb0, 0xff, 0xb5, 0xb7, 0xff, 0x5a, 0xec, 0x00, 
  0x5a, 0xec, 0x00, 0x5a, 0xec, 0x00, 0xd6, 0xdc, 0xff, 0xd6, 0x9b, 0xff, 0xa5, 0x36, 0xff, 0x9d, 0x15, 0xff, 0xbe, 0x19, 0xff, 0xb5, 0xd8, 0xff, 0x5a, 0xec, 0x00, 0x5a, 0xec, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0x00, 0xd9, 0xd1, 0xcd, 0xff, 0xd4, 0xcc, 0xc7, 0xff, 0xcd, 0xc5, 0xc0, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0x00, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0xd4, 0xcc, 0xc7, 0xff, 0xcd, 0xc5, 0xc0, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0x14, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0xd4, 0xcc, 0xc7, 0xff, 0xcd, 0xc5, 0xc0, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0xd3, 0xcb, 0xc7, 0xff, 0xbc, 0xb3, 0xc4, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x3c, 0x2a, 0xe6, 0xff, 0x3c, 0x2a, 0xe6, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x5f, 0x50, 0xeb, 0xff, 0x3c, 0x2a, 0xe6, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x5f, 0x50, 0xeb, 0xff, 0x3c, 0x2a, 0xe6, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x5f, 0x50, 0xeb, 0xff, 0x3c, 0x2a, 0xe6, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x5f, 0x50, 0xeb, 0xff, 0x3c, 0x2a, 0xe6, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x5f, 0x50, 0xeb, 0xff, 0x3c, 0x2a, 0xe6, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x5c, 0x4f, 0xe7, 0xff, 0x3a, 0x29, 0xe4, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x56, 0x4b, 0xe1, 0xff, 0x34, 0x25, 0xdd, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x50, 0x47, 0xd9, 0xff, 0x2d, 0x20, 0xd5, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x49, 0x42, 0xd2, 0xff, 0x25, 0x1b, 0xcc, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x42, 0x3e, 0xca, 0xff, 0x1c, 0x15, 0xc2, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x3c, 0x39, 0xc3, 0xff, 0x14, 0x10, 0xb9, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x36, 0x36, 0xbd, 0xff, 0x0d, 0x0b, 0xb1, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x35, 0x35, 0xbb, 0xff, 0x08, 0x08, 0xac, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0xe9, 0xe2, 0xdd, 0x00, 0xe4, 0xdd, 0xd9, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0x35, 0x35, 0xbb, 0xff, 0x08, 0x08, 0xac, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0x00, 0xb8, 0xae, 0xaa, 0x00, 
  0x5e, 0x5b, 0x5a, 0x00, 0xe4, 0xdd, 0xd9, 0xff, 0xdf, 0xd7, 0xd3, 0xff, 0x5c, 0x51, 0xe1, 0xff, 0x8c, 0x84, 0xeb, 0xff, 0x71, 0x68, 0xe8, 0xff, 0x6c, 0x60, 0xe8, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0xbc, 0xb3, 0xaf, 0xff, 0x5e, 0x5b, 0x5a, 0x00, 
  0xe9, 0xe2, 0xdd, 0xff, 0xe4, 0xdd, 0xd9, 0xff, 0x77, 0x70, 0xe2, 0xff, 0x58, 0x4e, 0xdc, 0xff, 0x5d, 0x53, 0xdf, 0xff, 0x64, 0x5a, 0xe2, 0xff, 0x6a, 0x5f, 0xe5, 0xff, 0x70, 0x66, 0xe7, 0xff, 0xbc, 0xb3, 0xaf, 0xff, 0xb8, 0xae, 0xaa, 0xfc, 
  0xe9, 0xe2, 0xdd, 0xff, 0x23, 0x1a, 0xca, 0xff, 0x3f, 0x36, 0xd2, 0xff, 0x45, 0x3c, 0xd5, 0xff, 0x4b, 0x42, 0xd7, 0xff, 0x53, 0x4a, 0xdb, 0xff, 0x59, 0x4f, 0xdd, 0xff, 0x60, 0x56, 0xe0, 0xff, 0x32, 0x25, 0xda, 0xff, 0xb8, 0xae, 0xaa, 0xff, 
  0xe9, 0xe2, 0xdd, 0xff, 0x1d, 0x16, 0xc4, 0xff, 0x30, 0x28, 0xcc, 0xff, 0x36, 0x2d, 0xce, 0xff, 0x3c, 0x33, 0xd1, 0xff, 0x43, 0x3a, 0xd4, 0xff, 0x49, 0x40, 0xd6, 0xff, 0x50, 0x47, 0xda, 0xff, 0x2d, 0x21, 0xd5, 0xff, 0xb8, 0xae, 0xaa, 0xff, 
  0xe9, 0xe2, 0xdd, 0xff, 0x18, 0x13, 0xbe, 0xff, 0x1d, 0x16, 0xc2, 0xff, 0x28, 0x20, 0xc8, 0xff, 0x2d, 0x25, 0xca, 0xff, 0x33, 0x2c, 0xcd, 0xff, 0x3a, 0x31, 0xd0, 0xff, 0x2b, 0x21, 0xce, 0xff, 0x28, 0x1d, 0xd0, 0xff, 0xb8, 0xae, 0xaa, 0xff, 
  0xe9, 0xe2, 0xdd, 0xff, 0x13, 0x0f, 0xb8, 0xff, 0x15, 0x11, 0xba, 0xff, 0x17, 0x12, 0xbd, 0xff, 0x19, 0x13, 0xbf, 0xff, 0x1b, 0x15, 0xc2, 0xff, 0x1d, 0x16, 0xc4, 0xff, 0x20, 0x18, 0xc7, 0xff, 0x22, 0x19, 0xc9, 0xff, 0xb8, 0xae, 0xaa, 0xff, 
  0xe9, 0xe2, 0xdd, 0xff, 0x66, 0x61, 0x8b, 0xff, 0x11, 0x0e, 0xb5, 0xff, 0x12, 0x0f, 0xb7, 0xff, 0x14, 0x10, 0xb9, 0xff, 0x16, 0x12, 0xbc, 0xff, 0x18, 0x13, 0xbe, 0xff, 0x1b, 0x14, 0xc1, 0xff, 0x58, 0x51, 0x7e, 0xff, 0xb8, 0xae, 0xaa, 0xff, 
  0x5e, 0x5b, 0x5a, 0x00, 0xe4, 0xdd, 0xd9, 0xff, 0x46, 0x42, 0x82, 0xff, 0x0e, 0x0c, 0xb2, 0xff, 0x0f, 0x0d, 0xb4, 0xff, 0x11, 0x0e, 0xb6, 0xff, 0x13, 0x0f, 0xb8, 0xff, 0x7d, 0x76, 0x73, 0xff, 0xbc, 0xb3, 0xaf, 0xff, 0x5e, 0x5b, 0x5a, 0x00, 
  0x5e, 0x5b, 0x5a, 0x00, 0x5e, 0x5b, 0x5a, 0x00, 0xdf, 0xd7, 0xd3, 0xff, 0xd9, 0xd1, 0xcd, 0xff, 0xad, 0xa5, 0xa1, 0xff, 0xa8, 0xa0, 0x9c, 0xff, 0xc8, 0xbf, 0xbb, 0xff, 0xc1, 0xb8, 0xb4, 0xff, 0x5e, 0x5b, 0x5a, 0x00, 0x5e, 0x5b, 0x5a, 0x00, 
#endif
};

const lv_img_dsc_t w_900 = {
  .header.always_zero = 0,
  .header.w = 10,
  .header.h = 28,
  .data_size = 280 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = w_900_map,
};
