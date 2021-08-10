/******************************************************************
 * @file hgm_top_framework.c
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 18:36
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/

#include "hgm_wifi_ui.h"
#include "hgm_top_framework.h"

//#define TILE_DIR 0      // Vertical
#define TILE_DIR 1      // Horizontal


lv_obj_t *hgm_fw_tv;
lv_obj_t *tv_tile_list[TILE_NUMBER];


/**
 * @brief initialize the hgm framework
 */
void hgm_framework_init(void)
{

	hgm_fw_tv = lv_tileview_create(lv_scr_act());


	for (uint8_t i = 0; i < TILE_NUMBER; i++) {
#if TILE_DIR == 1
		tv_tile_list[i] = lv_tileview_add_tile(hgm_fw_tv, i, 0, (LV_DIR_LEFT | LV_DIR_RIGHT));
#else
        tv_tile_list[i] = lv_tileview_add_tile(hgm_fw_tv, 0, i, (LV_DIR_BOTTOM | LV_DIR_TOP));
#endif
	}

    /* ui init */
    hgm_wifi_config_ui(0);

}

