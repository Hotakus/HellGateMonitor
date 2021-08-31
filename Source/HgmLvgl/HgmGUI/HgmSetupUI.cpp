/******************************************************************
 * @file HgmSetupUI.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/18 23:18
 * @copyright Copyright (c) 2021/8/18
*******************************************************************/
#include "HgmSetupUI.h"
#include"../HgmLvgl.h"
#include <TJpg_Decoder.h>
#include <iostream>

using namespace HgmGUI;
using namespace HGM;

LV_IMG_DECLARE(testbg);
LV_IMG_DECLARE(HGM_LOGO);

LV_IMG_DECLARE(book_left);
LV_IMG_DECLARE(book_mid);
LV_IMG_DECLARE(book_right);

LV_IMG_DECLARE(bg_left);
LV_IMG_DECLARE(bg_mid);
LV_IMG_DECLARE(bg_right);

// background's buffer type
typedef uint16_t(*_bg_t)[HGM_MONITOR_HEIGHT];
static uint16_t* BackgroundBuf = NULL;  // background's buffer

static String prevText = "";
static String curText = "";

static bool initFlag = false;

// progress bar
static lv_obj_t* pb;
// LOGO
lv_obj_t* logo;
// progress label
lv_obj_t* prevCheckLabel;
lv_obj_t* curCheckLabel;
static lv_style_t clStyle;

//
static QueueHandle_t setupMsgBox;
static TaskHandle_t setupTaskHandle;
static void SetupCheckTask(void* params);


HgmSetupUI::HgmSetupUI()
{
    setupMsgBox = xQueueCreate(1, sizeof(void*));   // Get size of a pointer
    xTaskCreatePinnedToCore(
        SetupCheckTask,
        "SetupCheckTask",
        2048,
        NULL,
        5,
        &setupTaskHandle,
        1
    );
}

HgmSetupUI::~HgmSetupUI()
{
    vTaskDelete(setupTaskHandle);
    vQueueDelete(setupMsgBox);
}

static void anim_cb(void* obj, int32_t val)
{
    lv_obj_set_x((_lv_obj_t*)obj, val);
}

