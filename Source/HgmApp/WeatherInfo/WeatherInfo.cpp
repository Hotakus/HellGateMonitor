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

extern HgmBT hgmBT;
extern HgmSetupView* hgmSetupUI;
static HgmComponent component;

WeatherData weatherDataToday;
static HTTPClient hc;
static File _file;
static StaticJsonDocument<2048> doc;
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

WeatherData::WeatherData() = default;
WeatherData::~WeatherData() = default;

void HgmApplication::WeatherInfo::begin()
{
    this->checkWeatherconfig();
}

void HgmApplication::WeatherInfo::initTask()
{
    if (!WeatherCheckTaskHandle) {
        xTaskCreatePinnedToCore(
            WeatherCheckTask,
            "WeatherCheckTask",
            8192,
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


static void _get()
{
    weatherInfo._id = doc["data"]["id"].as<String>();
    weatherInfo._key = doc["data"]["key"].as<String>();
    weatherInfo._adm = doc["data"]["adm"].as<String>();
    weatherInfo._adm2 = doc["data"]["adm2"].as<String>();
    weatherInfo._location = doc["data"]["location"].as<String>();
    weatherInfo._lat = doc["data"]["lat"].as<String>();
    weatherInfo._lon = doc["data"]["lon"].as<String>();

    component.curStatus = true;
    component.waitStatus = true;
}

static void WeatherConfig()
{
    component.type = HGM_COMPONENT_WEATHER;
    component.curStatus = false;
    component.waitStatus = false;
    hgmSetupUI->componentControl(&component);

    Serial.println("Waiting the Weather config...");
    while (weatherInfo.configFlag != true)
        vTaskDelay(5);

    _get();
}


bool HgmApplication::WeatherInfo::checkWeatherconfig()
{
    if (!SPIFFS.exists(WEATHER_CONFIG_FILE_PATH)) {
        Serial.printf("Can't find the config file for the weather component.\n");
        WeatherConfig();
    } else {
        _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_READ);
        if (!_file.size()) {
            _file.close();
            Serial.printf("Weather config file is null.\n");
            WeatherConfig();
        } else {
            _file.close();

            Serial.printf("Found the weather config file.\n");
            String tmp;
            _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_READ);
            tmp = _file.readString();
            _file.close();

            deserializeJson(doc, tmp);
            Serial.println(tmp);

            String str = "Weather";
            String header = doc["Header"];
            if (header.compareTo(str) != 0) {
                WeatherConfig();
            } else {
                _get();
            }

            _lat = doc["Data"]["lat"].as<String>();
            _lon = doc["Data"]["lon"].as<String>();
            _key = doc["Data"]["key"].as<String>();

            weatherInfo.configFlag = true;
            vTaskDelay(200);
        }
    }

    // this->initTask();

    return true;
}

void HgmApplication::WeatherInfo::setWeatherConfig()
{
    // TODO: Send msg
    _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_WRITE);

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
#if HGM_DEBUG == 1
    String __lat = "23.172";
    String __lon = "108.241";
    String __key = "bc1f1bdefb944930bef0208ecd03f66a";
#else
    String& __lat = _lat;
    String& __lon = _lon;
    String& __key = _key;
#endif

    String lonLat = "&location=" + __lon + ',' + __lat;
    String key = "&key=" + __key;
    String gzip = "&gzip=n";
    String nowApi = weatherInfo.nowWeatherAPI + lonLat + key + gzip;
    String threeApi = weatherInfo.threeWeatherAPI + lonLat + key + gzip;
    String airApi = weatherInfo.airAPI + lonLat + key + gzip;

#if HGM_DEBUG == 1
    Serial.println(nowApi);
    Serial.println(threeApi);
    Serial.println(airApi);
#endif

    HDJsonDoc doc(8192);
    uint8_t* buf = (uint8_t*)hotakusAlloc(8192);

    /* Air */
    memset(buf, 0, 8192);
    size_t ret = HotakusHttpUtil::GET(hc, airApi, buf, 8192);
    if (ret) {
        deserializeJson(doc, buf);
        weatherDataToday.aqi = doc["now"]["aqi"].as<uint16_t>();
    }

    /* Now */
    memset(buf, 0, 8192);
    ret = HotakusHttpUtil::GET(hc, nowApi, buf, 8192);
    if (ret) {
        deserializeJson(doc, buf);
        weatherDataToday.temp = doc["now"]["temp"].as<uint16_t>();
        weatherDataToday.humidity = doc["now"]["humidity"].as<uint16_t>();
        weatherDataToday.icon = doc["now"]["icon"].as<uint16_t>();
    }
    /* Three days */


    hotakusFree(buf);

}

static void WeatherCheckTask(void* params)
{
    while (true) {
        while (!WiFi.isConnected())
            vTaskDelay(1000);

        xSemaphoreTake(wbs, portMAX_DELAY);
        WeatherInfo::getWeather();
        xSemaphoreGive(wbs);
        vTaskDelay(WEATHER_GET_GAP);
    }
}
