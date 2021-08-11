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


/**
 * @brief initialize the hgm framework
 */
void HgmGUI::HgmFramework::begin()
{
	hgmFwTabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 5);

	for (uint8_t i = 0; i < TAB_NUMBER; i++) {
		hgmTabList[i] = lv_tabview_add_tab(hgmFwTabview, "-");
	}

	/* ui init */
	this->hgmWiFiUI->begin();
}
