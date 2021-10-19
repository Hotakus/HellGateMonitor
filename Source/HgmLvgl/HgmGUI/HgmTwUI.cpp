/******************************************************************
 * @file HgmTwUI.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/31 22:54
 * @copyright Copyright (c) 2021/8/31
*******************************************************************/
#include "HgmTwUI.h"
#include "../HgmLvgl.h"
#include "../../HgmApp/TimeInfo/TimeInfo.h"
#include "../../HgmApp/BiliInfoRecv/BiliInfoRecv.h"
#include "../../HgmApp/WeatherInfo/WeatherInfo.h"

#include <Arduino.h>
#include <ESP32Time.h>
#include <WiFi.h>


using namespace HgmApplication;
using namespace HgmGUI;
using namespace HGM;

/* Assets */
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

static lv_obj_t* clock_img = NULL;


// TODO: Add btn
LV_IMG_DECLARE(tw_t);
LV_IMG_DECLARE(tw_w);
LV_IMG_DECLARE(book_left);
LV_IMG_DECLARE(book_right);
LV_IMG_DECLARE(book_mid);

LV_FONT_DECLARE(k12x8_6px);
LV_FONT_DECLARE(k12x8_7px);
LV_FONT_DECLARE(k12x8_8px);
LV_FONT_DECLARE(k12x8_10px);
LV_FONT_DECLARE(k12x8_14px_time);
LV_FONT_DECLARE(k12x8_16px_time);
LV_FONT_DECLARE(k12x8_24px_time);

static lv_img_dsc_t face_dsc;
static lv_obj_t* faceImg = NULL;

static lv_obj_t* tw_time = NULL;
static lv_obj_t* tw_weather = NULL;
static lv_obj_t* book = NULL;

static lv_obj_t* main_time_label = NULL;
static lv_obj_t* date_label = NULL;

static lv_obj_t* biliName = NULL;
static lv_obj_t* biliFans = NULL;
static lv_obj_t* wifiLabel = NULL;
static lv_obj_t* batLabel;

static lv_anim_t* anim_book = NULL;
static lv_anim_t* anim_t = NULL;
static lv_anim_t* anim_w = NULL;
static lv_anim_t* anim_tw_expand = NULL;

static lv_timer_t* showTimeTimer = NULL;
static lv_timer_t* showBiliTimer = NULL;
static lv_timer_t* showWeatherTimer = NULL;


static void ShowTime(lv_timer_t* timer);
static void ShowWeather(lv_timer_t* timer);

extern TimeInfo ti;
extern BiliInfoRecv bili;
extern WeatherInfo weatherInfo;
extern WeatherData weatherDataToday;

static void weatherInfoJump();


HgmTwUI::HgmTwUI()
{

}

