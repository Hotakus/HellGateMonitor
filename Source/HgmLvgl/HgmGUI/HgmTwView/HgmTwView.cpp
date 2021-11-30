/******************************************************************
 * @file HgmTwView.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/31 22:54
 * @copyright Copyright (c) 2021/8/31
*******************************************************************/
#include "HgmTwView.h"
#include "../../HgmLvgl.h"
#include "../../../HgmApp/TimeInfo/TimeInfo.h"
#include "../../../HgmApp/BiliInfoRecv/BiliInfoRecv.h"
#include "../../../HgmApp/WeatherInfo/WeatherInfo.h"
#include "../../../Utils/SPIFFSUtil/SPIFFSUtil.h"

#include <Arduino.h>
#include <ESP32Time.h>
#include <WiFi.h>


using namespace HgmApplication;
using namespace HgmGUI;
using namespace HGM;
using namespace spiffsutil;

extern lv_group_t* keypad_group;

/* Assets */
// TODO: Add btn
LV_IMG_DECLARE(tw_t);
LV_IMG_DECLARE(tw_w);
LV_IMG_DECLARE(book_left);
LV_IMG_DECLARE(book_right);
LV_IMG_DECLARE(book_mid);

LV_IMG_DECLARE(bat_100);
LV_IMG_DECLARE(bat_75);
LV_IMG_DECLARE(bat_50);
LV_IMG_DECLARE(bat_25);
LV_IMG_DECLARE(bat_10);
LV_IMG_DECLARE(bat_null);

LV_IMG_DECLARE(signal_0);
LV_IMG_DECLARE(signal_1);
LV_IMG_DECLARE(signal_2);
LV_IMG_DECLARE(signal_3);
LV_IMG_DECLARE(signal_4);
LV_IMG_DECLARE(signal_5);

LV_FONT_DECLARE(black_8px);
LV_FONT_DECLARE(black_10px);
LV_FONT_DECLARE(fangpx_8px);
LV_FONT_DECLARE(fangpx_10px);
LV_FONT_DECLARE(fangpx_12px);
LV_FONT_DECLARE(k12x8_6px);
LV_FONT_DECLARE(k12x8_7px);
LV_FONT_DECLARE(k12x8_8px);
LV_FONT_DECLARE(k12x8_10px);
LV_FONT_DECLARE(k12x8_14px_time);
LV_FONT_DECLARE(k12x8_16px_time);
LV_FONT_DECLARE(k12x8_24px_time);

LV_IMG_DECLARE(clock_00)
LV_IMG_DECLARE(clock_07)
LV_IMG_DECLARE(clock_12)
LV_IMG_DECLARE(clock_16)
LV_IMG_DECLARE(clock_22)
LV_IMG_DECLARE(clock_27)
LV_IMG_DECLARE(clock_32)
LV_IMG_DECLARE(clock_39)
LV_IMG_DECLARE(clock_43)
LV_IMG_DECLARE(clock_49)
LV_IMG_DECLARE(clock_54)
LV_IMG_DECLARE(clock_60)

LV_IMG_DECLARE(next_pr)
LV_IMG_DECLARE(next_rel)
LV_IMG_DECLARE(prev_pr)
LV_IMG_DECLARE(prev_rel)
LV_IMG_DECLARE(prompt_frame_left);
LV_IMG_DECLARE(prompt_frame_mid);
LV_IMG_DECLARE(prompt_frame_right);

static const lv_img_dsc_t* clock_imgs_array[] = {
    // 24:00
    &clock_32,
    &clock_39,
    &clock_43,
    &clock_49,
    &clock_54,
    &clock_60,
    // 12:00
    &clock_00,
    &clock_07,
    &clock_12,
    &clock_16,
    &clock_22,
    &clock_27,
};


static lv_timer_t* showTimeTimer = NULL;

extern BiliInfoRecv bili;
extern WeatherInfo weatherInfo;
extern WeatherData weatherDataToday;

static void ShowTime(lv_timer_t* timer);

static void weatherWidgetsCreate();
static void biliWidgetsCreate();
static void timeWidgetsCreate();

