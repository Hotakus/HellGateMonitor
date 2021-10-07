/******************************************************************
 * @file TimeInfo.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/20 10:27
 * @copyright Copyright (c) 2021/8/20
*******************************************************************/
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Time.h>
#include "TimeInfo.h"
#include "../HgmWiFi/HgmTCP/HgmTCP.h"
#include "../../HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "../HgmJsonUtil.h"

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;
using namespace HgmGUI;

static String timeAPI = "http://quan.suning.com/getSysTime.do";

static ESP32Time *_rtc;
static struct tm _timeStruct;

extern HTTPClient hgmHttpClient;

static TaskHandle_t netTimeTaskHandle;
static QueueHandle_t netTimeMsgBox;
static void netTimeTask(void* params);

static HgmComponent component;

extern HgmSetupUI *hgmSetupUI;

TimeInfo ti;

TimeInfo::TimeInfo()
{
	_rtc = &this->rtc;
}

TimeInfo::~TimeInfo()
{
	this->DeInitTask();
}

void HgmApplication::TimeInfo::InitTask()
{
	if (netTimeTaskHandle)
		return;

	xTaskCreatePinnedToCore(
		netTimeTask,
		"netTimeTask",
		3072,
		NULL,
		8,
		&netTimeTaskHandle,
		1
	);
}

void HgmApplication::TimeInfo::DeInitTask()
{
	if (netTimeTaskHandle) {
		vTaskDelete(netTimeTaskHandle);
		netTimeTaskHandle = NULL;
	}
}

void HgmApplication::TimeInfo::Begin()
{
	uint8_t timeout = 50;

	component.type = HGM_COMPONENT_NET_TIME;
	component.curStatus = true;
	component.waitStatus = false;
	hgmSetupUI->ComponentControl(&component);
	while (GetNetTime(0) != 0) {
		if (!(--timeout))
			return;
		vTaskDelay(100);
	}
	component.waitStatus = true;

	this->InitTask();
}

int HgmApplication::TimeInfo::GetNetTime(struct tm *timeStruct)
{
	hgmHttpClient.setConnectTimeout(3 * 1000);
	hgmHttpClient.setTimeout(3 * 1000);
	hgmHttpClient.begin(timeAPI);
	int code = hgmHttpClient.GET();

	if (code != HTTP_CODE_OK) {
		Serial.printf("HTTP code : %d\n", code);
		hgmHttpClient.end();
		return -1;
	}
	String recv = hgmHttpClient.getString();
	HotakusDynamicJsonDocument doc(recv.length() + 512);
	deserializeJson(doc, recv);
	Serial.println(recv);

	// {"sysTime2":"2021-08-21 04:55:48","sysTime1":"20210821045548"}
	String sysTime1 = doc["sysTime1"];
	if (!sysTime1) {
		Serial.printf("Get time error.\n", code);
		return -1;
	}

	uint16_t year = sysTime1.substring(0, 4).toInt();
	uint8_t mon = sysTime1.substring(4, 6).toInt();
	uint8_t day = sysTime1.substring(6, 8).toInt();
	uint8_t hour = sysTime1.substring(8, 10).toInt();
	uint8_t min = sysTime1.substring(10, 12).toInt();
	uint8_t sec = sysTime1.substring(12).toInt();

	_rtc->setTime(sec, min, hour, day, mon, year);
	_timeStruct = _rtc->getTimeStruct();
	timeStruct = &_timeStruct;

	hgmHttpClient.end();
	return 0;
}

static void netTimeTask(void* params)
{
	static struct tm ts;
	extern SemaphoreHandle_t wbs;

	Serial.println("netTimeTask");

	while (true) {

		if (!WiFi.isConnected()) {
			vTaskDelay(1000);
			continue;
		}

		xSemaphoreTake(wbs, portMAX_DELAY);
		TimeInfo::GetNetTime(&ts);
		xSemaphoreGive(wbs);
		
		vTaskDelay(NET_TIME_GAP);
	}
}
