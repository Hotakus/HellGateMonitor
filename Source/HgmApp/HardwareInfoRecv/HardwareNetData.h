/******************************************************************
 * @file HardwareNetData.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/23 20:12
 * @copyright Copyright (c) 2021/9/23
*******************************************************************/
#ifndef HELLGATEMONITOR_HARDWARENETDATA_H
#define HELLGATEMONITOR_HARDWARENETDATA_H

#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;

namespace HgmApplication {
	class HardwareNetData {
	private:
	public:




		HardwareNetData();
		~HardwareNetData();

		void Set(HotakusDynamicJsonDocument& hdjd);
	};
}

#endif //HELLGATEMONITOR_HARDWARENETDATA_H
