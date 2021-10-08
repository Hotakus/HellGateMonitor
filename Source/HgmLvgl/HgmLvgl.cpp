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
#include <Wire.h>

#include "HgmGUI/HgmFramework.h"
#include "LvglPort/lv_port_disp.h"
#include "LvglPort/lv_port_indev.h"

using namespace HGM;
using namespace HgmGUI;

LV_IMG_DECLARE(HGMBG);
LV_IMG_DECLARE(bg_left);
LV_IMG_DECLARE(bg_mid);
LV_IMG_DECLARE(bg_right);

xTaskHandle hgmControlHandle;
xTaskHandle hgmLvglTaskHandle;
xTaskHandle hgmLvglTickHandle;

HgmLvgl* hgmLvgl = new HgmLvgl(HGM_MONITOR_HEIGHT, HGM_MONITOR_WIDTH);

static TFT_eSPI* _lcd = nullptr;

HGM::HgmLvgl::HgmLvgl(int16_t width, int16_t height)
{
    this->_width = width;
    this->_height = height;
    _lcd = new TFT_eSPI(this->_width, this->_height);
    this->lcd = _lcd;

    this->hcl = new HgmControlLogic(Wire1);
    this->hgmFw = new HgmFramework();
}

HgmLvgl::~HgmLvgl()
{
    delete _lcd;
    delete this->hcl;
    delete this->hgmFw;
    vTaskDelete(hgmLvglTaskHandle);
}

/* public function */
/**
 * @brief HGM LVGL begin.
 */
void HGM::HgmLvgl::HgmLvglBegin()
{
    /* LCD init */
    _lcd->begin();
    _lcd->setRotation(1);
    _lcd->fillScreen(TFT_BLACK);

#if HGM_LVGL_USE_DMA == 1
    _lcd->setSwapBytes(true);
    _lcd->initDMA();
#endif

    /* LVGL init */
    lv_init();
    this->HgmLvglDispInit();
    // this->HgmLvglIndevInit();
    // this->HgmLvglFsInit();
    
    /* Create All basic UI */
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_make(0, 0, 0), 0); // Set the bg color as black default
    lv_obj_set_style_bg_img_src(lv_scr_act(), &HGMBG, 0);
    lv_obj_set_scrollbar_mode(lv_scr_act(), LV_SCROLLBAR_MODE_OFF);
    
    // //lv_obj_t* bg = lv_imgbtn_create(lv_scr_act());
    // //lv_imgbtn_set_src(bg, LV_IMGBTN_STATE_RELEASED, &bg_left, &bg_mid, &bg_right);
    // //lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);
    // //lv_obj_set_width(bg, 240);
    
    
    /* Create the basic tasks */
    xTaskCreatePinnedToCore(
        HgmLvglTask,
        "HgmLvglTask",
        2256,
        NULL,
        4,
        &hgmLvglTaskHandle,
        1
    );

#if LV_TICK_CUSTOM != 1
    xTaskCreatePinnedToCore(
        HgmLvglTick,
        "HgmLvglTick",
        768,
        NULL,
        5,
        &hgmLvglTickHandle,
        1
    );
#endif

    // Wire1.begin(21, 22);
    // Wire1.setClock(400 * 1000);
    // xTaskCreatePinnedToCore(
    //     HgmControlCheckTask,
    //     "HgmControlCheckTask",
    //     2048,
    //     this,
    //     5,
    //     &hgmControlHandle,
    //     1
    // );
}

/**
 * @brief Initialize basic UI.
 */
void HGM::HgmLvgl::HgmLvglUIBegin()
{
    this->hgmFw->begin();
}

void HGM::HgmLvgl::HgmLvglTask(void* params)
{
    while (true) {
        lv_timer_handler(); 
        vTaskDelay(HGM_LVGL_TICK);
    }
}

void HGM::HgmLvgl::HgmLvglTick(void* params)
{
    uint16_t tick = *(uint16_t*)params;
    while (true) {
        lv_tick_inc(HGM_LVGL_TICK);
        vTaskDelay(HGM_LVGL_TICK);
    }
}

void HGM::HgmLvgl::HgmControlCheckTask(void* params)
{
    HgmLvgl* hgmLvgl = (HgmLvgl*)params;
    while (true) {
        hgmLvgl->hcl->AnalyzeTask();
        vTaskDelay(250);
    }
}

void HGM::HgmLvgl::HgmLvglDispInit()
{
    lv_port_disp_init(_width, _height, true);
}


void HGM::HgmLvgl::HgmLvglDispFlush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    //size_t end = 0;
    //size_t start = millis();

    _lcd->startWrite();
#if HGM_LVGL_USE_DMA == 0
    _lcd->setAddrWindow(area->x1, area->y1, w, h);
    _lcd->pushColors((uint16_t*)&color_p->full, w * h, true);
#else
    _lcd->pushImageDMA(area->x1, area->y1, w, h, (uint16_t*)disp_drv->draw_buf->buf_act);
    while (_lcd->dmaBusy());
#endif
    _lcd->endWrite();

    //end = millis();
    //Serial.printf("elapse : %d\n", end - start);
    
    lv_disp_flush_ready(disp_drv);
}

void HGM::HgmLvgl::HgmLvglIndevInit()
{
    lv_port_indev_init();
}

void HGM::HgmLvgl::HgmLvglFsInit()
{
    // lv_port_fs_init();
}


