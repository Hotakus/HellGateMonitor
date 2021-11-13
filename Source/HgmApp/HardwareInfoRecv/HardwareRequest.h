/******************************************************************
 * @file HardwareRequest.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/21 22:33
 * @copyright Copyright (c) 2021/9/21
*******************************************************************/
#ifndef HELLGATEMONITOR_HARDWAREREQUEST_H
#define HELLGATEMONITOR_HARDWAREREQUEST_H
#include "HardwareCpuData.h"
#include "HardwareGpuData.h"
#include "HardwareMemData.h"
#include "HardwareNetData.h"
#include "HardwareDiskData.h"
#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;

namespace HgmApplication {
#define HARDWARE_REQUEST_GAP (2 * 1000)
    /* HGM 所支持监控的硬件对象 */
    typedef enum _HgmHardware {
        HGM_CPU,
        HGM_GPU,
        HGM_MEMORY,
        HGM_HARD_DISK,
        HGM_NETWORK,

        HGM_HARD_NULL
    } HgmHardware;

    /* HGM 硬件监控对象的位置 */
    typedef enum _HgmHardwarePosition {
        HGM_LEFT_TOP,
        HGM_LEFT_BOTTOM,
        HGM_RIGHT_TOP,
        HGM_RIGHT_BOTTOM,
        HGM_POS_NULL,
    } HgmHardwarePosition;

    /* HGM 受硬件监控对象。HGM会对 “受硬件监控对象” 发出参数请求，以此显示硬件参数 */
    /* "params" 参数指向对应硬件信息的数据类指针 */
    typedef struct _HgmHardwareObject {
        void* params;
        bool request;
        HgmHardware hardware;
        HgmHardwarePosition pos;
    } HgmHardwareObject;

    class HardwareRequest {
    private:
    public:

        struct _hardData {
            HardwareCpuData* cpuData;
            HardwareGpuData* gpuData;
            HardwareMemData* memData;
            HardwareNetData* netData;
            HardwareDiskData* diskData;
        } *hd;
        HgmHardwareObject** hgmHardObj;
        const uint8_t supportHardwareCnt = HGM_HARD_NULL;

        struct _frtos {
            TaskHandle_t hardwareReqTaskHandle;
        } frtos;

        HardwareRequest();
        ~HardwareRequest();

        void begin();
        void end();

        void initTask();
        void deInitTask();

        void UseDefault();

        /* Register a new hardware into manager */
        bool RegisterNewHardware(void* pHardData, HgmHardware ht, HgmHardwarePosition pos);
        bool UnregisterHardware(HgmHardware ht);
        HgmHardwareObject* GetHardwareObj(HgmHardware ht);
        void SetHardwareRequest(HgmHardware ht, bool request);
        void FlushRequestList();

        bool isRequest(HgmHardware ht);

        template <typename t> t* GetParams(HgmHardware ht);

    };
}

#endif //HELLGATEMONITOR_HARDWAREREQUEST_H
