/******************************************************************
 * @file HardwareGpuData.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/22 22:53
 * @copyright Copyright (c) 2021/9/22
*******************************************************************/
#ifndef HELLGATEMONITOR_HARDWAREGPUDATA_H
#define HELLGATEMONITOR_HARDWAREGPUDATA_H

#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;

namespace HgmApplication{
	class HardwareGpuData {
	private:
	public:

		String name = "";

		// Unit: Mhz
		float coreFreq = 0;
		float memFreq = 0;

		// Unit: Celsius
		float tempCoreMax = 0;
		float tempCoreCur = 0;

		// Unit: %
		float coreLoad = 0;
		float coreLoadMax = 0;

		// Unit: Watt
		float powerCur = 0;
		float powerMax = 0;

		HardwareGpuData();
		~HardwareGpuData();

		void Set(HDJsonDoc& hdjd);
        void Set(DynamicJsonDocument& hdjd);
	};
}



#endif //HELLGATEMONITOR_HARDWAREGPUDATA_H
