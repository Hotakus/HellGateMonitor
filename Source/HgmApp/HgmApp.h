/******************************************************************
 * @file HgmApp.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/11 21:57
 * @copyright Copyright (c) 2021/8/11
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMAPP_H
#define HELLGATEMONITOR_HGMAPP_H

#include <WiFi.h>
#include "HgmWiFi/HgmWiFi.h"
#include "HgmBT/HgmBT.h"

namespace HgmApplication {

#define WIFI_USE_MODE WIFI_STA

	class HgmApp
	{
	private:

	public:
		HgmWiFi* hgmWifi = nullptr;
		HgmBT* hgmBT = nullptr;

		HgmApp(bool flag);
		HgmApp(char* ssid = nullptr, char* password = nullptr);
		~HgmApp();

		void Begin();

		void BeginWiFi();
		void BeginWiFiWithConfig(char* ssid, char* password);
		void BeginBT();

		void Stop();
		void StopWiFi();
		void StopBT();

	};

};

#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMAPP_H
