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
#include <TJpg_Decoder.h>

/* User include files */
#include "Source/HgmApp/HgmBT/HgmBT.h"
#include "Source/HgmApp/HgmApp.h"
#include "Source/HgmLvgl/HgmLvgl.h"
#include "Source/HgmSelfChecking/HgmSelfChecking.h"
#include "Source/HgmApp/BiliInfoRecv/BiliInfoRecv.h"

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



TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
    tft.pushImage(x, y, w, h, bitmap);
    return 1;
}


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

    // TODO: Complete the UI transition after power on.
    ledcAttachPin(32, 0);
    ledcSetup(0, (10 * 1000), 8);
    ledcWrite(0, 0);

    //hgmLvgl->HgmLvglBegin();

    HgmSC hgmSC;
    hgmSC.Begin();

    BiliInfoRecv bili;
    bili.SetUID("341974201");
    bili.GetBasicInfo();
    bili.GetFollower();
    // bili.GetUserFaceImg();
    // uint8_t* face;
    // size_t size = 0;
    // face = bili.GetUserFaceImgBuf(&size);
    // Serial.printf("%x\n", face);

    // Initialise the TFT
    tft.begin();
    tft.fillScreen(TFT_RED);

    /*TJpgDec.setJpgScale(1);
    TJpgDec.setSwapBytes(true);
    TJpgDec.setCallback(tft_output);

    uint32_t t = millis();
    uint16_t w = 0, h = 0;
    TJpgDec.getJpgSize(&w, &h, face, size);
    Serial.print("Width = ");
    Serial.print(w);
    Serial.print(", height = ");
    Serial.println(h);
    TJpgDec.drawJpg(0, 0, face, size);
    t = millis() - t;
    Serial.print(t); Serial.println(" ms");*/

    hgmApp->StopBT();
    vTaskDelay(200);
    hgmApp->BeginBT();
}

void loop()
{
    for (size_t i = 0; i < 255; i++) {
        ledcWrite(0, i);
        vTaskDelay(10);
    }
    vTaskDelay(200);

    for (size_t i = 255; i > 0; i--) {
        ledcWrite(0, i);
        vTaskDelay(10);
    }
    vTaskDelay(200);
}
