/******************************************************************
 * @file HardwareNetData.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/23 20:12
 * @copyright Copyright (c) 2021/9/23
*******************************************************************/
#include "HardwareNetData.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;


HgmApplication::HardwareNetData::HardwareNetData()
{
    wlan.nd.downloaded = 0;
    wlan.nd.uploaded = 0;
    wlan.nt.download = 0;
    wlan.nt.upload = 0;

    ethernet = wlan;
}

HgmApplication::HardwareNetData::~HardwareNetData()
{
}

void HgmApplication::HardwareNetData::Set(HDJsonDoc& hdjd)
{
    this->ethernet.nd.downloaded = hdjd["Data"]["Network"]["ethernet"]["data"]["downloaded"].as<float>();
    this->ethernet.nd.uploaded = hdjd["Data"]["Network"]["ethernet"]["data"]["uploaded"].as<float>();
    this->ethernet.nt.download = hdjd["Data"]["Network"]["ethernet"]["data"]["download"].as<float>();
    this->ethernet.nt.upload = hdjd["Data"]["Network"]["ethernet"]["data"]["upload"].as<float>();

    this->wlan.nd.downloaded = hdjd["Data"]["Network"]["wlan"]["data"]["downloaded"].as<float>();
    this->wlan.nd.uploaded = hdjd["Data"]["Network"]["wlan"]["data"]["uploaded"].as<float>();
    this->wlan.nt.download = hdjd["Data"]["Network"]["wlan"]["data"]["download"].as<float>();
    this->wlan.nt.upload = hdjd["Data"]["Network"]["wlan"]["data"]["upload"].as<float>();
}
