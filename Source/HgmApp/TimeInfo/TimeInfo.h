/******************************************************************
 * @file TimeInfo.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/20 10:26
 * @copyright Copyright (c) 2021/8/20
*******************************************************************/
#ifndef HELLGATEMONITOR_TIMEINFO_H
#define HELLGATEMONITOR_TIMEINFO_H

#include <Arduino.h>
#include "../../HgmLvgl/HgmGUI/HgmSetupUI.h"
#include <ESP32Time.h>

namespace HgmApplication {

#define NET_TIME_GAP	(3600U * 1000U)	// Get the time per one hour

	class TimeInfo
	{
	private:

	public:
		ESP32Time rtc;

		TimeInfo();
		~TimeInfo();

		void initTask();
		void deInitTask();

		void begin();

		static int GetNetTime(struct tm* timeStruct);
	};

};



#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_TIMEINFO_H
