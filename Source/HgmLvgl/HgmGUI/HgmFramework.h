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

#include "../../Utils/MsgCenter/MsgCenter.h"
#include "HgmSetupView.h"

using namespace msgmanager;

namespace HgmGUI {
#define MAX_VIEWS 32
    class HgmFramework
    {
    public:
        typedef enum _CTL_t {
            SET_DATA,
            BEGIN,
            END
        } CTL_t;

        typedef struct _gui_data_t {
            void* pData;
            CTL_t ctl;
        } gui_data_t;

    private:
        String prev = "";
        String curr = "";

        HgmFramework::gui_data_t _gd;

    public:

        MsgCenter hgmFwCenter;
        Chain guiChain;

        HgmFramework();
        ~HgmFramework();

        void begin();
        void stop();

        bool changeGUI(String name);
        bool changePrev();
        bool changeNext();

        static HgmFramework* getInstance();

    };

};



#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //LVGL_HGM_TOP_FRAMEWORK_H
