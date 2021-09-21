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

#include <Arduino.h>
#include <ArduinoJson.h>

namespace HgmApplication {
	class HardwareRequest {
	public:
		bool rCpu = true;
		bool rGpu = true;
		bool rMemory = true;
		bool rHardDisk = true;
		bool rNetwork = false;

		HardwareRequest();
		~HardwareRequest();
	};
}

#endif //HELLGATEMONITOR_HARDWAREREQUEST_H
