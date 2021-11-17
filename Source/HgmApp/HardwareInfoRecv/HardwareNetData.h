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

		// Unit: GiB
		struct NetData {
			float uploaded;
			float downloaded;
		};

		// Unit: Bytes
		struct NetThroughput {
			float upload;
			float download;
		};

		struct HgmNetwork
		{
			NetData nd;
			NetThroughput nt;
            uint8_t utilization;
		} wlan, ethernet;

        bool isWiFi = false;

		HardwareNetData();
		~HardwareNetData();

        void Set(HDJsonDoc& hdjd);
	};
}

#endif //HELLGATEMONITOR_HARDWARENETDATA_H
