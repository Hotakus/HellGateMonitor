/******************************************************************
 * @file ScreenRecv.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/12/5 19:51
 * @copyright Copyright (c) 2021/12/5
*******************************************************************/
#include "ScreenRecv.h"
#include "../HgmWiFi/HgmTCP/HgmTCP.h"
#include "../HgmBT/HgmBT.h"
#include "../../HgmLvgl/HgmGUI/HgmSetupView.h"
#include "../HgmJsonUtil.h"
#include "../HotakusHttpUtil.h"
#include "../../HgmLvgl/HgmGUI/HgmFramework.h"
#include "../../Utils/SPIFFSUtil/SPIFFSUtil.h" 
#include "../HotakusMemUtil.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>
#include <SPIFFS.h>

#define TAG "ScreenRecv"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

using namespace HgmApplication;

static ScreenRecv* instance = nullptr;

HgmApplication::ScreenRecv::ScreenRecv()
{
    instance = this;
}

HgmApplication::ScreenRecv::~ScreenRecv()
{
    instance = nullptr;
}

typedef uint16_t(*_fb_t)[240];
static bool _DecodeCallback(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
    // 强制为二维数组
    //uint16_t(*_faceBuf)[240] = (_fb_t)instance->info.userFaceBitmap;

    size_t pos = 0;
    for (size_t _h = 0; _h < h; _h++) {
        for (size_t _w = 0; _w < w; _w++) {
            // 字序交替赋值
            //_faceBuf[y + _h][x + _w] = (((bitmap[pos] & 0xFF) << 8) | ((bitmap[pos] >> 8) & 0xFF));
            //_faceBuf[y + _h][x + _w] = bitmap[pos];
            pos++;
        }
    }

    return 1;
}

void ScreenRecv::begin(sr_open_methid_t om, sr_recv_methid_t rm)
{
    /* allocte memory */

    // if (rm = SR_IMG_FMT_JPG)

    sr.recv_frame_buf = (uint8_t*)malloc(sizeof(uint8_t) * (HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT * 2));
    sr.decode_frame_buf1 = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * (HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT * 2));
    if (om == SR_OPEN_DOUBLE_BUFF)
        sr.decode_frame_buf2 = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * (HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT * 2));

}

void ScreenRecv::end()
{
    if (sr.recv_frame_buf)
        free(sr.recv_frame_buf);
    if (sr.decode_frame_buf1)
        hotakusFree(sr.decode_frame_buf1);
    if (sr.decode_frame_buf2)
        hotakusFree(sr.decode_frame_buf2);
}
