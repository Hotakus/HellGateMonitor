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
    File file = NULL;

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
        file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);

    }

    if (!file)
    file.close();


    this->beginFlag = true;
}
