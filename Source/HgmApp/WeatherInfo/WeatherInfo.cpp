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

static String weatherAPI = "";

static String _id = "";
static String _key = "";
static String _adm = "";
static String _adm2 = "";
static String _location = "";
static String _lat = "";
static String _lon = "";


static QueueHandle_t WCMsgBox;
static TaskHandle_t WCTaskHandle;
static void WCTask(void* params);


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


static void WeatherConfig(File* file)
{
    component.type = HGM_COMPONENT_WEATHER;
    component.curStatus = false;
    component.waitStatus = false;
    hgmSetupUI->ComponentControl(&component);


    // TODO: Send config msg
    while (true) {
        vTaskDelay(50);
    }

    //Serial.println("Waiting the Weather config...");
    //while (!WiFi.isConnected())
    //    vTaskDelay(50);
    //component.waitStatus = true;

    //// If WiFi is connected, then save the correct SSID and password
    //StaticJsonDocument<128> doc;
    //String tmp;
    //doc["Header"] = "WiFi";
    //doc["ssid"] = HgmWiFi::GetSSID();
    //doc["password"] = HgmWiFi::GetPassword();
    //serializeJson(doc, tmp);
    //file->write((const uint8_t*)tmp.c_str(), tmp.length());
}

bool HgmApplication::WeatherInfo::CheckWeatherconfig()
{
    File file;

    if (!SPIFFS.exists(WEATHER_CONFIG_FILE_PATH)) {
        Serial.printf("Can't find the config file for the weather component.\n");

        file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);
        WeatherConfig(&file);
        file.close();
    } else {
        if (!file.size()) {
            Serial.printf("Weather config file is null.\n");
            file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);
            WeatherConfig(&file);
            file.close();
        } else {

            String tmp;
            StaticJsonDocument<1024> doc;
            file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
            tmp = file.readString();
            deserializeJson(doc, tmp);

            Serial.println(tmp);

            String str = "Weather";
            String header = doc["Header"];
            if (header.compareTo(str) != 0) {
                file.close();
                file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);
                WeatherConfig(&file);
            }

            _id = doc["data"]["id"].as<String>();
            _key = doc["data"]["key"].as<String>();
            _adm = doc["data"]["adm"].as<String>();
            _adm2 = doc["data"]["adm2"].as<String>();
            _location = doc["data"]["location"].as<String>();
            _lat = doc["data"]["lat"].as<String>();
            _lon = doc["data"]["lon"].as<String>();

            WeatherInfo::SetWeatherConfig();

            component.type = HGM_COMPONENT_WEATHER;
            component.curStatus = true;
            component.waitStatus = true;
            hgmSetupUI->ComponentControl(&component);

            file.close();
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
    int tmp = 0;
    //xQueueSend(WCMsgBox, &tmp, portMAX_DELAY);
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


static void WCTask(void* params)
{
    int tmp = 0;
    while (true) {
        //xQueueReceive(WCMsgBox, &tmp, portMAX_DELAY);



        vTaskDelay(WEATHER_GET_GAP);
    }
}
