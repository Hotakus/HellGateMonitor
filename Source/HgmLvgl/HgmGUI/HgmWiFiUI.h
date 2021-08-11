/******************************************************************
 * @file hgm_wifi_ui.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 19:36
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/
#ifndef LVGL_HGM_WIFI_UI_H
#define LVGL_HGM_WIFI_UI_H

#include <stdint.h>

namespace HgmGUI {

	class HgmWiFiUI
	{
	private:
		uint8_t tab_id = 0;

	public:
		HgmWiFiUI(uint8_t tab_id);
		~HgmWiFiUI();

		void begin();
	};

};




#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif // __cplusplus

#endif //LVGL_HGM_WIFI_UI_H
