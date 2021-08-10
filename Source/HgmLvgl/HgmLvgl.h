/******************************************************************
 * @file HgmLvgl.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/10 11:21
 * @copyright Copyright (c) 2021/8/10
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMLVGL_H
#define HELLGATEMONITOR_HGMLVGL_H

#include <TFT_eSPI.h>
#include "../LvglSrc/lvgl/lvgl.h"

namespace HGM {
#define HGM_MONITOR_WIDTH  240
#define HGM_MONITOR_HEIGHT 320

	class HgmLvgl
	{
	private:
		/*  */
		xTaskHandle hgmLvglTaskHandle;
		int16_t lvTick = 50;

		void HgmLvglDispInit();
		void HgmLvglIndevInit();
		void HgmLvglFsInit();

		static void HgmLvglDispFlush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p);
		static void HgmLvglTask(void* params);
	public:

		HgmLvgl(int16_t w = HGM_MONITOR_WIDTH, int16_t h = HGM_MONITOR_HEIGHT);
		~HgmLvgl();

		void HgmLvglBegin();
		void HgmLvglUIBegin();
	};
};

#ifdef __cplusplus
extern "C" {
#endif

	/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !HELLGATEMONITOR_HGMLVGL_H
