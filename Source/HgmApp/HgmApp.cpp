/******************************************************************
 * @file HgmApp.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ESP32 as WiFi STA and TCP Server
 * @version 1.0
 * @date 2021/8/11 21:57
 * @copyright Copyright (c) 2021/8/11
*******************************************************************/

#include <WiFi.h>
#include <Arduino.h>
#include "HgmApp.h"

using namespace HgmApplication;

static WiFiClass wifi = WiFi;

HgmApplication::HgmApp::HgmApp()
{
    // TODO
}

HgmApp::HgmApp(char* ssid, char* password)
{
    this->hgmWifi = new HgmWiFi(ssid, password);
}

HgmApp::~HgmApp()
{
    delete this->hgmWifi;
}

/**
 * @brief All application begin in here.
 */
void HgmApplication::HgmApp::Begin()
{
    // WiFi app
    this->hgmWifi->Begin();
    //
}



