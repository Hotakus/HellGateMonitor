/******************************************************************
 * @file HgmWiFi.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/12 5:52
 * @copyright Copyright (c) 2021/8/12
*******************************************************************/
#include "HgmWiFi.h"
#include "../HotakusMemUtil.h"

#include <WiFi.h>
#include <HTTPClient.h>

using namespace HgmApplication;

static bool wifiSwitch = true;		// To control the WiFi's on/off

static WiFiClass _wifi = WiFi;
static String _ssid;
static String _password;

static TaskHandle_t wifiCheckTaskHandle = NULL;
static TaskHandle_t wifiControlTaskHandle = NULL;
static QueueHandle_t wifiCtlMsgBox = NULL;
static void wifiCheckTask(void* params);
static void wifiControlTask(void* params);

HgmWiFi hgmWiFi;
HTTPClient *https;

HgmWiFi::HgmWiFi()
{
    https = new HTTPClient();
    this->wifi = &_wifi;
    this->hgmTcp = new HgmTCP();
    this->WifiTaskInit();

    this->hgmTcp->begin();
}

HgmWiFi::HgmWiFi(String ssid, String password)
{
    https = new HTTPClient();
    _ssid = ssid;
    _password = password;

    this->wifi = &_wifi;
    this->hgmTcp = new HgmTCP();
    this->WifiTaskInit();

    this->hgmTcp->begin();
}

HgmWiFi::~HgmWiFi()
{
    delete this->hgmTcp;
    vTaskDelete(wifiControlTaskHandle);
    vQueueDelete(wifiCtlMsgBox);
    delete https;

    this->hgmTcp->stop();
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
    if (xQueueSend(wifiCtlMsgBox, &wifiSwitch, portMAX_DELAY) == pdPASS) {
        Serial.println(
            sw ? "Open wifi" : "Close wifi"
        );
    } else {
        Serial.println("Switch the _wifi on/off failed.");
    }

    // if (sw) {
    //     if (wifiCheckTaskHandle == NULL) {
    //         uint16_t timeout = 10 * 1000;
    // 
    //         _wifi.setHostname(WIFI_DEFAULT_NAME);
    //         _wifi.mode(WIFI_USE_MODE);
    //         _wifi.setSleep(true);
    //         _wifi.setAutoReconnect(true);
    //         _wifi.setTxPower(WIFI_POWER_15dBm);
    //         _wifi.begin(_ssid.c_str(), _password.c_str());
    //         while (_wifi.status() != WL_CONNECTED && timeout > 0) {
    //             vTaskDelay(500);
    //             Serial.print(".#");
    //             Serial.print(_wifi.status());
    //             timeout -= 500;
    //         }
    //         if (timeout <= 0) {
    //             Serial.println("WiFi open failed.");
    // 
    //             hgmWiFi.OpenTCP(false, false);
    //             hgmWiFi.OpenTCP(false, true);
    // 
    //             _wifi.disconnect();
    //             _wifi.mode(WIFI_OFF);
    //             return;
    //         }
    // 
    //         Serial.println("\nWiFi Connected successfully.");
    //         Serial.printf("Local IP Address: %s\n", WiFi.localIP().toString().c_str());
    //         Serial.printf("RSSI : %d\n", WiFi.RSSI());
    //     } else {
    //         Serial.println("WiFi open already.");
    //     }
    // } else {
    //     if (wifiCheckTaskHandle) {
    //         vTaskDelete(wifiCheckTaskHandle);
    //         wifiCheckTaskHandle = NULL;
    //         Serial.println("WiFi close.");
    //     } else {
    //         Serial.println("WiFi close already.");
    //     }
    // 
    //     _wifi.disconnect();
    //     _wifi.mode(WIFI_OFF);
    // }
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
        if (asServer) {
            this->hgmTcp->StopServer();
        } else
            this->hgmTcp->StopClient();
    }
}

/**
 * @brief Begin the WiFi.
 */
void HgmApplication::HgmWiFi::begin()
{
    this->OpenWiFi();

    // this->OpenTCP(true, true);          // Open TCP Server
    // this->OpenTCP(true, false);         // Open TCP client

    uint16_t timeout = 10 * 1000;
}

/**
 * @brief Stop the WiFi and.
 */
void HgmApplication::HgmWiFi::stop()
{
    // this->OpenTCP(false, true);     // Close server
    // this->OpenTCP(false, false);    // Close client

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
        2048 + 128,
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
                uint16_t timeout = 10 * 1000;

                _wifi.setHostname(WIFI_DEFAULT_NAME);
                _wifi.mode(WIFI_USE_MODE);
                _wifi.setSleep(true);
                _wifi.setAutoReconnect(true);
                _wifi.setTxPower(WIFI_POWER_15dBm);
                _wifi.begin(_ssid.c_str(), _password.c_str());
                while (_wifi.status() != WL_CONNECTED && timeout > 0) {
                    vTaskDelay(500);
                    Serial.print(".#");
                    Serial.print(_wifi.status());
                    timeout -= 500;
                }
                if (timeout <= 0) {
                    Serial.println("WiFi open failed.");

                    hgmWiFi.OpenTCP(false, false);
                    hgmWiFi.OpenTCP(false, true);

                    _wifi.disconnect();
                    _wifi.mode(WIFI_OFF);
                } else {
                    Serial.println("\nWiFi Connected successfully.");
                    Serial.printf("Local IP Address: %s\n", WiFi.localIP().toString().c_str());
                    Serial.printf("RSSI : %d\n", WiFi.RSSI());
                }
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

