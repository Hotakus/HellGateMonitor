/******************************************************************
 * @file HgmSelfChecking.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/13 17:57
 * @copyright Copyright (c) 2021/8/13
*******************************************************************/
#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#include "../HgmApp/HgmApp.h"
#include "../HgmApp/HgmWiFi/HgmWiFi.h"
#include "HgmSelfChecking.h"

using namespace HgmApplication;
using namespace HGM;
using namespace fs;

extern HgmApp* hgmApp;

static void WiFiBTConfig(File *file);

HgmSC::HgmSC()
{
    // TODO:
}

HgmSC::~HgmSC()
{
    // TODO:
    SPIFFS.end();
}

void HGM::HgmSC::Begin()
{
    uint8_t i = 0;
    uint8_t timeout = 10;
    File file;

    /* Delay 500ms for PSRAM */
    delay(500);

    Serial.println("SPIFFS beginning...");
    for (i = 0; i < timeout; i++) {
        if (SPIFFS.begin())
            break;
        Serial.print(".");
    }
    if (i >= timeout) {
        Serial.println("SPIFFS begin failed.");
        this->CheckFlag = false;
        return;
    }
    Serial.println("SPIFFS is OK.");
    Serial.printf("SPIFFS total : %d Bytes\n", SPIFFS.totalBytes());
    Serial.printf("SPIFFS used  : %d Bytes\n", SPIFFS.usedBytes());

    Serial.printf("Try to read \"%s\"\n", WIFI_CONFIG_FILE_PATH);
    if (!SPIFFS.exists(WIFI_CONFIG_FILE_PATH)) {
        // TODO: If there isn't config file, show the info to screen and serial. Then use BT config wifi.
        Serial.println("No WiFi config file be found in spiffs.");
        Serial.println("Open bluetooth to config wifi file and open wifi.");
        file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);
        WiFiBTConfig(&file);
        Serial.printf("WiFi config file size : %d\n", file.size());
        file.close();
    } else {
        // TODO: If there is the config file, read and analyze the json content then store to HgmWiFi object.
        // TODO: Create mailbox in HgmWiFi, then this function send a mail to trigger wifi config function.
        // TODO: If read content from wifi config file is null, then show log and begin BT config
        Serial.println("Found the WiFi config file.");
        file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
        if (!file.size()) {
            Serial.println("WiFi config file is null, start to WiFi config via BT.");
            file.close();
            file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);
            WiFiBTConfig(&file);
            file.close();

            file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
            Serial.println(file.readString());
            file.close();
            // SPIFFS.remove(WIFI_CONFIG_FILE_PATH); // TODO: delate
        } else {
            // TODO: To open wifi with content that from wifi config file.
            String tmp;
            StaticJsonDocument<128> doc;
            file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_READ);
            tmp = file.readString();
            deserializeJson(doc, tmp);

            String str = "WiFi";
            String header = doc["Header"];
            if (header.compareTo("WiFi") != 0) {
                file.close();
                file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);
                WiFiBTConfig(&file);
                file.close();
                this->CheckFlag = true;
                return;
            }

            String ssid = doc["ssid"];
            String password = doc["password"];
            hgmApp->BeginWiFiWithConfig((char*)ssid.c_str(), (char*)password.c_str());

            file.close();
        }
        
    }

    this->CheckFlag = true;
}

static void WiFiBTConfig(File* file)
{

    hgmApp->BeginBT();
    vTaskDelay(500);
    Serial.println("Waiting the BT config WiFi...");

    while (!WiFi.isConnected()) {
        // TODO: LVGL Show
        vTaskDelay(50);
    }
        
    StaticJsonDocument<128> doc;
    String tmp;
    doc["Header"] = "WiFi";
    doc["ssid"] = HgmWiFi::GetSSID();
    doc["password"] = HgmWiFi::GetPassword();
    serializeJson(doc, tmp);
    file->write((const uint8_t*)tmp.c_str(), tmp.length());

    hgmApp->StopBT();
    vTaskDelay(500);
}