static HgmTwView* instance = NULL;

HgmTwView::HgmTwView()
{
    instance = this;
}

HgmTwView::~HgmTwView()
{
    instance = NULL;
}

static void _initTask()
{
    bili.initTask();
    weatherInfo.initTask();
}

static void _deInitTask()
{
    bili.deInitTask();
    weatherInfo.deInitTask();
}


static lv_timer_t* stateCheckTimer = NULL;
static void stateCheck(lv_timer_t* timer)
{
    //lv_img_set_src(widget.status_bar.battery.icon, &bat_50);
    // TODO: battery

    if (!WiFi.isConnected()) {
        lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_0);
    } else {
        lv_img_dsc_t* dsc;
        int8_t rssi = WiFi.RSSI();
        uint8_t ret = (((rssi + 100) << 1) << 1) >> 1;

        if (ret < 40)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_1);
        else if (ret < 60)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_2);
        else if (ret < 80)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_3);
        else if (ret < 100)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_4);
        else if (ret >= 100)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_5);
    }
}

void HgmGUI::HgmTwView::begin()
{
    instance->frameCreate();
    instance->widgetCreate();
    instance->animCreate();
    
    showTimeTimer = lv_timer_create(ShowTime, 500, NULL);
    stateCheckTimer = lv_timer_create(stateCheck, 2000, NULL);
    
    _initTask();
}

void HgmGUI::HgmTwView::end()
{
    _deInitTask();
     
    lv_timer_del(stateCheckTimer);
    lv_timer_del(showTimeTimer);

    lv_group_remove_all_objs(widget.group);

    instance->animDestroy();
    instance->widgetDestroy();
    instance->frameDestroy();
}

