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

WeatherInfo::WeatherInfo()
{
    // TODO: Create a task to loop to get the weather
}

WeatherInfo::~WeatherInfo()
{
}

void HgmApplication::WeatherInfo::Begin()
{

    File file;



}


bool HgmApplication::WeatherInfo::CheckWeatherconfig(File* file)
{
    if (!SPIFFS.exists(WEATHER_CONFIG_FILE_PATH)) {
        Serial.printf("Can't find the config file for the weather component.");
        component.type = HGM_COMPONENT_CONFIG_FILE;
        component.curStatus = false;
        component.waitStatus = false;
        // TODO:

        component.waitStatus = true;
    } else {

    }
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String& adm, String& adm2, String& location, String& latitude, String& longitude)
{
    Serial.println(adm);
    Serial.println(adm2);
    Serial.println(location);
    Serial.println(latitude);
    Serial.println(longitude);
}

void HgmApplication::WeatherInfo::GetWeatherConfig(String& adm, String& adm2, String& location)
{
}

void HgmApplication::WeatherInfo::GetWeatherConfig(String& latitude, String& longitude)
{
}
