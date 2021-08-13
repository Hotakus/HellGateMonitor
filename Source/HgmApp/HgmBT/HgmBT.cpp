/******************************************************************
 * @file HgmBT.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/13 5:08
 * @copyright Copyright (c) 2021/8/13
*******************************************************************/
#include <Arduino.h>
#include <BluetoothSerial.h>
#include "HgmBT.h"

using namespace HgmApplication;

static QueueHandle_t btCtlMsgbox = NULL;
static TaskHandle_t bluetoothCheckTaskHandle = NULL;
static BluetoothSerial* _bs = NULL;

static char* name = nullptr;

static void BluetoothCheckTask(void* params);
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
        BluetoothCheckTask,
        "BluetoothCheckTask",
        4096,
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


/**
 * @brief Pack the raw data as a data frame via designated method.
 * @param dataToPack
 * @param method
 */
void HgmApplication::HgmBT::PackRawData(const char* dataToPack, size_t size, HgmBTPackMethod method)
{
    // TODO:
}

/**
 * @brief Send the data that is packed.
 * @param rawData
 * @param size
 * @param method
 */
void HgmApplication::HgmBT::SendDatePack(const char* rawData, size_t size, HgmBTPackMethod method)
{
    this->PackRawData(rawData, size, method);
    this->bs->write((const uint8_t*)rawData, size);
}



static void BluetoothCheckTask(void* params)
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
            if (bluetoothListeningTaskHandle) {
                Serial.println("BT stop listening ...");
                _bs->disconnect();
                _bs->end();
                vTaskDelete(bluetoothListeningTaskHandle);
                bluetoothListeningTaskHandle = NULL;
            }
        }
    }
}

static void BluetoothListeningTask(void* params)
{
    while (true) {
        // TODO:
        _bs->printf("Hello %s\n", __func__);
        vTaskDelay(1000);
    }
}
