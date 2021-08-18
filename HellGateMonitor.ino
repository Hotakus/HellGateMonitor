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

/* User include files */
#include "Source/HgmApp/HgmBT/HgmBT.h"
#include "Source/HgmApp/HgmApp.h"
#include "Source/HgmLvgl/HgmLvgl.h"
#include "Source/HgmSelfChecking/HgmSelfChecking.h"
#include "Source/HgmApp/BiliInfoRecv/BiliInfoRecv.h"
#include "Source/LvglSrc/lv_sjpg.h"

#define SCREEN_BK_PIN   32

#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__

using namespace HGM;
using namespace HgmApplication;


char* ssid = "trisuborn";
char* password = "12345678";

extern HgmApp* hgmApp;
extern HgmLvgl* hgmLvgl;


static QueueHandle_t bkMsgBox;
static TaskHandle_t bkHandle;
// Show the init progress task
static void backlightControl(void* params)
{
    bool flag = false;
    while (true) {
        if (xQueueReceive(bkMsgBox, &flag, portMAX_DELAY) != pdPASS) {

        }

        if (flag) {
            for (size_t i = 0; i < 255; i++) {
                ledcWrite(0, i);
                vTaskDelay(10);
            }
        } else {
            for (size_t i = 255; i > 0; i--) {
                ledcWrite(0, i);
                vTaskDelay(10);
            }
        }
    }
}

typedef uint16_t(*_fb_t)[64];
static uint16_t* faceBuf = NULL;
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
    // 强制为二维数组
    uint16_t(*_faceBuf)[64] = (_fb_t)faceBuf;

    size_t pos = 0;
    for (size_t _h = 0; _h < h; _h++) {
        for (size_t _w = 0; _w < w; _w++) {
            _faceBuf[y + _h][x + _w] = (((bitmap[pos] & 0xFF) << 8) | ((bitmap[pos] >> 8) & 0xFF));
            pos++;
        }
    }

    return 1;
}



void setup()
{
    Serial.begin(115200);
    delay(10);

    size_t codeSize = ESP.getSketchSize();
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
    Serial.printf("ESP-IDF  : %x\n", ESP_IDF_VERSION);
    Serial.printf("FreeRTOS : %s\n", tskKERNEL_VERSION_NUMBER);
    Serial.printf("LVGL     : V%d.%d.%d %s\n", lv_version_major(), lv_version_minor(), lv_version_patch(), lv_version_info());
    Serial.printf("Firmware : %0.2f MiB\n", codeSize / 1024.0 / 1024.0);
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
    hgmLvgl->HgmLvglBegin();

    bool flag = true;
    xQueueSend(bkMsgBox, &flag, portMAX_DELAY); // Open backloght

    hgmLvgl->HgmLvglUIBegin();


    hgmApp = new HgmApp(true);

    HgmSC hgmSC;
    hgmSC.Begin();

    BiliInfoRecv bili;
    bili.SetUID("341974201");
    bili.GetBasicInfo();
    bili.GetFollower();
    bili.GetUserFaceImg();
    uint8_t* face;
    size_t size = 0;
    face = bili.GetUserFaceImgBuf(&size);
    Serial.printf("%x\n", face);


    faceBuf = (uint16_t*)heap_caps_calloc(64*64, 2, MALLOC_CAP_SPIRAM);
    TJpgDec.setJpgScale(1);
    TJpgDec.setSwapBytes(true);
    TJpgDec.setCallback(tft_output);

    uint32_t t = millis();
    uint16_t w = 0, h = 0;
    TJpgDec.getJpgSize(&w, &h, face, size);
    Serial.print("Width = ");
    Serial.print(w);
    Serial.print(", height = ");
    Serial.println(h);
    TJpgDec.drawJpg(0, 0, face, size);

    hgmLvgl->lcd->pushImage(0, 0, 64, 64, faceBuf);
    
    t = millis() - t;
    Serial.print(t); Serial.println(" ms");


    delay(1000);

    static lv_obj_t* img1;
    lv_split_jpeg_init();
    img1 = lv_img_create(lv_scr_act());
    static lv_img_dsc_t face_dsc;
    face_dsc.header.always_zero = 0;
    face_dsc.header.w = 64;
    face_dsc.header.h = 64;
    face_dsc.data_size = 4096 * 2;
    face_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
    face_dsc.data = (uint8_t*)faceBuf;
    lv_img_set_src(img1, &face_dsc);
    lv_obj_align(img1, LV_ALIGN_LEFT_MID, 0, 0);
    
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, img1);
    lv_anim_set_values(&anim, 0, 100);
    lv_anim_set_time(&anim, 5000);
    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&anim, lv_anim_path_overshoot);
    lv_anim_start(&anim);

    /*  hgmApp->StopBT();
      vTaskDelay(200);
      hgmApp->BeginBT();*/
}

void loop()
{

}
