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

#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

#define SERVER_DEFAULT_PORT 20

// extern HardwareCpuData hardwareCpuData;
// extern HardwareGpuData hardwareGpuData;
// extern HardwareMemData hardwareMemData;

extern HardwareRequest hrr;
extern HgmHardwareObject* hgmHardObj[];

extern SemaphoreHandle_t wbs;

static WiFiClass wifi = WiFi;
static WiFiServer _wifiServer;
static WiFiClient _wifiClient;
static WiFiClient wc = NULL;        // To store the object of the client that want to connect to server.

static bool tcpOk = false;
static TcpControlMethod tcm;

static String _dataToSave;
static HgmTcpPackMethod _recvMethod;


static TaskHandle_t tcpControlTaskHandle = NULL;
static QueueHandle_t beginMsgbox = NULL;
static void TcpControlTask(void* params);
static void TcpServerListeningTask(void* params);

static TaskHandle_t tcpServerTaskHandle = NULL;
static TaskHandle_t tcpClientTaskHandle = NULL;

HgmTCP::HgmTCP()
{
    this->wifiServer = wifiServer;
    this->wifiClient = wifiClient;
    beginMsgbox = xQueueCreate(10, sizeof(TcpControlMethod));
}

HgmTCP::~HgmTCP()
{
    vTaskDelete(tcpControlTaskHandle);
    vQueueDelete(beginMsgbox);
}

void HgmApplication::HgmTCP::Begin()
{
    this->HgmTcpTaskInit();
}

void HgmApplication::HgmTCP::Stop()
{

}

/**
 * @brief Init TCP relative task.
 */
void HgmApplication::HgmTCP::HgmTcpTaskInit()
{
    xTaskCreatePinnedToCore(
        TcpControlTask,
        "TcpControlTask",
        2048,
        NULL,
        13,
        &tcpControlTaskHandle,
        1
    );
}


void HgmApplication::HgmTCP::BeginServer()
{
    Serial.println(__func__);
    tcm = TCP_BEGIN_SERVER;
    this->tcm = tcm;
    xQueueSend(beginMsgbox, &tcm, portMAX_DELAY);
}

void HgmApplication::HgmTCP::StopServer()
{
    Serial.println(__func__);
    tcm = TCP_STOP_SERVER;
    this->tcm = tcm;
    xQueueSend(beginMsgbox, &tcm, portMAX_DELAY);
}

void HgmApplication::HgmTCP::BeginClient()
{
    Serial.println(__func__);
    tcm = TCP_BEGIN_CLIENT;
    this->tcm = tcm;
    xQueueSend(beginMsgbox, &tcm, portMAX_DELAY);
}

void HgmApplication::HgmTCP::StopClient()
{
    Serial.println(__func__);
    tcm = TCP_STOP_CLIENT;
    this->tcm = tcm;
    xQueueSend(beginMsgbox, &tcm, portMAX_DELAY);
}

WiFiServer* HgmApplication::HgmTCP::GetWiFiServer()
{
    return &_wifiServer;
}

WiFiClient* HgmApplication::HgmTCP::GetWiFiClient()
{
    return &_wifiClient;
}


/**
 * @brief Pack the raw data as a data frame via designated method..
 * @param dataToPack
 * @param method
 * @return pack
 */
