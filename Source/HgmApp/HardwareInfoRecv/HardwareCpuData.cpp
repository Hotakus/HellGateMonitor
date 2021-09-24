/******************************************************************
 * @file HardwareCpuData.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/21 21:39
 * @copyright Copyright (c) 2021/9/21
*******************************************************************/
#include "HardwareCpuData.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

HardwareCpuData hardwareCpuData;

HardwareCpuData::HardwareCpuData()
{
    
}

HardwareCpuData::~HardwareCpuData()
{
    free(coreFreq);
    free(coreTemp);
    free(coreLoad);
}


void HgmApplication::HardwareCpuData::Set(HotakusDynamicJsonDocument& hdjd)
{
    this->coreCount = hdjd["Data"]["CPU"]["coreCount"].as<int8_t>();

    if (!coreFreq || !coreTemp || !coreLoad) {
        coreFreq = (float*)malloc(coreCount * sizeof(float));
        coreTemp = (float*)malloc(coreCount * sizeof(float));
        coreLoad = (float*)malloc(coreCount * sizeof(float));
    } else {
        coreFreq = (float*)realloc(coreFreq, coreCount * sizeof(float));
        coreTemp = (float*)realloc(coreTemp, coreCount * sizeof(float));
        coreLoad = (float*)realloc(coreLoad, coreCount * sizeof(float));
    }

    this->name = hdjd["Data"]["CPU"]["name"].as<String>();

    for (uint8_t i = 0; i < this->coreCount; i++)
        this->coreFreq[i] = hdjd["Data"]["CPU"]["freq"]["current"][i].as<float>();
    for (uint8_t i = 0; i < this->coreCount; i++)
        this->coreTemp[i] = hdjd["Data"]["CPU"]["temp"]["current"][i].as<float>();
    for (uint8_t i = 0; i < this->coreCount; i++)
        this->coreLoad[i] = hdjd["Data"]["CPU"]["load"]["current"][i].as<float>();

    this->tempMax = hdjd["Data"]["CPU"]["temp"]["max"].as<float>();
    this->tempAverage = hdjd["Data"]["CPU"]["temp"]["average"].as<float>();
    this->loadTotal = hdjd["Data"]["CPU"]["load"]["total"].as<float>();
    this->powerCur = hdjd["Data"]["CPU"]["power"]["current"].as<float>();
    this->powerMax = hdjd["Data"]["CPU"]["power"]["max"].as<float>();
}