/******************************************************************
 * @file BiliInfoRecv.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/15 16:33
 * @copyright Copyright (c) 2021/8/15
*******************************************************************/
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "BiliInfoRecv.h"
#include <ArduinoJson.h>
#include <iostream>

using namespace HgmApplication;

HTTPClient* _httpClient = nullptr;

static String _uid = "";
static String basicInfoAPI = "http://api.bilibili.com/x/space/acc/info?mid=";
static String statAPI = "https://api.bilibili.com/x/relation/stat?vmid=";

static String userName = "";
static String userFaceImgUrl = "";
static uint8_t userLevel = 0;
static size_t userFans = 0;

static size_t userFaceImgBufSize = 0;
static uint8_t* userFaceImgBuf = nullptr;   // default 64 x 64 jpg format

/* Maybe no effective */
static size_t userTotalViews = 0;
static size_t userTotalLikes = 0;

BiliInfoRecv::BiliInfoRecv()
{
    _httpClient = new HTTPClient();
}

BiliInfoRecv::~BiliInfoRecv()
{
    delete _httpClient;
}

void HgmApplication::BiliInfoRecv::SetUID(String uid)
{
    _uid = uid;
}

void HgmApplication::BiliInfoRecv::GetUID(String& uid)
{
    uid = _uid;
}


int HgmApplication::BiliInfoRecv::GetFollower()
{
    String url = statAPI + _uid;
    StaticJsonDocument<512> userInfo;

    _httpClient->end();
    vTaskDelay(100);
    _httpClient->begin(url);
    int code = _httpClient->GET();

    if (code != 200) {
        Serial.printf("HTTP code : %d", code);
        _httpClient->end();
        return -1;
    }
    String recv = _httpClient->getString();
    deserializeJson(userInfo, recv);

    userFans = userInfo["data"]["follower"].as<size_t>();

    Serial.printf("Fans : %d\n", userFans);

    _httpClient->end();
    return userFans;
}

void HgmApplication::BiliInfoRecv::GetBasicInfo()
{
    String url = basicInfoAPI + _uid;
    StaticJsonDocument<4096> userInfo;

    _httpClient->end();
    vTaskDelay(100);
    _httpClient->begin(url);
    int code = _httpClient->GET();

    if (code != 200) {
        Serial.printf("HTTP code : %d", code);
        _httpClient->end();
        return;
    }
    String recv = _httpClient->getString();
    deserializeJson(userInfo, recv);

    if (userInfo["data"]["mid"].as<String>().compareTo(_uid) != 0) {
        Serial.printf("Get user info is no correct : %s", userInfo["data"]["mid"].as<String>().c_str());
        _httpClient->end();
        return;
    }

    userName = userInfo["data"]["name"].as<String>();
    userFaceImgUrl = userInfo["data"]["face"].as<String>();
    userLevel = userInfo["data"]["level"].as<uint8_t>();

    _httpClient->end();
}


void HgmApplication::BiliInfoRecv::GetUserFaceImg(uint16_t imgWidth, uint16_t imgHeight)
{
    if (!userFaceImgUrl) {
        Serial.println("The URL of the user's face has not been get. please run \"GetBasicInfo()\"");
        return;
    }

    String width = String(imgWidth) + "w";
    String height = String(imgHeight) + "h";
    String imgUrl = userFaceImgUrl + "@" + width + "_" + height + "_1o" + ".jpg";    // get the face image URL with the designated size
    Serial.println(imgUrl);

    _httpClient->begin(imgUrl);
    int code = _httpClient->GET();

    if (code != 200) {
        Serial.printf("Get user's face image error. (%d)\n", code);
        return;
    }

    WiFiClient* client = _httpClient->getStreamPtr();
    if (client->available()) {
        size_t size = client->available();
        userFaceImgBufSize = size;
        Serial.printf("Face image size : %d Bytes\n", size);

        if (userFaceImgBuf)
            heap_caps_free(userFaceImgBuf);
        userFaceImgBuf = (uint8_t*)heap_caps_calloc(size, 1, MALLOC_CAP_SPIRAM);
        if (!userFaceImgBuf) {
            Serial.println("Face image buffer allocated failed.");
            _httpClient->end();
            return;
        }

        if (client->readBytes(userFaceImgBuf, size) != size) {
            Serial.println("Face image buffer save failed.");
            _httpClient->end();
            return;
        }
        Serial.println("Face image get done.");
    } else {
        Serial.println("Face image is null, check image URL.");
    }

    _httpClient->end();
}

uint8_t* HgmApplication::BiliInfoRecv::GetUserFaceImgBuf(size_t* imgSize)
{
    *imgSize = userFaceImgBufSize;
    return userFaceImgBuf;
}

