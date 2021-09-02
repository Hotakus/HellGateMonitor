/******************************************************************
 * @file lv_port_disp.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/10 16:48
 * @copyright Copyright (c) 2021/8/10
*******************************************************************/
/*********************
 *      INCLUDES
 *********************/

#include "../../LvglSrc/lvgl/lvgl.h"
#include "lv_port_disp.h"
#include "../HgmLvgl.h"

using namespace HGM;

#define BUF_METHOD 0

void lv_port_disp_init(int16_t width, int16_t height, bool hwSwap)
{

    int16_t _width = hwSwap ? height : width;
    int16_t _height = hwSwap ? width : height;

    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/
    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/
    /*Set the resolution of the display*/
    disp_drv.hor_res = _width;
    disp_drv.ver_res = _height;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = HGM::HgmLvgl::HgmLvglDispFlush;

#if BUF_METHOD == 0
    /* Example for 1) */
    static lv_disp_draw_buf_t draw_buf_dsc_1;
    static lv_color_t buf_1[HGM_MONITOR_WIDTH * 30];
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, HGM_MONITOR_WIDTH * 30);   /*Initialize the display buffer*/
    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_1;
#elif BUF_METHOD == 1
    /* Example for 2) */
    static lv_disp_draw_buf_t draw_buf_dsc_2;
    static lv_color_t buf_2_1[HGM_MONITOR_WIDTH * 10];
    static lv_color_t buf_2_2[HGM_MONITOR_WIDTH * 10];
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, _width * 10);
    disp_drv.draw_buf = &draw_buf_dsc_2;
#elif BUF_METHOD == 2
    /* Example for 3) also set disp_drv.full_refresh = 1 below */
    static lv_disp_draw_buf_t draw_buf_dsc_3;
    static lv_color_t* buf_3_1[HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT];
    static lv_color_t* buf_3_2[HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT];
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
