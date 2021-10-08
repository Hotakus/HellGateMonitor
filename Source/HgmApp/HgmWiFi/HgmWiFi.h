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

namespace HgmApplication {
#define WIFI_CONFIG_FILE_PATH "/wifi.json"
#define WIFI_DEFAULT_NAME "HellGateMonitorWiFi"
#define WIFI_USE_MODE WIFI_STA
	class HgmWiFi
	{
	private:
		String ssid;		// For storing ssid after power on self checking
		String password;	// For storing password after power on self checking

		void WifiTaskInit();
	public:
		WiFiClass* wifi;
		HgmTCP* hgmTcp = nullptr;

		HgmWiFi();
		HgmWiFi(String ssid, String password);
		~HgmWiFi();

		void ConfigWiFi(String ssid, String password);
		void OpenWiFi(bool sw = true);
		void OpenTCP(bool sw = true, bool asServer = true);

		void Begin();
		void Stop();

		static String GetSSID();
		static String GetPassword();

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
