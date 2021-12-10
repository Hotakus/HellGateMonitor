/******************************************************************
 * @file HgmSRView.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/12/1 10:57
 * @copyright Copyright (c) 2021/12/1
*******************************************************************/
#include "HgmSR.h"
#include "HgmSRView.h"
#include "../../../HgmApp/HgmWiFi/HgmWiFi.h"
#include "../../../HgmApp/TimeInfo/TimeInfo.h"
#include "../../../HgmApp/HardwareInfoRecv/HardwareRequest.h"

#include "../../../Utils/SPIFFSUtil/SPIFFSUtil.h"

using namespace HgmGUI;
using namespace HgmApplication;
using namespace spiffsutil;

extern lv_group_t* keypad_group;

LV_IMG_DECLARE(frame_left);
LV_IMG_DECLARE(frame_right);
LV_IMG_DECLARE(frame_mid);

LV_IMG_DECLARE(bat_100);
LV_IMG_DECLARE(bat_75);
LV_IMG_DECLARE(bat_50);
LV_IMG_DECLARE(bat_25);
LV_IMG_DECLARE(bat_10);
LV_IMG_DECLARE(bat_null);

LV_IMG_DECLARE(signal_0);
LV_IMG_DECLARE(signal_1);
LV_IMG_DECLARE(signal_2);
LV_IMG_DECLARE(signal_3);
LV_IMG_DECLARE(signal_4);
LV_IMG_DECLARE(signal_5);

LV_FONT_DECLARE(fangpx_10px);
LV_FONT_DECLARE(k12x8_6px);
LV_FONT_DECLARE(k12x8_7px);
LV_FONT_DECLARE(k12x8_8px);
LV_FONT_DECLARE(k12x8_10px);
LV_FONT_DECLARE(k12x8_14px_time);
LV_FONT_DECLARE(k12x8_16px_time);
LV_FONT_DECLARE(k12x8_24px_time);

LV_IMG_DECLARE(next_btn2_pr);
LV_IMG_DECLARE(next_btn2_rel);
LV_IMG_DECLARE(promt_btn_rel);
LV_IMG_DECLARE(promt_btn_checked);

LV_IMG_DECLARE(prompt_frame_left);
LV_IMG_DECLARE(prompt_frame_mid);
LV_IMG_DECLARE(prompt_frame_right);

static HgmSRView* instance;

HgmGUI::HgmSRView::HgmSRView()
{
    instance = this;
}

HgmGUI::HgmSRView::~HgmSRView()
{
    instance = nullptr;
}

static void fade(void* obj, int32_t val)
{
    lv_obj_set_style_opa((lv_obj_t*)obj, val, 0);
}

static void ctl_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_current_target(e);

    if (obj == instance->widget.prompt.btn) {
        instance->widget.prompt.value = ~(instance->widget.prompt.value);
        if (instance->widget.prompt.value) {
            lv_label_set_text_fmt(instance->widget.prompt.frame.ip_label, "#ffffff IP: %s#", WiFi.localIP().toString().c_str());
            lv_label_set_text_fmt(instance->widget.prompt.frame.port_label, "#ffffff 端口: %d#", SERVER_DEFAULT_PORT);

            lv_anim_set_values(&instance->widget.prompt.fa, LV_OPA_0, LV_OPA_80);
            lv_anim_set_time(&instance->widget.prompt.fa, 200);
            lv_anim_set_exec_cb(&instance->widget.prompt.fa, (lv_anim_exec_xcb_t)fade);
            lv_anim_set_path_cb(&instance->widget.prompt.fa, lv_anim_path_ease_in_out);
            lv_anim_set_var(&instance->widget.prompt.fa, instance->widget.prompt.frame.self);
            lv_anim_start(&instance->widget.prompt.fa);
        } else {
            lv_anim_set_values(&instance->widget.prompt.fa, LV_OPA_80, LV_OPA_0);
            lv_anim_set_time(&instance->widget.prompt.fa, 200);
            lv_anim_set_exec_cb(&instance->widget.prompt.fa, (lv_anim_exec_xcb_t)fade);
            lv_anim_set_path_cb(&instance->widget.prompt.fa, lv_anim_path_ease_in_out);
            lv_anim_set_var(&instance->widget.prompt.fa, instance->widget.prompt.frame.self);
            lv_anim_start(&instance->widget.prompt.fa);
        }
    } else {
        // TODO: menu
        HgmFramework::getInstance()->changeGUI("HgmMonitor");
    }
}


static lv_timer_t* showFpsTimer = NULL;
static void show_fps(lv_timer_t* timer)
{
    uint32_t fps = lv_refr_get_fps_avg();
    //lv_label_set_text_fmt(instance->widget.fps_label, "#486817 %02d#", fps);
    lv_label_set_text_fmt(instance->widget.fps_label, "#ffffff %02d#", fps);
}


void HgmGUI::HgmSRView::begin()
{
    frameCreate();
    widgetCreate();
    animCreate();

    showFpsTimer = lv_timer_create(show_fps, 1000, NULL);

    //lv_event_send(instance->widget.prompt.btn, LV_EVENT_CLICKED, NULL);
}

