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

#include "HgmSetupView.h"
#include "HgmViews.h"

namespace HgmGUI {
#define MAX_VIEWS 32
    class HgmFramework
    {
    private:
        HgmViews* prevView = NULL;
        HgmViews* currView = NULL;
    public:
        HgmViews** viewsGroup;

        HgmFramework();
        ~HgmFramework();

        void begin();
        void stop();

        bool RegisterNewView(String viewName, vcb_t vcb, vdb_t vdb);
        bool UnRegisterView(String viewName);

        bool ChangeView(String viewName);
    };

};



#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //LVGL_HGM_TOP_FRAMEWORK_H
