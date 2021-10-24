/******************************************************************
 * @file HardwareMemData.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/22 23:22
 * @copyright Copyright (c) 2021/9/22
*******************************************************************/
#include "HardwareMemData.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;


HgmApplication::HardwareMemData::HardwareMemData()
{
}

HgmApplication::HardwareMemData::~HardwareMemData()
{
}

void HgmApplication::HardwareMemData::Set(HotakusDynamicJsonDocument& hdjd)
{
    this->load = hdjd["Data"]["Memory"]["load"]["current"].as<float>();
    this->loadMax = hdjd["Data"]["Memory"]["load"]["max"].as<float>();

    this->free = hdjd["Data"]["Memory"]["data"]["free"].as<float>();
    this->used = hdjd["Data"]["Memory"]["data"]["used"].as<float>();
    this->total = hdjd["Data"]["Memory"]["data"]["total"].as<float>();
}
