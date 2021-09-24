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

#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;

namespace HgmApplication {

    /* HGM 所支持监控的硬件对象 */
    typedef enum {
        HGM_CPU,
        HGM_GPU,
        HGM_MEMORY,
        HGM_HARD_DISK,
        HGM_NETWORK,
    } HgmHardware;

    /* HGM 硬件监控对象的位置 */
    typedef enum {
        LEFT_TOP,
        LEFT_BOTTOM,
        RIGHT_TOP,
        RIGHT_BOTTOM,
    } HgmHardwarePosition;

    /* HGM 受硬件监控对象。HGM会对 “受硬件监控对象” 发出参数请求，以此显示硬件参数 */
    /* "params" 参数指向对应硬件信息的数据类指针 */
    typedef struct {
        // TODO:
        void* params;
        HgmHardware hardware;
        HgmHardwarePosition pos;
    } HgmHardwareObject;

    class HardwareRequest {
    private:
    public:
        bool rCpu = true;
        bool rGpu = true;
        bool rMemory = true;
        bool rHardDisk = true;
        bool rNetwork = false;

        HardwareRequest();
        ~HardwareRequest();

        void UseDefault();

        void HardwareRequestConfig(HotakusDynamicJsonDocument& hdjd);
    };
}

#endif //HELLGATEMONITOR_HARDWAREREQUEST_H
