/******************************************************************
 * @file HardwareMemData.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/22 23:22
 * @copyright Copyright (c) 2021/9/22
*******************************************************************/
#ifndef HELLGATEMONITOR_HARDWAREMEMDATA_H
#define HELLGATEMONITOR_HARDWAREMEMDATA_H

#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;

namespace HgmApplication {
	class HardwareMemData {
	private:
	public:
		String name = "Memory";

		// Unit: GiB
		float free = 0;
		float used = 0;
		float total = 0;

		// Unit: %
		float load = 0;
		float loadMax = 0;
		
		HardwareMemData();
		~HardwareMemData();

		void Set(HDJsonDoc& hdjd);
        void Set(DynamicJsonDocument& hdjd);
	};
}

#endif //HELLGATEMONITOR_HARDWAREMEMDATA_H
