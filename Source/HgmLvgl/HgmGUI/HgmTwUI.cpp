/******************************************************************
 * @file HgmTwUI.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/31 22:54
 * @copyright Copyright (c) 2021/8/31
*******************************************************************/
#include <Arduino.h>
#include <ESP32Time.h>
#include "HgmTwUI.h"
#include"../HgmLvgl.h"
#include "../../HgmApp/TimeInfo/TimeInfo.h"

using namespace HgmApplication;
using namespace HgmGUI;
using namespace HGM;

/* Assets */
// TODO: Add btn
LV_IMG_DECLARE(tw_t);
LV_IMG_DECLARE(tw_w);
LV_IMG_DECLARE(book_left);
LV_IMG_DECLARE(book_right);
LV_IMG_DECLARE(book_mid);


lv_obj_t* tw_time = NULL;
lv_obj_t* tw_weather = NULL;
lv_obj_t* book = NULL;

struct tm time_s;

extern TimeInfo ti;

static void ShowTime();
static void ShowWeather();
static void ShowBili();


HgmTwUI::HgmTwUI()
{

}

HgmTwUI::~HgmTwUI()
{
    
}

void HgmGUI::HgmTwUI::Begin()
{
    //
    tw_time = lv_img_create(lv_scr_act());
    lv_img_set_src(tw_time, &tw_t);
    lv_obj_align(tw_time, LV_ALIGN_TOP_LEFT, 0, 6);

    tw_weather = lv_img_create(lv_scr_act());
    lv_img_set_src(tw_weather, &tw_w);
    // lv_obj_align(tw_weather, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_align(tw_weather, LV_ALIGN_TOP_LEFT, 0, 6);

    book = lv_imgbtn_create(lv_scr_act());
    lv_imgbtn_set_src(book, LV_IMGBTN_STATE_RELEASED, &book_left, &book_mid, &book_right);
    lv_obj_align(book, LV_ALIGN_LEFT_MID, -97, 0);
    lv_obj_set_width(book, 97);

    // anim_book
    lv_anim_t anim_book;
    lv_anim_init(&anim_book);
    lv_anim_set_var(&anim_book, book);
    lv_anim_set_values(&anim_book, -97, 2);
    lv_anim_set_early_apply(&anim_book, false);
    lv_anim_set_exec_cb(&anim_book, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&anim_book, lv_anim_path_ease_in_out);
    lv_anim_set_time(&anim_book, 700);

    // anim_tw
    lv_anim_t anim_tu;
    lv_anim_init(&anim_tu);
    lv_anim_set_var(&anim_tu, tw_time);
    lv_anim_set_values(&anim_tu, -132, 103);
    lv_anim_set_exec_cb(&anim_tu, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&anim_tu, lv_anim_path_ease_in_out);
    lv_anim_set_time(&anim_tu, 1000);

    lv_anim_t anim_td;
    lv_anim_init(&anim_td);
    lv_anim_set_var(&anim_td, tw_weather);
    lv_anim_set_values(&anim_td, -132, 104);
    lv_anim_set_exec_cb(&anim_td, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&anim_td, lv_anim_path_ease_in_out);
    lv_anim_set_time(&anim_td, 1000);

    lv_anim_t anim_tw_expand;
    lv_anim_init(&anim_tw_expand);
    lv_anim_set_var(&anim_tw_expand, tw_weather);
    lv_anim_set_values(&anim_tw_expand, 6, 63);
    lv_anim_set_exec_cb(&anim_tw_expand, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&anim_tw_expand, lv_anim_path_ease_in_out);
    lv_anim_set_time(&anim_tw_expand, 500);

    lv_anim_timeline_t* at = lv_anim_timeline_create();
    lv_anim_timeline_add(at, 0, &anim_book);
    lv_anim_timeline_add(at, 700, &anim_tu);
    lv_anim_timeline_add(at, 700, &anim_td);
    lv_anim_timeline_add(at, 1700, &anim_tw_expand);
    lv_anim_timeline_start(at);

    ShowTime();
}

void HgmGUI::HgmTwUI::Stop()
{
}



static void ShowTime()
{

    while (true) {
        time_s = ti.rtc.getTimeStruct();
        Serial.println(ti.rtc.getTime("%A, %B %d %Y %H:%M:%S"));
        vTaskDelay(1000);
    }
}

static void ShowWeather()
{

}

static void ShowBili()
{

}

