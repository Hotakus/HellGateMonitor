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
#include "../../HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "../HgmWiFi/HgmTCP/HgmTCP.h"
#include "../HgmWiFi/HgmWiFi.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "BiliInfoRecv.h"
#include <ArduinoJson.h>
#include <iostream>
#include <TJpg_Decoder.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#define HGM_DEBUG 0

using namespace fs;
using namespace HgmGUI;
using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;
using namespace HGM;

extern HgmLvgl* hgmLvgl;
extern HgmSetupUI* hgmSetupUI;

BiliInfoRecv bili;

extern HTTPClient hgmHttpClient;

static String _uid = "";
static String basicInfoAPI = "http://api.bilibili.com/x/space/acc/info?mid=";
static String statAPI = "https://api.bilibili.com/x/relation/stat?vmid=";

static String userName = "";
static String userFaceImgUrl = "";
static uint8_t userLevel = 0;
static size_t userFans = 0;

static size_t userFaceImgBufSize = 0;
static uint8_t* userFaceImgBuf = NULL;   // default 64 x 64 jpg format
static uint16_t* userFaceBitmap = NULL;  // Bitmap that was decoded.

static HgmComponent component;

static bool getFlag = false;
static bool configFlag = false;

// TODO: add task
TaskHandle_t biliTaskHandle;
static void biliTask(void* params);


BiliInfoRecv::BiliInfoRecv()
{
}

BiliInfoRecv::~BiliInfoRecv()
{
    this->DeInitTask();
}

void HgmApplication::BiliInfoRecv::InitTask()
{
    if (biliTaskHandle)
        return;

    xTaskCreatePinnedToCore(
        biliTask,
        "biliTask",
        2512,
        NULL,
        8,
        &biliTaskHandle,
        1
    );
}

void HgmApplication::BiliInfoRecv::DeInitTask()
{
    if (biliTaskHandle) {
        vTaskDelete(biliTaskHandle);
        biliTaskHandle = NULL;
    }
}

static void BiliConfig()
{
    component.type = HGM_COMPONENT_BILIBILI;
    component.curStatus = false;
    component.waitStatus = false;
    hgmSetupUI->ComponentControl(&component);

    Serial.println("Waiting the BiliBili config...");
    while (configFlag != true)
        vTaskDelay(5);

    component.waitStatus = true;
}

void HgmApplication::BiliInfoRecv::Begin()
{
    File file;

    if (!SPIFFS.exists(BILI_CONFIG_FILE_PATH)) {
        Serial.printf("Can't find the bilibili.conf file, need to config by BT.\n");
        BiliConfig();
    } else {
        file = SPIFFS.open(BILI_CONFIG_FILE_PATH, FILE_READ);
        if (!file.size()) {
            file.close();
            Serial.printf("The bilibili.conf file is null, need to config by BT.\n");
            BiliConfig();
        } else {
            Serial.printf("Found the bilibili.conf file.\n");
            String tmp;
            HotakusDynamicJsonDocument doc(256);
            file = SPIFFS.open(BILI_CONFIG_FILE_PATH, FILE_READ);
            tmp = file.readString();
            deserializeJson(doc, tmp);

            Serial.println(tmp);

            String str = "bilibili";
            String header = doc["Header"];
            if (header.compareTo(str) != 0) {
                Serial.printf("BiliBili config file header error, need to config by BT.\n");
                file.close();
                BiliConfig();
                file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
            }

            component.type = HGM_COMPONENT_BILIBILI;
            component.curStatus = true;
            component.waitStatus = true;
            hgmSetupUI->ComponentControl(&component);

            this->SetUID(doc["Data"]["uid"]);

            file.close();
        }
    }

    this->InitTask();
}

/**
 * @brief Set UID.
 * @param uid
 */
void HgmApplication::BiliInfoRecv::SetUID(String uid)
{
    _uid = uid;
    configFlag = true;
}

/**
 * @brief Get UID.
 * @param uid
 */
void HgmApplication::BiliInfoRecv::GetUID(String& uid)
{
    uid = _uid;
}


static int _GetFollower() 
{
    String url = statAPI + _uid;
    HotakusDynamicJsonDocument userInfo(512);

    hgmHttpClient.setConnectTimeout(3 * 1000);
    hgmHttpClient.setTimeout(3 * 1000);
    hgmHttpClient.begin(url);
    int code = hgmHttpClient.GET();

    if (code != HTTP_CODE_OK) {
        Serial.printf("HTTP code : %d", code);
        hgmHttpClient.end();
        return -1;
    }
    String recv = hgmHttpClient.getString();
    deserializeJson(userInfo, recv);

    userFans = userInfo["data"]["follower"].as<size_t>();

    hgmHttpClient.end();
    return userFans;
}

/**
 * @brief Get followers.
 * @return user's fans.
 */
size_t HgmApplication::BiliInfoRecv::GetFollower()
{
    return userFans;
}

String& HgmApplication::BiliInfoRecv::GetUserName()
{
    return userName;
}


