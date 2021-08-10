/******************************************************************
 * @file hgm_wifi_ui.c
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 19:36
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/

#include "hgm_wifi_ui.h"
#include "hgm_top_framework.h"


/**
 * @brief Add the ui to specified tile_id.
 * @param tile_id specified tile_id.
 */
void hgm_wifi_config_ui(uint8_t tile_id)
{
    lv_obj_t *tile = tv_tile_list[tile_id];


    lv_obj_t *btn = lv_btn_create(tile);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "Tri");
    lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(btn);
}
