/******************************************************************
 * @file HellGateMonitor.ino
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/11 20:19
 * @copyright Copyright (c) 2021/8/11
*******************************************************************/
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <User_Setup_Select.h>
#include <I2C_MPU6886.h>
#include <ArduinoJson.h>
#include <iostream>
#include <string>

/* User include files */
#include "Source/HgmApp/HgmBT/HgmBT.h"
#include "Source/HgmApp/HgmApp.h"
#include "Source/HgmLvgl/HgmLvgl.h"
#include "Source/HgmSelfChecking/HgmSelfChecking.h"

// TODO: TCP Server for projection
// TODO: TCP Client for getting another info
// TODO: Bluetooth for wifi config

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__

using namespace HGM;
using namespace HgmApplication;


char* ssid = "trisuborn";
char* password = "12345678";

extern HgmApp* hgmApp;
//extern HgmLvgl* hgmLvgl;

void setup()
{
    Serial.begin(115200);

    /* Base init */
    size_t codeSize = ESP.getSketchSize();
    Serial.printf("\n********** Hell Gate Monitor **********\n");
    Serial.printf("Date     : %s %s\n", COMPILE_DATE, COMPILE_TIME);
    Serial.printf("ESP-IDF  : %x\n", ESP_IDF_VERSION);
    Serial.printf("FreeRTOS : %s\n", tskKERNEL_VERSION_NUMBER);
    Serial.printf("LVGL     : V%d.%d.%d %s\n", lv_version_major(), lv_version_minor(), lv_version_patch(), lv_version_info());
    Serial.printf("Firmware : %0.2f MiB\n", codeSize / 1024.0 / 1024.0);
    Serial.printf("***************************************\n");

    hgmApp = new HgmApp(true);
    
    // TODO: Check the wifi config file in SPIFF
    HgmSC hgmSC;
    hgmSC.Begin();

    //hgmLvgl->HgmLvglBegin();
}


uint8_t buf[512];
void loop()
{

    //memset(buf, 0, 512);
    //if (SerialBT.available()) {
    //    /*String str = SerialBT.readString();
    //    Serial.println(str.c_str());*/

    //    int i = 0;
    //    while (SerialBT.available()) {
    //        buf[i] = SerialBT.read();
    //        i++;
    //    }
    //    Serial.printf("%s\n", buf);
    //}

    /*if (hgmApp->hgmBT->bs->connected()) {
        String test = "Hotakus";
        hgmApp->hgmBT->SendDatePack(test, HGM_BT_PACK_METHOD_OK);
    }*/

    vTaskDelay(1 * 1000);
}
