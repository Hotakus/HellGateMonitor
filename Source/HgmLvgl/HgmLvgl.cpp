/******************************************************************
 * @file HgmLvgl.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/10 11:21
 * @copyright Copyright (c) 2021/8/10
*******************************************************************/


#include <Arduino.h>
#include "HgmLvgl.h"
#include "./HgmGUI/hgm_top_framework.h"


using namespace HGM;

static TFT_eSPI* lcd = nullptr;

HGM::HgmLvgl::HgmLvgl(int16_t w, int16_t h)
{
	lcd = new TFT_eSPI();
}

HgmLvgl::~HgmLvgl()
{
	delete lcd;
	vTaskDelete(&this->hgmLvglTaskHandle);
}

/* public function */
void HGM::HgmLvgl::HgmLvglBegin()
{
	/* LCD init */
	lcd->begin();
	lcd->fillScreen(TFT_RED);

	/* LVGL init */
	lv_init();
	this->HgmLvglDispInit();
	this->HgmLvglIndevInit();
	this->HgmLvglFsInit();

	xTaskCreate(
		HgmLvglTask,
		"HgmLvglTask",
		4096,
		&lvTick,
		5,
		&this->hgmLvglTaskHandle
	);
}

/**
 * @brief Initialize basic UI.
 */
void HGM::HgmLvgl::HgmLvglUIBegin()
{
	//hgm_framework_init();
	static lv_obj_t* btn = lv_btn_create(lv_scr_act());
	lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
}

/* private function */
void HGM::HgmLvgl::HgmLvglTask(void* params)
{
	uint16_t tick = *(uint16_t*)params;
	while (true) {
		lv_tick_inc(tick);
		lv_timer_handler(); /* let the GUI do its work */
		vTaskDelay(tick);		// use FreeRTOS
	}
}

void HGM::HgmLvgl::HgmLvglDispInit()
{
	/*-----------------------------------
	 * Register the display in LVGL
	 *----------------------------------*/
	static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
	lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

	/*Set up the functions to access to your display*/
	/*Set the resolution of the display*/
	disp_drv.hor_res = HGM_MONITOR_WIDTH;
	disp_drv.ver_res = HGM_MONITOR_HEIGHT;

	/*Used to copy the buffer's content to the display*/
	disp_drv.flush_cb = HgmLvglDispFlush;

#define BUF_METHOD 0
#if BUF_METHOD == 0
	/* Example for 1) */
	static lv_disp_draw_buf_t draw_buf_dsc_1;
	static lv_color_t buf_1[HGM_MONITOR_WIDTH * 10];                          /*A buffer for 10 rows*/
	lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, HGM_MONITOR_WIDTH * 10);   /*Initialize the display buffer*/
	/*Set a display buffer*/
	disp_drv.draw_buf = &draw_buf_dsc_1;
#elif BUF_METHOD == 1
	/* Example for 2) */
	static lv_disp_draw_buf_t draw_buf_dsc_2;
	static lv_color_t buf_2_1[HGM_MONITOR_WIDTH * 10];                        /*A buffer for 10 rows*/
	static lv_color_t buf_2_2[HGM_MONITOR_WIDTH * 10];                        /*An other buffer for 10 rows*/
	lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, HGM_MONITOR_WIDTH * 10);   /*Initialize the display buffer*/
	disp_drv.draw_buf = &draw_buf_dsc_2;
#elif BUF_METHOD == 2
	* Example for 3) also set disp_drv.full_refresh = 1 below * /
	static lv_disp_draw_buf_t draw_buf_dsc_3;
	static lv_color_t buf_3_1[HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT];            /*A screen sized buffer*/
	static lv_color_t buf_3_2[HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT];            /*An other screen sized buffer*/
	lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2, HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT);   /*Initialize the display buffer*/
	disp_drv.full_refresh = 1;
	disp_drv.draw_buf = &draw_buf_dsc_3;
#endif // 0


	/* Fill a memory array with a color if you have GPU.
	 * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
	 * But if you have a different GPU you can use with this callback.*/
	 //disp_drv.gpu_fill_cb = gpu_fill;

	 /*Finally register the driver*/
	lv_disp_drv_register(&disp_drv);
}
void HGM::HgmLvgl::HgmLvglDispFlush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
	uint32_t w = (area->x2 - area->x1 + 1);
	uint32_t h = (area->y2 - area->y1 + 1);

	lcd->startWrite();
	lcd->setAddrWindow(area->x1, area->y1, w, h);
	lcd->pushColors((uint16_t*)&color_p->full, w * h, true);
	lcd->endWrite();

	lv_disp_flush_ready(disp_drv);
}


void HGM::HgmLvgl::HgmLvglIndevInit()
{
}

void HGM::HgmLvgl::HgmLvglFsInit()
{
}