void HgmGUI::HgmSRView::end()
{
    lv_timer_del(showFpsTimer);

    lv_group_remove_all_objs(widget.group);

    // if (instance->widget.prompt.value) {
    //     lv_event_send(instance->widget.prompt.btn, LV_EVENT_CLICKED, NULL);
    //     vTaskDelay(300);
    // }

    Serial.println("HgmSRView::begin() ----------------------------------------- 05");
    // TODO: Destroy
    widgetDestroy();
    Serial.println("HgmSRView::begin() ----------------------------------------- 06");
    animDestroy();
    Serial.println("HgmSRView::begin() ----------------------------------------- 07");
    frameDestroy();
    Serial.println("HgmSRView::begin() ----------------------------------------- 08");
}


void HgmGUI::HgmSRView::frameCreate()
{

}

static void prompt_create()
{
    lv_anim_init(&instance->widget.prompt.fa);
    instance->widget.prompt.value = 0;

    // prompt frame
    instance->widget.prompt.frame.self = lv_imgbtn_create(lv_scr_act());
    lv_obj_set_width(instance->widget.prompt.frame.self, 200);
    lv_obj_set_style_opa(instance->widget.prompt.frame.self, LV_OPA_70, 0);
    lv_obj_align(instance->widget.prompt.frame.self, LV_ALIGN_CENTER, 0, 0);
    // lv_img_set_src(instance->widget.prompt.frame.self, &prompt_frame);
    lv_imgbtn_set_src(instance->widget.prompt.frame.self, LV_IMGBTN_STATE_RELEASED, &prompt_frame_left, &prompt_frame_mid, &prompt_frame_right);

    instance->widget.prompt.frame.conn_status = lv_label_create(instance->widget.prompt.frame.self);
    lv_obj_set_style_text_font(instance->widget.prompt.frame.conn_status, &fangpx_10px, 0);
    lv_label_set_recolor(instance->widget.prompt.frame.conn_status, true);
    lv_label_set_text_fmt(instance->widget.prompt.frame.conn_status, "#ffffff 无数据源#");
    lv_obj_align(instance->widget.prompt.frame.conn_status, LV_ALIGN_TOP_MID, 0, 10);

    instance->widget.prompt.frame.ip_label = lv_label_create(instance->widget.prompt.frame.self);
    lv_obj_set_style_text_font(instance->widget.prompt.frame.ip_label, &fangpx_10px, 0);
    lv_label_set_recolor(instance->widget.prompt.frame.ip_label, true);
    lv_obj_set_style_text_align(instance->widget.prompt.frame.ip_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text_fmt(instance->widget.prompt.frame.ip_label, "#ffffff IP: 192.169.223.233#");
    lv_obj_align_to(instance->widget.prompt.frame.ip_label, instance->widget.prompt.frame.conn_status, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);

    instance->widget.prompt.frame.port_label = lv_label_create(instance->widget.prompt.frame.self);
    lv_obj_set_style_text_font(instance->widget.prompt.frame.port_label, &fangpx_10px, 0);
    lv_label_set_recolor(instance->widget.prompt.frame.port_label, true);
    lv_obj_set_style_text_align(instance->widget.prompt.frame.port_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text_fmt(instance->widget.prompt.frame.port_label, "#ffffff 端口: 20#");
    lv_obj_align_to(instance->widget.prompt.frame.port_label, instance->widget.prompt.frame.ip_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);
}

void HgmGUI::HgmSRView::widgetCreate()
{
    widget.img.self = lv_img_create(lv_scr_act());
    lv_obj_set_size(widget.img.self, 240, 135);
    lv_obj_align(widget.img.self, LV_ALIGN_TOP_LEFT, 0, 0);

    String path = String("/") + String("sr_test.png");
    instance->widget.img.buf = (uint8_t*)hotakusAlloc(sizeof(uint8_t) * (Sfu::fileSize(path) + 1024));
    size_t icon_size = Sfu::read(path, instance->widget.img.buf);

    instance->widget.img.dsc.data_size = icon_size;
    instance->widget.img.dsc.header.always_zero = 0;
    instance->widget.img.dsc.header.w = 240;
    instance->widget.img.dsc.header.h = 135;
    instance->widget.img.dsc.header.cf = LV_IMG_CF_RAW_ALPHA;
    instance->widget.img.dsc.data = instance->widget.img.buf;
    lv_img_set_src(widget.img.self, &instance->widget.img.dsc);

    widget.fps_label = lv_label_create(widget.img.self);
    lv_obj_align(widget.fps_label, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_obj_set_style_text_font(widget.fps_label, &k12x8_10px, 0);
    lv_label_set_recolor(widget.fps_label, true);
    //lv_label_set_text_fmt(widget.fps_label, "#486817 --#", 0);
    lv_label_set_text_fmt(widget.fps_label, "#ffffff --#", 0);

    //prompt_create();

    widget.group = keypad_group;
}

void HgmGUI::HgmSRView::animCreate()
{

}



void HgmGUI::HgmSRView::animDestroy()
{
}

void HgmGUI::HgmSRView::widgetDestroy()
{
}

void HgmGUI::HgmSRView::frameDestroy()
{
}


void HgmGUI::HgmSRView::update_status(bool ds)
{
    lv_label_set_text_fmt(instance->widget.prompt.frame.conn_status, (ds ? "#ffffff 数据源已连接#" : "#ffffff 无数据源#"));
}
