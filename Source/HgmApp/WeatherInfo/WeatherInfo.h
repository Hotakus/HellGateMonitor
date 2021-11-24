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

#include "../../HgmLvgl/HgmGUI/HgmFramework.h"

#include <Arduino.h>
#include <SPIFFS.h>

using namespace fs;

namespace HgmApplication {
#define WEATHER_CONFIG_FILE_PATH "/weather.json"
#define WEATHER_GET_GAP (1800U * 1000U)	// 30 min

	class WeatherData
	{
	public:
		// Unit: Celsius
        uint8_t temp = 0;

		uint16_t aqi = -1;
		uint16_t icon = -1;

		// Unit: %
        uint8_t humidity = 0;

        WeatherData() = default;
        ~WeatherData() = default;
    };  

	class WeatherInfo
	{
	private:
        
	public:

        WeatherData wdt;

        String nowWeatherAPI = "https://devapi.qweather.com/v7/weather/now?";
        String threeWeatherAPI = "https://devapi.qweather.com/v7/weather/3d?";
        String airAPI = "https://devapi.qweather.com/v7/air/now?";

        String _id = "";
        String _key = "";
        String _adm = "";
        String _adm2 = "";
        String _location = "";
        String _lat = "";
        String _lon = "";

        QueueHandle_t WeatherCheckMsgBox;
        TaskHandle_t WeatherCheckTaskHandle;
        bool configFlag = false;

		WeatherInfo();
		~WeatherInfo();

		void begin();

		void initTask();
		void deInitTask();

		static void setAppKey(String key);
		// two method to set the location info
		static void setWeatherConfig();
		static void setWeatherConfig(String id);
		static void setWeatherConfig(String adm, String adm2, String location);
		static void setWeatherConfig(String latitude, String longitude);
		// two method to get the location info
		static void getWeatherConfig(String& id);
		static void getWeatherConfig(String& adm, String& adm2, String& location);
		static void getWeatherConfig(String& latitude, String& longitude);

		static void getWeather();
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
