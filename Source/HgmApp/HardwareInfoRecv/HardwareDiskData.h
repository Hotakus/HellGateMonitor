/******************************************************************
 * @file HardwareDiskData.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/24 17:26
 * @copyright Copyright (c) 2021/9/24
*******************************************************************/
#ifndef HELLGATEMONITOR_HARDWAREDISKDATA_H
#define HELLGATEMONITOR_HARDWAREDISKDATA_H

#include "../HgmJsonUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

using namespace HgmApplication::HgmJsonParseUtil;

namespace HgmApplication {
	class HardwareDiskData
	{
	private:
	public:

		uint8_t diskCount = -1;

		typedef struct _HgmDisk
		{
			String name = "";

			// Unit: Celsius
			float tempCur = 0;
			float tempMax = 0;

			// Unit: %
			float freeSpace = 0;

			// Unit: Bytes per second
			float readRate = 0;
			float writeRate = 0;
		} HgmDisk;

		HgmDisk* disk = NULL;

		HardwareDiskData();
		~HardwareDiskData();

		void Set(HDJsonDoc& hdjd);
        void Set(DynamicJsonDocument& hdjd);
	};

}

#endif //HELLGATEMONITOR_HARDWAREDISKDATA_H
