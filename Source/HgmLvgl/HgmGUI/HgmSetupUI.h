/******************************************************************
 * @file HgmSetupUI.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/18 23:17
 * @copyright Copyright (c) 2021/8/18
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMSETUPUI_H
#define HELLGATEMONITOR_HGMSETUPUI_H

#include "../../LvglSrc/lvgl/lvgl.h"
#include <TJpg_Decoder.h>

namespace HgmGUI {

    // HGM's components' type
    typedef enum _HgmComponentType
    {
        HGM_COMPONENT_BT,
        HGM_COMPONENT_CONFIG_FILE,
        HGM_COMPONENT_WIFI,
        HGM_COMPONENT_NET_TIME,
        HGM_COMPONENT_WEATHER,
        HGM_COMPONENT_BILIBILI,

        HGM_COMPONENT_DONE,

        HGM_COMPONENT_NULL,
    } HgmComponentType;

    // HGM's components
    typedef struct _HgmComponent
    {
        HgmComponentType type;
        bool curStatus;			// Component's current status
        bool waitStatus;		// Component's wait status
    } HgmComponent;

    class HgmSetupUI
    {
    private:

    public:

        struct _frtos {
            QueueHandle_t msgBox;
            TaskHandle_t taskHandle;
        } frtos;

        struct _widget {
            lv_obj_t* pb;
            lv_obj_t* logo;
            lv_obj_t* prevCheckLabel;
            lv_obj_t* curCheckLabel;
            lv_style_t clStyle;
        } widget;

        String prevText = "";
        String curText = "";

        HgmSetupUI();
        ~HgmSetupUI();

        void begin();

        // Be call for other class
        static void componentControl(HgmComponent* component);
        static void componentInitDone();
    };

};



#ifdef __cplusplus
extern "C" {
#endif

    /*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMSETUPUI_H
