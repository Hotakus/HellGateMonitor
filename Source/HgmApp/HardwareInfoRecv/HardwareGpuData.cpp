/******************************************************************
 * @file HardwareGpuData.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/22 22:53
 * @copyright Copyright (c) 2021/9/22
*******************************************************************/
#include "HardwareGpuData.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;


HgmApplication::HardwareGpuData::HardwareGpuData()
{
}

HgmApplication::HardwareGpuData::~HardwareGpuData()
{
}

void HgmApplication::HardwareGpuData::Set(HotakusDynamicJsonDocument& hdjd)
{
    this->name = hdjd["Data"]["GPU"]["name"].as<String>();

    this->tempCoreCur = hdjd["Data"]["GPU"]["temp"]["current"].as<float>();
    this->tempCoreMax = hdjd["Data"]["GPU"]["temp"]["max"].as<float>();

    this->coreFreq = hdjd["Data"]["GPU"]["freq"]["core"]["current"].as<float>();
    this->memFreq = hdjd["Data"]["GPU"]["freq"]["mem"]["current"].as<float>();

    this->coreLoad = hdjd["Data"]["GPU"]["load"]["coreCurrent"].as<float>();
    this->coreLoadMax = hdjd["Data"]["GPU"]["load"]["coreMax"].as<float>();

    this->powerCur = hdjd["Data"]["GPU"]["power"]["current"].as<float>();
    this->powerMax = hdjd["Data"]["GPU"]["power"]["max"].as<float>();
}
