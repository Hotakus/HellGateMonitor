/******************************************************************
 * @file WeatherInfo.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/22 6:27
 * @copyright Copyright (c) 2021/8/22
*******************************************************************/
#include "WeatherInfo.h"
#include "../HgmWiFi/HgmTCP/HgmTCP.h"
#include "../HgmBT/HgmBT.h"
#include "../../HgmLvgl/HgmGUI/HgmSetupView.h"
#include "../HgmJsonUtil.h"
#include "../TimeInfo/TimeInfo.h"
#include "../BiliInfoRecv/BiliInfoRecv.h"
#include "../HotakusHttpUtil.h"
#include "../../HgmLvgl/HgmGUI/HgmFramework.h"
#include "../../Utils/SPIFFSUtil/SPIFFSUtil.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>
#include <SPIFFS.h>

#define TAG "Weather"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;
using namespace HgmGUI;
using namespace fs;
using namespace spiffsutil;

extern HgmBT hgmBT;
static HgmComponent component;

static HTTPClient hc;
extern SemaphoreHandle_t wbs;

static void WeatherCheckTask(void* params);

WeatherInfo weatherInfo;

WeatherInfo::WeatherInfo()
{
    WeatherCheckMsgBox = xQueueCreate(1, sizeof(int));
}

WeatherInfo::~WeatherInfo()
{
    vQueueDelete(WeatherCheckMsgBox);
}

void HgmApplication::WeatherInfo::begin()
{
}

void HgmApplication::WeatherInfo::initTask()
{
    if (!WeatherCheckTaskHandle) {
        xTaskCreatePinnedToCore(
            WeatherCheckTask,
            "WeatherCheckTask",
            4096 + 1024,
            NULL,
            4,
            &WeatherCheckTaskHandle,
            1
        );
    }
}

void HgmApplication::WeatherInfo::deInitTask()
{
    if (WeatherCheckTaskHandle) {
        vTaskDelete(WeatherCheckTaskHandle);
        WeatherCheckTaskHandle = NULL;
    }
}

void HgmApplication::WeatherInfo::setWeatherConfig()
{
    File _file;
    _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_WRITE);
    HDJsonDoc doc(2048);

    String wi;
    doc["Header"] = "Weather";
    doc["Data"]["id"] = weatherInfo._id;
    doc["Data"]["key"] = weatherInfo._key;
    doc["Data"]["adm"] = weatherInfo._adm;
    doc["Data"]["adm2"] = weatherInfo._adm2;
    doc["Data"]["location"] = weatherInfo._location;
    doc["Data"]["lat"] = weatherInfo._lat;
    doc["Data"]["lon"] = weatherInfo._lon;
    serializeJson(doc, wi);

    _file.write((const uint8_t*)wi.c_str(), wi.length());

    _file.close();
    weatherInfo.configFlag = true;
}

void HgmApplication::WeatherInfo::setAppKey(String key)
{
    weatherInfo._key = key;
}

void HgmApplication::WeatherInfo::setWeatherConfig(String id)
{
    weatherInfo._id = id;
}

void HgmApplication::WeatherInfo::setWeatherConfig(String adm, String adm2, String location)
{
    weatherInfo._adm = adm;
    weatherInfo._adm2 = adm2;
    weatherInfo._location = location;
}

void HgmApplication::WeatherInfo::setWeatherConfig(String latitude, String longitude)
{
    Serial.println(latitude);
    Serial.println(longitude);

    weatherInfo._lat = latitude;
    weatherInfo._lon = longitude;
}

void HgmApplication::WeatherInfo::getWeatherConfig(String& id)
{
    id = weatherInfo._id;
}

void HgmApplication::WeatherInfo::getWeatherConfig(String& adm, String& adm2, String& location)
{
    adm = weatherInfo._adm;
    adm2 = weatherInfo._adm2;
    location = weatherInfo._location;
}

void HgmApplication::WeatherInfo::getWeatherConfig(String& latitude, String& longitude)
{
    latitude = weatherInfo._lat;
    longitude = weatherInfo._lon;
}

void HgmApplication::WeatherInfo::getWeather()
{
    String& __lat = weatherInfo._lat;
    String& __lon = weatherInfo._lon;
    String& __key = weatherInfo._key;

    String lonLat = "&location=" + __lon + ',' + __lat;
    String key = "&key=" + __key;
    String gzip = "&gzip=n";
    String nowApi = weatherInfo.nowWeatherAPI + lonLat + key + gzip;
    String threeApi = weatherInfo.threeWeatherAPI + lonLat + key + gzip;
    String airApi = weatherInfo.airAPI + lonLat + key + gzip;
    String locationApi = weatherInfo.locationAPI + lonLat + key + String("&number=1") + gzip;

    HDJsonDoc doc(8192);
    uint8_t* buf = (uint8_t*)hotakusAlloc(8192);

    /* Air */
    memset(buf, 0, 8192);
    size_t ret = HotakusHttpUtil::GET(hc, airApi, buf, 8192);
    if (ret) {
        deserializeJson(doc, buf);
        weatherInfo.wdt.aqi = doc["now"]["aqi"].as<uint16_t>();
    }

    /* Now */
    memset(buf, 0, 8192);
    ret = HotakusHttpUtil::GET(hc, nowApi, buf, 8192);
    if (ret) {
        deserializeJson(doc, buf);
        weatherInfo.wdt.temp = doc["now"]["temp"].as<uint16_t>();
        weatherInfo.wdt.humidity = doc["now"]["humidity"].as<uint16_t>();
        weatherInfo.wdt.icon = doc["now"]["icon"].as<uint16_t>();
    }
    
    /* Location */
    memset(buf, 0, 8192);
    ret = HotakusHttpUtil::GET(hc, locationApi, buf, 8192);
    if (ret) {
        deserializeJson(doc, buf);
        weatherInfo.wdt.location = doc["location"][0]["name"].as<String>();
    }

    hotakusFree(buf);
}

static void WeatherCheckTask(void* params)
{
    while (true) {
        while (!WiFi.isConnected())
            vTaskDelay(1000);

        String str = String("HgmTwUpdate");
        MsgCenter* mc = &HgmFramework::getInstance()->dataCenter;
        msg_t* msg = mc->findMsg(str);
        HgmTwModel::tw_data_t* tw_data = (HgmTwModel::tw_data_t*)msg->pData();

        xSemaphoreTake(wbs, portMAX_DELAY);
        tw_data->tdt = HgmTwModel::CONTROLLABLE;
        tw_data->controllable = false;
        mc->notify(str, str);
        WeatherInfo::getWeather();
        tw_data->tdt = HgmTwModel::CONTROLLABLE;
        tw_data->controllable = true;
        mc->notify(str, str);
        xSemaphoreGive(wbs);

        tw_data->tdt = HgmTwModel::WEATHER;
        tw_data->wd.aqi = weatherInfo.wdt.aqi;
        tw_data->wd.temp = weatherInfo.wdt.temp;
        tw_data->wd.rh = weatherInfo.wdt.humidity;
        tw_data->wd.icon = weatherInfo.wdt.icon;
        tw_data->name = weatherInfo.wdt.location;

        mc->notify(str, str);

        vTaskDelay(WEATHER_GET_GAP);
    }
}
