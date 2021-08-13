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

HgmApplication::HgmApp::HgmApp(bool flag)
{
    this->hgmWifi = new HgmWiFi(true);
    this->hgmBT = new HgmBT();
}

HgmApp::HgmApp(char* ssid, char* password)
{
    this->hgmWifi = new HgmWiFi(ssid, password);
    this->hgmBT = new HgmBT();
}

HgmApp::~HgmApp()
{
    delete this->hgmWifi;
    delete this->hgmBT;
}

/**
 * @brief All application begin in here.
 */
void HgmApplication::HgmApp::Begin()
{
    this->BeginWiFi();
    this->BeginBT();
}


void HgmApplication::HgmApp::BeginWiFi()
{
    // WiFi 
    this->hgmWifi->Begin();
}

void HgmApplication::HgmApp::BeginWiFiWithConfig(char* ssid, char* password)
{
    this->hgmWifi->ConfigWiFi(ssid, password);
    this->hgmWifi->Begin();
}

void HgmApplication::HgmApp::BeginBT()
{
    // Bluetooth
    this->hgmBT->Begin();
}

void HgmApplication::HgmApp::Stop()
{
}

void HgmApplication::HgmApp::StopWiFi()
{
    this->hgmWifi->Stop();
}

void HgmApplication::HgmApp::StopBT()
{
    this->hgmBT->Stop();
}



