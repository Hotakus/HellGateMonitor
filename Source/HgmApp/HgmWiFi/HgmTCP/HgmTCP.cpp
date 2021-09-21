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

#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

using namespace HgmApplication;

#define SERVER_DEFAULT_PORT 20

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
        15,
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
    DynamicJsonDocument hgmPack(512);
    String tmp;
    JsonObject Data;

    hgmPack["Header"] = TCP_PACK_HEADER;
    hgmPack["DataType"] = "";

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
void HgmApplication::HgmTCP::SendDatePack(String& rawData, HgmTcpPackMethod method)
{
    String pack = HgmTCP::PackRawData(rawData, method);
    wc.write((uint8_t*)pack.c_str(), pack.length());
}

/**
 * @brief Receive and analyze the data pack.
 * @param DateToSave Return data that was analyzed
 * @param method Return method
 *
 * @return if OK return HGM_TCP_PACK_METHOD_OK else HGM_TCP_PACK_METHOD_ERROR
 */
HgmTcpPackMethod HgmApplication::HgmTCP::ReceiveDataPack(String& dataToSave, HgmTcpPackMethod* method)
{
    dataToSave = "";

    if (!wc.available())
        return HGM_TCP_PACK_METHOD_ERROR;

    DynamicJsonDocument rawPack(2048);

    // Receive raw pack
    while (wc.available())
        dataToSave.concat((char)wc.read());
    deserializeJson(rawPack, dataToSave.c_str());
    Serial.println(dataToSave);

    // Match Header
    String Header = rawPack["Header"];
    if (Header.compareTo(TCP_PACK_HEADER)) {
        dataToSave = "Header error. No a valid HGM TCP pack";
        Serial.println(dataToSave);
        *method = HGM_TCP_PACK_METHOD_ERROR;
        HgmTCP::SendDatePack(dataToSave, *method);
        return HGM_TCP_PACK_METHOD_ERROR;
    }

    // Match data type
    HgmTcpPackMethod DataType = rawPack["DataType"];
    switch (DataType) {
    case HGM_TCP_PACK_METHOD_NORMAL: {
        dataToSave = "null";
        *method = HGM_TCP_PACK_METHOD_NORMAL;

        Serial.printf("(TCP %d)%s: %s\n", 
            rawPack["Data"].as<String>().length(), 
            wc.remoteIP().toString().c_str(),
            rawPack["Data"].as<String>().c_str());

        HgmTCP::SendDatePack(dataToSave, HGM_TCP_PACK_METHOD_OK);
        return HGM_TCP_PACK_METHOD_OK;
    }
    case HGM_TCP_PACK_METHOD_HWI: {
        dataToSave = "null";
        *method = HGM_TCP_PACK_METHOD_HWI;



        HgmTCP::SendDatePack(dataToSave, HGM_TCP_PACK_METHOD_OK);
        return HGM_TCP_PACK_METHOD_OK;
    }
    default:
        dataToSave = "DataType error. it's not a valid HGM TCP pack";
        Serial.println(dataToSave);
        *method = HGM_TCP_PACK_METHOD_ERROR;
        HgmTCP::SendDatePack(dataToSave, HGM_TCP_PACK_METHOD_OK);
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
    static TaskHandle_t tcpServerTaskHandle = NULL;
    static TaskHandle_t tcpClientTaskHandle = NULL;

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
                    2048,
                    NULL,
                    10,
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
            //if (wc.available()) {
                // TODO: Analyze HGM data pack
                /*size_t size = wc.available();
                uint8_t *buf = (uint8_t*)heap_caps_calloc(size + 1,  1, MALLOC_CAP_SPIRAM);
                buf[wc.available()] = '\0';
                wc.read(buf, size);
                Serial.print(wc.remoteIP());
                Serial.print(" -> ");
                Serial.printf("%s\n", buf);
                heap_caps_free(buf);*/
            //}

            HgmTCP::ReceiveDataPack(_dataToSave, &_recvMethod);

            xSemaphoreGive(wbs);
            vTaskDelay(10);
        }


    _delay:
        vTaskDelay(500);
    }
}
