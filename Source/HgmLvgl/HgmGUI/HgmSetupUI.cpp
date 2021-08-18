/******************************************************************
 * @file HgmSetupUI.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/18 23:18
 * @copyright Copyright (c) 2021/8/18
*******************************************************************/
#include "HgmSetupUI.h"
#include"../HgmLvgl.h"
#include <TJpg_Decoder.h>

using namespace HgmGUI;
using namespace HGM;

LV_IMG_DECLARE(HGMBG);
LV_IMG_DECLARE(HGM_LOGO);

// background's buffer type
typedef uint16_t(*_bg_t)[HGM_MONITOR_HEIGHT];
static uint16_t* BackgroundBuf = NULL;  // background's buffer

static lv_obj_t* bg = NULL;
static lv_img_dsc_t bg_dsc;


static void ProgressCheckTask(void* params);


HgmSetupUI::HgmSetupUI()
{
}

HgmSetupUI::~HgmSetupUI()
{
}

void HgmGUI::HgmSetupUI::Begin()
{
    // Set the bg for lv_scr_act()
    lv_obj_set_style_bg_img_src(lv_scr_act(), &HGMBG, 0);

    lv_obj_t* logo;
    logo = lv_img_create(lv_scr_act());
    lv_img_set_src(logo, &HGM_LOGO);
    lv_obj_align(logo, LV_ALIGN_TOP_MID, 0, -32);

    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, logo);
    lv_anim_set_values(&anim, -32, 20);
    lv_anim_set_time(&anim, 1000);
    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&anim, lv_anim_path_overshoot);
    lv_anim_start(&anim);





    lv_anim_set_var(&anim, logo);
    lv_anim_set_values(&anim, 20, -32);
    lv_anim_set_time(&anim, 200);
    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_out);
    lv_anim_start(&anim);
}

void HgmGUI::HgmSetupUI::ProgressUIBegin()
{
}

void HgmGUI::HgmSetupUI::ProgressSet(uint8_t progress)
{
}


static void ProgressCheckTask(void* params)
{
    while (true) {

    }
}
