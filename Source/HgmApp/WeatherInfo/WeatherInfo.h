/******************************************************************
 * @file WeatherInfo.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/22 6:27
 * @copyright Copyright (c) 2021/8/22
*******************************************************************/
#ifndef HELLGATEMONITOR_WEATHERINFO_H
#define HELLGATEMONITOR_WEATHERINFO_H


#include <Arduino.h>
#include <SPIFFS.h>

using namespace fs;

namespace HgmApplication {
#define WEATHER_CONFIG_FILE_PATH "/weather.conf"
#define WEATHER_GET_GAP (1800U * 1000U)	// 30 min

	class WeatherData
	{
	public:
		// Unit: Celsius
		float temp = 0;

		int16_t aqi = -1;
		int16_t icon = -1;

		// Unit: %
		float humidity = 0;

		WeatherData();
		~WeatherData();
	};

	class WeatherInfo
	{
	private:

	public:

		WeatherInfo();
		~WeatherInfo();

		void Begin();

		void InitTask();
		void DeInitTask();

		bool CheckWeatherconfig();

		static void SetAppKey(String key);
		// two method to set the location info
		static void SetWeatherConfig();
		static void SetWeatherConfig(String id);
		static void SetWeatherConfig(String adm, String adm2, String location);
		static void SetWeatherConfig(String latitude, String longitude);
		// two method to get the location info
		static void GetWeatherConfig(String& id);
		static void GetWeatherConfig(String& adm, String& adm2, String& location);
		static void GetWeatherConfig(String& latitude, String& longitude);

		static void GetWeather();
	};


};




#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_WEATHERINFO_H
