/******************************************************************
 * @file hgm_wifi_ui.c
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 19:36
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/

#include "HgmWiFiUI.h"
#include "HgmFramework.h"


static void hgm_wifi_config_ui(uint8_t tab_id);

using namespace HgmGUI;

HgmWiFiUI::HgmWiFiUI(uint8_t tab_id)
{
    this->tab_id = tab_id;
}

HgmWiFiUI::~HgmWiFiUI()
{
}

/**
 * @brief Add the ui to specified tab_id.
 * @param tile_id specified tab_id.
 */
void HgmGUI::HgmWiFiUI::begin()
{
    lv_obj_t* tab = hgmTabList[this->tab_id];
    /*lv_obj_t *btn = lv_btn_create(tab);
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, "WiFi");
    lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(btn);*/

    lv_obj_t* label1 = lv_label_create(tab);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label, align the lines to the center ");
    lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, -20);


    lv_obj_t* label2 = lv_label_create(tab);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
    lv_obj_set_width(label2, 150);
    lv_label_set_recolor(label2, true);
    lv_label_set_text(label2, "It #ff00ff is a circularly# scrolling text. ");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 20);
}

