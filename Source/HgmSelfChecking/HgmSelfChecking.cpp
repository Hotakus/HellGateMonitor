/******************************************************************
 * @file HgmSelfChecking.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/13 17:57
 * @copyright Copyright (c) 2021/8/13
*******************************************************************/

#include "../HgmApp/HgmApp.h"
#include "../HgmApp/HgmWiFi/HgmWiFi.h"
#include "HgmSelfChecking.h"
#include "../HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "../HgmApp/WeatherInfo/WeatherInfo.h"

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>


using namespace HgmApplication;
using namespace HgmGUI;
using namespace HGM;
using namespace fs;

extern HgmApp* hgmApp;
extern HgmSetupUI* hgmSetupUI;
static HgmComponent component;

String ssid;
String password;


static void WiFiBTConfig();

HgmSC::HgmSC()
{
    // TODO:
}

HgmSC::~HgmSC()
{
    // TODO:
}

void HGM::HgmSC::Begin()
{
    uint8_t i = 0;
    uint8_t timeout = 10;
    File file;
    
    component.type = HGM_COMPONENT_CONFIG_FILE;

    /* Delay 500ms for PSRAM */
    delay(500);
    
    Serial.println("SPIFFS beginning...");
    for (i = 0; i < timeout; i++) {
        if (SPIFFS.begin())
            break;
        Serial.print(".");
        vTaskDelay(100);
    }
    if (i >= timeout) {
        Serial.println("SPIFFS begin failed.");
        this->CheckFlag = false;
        component.curStatus = false;
        component.waitStatus = false;
        hgmSetupUI->ComponentControl(&component);
        vTaskDelay(2000);
        ESP.restart();
    }
    Serial.println("SPIFFS is OK.");
    Serial.printf("SPIFFS total : %d Bytes\n", SPIFFS.totalBytes());
    Serial.printf("SPIFFS used  : %d Bytes\n", SPIFFS.usedBytes());


    Serial.printf("Try to read \"%s\"\n", WIFI_CONFIG_FILE_PATH);
    if (!SPIFFS.exists(WIFI_CONFIG_FILE_PATH)) {
        // If there isn't config file, show the info to screen and serial. Then use BT to config wifi.
        Serial.println("No WiFi config file be found in spiffs.");
        Serial.println("Open bluetooth to config wifi file and open wifi.");
        WiFiBTConfig();
        Serial.printf("WiFi config file size : %d\n", file.size());
    } else {
        // If there is the config file, read and analyze the json content then store to HgmWiFi object.
        // Create mailbox in HgmWiFi, then this function send a mail to trigger wifi config function.
        // If read content from wifi config file is null, then show log and begin BT config
        Serial.println("Found the WiFi config file.");
        file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
        if (!file.size()) {
            Serial.println("WiFi config file is null, start to WiFi config via BT.");
            file.close();
            WiFiBTConfig();
        } else {
            // To open wifi with content that from wifi config file.
            String tmp;
            DynamicJsonDocument doc(256);
            file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
            tmp = file.readString();
            deserializeJson(doc, tmp);

            // TODO: Debug
            Serial.println(tmp);

            String str = "WiFi";
            String header = doc["Header"];
            if (header.compareTo("WiFi") != 0) {
                file.close();
                WiFiBTConfig();
                file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
            }
            component.type = HGM_COMPONENT_CONFIG_FILE;
            component.curStatus = true;
            component.waitStatus = true;
            hgmSetupUI->ComponentControl(&component);

            ssid = doc["ssid"].as<String>();
            password = doc["password"].as<String>();
            hgmApp->hgmWifi->ConfigWiFi(ssid, password);

            file.close();
            vTaskDelay(200);
        }
    }

    this->CheckFlag = true;
}

static void WiFiBTConfig()
{
    component.type = HGM_COMPONENT_CONFIG_FILE;
    component.curStatus = false;
    component.waitStatus = false;
    hgmSetupUI->ComponentControl(&component);

    Serial.println("Waiting the BT config WiFi...");
    while (!WiFi.isConnected()) 
        vTaskDelay(50);
    component.waitStatus = true;
}


