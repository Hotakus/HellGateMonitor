/******************************************************************
 * @file TimeInfo.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/20 10:27
 * @copyright Copyright (c) 2021/8/20
*******************************************************************/
#include "TimeInfo.h"
#include "../HgmWiFi/HgmTCP/HgmTCP.h"
#include "../../HgmLvgl/HgmGUI/HgmSetupView.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>

#define HGM_DEBUG 0

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;
using namespace HgmGUI;

static String timeAPI = "http://quan.suning.com/getSysTime.do";

static ESP32Time* _rtc;

extern HTTPClient* https;

static TaskHandle_t netTimeTaskHandle;
static QueueHandle_t netTimeMsgBox;
static void netTimeTask(void* params);

static HgmComponent component;

TimeInfo ti;

TimeInfo::TimeInfo()
{
    _rtc = &this->rtc;
}

TimeInfo::~TimeInfo()
{
    this->deInitTask();
}

void HgmApplication::TimeInfo::initTask()
{
    if (netTimeTaskHandle)
        return;

    xTaskCreatePinnedToCore(
        netTimeTask,
        "netTimeTask",
        2048 + 256,
        NULL,
        8,
        &netTimeTaskHandle,
        1
    );
}

void HgmApplication::TimeInfo::deInitTask()
{
    if (netTimeTaskHandle) {
        vTaskDelete(netTimeTaskHandle);
        netTimeTaskHandle = NULL;
    }
}

void HgmApplication::TimeInfo::begin()
{
   
}

bool HgmApplication::TimeInfo::getNetTime()
{
    if (https->connected()) {
        Serial.print("[HTTPS] time https->connected()...\n");
        https->end();
    }

    https->setConnectTimeout(3 * 1000);
    https->setTimeout(3 * 1000);
    https->begin(timeAPI);
    int code = https->GET();

    if (code != HTTP_CODE_OK) {
        Serial.printf("Net time HTTP code : %d\n", code);
        https->end();
        return false;
    }
    String recv = https->getString();
    HDJsonDoc doc(recv.length() + 512);
    deserializeJson(doc, recv);

#if HGM_DEBUG == 1
    Serial.println(recv);
#endif

    // {"sysTime2":"2021-08-21 04:55:48","sysTime1":"20210821045548"}
    String sysTime1 = doc["sysTime1"];
    if (!sysTime1) {
        Serial.printf("Get time error.\n", code);
        return false;
    }

    uint16_t year = sysTime1.substring(0, 4).toInt();
    uint8_t mon = sysTime1.substring(4, 6).toInt();
    uint8_t day = sysTime1.substring(6, 8).toInt();
    uint8_t hour = sysTime1.substring(8, 10).toInt();
    uint8_t min = sysTime1.substring(10, 12).toInt();
    uint8_t sec = sysTime1.substring(12).toInt();

    _rtc->setTime(sec, min, hour, day, mon, year);

    https->end();
    return true;
}

static void netTimeTask(void* params)
{
    extern SemaphoreHandle_t wbs;
    Serial.println("netTimeTask");

    while (true) {

        if (!WiFi.isConnected()) {
            vTaskDelay(1000);
            continue;
        }

        xSemaphoreTake(wbs, portMAX_DELAY);
        ti.getNetTime();
        xSemaphoreGive(wbs);

        vTaskDelay(NET_TIME_GAP);
    }
}