HgmTwUI::~HgmTwUI()
{

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

void HgmGUI::HgmTwUI::begin()
{

    _initTask();

    // To avoid crush when LVGL running busy
    vTaskDelay(500);

    tw_time = lv_img_create(lv_scr_act());
    lv_obj_align(tw_time, LV_ALIGN_TOP_LEFT, -132, 6);
    lv_img_set_src(tw_time, &tw_t);

    tw_weather = lv_img_create(lv_scr_act());
    lv_obj_align(tw_weather, LV_ALIGN_TOP_LEFT, -132, 6);
    lv_img_set_src(tw_weather, &tw_w);

    book = lv_imgbtn_create(lv_scr_act());
    lv_obj_align(book, LV_ALIGN_LEFT_MID, -97, 0);
    lv_imgbtn_set_src(book, LV_IMGBTN_STATE_RELEASED, &book_left, &book_mid, &book_right);
    lv_obj_set_width(book, 97);

    /* Label */
    main_time_label = lv_label_create(tw_time);
    lv_label_set_recolor(main_time_label, true);
    lv_label_set_text(main_time_label, "#59493f --:--#");
    lv_obj_align(main_time_label, LV_ALIGN_TOP_RIGHT, -3, 10);
    lv_obj_set_style_text_font(main_time_label, &k12x8_14px_time, 0);

    date_label = lv_label_create(tw_time);
    lv_label_set_recolor(date_label, true);
    lv_label_set_text(date_label, "#59493f 1970.01.01 ---#");
    lv_obj_align(date_label, LV_ALIGN_BOTTOM_RIGHT, -8, -5);
    lv_obj_set_style_text_font(date_label, &k12x8_6px, 0);



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
    showTimeTimer = lv_timer_create(ShowTime, 500, NULL);

    // clock image
    clock_img = lv_img_create(tw_time);
    lv_obj_align(clock_img, LV_ALIGN_TOP_LEFT, 5, 2);


    // Face
    face_dsc.header.always_zero = 0;
    face_dsc.header.w = 64;
    face_dsc.header.h = 64;
    face_dsc.data_size = 4096 * 2;
    face_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
    face_dsc.data = (uint8_t*)BiliInfoRecv::getUserFaceBitmap();
    faceImg = lv_img_create(book);
    lv_img_set_src(faceImg, &face_dsc);
    lv_obj_align(faceImg, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_size(faceImg, 64, 64);

    // Bili label
    biliName = lv_label_create(book);
    lv_obj_set_style_text_font(biliName, &k12x8_10px, 0);
    lv_obj_set_width(biliName, 85);
    lv_label_set_recolor(biliName, true);
    lv_label_set_long_mode(biliName, LV_LABEL_LONG_SCROLL_CIRCULAR);
    // TODO: Check chinese
    lv_label_set_text_fmt(biliName, "#59493f %s#", BiliInfoRecv::getUserName().c_str());
    lv_obj_set_style_text_align(biliName, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(biliName, LV_ALIGN_BOTTOM_MID, 0, -35);

    biliFans = lv_label_create(book); 
    lv_label_set_recolor(biliFans, true);
    lv_label_set_text_fmt(biliFans, "#59493f %d#", BiliInfoRecv::getFollower());
    lv_obj_set_style_text_align(biliFans, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(biliFans, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_style_text_font(biliFans, &k12x8_6px, 0);

    weatherInfoJump();
    showWeatherTimer = lv_timer_create(ShowWeather, 10000, NULL);

    wifiLabel = lv_label_create(tw_weather);
    lv_obj_set_style_opa(wifiLabel, LV_OPA_0, 0);
    lv_label_set_text(wifiLabel, LV_SYMBOL_WIFI);
    lv_obj_align(wifiLabel, LV_ALIGN_TOP_LEFT, 3, 3);
}


void HgmGUI::HgmTwUI::stop()
{
    // TODO: delete
    _deInitTask();
}


typedef struct _wLabelObj {
    lv_obj_t* label;        // label主体
    lv_obj_t* bar;          // 指示条
} wLabelObj;

wLabelObj tempLabel;
wLabelObj aqiLabel;
wLabelObj humidityLabel;

static void weatherUpdate()
{
    if (weatherDataToday.temp >= 0)
        lv_label_set_text_fmt(tempLabel.label, "#59493f Now:%s%02d℃#", " ", weatherDataToday.temp);
    else
        lv_label_set_text_fmt(tempLabel.label, "#59493f Now:%s%02d℃#", "-", weatherDataToday.temp);

    lv_label_set_text_fmt(aqiLabel.label, "#59493f AQI: %02d#", weatherDataToday.aqi);
    lv_label_set_text_fmt(humidityLabel.label, "#59493f RH : %02d%%#", weatherDataToday.humidity);
}

static void weatherInfoJump()
{
    tempLabel.label = lv_label_create(tw_weather);
    lv_obj_set_style_text_font(tempLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(tempLabel.label, true);
    lv_label_set_text_fmt(tempLabel.label, "#59493f Now:%c%02d℃#", ' ', 0);
    lv_obj_set_style_text_align(tempLabel.label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(tempLabel.label, LV_ALIGN_RIGHT_MID, -3, -8);

    aqiLabel.label = lv_label_create(tw_weather);
    lv_obj_set_style_text_font(aqiLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(aqiLabel.label, true);
    lv_label_set_text_fmt(aqiLabel.label, "#59493f AQI: %02d#", 72);
    lv_obj_set_style_text_align(aqiLabel.label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(aqiLabel.label, tempLabel.label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);

    humidityLabel.label = lv_label_create(tw_weather);
    lv_obj_set_style_text_font(humidityLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(humidityLabel.label, true);
    lv_label_set_text_fmt(humidityLabel.label, "#59493f RH : %02d%%#", 80);
    lv_obj_set_style_text_align(humidityLabel.label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(humidityLabel.label, aqiLabel.label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);

    batLabel = lv_label_create(tw_weather);
    lv_obj_set_style_text_align(batLabel, LV_TEXT_ALIGN_RIGHT, 0);
    lv_label_set_text_fmt(batLabel, "%d%%%s", 100, LV_SYMBOL_BATTERY_2);
    lv_obj_align_to(batLabel, tempLabel.label, LV_ALIGN_OUT_TOP_RIGHT, 0, -2);

}


static void ShowWeather(lv_timer_t* timer)
{
    weatherUpdate();
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
    uint8_t pd = 0; // 要保留的整数位数
    uint8_t times = 0;
    float ffans = (float)fans;

    if (digit < 5)
        return String(fans);

    switch (digit)
    {
    case 5:
    case 6: {   // 百万以下
        pd = 3;
        times = digit - pd;
        for (size_t i = 0; i < times; i++)
            ffans /= 10;
        return (String(ffans) + String("K"));
    }
    case 7:
    case 8:
    case 9: {   // 百万及以上
        // TODO: 
    }
    default:
        break;
    }

}


static bool CheckNoEn(String& str)
{
    for (int ch : str)
        if (ch < 0 || ch > 127) return true;
    return false;
}


static void ShowBili()
{
    face_dsc.data = (uint8_t*)BiliInfoRecv::getUserFaceBitmap();
    lv_img_set_src(faceImg, &face_dsc);

    if (CheckNoEn(BiliInfoRecv::getUserName())) {
        lv_label_set_text_fmt(biliName, "#59493f %s#", BiliInfoRecv::GetUID().c_str());
    } else {
        lv_label_set_text_fmt(biliName, "#59493f %s#", BiliInfoRecv::getUserName().c_str());
    }

    lv_label_set_text_fmt(biliFans, "#59493f %s#", _numWithUnit(BiliInfoRecv::getFollower()).c_str());
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

    lv_img_set_src(clock_img, clock_imgs_array[_tm.tm_hour / 2]);

    if (WiFi.isConnected())
        lv_obj_set_style_opa(wifiLabel, LV_OPA_70, 0);
    else
        lv_obj_set_style_opa(wifiLabel, LV_OPA_0, 0);

    ShowBili();
}



