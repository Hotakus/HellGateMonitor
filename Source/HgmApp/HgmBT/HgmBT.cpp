/******************************************************************
 * @file HgmBT.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief HGM's BT function, use the json format to send/receive data
 * @version 1.0
 * @date 2021/8/13 5:08
 * @copyright Copyright (c) 2021/8/13
*******************************************************************/
#include "HgmBT.h"
#include "../HgmApp.h"
#include "../WeatherInfo/WeatherInfo.h"
#include "../BiliInfoRecv/BiliInfoRecv.h"
#include "../HgmJsonUtil.h"
#include "../HardwareInfoRecv/HardwareRequest.h"

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>


using namespace fs;
using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

extern HgmApp* hgmApp;
extern SemaphoreHandle_t wbs;
extern HardwareRequest hrr;

static QueueHandle_t btCtlMsgbox = NULL;
static TaskHandle_t bluetoothCheckTaskHandle = NULL;
static BluetoothSerial* _bs = NULL;

static char* name = nullptr;

static String _dataToSave = "";
static HgmBTPackMethod _method = HGM_BT_PACK_METHOD_NULL;

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
        13,
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



static void BeginWiFiWithConfig(String ssid, String password)
{
    hgmApp->BeginWiFiWithConfig(ssid, password);

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
        hgmPack["DataType"] = String(HGM_BT_PACK_METHOD_OK);
        hgmPack["Data"] = "ok";
        break;
    }
    case HGM_BT_PACK_METHOD_ERROR: {
        hgmPack["DataType"] = String(HGM_BT_PACK_METHOD_ERROR);
        hgmPack["Data"] = "error";
        break;
    }
    case HGM_BT_PACK_METHOD_NORMAL: {
        hgmPack["DataType"] = String(HGM_BT_PACK_METHOD_NULL - 1);
        hgmPack["Data"] = dataToPack;
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
 * 
 * @return if OK return HGM_BT_PACK_METHOD_OK else HGM_BT_PACK_METHOD_ERROR
 */
HgmBTPackMethod HgmApplication::HgmBT::ReceiveDataPack(String& dataToSave, HgmBTPackMethod* method)
{
    if (!_bs->available())
        return HGM_BT_PACK_METHOD_ERROR;

    HotakusDynamicJsonDocument rawPack(_bs->available() + 1024);

    dataToSave = "";

    // Receive raw pack
    while (_bs->available())
        dataToSave.concat((char)_bs->read());
    deserializeJson(rawPack, dataToSave.c_str());
    Serial.println(dataToSave);

    // Match Header
    String Header = rawPack["Header"];
    if (Header.compareTo(BT_PACK_HEADER)) {
        dataToSave = "Header error. it's not a valid HGM bluetooth pack";
        Serial.println(dataToSave);
        Serial.println(Header);
        *method = HGM_BT_PACK_METHOD_ERROR;
        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_ERROR);
        return HGM_BT_PACK_METHOD_ERROR;
    }

    // Match DataType
    HgmBTPackMethod DataType = rawPack["DataType"];
    switch (DataType) {
    case HGM_BT_PACK_METHOD_WIFI_CONF: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_WIFI_CONF;

        String _ssid = rawPack["Data"]["ssid"];
        String _password = rawPack["Data"]["password"];

        hgmApp->StopWiFi();
        vTaskDelay(1000);
        BeginWiFiWithConfig(_ssid, _password);

        DynamicJsonDocument doc(256);
        String tmp;
        doc["Header"] = "WiFi";
        doc["ssid"] = HgmWiFi::GetSSID();
        doc["password"] = HgmWiFi::GetPassword();
        serializeJson(doc, tmp);

        Serial.println(tmp);

        File file = SPIFFS.open(WIFI_CONFIG_FILE_PATH, FILE_WRITE);
        file.write((const uint8_t*)tmp.c_str(), tmp.length());
        file.close();

        Serial.println("WiFi had been config via bluetooth.");

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);

        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_WIFI_CLOSE: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_WIFI_CLOSE;

        hgmApp->StopWiFi();

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);
        return HGM_BT_PACK_METHOD_OK;
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
        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_BILIBILI_CONF: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_BILIBILI_CONF;

        String _uid = rawPack["Data"]["uid"];

        BiliInfoRecv::SetUID(_uid);

        DynamicJsonDocument doc(256);
        String tmp;
        doc["Header"] = "bilibili";
        doc["Data"]["uid"] = _uid;
        serializeJson(doc, tmp);

        Serial.printf("BT Bili config : %s\n", tmp.c_str());

        File file = SPIFFS.open(BILI_CONFIG_FILE_PATH, FILE_WRITE);
        file.write((const uint8_t*)tmp.c_str(), tmp.length());
        file.close();

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);
        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_NORMAL: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_NORMAL;

        Serial.printf("(BT %d): %s\n",
            rawPack["Data"].as<String>().length(),
            rawPack["Data"].as<String>().c_str());

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);
    }
    case HGM_BT_PACK_METHOD_OK: {
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_OK;
        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_GET_M: {
        dataToSave = String(HGM_BT_PACK_METHOD_NULL);
        *method = HGM_BT_PACK_METHOD_GET_M;
        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_NORMAL);
        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_HWM_CONF: {
        // TODO: 
        dataToSave = "null";
        *method = HGM_BT_PACK_METHOD_HWM_CONF;

        

        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_OK);
        return HGM_BT_PACK_METHOD_OK;
    }
    default:
        dataToSave = "DataType error. it's not a valid HGM TCP pack";
        Serial.println(dataToSave);
        *method = HGM_BT_PACK_METHOD_ERROR;
        HgmBT::SendDatePack(dataToSave, HGM_BT_PACK_METHOD_ERROR);
        return HGM_BT_PACK_METHOD_ERROR;
    }

    return HGM_BT_PACK_METHOD_ERROR;
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
                    3072,
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
    bool flag = false;
    String greet = "Hello, I am HellGateMonitorBT!!";

    while (true) {
        if (!_bs->connected()) {
            flag = false;
            vTaskDelay(1000);
            continue;
        }

        if (!flag) {
            flag = true;
            xSemaphoreTake(wbs, portMAX_DELAY);
            _bs->write((const uint8_t*)greet.c_str(), greet.length());
            xSemaphoreGive(wbs);
        }
        
        xSemaphoreTake(wbs, portMAX_DELAY);
        if (_bs->available())
            HgmBT::ReceiveDataPack(_dataToSave, &_method);
        xSemaphoreGive(wbs);

        vTaskDelay(50);
    }
}
