/******************************************************************
 * @file HgmSRView.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/12/1 10:57
 * @copyright Copyright (c) 2021/12/1
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMSRVIEW_H
#define HELLGATEMONITOR_HGMSRVIEW_H

#include "../../../LvglSrc/lvgl/lvgl.h"
#include "../../../HgmApp/HardwareInfoRecv/HardwareRequest.h"
#include "../../../HgmApp/ScreenRecv/ScreenRecv.h"

using namespace HgmApplication;

namespace HgmGUI {
    class HgmSRView {
    private:
        void frameCreate();
        void widgetCreate();
        void animCreate();

        void animDestroy();
        void widgetDestroy();
        void frameDestroy();
    public:
        struct _widget {
            lv_style_t style_pr;
            lv_group_t* group;

            lv_obj_t* fps_label;

            struct {
                lv_obj_t* self;
                lv_img_dsc_t dsc;
                uint8_t* buf;
            } img;

            struct {
                struct {
                    lv_obj_t* self;
                    lv_obj_t* conn_status;
                    lv_obj_t* ip_label;
                    lv_obj_t* port_label;
                } frame;
                lv_obj_t* btn;
                uint8_t value;
                lv_anim_t fa;
            } prompt;

            lv_obj_t* prev_btn;
            lv_obj_t* next_btn;

        } widget;

        HgmSRView();
        ~HgmSRView();

        void begin();
        void end();

        void update_screen(sr_t* sr);
        void update_status(bool ds);
    };
}

#endif //HELLGATEMONITOR_HGMSRVIEW_H
