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
#include "../HgmWiFi/HgmWiFi.h"

#include <Arduino.h>
#include <ArduinoJson.h>

#define TAG "HgmRequest"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

extern HgmWiFi hgmWiFi;
extern SemaphoreHandle_t wbs;
static HardwareRequest* instance = nullptr;

static void hrtask(void* params)
{
    String str = "";

    while (true) {
        if (!hgmWiFi.hgmTcp->hasClient) {
            vTaskDelay(2000);
            continue;
        }

        if (!hgmWiFi.hgmTcp->isDataSrc) {
            vTaskDelay(2000);
            continue;
        }
        
        // xSemaphoreTake(wbs, portMAX_DELAY);
        // HgmTCP::sendDatePack(str, HgmTcpPackMethod::HGM_TCP_PACK_METHOD_REQUEST_HWI);
        // xSemaphoreGive(wbs);
        vTaskDelay(HARDWARE_REQUEST_GAP);
    }
}

void HgmApplication::HardwareRequest::initTask()
{
    xTaskCreatePinnedToCore(hrtask, "hardwareReqTask", 3072, NULL, 3, &frtos.hardwareReqTaskHandle, 1);
}

void HgmApplication::HardwareRequest::deInitTask()
{
    vTaskDelete(frtos.hardwareReqTaskHandle);
}

HgmApplication::HardwareRequest::HardwareRequest()
{
    instance = this;
    hgmHardObj = (HgmHardwareObject**)malloc(sizeof(HgmHardwareObject*) * supportHardwareCnt);
    for (uint8_t i = 0; i < supportHardwareCnt; i++) {
        hgmHardObj[i] = (HgmHardwareObject*)malloc(sizeof(HgmHardwareObject));
        hgmHardObj[i]->hardware = HGM_HARD_NULL;
        hgmHardObj[i]->pos = HGM_POS_NULL;
        hgmHardObj[i]->params = NULL;
        hgmHardObj[i]->request = true;
    }
}

HgmApplication::HardwareRequest::~HardwareRequest()
{
    for (uint8_t i = 0; i < supportHardwareCnt; i++)
        free(hgmHardObj[i]);
    free(hgmHardObj);
    instance = nullptr;
}

void HardwareRequest::begin()
{
    hd = (_hardData*)malloc(sizeof(_hardData));
    hd->cpuData = new HardwareCpuData();
    hd->gpuData = new HardwareGpuData();
    hd->memData = new HardwareMemData();
    hd->diskData = new HardwareDiskData();
    hd->netData = new HardwareNetData();

    RegisterNewHardware(hd->cpuData, HGM_CPU, HGM_LEFT_TOP);
    RegisterNewHardware(hd->gpuData, HGM_GPU, HGM_LEFT_BOTTOM);
    RegisterNewHardware(hd->memData, HGM_MEMORY, HGM_RIGHT_TOP);
    RegisterNewHardware(hd->diskData, HGM_HARD_DISK, HGM_POS_NULL);
    RegisterNewHardware(hd->netData, HGM_NETWORK, HGM_RIGHT_BOTTOM);

    SetHardwareRequest(HGM_CPU, true);
    SetHardwareRequest(HGM_GPU, true);
    SetHardwareRequest(HGM_MEMORY, true);
    SetHardwareRequest(HGM_HARD_DISK, false);
    SetHardwareRequest(HGM_NETWORK, true);

    hgm_log_d(TAG, "begin...");
}

void HardwareRequest::end()
{
    SetHardwareRequest(HGM_CPU, false);
    SetHardwareRequest(HGM_GPU, false);
    SetHardwareRequest(HGM_MEMORY, false);
    SetHardwareRequest(HGM_HARD_DISK, false);
    SetHardwareRequest(HGM_NETWORK, false);

    UnregisterHardware(HGM_CPU);
    UnregisterHardware(HGM_GPU);
    UnregisterHardware(HGM_MEMORY);
    UnregisterHardware(HGM_HARD_DISK);
    UnregisterHardware(HGM_NETWORK);

    delete hd->cpuData;
    delete hd->gpuData;
    delete hd->memData;
    delete hd->diskData;
    delete hd->netData;
    free(hd);

    hgm_log_d(TAG, "end");
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
        if (!hgmHardObj[i]->params) {
            nullIndex = i;
            continue;
        }
        if (hgmHardObj[i]->hardware == ht) {
            hgm_log_e(TAG, "Hardware Data obj is existing.");
            return false;
        }
    }

    if (nullIndex > -1) {
        hgmHardObj[nullIndex]->hardware = ht;
        hgmHardObj[nullIndex]->params = pHardData;
        hgmHardObj[nullIndex]->pos = pos;
        hgmHardObj[nullIndex]->request = false;
        return true;
    }

    for (nullIndex = 0; nullIndex < supportHardwareCnt; nullIndex++) {
        if (!hgmHardObj[nullIndex]->params) {
            hgmHardObj[nullIndex]->hardware = ht;
            hgmHardObj[nullIndex]->params = pHardData;
            hgmHardObj[nullIndex]->pos = pos;
            hgmHardObj[nullIndex]->request = false;
            return true;
        }
    }


    hgm_log_e(TAG, "Register failed, Hardware obj is full.");
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
        if (hgmHardObj[i]->params && hgmHardObj[i]->hardware == ht) {
            hgmHardObj[i]->hardware = HGM_HARD_NULL;
            hgmHardObj[i]->params = NULL;
            hgmHardObj[i]->pos = HGM_POS_NULL;
            hgmHardObj[i]->request = false;
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

template <typename t>
t* HardwareRequest::GetParams(HgmHardware ht)
{
    HgmHardwareObject* hho = this->GetHardwareObj(ht);
    if (hho)
        return ((t*)hho->params);
    else
        return NULL;
}


bool HardwareRequest::isRequest(HgmHardware ht)
{
    HgmHardwareObject* hho = this->GetHardwareObj(ht);
    if (hho)
        return hho->request;
    else
        return false;
}
