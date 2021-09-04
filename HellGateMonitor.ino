/******************************************************************
 * @file HellGateMonitor.ino
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/11 20:19
 * @copyright Copyright (c) 2021/8/11
*******************************************************************/

/* User include files */
#include "Source/HgmApp/HgmBT/HgmBT.h"
#include "Source/HgmApp/HgmApp.h"
#include "Source/HgmLvgl/HgmLvgl.h"
#include "Source/HgmSelfChecking/HgmSelfChecking.h"
#include "Source/HgmApp/BiliInfoRecv/BiliInfoRecv.h"
#include "Source/HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "Source/HgmApp/TimeInfo/TimeInfo.h"

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <User_Setup_Select.h>
#include <I2C_MPU6886.h>
#include <ArduinoJson.h>
#include <iostream>
#include <string>
#include <TJpg_Decoder.h>
#include <SPIFFS.h>
#include <freertos/FreeRTOSConfig.h>


#define SCREEN_BK_PIN   32

#define HGM_VERSION_INFO  "dev"
#define HGM_VERSION_MAJOR 1
#define HGM_VERSION_MINOR 0
#define HGM_VERSION_PATCH 0

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__

using namespace HGM;
using namespace HgmGUI;
using namespace HgmApplication;
using namespace fs;

extern HgmApp *hgmApp;
extern HgmLvgl *hgmLvgl;
extern BiliInfoRecv bili;
HgmSetupUI *hgmSetupUI;
TimeInfo ti;


static QueueHandle_t bkMsgBox;
static TaskHandle_t bkHandle;

SemaphoreHandle_t wbs;

// Show the init progress task
static void backlightControl(void *params)
{
	bool flag = false;
	while (true) {
		if (xQueueReceive(bkMsgBox, &flag, portMAX_DELAY) != pdPASS) {

		}

		if (flag) {
			for (size_t i = 0; i < 127; i++) {
				ledcWrite(0, i);
				vTaskDelay(13);
			}
		} else {
			for (size_t i = 127; i > 0; i--) {
				ledcWrite(0, i);
				vTaskDelay(13);
			}
		}
	}
}


