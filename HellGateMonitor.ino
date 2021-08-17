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

#define SCREEN_BK_PIN   32

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__

using namespace HGM;
using namespace HgmApplication;


char* ssid = "trisuborn";
char* password = "12345678";

extern HgmApp* hgmApp;
extern HgmLvgl* hgmLvgl;


static QueueHandle_t bkMsgBox;
static TaskHandle_t bkHandle;
// Show the init progress task
static void backlightControl(void* params)
{
    bool flag = false;
    while (true) {
        if (xQueueReceive(bkMsgBox, &flag, portMAX_DELAY) != pdPASS) {

        }

        if (flag) {
            for (size_t i = 0; i < 255; i++) {
                ledcWrite(0, i);
                vTaskDelay(10);
            }
        } else {
            for (size_t i = 255; i > 0; i--) {
                ledcWrite(0, i);
                vTaskDelay(10);
            }
        }
    }
}

void setup()
{
    Serial.begin(115200);

    size_t codeSize = ESP.getSketchSize();
    Serial.printf("\n************** Hell Gate Monitor **************\n");
    Serial.printf("           ___           ___           ___               \n");
    Serial.printf("          /\\__\\         /\\  \\         /\\__\\        \n");
    Serial.printf("         /:/  /        /::\\  \\       /::|  |           \n");
    Serial.printf("        /:/__/        /:/\\:\\  \\     /:|:|  |          \n");
    Serial.printf("       /::\\  \\ ___   /:/  \\:\\  \\   /:/|:|__|__      \n");
    Serial.printf("      /:/\\:\\  /\\__\\ /:/__/_\\:\\__\\ /:/ |::::\\__\\ \n");
    Serial.printf("      \\/__\\:\\/:/  / \\:\\  /\\ \\/__/ \\/~~/__/:/  /  \n");
    Serial.printf("           \\::/  /   \\:\\ \\:\\__\\         /:/  /     \n");
    Serial.printf("           /:/  /     \\:\\/:/  /        /:/  /          \n");
    Serial.printf("          /:/  /       \\::/  /        /:/  /            \n");
    Serial.printf("          \\/__/         \\/__/         \\/__/           \n\n");
    Serial.printf("Date     : %s %s\n", COMPILE_DATE, COMPILE_TIME);
    Serial.printf("ESP-IDF  : %x\n", ESP_IDF_VERSION);
    Serial.printf("FreeRTOS : %s\n", tskKERNEL_VERSION_NUMBER);
    Serial.printf("LVGL     : V%d.%d.%d %s\n", lv_version_major(), lv_version_minor(), lv_version_patch(), lv_version_info());
    Serial.printf("Firmware : %0.2f MiB\n", codeSize / 1024.0 / 1024.0);
    Serial.printf("Github   : https://github.com/Hotakus/HellGateMonitor \n");
    Serial.printf("***********************************************\n");

    ledcAttachPin(SCREEN_BK_PIN, 0);
    ledcSetup(0, (10 * 1000), 8);   // PWM 10kHz
    ledcWrite(0, 0);

    bkMsgBox = xQueueCreate(1, sizeof(bool));
    xTaskCreatePinnedToCore(
        backlightControl,
        "backlightControl",
        1024,
        NULL,
        5,
        &bkHandle,
        1
    );

    /* HGM LVGL Component initialize */
    Wire1.begin(21, 22);
    hgmLvgl->HgmLvglBegin();

    bool flag = true;
    xQueueSend(bkMsgBox, &flag, portMAX_DELAY); // Open backloght

    hgmLvgl->HgmLvglUIBegin();

    /*HgmSC hgmSC;
    hgmSC.Begin();

    BiliInfoRecv bili;
    bili.SetUID("341974201");
    bili.GetBasicInfo();
    bili.GetFollower();
    bili.GetUserFaceImg();
    uint8_t* face;
    size_t size = 0;
    face = bili.GetUserFaceImgBuf(&size);
    Serial.printf("%x\n", face);

    hgmApp = new HgmApp(true);
    hgmApp->StopBT();
    vTaskDelay(200);
    hgmApp->BeginBT();*/
}

void loop()
{
    
}
