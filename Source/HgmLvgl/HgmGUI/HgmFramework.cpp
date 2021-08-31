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
#include "../../LvglSrc/lvgl/lvgl.h"
#include "HgmFramework.h"
#include "HgmTwUI.h"

using namespace HgmGUI;

lv_obj_t* hgmFwTabview;
lv_obj_t* hgmTabList[TAB_NUMBER];

HgmTwUI* hgmTwUI = NULL;



HgmFramework::HgmFramework()
{
	/* Create All UI */
	hgmTwUI = new HgmTwUI();
}

HgmFramework::~HgmFramework()
{
	/* Remove All UI */
	delete hgmTwUI;
}


/**
 * @brief initialize the hgm framework
 */
void HgmGUI::HgmFramework::begin()
{
	/* ui init */
	hgmTwUI->Begin();

}