void HgmGUI::HgmSetupUI::Begin()
{
    // Set the bg for lv_scr_act()
    //lv_obj_set_style_bg_img_src(lv_scr_act(), &HGMBG, 0);
    //lv_obj_set_style_bg_img_src(lv_scr_act(), &testbg, 0);
    lv_obj_set_scrollbar_mode(lv_scr_act(), LV_SCROLLBAR_MODE_OFF);

    lv_obj_t* bg = lv_imgbtn_create(lv_scr_act());
    lv_imgbtn_set_src(bg, LV_IMGBTN_STATE_RELEASED, &bg_left, &bg_mid, &bg_right);
    lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_width(bg, 240);

    vTaskDelay(0);

    // TODO: test
    lv_obj_t* imgbtn = lv_imgbtn_create(lv_scr_act());
    lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, &book_left, &book_mid, &book_right);
    lv_obj_align(imgbtn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_width(imgbtn, 97);

    lv_anim_t logoAnim;
    lv_anim_init(&logoAnim);
    lv_anim_set_var(&logoAnim, imgbtn);
    lv_anim_set_values(&logoAnim, 97, 234);
    lv_anim_set_time(&logoAnim, 1000);
    lv_anim_set_exec_cb(&logoAnim, (lv_anim_exec_xcb_t)lv_obj_set_width);
    lv_anim_set_path_cb(&logoAnim, lv_anim_path_linear);
    lv_anim_start(&logoAnim);

    vTaskDelay(2000);

    // logo
    //logo = lv_img_create(lv_scr_act());
    //lv_img_set_src(logo, &HGM_LOGO);
    //lv_obj_align(logo, LV_ALIGN_TOP_MID, 0, -32);
    //lv_anim_t logoAnim;
    //lv_anim_init(&logoAnim);
    //lv_anim_set_var(&logoAnim, logo);
    //lv_anim_set_values(&logoAnim, -32, 25);
    //lv_anim_set_time(&logoAnim, 700);
    //lv_anim_set_exec_cb(&logoAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    //lv_anim_set_path_cb(&logoAnim, lv_anim_path_overshoot);
    //lv_anim_start(&logoAnim);

    //vTaskDelay(400);

    //// progress bar
    //pb = lv_bar_create(lv_scr_act());
    //lv_obj_set_size(pb, 135, 5);
    //lv_bar_set_range(pb, 0, ((HGM_COMPONENT_NULL - 1) * 1000));
    //lv_obj_set_style_anim_time(pb, 70, 0);
    //lv_obj_align(pb, LV_ALIGN_BOTTOM_MID, 0, 20);
    //lv_bar_set_start_value(pb, 0, LV_ANIM_OFF);
    //lv_obj_set_style_bg_color(pb, lv_color_make(0xb5, 0xb5, 0xb5), 0);
    //lv_obj_set_style_bg_color(pb, lv_color_make(0x48, 0x68, 0x17), LV_PART_INDICATOR);
    //lv_anim_t pdAnim;
    //lv_anim_init(&pdAnim);
    //lv_anim_set_var(&pdAnim, pb);
    //lv_anim_set_values(&pdAnim, 20, -30);
    //lv_anim_set_time(&pdAnim, 500);
    //lv_anim_set_exec_cb(&pdAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    //lv_anim_set_path_cb(&pdAnim, lv_anim_path_overshoot);
    //lv_anim_start(&pdAnim);

    //// progress label
    //lv_style_init(&clStyle);
    //lv_style_set_text_font(&clStyle, &k12x8_8px);
    //lv_style_set_text_color(&clStyle, lv_color_make(0xFF, 0xFF, 0xFF));

    //curCheckLabel = lv_label_create(lv_scr_act());
    //lv_label_set_text(curCheckLabel, " ");
    //lv_obj_add_style(curCheckLabel, &clStyle, 0);
    //lv_obj_align(curCheckLabel, LV_ALIGN_CENTER, 0, 20);
    //lv_label_set_recolor(curCheckLabel, true);
    //prevCheckLabel = lv_label_create(lv_scr_act());
    //lv_label_set_text(prevCheckLabel, " ");
    //lv_obj_set_style_opa(prevCheckLabel, LV_OPA_30, 0);
    //lv_obj_add_style(prevCheckLabel, &clStyle, 0);
    //lv_obj_align(prevCheckLabel, LV_ALIGN_CENTER, 0, 10);
    //lv_label_set_recolor(prevCheckLabel, true);

    //vTaskDelay(700);

    // For test
    /*HgmComponent com;
    com.curStatus = true;
    com.waitStatus = true;

    com.type = HGM_COMPONENT_BT;
    this->ComponentControl(&com);
    vTaskDelay(600);
    com.type = HGM_COMPONENT_CONFIG_FILE;
    this->ComponentControl(&com);
    vTaskDelay(700);
    com.type = HGM_COMPONENT_WIFI;
    this->ComponentControl(&com);
    vTaskDelay(800);
    com.type = HGM_COMPONENT_NET_TIME;
    this->ComponentControl(&com);
    vTaskDelay(400);
    com.type = HGM_COMPONENT_WEATHER;
    this->ComponentControl(&com);
    vTaskDelay(900);
    com.type = HGM_COMPONENT_BILIBILI;
    this->ComponentControl(&com);
    vTaskDelay(500);
    com.type = HGM_COMPONENT_DONE;
    this->ComponentControl(&com);
    vTaskDelay(1000);

    this->ComponentInitDone();*/



}

/**
 * @brief Use it to control SetupCheckTask().
 * @param component
 */
void HgmGUI::HgmSetupUI::ComponentControl(HgmComponent* component)
{
    xQueueSend(setupMsgBox, &component, portMAX_DELAY);
}

