/******************************************************************
 * @file HardwareDiskData.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/24 17:26
 * @copyright Copyright (c) 2021/9/24
*******************************************************************/
#include "HardwareDiskData.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;


HardwareDiskData::HardwareDiskData()
{
}

HardwareDiskData::~HardwareDiskData()
{
}

void HgmApplication::HardwareDiskData::Set(HDJsonDoc& hdjd)
{
    this->diskCount = hdjd["Data"]["HardDisk"]["count"].as<uint8_t>();

    if (!this->disk) {
        this->disk = (HgmDisk*)malloc(sizeof(HgmDisk) * this->diskCount);
    } else {
        this->disk = (HgmDisk*)realloc(this->disk, (sizeof(HgmDisk) * this->diskCount));
    }

    for (uint8_t i = 0; i < this->diskCount; i++) {
        this->disk[i].name = hdjd["Data"]["HardDisk"]["data"][i]["name"].as<String>();
        this->disk[i].tempCur = hdjd["Data"]["HardDisk"]["data"][i]["temp"]["current"].as<float>();
        this->disk[i].tempMax = hdjd["Data"]["HardDisk"]["data"][i]["temp"]["max"].as<float>();
        this->disk[i].freeSpace = hdjd["Data"]["HardDisk"]["data"][i]["load"]["current"].as<float>();
        this->disk[i].readRate = hdjd["Data"]["HardDisk"]["data"][i]["throughput"]["readRate"].as<float>();
        this->disk[i].readRate = hdjd["Data"]["HardDisk"]["data"][i]["throughput"]["writeRate"].as<float>();
    }

}

