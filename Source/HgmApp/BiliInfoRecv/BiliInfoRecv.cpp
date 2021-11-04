/******************************************************************
 * @file BiliInfoRecv.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/15 16:33
 * @copyright Copyright (c) 2021/8/15
*******************************************************************/
#include "../../HgmLvgl/HgmLvgl.h"
#include "../HgmWiFi/HgmTCP/HgmTCP.h"
#include "../HgmWiFi/HgmWiFi.h"
#include "../HgmJsonUtil.h"
#include "BiliInfoRecv.h"
#include "../HotakusHttpUtil.h"
#include "../HotakusMemUtil.h"
#include "../../HgmLvgl/HgmGUI/HgmTwView/HgmTwModel.h"

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <iostream>
#include <TJpg_Decoder.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#define TAG "bili"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

using namespace fs;
using namespace HgmGUI;
using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;
using namespace HGM;

extern HgmLvgl* hgmLvgl;
extern HgmSetupView* hgmSetupUI;

BiliInfoRecv bili;

extern HTTPClient* https;

static SemaphoreHandle_t biliSemaphore;

extern HgmComponent component;

static bool configFlag = false;

// TODO: add task
TaskHandle_t biliTaskHandle;
static void biliTask(void* params);

static BiliInfoRecv* instance = NULL;

BiliInfoRecv::BiliInfoRecv()
{
    instance = this;
}

BiliInfoRecv::~BiliInfoRecv()
{
    instance = NULL;
}

void HgmApplication::BiliInfoRecv::initTask()
{
    if (biliTaskHandle)
        return;

    if (!info)
        info = (_info*)hotakusAlloc(sizeof(_info));

    biliSemaphore = xSemaphoreCreateBinary();
    xTaskCreatePinnedToCore(
        biliTask,
        "biliTask",
        2048 + 512,
        NULL,
        8,
        &biliTaskHandle,
        1
    );
}

void HgmApplication::BiliInfoRecv::deInitTask()
{
    if (biliTaskHandle) {
        vTaskDelete(biliTaskHandle);
        biliTaskHandle = NULL;
    }
    vSemaphoreDelete(biliSemaphore);

    if (info)
        hotakusFree(info);
}

void HgmApplication::BiliInfoRecv::begin()
{
    
}

/**
 * @brief Set UID.
 * @param uid
 */
void HgmApplication::BiliInfoRecv::uid(String uid)
{
    if (!instance->info)
        instance->info = (_info*)hotakusAlloc(sizeof(_info));
    instance->info->_uid = uid;
    configFlag = true;
}

/**
 * @brief Get UID.
 * @param uid
 */
String HgmApplication::BiliInfoRecv::uid()
{
    return instance->info->_uid;
}

/**
 * @brief Get followers.
 * @return user's fans.
 */
size_t HgmApplication::BiliInfoRecv::getFollower()
{
    return instance->info->userFans;
}

String& HgmApplication::BiliInfoRecv::getUserName()
{
    return instance->info->userName;
}


uint8_t HgmApplication::BiliInfoRecv::getLevel()
{
    return instance->info->userLevel;
}


