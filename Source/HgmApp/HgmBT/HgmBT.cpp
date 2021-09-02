/******************************************************************
 * @file HgmBT.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief HGM's BT function, use the json format to send/receive data
 * @version 1.0
 * @date 2021/8/13 5:08
 * @copyright Copyright (c) 2021/8/13
*******************************************************************/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
#include <SPIFFS.h>
#include "HgmBT.h"
#include "../HgmApp.h"
#include "../WeatherInfo/WeatherInfo.h"
#include "../BiliInfoRecv/BiliInfoRecv.h"

using namespace HgmApplication;
using namespace fs;

extern HgmApp* hgmApp;
extern SemaphoreHandle_t wbs;

static QueueHandle_t btCtlMsgbox = NULL;
static TaskHandle_t bluetoothCheckTaskHandle = NULL;
static BluetoothSerial* _bs = NULL;

static char* name = nullptr;

static void BluetoothControlTask(void* params);
static void BluetoothListeningTask(void* params);

/**
 * @brief Construct.
 * @param n set the name of the bluetooth
 */
HgmBT::HgmBT(char* n)
{
    name = n;
    this->bs = new BluetoothSerial();
    _bs = this->bs;
    btCtlMsgbox = xQueueCreate(1, sizeof(bool));
    this->BluetoothTaskInit();
}

HgmBT::~HgmBT()
{
    delete this->bs;
    this->BluetoothTaskDelete();
    vQueueDelete(btCtlMsgbox);
}

void HgmApplication::HgmBT::BluetoothTaskInit()
{
    xTaskCreatePinnedToCore(
        BluetoothControlTask,
        "BluetoothControlTask",
        2048,
        NULL,
        9,
        &bluetoothCheckTaskHandle,
        1
    );
}

void HgmApplication::HgmBT::BluetoothTaskDelete()
{
    vTaskDelete(bluetoothCheckTaskHandle);
}

void HgmApplication::HgmBT::Begin()
{
    bool sw = true;
    xQueueSend(btCtlMsgbox, &sw, portMAX_DELAY);
}

void HgmApplication::HgmBT::Stop()
{
    bool sw = false;
    xQueueSend(btCtlMsgbox, &sw, portMAX_DELAY);
}



static void BeginWiFiWithConfig(String& ssid, String& password)
{
    hgmApp->BeginWiFiWithConfig((char*)ssid.c_str(), (char*)password.c_str());
}

/**
 * @brief Pack the raw data as a data frame via designated method..
 * @param dataToPack
 * @param method
 * @return pack
 */
String HgmApplication::HgmBT::PackRawData(String& dataToPack, HgmBTPackMethod method)
{
    StaticJsonDocument<512> hgmPack;
    String tmp;
    JsonObject Data;

    hgmPack["Header"] = BT_PACK_HEADER;
    hgmPack["DataType"] = "";

    switch (method) {
    case HGM_BT_PACK_METHOD_OK: {
        // TODO:
        hgmPack["DataType"] = "3";
        hgmPack["Data"] = "ok";
        break;
    }
    case HGM_BT_PACK_METHOD_NORMAL: {
        hgmPack["DataType"] = String(HGM_BT_PACK_METHOD_NULL - 1);
        hgmPack["Data"] = dataToPack.c_str();
    }
    default:
        break;
    }

    serializeJson(hgmPack, tmp);
    return tmp;
}


/**
 * @brief Send the data that is packed.
 * @param rawData
 * @param method
 */
void HgmApplication::HgmBT::SendDatePack(String& rawData, HgmBTPackMethod method)
{
    String pack = HgmBT::PackRawData(rawData, method);
    _bs->write((uint8_t*)pack.c_str(), pack.length());
}

/**
 * @brief Receive and analyze the data pack.
 * @param DateToSave Return data that was analyzed
 * @param method Return method
 */