String HgmApplication::HgmTCP::PackRawData(String& dataToPack, HgmTcpPackMethod method)
{
    HotakusDynamicJsonDocument hgmPack(dataToPack.length() + 1024);

    hgmPack["Header"] = TCP_PACK_HEADER;

    switch (method) {
    case HGM_TCP_PACK_METHOD_OK: {
        hgmPack["DataType"] = String(HGM_TCP_PACK_METHOD_OK);
        hgmPack["Data"] = "ok";
        break;
    }
    case HGM_TCP_PACK_METHOD_ERROR: {
        hgmPack["DataType"] = String(HGM_TCP_PACK_METHOD_ERROR);
        hgmPack["Data"] = "error";
        break;
    }
    case HGM_TCP_PACK_METHOD_NORMAL: {
        hgmPack["DataType"] = String(HGM_TCP_PACK_METHOD_NULL - 1);
        hgmPack["Data"] = dataToPack;
        break;
    }
    case HGM_TCP_PACK_METHOD_REQUEST_HWI: {
        hgmPack["DataType"] = String(HGM_TCP_PACK_METHOD_REQUEST_HWI);
        hgmPack["Data"]["CPU"] = String(hrr.rCpu);
        hgmPack["Data"]["GPU"] = String(hrr.rGpu);
        hgmPack["Data"]["Memory"] = String(hrr.rMemory);
        hgmPack["Data"]["HardDisk"] = String(hrr.rHardDisk);
        hgmPack["Data"]["Network"] = String(hrr.rNetwork);
        break;
    }
    default:
        hgmPack["DataType"] = String(HGM_TCP_PACK_METHOD_ERROR);
        hgmPack["Data"] = "null";
        break;
    }

    serializeJson(hgmPack, dataToPack);
    return dataToPack;
}


/**
 * @brief Send the data that is packed.
 * @param rawData
 * @param method
 */
void HgmApplication::HgmTCP::SendDatePack(String& rawData, HgmTcpPackMethod method)
{
    String s = HgmTCP::PackRawData(rawData, method);
    wc.write((uint8_t*)s.c_str(), s.length());
}

/**
 * @brief Receive and analyze the data pack.
 * @param DateToSave Return data that was analyzed
 * @param method Return method
 *
 * @return if OK return HGM_TCP_PACK_METHOD_OK else HGM_TCP_PACK_METHOD_ERROR
 */
HgmTcpPackMethod HgmApplication::HgmTCP::ReceiveDataPack()
{
    if (!wc.available())
        return HGM_TCP_PACK_METHOD_ERROR;

    String str = "";

    // Receive raw pack
    size_t packSize = (wc.available() + 1);
    HotakusDynamicJsonDocument rawPack(packSize + 1024);
    uint8_t* buf = (uint8_t*)heap_caps_calloc(packSize, sizeof(uint8_t), MALLOC_CAP_SPIRAM);
    if (!buf) {
        Serial.println("TCP allocated error");
        HgmTCP::SendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
        return HGM_TCP_PACK_METHOD_ERROR;
    }
    buf[packSize - 1] = '\0';
    for (size_t i = 0; i < packSize - 1; i++)
        buf[i] = (char)wc.read();
    Serial.printf("%s\n", buf);
    deserializeJson(rawPack, buf);
    heap_caps_free(buf);

    // Match Header
    String Header = rawPack["Header"];
    Serial.println("");
    if (Header.compareTo(TCP_PACK_HEADER)) {
        str = "Header error. No a valid HGM TCP pack";
        Serial.println(str);
        HgmTCP::SendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
        return HGM_TCP_PACK_METHOD_ERROR;
    }

    // Match data type
    HgmTcpPackMethod DataType = rawPack["DataType"];
    switch (DataType) {
    case HGM_TCP_PACK_METHOD_NORMAL: {

        Serial.printf("(TCP %d)%s: %s\n",
            rawPack["Data"].as<String>().length(),
            wc.remoteIP().toString().c_str(),
            rawPack["Data"].as<String>().c_str());

        HgmTCP::SendDatePack(str, HGM_TCP_PACK_METHOD_OK);

        return HGM_TCP_PACK_METHOD_OK;
    }
    case HGM_TCP_PACK_METHOD_HWI: {
        if (hrr.rCpu)
            ((HardwareCpuData*)hgmHardObj[HGM_CPU]->params)->Set(rawPack);
        if (hrr.rGpu) 
            ((HardwareGpuData*)hgmHardObj[HGM_GPU]->params)->Set(rawPack);
        if (hrr.rMemory) 
            ((HardwareMemData*)hgmHardObj[HGM_MEMORY]->params)->Set(rawPack);
        if (hrr.rNetwork)
            ((HardwareMemData*)hgmHardObj[HGM_NETWORK]->params)->Set(rawPack);
        if (hrr.rHardDisk)
            ((HardwareDiskData*)hgmHardObj[HGM_HARD_DISK]->params)->Set(rawPack);

        // Serial.println(((HardwareCpuData*)hgmHardObj[HGM_CPU]->params)->name);
        // Serial.println(((HardwareGpuData*)hgmHardObj[HGM_GPU]->params)->name);
        // Serial.println(((HardwareMemData*)hgmHardObj[HGM_MEMORY]->params)->free);
        // Serial.println(((HardwareDiskData*)hgmHardObj[HGM_HARD_DISK]->params)->disk[1].name);
        // Serial.println(((HardwareNetData*)hgmHardObj[HGM_NETWORK]->params)->wlan.nd.downloaded);

        HgmTCP::SendDatePack(str, HGM_TCP_PACK_METHOD_OK);
        return HGM_TCP_PACK_METHOD_OK;
    }
    case HGM_TCP_PACK_METHOD_PROJECTION: {



        HgmTCP::SendDatePack(str, HGM_TCP_PACK_METHOD_OK);
        return HGM_TCP_PACK_METHOD_PROJECTION;
    }
    default:
        str = "DataType error. it's not a valid HGM TCP pack";
        Serial.println(str);
        HgmTCP::SendDatePack(str, HGM_TCP_PACK_METHOD_ERROR);
        return HGM_TCP_PACK_METHOD_OK;
    }

    return HGM_TCP_PACK_METHOD_ERROR;
}

