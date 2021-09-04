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

static WiFiClass _wifi = WiFi;
static String _ssid ;
static String _password ;

static TaskHandle_t wifiCheckTaskHandle = NULL;
static TaskHandle_t wifiControlTaskHandle = NULL;
static QueueHandle_t wifiCtlMsgBox = NULL;
static void wifiCheckTask(void* params);
static void wifiControlTask(void* params);

HgmWiFi::HgmWiFi(bool flag)
{
    this->wifi = &_wifi;

    this->hgmTcp = new HgmTCP();
    this->WifiTaskInit();
    this->hgmTcp->Begin();
}

HgmWiFi::HgmWiFi(String ssid, String password)
{
    _ssid = ssid;
    _password = password;

    this->wifi = &_wifi;

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
void HgmApplication::HgmWiFi::ConfigWiFi(String ssid, String password)
{
    _ssid = ssid;
    _password = password;
    this->ssid = ssid;
    this->password = password;
}

/**
 * @brief Use to open or close _wifi.
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
        Serial.println("Switch the _wifi on/off failed.");
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
    this->OpenWiFi();

    // _wifi.mode(WIFI_STA);
    // _wifi.setSleep(true); //关闭STA模式下wifi休眠，提高响应速度
    // _wifi.begin("trisuborn", "12345678");
    // while (_wifi.status() != WL_CONNECTED) {
    // 	vTaskDelay(500);
    // 	Serial.print(".");
    // }
    // Serial.println("Connected");
    // Serial.print("IP Address:");
    // Serial.println(_wifi.localIP());

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
        2048,
        NULL,
        5,
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
                _wifi.mode(WIFI_USE_MODE);
                _wifi.setSleep(true);
                _wifi.setAutoReconnect(true);
                _wifi.setTxPower(WIFI_POWER_15dBm);
                Serial.printf("wifiControlTask %s %s\n", _ssid, _password);
                _wifi.begin(_ssid.c_str(), _password.c_str());
                while (_wifi.status() != WL_CONNECTED) {
                    vTaskDelay(500);
                    Serial.print(".#");
                    Serial.println(_wifi.status());
                }

                xTaskCreatePinnedToCore(
                    wifiCheckTask,
                    "wifiCheckTask",
                    1024,
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
                vTaskDelete(wifiCheckTaskHandle);
                wifiCheckTaskHandle = NULL;
                Serial.println("WiFi close.");
            } else {
                Serial.println("WiFi close already.");
            }

            _wifi.disconnect();
            _wifi.mode(WIFI_OFF);
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

        if (_wifi.status() == WL_IDLE_STATUS) {
            vTaskDelay(500);
            continue;
        }

        if (_wifi.status() != WL_CONNECTED) {
            Serial.print(".-");
            Serial.println(_wifi.status());
            vTaskDelay(500);
            flag = false;
            continue;
        }

        if (!flag) {
            Serial.println("");
            flag = true;

            Serial.println("\nWiFi Connected");
            Serial.print("Local IP Address: ");
            Serial.println(WiFi.localIP());
            Serial.print("RSSI : ");
            Serial.println(WiFi.RSSI());
        }

        vTaskDelay(2000);
    }
}




