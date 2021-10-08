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
#include "Source/HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "Source/HgmApp/WeatherInfo/WeatherInfo.h"

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <User_Setup_Select.h>
#include <I2C_MPU6886.h>
#include <ArduinoJson.h>
#include <iostream>
#include <string>
#include <TJpg_Decoder.h>
#include <SPIFFS.h>
#include <freertos/FreeRTOSConfig.h>


#define SCREEN_BK_PIN   32

#define HGM_VERSION_INFO  "dev"
#define HGM_VERSION_MAJOR 1
#define HGM_VERSION_MINOR 0
#define HGM_VERSION_PATCH 0

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__

using namespace HGM;
using namespace HgmGUI;
using namespace HgmApplication;
using namespace fs;

extern HgmWiFi hgmWiFi;
extern HgmBT hgmBT;
extern TimeInfo ti;
extern BiliInfoRecv bili;
extern WeatherInfo weatherInfo;
extern HgmLvgl* hgmLvgl;

static QueueHandle_t bkMsgBox;
static TaskHandle_t bkHandle;

SemaphoreHandle_t wbs;
HgmComponent component;

float firmwareSize = 0;


static String wurl = "https://devapi.qweather.com/v7/air/now?gzip=n&location=108.241,23.172&key=bc1f1bdefb944930bef0208ecd03f66a";
extern HTTPClient* https;

// Show the init progress task
static void backlightControl(void* params)
{
    bool flag = false;

    ledcAttachPin(SCREEN_BK_PIN, 0);
    ledcSetup(0, (10 * 1000), 8);   // PWM 10kHz
    ledcWrite(0, 0);

    while (true) {
        if (xQueueReceive(bkMsgBox, &flag, portMAX_DELAY) != pdPASS) {

        }

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

    hgmBT.Stop();
    while (hgmBT.bs->isReady())
        vTaskDelay(500);

    //hgmWiFi.Stop();
    //while (WiFi.isConnected())
    //    vTaskDelay(500);

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
    xTaskCreatePinnedToCore(backlightControl, "backlightControl", 1024, NULL, 5, &bkHandle, 1);

    // Semaphore for BT and WiFi. Don't remove it
    wbs = xSemaphoreCreateBinary();
    xSemaphoreGive(wbs);

    /* HGM LVGL initialize */
    hgmLvgl->HgmLvglBegin();

    bool flag = true;
    xQueueSend(bkMsgBox, &flag, portMAX_DELAY); // Open backlight

    HgmSetupUI* hgmSetupUI = new HgmSetupUI();
    hgmSetupUI->Begin();

    // Open bluetooth
    component.type = HGM_COMPONENT_BT;
    component.curStatus = true;
    component.waitStatus = false;
    hgmSetupUI->ComponentControl(&component);
    hgmBT.SetName();
    hgmBT.Begin();
    while (!hgmBT.bs->isReady())
        vTaskDelay(200);
    component.waitStatus = true;
    vTaskDelay(200);

    // Check config file
    HgmSC hgmSC;
    hgmSC.Begin();
    vTaskDelay(200);

    // Check WiFi
    component.type = HGM_COMPONENT_WIFI;
    component.curStatus = true;
    component.waitStatus = false;
    hgmSetupUI->ComponentControl(&component);
    hgmWiFi.Begin();
    while (!hgmWiFi.wifi->isConnected())
        vTaskDelay(100);
    component.waitStatus = true;
    vTaskDelay(300);

    // Check time
    ti.Begin();
    vTaskDelay(300);

    // Check bilibili component
    bili.Begin();
    vTaskDelay(300);

    // Check weather
    weatherInfo.Begin();
    vTaskDelay(300);

    // All done
    component.type = HGM_COMPONENT_DONE;
    component.curStatus = true;
    component.waitStatus = true;
    hgmSetupUI->ComponentControl(&component);
    vTaskDelay(500);
    hgmSetupUI->ComponentInitDone();
    delete hgmSetupUI;

    hgmLvgl->HgmLvglUIBegin();


    char* task_buf = (char*)heap_caps_calloc(1, 8192, MALLOC_CAP_SPIRAM);
    vTaskList(task_buf);
    //vTaskGetRunTimeStats(task_buf);
    Serial.printf("%s\n", task_buf);
    heap_caps_free(task_buf);
    Serial.printf("[%d] free mem : %d\n", uxTaskGetNumberOfTasks(),
        heap_caps_get_free_size(MALLOC_CAP_INTERNAL));

}


void loop()
{
    Serial.printf("[%d] free mem : %d\n", uxTaskGetNumberOfTasks(),
        heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    vTaskDelay(10 * 60 * 1000);
}
