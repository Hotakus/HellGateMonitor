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

                lv_obj_t* time_label;
                lv_obj_t* next_btn;

            } status_bar;
        } widget;

        HgmSRView();
        ~HgmSRView();

        void begin();
        void end();

        void update_screen(HardwareRequest* hrr);
    };
}

#endif //HELLGATEMONITOR_HGMSRVIEW_H
