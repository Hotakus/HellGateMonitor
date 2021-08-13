/******************************************************************
 * @file HgmWiFi.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/12 5:26
 * @copyright Copyright (c) 2021/8/12
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMWIFI_H
#define HELLGATEMONITOR_HGMWIFI_H

#include <WiFi.h>
#include "HgmTCP/HgmTCP.h"

#define WIFI_CONFIG_FILE_PATH "/wifi.conf"

namespace HgmApplication {
	class HgmWiFi
	{
	private:
		char* ssid;		// For storing ssid after power on self checking
		char* password;	// For storing password after power on self checking

		void WifiTaskInit();
	public:
		

		HgmTCP* hgmTcp = nullptr;

		HgmWiFi(bool flag);
		HgmWiFi(char* ssid = nullptr, char* password = nullptr);
		~HgmWiFi();

		void ConfigWiFi(char* ssid = nullptr, char* password = nullptr);
		void OpenWiFi(bool sw = true);
		void OpenTCP(bool sw = true, bool asServer = true);

		void Begin();

		// TODO: WiFi stop;
		void Stop();
	};
};


#ifdef __cplusplus
extern "C" {
#endif
     
/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMWIFI_H