void HgmApplication::HgmBT::ReceiveDataPack(String& dataToSave, HgmBTPackMethod* method)
{
    if (!_bs->available())
        return;

    DynamicJsonDocument rawPack(1024);

    // Receive raw pack
    while (_bs->available()) {
        dataToSave.concat((char)_bs->read());
    }
    deserializeJson(rawPack, dataToSave.c_str());
    Serial.println(dataToSave);

    // Match Header
    String Header = rawPack["Header"];
    if (Header.compareTo(BT_PACK_HEADER)) {
        Serial.println("Header error. No a valid HGM bluetooth pack");
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_NULL;
    }

    // Match DataType
    HgmBTPackMethod DataType = rawPack["DataType"];
    switch (DataType) {
    case HGM_BT_PACK_METHOD_WIFI_CONF: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_WIFI_CONF;

        // { "Header": "Hgm", "DataType": "0", "Data": { "ssid": "xxx", "password": "xxx" } }
        String _ssid = rawPack["Data"]["ssid"];
        String _password = rawPack["Data"]["password"];
        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);

        hgmApp->StopWiFi();
        vTaskDelay(500);
        BeginWiFiWithConfig(_ssid, _password);
        while (!hgmApp->hgmWifi->wifi->isConnected()) {
            vTaskDelay(50);
        }

        File file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);
        StaticJsonDocument<128> doc;
        String tmp;
        doc["Header"] = "WiFi";
        doc["ssid"] = HgmWiFi::GetSSID();
        doc["password"] = HgmWiFi::GetPassword();
        serializeJson(doc, tmp);
        file.write((const uint8_t*)tmp.c_str(), tmp.length());
        file.close();

        Serial.println("WiFi had been config via bluetooth.");
        return;
    }
    case HGM_BT_PACK_METHOD_WIFI_CLOSE: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_WIFI_CLOSE;

        hgmApp->StopWiFi();

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);
        return;
    }
    case HGM_BT_PACK_METHOD_WEATHER_CONF: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_WEATHER_CONF;

        String id = rawPack["Data"]["id"];
        String adm = rawPack["Data"]["adm"];
        String adm2 = rawPack["Data"]["adm2"];
        String location = rawPack["Data"]["location"];
        String lat = rawPack["Data"]["lat"];
        String lon = rawPack["Data"]["lon"];
        String appKey = rawPack["Data"]["key"];

        WeatherInfo::SetAppKey(appKey);
        WeatherInfo::SetWeatherConfig(id);
        WeatherInfo::SetWeatherConfig(adm, adm2, location);
        WeatherInfo::SetWeatherConfig(lat, lon);

        WeatherInfo::SetWeatherConfig();

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);
        return;
    }
    case HGM_BT_PACK_METHOD_BILIBILI_CONF: {
        dataToSave = String(HGM_BT_PACK_METHOD_NULL);
        *method = HGM_BT_PACK_METHOD_BILIBILI_CONF;

        BiliInfoRecv::SetUID(rawPack["Data"]["uid"].as<String>());
        // TODO: perfect

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);
        return;
    }
    case HGM_BT_PACK_METHOD_NORMAL: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_NORMAL;

        Serial.printf("BT Get (%d) : %s\n", rawPack["Data"].as<String>().length(), rawPack["Data"].as<String>().c_str());

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);
    }
    case HGM_BT_PACK_METHOD_OK: {
        // TODO: test
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_OK;
        return;
    }
    case HGM_BT_PACK_METHOD_GET_M: {
        // TODO: test
        dataToSave = String(HGM_BT_PACK_METHOD_NULL);
        *method = HGM_BT_PACK_METHOD_GET_M;
        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_NORMAL);
        return;
    }
    default:
        Serial.println("DataType error. No a valid HGM bluetooth pack");
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_NULL;
    }

    return;

}


/**
 * @brief To control BT behavior.
 * @param params
 */
static void BluetoothControlTask(void* params)
{
    static TaskHandle_t bluetoothListeningTaskHandle = NULL;
    static bool sw = false;

    while (true) {
        if (xQueueReceive(btCtlMsgbox, &sw, portMAX_DELAY) != pdPASS) {
            continue;
        }

        if (sw) {
            if (bluetoothListeningTaskHandle == NULL) {
                Serial.println("BT Start to listening...");
                _bs->begin(name);
                xTaskCreatePinnedToCore(
                    BluetoothListeningTask,
                    "bluetoothListeningTask",
                    4096,
                    NULL,
                    10,
                    &bluetoothListeningTaskHandle,
                    1
                );
            }
        } else {
            _bs->disconnect();
            _bs->end();
            if (bluetoothListeningTaskHandle) {
                vTaskDelete(bluetoothListeningTaskHandle);
                bluetoothListeningTaskHandle = NULL;
                Serial.println("BT stop ...");
            } else {
                Serial.println("BT stop already");
            }

        }
    }
}

/**
 * @brief Bluetooth listening task.
 * @param params
 */
static void BluetoothListeningTask(void* params)
{
    uint16_t sleepTimes = 1000;
    uint16_t times = 0;
    bool flag = false;

    while (true) {
        // TODO:
        if (!_bs->connected()) {
            flag = false;
            vTaskDelay(1000);
            continue;
        }

        xSemaphoreTake(wbs, portMAX_DELAY);
        if (_bs->available()) {
            String str;
            HgmBTPackMethod method;
            HgmBT::ReceiveDataPack(str, &method);
        }
        xSemaphoreGive(wbs);

        vTaskDelay(10);
    }
}