typedef uint16_t(*_fb_t)[64];
static bool _DecodeCallback(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
    // 强制为二维数组
    uint16_t(*_faceBuf)[64] = (_fb_t)instance->info->userFaceBitmap;

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

/**
 * @brief Decode the JPG user face image and save the bitmap.
 */
static void _SaveUserFaceImg()
{
    if (!instance->info->userFaceBitmap) {
        instance->info->userFaceBitmap = (uint16_t*)heap_caps_calloc(64 * 64, 2, MALLOC_CAP_SPIRAM);
    }

    TJpgDec.setJpgScale(1);
    TJpgDec.setSwapBytes(false);
    TJpgDec.setCallback(_DecodeCallback);

    uint32_t t = millis();
    uint16_t w = 0, h = 0;
    TJpgDec.getJpgSize(&w, &h, instance->info->userFaceImgBuf, instance->info->userFaceImgBufSize);
    Serial.printf("Width = %d, height = %d\n", w, h);
    TJpgDec.drawJpg(0, 0, instance->info->userFaceImgBuf, instance->info->userFaceImgBufSize);

    // hgmLvgl->lcd->pushImage(0, 0, 64, 64, userFaceBitmap);

    t = millis() - t;
    Serial.print(t); Serial.println(" ms");

    Serial.printf("User face image was decoded.\n");
}

/**
 * @brief Get user face image from UID.
 * @param imgWidth
 * @param imgHeight
 * @return Error code
 */
int HgmApplication::BiliInfoRecv::getUserFaceImg(uint16_t imgWidth, uint16_t imgHeight)
{
    if (!instance->info->userFaceImgUrl) {
        Serial.println("The URL of the user's face has not been get. please run \"getBasicInfo()\"");
        return -1;
    }

    String width = String(imgWidth) + "w";
    String height = String(imgHeight) + "h";
    String imgUrl = instance->info->userFaceImgUrl + "@" + width + "_" + height + "_1o" + ".jpg";    // get the face image URL with the designated size
    Serial.println(imgUrl);

    int code = -1;

    https->setConnectTimeout(3 * 1000);
    https->setTimeout(3 * 1000);
    https->begin(imgUrl);
    code = https->GET();

    WiFiClient* client = https->getStreamPtr();
    if (client->available()) {
        size_t size = client->available();
        instance->info->userFaceImgBufSize = size;
        Serial.printf("Face image size : %d Bytes\n", size);

        if (instance->info->userFaceImgBuf)
            heap_caps_free(instance->info->userFaceImgBuf);
        instance->info->userFaceImgBuf = (uint8_t*)heap_caps_calloc(size, 1, MALLOC_CAP_SPIRAM);
        if (!instance->info->userFaceImgBuf) {
            Serial.println("Face image buffer allocated failed.");
            https->end();
            return -1;
        }

        if (client->readBytes(instance->info->userFaceImgBuf, size) != size) {
            Serial.println("Face image buffer save failed.");
            https->end();
            return -1;
        }
        Serial.println("Face image get done.");
    } else {
        Serial.println("Face image is null, check image URL.");
    }

    https->end();

    _SaveUserFaceImg();
}

uint8_t* HgmApplication::BiliInfoRecv::getUserFaceImgBuf(size_t* imgSize)
{
    *imgSize = instance->info->userFaceImgBufSize;
    return instance->info->userFaceImgBuf;
}

void* HgmApplication::BiliInfoRecv::getUserFaceBitmap()
{
    return instance->info->userFaceBitmap;
}



static int _GetFollower()
{
    String url = instance->statAPI + instance->info->_uid;
    HDJsonDoc userInfo(1024);

    uint8_t* buf = (uint8_t*)hotakusAlloc(1024);
    HotakusHttpUtil::GET(*https, url, buf, 1024);
    deserializeJson(userInfo, buf);
    hotakusFree(buf);

    instance->info->userFans = userInfo["data"]["follower"].as<size_t>();
    return instance->info->userFans;
}

/**
 * @brief Get basic bilibili user info.
 */
void HgmApplication::BiliInfoRecv::getBasicInfo()
{
    String url = instance->basicInfoAPI + instance->info->_uid;
    Serial.println(url);

    uint8_t* recvBuf = (uint8_t*)hotakusAlloc(8192);
    uint8_t* pRecvBuf = recvBuf;
    size_t ret = HotakusHttpUtil::GET(*https, url, recvBuf, 8192);
    //hotakusRealloc(recvBuf, ret + 1);

    /* Check begin characters */
    while (*pRecvBuf != '{' && (*pRecvBuf != recvBuf[ret - 1]))
        pRecvBuf++;

    HDJsonDoc userInfo(ret + 1024);
    deserializeJson(userInfo, pRecvBuf);
    hotakusFree(recvBuf);

    if (userInfo["data"]["mid"].as<String>().compareTo(instance->info->_uid) != 0) {
        hgm_log_e(TAG, "Get user info is no correct : %s\n", userInfo["data"]["mid"].as<String>().c_str());
        return;
    }

    instance->info->userName = userInfo["data"]["name"].as<String>();
    instance->info->userLevel = userInfo["data"]["level"].as<uint8_t>();
    instance->info->userFaceImgUrl = userInfo["data"]["face"].as<String>();

    _GetFollower();
}

static void biliTask(void* params)
{
    extern SemaphoreHandle_t wbs;

    while (true) {
        if (!WiFi.isConnected() || !configFlag) {
            vTaskDelay(1000);
            continue;
        }

        xSemaphoreTake(wbs, portMAX_DELAY);
        bili.getBasicInfo();
        bili.getUserFaceImg();
        xSemaphoreGive(wbs);

        String str = String("HgmTwUpdate");
        MsgCenter* mc = &HgmFramework::getInstance()->hgmFwCenter;
        msg_t* msg = mc->findMsg(str);
        HgmTwModel::tw_data_t* tw_data = (HgmTwModel::tw_data_t*)msg->pData();
        
        tw_data->tdt = HgmTwModel::BILI;
        tw_data->bd.bn = bili.getUserName();
        tw_data->bd.fans = bili.getFollower();
        tw_data->bd.ufb = (uint8_t*)bili.getUserFaceBitmap();
        tw_data->bd.uid = bili.uid();
        
        mc->notify(str, str);

        vTaskDelay(BILI_GET_GAP);
    }
}
