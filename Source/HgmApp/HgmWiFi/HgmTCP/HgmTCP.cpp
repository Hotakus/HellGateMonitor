/******************************************************************
 * @file HgmTCP.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/12 20:21
 * @copyright Copyright (c) 2021/8/12
*******************************************************************/

#include "HgmTCP.h"
#include "../../HgmJsonUtil.h"
#include "../../HardwareInfoRecv/HardwareCpuData.h"
#include "../../HardwareInfoRecv/HardwareGpuData.h"
#include "../../HardwareInfoRecv/HardwareMemData.h"
#include "../../HardwareInfoRecv/HardwareNetData.h"
#include "../../HardwareInfoRecv/HardwareDiskData.h"
#include "../../HardwareInfoRecv/HardwareRequest.h"
#include "../../../HgmLvgl/HgmGUI/HgmFramework.h"
#include "../../ScreenRecv/ScreenRecv.h"

#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

#define TAG "HgmTCP"
#define HGM_DEBUG 1
#include "../../../HgmLogUtil.h"
#include <mutex>

using namespace HgmGUI;
using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

extern SemaphoreHandle_t wbs;
extern ScreenRecv screenRecv;

static void TcpControlTask(void* params);
static void TcpServerListeningTask(void* params);

static HgmTCP* instance = nullptr;

HgmTCP::HgmTCP()
{
    instance = this;
    this->wifiServer = new WiFiServer();
    //this->wifiClient = new WiFiClient();
}

HgmTCP::~HgmTCP()
{
    this->stop();
    instance = nullptr;
    delete this->wifiServer;
    //delete this->wifiClient;
}

void HgmApplication::HgmTCP::begin()
{
    frtos.beginMsgbox = xQueueCreate(10, sizeof(TcpControlMethod));
    this->initTask();
}

void HgmApplication::HgmTCP::stop()
{
    this->StopServer();
    this->StopClient();

    while (frtos.tcpServerTaskHandle || frtos.tcpClientTaskHandle)
        vTaskDelay(100);

    this->deInitTask();
    if (frtos.beginMsgbox) {
        vQueueDelete(frtos.beginMsgbox);
        frtos.beginMsgbox = NULL;
    }
}

/**
 * @brief Init TCP relative task.
 */
void HgmApplication::HgmTCP::initTask()
{
    xTaskCreatePinnedToCore(
        TcpControlTask,
        "TcpControlTask",
        3072,
        NULL,
        6,
        &frtos.tcpControlTaskHandle,
        1
    );
}

void HgmApplication::HgmTCP::deInitTask()
{
    if (frtos.tcpControlTaskHandle) {
        vTaskDelete(frtos.tcpControlTaskHandle);
        frtos.tcpControlTaskHandle = NULL;
    }
    instance->isReady = false;
}


void HgmApplication::HgmTCP::BeginServer()
{
    if (!instance->isReady)
        return;
    this->tcm = TCP_BEGIN_SERVER;
    xQueueSend(frtos.beginMsgbox, &tcm, portMAX_DELAY);
}

void HgmApplication::HgmTCP::StopServer()
{
    if (!instance->isReady)
        return;
    this->tcm = TCP_STOP_SERVER;
    xQueueSend(frtos.beginMsgbox, &tcm, portMAX_DELAY);
}

void HgmApplication::HgmTCP::BeginClient()
{
    if (!instance->isReady)
        return;
    // Serial.println(__func__);
    // tcm = TCP_BEGIN_CLIENT;
    // this->tcm = tcm;
    // xQueueSend(beginMsgbox, &tcm, portMAX_DELAY);
}

void HgmApplication::HgmTCP::StopClient()
{
    if (!instance->isReady)
        return;
    // Serial.println(__func__);
    // tcm = TCP_STOP_CLIENT;
    // this->tcm = tcm;
    // xQueueSend(beginMsgbox, &tcm, portMAX_DELAY);
}

WiFiServer* HgmApplication::HgmTCP::GetWiFiServer()
{
    return instance->wifiServer;
}

WiFiClient* HgmApplication::HgmTCP::GetWiFiClient()
{
    return instance->wifiClient;
}


/**
 * @brief Pack the raw data as a data frame via designated method..
 * @param dataToPack
 * @param method
 * @return pack
 */
String HgmApplication::HgmTCP::packRawData(String& dataToPack, HgmTcpPackMethod method)
{
    String out = "";
    HDJsonDoc hgmPack(dataToPack.length() + 1024);

    hgmPack["Header"] = TCP_PACK_HEADER;
    hgmPack["DataType"] = String(method);

    switch (method) {
    case HGM_TCP_PACK_METHOD_OK: {
        hgmPack["Data"] = "ok";
        break;
    }
    case HGM_TCP_PACK_METHOD_ERROR: {
        hgmPack["Data"] = "error";
        break;
    }
    case HGM_TCP_PACK_METHOD_NORMAL: {
        hgmPack["Data"] = dataToPack;
        break;
    }
    case HGM_TCP_PACK_METHOD_REQUEST_HWI: {
        // TODO:
        // hgmPack["Data"]["CPU"] = String(hrr->isRequest(HGM_CPU));
        // hgmPack["Data"]["GPU"] = String(hrr->isRequest(HGM_GPU));
        // hgmPack["Data"]["Memory"] = String(hrr->isRequest(HGM_MEMORY));
        // hgmPack["Data"]["HardDisk"] = String(hrr->isRequest(HGM_HARD_DISK));
        // hgmPack["Data"]["Network"] = String(hrr->isRequest(HGM_NETWORK));
        break;
    }
    case HGM_TCP_PACK_METHOD_DS_MATCH: {
        hgmPack["Data"] = "match";
        break;
    }
    default:
        hgmPack["DataType"] = String(HGM_TCP_PACK_METHOD_ERROR);
        hgmPack["Data"] = "null";
        break;
    }

    serializeJson(hgmPack, out);
    return out;
}


