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



// TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
// 
// /*Change to your screen resolution*/
// static const uint32_t screenWidth = 480;
// static const uint32_t screenHeight = 320;
// 
// static lv_disp_draw_buf_t draw_buf;
// static lv_color_t buf[screenWidth * 10];
// 
// #if LV_USE_LOG != 0
// /* Serial debugging */
// void my_print(lv_log_level_t level, const char* file, uint32_t line, const char* fn_name, const char* dsc)
// {
//     Serial.printf("%s(%s)@%d->%s\r\n", file, fn_name, line, dsc);
//     Serial.flush();
// }
// #endif
// 
// /* Display flushing */
// void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
// {
//     uint32_t w = (area->x2 - area->x1 + 1);
//     uint32_t h = (area->y2 - area->y1 + 1);
// 
//     tft.startWrite();
//     tft.setAddrWindow(area->x1, area->y1, w, h);
//     tft.pushColors((uint16_t*)&color_p->full, w * h, true);
//     tft.endWrite();
// 
//     lv_disp_flush_ready(disp);
// }
// 
// void setup()
// {
//     Serial.begin(115200); /* prepare for possible serial debug */
//     Serial.println("Hello Arduino! (V8.0.X)");
//     Serial.println("I am LVGL_Arduino");
// 
//     lv_init();
// 
// #if LV_USE_LOG != 0
//     lv_log_register_print_cb(my_print); /* register print function for debugging */
// #endif
// 
//     tft.begin();          /* TFT init */
//     tft.setRotation(1); /* Landscape orientation, flipped */
// 
//     lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);
// 
//     /*Initialize the display*/
//     static lv_disp_drv_t disp_drv;
//     lv_disp_drv_init(&disp_drv);
//     /*Change the following line to your display resolution*/
//     disp_drv.hor_res = screenWidth;
//     disp_drv.ver_res = screenHeight;
//     disp_drv.flush_cb = my_disp_flush;
//     disp_drv.draw_buf = &draw_buf;
//     lv_disp_drv_register(&disp_drv);
// 
//     /*Initialize the (dummy) input device driver*/
//     static lv_indev_drv_t indev_drv;
//     lv_indev_drv_init(&indev_drv);
//     indev_drv.type = LV_INDEV_TYPE_POINTER;
//     indev_drv.read_cb = my_touchpad_read;
//     lv_indev_drv_register(&indev_drv);
// 
// #if 1
//     /* Create simple label */
//     lv_obj_t* label = lv_label_create(lv_scr_act());
//     lv_label_set_text(label, "Hello Arduino! (V8.0.X)");
//     lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
// #else
//     /* Try an example from the lv_examples Arduino library
//        make sure to include it as written above.
//     lv_example_btn_1();
//     */
// 
//     // uncomment one of these demos
//     // lv_demo_widgets();            // OK
//     // lv_demo_benchmark();          // OK
//     // lv_demo_keypad_encoder();     // works, but I haven't an encoder
//     // lv_demo_music();              // NOK
//     // lv_demo_printer();
//     // lv_demo_stress();             // seems to be OK
// #endif
//     Serial.println("Setup done");
// }
// 
// void loop()
// {
//     lv_timer_handler(); /* let the GUI do its work */
//     delay(5);
// }
