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
#include "../HgmWiFi/HgmWiFi.h"
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

extern SemaphoreHandle_t wbs;

static void BluetoothControlTask(void* params);
static void BluetoothListeningTask(void* params);

extern HgmWiFi hgmWiFi;
extern BiliInfoRecv bili;
HgmBT hgmBT;

/**
 * @brief Construct.
 * @param n set the name of the bluetooth
 */
HgmBT::HgmBT()
{
    this->bs = new BluetoothSerial();
    frtos.btCtlMsgbox = xQueueCreate(1, sizeof(bool));
    //this->BluetoothTaskInit();
}

HgmBT::~HgmBT()
{
    this->BluetoothTaskDelete();
    vQueueDelete(frtos.btCtlMsgbox);
}

void HgmApplication::HgmBT::BluetoothTaskInit()
{
    //xTaskCreatePinnedToCore(
    //    BluetoothControlTask,
    //    "BluetoothControlTask",
    //    3072,
    //    NULL,
    //    10,
    //    &bluetoothCheckTaskHandle,
    //    1
    //);
}

void HgmApplication::HgmBT::BluetoothTaskDelete()
{
    // vTaskDelete(bluetoothCheckTaskHandle);
}

bool sw = false;
void HgmApplication::HgmBT::begin()
{
    //sw = true;
    //Serial.println("HgmBT::begin() 0");
    //xQueueSend(frtos.btCtlMsgbox, &sw, portMAX_DELAY);
    //Serial.println("HgmBT::begin() 1");

    if (!frtos.btListeningTaskHandle) {
        hgmBT.bs->begin(name);
        xTaskCreatePinnedToCore(
            BluetoothListeningTask,
            "bluetoothListeningTask",
            3072,
            NULL,
            9,
            &frtos.btListeningTaskHandle,
            1
        );
    }
}

void HgmApplication::HgmBT::stop()
{
    //sw = false;
    //xQueueSend(frtos.btCtlMsgbox, &sw, portMAX_DELAY);

    hgmBT.bs->disconnect();
    hgmBT.bs->end();
    if (frtos.btListeningTaskHandle) {
        vTaskDelete(frtos.btListeningTaskHandle);
        frtos.btListeningTaskHandle = NULL;
        Serial.println("BT stop ...");
    } else {
        Serial.println("BT stop already");
    }
}

void HgmApplication::HgmBT::setName(String _name)
{
    hgmBT.name = _name;
}

static void BeginWiFiWithConfig(String ssid, String password)
{
    hgmWiFi.ConfigWiFi(ssid, password);
    hgmWiFi.begin();
}

/**
 * @brief Pack the raw data as a data frame via designated method..
 * @param dataToPack
 * @param method
 * @return pack
 */
