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

HGM::HgmLvgl::HgmLvgl(int16_t w, int16_t h)
{
	this->lcd = new TFT_eSPI();
}

HgmLvgl::~HgmLvgl()
{
	delete this->lcd;
}

void HGM::HgmLvgl::HgmLvglBegin()
{
	/* LCD init */
	this->lcd->begin();
	this->lcd->fillScreen(TFT_RED);

	/* LVGL init */
    lv_init();

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
