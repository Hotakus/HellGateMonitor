/******************************************************************
 * @file hgm_top_framework.c
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 18:36
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/

#include <Arduino.h>
#include "HgmWiFiUI.h"
#include "../../LvglSrc/lvgl/lvgl.h"
#include "HgmFramework.h"


using namespace HgmGUI;


lv_obj_t* hgmFwTabview;
lv_obj_t* hgmTabList[TAB_NUMBER];

HgmFramework::HgmFramework()
{
	/* Create All UI */
	this->hgmWiFiUI = new HgmWiFiUI(0);
}

HgmFramework::~HgmFramework()
{
	/* Remove All UI */
	 delete this->hgmWiFiUI;
}



#include "../../LvglSrc/lvjpg/lv_tjpgd.h"

LV_IMG_DECLARE(wallpaper_jpg);
static void anim_callback(void* var, int32_t v)
{
	lv_obj_set_x((_lv_obj_t*)var, v);
}
void demo_jpg_sjpg(void)
{
	lv_obj_t* img1;

	lv_tjpgd_init();

	img1 = lv_img_create(lv_scr_act());
	//jpg from c array
	lv_img_set_src(img1, &wallpaper_jpg);

	lv_anim_t anim;
	lv_anim_init(&anim);

	lv_anim_set_var(&anim, img1);
	lv_anim_set_values(&anim, 0, 100);
	lv_anim_set_time(&anim, 2000);
	lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)anim_callback);
	lv_anim_set_path_cb(&anim, lv_anim_path_overshoot);
	lv_anim_start(&anim);
}


/**
 * @brief initialize the hgm framework
 */
void HgmGUI::HgmFramework::begin()
{
	//hgmFwTabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 5);

	//for (uint8_t i = 0; i < TAB_NUMBER; i++) {
	//	hgmTabList[i] = lv_tabview_add_tab(hgmFwTabview, "-");
	//}

	///* ui init */
	//this->hgmWiFiUI->begin();

	demo_jpg_sjpg();

}
