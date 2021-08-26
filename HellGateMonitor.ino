/******************************************************************
 * @file HellGateMonitor.ino
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/11 20:19
 * @copyright Copyright (c) 2021/8/11
*******************************************************************/
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <User_Setup_Select.h>
#include <I2C_MPU6886.h>
#include <ArduinoJson.h>
#include <iostream>
#include <string>
#include <TJpg_Decoder.h>
#include <freertos/FreeRTOSConfig.h>

/* User include files */
#include "Source/HgmApp/HgmBT/HgmBT.h"
#include "Source/HgmApp/HgmApp.h"
#include "Source/HgmLvgl/HgmLvgl.h"
#include "Source/HgmSelfChecking/HgmSelfChecking.h"
#include "Source/HgmApp/BiliInfoRecv/BiliInfoRecv.h"
#include "Source/HgmLvgl/HgmGUI/HgmSetupUI.h"
#include "Source/HgmApp/TimeInfo/TimeInfo.h"

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

extern HgmApp *hgmApp;
extern HgmLvgl *hgmLvgl;
HgmSetupUI *hgmSetupUI;
TimeInfo ti;

static QueueHandle_t bkMsgBox;
static TaskHandle_t bkHandle;

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

typedef uint16_t(*_fb_t)[64];
static uint16_t *faceBuf = NULL;

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
	// 强制为二维数组
	uint16_t(*_faceBuf)[64] = (_fb_t) faceBuf;

	size_t pos = 0;
	for (size_t _h = 0; _h < h; _h++) {
		for (size_t _w = 0; _w < w; _w++) {
			// 字序交替赋值
			//_faceBuf[y + _h][x + _w] = (((bitmap[pos] & 0xFF) << 8) | ((bitmap[pos] >> 8) & 0xFF));
			_faceBuf[y + _h][x + _w] = bitmap[pos];
			pos++;
		}
	}

	return 1;
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

	hgmApp = new HgmApp(true);

	// Stop BT and WiFi.
	hgmApp->Stop();
	vTaskDelay(200);

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

	// Check weather component
	




	//BiliInfoRecv bili;
	//bili.SetUID("341974201");
	//bili.GetBasicInfo();
	//bili.GetFollower();
	//bili.GetUserFaceImg();
	//uint8_t* face;
	//size_t size = 0;
	//face = bili.GetUserFaceImgBuf(&size);
	//Serial.printf("%x\n", face);

	//faceBuf = (uint16_t*)heap_caps_calloc(64*64, 2, MALLOC_CAP_SPIRAM);
	//TJpgDec.setJpgScale(1);
	//TJpgDec.setSwapBytes(false);
	//TJpgDec.setCallback(tft_output);

	//uint32_t t = millis();
	//uint16_t w = 0, h = 0;
	//TJpgDec.getJpgSize(&w, &h, face, size);
	//Serial.print("Width = ");
	//Serial.print(w);
	//Serial.print(", height = ");
	//Serial.println(h);
	//TJpgDec.drawJpg(0, 0, face, size);

	//hgmLvgl->lcd->pushImage(0, 0, 64, 64, faceBuf);

	//t = millis() - t;
	//Serial.print(t); Serial.println(" ms");


	//delay(1000);

	//static lv_obj_t* img2;
	//img2 = lv_img_create(lv_scr_act());
	//static lv_img_dsc_t face_dsc;
	//face_dsc.header.always_zero = 0;
	//face_dsc.header.w = 64;
	//face_dsc.header.h = 64;
	//face_dsc.data_size = 4096 * 2;
	//face_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
	//face_dsc.data = (uint8_t*)faceBuf;
	//lv_img_set_src(img2, &face_dsc);
	//lv_obj_align(img2, LV_ALIGN_LEFT_MID, 0, 0);

	//lv_anim_t anim1;
	//lv_anim_init(&anim1);
	//lv_anim_set_var(&anim1, img2);
	//lv_anim_set_values(&anim1, 0, 100);
	//lv_anim_set_time(&anim1, 1000);
	//lv_anim_set_exec_cb(&anim1, (lv_anim_exec_xcb_t)lv_obj_set_x);
	//lv_anim_set_path_cb(&anim1, lv_anim_path_overshoot);
	//lv_anim_start(&anim1);


	Serial.println(ESP.getSdkVersion());
	Serial.println(ESP.getChipCores());
	Serial.println(ESP.getChipModel());
	Serial.println(ESP.getCpuFreqMHz());
	Serial.println(ESP.getFlashChipSize());
	Serial.println(ESP.getFlashChipSpeed());
	Serial.println(heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
	Serial.println(heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
	Serial.println(ESP.getSketchSize());
}

void loop()
{
	vTaskDelay(3600 * 24);  // loop per one day
}



//// Include the jpeg decoder library
//#include <TJpg_Decoder.h>
//#include "SPI.h"
//#include <TFT_eSPI.h>      
//
//#define USE_DMA
//
//#ifdef USE_DMA
//uint16_t  dmaBuffer1[16 * 16]; // Toggle buffer for 16*16 MCU block, 512bytes
//uint16_t  dmaBuffer2[16 * 16]; // Toggle buffer for 16*16 MCU block, 512bytes
//uint16_t* dmaBufferPtr = dmaBuffer1;
//bool dmaBufferSel = 0;
//#endif
//    
//TFT_eSPI tft = TFT_eSPI(240, 135);         // Invoke custom library
//
//// This next function will be called during decoding of the jpeg file to render each
//// 16x16 or 8x8 image tile (Minimum Coding Unit) to the TFT.
//bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
//{
//
//#ifdef USE_DMA
//  // Double buffering is used, the bitmap is copied to the buffer by pushImageDMA() the
//  // bitmap can then be updated by the jpeg decoder while DMA is in progress
//    if (dmaBufferSel) dmaBufferPtr = dmaBuffer2;
//    else dmaBufferPtr = dmaBuffer1;
//    dmaBufferSel = !dmaBufferSel; // Toggle buffer selection
//    //  pushImageDMA() will clip the image block at screen boundaries before initiating DMA
//    tft.pushImageDMA(x, y, w, h, bitmap, dmaBufferPtr); // Initiate DMA - blocking only if last DMA is not complete
//    // The DMA transfer of image block to the TFT is now in progress...
//#else
//  // Non-DMA blocking alternative
//    tft.pushImage(x, y, w, h, bitmap);  // Blocking, so only returns when image block is drawn
//#endif
//    return 1;
//}
//
//void setup()
//{
//    Serial.begin(115200);
//    Serial.println("\n\n Testing TJpg_Decoder library");
//
//    // Initialise the TFT
//    tft.begin();
//    tft.setTextColor(TFT_WHITE, TFT_BLACK);
//    tft.fillScreen(TFT_BLACK);
//
//#ifdef USE_DMA
//    tft.initDMA(); // To use SPI DMA you must call initDMA() to setup the DMA engine
//#endif
//
//  // The jpeg image can be scaled down by a factor of 1, 2, 4, or 8
//    TJpgDec.setJpgScale(1);
//
//    // The colour byte order can be swapped by the decoder
//    // using TJpgDec.setSwapBytes(true); or by the TFT_eSPI library:
//    tft.setSwapBytes(true);
//
//    // The decoder must be given the exact name of the rendering function above
//    TJpgDec.setCallback(tft_output);
//}
//
//void loop()
//{
//    // Show a contrasting colour for demo of draw speed
//    tft.fillScreen(TFT_RED);
//    uint32_t dt = millis();
//    tft.startWrite();
//
//    tft.dma
//
//    tft.endWrite();
//
//    dt = millis() - dt;
//    Serial.print(dt); Serial.println(" ms");
//
//    // Wait before drawing again
//    delay(1000);
//}
