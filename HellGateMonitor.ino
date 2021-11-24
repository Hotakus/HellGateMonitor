/******************************************************************
 * @file HellGateMonitor.ino
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/11 20:19
 * @copyright Copyright (c) 2021/9/16
*******************************************************************/

/* User include files */
#include "Source/HgmApp/HgmWiFi/HgmWiFi.h"
#include "Source/HgmApp/HgmBT/HgmBT.h"
#include "Source/HgmLvgl/HgmLvgl.h"
#include "Source/HgmSelfChecking/HgmSelfChecking.h"
#include "Source/HgmApp/TimeInfo/TimeInfo.h"
#include "Source/HgmApp/BiliInfoRecv/BiliInfoRecv.h"
#include "Source/HgmLvgl/HgmGUI/HgmSetupView.h"
#include "Source/HgmApp/WeatherInfo/WeatherInfo.h"
#include "Source/HgmApp/HotakusMemUtil.h"
#include "Source/HgmApp/HotakusHttpUtil.h"
#include "Source/HgmApp/HardwareInfoRecv/HardwareRequest.h"
#include "Source/Utils/MsgCenter/MsgCenter.h"
#include "Source/Utils/SPIFFSUtil/SPIFFSUtil.h"

#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <User_Setup_Select.h>
#include <I2C_MPU6886.h>
#include <ArduinoJson.h>
#include <iostream>
#include <TJpg_Decoder.h>
#include <SPIFFS.h>
#include <freertos/FreeRTOSConfig.h>

#define SCREEN_BK_PIN   32

#define HGM_VERSION_INFO  "dev"
#define HGM_VERSION_MAJOR 0
#define HGM_VERSION_MINOR 7
#define HGM_VERSION_PATCH 0

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__

using namespace HGM;
using namespace HgmGUI;
using namespace HgmApplication;
using namespace fs;
using namespace msgmanager;
using namespace spiffsutil;

extern HgmWiFi hgmWiFi;
extern HgmBT hgmBT;
extern TimeInfo ti;
extern BiliInfoRecv bili;
extern WeatherInfo weatherInfo;
extern HgmLvgl hgmLvgl;

static QueueHandle_t bkMsgBox;
static TaskHandle_t bkHandle;

SemaphoreHandle_t wbs;

float firmwareSize = 0;

// Show the init progress task
static void backlightControl(void* params)
{
    bool flag = false;
    
    ledcAttachPin(SCREEN_BK_PIN, 0);
    ledcSetup(0, (10 * 1000), 8);   // PWM 10kHz
    ledcWrite(0, 0);

    while (true) {
        if (xQueueReceive(bkMsgBox, &flag, portMAX_DELAY) != pdPASS)
            continue;
        if (flag) {
            for (size_t i = 0; i < 127; i++) {
                ledcWrite(0, i);
                vTaskDelay(13);
            }
        } else {
            for (size_t i = 127; i > 0; i--) {
                ledcWrite(0, i);
                vTaskDelay(13);
            }
        }
    }
}

void setup()
{
    Serial.begin(115200);

    firmwareSize = ESP.getSketchSize() / 1024.0 / 1024.0;

    Serial.printf("\n****************** Hell Gate Monitor ******************\n");
    Serial.printf("           ___           ___           ___               \n");
    Serial.printf("          /\\__\\         /\\  \\         /\\__\\        \n");
    Serial.printf("         /:/  /        /::\\  \\       /::|  |           \n");
    Serial.printf("        /:/__/        /:/\\:\\  \\     /:|:|  |          \n");
    Serial.printf("       /::\\  \\ ___   /:/  \\:\\  \\   /:/|:|__|__      \n");
    Serial.printf("      /:/\\:\\  /\\__\\ /:/__/_\\:\\__\\ /:/ |::::\\__\\ \n");
    Serial.printf("      \\/__\\:\\/:/  / \\:\\  /\\ \\/__/ \\/__/~~/:/  /  \n");
    Serial.printf("           \\::/  /   \\:\\ \\:\\__\\         /:/  /     \n");
    Serial.printf("           /:/  /     \\:\\/:/  /        /:/  /          \n");
    Serial.printf("          /:/  /       \\::/  /        /:/  /            \n");
    Serial.printf("          \\/__/         \\/__/         \\/__/           \n\n");
    Serial.printf("Date     : %s %s\n", COMPILE_DATE, COMPILE_TIME);
    Serial.printf("ESP-IDF  : %s\n", ESP.getSdkVersion());
    Serial.printf("FreeRTOS : %s\n", tskKERNEL_VERSION_NUMBER);
    Serial.printf("LVGL     : V%d.%d.%d %s\n", lv_version_major(), lv_version_minor(), lv_version_patch(),
        lv_version_info());
    Serial.printf("Firmware : V%d.%d.%d %s %0.2f MiB\n", HGM_VERSION_MAJOR, HGM_VERSION_MINOR, HGM_VERSION_PATCH,
        HGM_VERSION_INFO, firmwareSize);
    Serial.printf("Github   : https://github.com/Hotakus/HellGateMonitor \n");
    Serial.printf("********************************************************\n");

    bkMsgBox = xQueueCreate(1, sizeof(bool));
    xTaskCreatePinnedToCore(backlightControl, "backlightControl", 1024 + 128, NULL, 5, &bkHandle, 1);

    // Semaphore for BT and WiFi. Don't remove it
    wbs = xSemaphoreCreateBinary();
    xSemaphoreGive(wbs);
    
    /* HGM LVGL initialize */
    hgmLvgl.begin();

    bool flag = true;
    xQueueSend(bkMsgBox, &flag, portMAX_DELAY); // Open backlight

    HgmSC* hgmSC = new HgmSC;
    hgmSC->begin();
    delete hgmSC;

    hgmLvgl.guiBegin();
    
    char* task_buf = (char*)hotakusAlloc(8192); 
    vTaskList(task_buf);
    Serial.printf("%s\n", task_buf);
    hotakusFree(task_buf);

    //hgmLvgl.hgmFw->changeGUI("HgmTw");
}

void loop()
{
    Serial.printf("[%d] free mem : %d\n", uxTaskGetNumberOfTasks(),
        heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    char* task_buf = (char*)hotakusAlloc(8192);
    vTaskList(task_buf);
    Serial.printf("%s\n", task_buf);
    hotakusFree(task_buf);

    // vTaskDelay(10 * 60 * 1000);
    vTaskDelay(2000);
}
