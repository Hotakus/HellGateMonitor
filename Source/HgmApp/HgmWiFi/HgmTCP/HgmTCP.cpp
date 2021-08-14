/******************************************************************
 * @file HgmTCP.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/12 20:21
 * @copyright Copyright (c) 2021/8/12
*******************************************************************/
#include <Arduino.h>
#include <WiFi.h>
#include "HgmTCP.h"

using namespace HgmApplication;

#define SERVER_DEFAULT_PORT 20

static WiFiClass wifi = WiFi;
static WiFiServer wifiServer;
static WiFiClient wifiClient;

static bool tcpOk = false;
TcpControlMethod method;

static TaskHandle_t tcpControlTaskHandle = NULL;
static QueueHandle_t beginMsgbox = NULL;
static void TcpControlTask(void* params);
static void TcpServerListeningTask(void* params);


HgmTCP::HgmTCP()
{
    this->wifiServer = wifiServer;
    this->wifiClient = wifiClient;
    beginMsgbox = xQueueCreate(1, sizeof(TcpControlMethod));
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
        4096,
        NULL,
        5,
        &tcpControlTaskHandle,
        1
    );
}


void HgmApplication::HgmTCP::BeginServer()
{
    Serial.println(__func__);
    method = TCP_BEGIN_SERVER;
    this->tcm = method;
    xQueueSend(beginMsgbox, &method, portMAX_DELAY);
}

void HgmApplication::HgmTCP::StopServer()
{
    method = TCP_STOP_SERVER;
    this->tcm = method;
    xQueueSend(beginMsgbox, &method, portMAX_DELAY);
}

void HgmApplication::HgmTCP::BeginClient()
{
    method = TCP_BEGIN_CLIENT;
    this->tcm = method;
    xQueueSend(beginMsgbox, &method, portMAX_DELAY);
}

void HgmApplication::HgmTCP::StopClient()
{
    method = TCP_STOP_CLIENT;
    this->tcm = method;
    xQueueSend(beginMsgbox, &method, portMAX_DELAY);
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

        for (uint8_t i = 0; i < checkTime; ++i) {
            if (!wifi.isConnected()) {
                Serial.print(".");
                vTaskDelay(500);
            }
        }
        if (!wifi.isConnected()) {
            Serial.println("");
            tcpOk = false;
            continue;
        }

        switch (methodRecv) {
        case TCP_BEGIN_SERVER:         // server begin
            if (tcpServerTaskHandle == NULL) {
                wifiServer.begin(SERVER_DEFAULT_PORT);
                xTaskCreatePinnedToCore(
                    TcpServerListeningTask,
                    "TcpServerListeningTask",
                    4096,
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
            // TODO:

            Serial.printf("TCP Client begin\n");
            break;
        case TCP_STOP_SERVER:         // server stop
            if (tcpServerTaskHandle) {
                wifiServer.stop();
                vTaskDelete(tcpServerTaskHandle);
                tcpServerTaskHandle = NULL;
                Serial.printf("TCP server stop\n");
            }
            break;
        case TCP_STOP_CLIENT:         // client stop
            if (tcpClientTaskHandle) {
                wifiClient.stop();
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
    static WiFiClient wc = NULL;        // To store the object of the client that want to connect to server.

    while (true) {
        hasClient = wifiServer.hasClient();
        if (!hasClient)
            goto _delay;

        /*To accept the client that want to connect server */
        wc = wifiServer.accept();
        if (!wc)
            goto _delay;
        Serial.printf("A client has connected into server.\n");
        

        // TODO: complete the
        while (wc.connected()) {
            if (wc.available()) {
                uint8_t buf[512] = {0};
                wc.read(buf, wc.available());
                Serial.print(wc.remoteIP());
                Serial.print(" -> ");
                Serial.printf("%s\n", buf);
            }
            vTaskDelay(50);
        }


    _delay:
        vTaskDelay(500);
    }
}
