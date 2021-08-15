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

static TaskHandle_t wifiCheckTaskHandle = NULL;
static TaskHandle_t wifiControlTaskHandle = NULL;
static QueueHandle_t wifiCtlMsgBox = NULL;
static void wifiCheckTask(void* params);
static void wifiControlTask(void* params);

HgmWiFi::HgmWiFi(bool flag)
{
    this->hgmTcp = new HgmTCP();
    this->WifiTaskInit();
    this->hgmTcp->Begin();
}

HgmWiFi::HgmWiFi(char* ssid, char* password)
{
    _ssid = ssid;
    _password = password;

    this->hgmTcp = new HgmTCP();
    this->WifiTaskInit();
    this->hgmTcp->Begin();
}

HgmWiFi::~HgmWiFi()
{
    delete this->hgmTcp;

    // TODO: finish the gc
    vTaskDelete(wifiControlTaskHandle);
    vQueueDelete(wifiCtlMsgBox);
}

/**
 * @brief Configuring the WiFi ssid and password.
 * @param ssid
 * @param password
 */
void HgmApplication::HgmWiFi::ConfigWiFi(char* ssid, char* password)
{
    
    this->Stop();
    vTaskDelay(2 * 1000);

    _ssid = ssid;
    _password = password;
    this->ssid = ssid;
    this->password = password;
    
    this->Begin();
    vTaskDelay(2 * 1000);
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
        Serial.println(
            sw ? "Open wifi" : "Close wifi"
        );
    } else {
        Serial.println("Switch the wifi on/off failed.");
    }
}

/**
 * @brief Open TCP as the server at default.
 * @param sw to control on/off
 * @param asServer to control asServer of asClient
 */
void HgmApplication::HgmWiFi::OpenTCP(bool sw, bool asServer)
{
    if (sw) {
        if (asServer)
            this->hgmTcp->BeginServer();
        else
            this->hgmTcp->BeginClient();
    } else {
        if (asServer)
            this->hgmTcp->StopServer();
        else
            this->hgmTcp->StopClient();
    }
}

/**
 * @brief Begin the WiFi.
 */
void HgmApplication::HgmWiFi::Begin()
{

    if (!_ssid || !_password) {
        Serial.println("SSID or Password has not been given. \n WiFi begin failed. \n");
        return;
    }

    this->OpenWiFi();

    this->OpenTCP(true, true);          // Open TCP Server
    this->OpenTCP(true, false);         // Open TCP client
}

/**
 * @brief Stop the WiFi and.
 */
void HgmApplication::HgmWiFi::Stop()
{
    this->OpenTCP(false, true);     // Close server
    this->OpenTCP(false, false);    // Close client

    this->OpenWiFi(false);
}

String HgmApplication::HgmWiFi::GetSSID()
{
    return _ssid;
}

String HgmApplication::HgmWiFi::GetPassword()
{
    return _password;
}

/**
 * @brief All WiFi application are initialized in here.
 */
void HgmApplication::HgmWiFi::WifiTaskInit()
{
    wifiCtlMsgBox = xQueueCreate(1, sizeof(bool));

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
            if (wifiCheckTaskHandle == NULL) {
                wifi.mode(WIFI_USE_MODE);
                wifi.begin(_ssid, _password);
                wifi.setTxPower(WIFI_POWER_15dBm);
                xTaskCreatePinnedToCore(
                    wifiCheckTask,
                    "wifiCheckTask",
                    4096,
                    NULL,
                    7,
                    &wifiCheckTaskHandle,
                    1
                );
                Serial.println("WiFi open.");
            } else {
                Serial.println("WiFi open already.");
            }
        } else {
            if (wifiCheckTaskHandle) {
                wifi.mode(WIFI_OFF);
                wifi.disconnect();
                wifi.setSleep(true);
                vTaskDelete(wifiCheckTaskHandle);
                wifiCheckTaskHandle = NULL;
                Serial.println("WiFi close.");
            } else {
                Serial.println("WiFi close already.");
            }
        }
    }
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
            if (cnt == 20) {
                cnt = 0;
                wifi.disconnect();
                wifi.mode(WIFI_USE_MODE);
                wifi.begin(_ssid, _password);
            }
            Serial.print(".");
            vTaskDelay(500);
            continue;
        }
        cnt = 0;

        if (!flag) {
            Serial.println("");
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