String HgmApplication::HgmBT::packRawData(String& dataToPack, HgmBTPackMethod method)
{
    HDJsonDoc hgmPack(8192);
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
void HgmApplication::HgmBT::sendDatePack(String& rawData, HgmBTPackMethod method)
{
    String pack = HgmBT::packRawData(rawData, method);
    hgmBT.bs->write((uint8_t*)pack.c_str(), pack.length());
}

/**
 * @brief Receive and analyze the data pack.
 * @param DateToSave Return data that was analyzed
 * @param method Return method
 *
 * @return if OK return HGM_BT_PACK_METHOD_OK else HGM_BT_PACK_METHOD_ERROR
 */
HgmBTPackMethod HgmApplication::HgmBT::receiveDataPack()
{
    if (!hgmBT.bs->available())
        return HGM_BT_PACK_METHOD_ERROR;

    String str = "";
    HDJsonDoc rawPack(hgmBT.bs->available() + 1024);

    size_t packSize = hgmBT.bs->available();
    uint8_t* buf = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * (packSize + 32));
    hgmBT.bs->readBytes(buf, packSize);
    buf[packSize] = '\0';
    deserializeJson(rawPack, buf);
    Serial.printf("%s\n", buf);

    // Match Header
    String Header = rawPack["Header"];
    if (Header.compareTo(BT_PACK_HEADER)) {
        str = "Header error. it's not a valid HGM bluetooth pack";
        Serial.println(str);
        Serial.println(Header);
        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_ERROR);
        return HGM_BT_PACK_METHOD_ERROR;
    }

    // Match DataType
    HgmBTPackMethod DataType = rawPack["DataType"];
    switch (DataType) {
    case HGM_BT_PACK_METHOD_WIFI_CONF: {
        str = "";

        String _ssid = rawPack["Data"]["ssid"];
        String _password = rawPack["Data"]["password"];

        hgmWiFi.stop();
        vTaskDelay(1000);
        BeginWiFiWithConfig(_ssid, _password);

        HDJsonDoc doc(256);
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

        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_OK);

        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_WIFI_CLOSE: {
        str = "";
        hgmWiFi.stop();
        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_OK);
        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_WEATHER_CONF: {
        str = "";

        String id = rawPack["Data"]["id"];
        String adm = rawPack["Data"]["adm"];
        String adm2 = rawPack["Data"]["adm2"];
        String location = rawPack["Data"]["location"];
        String lat = rawPack["Data"]["lat"];
        String lon = rawPack["Data"]["lon"];
        String appKey = rawPack["Data"]["key"];

        WeatherInfo::setAppKey(appKey);
        WeatherInfo::setWeatherConfig(id);
        WeatherInfo::setWeatherConfig(adm, adm2, location);
        WeatherInfo::setWeatherConfig(lat, lon);

        WeatherInfo::setWeatherConfig();

        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_OK);
        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_BILIBILI_CONF: {
        str = "";

        String _uid = rawPack["Data"]["uid"];
        BiliInfoRecv::uid(_uid);
        HDJsonDoc doc(256);
        String tmp;
        doc["Header"] = "bilibili";
        doc["Data"]["uid"] = _uid;
        serializeJson(doc, tmp);

        Serial.printf("BT Bili config : %s\n", tmp.c_str());

        File file = SPIFFS.open(BILI_CONFIG_FILE_PATH, FILE_WRITE);
        file.write((const uint8_t*)tmp.c_str(), tmp.length());
        file.close();

        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_OK);
        
        bili.getBasicInfo();
        bili.getUserFaceImg();

        String str = String("HgmTwUpdate");
        MsgCenter* mc = &HgmFramework::getInstance()->dataCenter;
        msg_t* msg = mc->findMsg(str);
        HgmTwModel::tw_data_t* tw_data = (HgmTwModel::tw_data_t*)msg->pData();

        tw_data->tdt = HgmTwModel::BILI;
        tw_data->bd.bn = bili.getUserName();
        tw_data->bd.fans = bili.getFollower();
        tw_data->bd.ufb = (uint8_t*)bili.getUserFaceBitmap();
        tw_data->bd.uid = bili.uid();

        mc->notify(str, str);

        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_NORMAL: {
        str = "";

        Serial.printf("(BT %d): %s\n",
            rawPack["Data"].as<String>().length(),
            rawPack["Data"].as<String>().c_str());

        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_OK);
    }
    case HGM_BT_PACK_METHOD_OK: {
        str = "";
        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_GET_M: {
        str = String(HGM_BT_PACK_METHOD_NULL);
        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_NORMAL);
        return HGM_BT_PACK_METHOD_OK;
    }
    case HGM_BT_PACK_METHOD_HWM_CONF: {
        // TODO: 
        str = "";

        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_OK);
        return HGM_BT_PACK_METHOD_OK;
    }
    default:
        str = "DataType error. it's not a valid HGM TCP pack";
        Serial.println(str);
        HgmBT::sendDatePack(str, HGM_BT_PACK_METHOD_ERROR);
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
    static bool sw = false;

    while (true) {
        if (xQueueReceive(hgmBT.frtos.btCtlMsgbox, &sw, portMAX_DELAY) != pdPASS)
            continue;

        if (sw) {

        } else {

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
        if (!hgmBT.bs->connected()) {
            flag = false;
            vTaskDelay(1000);
            continue;
        }

        if (!flag) {
            flag = true;
            xSemaphoreTake(wbs, portMAX_DELAY);
            hgmBT.bs->write((const uint8_t*)greet.c_str(), greet.length());
            xSemaphoreGive(wbs);
        }

        if (hgmBT.bs->available()) {
            xSemaphoreTake(wbs, portMAX_DELAY);
            HgmBT::receiveDataPack();
            xSemaphoreGive(wbs);
        }

        vTaskDelay(100);
    }
}
