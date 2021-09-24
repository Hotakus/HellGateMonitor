/******************************************************************
 * @file HardwareRequest.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/21 22:41
 * @copyright Copyright (c) 2021/9/21
*******************************************************************/
#include "HardwareCpuData.h"
#include "HardwareRequest.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;
using namespace HgmApplication;

HardwareRequest hardwareRequest;
static HardwareRequest hardwareRequestDefault;

HgmApplication::HardwareRequest::HardwareRequest()
{
}

HgmApplication::HardwareRequest::~HardwareRequest()
{

}

void HgmApplication::HardwareRequest::UseDefault()
{
    hardwareRequest = hardwareRequestDefault;
}


void HgmApplication::HardwareRequest::HardwareRequestConfig(HotakusDynamicJsonDocument& hdjd)
{
    
}