void setup()
{
	Serial.begin(115200);
	
	Serial.printf("\n****************** Hell Gate Monitor ******************\n");
	Serial.printf("           ___           ___           ___               \n");
	Serial.printf("          /\\__\\         /\\  \\         /\\__\\        \n");
	Serial.printf("         /:/  /        /::\\  \\       /::|  |           \n");
	Serial.printf("        /:/__/        /:/\\:\\  \\     /:|:|  |          \n");
	Serial.printf("       /::\\  \\ ___   /:/  \\:\\  \\   /:/|:|__|__      \n");
	Serial.printf("      /:/\\:\\  /\\__\\ /:/__/_\\:\\__\\ /:/ |::::\\__\\ \n");
	Serial.printf("      \\/__\\:\\/:/  / \\:\\  /\\ \\/__/ \\/__/~~/:/  /  \n");
	Serial.printf("           \\::/  /   \\:\\ \\:\\__\\         /:/  /     \n");
	Serial.printf("           /:/  /     \\:\\/:/  /        /:/  /          \n");
	Serial.printf("          /:/  /       \\::/  /        /:/  /            \n");
	Serial.printf("          \\/__/         \\/__/         \\/__/           \n\n");
	Serial.printf("Date     : %s %s\n", COMPILE_DATE, COMPILE_TIME);
	Serial.printf("ESP-IDF  : %s\n", ESP.getSdkVersion());
	Serial.printf("FreeRTOS : %s\n", tskKERNEL_VERSION_NUMBER);
	Serial.printf("LVGL     : V%d.%d.%d %s\n", lv_version_major(), lv_version_minor(), lv_version_patch(),
	              lv_version_info());
	Serial.printf("Firmware : V%d.%d.%d %s\n", HGM_VERSION_MAJOR, HGM_VERSION_MINOR, HGM_VERSION_PATCH,
	              HGM_VERSION_INFO);
	Serial.printf("Github   : https://github.com/Hotakus/HellGateMonitor \n");
	Serial.printf("********************************************************\n");

	ledcAttachPin(SCREEN_BK_PIN, 0);
	ledcSetup(0, (10 * 1000), 8);   // PWM 10kHz
	ledcWrite(0, 0);

	bkMsgBox = xQueueCreate(1, sizeof(bool));
	xTaskCreatePinnedToCore(
			backlightControl,
			"backlightControl",
			1024,
			NULL,
			5,
			&bkHandle,
			1
	);

	/* HGM LVGL Component initialize */
	Wire1.begin(21, 22);
	Wire1.setClock(400 * 1000);
	hgmLvgl->HgmLvglBegin();

	bool flag = true;
	xQueueSend(bkMsgBox, &flag, portMAX_DELAY); // Open backlight

	HgmComponent component;
	hgmSetupUI = new HgmSetupUI();
	hgmSetupUI->Begin();
	
	// Semaphore for BT and WiFi. Don't remove it
	wbs = xSemaphoreCreateBinary();
	xSemaphoreGive(wbs);

	hgmApp = new HgmApp(true);
	hgmApp->Stop();	// Stop BT and WiFi.
	while (hgmApp->hgmWifi->wifi->isConnected() || hgmApp->hgmBT->bs->isReady()) // wait to close
		vTaskDelay(10);
	
	// Open bluetooth
	component.type = HGM_COMPONENT_BT;
	component.curStatus = true;
	component.waitStatus = false;
	hgmSetupUI->ComponentControl(&component);
	hgmApp->BeginBT();
	while (!hgmApp->hgmBT->bs->isReady())
		vTaskDelay(10);
	component.waitStatus = true;
	
	vTaskDelay(200);
	
	// Check config file
	HgmSC hgmSC;
	hgmSC.Begin();
	 
	vTaskDelay(200);
	
	// Check WiFi
	component.type = HGM_COMPONENT_WIFI;
	component.curStatus = true;
	component.waitStatus = false;
	hgmSetupUI->ComponentControl(&component);
	hgmApp->hgmWifi->Begin();
	while (!hgmApp->hgmWifi->wifi->isConnected())
		vTaskDelay(50);
	component.waitStatus = true;
	vTaskDelay(200);
	
	// Check time
	ti.Begin();
	vTaskDelay(200);

	// TODO: Check weather component
	
	
	// Check bilibili component
	bili.Begin();
	// bili.GetBasicInfo();
	// bili.GetUserFaceImg();

	// lv_obj_t* img2 = lv_img_create(lv_scr_act());
	// static lv_img_dsc_t face_dsc;
	// face_dsc.header.always_zero = 0;
	// face_dsc.header.w = 64;
	// face_dsc.header.h = 64;
	// face_dsc.data_size = 4096 * 2;
	// face_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
	// face_dsc.data = (uint8_t*)faceBuf;
	// lv_img_set_src(img2, &face_dsc);
	// lv_obj_align(img2, LV_ALIGN_LEFT_MID, 0, 0);


	delete hgmSetupUI;
	
	// TODO: Use task to run
	Serial.println(ESP.getSdkVersion());
	Serial.println(ESP.getChipCores());
	Serial.println(ESP.getChipModel());
	Serial.println(ESP.getCpuFreqMHz());
	Serial.println(ESP.getFlashChipSize());
	Serial.println(ESP.getFlashChipSpeed());
	Serial.println(heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
	Serial.println(ESP.getSketchSize());

	hgmLvgl->HgmLvglUIBegin();

	char* task_buf = (char*)heap_caps_calloc(1, 4096, MALLOC_CAP_SPIRAM);
	vTaskList(task_buf);
	Serial.printf("%s\n", task_buf);
	Serial.printf("Total tasks : %d\n", uxTaskGetNumberOfTasks());
	heap_caps_free(task_buf);
}

void loop()
{
	// char* task_buf = (char*)heap_caps_calloc(1, 4096, MALLOC_CAP_SPIRAM);
	// vTaskList(task_buf);
	// Serial.printf("%s\n", task_buf);
	// Serial.printf("Total tasks : %d\n", uxTaskGetNumberOfTasks());
	// heap_caps_free(task_buf);
	// vTaskDelay(1000);
	
	// vTaskDelay(24 * 3600 * 1000);  // loop per one day
}
