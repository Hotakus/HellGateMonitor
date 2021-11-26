/******************************************************************
 * @file HgmTwUI.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/31 22:54
 * @copyright Copyright (c) 2021/8/31
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMTWUI_H
#define HELLGATEMONITOR_HGMTWUI_H

#include "../../../LvglSrc/lvgl/lvgl.h"
#include "HgmTwModel.h"
#include <Arduino.h>

namespace HgmGUI {
    class HgmTwView
    {
    private:
        bool _controllable = false;

        void frameCreate();
        void widgetCreate();
        void animCreate();

        void animDestroy();
        void widgetDestroy();
        void frameDestroy();

        void status_bar_create();
    public:
        struct _widget {
            lv_group_t group;
            lv_style_t style_pr;
            lv_obj_t* next_btn = NULL;
            lv_obj_t* prev_btn = NULL;

            struct _biliWidget {
                lv_img_dsc_t face_dsc;
                lv_obj_t* book = NULL;
                lv_obj_t* faceImg = NULL;
                lv_obj_t* biliName = NULL;
                lv_obj_t* biliFans = NULL;
            } bili;

            struct _timeWidget {
                lv_obj_t* tw_time = NULL;
                lv_obj_t* main_time_label = NULL;
                lv_obj_t* date_label = NULL;
                lv_obj_t* clock_img = NULL;
            } time;

            struct _weatherWidget {
                lv_img_dsc_t icon_dsc;
                uint8_t* icon_buf;
                lv_obj_t* tw_weather = NULL;
                lv_obj_t* icon = NULL;
                lv_obj_t* wifiLabel = NULL;
                lv_obj_t* batLabel = NULL;
                lv_obj_t* location = NULL;

                // 复合控件
                struct _weatherInfoLabel {
                    lv_obj_t* label;        // label主体
                    lv_obj_t* bar;          // 指示条
                } tempLabel, aqiLabel, humidityLabel;
            } weather;

            struct _status_bar {
                lv_obj_t* bg;
                struct _bat_icon {
                    lv_obj_t* icon;
                    uint8_t value;  // %
                } battery;

                struct _signal_icon {
                    lv_obj_t* icon;
                    uint8_t value;
                } signal;
            } status_bar;

            struct _animation {
                lv_anim_timeline_t* at;
                lv_anim_t anim_book;
                lv_anim_t anim_t;
                lv_anim_t anim_w;
                lv_anim_t anim_tw_expand;
            } anim;
        } *widget;

        HgmTwView();
        ~HgmTwView();

        void begin();
        void end();

        static void controllable(bool ca);
        static bool controllable();
        static void update_bili(HgmTwModel::tw_data_t* dat);
        static void update_weather(HgmTwModel::tw_data_t* dat);
        static void update_time(HgmTwModel::tw_data_t* dat);

    };

};


#ifdef __cplusplus
extern "C" {
#endif

    /*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMTWUI_H
