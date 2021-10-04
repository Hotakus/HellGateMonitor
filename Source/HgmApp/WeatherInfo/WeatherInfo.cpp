/******************************************************************
 * @file WeatherInfo.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/22 6:27
 * @copyright Copyright (c) 2021/8/22
*******************************************************************/
#include "WeatherInfo.h"
#include "../HgmWiFi/HgmTCP/HgmTCP.h"
#include "../HgmBT/HgmBT.h"
#include "../../HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "../HgmJsonUtil.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>
#include <SPIFFS.h>

#define HGM_DEBUG 1

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;
using namespace HgmGUI;
using namespace fs;

extern HgmBT hgmBT;
extern HgmSetupUI* hgmSetupUI;
static HgmComponent component;

extern SemaphoreHandle_t wbs;

static String nowWeatherAPI = "https://devapi.qweather.com/v7/weather/now?";
static String threeWeatherAPI = "https://devapi.qweather.com/v7/weather/3d?";
static String airAPI = "https://devapi.qweather.com/v7/air/now?";

static String _id = "";
static String _key = "";
static String _adm = "";
static String _adm2 = "";
static String _location = "";
static String _lat = "";
static String _lon = "";

static StaticJsonDocument<2048> doc;

static File _file;

static QueueHandle_t WCMsgBox;
static TaskHandle_t WCTaskHandle;
static void WCTask(void* params);

static bool configFlag = false;

WeatherInfo weatherInfo;
WeatherData weatherToday;

HTTPClient hgmHttpClient;

WeatherInfo::WeatherInfo()
{
    // TODO: Create a task to loop to get the weather
    WCMsgBox = xQueueCreate(1, sizeof(int));
}

WeatherInfo::~WeatherInfo()
{
    vQueueDelete(WCMsgBox);
}


WeatherData::WeatherData()
{
}

WeatherData::~WeatherData()
{
}

void HgmApplication::WeatherInfo::Begin()
{
    this->CheckWeatherconfig();
}

void HgmApplication::WeatherInfo::InitTask()
{
    xTaskCreatePinnedToCore(
        WCTask,
        "WCTask",
        8192,
        NULL,
        3,
        &WCTaskHandle,
        1
    );
}

void HgmApplication::WeatherInfo::DeInitTask()
{
    vTaskDelete(WCTaskHandle);
    WCTaskHandle = NULL;
}


static void _get()
{
    _id = doc["data"]["id"].as<String>();
    _key = doc["data"]["key"].as<String>();
    _adm = doc["data"]["adm"].as<String>();
    _adm2 = doc["data"]["adm2"].as<String>();
    _location = doc["data"]["location"].as<String>();
    _lat = doc["data"]["lat"].as<String>();
    _lon = doc["data"]["lon"].as<String>();

    component.curStatus = true;
    component.waitStatus = true;
}

static void WeatherConfig()
{
    component.type = HGM_COMPONENT_WEATHER;
    component.curStatus = false;
    component.waitStatus = false;
    hgmSetupUI->ComponentControl(&component);

    Serial.println("Waiting the Weather config...");
    while (configFlag != true)
        vTaskDelay(5);

    _get();
}


bool HgmApplication::WeatherInfo::CheckWeatherconfig()
{
    if (!SPIFFS.exists(WEATHER_CONFIG_FILE_PATH)) {
        Serial.printf("Can't find the config file for the weather component.\n");
        WeatherConfig();
    } else {
        _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_READ);
        if (!_file.size()) {
            _file.close();
            Serial.printf("Weather config file is null.\n");
            WeatherConfig();
        } else {
            _file.close();

            Serial.printf("Found the weather config file.\n");
            String tmp;
            _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_READ);
            tmp = _file.readString();
            _file.close();

            deserializeJson(doc, tmp);
            Serial.println(tmp);

            String str = "Weather";
            String header = doc["Header"];
            if (header.compareTo(str) != 0) {
                WeatherConfig();
            } else {
                _get();
            }

            _lat = doc["Data"]["lat"].as<String>();
            _lon = doc["Data"]["lon"].as<String>();
            _key = doc["Data"]["key"].as<String>();

            configFlag = true;
            vTaskDelay(200);
        }
    }

    this->InitTask();

    return true;
}

void HgmApplication::WeatherInfo::SetWeatherConfig()
{
    // TODO: Send msg
    _file = SPIFFS.open(WEATHER_CONFIG_FILE_PATH, FILE_WRITE);

    String wi;
    doc["Header"] = "Weather";
    doc["Data"]["id"] = _id;
    doc["Data"]["key"] = _key;
    doc["Data"]["adm"] = _adm;
    doc["Data"]["adm2"] = _adm2;
    doc["Data"]["location"] = _location;
    doc["Data"]["lat"] = _lat;
    doc["Data"]["lon"] = _lon;
    serializeJson(doc, wi);

    _file.write((const uint8_t*)wi.c_str(), wi.length());

    _file.close();
    configFlag = true;
}