/**
 * @brief TCP control task.
 * @param params
 */

static void TcpControlTask(void* params)
{
    static TcpControlMethod methodRecv = TCP_NULL;
    static uint8_t checkTime = 20;


    while (true) {
        if (xQueueReceive(beginMsgbox, &methodRecv, portMAX_DELAY) != pdPASS) {
            continue;
        }

        switch (methodRecv) {
        case TCP_BEGIN_SERVER:         // server begin
            if (tcpServerTaskHandle == NULL) {
                while (!wifi.isConnected())
                    vTaskDelay(100);
                _wifiServer.begin(SERVER_DEFAULT_PORT);
                xTaskCreatePinnedToCore(
                    TcpServerListeningTask,
                    "TcpServerListeningTask",
                    3072,
                    NULL,
                    9,
                    &tcpServerTaskHandle,
                    1
                );
                Serial.printf("TCP Server begin to listen in port %d.\n", SERVER_DEFAULT_PORT);
            } else {
                Serial.printf("TCP Server already open in port %d\n", SERVER_DEFAULT_PORT);
            }

            break;
        case TCP_BEGIN_CLIENT:         // client begin
            // TODO: If there is not any other app that use client handle
            //while (!wifi.isConnected())
                //vTaskDelay(100);

            Serial.printf("TCP Client begin\n");
            break;
        case TCP_STOP_SERVER:         // server stop
            if (tcpServerTaskHandle) {
                _wifiServer.stop();
                vTaskDelete(tcpServerTaskHandle);
                tcpServerTaskHandle = NULL;
                Serial.printf("TCP server stop\n");
            }
            break;
        case TCP_STOP_CLIENT:         // client stop
            if (tcpClientTaskHandle) {
                _wifiClient.stop();
                vTaskDelete(tcpClientTaskHandle);
                tcpClientTaskHandle = NULL;
                Serial.printf("TCP client stop\n");
            }
            break;
        default:
            Serial.printf("Error in %s %s %s\n", __FILE__, __func__, __LINE__);
            break;
        }

        tcpOk = true;
    }
}

/**
 * @brief Tcp server listening task.
 * @param params
 */
static void TcpServerListeningTask(void* params)
{
    static bool hasClient = false;

    while (true) {
        hasClient = _wifiServer.hasClient();
        if (!hasClient)
            goto _delay;

        /*To accept the client that want to connect server */
        wc = _wifiServer.accept();
        if (!wc)
            goto _delay;
        Serial.printf("A client has connected into server.\n");

        while (wc.connected()) {
            xSemaphoreTake(wbs, portMAX_DELAY);
            HgmTCP::ReceiveDataPack();
            xSemaphoreGive(wbs);
            vTaskDelay(10);
        }


    _delay:
        vTaskDelay(500);
    }





}
