/******************************************************************
 * @file hgm_top_framework.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 18:39
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/
#ifndef LVGL_HGM_FRAMEWORK_H
#define LVGL_HGM_FRAMEWORK_H

#include "../../LvglSrc/lvgl/lvgl.h"
#include "HgmSetupUI.h"


namespace HgmGUI {

    typedef enum _HgmGuiType {
        HGM_GUI_NULL,

        HGM_GUI_HARDWARE_MONITOR,

        HGM_GUI_MISC,
        HGM_GUI_PROJECTION,
    } HgmGuiType;

    class HgmFramework
    {
    private:
    public:
        HgmFramework();
        ~HgmFramework();

        void begin();
        void stop();

        static void changeUI(HgmGuiType gui);

        static void setDefaultGui(HgmGuiType def = HGM_GUI_MISC);
        static HgmGuiType getDefaultGui();
        static HgmGuiType getCurrentGui();
    };

};



#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //LVGL_HGM_TOP_FRAMEWORK_H