void HgmApplication::WeatherInfo::SetAppKey(String key)
{
    _key = key;
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String id)
{
    _id = id;
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String adm, String adm2, String location)
{
    _adm = adm;
    _adm2 = adm2;
    _location = location;
}

void HgmApplication::WeatherInfo::SetWeatherConfig(String latitude, String longitude)
{
    Serial.println(latitude);
    Serial.println(longitude);

    _lat = latitude;
    _lon = longitude;
}

void HgmApplication::WeatherInfo::GetWeatherConfig(String& id)
{
    id = _id;
}

void HgmApplication::WeatherInfo::GetWeatherConfig(String& adm, String& adm2, String& location)
{
    adm = _adm;
    adm2 = _adm2;
    location = _location;
}

void HgmApplication::WeatherInfo::GetWeatherConfig(String& latitude, String& longitude)
{
    latitude = _lat;
    longitude = _lon;
}



void HgmApplication::WeatherInfo::GetWeather()
{
#if HGM_DEBUG == 1
    String __lat = "23.172";
    String __lon = "108.241";
    String __key = "bc1f1bdefb944930bef0208ecd03f66a"; // TODO: delete
#else
    String& __lat = _lat;
    String& __lon = _lon;
    String& __key = _key;
#endif

    String lonLat = "&location=" + __lon + ',' + __lat;
    String key = "&key=" + __key;
    String gzip = "&gzip=n";
    String nowApi = nowWeatherAPI + lonLat + key + gzip;
    String threeApi = threeWeatherAPI + lonLat + key + gzip;
    String airApi = airAPI + lonLat + key + gzip;

#if HGM_DEBUG == 1
    Serial.println(nowApi);
    Serial.println(threeApi);
    Serial.println(airApi);
#endif

    WiFiClient* wc = NULL;
    size_t packSize = 0;
    HotakusDynamicJsonDocument rawPack(8192);
    uint8_t* packBuf = (uint8_t*)heap_caps_calloc(8192, sizeof(uint8_t), MALLOC_CAP_SPIRAM);
    HTTPClient* hc = (HTTPClient*)heap_caps_calloc(1, sizeof(HTTPClient), MALLOC_CAP_SPIRAM);

    /* Air */
    // TODO: create func
    uint8_t retry = 5;
    while (retry--) {
        hc->setTimeout(2000);
        hc->begin(airApi);
        vTaskDelay(50);
        int code = hc->GET();
        if (code != HTTP_CODE_OK) {
            Serial.printf("%s HTTP error code : % d\n", __func__, code);
            hc->end();
            continue;
        } else
            break;
    }
    if (retry) {
        wc = hc->getStreamPtr();
        packSize = wc->available();
        memset(packBuf, 0x00, 8192);
        packBuf[packSize] = '\0';
        for (size_t i = 0; i < packSize; i++) {
            packBuf[i] = (uint8_t)wc->read();
            Serial.printf("%c", packBuf[i]);
        }
        Serial.println();
        deserializeJson(rawPack, packBuf);

        if (rawPack["code"].as<uint16_t>() == 402) {
            Serial.println("The qweather api at max using times.");
            hc->end();
            return;
        }

        Serial.println(rawPack["now"]["aqi"].as<String>());
        hc->end();
    }

    

    /* Now */
    retry = 5;

    /* Three days */
    retry = 5;


    heap_caps_free(packBuf);
    heap_caps_free(hc);
}


static String url = "https://devapi.qweather.com/v7/air/now?gzip=n&location=108.241,23.172&key=bc1f1bdefb944930bef0208ecd03f66a";
static String url2 = "http://api.bilibili.com/x/space/acc/info?mid=114514";

static void WCTask(void* params)
{
    int tmp = 0;

    while (true) {
        if (!WiFi.isConnected()) {
            vTaskDelay(1000);
            continue;
        }


        xSemaphoreTake(wbs, portMAX_DELAY);
        hgmBT.Stop();
        while (hgmBT.bs->isReady())
            vTaskDelay(2000);
        
        /* Air */
        WeatherInfo::GetWeather();

        // HTTPClient* hc = (HTTPClient*)heap_caps_calloc(1, sizeof(HTTPClient), MALLOC_CAP_SPIRAM);
        // while (true) {
        //     hc->setTimeout(2000);
        //     hc->begin(url);
        //     vTaskDelay(50);
        //     int code = hc->GET();
        //     if (code < 0) {
        //         Serial.printf("1 HTTP error code : % d\n", code);
        //         hc->end();
        //         continue;
        //     } else {
        //         Serial.printf("HTTP GET OK\n");
        //         Serial.println(hc->getString());
        //         hc->end();
        //         break;
        //     }
        //     vTaskDelay(1000);
        // }
        // heap_caps_free(hc);
        
        hgmBT.Begin();
        while (!hgmBT.bs->isReady())
            vTaskDelay(1000);
        xSemaphoreGive(wbs);

        

        vTaskDelay(WEATHER_GET_GAP);
    }
}
