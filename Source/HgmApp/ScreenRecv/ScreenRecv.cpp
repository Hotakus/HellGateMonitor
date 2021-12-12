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
#include "../../HgmLvgl/HgmLvgl.h"

#include <TJpg_Decoder.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>
#include <SPIFFS.h>

#define TAG "ScreenRecv"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

using namespace HGM;
using namespace HgmGUI;
using namespace HgmApplication;

ScreenRecv screenRecv;

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
    uint16_t(*_faceBuf)[240] = (_fb_t)instance->sr.decode_frame_buf1;

    size_t pos = 0;
    for (size_t _h = 0; _h < h; _h++) {
        for (size_t _w = 0; _w < w; _w++) {
            // 字序交替赋值
            //_faceBuf[y + _h][x + _w] = (((bitmap[pos] & 0xFF) << 8) | ((bitmap[pos] >> 8) & 0xFF));
            _faceBuf[y + _h][x + _w] = bitmap[pos];
            pos++;
        }
    }

    return 1;
}

extern HgmLvgl *hgmLvgl;

void HgmApplication::ScreenRecv::decode_task(void* params)
{
    Serial.println("decode_task------------------------------------------------- decode_task");
    uint8_t* dummy;
    while (true)
    {
        if (xQueueReceive(instance->frtos.decode_mb, &dummy, portMAX_DELAY) != pdPASS)
            continue;

        TJpgDec.setJpgScale(1);
        TJpgDec.setSwapBytes(false);
        TJpgDec.setCallback(_DecodeCallback);

        uint16_t w = 0, h = 0;
        TJpgDec.getJpgSize(&w, &h, &instance->sr.recv_frame_buf[3], instance->sr.dat.fb);
        Serial.printf("Width = %d, height = %d\n", w, h);
        JRESULT ret = TJpgDec.drawJpg(0, 0, &instance->sr.recv_frame_buf[3], instance->sr.dat.fb);
        
        instance->sr.curr_frame_buf = instance->sr.decode_frame_buf1;

        //for (size_t s = 0; s < (HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT * 2); s++)
        //{
        //    Serial.printf("%X ", instance->sr.curr_frame_buf[s]);
        //}

        String _name = "HgmSRUpdate";
        MsgCenter& mc = HgmFramework::getInstance()->dataCenter;
        msg_t* msg = mc.findMsg(_name);
        if (!msg) {
            hgm_log_e(TAG, "HgmSRUpdate msg is null.");
            continue;
        }

        msg->pData(&instance->sr);
        mc.broadcast(msg);
    }
}


void ScreenRecv::begin(sr_open_methid_t om)
{
    /* allocte memory */
    sr.recv_frame_buf = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * (HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT * 2));
    sr.decode_frame_buf1 = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * (HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT * 2));
    if (om == SR_OPEN_DOUBLE_BUFF)
        sr.decode_frame_buf2 = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * (HGM_MONITOR_WIDTH * HGM_MONITOR_HEIGHT * 2));

    instance->sr.curr_frame_buf = instance->sr.decode_frame_buf1;
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

void HgmApplication::ScreenRecv::initTask()
{
    frtos.decode_mb = xQueueCreate(1, sizeof(void*));
    xTaskCreatePinnedToCore(
        decode_task,
        "decode_task",
        8192,
        NULL,
        3,
        &frtos.decode_th,
        1
    );
}

void HgmApplication::ScreenRecv::deInitTask()
{
    if (frtos.decode_th) {
        vTaskDelete(frtos.decode_th);
        frtos.decode_th = NULL;
    }
    vQueueDelete(frtos.decode_mb);
}

bool HgmApplication::ScreenRecv::setFrameHead(sr_data_t _dat)
{
    sr.dat = _dat;
    return true;
}

bool HgmApplication::ScreenRecv::imgReceive(WiFiClient& wc, size_t timeout)
{
    while (!wc.available() && timeout > 0) {
        timeout -= 10;
        vTaskDelay(10);
    }
    if (timeout <= 0)
        return false;

    //vTaskDelay(1000);

    Serial.println("---------------------------------11111111111111111111111111decode_start 01");

    uint8_t* buf = sr.recv_frame_buf;
    size_t i;
    for (i = 0; wc.available(); i++)
        buf[i] = (uint8_t)wc.read();
    buf[i] = '\0';

    Serial.println(i);

    for (size_t s = 0; s < i; s++)
    {
        Serial.printf("%X ", buf[s]);
    }

    Serial.println("---------------------------------11111111111111111111111111decode_start 02");

    if (buf[0] == 0x20 && buf[1] == 0x21 && buf[2] == 0x12) {
        if (buf[i - 1] == 0x20 && buf[i - 2] == 0x21 && buf[i - 3] == 0x12) {
            decode_start();
            return true;
        }
    } else
        return false;

}

void HgmApplication::ScreenRecv::decode_start()
{
    Serial.println("---------------------------------11111111111111111111111111decode_start 03");
    uint8_t* dummy;
    xQueueSend(instance->frtos.decode_mb, &dummy, portMAX_DELAY);
}
