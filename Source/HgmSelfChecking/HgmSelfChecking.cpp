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

#include "../HgmApp/HgmWiFi/HgmWiFi.h"
#include "HgmSelfChecking.h"

using namespace HGM;
using namespace fs;

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
        this->beginFlag = false;
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

        // If file size equal to zero, then begin BT config
        // if (!file.size())
        Serial.printf("WiFi config file size : %d\n", file.size());

        file.close();
    } else {
        // TODO: If there is the config file, read and analyze the json content then store to HgmWiFi object.
        // TODO: Create mailbox in HgmWiFi, then this function send a mail to trigger wifi config function.
        // TODO: If read content from wifi config file is null, then show log and begin BT config
        Serial.println("Found the WiFi config file.");
    }

    this->beginFlag = true;
}
