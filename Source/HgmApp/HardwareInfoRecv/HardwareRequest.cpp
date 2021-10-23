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
#include "HardwareNetData.h"
#include "HardwareDiskData.h"

#include "HardwareRequest.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

#define TAG "HgmRequest"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"


using namespace HgmApplication::HgmJsonParseUtil;
using namespace HgmApplication;

extern HardwareCpuData hardwareCpuData;
extern HardwareGpuData hardwareGpuData;
extern HardwareMemData hardwareMemData;
extern HardwareGpuData hardwareNetData;
extern HardwareMemData hardwareDiskData;

HgmApplication::HardwareRequest::HardwareRequest()
{

    hgmHardObj = (HgmHardwareObject**)hotakusAlloc(sizeof(HgmHardwareObject*) * supportHardwareCnt);
    for (uint8_t i = 0; i < supportHardwareCnt; i++) {
        hgmHardObj[i] = (HgmHardwareObject*)hotakusAlloc(sizeof(HgmHardwareObject));
        hgmHardObj[i]->hardware = HGM_HARD_NULL;
        hgmHardObj[i]->pos = HGM_POS_NULL;
        hgmHardObj[i]->params = NULL;
        hgmHardObj[i]->request = true;
    }

    RegisterNewHardware(&hardwareCpuData, HGM_CPU, HGM_LEFT_TOP);

    (hgmHardObj[HGM_CPU]->params) = &hardwareCpuData;
    (hgmHardObj[HGM_GPU]->params) = &hardwareGpuData;
    (hgmHardObj[HGM_MEMORY]->params) = &hardwareMemData;
    (hgmHardObj[HGM_HARD_DISK]->params) = &hardwareDiskData;
    (hgmHardObj[HGM_NETWORK]->params) = &hardwareNetData;

}

HgmApplication::HardwareRequest::~HardwareRequest()
{
    (hgmHardObj[HGM_CPU]->params) = NULL;
    (hgmHardObj[HGM_GPU]->params) = NULL;
    (hgmHardObj[HGM_MEMORY]->params) = NULL;
    (hgmHardObj[HGM_HARD_DISK]->params) = NULL;
    (hgmHardObj[HGM_NETWORK]->params) = NULL;

    for (uint8_t i = 0; i < supportHardwareCnt; i++)
        hotakusFree(hgmHardObj[i]);
    hotakusFree(hgmHardObj);
}

void HgmApplication::HardwareRequest::UseDefault()
{
    /* default request */

    /* default position */
    (hgmHardObj[HGM_CPU]->pos) = HGM_LEFT_TOP;
    (hgmHardObj[HGM_GPU]->pos) = HGM_RIGHT_TOP;
    (hgmHardObj[HGM_MEMORY]->pos) = HGM_LEFT_BOTTOM;
    (hgmHardObj[HGM_NETWORK]->pos) = HGM_RIGHT_BOTTOM;
    (hgmHardObj[HGM_HARD_DISK]->pos) = HGM_POS_NULL;
}

/**
 * @brief Register a new hardware.
 * @param pHardData
 * @param ht
 * @param pos
 * @return 
 */
bool HardwareRequest::RegisterNewHardware(void* pHardData, HgmHardware ht, HgmHardwarePosition pos)
{
    if (!pHardData || ht == HGM_HARD_NULL) {
        hgm_log_e(TAG, "Hardware Data obj is null");
        return false;
    }

    int nullIndex = -1;
    for (uint8_t i = 0; i < supportHardwareCnt; i++) {
        if (!hgmHardObj[i]->params)
            nullIndex = i;
        if (hgmHardObj[i]->hardware == ht) {
            hgm_log_e(TAG, "Hardware Data obj is existing.");
            return false;
        }
    }

    if (nullIndex > -1) {
        hgmHardObj[nullIndex]->hardware = ht;
        hgmHardObj[nullIndex]->params = pHardData;
        hgmHardObj[nullIndex]->pos = pos;
        return true;
    } else {
        for (nullIndex = 0; nullIndex < supportHardwareCnt; nullIndex++) {
            if (!hgmHardObj[nullIndex]->params) {
                hgmHardObj[nullIndex]->hardware = ht;
                hgmHardObj[nullIndex]->params = pHardData;
                hgmHardObj[nullIndex]->pos = pos;
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Unregister a hardware.
 * @param ht
 * @return 
 */
bool HardwareRequest::UnregisterHardware(HgmHardware ht)
{
    if (ht == HGM_HARD_NULL) {
        hgm_log_e(TAG, "Hardware obj is null");
        return false;
    }

    for (uint8_t i = 0; i < supportHardwareCnt; i++) {
        if (hgmHardObj[i]->hardware == ht) {
            hgmHardObj[i]->hardware = HGM_HARD_NULL;
            hgmHardObj[i]->params = NULL;
            hgmHardObj[i]->pos = HGM_POS_NULL;
            return true;
        }
    }

    return false;
}

/**
 * @brief Get a hardware object.
 * @param ht
 * @return if failed return NULL ,else pointer to the HgmHardwareObject
 */
HgmHardwareObject* HardwareRequest::GetHardwareObj(HgmHardware ht)
{
    if (ht == HGM_HARD_NULL) {
        hgm_log_e(TAG, "Hardware obj is null");
        return false;
    }
    for (uint8_t i = 0; i < supportHardwareCnt; i++)
        if (hgmHardObj[i]->hardware == ht)
            return hgmHardObj[i];
    return NULL;
}

/**
 * @brief Set the request to true or false to control request.
 * @param ht
 * @param request
 */
void HardwareRequest::SetHardwareRequest(HgmHardware ht, bool request)
{
    HgmHardwareObject* hho = this->GetHardwareObj(ht);
    if (hho) hho->request = request;
}

void HardwareRequest::FlushRequestList()
{
    for (uint8_t i = 0; i < supportHardwareCnt; i++) {
    }
}
