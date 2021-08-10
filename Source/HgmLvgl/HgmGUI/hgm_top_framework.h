/******************************************************************
 * @file hgm_top_framework.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 18:39
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/
#ifndef LVGL_HGM_TOP_FRAMEWORK_H
#define LVGL_HGM_TOP_FRAMEWORK_H

#include "../../LvglSrc/lvgl/lvgl.h"

#define TILE_NUMBER 3

#ifdef __cplusplus
extern "C" {
#endif

extern lv_obj_t *hgm_fw_tv;
extern lv_obj_t *tv_tile_list[TILE_NUMBER];

void hgm_framework_init(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //LVGL_HGM_TOP_FRAMEWORK_H
