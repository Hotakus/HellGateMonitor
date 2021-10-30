/******************************************************************
 * @file HgmSelfChecking.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/13 17:57
 * @copyright Copyright (c) 2021/8/13
*******************************************************************/

#include "../HgmApp/HgmWiFi/HgmWiFi.h"
#include "HgmSelfChecking.h"
#include "../HgmLvgl/HgmGUI/HgmSetupView.h"
#include "../HgmApp/WeatherInfo/WeatherInfo.h"

#include "../HgmApp/HgmWiFi/HgmWiFi.h"
#include "../HgmApp/HgmBT/HgmBT.h"
#include "../HgmLvgl/HgmLvgl.h"
#include "../HgmSelfChecking/HgmSelfChecking.h"
#include "../HgmApp/TimeInfo/TimeInfo.h"
#include "../HgmApp/BiliInfoRecv/BiliInfoRecv.h"
#include "../HgmLvgl/HgmGUI/HgmSetupView.h"
#include "../HgmApp/WeatherInfo/WeatherInfo.h"
#include "../HgmApp/HotakusMemUtil.h"
#include "../HgmApp/HotakusHttpUtil.h"
#include "../HgmApp/HardwareInfoRecv/HardwareRequest.h"
#include "../Utils/MsgCenter/MsgCenter.h"
#include "../Utils/SPIFFSUtil/SPIFFSUtil.h"

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#define TAG "HgmSC"
#define HGM_DEBUG 1
#include "../HgmLogUtil.h"

using namespace HGM;
using namespace HgmGUI;
using namespace HgmApplication;
using namespace fs;
using namespace msgmanager;
using namespace spiffsutil;

extern HgmSetupView* hgmSetupUI;

extern HgmWiFi hgmWiFi;
extern HgmBT hgmBT;
extern TimeInfo ti;
extern BiliInfoRecv bili;
extern WeatherInfo weatherInfo;

static void err_cb(const String& err)
{
    hgm_log_e(TAG, "%s", err.c_str());
    while (true) {
        vTaskDelay(1);
    };
}

void HGM::HgmSC::begin()
{
    hgmSetup = new HgmSetupView;
    hgmSetup->begin();
    
    checkBT();
    checkSpiffs();
    checkWiFi();
    checkTime();
    checkBili();
    checkWeather();
    
    hgmSetup->end();
    delete hgmSetup;
}

void HGM::HgmSC::setState(HgmComponentType ct, bool cur, bool wait)
{
    component.type = ct;
    component.curStatus = cur;
    component.waitStatus = wait;
    hgmSetupUI->componentControl(&component);
}

void HGM::HgmSC::checkBT()
{
    setState(HGM_COMPONENT_BT, true, false);
    hgmBT.setName();
    hgmBT.begin();
    while (!hgmBT.bs->isReady())
        vTaskDelay(100);
    component.waitStatus = true;
    vTaskDelay(300);
}

void HGM::HgmSC::checkSpiffs()
{
    if (!Sfu::begin()) {
        setState(HGM_COMPONENT_SPIFFS, false, false);
        err_cb(String("SPIFFS check failed."));
    }
    setState(HGM_COMPONENT_SPIFFS, true, true);
}

void HGM::HgmSC::checkWiFi()
{
    bool ret = Sfu::existsNoZero(WIFI_CONFIG_FILE_PATH);
    if (!ret) {
        setState(HGM_COMPONENT_WIFI, false, false);
        err_cb(String("WiFi check failed. (No existing)"));
    }

    HDJsonDoc doc(512);
    ret = Sfu::readJson(String(WIFI_CONFIG_FILE_PATH), doc);
    if (!ret) {
        setState(HGM_COMPONENT_WIFI, false, false);
        err_cb(String("WiFi check failed. (json parse error)"));
    }

    String ssid = doc["ssid"];
    String passwd = doc["password"];
    hgmWiFi.ConfigWiFi(ssid, passwd);
    hgmWiFi.begin();

    setState(HGM_COMPONENT_WIFI, true, false);
    while (!WiFi.isConnected())
        vTaskDelay(100);
    component.waitStatus = true;
}

void HGM::HgmSC::checkTime()
{
}

void HGM::HgmSC::checkBili()
{
}

void HGM::HgmSC::checkWeather()
{
}