void HgmGUI::HgmTwView::status_bar_create()
{
    widget.status_bar.battery.icon = lv_img_create(widget.weather.tw_weather);
    lv_obj_set_style_opa(widget.status_bar.battery.icon, LV_OPA_0, 0);
    lv_obj_align(widget.status_bar.battery.icon, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_img_set_src(widget.status_bar.battery.icon, &bat_null);

    widget.status_bar.signal.icon = lv_img_create(widget.weather.tw_weather);
    lv_obj_set_style_opa(widget.status_bar.signal.icon, LV_OPA_0, 0);
    lv_obj_align_to(widget.status_bar.signal.icon, widget.status_bar.battery.icon, LV_ALIGN_OUT_RIGHT_TOP, 5, 0);
    lv_img_set_src(widget.status_bar.signal.icon, &signal_0);
}

void HgmGUI::HgmTwView::widgetCreate()
{
    timeWidgetsCreate();
    biliWidgetsCreate();
    weatherWidgetsCreate();
    status_bar_create();

    widget.group = keypad_group;
    lv_group_add_obj(widget.group, widget.next_btn);
    lv_group_add_obj(widget.group, widget.prev_btn);
}

void HgmGUI::HgmTwView::frameCreate()
{
    instance->widget.time.tw_time = lv_img_create(lv_scr_act());
    lv_obj_align(instance->widget.time.tw_time, LV_ALIGN_TOP_LEFT, -132, 6);
    lv_img_set_src(instance->widget.time.tw_time, &tw_t);

    instance->widget.weather.tw_weather = lv_img_create(lv_scr_act());
    lv_obj_align(instance->widget.weather.tw_weather, LV_ALIGN_TOP_LEFT, -132, 6);
    lv_img_set_src(instance->widget.weather.tw_weather, &tw_w);

    instance->widget.bili.book = lv_imgbtn_create(lv_scr_act());
    lv_obj_align(instance->widget.bili.book, LV_ALIGN_LEFT_MID, -97, 0);
    lv_imgbtn_set_src(instance->widget.bili.book, LV_IMGBTN_STATE_RELEASED, &book_left, &book_mid, &book_right);
    lv_obj_set_width(instance->widget.bili.book, 97);
}

void HgmGUI::HgmTwView::animCreate()
{
    /* Animations */
    lv_anim_init(&instance->widget.anim.anim_book);
    lv_anim_set_var(&instance->widget.anim.anim_book, instance->widget.bili.book);
    lv_anim_set_values(&instance->widget.anim.anim_book, -97, 2);
    lv_anim_set_early_apply(&instance->widget.anim.anim_book, false);
    lv_anim_set_exec_cb(&instance->widget.anim.anim_book, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&instance->widget.anim.anim_book, lv_anim_path_ease_in_out);
    lv_anim_set_time(&instance->widget.anim.anim_book, 900);

    // anim_tw
    lv_anim_init(&instance->widget.anim.anim_t);
    lv_anim_set_var(&instance->widget.anim.anim_t, instance->widget.time.tw_time);
    lv_anim_set_values(&instance->widget.anim.anim_t, -132, 103);
    lv_anim_set_exec_cb(&instance->widget.anim.anim_t, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&instance->widget.anim.anim_t, lv_anim_path_ease_in_out);
    lv_anim_set_time(&instance->widget.anim.anim_t, 1000);

    lv_anim_init(&instance->widget.anim.anim_w);
    lv_anim_set_var(&instance->widget.anim.anim_w, instance->widget.weather.tw_weather);
    lv_anim_set_values(&instance->widget.anim.anim_w, -132, 104);
    lv_anim_set_exec_cb(&instance->widget.anim.anim_w, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&instance->widget.anim.anim_w, lv_anim_path_ease_in_out);
    lv_anim_set_time(&instance->widget.anim.anim_w, 1000);

    lv_anim_init(&instance->widget.anim.anim_tw_expand);
    lv_anim_set_var(&instance->widget.anim.anim_tw_expand, instance->widget.weather.tw_weather);
    lv_anim_set_values(&instance->widget.anim.anim_tw_expand, 6, 63);
    lv_anim_set_exec_cb(&instance->widget.anim.anim_tw_expand, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&instance->widget.anim.anim_tw_expand, lv_anim_path_ease_in_out);
    lv_anim_set_time(&instance->widget.anim.anim_tw_expand, 500);

    // anim time line
    instance->widget.anim.at = lv_anim_timeline_create();
    lv_anim_timeline_add(instance->widget.anim.at, 0, &instance->widget.anim.anim_book);
    lv_anim_timeline_add(instance->widget.anim.at, 800, &instance->widget.anim.anim_t);
    lv_anim_timeline_add(instance->widget.anim.at, 800, &instance->widget.anim.anim_w);
    lv_anim_timeline_add(instance->widget.anim.at, 1800, &instance->widget.anim.anim_tw_expand);
    vTaskDelay(lv_anim_timeline_start(instance->widget.anim.at) + 500);

    // show
    lv_obj_set_style_opa(instance->widget.bili.faceImg, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.bili.biliName, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.bili.biliFans, LV_OPA_100, 0);

    lv_obj_set_style_opa(instance->widget.time.main_time_label, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.time.date_label, LV_OPA_100, 0);

    lv_obj_set_style_opa(widget.status_bar.battery.icon, LV_OPA_100, 0);
    lv_obj_set_style_opa(widget.status_bar.signal.icon, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.weather.tempLabel.label, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.weather.aqiLabel.label, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.weather.humidityLabel.label, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.weather.location, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.weather.tempLabel.bar, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.weather.aqiLabel.bar, LV_OPA_100, 0);
    lv_obj_set_style_opa(instance->widget.weather.humidityLabel.bar, LV_OPA_100, 0);
}


static void fade(void* obj, int32_t val)
{
    lv_obj_set_style_opa((lv_obj_t*)obj, val, 0);
}

void HgmTwView::animDestroy()
{
    // fade out effect
    lv_anim_t fa;
    lv_anim_init(&fa);
    lv_anim_set_values(&fa, LV_OPA_100, LV_OPA_0);
    lv_anim_set_time(&fa, 300);
    lv_anim_set_exec_cb(&fa, (lv_anim_exec_xcb_t)fade);
    lv_anim_set_path_cb(&fa, lv_anim_path_ease_in_out);
    
    // weather
    lv_anim_set_var(&fa, instance->widget.weather.icon);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.weather.humidityLabel.label);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.weather.humidityLabel.bar);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.weather.aqiLabel.label);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.weather.aqiLabel.bar);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.weather.tempLabel.label);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.weather.tempLabel.bar);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.weather.location);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.status_bar.signal.icon);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.status_bar.battery.icon);
    lv_anim_start(&fa);
    vTaskDelay(300);

    // time
    lv_anim_set_var(&fa, instance->widget.time.date_label);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.time.main_time_label);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.time.clock_img);
    lv_anim_start(&fa);
    vTaskDelay(300);

    // bilibili
    lv_anim_set_var(&fa, instance->widget.bili.faceImg);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.bili.biliName);
    lv_anim_start(&fa);
    lv_anim_set_var(&fa, instance->widget.bili.biliFans);
    lv_anim_start(&fa);
    // TODO:
    vTaskDelay(500);
    lv_anim_del(&fa, nullptr);

    lv_anim_timeline_set_reverse(instance->widget.anim.at, true);
    vTaskDelay(lv_anim_timeline_start(instance->widget.anim.at));
    
    lv_anim_timeline_del(instance->widget.anim.at);
    lv_anim_del(&instance->widget.anim.anim_book     , NULL);
    lv_anim_del(&instance->widget.anim.anim_t        , NULL);
    lv_anim_del(&instance->widget.anim.anim_w        , NULL);
    lv_anim_del(&instance->widget.anim.anim_tw_expand, NULL);
}

