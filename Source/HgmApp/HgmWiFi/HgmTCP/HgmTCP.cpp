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
    static TaskHandle_t tcpTaskHandle;

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
            tcpOk = false;
            continue;
        }

        switch (methodRecv) {
        case TCP_BEGIN_SERVER:         // server begin
            wifiServer.begin(SERVER_DEFAULT_PORT);
            xTaskCreatePinnedToCore(
                TcpServerListeningTask,
                "TcpServerListeningTask",
                4096,
                NULL,
                10,
                &tcpTaskHandle,
                1
            );
            break;
        case TCP_BEGIN_CLIENT:         // client begin
            // TODO
            break;
        case TCP_STOP_SERVER:         // server stop
            vTaskDelete(tcpTaskHandle);
            wifiServer.stop();
            break;
        case TCP_STOP_CLIENT:         // client stop
            // TODO
            vTaskDelete(tcpTaskHandle);
            wifiClient.stop();
            break;
        default:
            Serial.printf("Error in %s %s %s", __FILE__, __func__, __LINE__);
            break;
        }



        tcpOk = true;
    }
}

static void TcpServerListeningTask(void* params)
{
    static bool hasClient = false;

    Serial.printf("TCP Server begin to listen in port %d.\n", SERVER_DEFAULT_PORT);
    while (true) {
        hasClient = wifiServer.hasClient();
        if (!hasClient)
            goto _delay;

        /*To accept the client that want to connect server */
        Serial.printf("There is a client try to connect.\n");
        wifiClient = wifiServer.accept();
        if (!wifiClient)
            goto _delay;
        Serial.printf("A client has connected into server.\n");
        
        while (wifiClient.connected()) {
            if (wifiClient.available()) {
                uint8_t buf[512] = {0};
                wifiClient.read(buf, wifiClient.available());
                Serial.print(wifiClient.remoteIP());
                Serial.print(" -> ");
                Serial.printf("%s\n", buf);
                if (buf[0] == 'e')
                    wifiClient.stop();
            }
            vTaskDelay(50);
        }


    _delay:
        vTaskDelay(500);
    }
}
