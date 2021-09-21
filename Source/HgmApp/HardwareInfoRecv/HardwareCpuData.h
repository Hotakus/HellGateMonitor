/******************************************************************
 * @file HardwareCpuData.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/21 21:38
 * @copyright Copyright (c) 2021/9/21
*******************************************************************/
#ifndef HELLGATEMONITOR_HARDWARECPUDATA_H
#define HELLGATEMONITOR_HARDWARECPUDATA_H

#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;

namespace HgmApplication {
	class HardwareCpuData {
    private:
    public:
        String name = "";
        int8_t coreCount = -1;

        // Unit: Mhz
        float* coreFreq = NULL;

        // Unit: Celsius
        float* coreTemp = NULL;
        float tempMax = 0;
        float tempAverage = 0;

        // Unit: %
        float* coreLoad = 0;
        float loadTotal = 0;

        // Unit: Watt
        float powerCur = 0;
        float powerMax = 0;

        HardwareCpuData();
        ~HardwareCpuData();

        void Set(HotakusDynamicJsonDocument& hdjd);
	};
}

#endif //HELLGATEMONITOR_HARDWARECPUDATA_H
