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

HgmLvgl* hgmLvgl = new HgmLvgl(135, 240);

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
    vTaskDelete(&this->hgmLvglTaskHandle);
}


/* public function */
void HGM::HgmLvgl::HgmLvglBegin()
{
    /* LCD init */
    _lcd->begin();
    _lcd->setRotation(1);
    _lcd->fillScreen(TFT_YELLOW);

    /* Hgm Control init */
    this->hcl->HgmControlBegin();
    Serial.printf("0x%X\n", this->hcl->imu->whoAmI());

    /* LVGL init */
    lv_init();
    this->HgmLvglDispInit();
    // this->HgmLvglIndevInit();
    // this->HgmLvglFsInit();

    /* Create All basic UI */
    // this->HgmLvglUIBegin();
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_make(0, 0, 0), 0); // Set the bg color as black default

    /* Create the basic tasks */
    xTaskCreatePinnedToCore(
        HgmLvglTask,
        "HgmLvglTask",
        4096,
        &this->lvTick,
        6,
        &this->hgmLvglTaskHandle,
        1
    );
    xTaskCreatePinnedToCore(
        HgmLvglTick,
        "HgmLvglTick",
        2048,
        &this->lvTick,
        10,
        &this->hgmLvglTickHandle,
        1
    );
    xTaskCreatePinnedToCore(
        HgmControlCheckTask,
        "HgmControlCheckTask",
        2048,
        this,
        7,
        &this->hgmControlHandle,
        1
    );
}

/**
 * @brief Initialize basic UI.
 */
void HGM::HgmLvgl::HgmLvglUIBegin()
{
    this->hgmFw->begin();
}

/* private function */
void HGM::HgmLvgl::HgmLvglTask(void* params)
{
    uint16_t tick = *(uint16_t*)params;
    while (true) {
        lv_timer_handler(); /* let the GUI do its work */
        vTaskDelay(tick);		// use FreeRTOS
    }
}

void HGM::HgmLvgl::HgmLvglTick(void* params)
{
    uint16_t tick = *(uint16_t*)params;
    while (true) {
        lv_tick_inc(tick);
        vTaskDelay(tick);
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

    _lcd->startWrite();
    _lcd->setAddrWindow(area->x1, area->y1, w, h);
    _lcd->pushColors((uint16_t*)&color_p->full, w * h, true);
    _lcd->endWrite();

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

