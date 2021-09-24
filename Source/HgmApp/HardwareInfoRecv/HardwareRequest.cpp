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
#include "HardwareGpuData.h"
#include "HardwareMemData.h"

#include "HardwareRequest.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;
using namespace HgmApplication;

extern HardwareCpuData hardwareCpuData;
extern HardwareGpuData hardwareGpuData;
extern HardwareMemData hardwareMemData;

HardwareRequest hrr;
static HardwareRequest hardwareRequestDefault;

static HgmHardwareObject hgmCpu;
static HgmHardwareObject hgmGpu;
static HgmHardwareObject hgmMem;
static HgmHardwareObject hgmDisk;
static HgmHardwareObject hgmNet;

HgmHardwareObject* hgmHardObj[] = {
    &hgmCpu,
    &hgmGpu,
    &hgmMem,
    &hgmDisk,
    &hgmNet
};

HgmApplication::HardwareRequest::HardwareRequest()
{
    (hgmHardObj[HGM_CPU]->params) = &hardwareCpuData;
    (hgmHardObj[HGM_GPU]->params) = &hardwareGpuData;
    (hgmHardObj[HGM_MEMORY]->params) = &hardwareMemData;

}

HgmApplication::HardwareRequest::~HardwareRequest()
{
    (hgmHardObj[HGM_CPU]->params) = NULL;
    (hgmHardObj[HGM_GPU]->params) = NULL;
    (hgmHardObj[HGM_MEMORY]->params) = NULL;
}

void HgmApplication::HardwareRequest::UseDefault()
{
    /* default request */
    hrr = hardwareRequestDefault;

    /* default position */
    (hgmHardObj[HGM_CPU]->pos) = HGM_LEFT_TOP;
    (hgmHardObj[HGM_GPU]->pos) = HGM_RIGHT_TOP;
    (hgmHardObj[HGM_MEMORY]->pos) = HGM_LEFT_BOTTOM;
}
