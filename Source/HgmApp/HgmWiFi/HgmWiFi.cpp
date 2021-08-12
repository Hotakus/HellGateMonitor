/******************************************************************
 * @file HgmWiFi.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/12 5:52
 * @copyright Copyright (c) 2021/8/12
*******************************************************************/
#include <WiFi.h>
#include "HgmWiFi.h"
#include "../HgmApp.h"

using namespace HgmApplication;

static bool wifiSwitch;		// To control the WiFi's on/off

static WiFiClass wifi = WiFi;
static char* _ssid = NULL;
static char* _password = NULL;

static TaskHandle_t wifiCheckTaskHandle   = NULL;
static TaskHandle_t wifiControlTaskHandle = NULL;
static QueueHandle_t wifiCtlMsgBox = NULL;
static void wifiCheckTask(void* params);
static void wifiControlTask(void* params);

HgmWiFi::HgmWiFi()
{
    // TODOs
}

HgmWiFi::HgmWiFi(char* ssid, char* password)
{
    _ssid = ssid;
    _password = password;
}

HgmWiFi::~HgmWiFi()
{
    // TODO
}

/**
 * @brief Configuring the WiFi ssid and password.
 * @param ssid
 * @param password
 */
void HgmApplication::HgmWiFi::ConfigWiFi(char* ssid, char* password)
{
    _ssid = ssid;
    _password = password;
}

/**
 * @brief Use to open or close wifi.
 * @param sw
 */
void HgmApplication::HgmWiFi::OpenWiFi(bool sw)
{
    wifiSwitch = sw;
    vTaskDelay(10);
    if (xQueueSend(wifiCtlMsgBox, &wifiSwitch, portMAX_DELAY) == pdPASS) {
        Serial.print("WiFi is open (");
        Serial.print(wifiSwitch);
        Serial.println(")");
    } else {
        Serial.println("Switch the wifi on/off failed.");
    }
}

/**
 * @brief Begin the WiFi.
 */
void HgmApplication::HgmWiFi::Begin()
{

    if (!_ssid || !_password) {
        Serial.println("SSID or Password has not been given. \n WiFi begin failed.");
        return;
    }

    /* Init WiFi relative tasks */
    this->wifiTaskInit();
    this->OpenWiFi();
}

/**
 * @brief All WiFi application are initialized in here.
 */
void HgmApplication::HgmWiFi::wifiTaskInit()
{
    wifiCtlMsgBox = xQueueCreate(1, sizeof(bool));

    xTaskCreatePinnedToCore(
        wifiCheckTask,
        "wifiCheckTask",
        4096,
        NULL,
        7,
        &wifiCheckTaskHandle,
        1
    );
    xTaskCreatePinnedToCore(
        wifiControlTask,
        "wifiControlTask",
        4096,
        NULL,
        10,
        &wifiControlTaskHandle,
        1
    );
}

/**
 * @brief WiFi check task.
 * @param params
 */
static void wifiCheckTask(void* params)
{
    static uint8_t cnt = 0;
    static bool flag = false;

    while (true) {
        if (wifiSwitch == false) {
            vTaskDelay(2000);
            continue;
        }
        if (wifi.status() != WL_CONNECTED) {
            cnt += 1;
            if (cnt == 255) {
                cnt = 0;
                wifi.disconnect();
                wifi.mode(WIFI_USE_MODE);
                wifi.begin(_ssid, _password);
            }
            vTaskDelay(500);
            continue;
        }
        cnt = 0;

        if (!flag) {
            flag = true;
            Serial.println("WiFi Connected");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
            Serial.println(WiFi.getTxPower());
            Serial.println(WiFi.RSSI());
        }

        vTaskDelay(2000);
    }
}


/**
 * @brief To Control WiFi application.
 * @param params
 */
static void wifiControlTask(void* params)
{
    static bool sw = false;

    while (true) {
        if (xQueueReceive(wifiCtlMsgBox, &sw, portMAX_DELAY) != pdPASS)
            continue;

        if (sw == true) {
            wifi.mode(WIFI_USE_MODE);
            wifi.begin(_ssid, _password);
            wifi.setTxPower(WIFI_POWER_15dBm);
        } else {
            wifi.mode(WIFI_OFF);
            wifi.disconnect();
            wifi.setSleep(true);
        }
    }
}



