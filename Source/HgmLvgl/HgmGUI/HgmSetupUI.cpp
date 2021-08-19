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
#include <iostream>

using namespace HgmGUI;
using namespace HGM;

LV_IMG_DECLARE(HGMBG);
LV_IMG_DECLARE(HGM_LOGO);
LV_FONT_DECLARE(k12x8_10px);

// background's buffer type
typedef uint16_t(*_bg_t)[HGM_MONITOR_HEIGHT];
static uint16_t* BackgroundBuf = NULL;  // background's buffer

static String prevText = "";
static String curText = "";
static String nextText = "";

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
    lv_obj_set_scrollbar_mode(lv_scr_act(), LV_SCROLLBAR_MODE_OFF);

    // logo
    lv_obj_t* logo;
    logo = lv_img_create(lv_scr_act());
    lv_img_set_src(logo, &HGM_LOGO);
    lv_obj_align(logo, LV_ALIGN_TOP_MID, 0, -32);
    lv_anim_t logoAnim;
    lv_anim_init(&logoAnim);
    lv_anim_set_var(&logoAnim, logo);
    lv_anim_set_values(&logoAnim, -32, 20);
    lv_anim_set_time(&logoAnim, 1000);
    lv_anim_set_exec_cb(&logoAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&logoAnim, lv_anim_path_overshoot);
    lv_anim_start(&logoAnim);

    // progress bar
    lv_obj_t* pb;
    pb = lv_bar_create(lv_scr_act());
    lv_obj_set_size(pb, 135, 5);
    lv_bar_set_range(pb, 0, 100);
    lv_obj_align(pb, LV_ALIGN_BOTTOM_MID, 0, 20);
    lv_bar_set_start_value(pb, 0, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(pb, lv_color_make(0xb5, 0xb5, 0xb5), 0);
    lv_obj_set_style_bg_color(pb, lv_color_make(0x48, 0x68, 0x17), LV_PART_INDICATOR);
    lv_anim_t pdAnim;
    lv_anim_init(&pdAnim);
    lv_anim_set_var(&pdAnim, pb);
    lv_anim_set_values(&pdAnim, 20, -30);
    lv_anim_set_time(&pdAnim, 500);
    lv_anim_set_exec_cb(&pdAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&pdAnim, lv_anim_path_overshoot);
    lv_anim_start(&pdAnim);

    // progress label
    
    lv_obj_t* prevCheckLabel;
    lv_obj_t* curCheckLabel;
    static lv_style_t clStyle;

    lv_style_init(&clStyle);
    lv_style_set_text_font(&clStyle, &k12x8_10px);
    lv_style_set_text_color(&clStyle, lv_color_make(0xFF, 0xFF, 0xFF));

    prevCheckLabel = lv_label_create(lv_scr_act());
    lv_obj_add_style(prevCheckLabel, &clStyle, 0);
    lv_obj_align(prevCheckLabel, LV_ALIGN_CENTER, 0, 10);
    lv_label_set_recolor(prevCheckLabel, true);
    lv_label_set_text(prevCheckLabel, "Boot begin.");


    vTaskDelay(2000);   // TODO: delete

    /* out */

    /*lv_anim_set_var(&logoAnim, logo);
    lv_anim_set_values(&logoAnim, 20, -32);
    lv_anim_set_time(&logoAnim, 200);
    lv_anim_set_exec_cb(&logoAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&logoAnim, lv_anim_path_ease_out);
    lv_anim_start(&logoAnim);*/


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