void HgmGUI::HgmSetupUI::ComponentInitDone()
{
    lv_anim_t barAnim;
    lv_anim_init(&barAnim);
    lv_anim_set_values(&barAnim, -30, 50);
    lv_anim_set_time(&barAnim, 1000);
    lv_anim_set_exec_cb(&barAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&barAnim, lv_anim_path_overshoot);
    lv_anim_set_var(&barAnim, pb);
    lv_anim_start(&barAnim);
    vTaskDelay(100);

    /* label out */
    lv_anim_t checkLabelAnim;
    lv_anim_init(&checkLabelAnim);
    lv_anim_set_values(&checkLabelAnim, 20, 100);
    lv_anim_set_time(&checkLabelAnim, 1000);
    lv_anim_set_exec_cb(&checkLabelAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&checkLabelAnim, lv_anim_path_overshoot);
    lv_anim_set_var(&checkLabelAnim, curCheckLabel);
    lv_anim_start(&checkLabelAnim);
    vTaskDelay(100);

    lv_anim_t checkLabelAnim2;
    lv_anim_init(&checkLabelAnim2);
    lv_anim_set_values(&checkLabelAnim2, 10, 100);
    lv_anim_set_time(&checkLabelAnim2, 1000);
    lv_anim_set_exec_cb(&checkLabelAnim2, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&checkLabelAnim2, lv_anim_path_overshoot);
    lv_anim_set_var(&checkLabelAnim2, prevCheckLabel);
    lv_anim_start(&checkLabelAnim2);
    vTaskDelay(100);

    lv_anim_t logoAnim;
    lv_anim_set_var(&logoAnim, logo);
    lv_anim_set_values(&logoAnim, 25, -32);
    lv_anim_set_time(&logoAnim, 700);
    lv_anim_set_exec_cb(&logoAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&logoAnim, lv_anim_path_overshoot);
    lv_anim_start(&logoAnim);
    vTaskDelay(200);
}

/**
 * @brief Setup check task.
 * @param params
 */
static void SetupCheckTask(void* params)
{
    uint16_t progress = 0;
    HgmComponent* component;

    static String ok = "#486817 ok#";
    static String failed = "#ce0b0b failed#";

    while (true) {
        // Wait components begin
        if (xQueueReceive(setupMsgBox, &component, portMAX_DELAY) != pdPASS)
            continue;

        switch (component->type) {
        case HGM_COMPONENT_BT: {
            prevText = " ";
            curText = "Check BT...";
            break;
        }
        case HGM_COMPONENT_CONFIG_FILE: {
            prevText = curText;
            curText = "Check config...";
            break;
        }
        case HGM_COMPONENT_WIFI: {
            prevText = curText;
            curText = "Check WiFi...";
            break;
        }
        case HGM_COMPONENT_NET_TIME: {
            prevText = curText;
            curText = "Check time...";
            break;
        }
        case HGM_COMPONENT_WEATHER: {
            prevText = curText;
            curText = "Check weather...";
            break;
        }
        case HGM_COMPONENT_BILIBILI: {
            prevText = curText;
            curText = "Check bilibili...";
            break;
        }
        case HGM_COMPONENT_DONE: {
            prevText = curText;
            curText = "Initialized done";
            break;
        }
        default:
            break;
        }
        lv_label_set_text(prevCheckLabel, prevText.c_str());
        lv_label_set_text(curCheckLabel, curText.c_str());
        if (component->type == HGM_COMPONENT_DONE)
            continue;

        // If the curStatus != true, then loop to wait the waitStatus
        // If the waitStatus == true, component initialization is OK
        // If they both are false, then component initialization is failed
        if (!component->curStatus) {
            String tmp = curText + failed;
            lv_label_set_text(curCheckLabel, tmp.c_str());
        }

        // Check the wait status of the component.
        uint16_t timeout = 1000;
        while (!component->waitStatus && --timeout) {
            if ((timeout <= 500) && (timeout % 50 == 0)) {
                String tmp = curText + failed + "(" + String(timeout / 50) + ")";
                lv_label_set_text(curCheckLabel, tmp.c_str());
            }
            vTaskDelay(20);
        }
        if (!component->waitStatus)
            continue;

        vTaskDelay(100);

        progress += (HGM_COMPONENT_NULL - 1) * 1000 / (HGM_COMPONENT_NULL - 1);
        lv_bar_set_value(pb, progress, LV_ANIM_ON);

        curText += ok;
        lv_label_set_text(curCheckLabel, curText.c_str());

    }
}
