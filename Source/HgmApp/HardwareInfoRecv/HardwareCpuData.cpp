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
#include "../HotakusMemUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

HardwareCpuData::HardwareCpuData()
{
    
}

HardwareCpuData::~HardwareCpuData()
{
    hotakusFree(coreFreq);
    hotakusFree(coreTemp);
    hotakusFree(coreLoad);
}


void HgmApplication::HardwareCpuData::Set(HDJsonDoc& hdjd)
{
    this->coreCount = hdjd["Data"]["CPU"]["coreCount"].as<int8_t>();

    if (!coreFreq || !coreTemp || !coreLoad) {
        coreFreq = (float*)hotakusAlloc(coreCount * sizeof(float));
        coreTemp = (float*)hotakusAlloc(coreCount * sizeof(float));
        coreLoad = (float*)hotakusAlloc(coreCount * sizeof(float));
    } else {
        coreFreq = (float*)hotakusRealloc(coreFreq, coreCount * sizeof(float));
        coreTemp = (float*)hotakusRealloc(coreTemp, coreCount * sizeof(float));
        coreLoad = (float*)hotakusRealloc(coreLoad, coreCount * sizeof(float));
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