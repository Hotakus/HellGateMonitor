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
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>
#include "../HgmWiFi/HgmTCP/HgmTCP.h"
#include "../../HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "../HgmApp.h"
#include <SPIFFS.h>

using namespace HgmApplication;
using namespace HgmGUI;
using namespace fs;

extern HgmApp* hgmApp;
extern HgmSetupUI* hgmSetupUI;
static HgmComponent component;

static String nowWeatherAPI = "https://devapi.qweather.com/v7/weather/now";
static String threeWeatherAPI = "https://devapi.qweather.com/v7/weather/3d";

static String _id = "";
static String _key = "";
static String _adm = "";
static String _adm2 = "";
static String _location = "";
static String _lat = "";
static String _lon = "";

static StaticJsonDocument<2048> doc;

File _file;


static QueueHandle_t WCMsgBox;
static TaskHandle_t WCTaskHandle;
static void WCTask(void* params);

bool configFlag = false;

WeatherInfo::WeatherInfo()
{
    // TODO: Create a task to loop to get the weather
    WCMsgBox = xQueueCreate(1, sizeof(int));
}

WeatherInfo::~WeatherInfo()
{
}

void HgmApplication::WeatherInfo::Begin()
{

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
    hgmSetupUI->ComponentControl(&component);

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
        _file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
        if (!_file.size()) {
            _file.close();
            Serial.printf("Weather config file is null.\n");
            WeatherConfig();
        } else {
            _file.close();

            Serial.printf("Found the weather config file.\n");
            String tmp;
            _file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
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
            
            configFlag = true;
            vTaskDelay(200);
        }
    }

    xTaskCreatePinnedToCore(
        WCTask,
        "WCTask",
        2048,
        NULL,
        5,
        &WCTaskHandle,
        1
    );

    return true;
}



void HgmApplication::WeatherInfo::SetWeatherConfig()
{
    // TODO: Send msg
    _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_WRITE);

    String wi;
    doc["data"]["id"] = _id;
    doc["data"]["key"] = _key;
    doc["data"]["adm"] = _adm;
    doc["data"]["adm2"] = _adm2;
    doc["data"]["location"] = _location;
    doc["data"]["lat"] = _lat;
    doc["data"]["lon"] = _lon;
    serializeJson(doc, wi);

    _file.write((const uint8_t*)wi.c_str(), wi.length());

    _file.close();
    configFlag = true;
}

void HgmApplication::WeatherInfo::SetAppKey(String key)
{
    Serial.println(key);

    _key = key;
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String id)
{
    Serial.println(id);

    _id = id;
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String adm, String adm2, String location)
{
    Serial.println(adm);
    Serial.println(adm2);
    Serial.println(location);

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
    // TODO:
    Serial.println("Get weather...");
}


static void WCTask(void* params)
{
    int tmp = 0;
    while (true) {
        //xQueueReceive(WCMsgBox, &tmp, portMAX_DELAY);

        if (!WiFi.isConnected()) {
            vTaskDelay(1000);
            continue;
        }

        WeatherInfo::GetWeather();

        vTaskDelay(WEATHER_GET_GAP);
    }
}