void HgmTwView::widgetDestroy()
{
    hotakusFree(instance->widget.weather.icon_buf);
}

void HgmTwView::frameDestroy()
{
    lv_obj_del(instance->widget.time.tw_time);
    lv_obj_del(instance->widget.weather.tw_weather);
    lv_obj_del(instance->widget.bili.book);
}

static void timeWidgetsCreate()
{
    instance->widget.time.main_time_label = lv_label_create(instance->widget.time.tw_time);
    lv_obj_set_style_opa(instance->widget.time.main_time_label, LV_OPA_0, 0);
    lv_label_set_recolor(instance->widget.time.main_time_label, true);
    lv_label_set_text(instance->widget.time.main_time_label, "#59493f --:--#");
    lv_obj_align(instance->widget.time.main_time_label, LV_ALIGN_TOP_RIGHT, -3, 10);
    lv_obj_set_style_text_font(instance->widget.time.main_time_label, &k12x8_14px_time, 0);

    instance->widget.time.date_label = lv_label_create(instance->widget.time.tw_time);
    lv_obj_set_style_opa(instance->widget.time.date_label, LV_OPA_0, 0);
    lv_label_set_recolor(instance->widget.time.date_label, true);
    lv_label_set_text(instance->widget.time.date_label, "#59493f 1970.01.01 ---#");
    lv_obj_align(instance->widget.time.date_label, LV_ALIGN_BOTTOM_RIGHT, -8, -5);
    lv_obj_set_style_text_font(instance->widget.time.date_label, &k12x8_6px, 0);

    // clock image
    instance->widget.time.clock_img = lv_img_create(instance->widget.time.tw_time);
    lv_obj_align(instance->widget.time.clock_img, LV_ALIGN_TOP_LEFT, 5, 2);
}

static void ctl_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_current_target(e);

    if (!instance->controllable())
        return;

    if (obj == instance->widget.next_btn) {
        HgmFramework::getInstance()->changeGUI("ScreenRecv");
    } else {
        HgmFramework::getInstance()->changeGUI("HgmMonitor");
    }
}

static void focus_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_current_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    switch (code) {
    case LV_EVENT_FOCUSED:
        if (obj == instance->widget.next_btn) {
            lv_imgbtn_set_src(instance->widget.next_btn, LV_IMGBTN_STATE_RELEASED, &next_pr, 0, 0);
        } else if (obj == instance->widget.prev_btn) {
            lv_imgbtn_set_src(instance->widget.prev_btn, LV_IMGBTN_STATE_RELEASED, &prev_pr, 0, 0);
        }
        break;
    case LV_EVENT_DEFOCUSED:
        if (obj == instance->widget.next_btn) {
            lv_imgbtn_set_src(instance->widget.next_btn, LV_IMGBTN_STATE_RELEASED, &next_rel, 0, 0);
        } else if (obj == instance->widget.prev_btn) {
            lv_imgbtn_set_src(instance->widget.prev_btn, LV_IMGBTN_STATE_RELEASED, &prev_rel, 0, 0);
        }
        break;
    default:
        break;
    }

}

