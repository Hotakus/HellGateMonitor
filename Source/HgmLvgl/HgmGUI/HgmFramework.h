/******************************************************************
 * @file hgm_top_framework.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 18:39
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/
#ifndef LVGL_HGM_TOP_FRAMEWORK_H
#define LVGL_HGM_TOP_FRAMEWORK_H

#include "../../LvglSrc/lvgl/lvgl.h"
#include "HgmWiFiUI.h"


namespace HgmGUI {

#define TAB_NUMBER 3

	class HgmFramework
	{
	private:

	public:
		HgmWiFiUI* hgmWiFiUI = nullptr;

		HgmFramework();
		~HgmFramework();

		void begin();
	};

};



#ifdef __cplusplus
extern "C" {
#endif

extern lv_obj_t * hgmFwTabview;
extern lv_obj_t * hgmTabList[TAB_NUMBER];

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //LVGL_HGM_TOP_FRAMEWORK_H
