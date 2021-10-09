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
#include "../../HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "../HgmJsonUtil.h"
#include "../TimeInfo/TimeInfo.h"
#include "../BiliInfoRecv/BiliInfoRecv.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>
#include <SPIFFS.h>

#define HGM_DEBUG 1

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;
using namespace HgmGUI;
using namespace fs;

extern HgmBT hgmBT;
extern HgmSetupUI* hgmSetupUI;
static HgmComponent component;

extern SemaphoreHandle_t wbs;

static String nowWeatherAPI = "https://devapi.qweather.com/v7/weather/now?";
static String threeWeatherAPI = "https://devapi.qweather.com/v7/weather/3d?";
static String airAPI = "https://devapi.qweather.com/v7/air/now?";

static String _id = "";
static String _key = "";
static String _adm = "";
static String _adm2 = "";
static String _location = "";
static String _lat = "";
static String _lon = "";

static StaticJsonDocument<2048> doc;

static File _file;

static QueueHandle_t WeatherCheckMsgBox;
static TaskHandle_t WeatherCheckTaskHandle;
static void WeatherCheckTask(void* params);

static bool configFlag = false;

WeatherInfo weatherInfo;
WeatherData weatherToday;

WeatherInfo::WeatherInfo()
{
    // TODO: Create a task to loop to get the weather
    WeatherCheckMsgBox = xQueueCreate(1, sizeof(int));
}

WeatherInfo::~WeatherInfo()
{
    vQueueDelete(WeatherCheckMsgBox);
}


WeatherData::WeatherData()
{
}

WeatherData::~WeatherData()
{
}

void HgmApplication::WeatherInfo::begin()
{
    this->CheckWeatherconfig();
}

void HgmApplication::WeatherInfo::initTask()
{
    if (!WeatherCheckTaskHandle) {
        xTaskCreatePinnedToCore(
            WeatherCheckTask,
            "WeatherCheckTask",
            8192,
            NULL,
            8,
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
    _id = doc["data"]["id"].as<String>();
    _key = doc["data"]["key"].as<String>();
    _adm = doc["data"]["adm"].as<String>();
    _adm2 = doc["data"]["adm2"].as<String>();
    _location = doc["data"]["location"].as<String>();
    _lat = doc["data"]["lat"].as<String>();
    _lon = doc["data"]["lon"].as<String>();

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
    while (configFlag != true)
        vTaskDelay(5);

    _get();
}


bool HgmApplication::WeatherInfo::CheckWeatherconfig()
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

            configFlag = true;
            vTaskDelay(200);
        }
    }

    this->initTask();

    return true;
}

void HgmApplication::WeatherInfo::SetWeatherConfig()
{
    // TODO: Send msg
    _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_WRITE);

    String wi;
    doc["Header"] = "Weather";
    doc["Data"]["id"] = _id;
    doc["Data"]["key"] = _key;
    doc["Data"]["adm"] = _adm;
    doc["Data"]["adm2"] = _adm2;
    doc["Data"]["location"] = _location;
    doc["Data"]["lat"] = _lat;
    doc["Data"]["lon"] = _lon;
    serializeJson(doc, wi);

    _file.write((const uint8_t*)wi.c_str(), wi.length());

    _file.close();
    configFlag = true;
}

void HgmApplication::WeatherInfo::SetAppKey(String key)
{
    _key = key;
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String id)
{
    _id = id;
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String adm, String adm2, String location)
{
    _adm = adm;
    _adm2 = adm2;
    _location = location;
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String latitude, String longitude)
{
    Serial.println(latitude);
    Serial.println(longitude);

    _lat = latitude;
    _lon = longitude;
}

void HgmApplication::WeatherInfo::GetWeatherConfig(String& id)
{
    id = _id;
}

void HgmApplication::WeatherInfo::GetWeatherConfig(String& adm, String& adm2, String& location)
{
    adm = _adm;
    adm2 = _adm2;
    location = _location;
}

void HgmApplication::WeatherInfo::GetWeatherConfig(String& latitude, String& longitude)
{
    latitude = _lat;
    longitude = _lon;
}



void HgmApplication::WeatherInfo::GetWeather()
{
#if HGM_DEBUG == 1
    String __lat = "23.172";
    String __lon = "108.241";
    String __key = "bc1f1bdefb944930bef0208ecd03f66a"; // TODO: delete
#else
    String& __lat = _lat;
    String& __lon = _lon;
    String& __key = _key;
#endif

    String lonLat = "&location=" + __lon + ',' + __lat;
    String key = "&key=" + __key;
    String gzip = "&gzip=n";
    String nowApi = nowWeatherAPI + lonLat + key + gzip;
    String threeApi = threeWeatherAPI + lonLat + key + gzip;
    String airApi = airAPI + lonLat + key + gzip;

#if HGM_DEBUG == 1
    Serial.println(nowApi);
    Serial.println(threeApi);
    Serial.println(airApi);
#endif


    /* Air */


    /* Now */

    /* Three days */

}


static String wurl = "https://devapi.qweather.com/v7/air/now?gzip=n&location=108.241,23.172&key=bc1f1bdefb944930bef0208ecd03f66a";

static void WeatherCheckTask(void* params)
{

    Serial.println("WeatherCheckTask");

    while (true) {
        xSemaphoreTake(wbs, portMAX_DELAY);
        HTTPClient* https = new HTTPClient();
        https->setConnectTimeout(50 * 1000);
        https->setTimeout(50 * 1000);
        if (https->begin(wurl)) {  // HTTPS
            Serial.printf("[Weather/HTTPS] GET %d...\n", https->connected());
            int httpCode = https->GET();
            if (httpCode > 0) {
                Serial.printf("[Weather/HTTPS] GET... code: %d\n", httpCode);
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                    Serial.println(https->getString());
                }
            } else {
                Serial.printf("[Weather/HTTPS] GET... failed, error: %s\n", https->errorToString(httpCode).c_str());
            }
            https->end();
        } else {
            Serial.printf("[Weather/HTTPS] Unable to connect\n");
        }

        delete https;
        xSemaphoreGive(wbs);

        vTaskDelay(WEATHER_GET_GAP);
    }
}