uint8_t HgmApplication::BiliInfoRecv::GetLevel()
{
    return userLevel;
}


typedef uint16_t(*_fb_t)[64];
static bool _DecodeCallback(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
    // 强制为二维数组
    uint16_t(*_faceBuf)[64] = (_fb_t)userFaceBitmap;

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
    if (!userFaceBitmap) {
        userFaceBitmap = (uint16_t*)heap_caps_calloc(64 * 64, 2, MALLOC_CAP_SPIRAM);
    }

    TJpgDec.setJpgScale(1);
    TJpgDec.setSwapBytes(false);
    TJpgDec.setCallback(_DecodeCallback);

    uint32_t t = millis();
    uint16_t w = 0, h = 0;
    TJpgDec.getJpgSize(&w, &h, userFaceImgBuf, userFaceImgBufSize);
    Serial.printf("Width = %d, height = %d\n", w, h);
    TJpgDec.drawJpg(0, 0, userFaceImgBuf, userFaceImgBufSize);

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
int HgmApplication::BiliInfoRecv::GetUserFaceImg(uint16_t imgWidth, uint16_t imgHeight)
{
    if (!userFaceImgUrl || !getFlag) {
        Serial.println("The URL of the user's face has not been get. please run \"GetBasicInfo()\"");
        return -1;
    }

    String width = String(imgWidth) + "w";
    String height = String(imgHeight) + "h";
    String imgUrl = userFaceImgUrl + "@" + width + "_" + height + "_1o" + ".jpg";    // get the face image URL with the designated size
    Serial.println(imgUrl);

    int code = -1;

    hgmHttpClient.setConnectTimeout(3 * 1000);
    hgmHttpClient.setTimeout(3 * 1000);
    hgmHttpClient.begin(imgUrl);
    code = hgmHttpClient.GET();

    WiFiClient* client = hgmHttpClient.getStreamPtr();
    if (client->available()) {
        size_t size = client->available();
        userFaceImgBufSize = size;
        Serial.printf("Face image size : %d Bytes\n", size);

        if (userFaceImgBuf)
            heap_caps_free(userFaceImgBuf);
        userFaceImgBuf = (uint8_t*)heap_caps_calloc(size, 1, MALLOC_CAP_SPIRAM);
        if (!userFaceImgBuf) {
            Serial.println("Face image buffer allocated failed.");
            hgmHttpClient.end();
            return -1;
        }

        if (client->readBytes(userFaceImgBuf, size) != size) {
            Serial.println("Face image buffer save failed.");
            hgmHttpClient.end();
            return -1;
        }
        Serial.println("Face image get done.");
    } else {
        Serial.println("Face image is null, check image URL.");
    }

    _SaveUserFaceImg();

    hgmHttpClient.end();
}

uint8_t* HgmApplication::BiliInfoRecv::GetUserFaceImgBuf(size_t* imgSize)
{
    *imgSize = userFaceImgBufSize;
    return userFaceImgBuf;
}

void* HgmApplication::BiliInfoRecv::GetUserFaceBitmap()
{
    return userFaceBitmap;
}

/**
 * @brief Get basic bilibili user info.
 */
void HgmApplication::BiliInfoRecv::GetBasicInfo()
{
    String url = basicInfoAPI + _uid;

    Serial.println(url);

    hgmHttpClient.setConnectTimeout(3 * 1000);
    hgmHttpClient.setTimeout(3 * 1000);
    hgmHttpClient.begin(url);
    int code = hgmHttpClient.GET();

    if (code != HTTP_CODE_OK) {
        Serial.printf("%s HTTP code : %d", __func__, code);
        hgmHttpClient.end();
        getFlag = false;
        return;
    }

    WiFiClient* wc = hgmHttpClient.getStreamPtr();
    size_t size = wc->available();
    uint8_t* recvBuf = (uint8_t*)heap_caps_calloc(size + 1, 1, MALLOC_CAP_SPIRAM);
    uint8_t* pRecvBuf = recvBuf;
    recvBuf[size] = '\0';
    wc->readBytes(recvBuf, size);

    

#if HGM_DEBUG == 1
    Serial.printf("%s", pRecvBuf);
#endif

    HotakusDynamicJsonDocument userInfo(8192);
    deserializeJson(userInfo, pRecvBuf);
    heap_caps_free(recvBuf);

    if (userInfo["data"]["mid"].as<String>().compareTo(_uid) != 0) {
        Serial.printf("Get user info is no correct : %s\n", userInfo["data"]["mid"].as<String>().c_str());
        hgmHttpClient.end();
        getFlag = false;
        return;
    }

    userName = userInfo["data"]["name"].as<String>();
    userLevel = userInfo["data"]["level"].as<uint8_t>();
    userFaceImgUrl = userInfo["data"]["face"].as<String>();

    hgmHttpClient.end();

    _GetFollower();

    getFlag = true;
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
        bili.GetBasicInfo();
        bili.GetUserFaceImg();
        xSemaphoreGive(wbs);

        vTaskDelay(BILI_GET_GAP);
        //vTaskDelay(2000);
    }
}
