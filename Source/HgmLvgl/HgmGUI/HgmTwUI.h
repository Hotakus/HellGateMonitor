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

#include "../../LvglSrc/lvgl/lvgl.h"

#include <Arduino.h>

namespace HgmGUI {
    class HgmTwUI
    {
    private:
 
    public:
        struct _widget {
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
                lv_obj_t* tw_weather = NULL;
                lv_obj_t* wifiLabel = NULL;
                lv_obj_t* batLabel = NULL;;

                // 复合控件
                struct _weatherInfoLabel {
                    lv_obj_t* label;        // label主体
                    lv_obj_t* bar;          // 指示条
                } tempLabel, aqiLabel, humidityLabel;
            } weather;

            struct _animation {
                lv_anim_t* anim_book = NULL;
                lv_anim_t* anim_t = NULL;
                lv_anim_t* anim_w = NULL;
                lv_anim_t* anim_tw_expand = NULL;
            } anim;
        } widget;
        

        HgmTwUI();
        ~HgmTwUI();

        void begin();
        void stop();

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
