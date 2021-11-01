/******************************************************************
 * @file HgmSetupView.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/18 23:18
 * @copyright Copyright (c) 2021/8/18
*******************************************************************/
#include "HgmSetupView.h"
#include "../../LvglSrc/lvgl/lvgl.h"
#include "../../Utils/MsgCenter/MsgCenter.h"
#include "HgmFramework.h"

#include <TJpg_Decoder.h>

using namespace HgmGUI;
using namespace msgmanager;

LV_IMG_DECLARE(HGM_LOGO);
static void SetupCheckTask(void* params);
static HgmSetupView* instance = NULL;

HgmSetupView::HgmSetupView()
{

    instance = this;
    instance->frtos.msgBox = xQueueCreate(1, sizeof(void*));   // Get size of a pointer
    xTaskCreatePinnedToCore(
        SetupCheckTask,
        "SetupCheckTask",
        3072,
        NULL,
        15,
        &instance->frtos.taskHandle,
        1
    );
}

HgmSetupView::~HgmSetupView()
{
    vTaskDelete(instance->frtos.taskHandle);
    vQueueDelete(instance->frtos.msgBox);
    instance = NULL;
}

void HgmGUI::HgmSetupView::begin()
{
    // logo
    instance->widget.logo = lv_img_create(lv_scr_act());
    lv_img_set_src(instance->widget.logo, &HGM_LOGO);
    lv_obj_align(instance->widget.logo, LV_ALIGN_TOP_MID, 0, -32);
    lv_anim_t logoAnim;
    lv_anim_init(&logoAnim);
    lv_anim_set_var(&logoAnim, instance->widget.logo);
    lv_anim_set_values(&logoAnim, -32, 25);
    lv_anim_set_time(&logoAnim, 700);
    lv_anim_set_exec_cb(&logoAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&logoAnim, lv_anim_path_overshoot);
    lv_anim_start(&logoAnim);

    vTaskDelay(400);

    // progress bar
    instance->widget.pb = lv_bar_create(lv_scr_act());
    lv_obj_set_size(instance->widget.pb, 135, 5);
    lv_bar_set_range(instance->widget.pb, 0, ((HGM_COMPONENT_NULL - 2) * 1000));
    lv_obj_set_style_anim_time(instance->widget.pb, 70, 0);
    lv_obj_align(instance->widget.pb, LV_ALIGN_BOTTOM_MID, 0, 20);
    lv_bar_set_start_value(instance->widget.pb, 0, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(instance->widget.pb, lv_color_make(0xb5, 0xb5, 0xb5), 0);
    lv_obj_set_style_bg_color(instance->widget.pb, lv_color_make(0x48, 0x68, 0x17), LV_PART_INDICATOR);
    lv_anim_t pdAnim;
    lv_anim_init(&pdAnim);
    lv_anim_set_var(&pdAnim, instance->widget.pb);
    lv_anim_set_values(&pdAnim, 20, -30);
    lv_anim_set_time(&pdAnim, 500);
    lv_anim_set_exec_cb(&pdAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&pdAnim, lv_anim_path_overshoot);
    lv_anim_start(&pdAnim);

    // progress label
    lv_style_init(&instance->widget.clStyle);
    lv_style_set_text_font(&instance->widget.clStyle, &k12x8_8px);
    lv_style_set_text_color(&instance->widget.clStyle, lv_color_make(0xFF, 0xFF, 0xFF));

    instance->widget.curCheckLabel = lv_label_create(lv_scr_act());
    lv_label_set_text(instance->widget.curCheckLabel, " ");
    lv_obj_add_style(instance->widget.curCheckLabel, &instance->widget.clStyle, 0);
    lv_obj_align(instance->widget.curCheckLabel, LV_ALIGN_CENTER, 0, 20);
    lv_label_set_recolor(instance->widget.curCheckLabel, true);
    instance->widget.prevCheckLabel = lv_label_create(lv_scr_act());
    lv_label_set_text(instance->widget.prevCheckLabel, " ");
    lv_obj_set_style_opa(instance->widget.prevCheckLabel, LV_OPA_30, 0);
    lv_obj_add_style(instance->widget.prevCheckLabel, &instance->widget.clStyle, 0);
    lv_obj_align(instance->widget.prevCheckLabel, LV_ALIGN_CENTER, 0, 10);
    lv_label_set_recolor(instance->widget.prevCheckLabel, true);

    vTaskDelay(700);

    // For test
    /*HgmComponent com;
    com.curStatus = true;
    com.waitStatus = true;

    com.type = HGM_COMPONENT_BT;
    this->componentControl(&com);
    vTaskDelay(600);
    com.type = HGM_COMPONENT_CONFIG_FILE;
    this->componentControl(&com);
    vTaskDelay(700);
    com.type = HGM_COMPONENT_WIFI;
    this->componentControl(&com);
    vTaskDelay(800);
    com.type = HGM_COMPONENT_NET_TIME;
    this->componentControl(&com);
    vTaskDelay(400);
    com.type = HGM_COMPONENT_WEATHER;
    this->componentControl(&com);
    vTaskDelay(900);
    com.type = HGM_COMPONENT_BILIBILI;
    this->componentControl(&com);
    vTaskDelay(500);
    com.type = HGM_COMPONENT_DONE;
    this->componentControl(&com);
    vTaskDelay(1000);

    this->componentInitDone();*/

}

void HgmGUI::HgmSetupView::end()
{
    this->componentInitDone();
}

/**
 * @brief Use it to control SetupCheckTask().
 * @param component
 */
void HgmGUI::HgmSetupView::componentControl(HgmComponent* component)
{
    xQueueSend(instance->frtos.msgBox, &component, portMAX_DELAY);
}

void HgmGUI::HgmSetupView::componentInitDone()
{
    lv_anim_t barAnim;
    lv_anim_init(&barAnim);
    lv_anim_set_values(&barAnim, -30, 50);
    lv_anim_set_time(&barAnim, 700);
    lv_anim_set_exec_cb(&barAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&barAnim, lv_anim_path_overshoot);
    lv_anim_set_var(&barAnim, instance->widget.pb);

    /* label out */
    lv_anim_t checkLabelAnim;
    lv_anim_init(&checkLabelAnim);
    lv_anim_set_values(&checkLabelAnim, 20, 100);
    lv_anim_set_time(&checkLabelAnim, 600);
    lv_anim_set_exec_cb(&checkLabelAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&checkLabelAnim, lv_anim_path_overshoot);
    lv_anim_set_var(&checkLabelAnim, instance->widget.curCheckLabel);

    lv_anim_t checkLabelAnim2;
    lv_anim_init(&checkLabelAnim2);
    lv_anim_set_values(&checkLabelAnim2, 10, 100);
    lv_anim_set_time(&checkLabelAnim2, 500);
    lv_anim_set_exec_cb(&checkLabelAnim2, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&checkLabelAnim2, lv_anim_path_overshoot);
    lv_anim_set_var(&checkLabelAnim2, instance->widget.prevCheckLabel);

    lv_anim_t logoAnim;
    lv_anim_set_var(&logoAnim, instance->widget.logo);
    lv_anim_set_values(&logoAnim, lv_obj_get_y_aligned(instance->widget.logo), -32);
    lv_anim_set_time(&logoAnim, 700);
    lv_anim_set_exec_cb(&logoAnim, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&logoAnim, lv_anim_path_overshoot);

    // anim time line
    lv_anim_timeline_t* at = lv_anim_timeline_create();
    lv_anim_timeline_add(at, 0, &barAnim);
    lv_anim_timeline_add(at, 100, &checkLabelAnim);
    lv_anim_timeline_add(at, 200, &checkLabelAnim2);
    lv_anim_timeline_add(at, 300, &logoAnim);

    vTaskDelay(lv_anim_timeline_start(at) + 500);

    lv_obj_del(instance->widget.logo);
    lv_obj_del(instance->widget.prevCheckLabel);
    lv_obj_del(instance->widget.curCheckLabel);
    lv_obj_del(instance->widget.pb);
}


/**
 * @brief Setup check task.
 * @param params
 */
static void SetupCheckTask(void* params)
{
    uint16_t progress = 0;
    HgmComponent* component;

    String ok = "#486817 ok#";
    String failed = "#ce0b0b failed#";

    while (true) {
        // Wait components begin
        if (xQueueReceive(instance->frtos.msgBox, &component, portMAX_DELAY) != pdPASS)
            continue;

        switch (component->type) {
        case HGM_COMPONENT_BT: {
            instance->prevText = " ";
            instance->curText = "Check BT...";
            break;
        }
        case HGM_COMPONENT_SPIFFS: {
            instance->prevText = instance->curText;
            instance->curText = "Check spiffs...";
            break;
        }
        case HGM_COMPONENT_WIFI: {
            instance->prevText = instance->curText;
            instance->curText = "Check WiFi...";
            break;
        }
        case HGM_COMPONENT_NET_TIME: {
            instance->prevText = instance->curText;
            instance->curText = "Check time...";
            break;
        }
        case HGM_COMPONENT_WEATHER: {
            instance->prevText = instance->curText;
            instance->curText = "Check weather...";
            break;
        }
        case HGM_COMPONENT_BILIBILI: {
            instance->prevText = instance->curText;
            instance->curText = "Check bilibili...";
            break;
        }
        case HGM_COMPONENT_DONE: {
            instance->prevText = instance->curText;
            instance->curText = "Initialized done";
            break;
        }
        default:
            break;
        }
        lv_label_set_text(instance->widget.prevCheckLabel, instance->prevText.c_str());
        lv_label_set_text(instance->widget.curCheckLabel, instance->curText.c_str());
        if (component->type == HGM_COMPONENT_DONE)
            continue;

        // If the curStatus != true, then loop to wait the waitStatus
        // If the waitStatus == true, component initialization is OK
        // If they both are false, then component initialization is failed
        if (!component->curStatus) {
            String tmp = instance->curText + failed;
            lv_label_set_text(instance->widget.curCheckLabel, tmp.c_str());
        }

        // Check the wait status of the component.
        uint16_t timeout = 1000;
        while (!component->waitStatus && --timeout) {
            if ((timeout <= 500) && (timeout % 50 == 0)) {
                String tmp = instance->curText + failed + "(" + String(timeout / 50) + ")";
                lv_label_set_text(instance->widget.curCheckLabel, tmp.c_str());
            }
            vTaskDelay(20);
        }
        if (!component->waitStatus)
            continue;

        vTaskDelay(100);

        progress += (HGM_COMPONENT_NULL - 2) * 1000 / (HGM_COMPONENT_NULL - 2);
        lv_bar_set_value(instance->widget.pb, progress, LV_ANIM_ON);

        instance->curText += ok;
        lv_label_set_text(instance->widget.curCheckLabel, instance->curText.c_str());

    }
}