static void biliWidgetsCreate()
{
    // Face
    instance->widget.bili.face_dsc.header.always_zero = 0;
    instance->widget.bili.face_dsc.header.w = 64;
    instance->widget.bili.face_dsc.header.h = 64;
    instance->widget.bili.face_dsc.data_size = 4096 * 2;
    instance->widget.bili.face_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
    instance->widget.bili.face_dsc.data = (uint8_t*)BiliInfoRecv::getUserFaceBitmap();
    instance->widget.bili.faceImg = lv_img_create(instance->widget.bili.book);
    lv_obj_set_style_opa(instance->widget.bili.faceImg, LV_OPA_0, 0);
    lv_img_set_src(instance->widget.bili.faceImg, &instance->widget.bili.face_dsc);
    lv_obj_align(instance->widget.bili.faceImg, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_size(instance->widget.bili.faceImg, 64, 64);

    lv_style_init(&instance->widget.style_pr);
    lv_style_set_img_recolor_opa(&instance->widget.style_pr, LV_OPA_30);
    lv_style_set_img_recolor(&instance->widget.style_pr, lv_color_black());

    instance->widget.next_btn = lv_imgbtn_create(instance->widget.bili.book);
    lv_obj_set_size(instance->widget.next_btn, 15, 8);
    lv_obj_add_style(instance->widget.next_btn, &instance->widget.style_pr, LV_STATE_PRESSED);
    lv_imgbtn_set_src(instance->widget.next_btn, LV_IMGBTN_STATE_PRESSED, &next_pr, 0, 0);
    lv_imgbtn_set_src(instance->widget.next_btn, LV_IMGBTN_STATE_RELEASED, &next_rel, 0, 0);
    lv_obj_align(instance->widget.next_btn, LV_ALIGN_BOTTOM_RIGHT, -15, -10);
    lv_obj_add_event_cb(instance->widget.next_btn, ctl_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(instance->widget.next_btn, focus_event_cb, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(instance->widget.next_btn, focus_event_cb, LV_EVENT_DEFOCUSED, NULL);

    instance->widget.prev_btn = lv_imgbtn_create(instance->widget.bili.book);
    lv_obj_set_size(instance->widget.prev_btn, 15, 8);
    lv_obj_add_style(instance->widget.prev_btn, &instance->widget.style_pr, LV_STATE_PRESSED);
    lv_imgbtn_set_src(instance->widget.prev_btn, LV_IMGBTN_STATE_PRESSED, &prev_pr, 0, 0);
    lv_imgbtn_set_src(instance->widget.prev_btn, LV_IMGBTN_STATE_RELEASED, &prev_rel, 0, 0);
    lv_obj_align(instance->widget.prev_btn, LV_ALIGN_BOTTOM_LEFT, 15, -10);
    lv_obj_add_event_cb(instance->widget.prev_btn, ctl_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(instance->widget.prev_btn, focus_event_cb, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(instance->widget.prev_btn, focus_event_cb, LV_EVENT_DEFOCUSED, NULL);

    // Bili label
    instance->widget.bili.biliName = lv_label_create(instance->widget.bili.book);
    lv_obj_set_style_opa(instance->widget.bili.biliName, LV_OPA_0, 0);
    lv_obj_set_style_text_font(instance->widget.bili.biliName, &k12x8_10px, 0);
    lv_obj_set_width(instance->widget.bili.biliName, 85);
    lv_label_set_recolor(instance->widget.bili.biliName, true);
    lv_label_set_long_mode(instance->widget.bili.biliName, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text_fmt(instance->widget.bili.biliName, "#59493f %s#", "------");
    lv_obj_set_style_text_align(instance->widget.bili.biliName, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(instance->widget.bili.biliName, LV_ALIGN_BOTTOM_MID, 0, -35);

    instance->widget.bili.biliFans = lv_label_create(instance->widget.bili.book);
    lv_obj_set_style_opa(instance->widget.bili.biliFans, LV_OPA_0, 0);
    lv_label_set_recolor(instance->widget.bili.biliFans, true);
    lv_label_set_text_fmt(instance->widget.bili.biliFans, "#59493f %s#", "------");
    lv_obj_set_style_text_align(instance->widget.bili.biliFans, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(instance->widget.bili.biliFans, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_style_text_font(instance->widget.bili.biliFans, &k12x8_6px, 0);
}

static void weatherWidgetsCreate()
{
    vTaskDelay(50);
    instance->widget.weather.location = lv_label_create(instance->widget.weather.tw_weather);
    lv_obj_set_width(instance->widget.weather.location, 70);
    lv_label_set_recolor(instance->widget.weather.location, true);
    lv_label_set_text_fmt(instance->widget.weather.location, "#39291f    #");
    lv_obj_set_style_text_align(instance->widget.weather.location, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(instance->widget.weather.location, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_text_font(instance->widget.weather.location, &fangpx_10px, 0);
    lv_label_set_long_mode(instance->widget.weather.location, LV_LABEL_LONG_SCROLL_CIRCULAR);

    vTaskDelay(50);

    /* temp */
    instance->widget.weather.tempLabel.label = lv_label_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_opa(instance->widget.weather.tempLabel.label, LV_OPA_0, 0);
    lv_obj_set_style_text_font(instance->widget.weather.tempLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(instance->widget.weather.tempLabel.label, true);
    lv_label_set_text_fmt(instance->widget.weather.tempLabel.label, "#59493f --℃#");
    lv_obj_set_style_text_align(instance->widget.weather.tempLabel.label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(instance->widget.weather.tempLabel.label, LV_ALIGN_TOP_LEFT, 45, 22);

    instance->widget.weather.tempLabel.bar = lv_bar_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_opa(instance->widget.weather.tempLabel.bar, LV_OPA_0, 0);
    lv_bar_set_mode(instance->widget.weather.tempLabel.bar, LV_BAR_MODE_SYMMETRICAL);
    lv_obj_set_size(instance->widget.weather.tempLabel.bar, 38, 8);
    lv_bar_set_range(instance->widget.weather.tempLabel.bar, -60, 60);
    lv_bar_set_value(instance->widget.weather.tempLabel.bar, -0, LV_ANIM_ON);
    lv_obj_set_style_radius(instance->widget.weather.tempLabel.bar, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(instance->widget.weather.tempLabel.bar, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(instance->widget.weather.tempLabel.bar, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(instance->widget.weather.tempLabel.bar, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(instance->widget.weather.tempLabel.bar, instance->widget.weather.tempLabel.label, LV_ALIGN_OUT_RIGHT_TOP, 5, 0);

    vTaskDelay(50);

    /* aqi */
    instance->widget.weather.aqiLabel.label = lv_label_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_opa(instance->widget.weather.aqiLabel.label, LV_OPA_0, 0);
    lv_obj_align_to(instance->widget.weather.aqiLabel.label, instance->widget.weather.tempLabel.label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);
    lv_obj_set_style_text_font(instance->widget.weather.aqiLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(instance->widget.weather.aqiLabel.label, true);
    lv_label_set_text_fmt(instance->widget.weather.aqiLabel.label, "#59493f AQI ");
    lv_obj_set_style_text_align(instance->widget.weather.aqiLabel.label, LV_TEXT_ALIGN_CENTER, 0);

    instance->widget.weather.aqiLabel.bar = lv_bar_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_opa(instance->widget.weather.aqiLabel.bar, LV_OPA_0, 0);
    lv_obj_set_size(instance->widget.weather.aqiLabel.bar, 38, 8);
    lv_bar_set_range(instance->widget.weather.aqiLabel.bar, 0, 400);
    lv_bar_set_value(instance->widget.weather.aqiLabel.bar, -0, LV_ANIM_ON);
    lv_obj_set_style_radius(instance->widget.weather.aqiLabel.bar, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(instance->widget.weather.aqiLabel.bar, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(instance->widget.weather.aqiLabel.bar, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(instance->widget.weather.aqiLabel.bar, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(instance->widget.weather.aqiLabel.bar, instance->widget.weather.aqiLabel.label, LV_ALIGN_OUT_RIGHT_TOP, 5, 0);
    lv_obj_set_style_bg_opa(instance->widget.weather.aqiLabel.bar, LV_OPA_COVER, LV_PART_INDICATOR);
    lv_obj_set_style_bg_grad_color(instance->widget.weather.aqiLabel.bar, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
    lv_obj_set_style_bg_grad_dir(instance->widget.weather.aqiLabel.bar, LV_GRAD_DIR_HOR, LV_PART_INDICATOR);

    vTaskDelay(50);

    /* Relative humidity */
    instance->widget.weather.humidityLabel.label = lv_label_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_opa(instance->widget.weather.humidityLabel.label, LV_OPA_0, 0);
    lv_obj_align_to(instance->widget.weather.humidityLabel.label, instance->widget.weather.aqiLabel.label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);
    lv_obj_set_style_text_font(instance->widget.weather.humidityLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(instance->widget.weather.humidityLabel.label, true);
    lv_label_set_text_fmt(instance->widget.weather.humidityLabel.label, "#59493f RH  #");
    lv_obj_set_style_text_align(instance->widget.weather.humidityLabel.label, LV_TEXT_ALIGN_CENTER, 0);

    instance->widget.weather.humidityLabel.bar = lv_bar_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_opa(instance->widget.weather.humidityLabel.bar, LV_OPA_0, 0);
    lv_obj_set_size(instance->widget.weather.humidityLabel.bar, 38, 8);
    lv_bar_set_range(instance->widget.weather.humidityLabel.bar, 0, 100);
    lv_bar_set_value(instance->widget.weather.humidityLabel.bar, -50, LV_ANIM_ON);
    lv_obj_set_style_radius(instance->widget.weather.humidityLabel.bar, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(instance->widget.weather.humidityLabel.bar, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(instance->widget.weather.humidityLabel.bar, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(instance->widget.weather.humidityLabel.bar, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(instance->widget.weather.humidityLabel.bar, instance->widget.weather.humidityLabel.label, LV_ALIGN_OUT_RIGHT_TOP, 5, 0);

    vTaskDelay(50);

    instance->widget.weather.icon = lv_img_create(instance->widget.weather.tw_weather);
    lv_obj_align(instance->widget.weather.icon, LV_ALIGN_LEFT_MID, 5, 7);
    instance->widget.weather.icon_buf = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * 8192);
}

static uint8_t _digitOfNumber(int num)
{
    uint8_t digit = 0;
    if (num < 10)
        return 1;
    do {
        num /= 10;
        digit += 1;
    } while (num > 0);
    return digit;
}

static String _numWithUnit(size_t fans)
{
    uint8_t digit = _digitOfNumber(fans);
    uint8_t pd = 3; // 要保留的整数位数
    uint8_t times = 0;
    float ffans = (float)fans;
    String unit;

    if (digit < 5)
        return String(fans);

    if (digit <= 6) {
        pd = 3;
        unit = String("K");
    } else {
        switch (digit) {
        case 7:
            pd = 1;
            break;
        case 8:
            pd = 2;
            break;
        case 9:
            pd = 3;
            break;
        case 10:
            // overflow
        default:
            break;
        }
        unit = String("M");
    }

    times = digit - pd;
    for (size_t i = 0; i < times; i++)
        ffans /= 10;
    
    return (String(ffans) + unit);
}


static bool CheckNoEn(String& str)
{
    for (int ch : str)
        if (ch < 0 || ch > 127)
            return true;
    return false;
}

void HgmGUI::HgmTwView::controllable(bool ca)
{
    // TODO: contollable
    instance->_controllable = ca;
}

bool HgmGUI::HgmTwView::controllable()
{
    return instance->_controllable;
}

static void ShowTime(lv_timer_t* timer)
{
    extern TimeInfo ti;
    static bool secIndicator = true;
    static char* wd[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    struct tm _tm = ti.rtc.getTimeStruct();
    String text1 = "#59493f %02d:%02d#";
    String text2 = "#59493f %02d %02d#";

    if (secIndicator) {
        lv_label_set_text_fmt(instance->widget.time.main_time_label, text1.c_str(), _tm.tm_hour, _tm.tm_min);
        secIndicator = false;
    } else {
        lv_label_set_text_fmt(instance->widget.time.main_time_label, text2.c_str(), _tm.tm_hour, _tm.tm_min);
        secIndicator = true;
    }

    lv_label_set_text_fmt(instance->widget.time.date_label, "#59493f %04d.%02d.%02d %s#",
        _tm.tm_year + 1900,
        _tm.tm_mon + 1,
        _tm.tm_mday,
        wd[_tm.tm_wday]
    );

    lv_img_set_src(instance->widget.time.clock_img, clock_imgs_array[_tm.tm_hour / 2]);
}


void HgmGUI::HgmTwView::update_bili(HgmTwModel::tw_data_t* dat)
{
    if (dat->bd.ufb) {
        instance->widget.bili.face_dsc.data = dat->bd.ufb;
        lv_img_set_src(instance->widget.bili.faceImg, &instance->widget.bili.face_dsc);
    }

    if (CheckNoEn(dat->bd.bn)) {
        lv_obj_set_style_text_font(instance->widget.bili.biliName, &fangpx_10px, 0);
    } else {
        lv_obj_set_style_text_font(instance->widget.bili.biliName, &k12x8_7px, 0);
    }
    lv_label_set_text_fmt(instance->widget.bili.biliName, "#39291f %s#", dat->bd.bn.c_str());
    lv_label_set_text_fmt(instance->widget.bili.biliFans, "#59493f %s#", _numWithUnit(dat->bd.fans).c_str());
}

void HgmGUI::HgmTwView::update_weather(HgmTwModel::tw_data_t* dat)
{
    Serial.println(dat->name);
    lv_label_set_text_fmt(instance->widget.weather.location, "#39291f %s#", dat->name.c_str());
    lv_obj_align_to(instance->widget.weather.location, instance->widget.status_bar.signal.icon, LV_ALIGN_OUT_RIGHT_TOP, 5, -2);

    lv_label_set_text_fmt(instance->widget.weather.tempLabel.label, "#59493f %02d℃#", dat->wd.temp);
    lv_label_set_text_fmt(instance->widget.weather.aqiLabel.label, "#59493f AQI #", dat->wd.aqi);
    lv_label_set_text_fmt(instance->widget.weather.humidityLabel.label, "#59493f R H  #", dat->wd.rh);

    lv_bar_set_value(instance->widget.weather.tempLabel.bar, dat->wd.temp, LV_ANIM_ON);
    lv_bar_set_value(instance->widget.weather.aqiLabel.bar, dat->wd.aqi, LV_ANIM_ON);
    lv_bar_set_value(instance->widget.weather.humidityLabel.bar, dat->wd.rh, LV_ANIM_ON);

    /* Read icon from SPIFFS to show */
    String path = String("/") + String("w_") + String(dat->wd.icon) + String(".png");
    size_t icon_size = Sfu::read(path, instance->widget.weather.icon_buf);
    instance->widget.weather.icon_dsc.data_size = icon_size;
    instance->widget.weather.icon_dsc.header.always_zero = 0;
    instance->widget.weather.icon_dsc.header.w = 40;
    instance->widget.weather.icon_dsc.header.h = 40;
    instance->widget.weather.icon_dsc.header.cf = LV_IMG_CF_RAW_ALPHA;
    instance->widget.weather.icon_dsc.data = instance->widget.weather.icon_buf;
    lv_img_set_src(instance->widget.weather.icon, &instance->widget.weather.icon_dsc);
}

void HgmGUI::HgmTwView::update_time(HgmTwModel::tw_data_t* dat)
{

}

