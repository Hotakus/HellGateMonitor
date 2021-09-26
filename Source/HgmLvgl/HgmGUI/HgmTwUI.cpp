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

LV_FONT_DECLARE(k12x8_8px);
LV_FONT_DECLARE(k12x8_10px);
LV_FONT_DECLARE(k12x8_14px_time);
LV_FONT_DECLARE(k12x8_16px_time);
LV_FONT_DECLARE(k12x8_24px_time);

static lv_obj_t* tw_time = NULL;
static lv_obj_t* tw_weather = NULL;
static lv_obj_t* book = NULL;

static lv_obj_t* main_time_label = NULL;
static lv_obj_t* date_label = NULL;

static lv_anim_t* anim_book = NULL;
static lv_anim_t* anim_t = NULL;
static lv_anim_t* anim_w = NULL;
static lv_anim_t* anim_tw_expand = NULL;

static lv_timer_t* showTimeTimer = NULL;

struct tm time_s;

extern TimeInfo ti;

static void ShowTime();
static void ShowWeather();
static void ShowBili();

static TaskHandle_t showTaskHandle;
static void ShowTime(lv_timer_t* timer);

HgmTwUI::HgmTwUI()
{

}

HgmTwUI::~HgmTwUI()
{

}

void HgmGUI::HgmTwUI::Begin()
{

    // TODO: use SPI RAM

    //
    tw_time = lv_img_create(lv_scr_act());
    lv_img_set_src(tw_time, &tw_t);
    lv_obj_align(tw_time, LV_ALIGN_TOP_LEFT, -132, 6);

    tw_weather = lv_img_create(lv_scr_act());
    lv_img_set_src(tw_weather, &tw_w);
    // lv_obj_align(tw_weather, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_align(tw_weather, LV_ALIGN_TOP_LEFT, -132, 6);

    book = lv_imgbtn_create(lv_scr_act());
    lv_imgbtn_set_src(book, LV_IMGBTN_STATE_RELEASED, &book_left, &book_mid, &book_right);
    lv_obj_align(book, LV_ALIGN_LEFT_MID, -97, 0);
    lv_obj_set_width(book, 97);

    /* Label */
    main_time_label = lv_label_create(tw_time);
    lv_label_set_recolor(main_time_label, true);
    lv_label_set_text(main_time_label, "#59493f --:--#");
    lv_obj_align(main_time_label, LV_ALIGN_TOP_RIGHT, -3, 10);
    lv_obj_set_style_opa(main_time_label, LV_OPA_0, 0);
    lv_obj_set_style_text_font(main_time_label, &k12x8_14px_time, 0);

    date_label = lv_label_create(tw_time);
    lv_label_set_recolor(date_label, true);
    lv_label_set_text(date_label, "#59493f 1970.01.01 ---#");
    lv_obj_align(date_label, LV_ALIGN_BOTTOM_RIGHT, -6, -5);
    lv_obj_set_style_opa(date_label, LV_OPA_0, 0);
    lv_obj_set_style_text_font(date_label, &k12x8_8px, 0);


    /* Animations */
    anim_book = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    anim_t = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    anim_w = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    anim_tw_expand = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));

    // anim_book
    lv_anim_init(anim_book);
    lv_anim_set_var(anim_book, book);
    lv_anim_set_values(anim_book, -97, 2);
    lv_anim_set_early_apply(anim_book, false);
    lv_anim_set_exec_cb(anim_book, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(anim_book, lv_anim_path_ease_in_out);
    lv_anim_set_time(anim_book, 900);

    // anim_tw
    lv_anim_init(anim_t);
    lv_anim_set_var(anim_t, tw_time);
    lv_anim_set_values(anim_t, -132, 103);
    lv_anim_set_exec_cb(anim_t, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(anim_t, lv_anim_path_ease_in_out);
    lv_anim_set_time(anim_t, 1000);

    lv_anim_init(anim_w);
    lv_anim_set_var(anim_w, tw_weather);
    lv_anim_set_values(anim_w, -132, 104);
    lv_anim_set_exec_cb(anim_w, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(anim_w, lv_anim_path_ease_in_out);
    lv_anim_set_time(anim_w, 1000);

    lv_anim_init(anim_tw_expand);
    lv_anim_set_var(anim_tw_expand, tw_weather);
    lv_anim_set_values(anim_tw_expand, 6, 63);
    lv_anim_set_exec_cb(anim_tw_expand, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(anim_tw_expand, lv_anim_path_ease_in_out);
    lv_anim_set_time(anim_tw_expand, 500);

    // anim time line
    lv_anim_timeline_t* at = lv_anim_timeline_create();
    lv_anim_timeline_add(at, 0, anim_book);
    lv_anim_timeline_add(at, 800, anim_t);
    lv_anim_timeline_add(at, 800, anim_w);
    lv_anim_timeline_add(at, 1800, anim_tw_expand);

    vTaskDelay(lv_anim_timeline_start(at));

    // TODO: add animation
    // TODO: Show clock img per 
    showTimeTimer = lv_timer_create(ShowTime, 500, NULL);

    lv_obj_set_style_opa(main_time_label, LV_OPA_100, 0);
    lv_obj_set_style_opa(date_label, LV_OPA_100, 0);
}

void HgmGUI::HgmTwUI::Stop()
{

}


static void ShowTime(lv_timer_t* timer)
{
    static bool secIndicator = true;
    static char* wd[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    struct tm _tm = ti.rtc.getTimeStruct();
    String text1 = "#59493f %02d:%02d#";
    String text2 = "#59493f %02d %02d#";

    if (secIndicator) {
        lv_label_set_text_fmt(main_time_label, text1.c_str(), _tm.tm_hour, _tm.tm_min);
        secIndicator = false;
    } else {
        lv_label_set_text_fmt(main_time_label, text2.c_str(), _tm.tm_hour, _tm.tm_min);
        secIndicator = true;
    }

    lv_label_set_text_fmt(date_label, "#59493f %04d.%02d.%02d %s#",
        _tm.tm_year + 1900,
        _tm.tm_mon + 1,
        _tm.tm_mday,
        wd[_tm.tm_wday]
    );
}

static void ShowWeather()
{

}

static void ShowBili()
{

}

