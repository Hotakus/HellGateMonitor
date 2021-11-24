/******************************************************************
 * @file HgmSetupView.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/18 23:17
 * @copyright Copyright (c) 2021/8/18
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMSETUPUI_H
#define HELLGATEMONITOR_HGMSETUPUI_H

#include "../../Utils/MsgCenter/MsgCenter.h"
#include "../../LvglSrc/lvgl/lvgl.h"
#include <TJpg_Decoder.h>

using namespace msgmanager;

namespace HgmGUI {

    // HGM's components' type
    typedef enum _HgmComponentType
    {
        HGM_COMPONENT_BT,
        HGM_COMPONENT_SPIFFS,
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

    class HgmSetupView
    {
    private:
        
        subscriber_t setup_subs;
        void componentInitDone(); 
        
    public:
        bool isEnd;
        MsgCenter mc;
        static void ctl(HgmComponent* component);

        struct _widget {
            lv_obj_t* pb;
            lv_obj_t* logo;
            lv_obj_t* prevCheckLabel;
            lv_obj_t* curCheckLabel;
        } widget;

        struct _frtos {
            QueueHandle_t msgBox;
            TaskHandle_t taskHandle;
        } frtos;

        String prevText = "";
        String curText = "";

        HgmSetupView();
        ~HgmSetupView();

        void begin();
        void end();
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