/**
 * @brief Send the data that is packed.
 * @param rawData
 * @param method
 */
void HgmApplication::HgmTCP::sendDatePack(String& rawData, HgmTcpPackMethod method)
{
    String s = HgmTCP::packRawData(rawData, method);
    instance->accept.write((uint8_t*)s.c_str(), s.length());
}

static uint8_t sbuf[8192];
/**
 * @brief Receive and analyze the data pack.
 * @param DateToSave Return data that was analyzed
 * @param method Return method
 *
 * @return if OK return HGM_TCP_PACK_METHOD_OK else HGM_TCP_PACK_METHOD_ERROR
 */
HgmTcpPackMethod HgmApplication::HgmTCP::receiveDataPack()
{
    if (!instance->accept.available())
        return HGM_TCP_PACK_METHOD_ERROR;

    String str = "";
    
    // Receive raw pack
    size_t packSize = (instance->accept.available() + 1);
    DynamicJsonDocument rawPack(packSize + 1024);

    if (!instance->tbuf) {
        Serial.println("TCP allocated error");
        HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
        return HGM_TCP_PACK_METHOD_ERROR;
    }

    instance->accept.readBytes(instance->tbuf, packSize - 1);
    instance->tbuf[packSize - 1] = '\0';
    deserializeJson(rawPack, instance->tbuf);

    // Match Header
    String Header = rawPack["Header"];
    //Serial.println(Header);
    if (Header.compareTo(TCP_PACK_HEADER)) {
        instance->accept.flush();
        str = "Header error. No a valid HGM TCP pack";
        Serial.println(str);
        HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
        return HGM_TCP_PACK_METHOD_ERROR;
    }

    // Match data type
    HgmTcpPackMethod DataType = rawPack["DataType"];
    switch (DataType) {
    case HGM_TCP_PACK_METHOD_NORMAL: {

        Serial.printf("(TCP %d)%s: %s\n",
            rawPack["Data"].as<String>().length(),
            instance->accept.remoteIP().toString().c_str(),
            rawPack["Data"].as<String>().c_str());

        HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_OK);

        return HGM_TCP_PACK_METHOD_OK;
    }
    case HGM_TCP_PACK_METHOD_HWI: {
        str = "HgmMonitorUpdate";
        MsgCenter& mc = HgmFramework::getInstance()->dataCenter;
        msg_t* msg = mc.findMsg(str);
        if (!msg) {
            hgm_log_e(TAG, "Monitor msg is null.");
            return HGM_TCP_PACK_METHOD_ERROR;
        }
        
        HardwareRequest* hrr = (HardwareRequest*)msg->pData();
        if (hrr->isRequest(HGM_CPU))
            hrr->hd->cpuData->Set(rawPack);
        if (hrr->isRequest(HGM_GPU))
            hrr->hd->gpuData->Set(rawPack);
        if (hrr->isRequest(HGM_MEMORY))
            hrr->hd->memData->Set(rawPack);
        if (hrr->isRequest(HGM_NETWORK))
            hrr->hd->netData->Set(rawPack);
        if (hrr->isRequest(HGM_HARD_DISK))
            hrr->hd->diskData->Set(rawPack);

        bool ret = mc.notify(str, str);
        if (ret)
            HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_OK);
        else {
            str = "Monitor has been not open.";
            HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
        }

        return HGM_TCP_PACK_METHOD_OK;
    }
    case HGM_TCP_PACK_METHOD_PROJECTION_BEGIN: {
        sr_data_t dat;

        if (rawPack["Data"]["cf"].as<String>() == "JPG") {
            dat.cf = SR_IMG_FMT_JPG;
        } else if (rawPack["Data"]["cf"].as<String>() == "PNG") {
            dat.cf = SR_IMG_FMT_PNG;
        } else if (rawPack["Data"]["cf"].as<String>() == "RAW") {
            dat.cf = SR_IMG_FMT_RAW;
        } else {
            hgm_log_e(TAG, "Image's format is wrong.");
            HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
            return HGM_TCP_PACK_METHOD_ERROR;
        }

        // dat.w = rawPack["Data"]["w"].as<size_t>();
        // dat.h = rawPack["Data"]["h"].as<size_t>();
        // 
        // screenRecv.setFrameHead(dat);
        // //Serial.printf("---------------------HGM_TCP_PACK_METHOD_PROJECTION- 5\n");
        // 
        // //HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_OK);
        // bool ret = screenRecv.imgReceive(instance->accept);
        // Serial.printf("---------------------HGM_TCP_PACK_METHOD_PROJECTION- 6\n");
        // if (ret)
        //     HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_OK);
        // else 
        //     HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
        // 
        // return HGM_TCP_PACK_METHOD_PROJECTION;

        screenRecv.beginFlag = true;
        screenRecv.setFrameHead(dat);
        screenRecv.imgReceive(instance->accept);
        return HGM_TCP_PACK_METHOD_OK;
    }
    case HGM_TCP_PACK_METHOD_PROJECTION_END: {
        screenRecv.beginFlag = false;
        return HGM_TCP_PACK_METHOD_OK;
    }
    case HGM_TCP_PACK_METHOD_DS_MATCH: {
        instance->isDataSrc = true;
        MsgCenter& mc = HgmFramework::getInstance()->dataCenter;
        msg_t* msg = mc.findMsg("connStatus");
        if (msg) {
            msg->pData(&instance->isDataSrc);
            mc.broadcast(msg);
            HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_OK);
            return HGM_TCP_PACK_METHOD_OK;
        } else {
            HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
            return HGM_TCP_PACK_METHOD_ERROR;
        }
        
    }
    default:
        str = "DataType error. it's not a valid HGM TCP pack";
        Serial.println(str);
        HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
        return HGM_TCP_PACK_METHOD_OK;
    }

    return HGM_TCP_PACK_METHOD_ERROR;
}

