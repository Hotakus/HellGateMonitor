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

/* Assets */
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

void HgmGUI::HgmTwView::begin()
{
    instance->frameCreate();
    instance->widgetCreate();
    instance->animRun();

    showTimeTimer = lv_timer_create(ShowTime, 500, NULL);

    _initTask();

    vTaskDelay(500);
}


void HgmGUI::HgmTwView::stop()
{
    // TODO: delete
    _deInitTask();
}

void HgmGUI::HgmTwView::widgetCreate()
{
    timeWidgetsCreate();
    biliWidgetsCreate();
    weatherWidgetsCreate();
}

void HgmGUI::HgmTwView::animRun()
{
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

    /* Animations */
    instance->widget.anim.anim_book = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    instance->widget.anim.anim_t = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    instance->widget.anim.anim_w = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    instance->widget.anim.anim_tw_expand = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));

    lv_anim_init(instance->widget.anim.anim_book);
    lv_anim_set_var(instance->widget.anim.anim_book, instance->widget.bili.book);
    lv_anim_set_values(instance->widget.anim.anim_book, -97, 2);
    lv_anim_set_early_apply(instance->widget.anim.anim_book, false);
    lv_anim_set_exec_cb(instance->widget.anim.anim_book, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(instance->widget.anim.anim_book, lv_anim_path_ease_in_out);
    lv_anim_set_time(instance->widget.anim.anim_book, 900);

    // anim_tw
    lv_anim_init(instance->widget.anim.anim_t);
    lv_anim_set_var(instance->widget.anim.anim_t, instance->widget.time.tw_time);
    lv_anim_set_values(instance->widget.anim.anim_t, -132, 103);
    lv_anim_set_exec_cb(instance->widget.anim.anim_t, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(instance->widget.anim.anim_t, lv_anim_path_ease_in_out);
    lv_anim_set_time(instance->widget.anim.anim_t, 1000);

    lv_anim_init(instance->widget.anim.anim_w);
    lv_anim_set_var(instance->widget.anim.anim_w, instance->widget.weather.tw_weather);
    lv_anim_set_values(instance->widget.anim.anim_w, -132, 104);
    lv_anim_set_exec_cb(instance->widget.anim.anim_w, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(instance->widget.anim.anim_w, lv_anim_path_ease_in_out);
    lv_anim_set_time(instance->widget.anim.anim_w, 1000);

    lv_anim_init(instance->widget.anim.anim_tw_expand);
    lv_anim_set_var(instance->widget.anim.anim_tw_expand, instance->widget.weather.tw_weather);
    lv_anim_set_values(instance->widget.anim.anim_tw_expand, 6, 63);
    lv_anim_set_exec_cb(instance->widget.anim.anim_tw_expand, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(instance->widget.anim.anim_tw_expand, lv_anim_path_ease_in_out);
    lv_anim_set_time(instance->widget.anim.anim_tw_expand, 500);

    // anim time line
    lv_anim_timeline_t* at = lv_anim_timeline_create();
    lv_anim_timeline_add(at, 0, instance->widget.anim.anim_book);
    lv_anim_timeline_add(at, 800, instance->widget.anim.anim_t);
    lv_anim_timeline_add(at, 800, instance->widget.anim.anim_w);
    lv_anim_timeline_add(at, 1800, instance->widget.anim.anim_tw_expand);
    vTaskDelay(lv_anim_timeline_start(at));
}

static void timeWidgetsCreate()
{
    instance->widget.time.main_time_label = lv_label_create(instance->widget.time.tw_time);
    lv_label_set_recolor(instance->widget.time.main_time_label, true);
    lv_label_set_text(instance->widget.time.main_time_label, "#59493f --:--#");
    lv_obj_align(instance->widget.time.main_time_label, LV_ALIGN_TOP_RIGHT, -3, 10);
    lv_obj_set_style_text_font(instance->widget.time.main_time_label, &k12x8_14px_time, 0);

    instance->widget.time.date_label = lv_label_create(instance->widget.time.tw_time);
    lv_label_set_recolor(instance->widget.time.date_label, true);
    lv_label_set_text(instance->widget.time.date_label, "#59493f 1970.01.01 ---#");
    lv_obj_align(instance->widget.time.date_label, LV_ALIGN_BOTTOM_RIGHT, -8, -5);
    lv_obj_set_style_text_font(instance->widget.time.date_label, &k12x8_6px, 0);

    // clock image
    instance->widget.time.clock_img = lv_img_create(instance->widget.time.tw_time);
    lv_obj_align(instance->widget.time.clock_img, LV_ALIGN_TOP_LEFT, 5, 2);
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
    lv_img_set_src(instance->widget.bili.faceImg, &instance->widget.bili.face_dsc);
    lv_obj_align(instance->widget.bili.faceImg, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_size(instance->widget.bili.faceImg, 64, 64);

    // Bili label
    instance->widget.bili.biliName = lv_label_create(instance->widget.bili.book);
    lv_obj_set_style_text_font(instance->widget.bili.biliName, &k12x8_10px, 0);
    lv_obj_set_width(instance->widget.bili.biliName, 85);
    lv_label_set_recolor(instance->widget.bili.biliName, true);
    lv_label_set_long_mode(instance->widget.bili.biliName, LV_LABEL_LONG_SCROLL_CIRCULAR);
    // TODO: Check chinese
    lv_label_set_text_fmt(instance->widget.bili.biliName, "#59493f %s#", "------");
    lv_obj_set_style_text_align(instance->widget.bili.biliName, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(instance->widget.bili.biliName, LV_ALIGN_BOTTOM_MID, 0, -35);

    instance->widget.bili.biliFans = lv_label_create(instance->widget.bili.book);
    lv_label_set_recolor(instance->widget.bili.biliFans, true);
    lv_label_set_text_fmt(instance->widget.bili.biliFans, "#59493f %s#", "------");
    lv_obj_set_style_text_align(instance->widget.bili.biliFans, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(instance->widget.bili.biliFans, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_set_style_text_font(instance->widget.bili.biliFans, &k12x8_6px, 0);
}

static lv_img_dsc_t w_100;

static void weatherWidgetsCreate()
{
    instance->widget.weather.tempLabel.label = lv_label_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_text_font(instance->widget.weather.tempLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(instance->widget.weather.tempLabel.label, true);
    lv_label_set_text_fmt(instance->widget.weather.tempLabel.label, "#59493f Now:%c%02d℃#", ' ', 0);
    lv_obj_set_style_text_align(instance->widget.weather.tempLabel.label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(instance->widget.weather.tempLabel.label, LV_ALIGN_RIGHT_MID, -3, -8);

    instance->widget.weather.aqiLabel.label = lv_label_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_text_font(instance->widget.weather.aqiLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(instance->widget.weather.aqiLabel.label, true);
    lv_label_set_text_fmt(instance->widget.weather.aqiLabel.label, "#59493f AQI: %02d#", 0);
    lv_obj_set_style_text_align(instance->widget.weather.aqiLabel.label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(instance->widget.weather.aqiLabel.label, instance->widget.weather.tempLabel.label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);

    instance->widget.weather.humidityLabel.label = lv_label_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_text_font(instance->widget.weather.humidityLabel.label, &k12x8_7px, 0);
    lv_label_set_recolor(instance->widget.weather.humidityLabel.label, true);
    lv_label_set_text_fmt(instance->widget.weather.humidityLabel.label, "#59493f RH : %02d%%#", 0);
    lv_obj_set_style_text_align(instance->widget.weather.humidityLabel.label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(instance->widget.weather.humidityLabel.label, instance->widget.weather.aqiLabel.label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);

    // TODO:
    instance->widget.weather.batLabel = lv_label_create(instance->widget.weather.tw_weather);
    lv_obj_set_style_text_align(instance->widget.weather.batLabel, LV_TEXT_ALIGN_RIGHT, 0);
    lv_label_set_text_fmt(instance->widget.weather.batLabel, "%d%%%s", 100, LV_SYMBOL_BATTERY_2);
    lv_obj_align_to(instance->widget.weather.batLabel, instance->widget.weather.tempLabel.label, LV_ALIGN_OUT_TOP_RIGHT, 0, -2);

    instance->widget.weather.icon = lv_img_create(instance->widget.weather.tw_weather);
    instance->widget.weather.icon_buf = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * 8192);
    lv_obj_align(instance->widget.weather.icon, LV_ALIGN_LEFT_MID, 5, 7);
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
        if (ch < 0 || ch > 127)
            return true;
    return false;
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
        lv_label_set_text_fmt(instance->widget.bili.biliName, "#59493f %s#", dat->bd.uid.c_str());
    } else {
        lv_label_set_text_fmt(instance->widget.bili.biliName, "#59493f %s#", dat->bd.bn.c_str());
    }
    lv_label_set_text_fmt(instance->widget.bili.biliFans, "#59493f %s#", _numWithUnit(dat->bd.fans).c_str());
}

void HgmGUI::HgmTwView::update_weather(HgmTwModel::tw_data_t* dat)
{
    Serial.println(dat->wd.temp);
    if (dat->wd.temp >= 0)
        lv_label_set_text_fmt(instance->widget.weather.tempLabel.label, "#59493f Now:%s%02d℃#", " ", dat->wd.temp);
    else
        lv_label_set_text_fmt(instance->widget.weather.tempLabel.label, "#59493f Now:%s%02d℃#", "-", dat->wd.temp);

    lv_label_set_text_fmt(instance->widget.weather.aqiLabel.label, "#59493f AQI: %02d#", dat->wd.aqi);
    lv_label_set_text_fmt(instance->widget.weather.humidityLabel.label, "#59493f RH : %02d%%#", dat->wd.rh);

    String path = String("/") + String("w_") + String(dat->wd.icon) + String(".png");
    size_t icon_size = Sfu::read(path, instance->widget.weather.icon_buf, 8192);

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