bool HgmApplication::HgmTCP::matchDataSrc(size_t timeout)
{
    /* 01 Send the pairing request */
    String str;
    HgmTCP::sendDatePack(str, HGM_TCP_PACK_METHOD_DS_MATCH);
}

/**
 * @brief TCP control task.
 * @param params
 */

static void TcpControlTask(void* params)
{
    static TcpControlMethod methodRecv = TCP_NULL;
    static uint8_t checkTime = 20;

    instance->isReady = true;

    while (true) {
        if (xQueueReceive(instance->frtos.beginMsgbox, &methodRecv, portMAX_DELAY) != pdPASS) {
            continue;
        }

        switch (methodRecv) {
        case TCP_BEGIN_SERVER:         // server begin 
            if (instance->frtos.tcpServerTaskHandle == NULL) {
                while (!WiFi.isConnected())
                    vTaskDelay(100);
                instance->GetWiFiServer()->begin(SERVER_DEFAULT_PORT);
                xTaskCreatePinnedToCore(
                    TcpServerListeningTask,
                    "TcpServerListeningTask",
                    8192,
                    NULL,
                    2, // 9
                    &instance->frtos.tcpServerTaskHandle,
                    1
                );
                Serial.printf("TCP Server begin to listen in port %d.\n", SERVER_DEFAULT_PORT);
            } else {
                Serial.printf("TCP Server already open in port %d\n", SERVER_DEFAULT_PORT);
            }

            break;
        case TCP_BEGIN_CLIENT:         // client begin
            // TODO: If there is not any other app that use client handle
            Serial.printf("TCP Client begin\n");
            break;
        case TCP_STOP_SERVER:         // server stop
            if (instance->frtos.tcpServerTaskHandle) {
                instance->GetWiFiServer()->stop();
                vTaskDelete(instance->frtos.tcpServerTaskHandle);
                instance->frtos.tcpServerTaskHandle = NULL;
                Serial.printf("TCP server stop\n");
            }
            break;
        case TCP_STOP_CLIENT:         // client stop
            break;
        default:
            Serial.printf("Error in %s %s %s\n", __FILE__, __func__, __LINE__);
            break;
        }
    }
}

/**
 * @brief Tcp server listening task.
 * @param params
 */
static void TcpServerListeningTask(void* params)
{
    while (true) {
        if (!instance->GetWiFiServer()->hasClient()) {
            vTaskDelay(1000);
            continue;
        }

        instance->accept = instance->GetWiFiServer()->accept();
        if (!instance->accept) {
            vTaskDelay(1000);
            continue;
        }

        Serial.printf("A client has connected into server.\n");
        instance->hasClient = true;
        instance->matchDataSrc();

        //instance->tbuf = (uint8_t*)heap_caps_calloc(TCP_MAX_BUF_SIZE, sizeof(uint8_t), MALLOC_CAP_SPIRAM);
        instance->tbuf = (uint8_t*)malloc(sizeof(uint8_t) * TCP_MAX_BUF_SIZE);
        while (instance->accept.connected()) {
            xSemaphoreTake(wbs, portMAX_DELAY);
            HgmTCP::receiveDataPack();
            xSemaphoreGive(wbs);
            vTaskDelay(10);
        }
        free(instance->tbuf);
        //heap_caps_free(instance->tbuf);

        instance->hasClient = false;
        instance->isDataSrc = false;
        MsgCenter& mc = HgmFramework::getInstance()->dataCenter;
        msg_t* msg = mc.findMsg("connStatus");
        if (msg) {
            msg->pData(&instance->isDataSrc);
            mc.broadcast(msg);
        }
    }
}
