/******************************************************************
 * @file HgmMonitorView.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/11/7 20:37
 * @copyright Copyright (c) 2021/11/7
*******************************************************************/
#include "../../../HgmApp/HgmWiFi/HgmWiFi.h"
#include "../../../HgmApp/TimeInfo/TimeInfo.h"
#include "../../../HgmApp/HardwareInfoRecv/HardwareRequest.h"
#include "HgmMonitorView.h"
#include "HgmMonitor.h"
#include "../../../Utils/SPIFFSUtil/SPIFFSUtil.h"

using namespace HgmGUI;
using namespace HgmApplication;
using namespace spiffsutil;

extern TimeInfo ti;
extern lv_group_t* keypad_group;

LV_IMG_DECLARE(mem_icon);
LV_IMG_DECLARE(vc_icon);
LV_IMG_DECLARE(cpu_icon);
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

static HgmMonitorView* instance;

HgmGUI::HgmMonitorView::HgmMonitorView()
{
    instance = this;
}

HgmGUI::HgmMonitorView::~HgmMonitorView()
{
    instance = nullptr;
}

lv_obj_t* HgmMonitorView::frame(HgmHardwarePosition pos)
{
    switch (pos)
    {
    case HGM_LEFT_TOP:
        return widget.frame.lt;
    case HGM_LEFT_BOTTOM:
        return widget.frame.lb;
    case HGM_RIGHT_TOP:
        return widget.frame.rt;
    case HGM_RIGHT_BOTTOM:
        return widget.frame.rb;
    default:
        return NULL;
    }
}

void HgmMonitorView::cpu_widget_create(HgmHardwarePosition pos)
{
    lv_obj_t* f = frame(pos);

    // Top left frame
    widget.cpu.label.name = lv_label_create(f);
    lv_obj_set_style_text_font(widget.cpu.label.name, &k12x8_7px, 0);
    lv_obj_set_width(widget.cpu.label.name, 90);
    lv_obj_align(widget.cpu.label.name, LV_ALIGN_TOP_MID, 0, 4);
    lv_label_set_recolor(widget.cpu.label.name, true);
    lv_label_set_long_mode(widget.cpu.label.name, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text_fmt(widget.cpu.label.name, "-----"); // Intel Core i7-8700
    lv_obj_set_style_anim_speed(widget.cpu.label.name, 15, 0);

    widget.cpu.label.power = lv_label_create(f);
    lv_obj_set_style_text_font(widget.cpu.label.power, &k12x8_7px, 0);
    lv_obj_align_to(widget.cpu.label.power, widget.cpu.label.name, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.cpu.label.power, true);
    lv_label_set_text_fmt(widget.cpu.label.power, "--W/--W", 0);

    widget.cpu.label.temp = lv_label_create(f);
    lv_obj_set_style_text_font(widget.cpu.label.temp, &k12x8_7px, 0);
    lv_obj_align_to(widget.cpu.label.temp, widget.cpu.label.power, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.cpu.label.temp, true);
    lv_label_set_text_fmt(widget.cpu.label.temp, "---℃", 0);

    widget.cpu.label.usage = lv_label_create(f);
    lv_obj_set_style_text_font(widget.cpu.label.usage, &k12x8_7px, 0);
    lv_obj_align_to(widget.cpu.label.usage, widget.cpu.label.temp, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.cpu.label.usage, true);
    lv_label_set_text_fmt(widget.cpu.label.usage, "---%%", 0);

    widget.cpu.bar.temp = lv_bar_create(f);
    lv_obj_set_size(widget.cpu.bar.temp, 40, 8);
    lv_bar_set_range(widget.cpu.bar.temp, 0, 100);
    lv_bar_set_value(widget.cpu.bar.temp, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.cpu.bar.temp, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.cpu.bar.temp, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.cpu.bar.temp, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.cpu.bar.temp, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(widget.cpu.bar.temp, widget.cpu.label.temp, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    widget.cpu.bar.usage = lv_bar_create(f);
    lv_obj_set_size(widget.cpu.bar.usage, 40, 8);
    lv_bar_set_range(widget.cpu.bar.usage, 0, 100);
    lv_bar_set_value(widget.cpu.bar.usage, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.cpu.bar.usage, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.cpu.bar.usage, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.cpu.bar.usage, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.cpu.bar.usage, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(widget.cpu.bar.usage, widget.cpu.label.usage, LV_ALIGN_OUT_RIGHT_MID, 11, 0);

}

void HgmMonitorView::gpu_widget_create(HgmHardwarePosition pos)
{
    lv_obj_t* f = frame(pos);

    // Top left frame
    widget.gpu.label.name = lv_label_create(f);
    lv_obj_set_style_text_font(widget.gpu.label.name, &k12x8_7px, 0);
    lv_obj_set_width(widget.gpu.label.name, 90);
    lv_obj_align(widget.gpu.label.name, LV_ALIGN_TOP_MID, 0, 4);
    lv_label_set_recolor(widget.gpu.label.name, true);
    lv_label_set_long_mode(widget.gpu.label.name, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text_fmt(widget.gpu.label.name, "-----");
    lv_obj_set_style_anim_speed(widget.gpu.label.name, 15, 0);

    widget.gpu.label.power = lv_label_create(f);
    lv_obj_set_style_text_font(widget.gpu.label.power, &k12x8_7px, 0);
    lv_obj_align_to(widget.gpu.label.power, widget.gpu.label.name, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.gpu.label.power, true);
    lv_label_set_text_fmt(widget.gpu.label.power, "--W/--W", 0);

    widget.gpu.label.temp = lv_label_create(f);
    lv_obj_set_style_text_font(widget.gpu.label.temp, &k12x8_7px, 0);
    lv_obj_align_to(widget.gpu.label.temp, widget.gpu.label.power, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.gpu.label.temp, true);
    lv_label_set_text_fmt(widget.gpu.label.temp, "---℃", 0);

    widget.gpu.label.usage = lv_label_create(f);
    lv_obj_set_style_text_font(widget.gpu.label.usage, &k12x8_7px, 0);
    lv_obj_align_to(widget.gpu.label.usage, widget.gpu.label.temp, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.gpu.label.usage, true);
    lv_label_set_text_fmt(widget.gpu.label.usage, "---%%", 0);

    widget.gpu.bar.temp = lv_bar_create(f);
    lv_obj_set_size(widget.gpu.bar.temp, 40, 8);
    lv_bar_set_range(widget.gpu.bar.temp, 0, 100);
    lv_bar_set_value(widget.gpu.bar.temp, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.gpu.bar.temp, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.gpu.bar.temp, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.gpu.bar.temp, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.gpu.bar.temp, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(widget.gpu.bar.temp, widget.gpu.label.temp, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    widget.gpu.bar.usage = lv_bar_create(f);
    lv_obj_set_size(widget.gpu.bar.usage, 40, 8);
    lv_bar_set_range(widget.gpu.bar.usage, 0, 100);
    lv_bar_set_value(widget.gpu.bar.usage, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.gpu.bar.usage, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.gpu.bar.usage, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.gpu.bar.usage, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.gpu.bar.usage, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(widget.gpu.bar.usage, widget.gpu.label.usage, LV_ALIGN_OUT_RIGHT_MID, 11, 0);
}

void HgmMonitorView::mem_widget_create(HgmHardwarePosition pos)
{
    lv_obj_t* f = frame(pos);

    widget.mem.label.name = lv_label_create(f);
    lv_obj_set_style_text_font(widget.mem.label.name, &k12x8_7px, 0);
    //lv_obj_set_width(widget.mem.label.name, 90);
    lv_obj_align(widget.mem.label.name, LV_ALIGN_TOP_LEFT, 5, 3);
    lv_label_set_recolor(widget.mem.label.name, true);
    lv_label_set_long_mode(widget.mem.label.name, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text_fmt(widget.mem.label.name, "Memory");

    widget.mem.label.percent = lv_label_create(f);
    lv_obj_set_style_text_font(widget.mem.label.percent, &k12x8_7px, 0);
    lv_label_set_recolor(widget.mem.label.percent, true);
    lv_label_set_text_fmt(widget.mem.label.percent, "Load:----", 0);
    lv_obj_align_to(widget.mem.label.percent, widget.mem.label.name, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 1);
    //lv_obj_align_to(widget.mem.label.percent, widget.mem.bar.usage, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    widget.mem.bar.usage = lv_bar_create(f);
    lv_obj_set_size(widget.mem.bar.usage, 30, 8);
    lv_bar_set_range(widget.mem.bar.usage, 0, 100);
    lv_bar_set_value(widget.mem.bar.usage, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.mem.bar.usage, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.mem.bar.usage, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.mem.bar.usage, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.mem.bar.usage, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    //lv_obj_align_to(widget.mem.bar.usage, widget.mem.label.name, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);
    //lv_obj_align_to(widget.mem.bar.usage, widget.mem.label.name, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
    lv_obj_align(widget.mem.bar.usage, LV_ALIGN_TOP_RIGHT, -8, 6);

    widget.mem.label.free = lv_label_create(f);
    lv_obj_set_style_text_font(widget.mem.label.free, &k12x8_7px, 0);
    lv_label_set_recolor(widget.mem.label.free, true);
    lv_label_set_text_fmt(widget.mem.label.free, "Free:--GB", 0);
    lv_obj_align_to(widget.mem.label.free, widget.mem.label.percent, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 1);

    widget.mem.label.used = lv_label_create(f);
    lv_obj_set_style_text_font(widget.mem.label.used, &k12x8_7px, 0);
    lv_label_set_recolor(widget.mem.label.used, true);
    lv_label_set_text_fmt(widget.mem.label.used, "Used:--GB", 0);
    lv_obj_align_to(widget.mem.label.used, widget.mem.label.free, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    // widget.mem.icon = lv_img_create(f);
    // lv_obj_align(widget.mem.icon, LV_ALIGN_TOP_RIGHT, -6, 5);
    // lv_img_set_src(widget.mem.icon, &mem_icon);
}

void HgmMonitorView::network_widget_create(HgmHardwarePosition pos)
{
    lv_obj_t* f = frame(pos);

    widget.network.label.name = lv_label_create(f);
    lv_obj_set_style_text_font(widget.network.label.name, &k12x8_7px, 0);
    lv_obj_set_width(widget.network.label.name, 90);
    lv_obj_align(widget.network.label.name, LV_ALIGN_TOP_MID, 0, 4);
    lv_label_set_recolor(widget.network.label.name, true);
    lv_label_set_long_mode(widget.network.label.name, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text_fmt(widget.network.label.name, "Network");
    lv_obj_set_style_anim_speed(widget.network.label.name, 20, 0);

    widget.network.label.percent = lv_label_create(f);
    lv_obj_set_style_text_font(widget.network.label.percent, &k12x8_7px, 0);
    lv_label_set_recolor(widget.network.label.percent, true);
    lv_label_set_text_fmt(widget.network.label.percent, "--%%", 0);
    lv_obj_align_to(widget.network.label.percent, widget.network.label.name, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    widget.network.bar.usage = lv_bar_create(f);
    lv_obj_set_size(widget.network.bar.usage, 20, 8);
    lv_bar_set_range(widget.network.bar.usage, 0, 100);
    lv_bar_set_value(widget.network.bar.usage, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.network.bar.usage, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.network.bar.usage, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.network.bar.usage, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.network.bar.usage, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    //lv_obj_align_to(widget.network.bar.usage, widget.network.label.percent, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
    lv_obj_align(widget.network.bar.usage, LV_ALIGN_TOP_RIGHT, -10, 6);

    widget.network.label.upload = lv_label_create(f);
    lv_obj_set_style_text_font(widget.network.label.upload, &k12x8_7px, 0);
    lv_label_set_recolor(widget.network.label.upload, true);
    lv_label_set_text_fmt(widget.network.label.upload, "↑---B/S", 0);
    lv_obj_align_to(widget.network.label.upload, widget.network.label.percent, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 1);

    widget.network.label.download = lv_label_create(f);
    lv_obj_set_style_text_font(widget.network.label.download, &k12x8_7px, 0);
    lv_label_set_recolor(widget.network.label.download, true);
    lv_label_set_text_fmt(widget.network.label.download, "↓---B/S", 0);
    lv_obj_align_to(widget.network.label.download, widget.network.label.upload, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
}

static void fade(void* obj, int32_t val)
{
    lv_obj_set_style_opa((lv_obj_t*)obj, val, 0);
}

static void ctl_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_current_target(e);

    if (obj == instance->widget.status_bar.prompt.btn) {
        instance->widget.status_bar.prompt.value = ~(instance->widget.status_bar.prompt.value);
        if (instance->widget.status_bar.prompt.value) {
            lv_label_set_text_fmt(instance->widget.status_bar.prompt.frame.ip_label, "#ffffff IP: %s#", WiFi.localIP().toString().c_str());
            lv_label_set_text_fmt(instance->widget.status_bar.prompt.frame.port_label, "#ffffff 端口: %d#", SERVER_DEFAULT_PORT);

            lv_anim_set_values(&instance->widget.status_bar.prompt.fa, LV_OPA_0, LV_OPA_80);
            lv_anim_set_time(&instance->widget.status_bar.prompt.fa, 200);
            lv_anim_set_exec_cb(&instance->widget.status_bar.prompt.fa, (lv_anim_exec_xcb_t)fade);
            lv_anim_set_path_cb(&instance->widget.status_bar.prompt.fa, lv_anim_path_ease_in_out);
            lv_anim_set_var(&instance->widget.status_bar.prompt.fa, instance->widget.status_bar.prompt.frame.self);
            lv_anim_start(&instance->widget.status_bar.prompt.fa);
        } else {
            lv_anim_set_values(&instance->widget.status_bar.prompt.fa, LV_OPA_80, LV_OPA_0);
            lv_anim_set_time(&instance->widget.status_bar.prompt.fa, 200);
            lv_anim_set_exec_cb(&instance->widget.status_bar.prompt.fa, (lv_anim_exec_xcb_t)fade);
            lv_anim_set_path_cb(&instance->widget.status_bar.prompt.fa, lv_anim_path_ease_in_out);
            lv_anim_set_var(&instance->widget.status_bar.prompt.fa, instance->widget.status_bar.prompt.frame.self);
            lv_anim_start(&instance->widget.status_bar.prompt.fa);
        }
    } else {
        HgmFramework::getInstance()->changeGUI("HgmTw");
    }

}

void HgmGUI::HgmMonitorView::status_bar_create()
{
    // TODO: Check battery
    widget.status_bar.battery.icon = lv_img_create(widget.status_bar.bg);
    lv_obj_align(widget.status_bar.battery.icon, LV_ALIGN_TOP_LEFT, 1, 5);
    lv_img_set_src(widget.status_bar.battery.icon, &bat_50);

    widget.status_bar.signal.icon = lv_img_create(widget.status_bar.bg);
    lv_obj_align(widget.status_bar.signal.icon, LV_ALIGN_TOP_MID, 0, 25);
    lv_img_set_src(widget.status_bar.signal.icon, &signal_2);

    widget.status_bar.time_label = lv_label_create(widget.status_bar.bg);
    lv_obj_set_style_text_font(widget.status_bar.time_label, &k12x8_7px, 0);
    lv_obj_align_to(widget.status_bar.time_label, widget.status_bar.signal.icon, LV_ALIGN_OUT_BOTTOM_LEFT, 1, 4);
    lv_label_set_recolor(widget.status_bar.time_label, true);
    lv_label_set_text_fmt(widget.status_bar.time_label, "#c5b8b0 --#\n#c5b8b0 --#", 0);

    lv_style_init(&widget.style_pr);
    lv_style_set_img_recolor_opa(&widget.style_pr, LV_OPA_30);
    lv_style_set_img_recolor(&widget.style_pr, lv_color_black());

    widget.status_bar.next_btn = lv_imgbtn_create(widget.status_bar.bg);
    lv_obj_set_size(widget.status_bar.next_btn, 13, 20);
    lv_obj_add_style(widget.status_bar.next_btn, &widget.style_pr, LV_STATE_PRESSED);
    lv_imgbtn_set_src(widget.status_bar.next_btn, LV_IMGBTN_STATE_PRESSED, &next_btn2_pr, 0, 0);
    lv_imgbtn_set_src(widget.status_bar.next_btn, LV_IMGBTN_STATE_RELEASED, &next_btn2_rel, 0, 0);
    lv_imgbtn_set_src(widget.status_bar.next_btn, LV_IMGBTN_STATE_CHECKED_RELEASED, &next_btn2_pr, 0, 0);
    lv_imgbtn_set_src(widget.status_bar.next_btn, LV_IMGBTN_STATE_CHECKED_PRESSED, &next_btn2_pr, 0, 0);
    lv_obj_align(widget.status_bar.next_btn, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_event_cb(widget.status_bar.next_btn, ctl_event_cb, LV_EVENT_CLICKED, NULL);

    lv_anim_init(&widget.status_bar.prompt.fa);
    widget.status_bar.prompt.value = 0;
    widget.status_bar.prompt.btn = lv_imgbtn_create(widget.status_bar.bg);
    lv_obj_set_size(widget.status_bar.prompt.btn, 20, 20);
    lv_obj_add_style(widget.status_bar.prompt.btn, &widget.style_pr, LV_STATE_PRESSED);
    lv_imgbtn_set_src(widget.status_bar.prompt.btn, LV_IMGBTN_STATE_PRESSED, &promt_btn_checked, 0, 0);
    lv_imgbtn_set_src(widget.status_bar.prompt.btn, LV_IMGBTN_STATE_RELEASED, &promt_btn_rel, 0, 0);
    lv_imgbtn_set_src(widget.status_bar.prompt.btn, LV_IMGBTN_STATE_CHECKED_RELEASED, &promt_btn_checked, 0, 0);
    lv_imgbtn_set_src(widget.status_bar.prompt.btn, LV_IMGBTN_STATE_CHECKED_PRESSED, &promt_btn_checked, 0, 0);
    lv_obj_align_to(widget.status_bar.prompt.btn, widget.status_bar.next_btn, LV_ALIGN_OUT_TOP_MID, 0, -5);
    lv_obj_add_event_cb(widget.status_bar.prompt.btn, ctl_event_cb, LV_EVENT_CLICKED, NULL);

    // prompt frame
    widget.status_bar.prompt.frame.self = lv_imgbtn_create(lv_scr_act());
    lv_obj_set_width(widget.status_bar.prompt.frame.self, 200);
    lv_obj_set_style_opa(widget.status_bar.prompt.frame.self, LV_OPA_0, 0);
    lv_obj_align(widget.status_bar.prompt.frame.self, LV_ALIGN_CENTER, 0, 0);
    // lv_img_set_src(widget.status_bar.prompt.frame.self, &prompt_frame);
    lv_imgbtn_set_src(widget.status_bar.prompt.frame.self, LV_IMGBTN_STATE_RELEASED, &prompt_frame_left, &prompt_frame_mid, &prompt_frame_right);

    widget.status_bar.prompt.frame.conn_status = lv_label_create(widget.status_bar.prompt.frame.self);
    lv_obj_set_style_text_font(widget.status_bar.prompt.frame.conn_status, &fangpx_10px, 0);
    lv_label_set_recolor(widget.status_bar.prompt.frame.conn_status, true);
    lv_label_set_text_fmt(widget.status_bar.prompt.frame.conn_status, "#ffffff 数据源验证失败#");
    lv_obj_align(widget.status_bar.prompt.frame.conn_status, LV_ALIGN_TOP_MID, 0, 10);

    widget.status_bar.prompt.frame.ip_label = lv_label_create(widget.status_bar.prompt.frame.self);
    lv_obj_set_style_text_font(widget.status_bar.prompt.frame.ip_label, &fangpx_10px, 0);
    lv_label_set_recolor(widget.status_bar.prompt.frame.ip_label, true);
    lv_obj_set_style_text_align(widget.status_bar.prompt.frame.ip_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text_fmt(widget.status_bar.prompt.frame.ip_label, "#ffffff IP: 192.169.223.233#");
    lv_obj_align_to(widget.status_bar.prompt.frame.ip_label, widget.status_bar.prompt.frame.conn_status, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);

    widget.status_bar.prompt.frame.port_label = lv_label_create(widget.status_bar.prompt.frame.self);
    lv_obj_set_style_text_font(widget.status_bar.prompt.frame.port_label, &fangpx_10px, 0);
    lv_label_set_recolor(widget.status_bar.prompt.frame.port_label, true);
    lv_obj_set_style_text_align(widget.status_bar.prompt.frame.port_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text_fmt(widget.status_bar.prompt.frame.port_label, "#ffffff 端口: 20#");
    lv_obj_align_to(widget.status_bar.prompt.frame.port_label, widget.status_bar.prompt.frame.ip_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);
}

void HgmGUI::HgmMonitorView::frameCreate()
{
    /* frame */
    widget.frame.lt = lv_imgbtn_create(lv_scr_act());
    lv_imgbtn_set_src(widget.frame.lt, LV_IMGBTN_STATE_RELEASED, &frame_left, &frame_mid, &frame_right);
    lv_obj_align(widget.frame.lt, LV_ALIGN_TOP_LEFT, 5 + 240, 5);
    lv_obj_set_width(widget.frame.lt, 100);

    widget.frame.lb = lv_imgbtn_create(lv_scr_act());
    lv_imgbtn_set_src(widget.frame.lb, LV_IMGBTN_STATE_RELEASED, &frame_left, &frame_mid, &frame_right);
    lv_obj_align(widget.frame.lb, LV_ALIGN_TOP_LEFT, 5 + 240, 70);
    lv_obj_set_width(widget.frame.lb, 100);

    widget.frame.rt = lv_imgbtn_create(lv_scr_act());
    lv_imgbtn_set_src(widget.frame.rt, LV_IMGBTN_STATE_RELEASED, &frame_left, &frame_mid, &frame_right);
    lv_obj_align(widget.frame.rt, LV_ALIGN_TOP_LEFT, 110 + 240, 5);
    lv_obj_set_width(widget.frame.rt, 100);

    widget.frame.rb = lv_imgbtn_create(lv_scr_act());
    lv_imgbtn_set_src(widget.frame.rb, LV_IMGBTN_STATE_RELEASED, &frame_left, &frame_mid, &frame_right);
    lv_obj_align(widget.frame.rb, LV_ALIGN_TOP_LEFT, 110 + 240, 70);
    lv_obj_set_width(widget.frame.rb, 100);

    widget.status_bar.bg = lv_img_create(lv_scr_act());
    lv_obj_set_size(widget.status_bar.bg, 29, 135);
    lv_obj_align(widget.status_bar.bg, LV_ALIGN_TOP_RIGHT, 30, 0);
    lv_obj_set_style_bg_color(widget.status_bar.bg, lv_color_make(0, 0, 0), 0);
    lv_obj_set_style_bg_opa(widget.status_bar.bg, LV_OPA_40, 0);

    status_bar_create();
}

void HgmGUI::HgmMonitorView::widgetCreate()
{
    /* widgets */
    HgmFramework* fw = HgmFramework::getInstance();
    String _name = String("HgmMonitorUpdate");
    msg_t* msg = fw->hgmFwCenter.findMsg(_name);
    HardwareRequest* hrr = (HardwareRequest*)msg->pData();

    cpu_widget_create(hrr->GetHardwareObj(HGM_CPU)->pos);
    gpu_widget_create(hrr->GetHardwareObj(HGM_GPU)->pos);
    mem_widget_create(hrr->GetHardwareObj(HGM_MEMORY)->pos);
    network_widget_create(hrr->GetHardwareObj(HGM_NETWORK)->pos);

    widget.group = keypad_group;
    lv_group_add_obj(widget.group, widget.status_bar.prompt.btn);
    lv_group_add_obj(widget.group, widget.status_bar.next_btn);
}

void HgmGUI::HgmMonitorView::animCreate()
{
    /* Animations */
    widget.anim.flt = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    widget.anim.flb = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    widget.anim.frt = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    widget.anim.frb = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));
    widget.anim.sb = (lv_anim_t*)lv_mem_alloc(sizeof(lv_anim_t));

    lv_anim_init(widget.anim.flt);
    lv_anim_set_var(widget.anim.flt, widget.frame.lt);
    lv_anim_set_values(widget.anim.flt, 5 + 240, 5);
    lv_anim_set_early_apply(widget.anim.flt, false);
    lv_anim_set_exec_cb(widget.anim.flt, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(widget.anim.flt, lv_anim_path_ease_in_out);
    lv_anim_set_time(widget.anim.flt, 1500);

    lv_anim_init(widget.anim.flb);
    lv_anim_set_var(widget.anim.flb, widget.frame.lb);
    lv_anim_set_values(widget.anim.flb, 5 + 240, 5);
    lv_anim_set_early_apply(widget.anim.flb, false);
    lv_anim_set_exec_cb(widget.anim.flb, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(widget.anim.flb, lv_anim_path_ease_in_out);
    lv_anim_set_time(widget.anim.flb, 1500);

    lv_anim_init(widget.anim.frt);
    lv_anim_set_var(widget.anim.frt, widget.frame.rt);
    lv_anim_set_values(widget.anim.frt, 110 + 240, 110);
    lv_anim_set_early_apply(widget.anim.frt, false);
    lv_anim_set_exec_cb(widget.anim.frt, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(widget.anim.frt, lv_anim_path_ease_in_out);
    lv_anim_set_time(widget.anim.frt, 1500);

    lv_anim_init(widget.anim.frb);
    lv_anim_set_var(widget.anim.frb, widget.frame.rb);
    lv_anim_set_values(widget.anim.frb, 110 + 240, 110);
    lv_anim_set_early_apply(widget.anim.frb, false);
    lv_anim_set_exec_cb(widget.anim.frb, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(widget.anim.frb, lv_anim_path_ease_in_out);
    lv_anim_set_time(widget.anim.frb, 1500);

    lv_anim_init(widget.anim.sb);
    lv_anim_set_var(widget.anim.sb, widget.status_bar.bg);
    lv_anim_set_values(widget.anim.sb, 30, 0);
    lv_anim_set_early_apply(widget.anim.sb, false);
    lv_anim_set_exec_cb(widget.anim.sb, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(widget.anim.sb, lv_anim_path_ease_in_out);
    lv_anim_set_time(widget.anim.sb, 500);

    widget.anim.at = lv_anim_timeline_create();
    lv_anim_timeline_add(widget.anim.at, 0, widget.anim.flt);
    lv_anim_timeline_add(widget.anim.at, 200, widget.anim.flb);
    lv_anim_timeline_add(widget.anim.at, 600, widget.anim.frt);
    lv_anim_timeline_add(widget.anim.at, 800, widget.anim.frb);
    lv_anim_timeline_add(widget.anim.at, 2700, widget.anim.sb);
    lv_anim_timeline_start(widget.anim.at);
}

void HgmGUI::HgmMonitorView::animDestroy()
{
}

void HgmGUI::HgmMonitorView::widgetDestroy()
{

}

void HgmGUI::HgmMonitorView::frameDestroy()
{
}


void HgmGUI::HgmMonitorView::cpu_update(HardwareRequest* hrr)
{
    // #59493f
    lv_label_set_text_fmt(widget.cpu.label.name, "%s", hrr->hd->cpuData->name.c_str());
    lv_label_set_text_fmt(widget.cpu.label.power, "%dW/%dW", (uint32_t)hrr->hd->cpuData->powerCur, (uint32_t)hrr->hd->cpuData->powerMax);
    lv_label_set_text_fmt(widget.cpu.label.temp, "%03d℃", (uint32_t)hrr->hd->cpuData->tempAverage);
    lv_label_set_text_fmt(widget.cpu.label.usage, "%03d%%", (uint32_t)hrr->hd->cpuData->loadTotal);

    lv_bar_set_value(widget.cpu.bar.temp, hrr->hd->cpuData->tempAverage, LV_ANIM_ON);
    lv_bar_set_value(widget.cpu.bar.usage, hrr->hd->cpuData->loadTotal, LV_ANIM_ON);
}

void HgmGUI::HgmMonitorView::gpu_update(HardwareRequest* hrr)
{
    lv_label_set_text_fmt(widget.gpu.label.name, "%s", hrr->hd->gpuData->name.c_str());
    lv_label_set_text_fmt(widget.gpu.label.power, "%dW/%dW", (uint32_t)hrr->hd->gpuData->powerCur, (uint32_t)hrr->hd->gpuData->powerMax);
    lv_label_set_text_fmt(widget.gpu.label.temp, "%03d℃", (uint32_t)hrr->hd->gpuData->tempCoreCur);
    lv_label_set_text_fmt(widget.gpu.label.usage, "%03d%%", (uint32_t)hrr->hd->gpuData->coreLoad);

    lv_bar_set_value(widget.gpu.bar.temp, (int32_t)hrr->hd->gpuData->tempCoreCur, LV_ANIM_ON);
    lv_bar_set_value(widget.gpu.bar.usage, (int32_t)hrr->hd->gpuData->coreLoad, LV_ANIM_ON);
}

void HgmGUI::HgmMonitorView::mem_update(HardwareRequest* hrr)
{
    lv_label_set_text_fmt(widget.mem.label.percent, "Load:%03d%%", (uint32_t)hrr->hd->memData->load);
    lv_label_set_text_fmt(widget.mem.label.free, "Free:%dGB", (uint32_t)hrr->hd->memData->free);
    lv_label_set_text_fmt(widget.mem.label.used, "Used:%dGB", (uint32_t)hrr->hd->memData->used);

    lv_bar_set_value(widget.mem.bar.usage, (int32_t)hrr->hd->memData->load, LV_ANIM_ON);
}

static String _numWithUnit(size_t bytes)
{
    float _tmp;
    String out;
    String unit;

    if (bytes < (1 << 10))
        return String(bytes) + String("B");
    else if (bytes >= (1 << 10) && bytes < (1 << 20)) {
        return String(bytes / 1024) + String("KB");
    } else if (bytes >= (1 << 20) && bytes < (1 << 30)) {
        _tmp = (float)(bytes / 1024.0 / 1024.0);
        unit = String("MB");
        out = String(_tmp);
        out.remove(out.length() - 1);
        return out + unit;
    } else
        return String();
}

void HgmGUI::HgmMonitorView::net_update(HardwareRequest* hrr)
{
    HardwareNetData::HgmNetwork* dat;

    if (hrr->hd->netData->isWiFi)
        dat = &hrr->hd->netData->wlan;
    else
        dat = &hrr->hd->netData->ethernet;

    lv_label_set_text_fmt(widget.network.label.percent, "Load:%d%%#", (uint32_t)dat->utilization);
    lv_label_set_text_fmt(widget.network.label.upload, "↑%s/S#", _numWithUnit(dat->nt.upload).c_str());
    lv_label_set_text_fmt(widget.network.label.download, "↓%s/S#", _numWithUnit(dat->nt.download).c_str());

    lv_bar_set_value(widget.network.bar.usage, (int32_t)hrr->hd->memData->load, LV_ANIM_ON);
}

void HgmGUI::HgmMonitorView::disk_update(HardwareRequest* hrr)
{
    // TODO:
}

static String hdt = "{\"Header\":\"HgmTCP\",\"DataType\":\"4\",\"Data\":{\"CPU\":{\"name\":\"Intel Core i7-8700\",\"coreCount\":6,\"freq\":{\"bus\":99.75,\"current\":[4289.25,4289.25,4289.25,798.0,798.0,798.0]},\"temp\":{\"current\":[51.0,51.0,51.0,52.0,52.0,66.0],\"max\":66.0,\"average\":53.83},\"load\":{\"total\":9.02,\"current\":[7.06,10.59,5.29,4.12,7.06,20.0]},\"power\":{\"current\":26.29,\"max\":30.29}},\"GPU\":{\"name\":\"NVIDIA GeForce GTX 1660 Ti\",\"temp\":{\"current\":38.0,\"max\":59.0},\"freq\":{\"core\":{\"current\":300.0,\"max\":300.0},\"mem\":{\"current\":405.0,\"max\":405.0}},\"load\":{\"coreCurrent\":1.0,\"coreMax\":5.0},\"mem\":{\"free\":4814.0,\"used\":1329.0,\"total\":6144.0},\"power\":{\"current\":17.55,\"max\":233.55}},\"Memory\":{\"data\":{\"free\":5.7,\"used\":10.22,\"total\":15.92},\"load\":{\"current\":78.71,\"max\":78.71}},\"HardDisk\":{\"count\":3,\"data\":[{\"name\":\"Nameless Hard Disk #0\",\"temp\":{\"current\":0.0,\"max\":0.0},\"load\":{\"current\":77.87},\"throughput\":{\"readRate\":150.5,\"writeRate\":175934.2}},{\"name\":\"Colorful SL500 512GB DDR\",\"temp\":{\"current\":40.0,\"max\":40.0},\"load\":{\"current\":52.07},\"throughput\":{\"readRate\":251773.0,\"writeRate\":422494.4}},{\"name\":\"GALAX TA1D0120A\",\"temp\":{\"current\":33.0,\"max\":33.0},\"load\":{\"current\":85.58},\"throughput\":{\"readRate\":467368.1,\"writeRate\":497647.8}}]},\"Network\":{\"wlan\":{\"data\":{\"uploaded\":0.0,\"downloaded\":0.0},\"throughput\":{\"upload\":0.0,\"download\":0.0}},\"ethernet\":{\"data\":{\"uploaded\":0.02,\"downloaded\":0.2},\"throughput\":{\"upload\":111111.0,\"download\":16878000.14}}}}}";

static lv_timer_t* showTimeTimer = NULL;
static void ShowTime(lv_timer_t* timer)
{
    struct tm _tm = ti.rtc.getTimeStruct();
    lv_label_set_text_fmt(instance->widget.status_bar.time_label, "#c5b8b0 %02d#\n#c5b8b0 %02d#", _tm.tm_hour, _tm.tm_min);
}

static lv_timer_t* stateCheckTimer = NULL;
static void stateCheck(lv_timer_t* timer)
{
    //lv_img_set_src(widget.status_bar.battery.icon, &bat_50);
    // TODO: battery

    if (!WiFi.isConnected()) {
        lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_0);
    } else {
        lv_img_dsc_t* dsc;
        int8_t rssi = WiFi.RSSI();
        uint8_t ret = (((rssi + 100) << 1) << 1) >> 1;

        if (ret < 40)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_1);
        else if (ret < 60)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_2);
        else if (ret < 80)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_3);
        else if (ret < 100)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_4);
        else if (ret >= 100)
            lv_img_set_src(instance->widget.status_bar.signal.icon, &signal_5);
    }
    
}

void HgmGUI::HgmMonitorView::begin()
{
    frameCreate();
    animCreate();
    widgetCreate();

    showTimeTimer = lv_timer_create(ShowTime, 500, NULL);
    stateCheckTimer = lv_timer_create(stateCheck, 2000, NULL);
    
    lv_event_send(widget.status_bar.prompt.btn, LV_EVENT_CLICKED, NULL);
}

void HgmGUI::HgmMonitorView::end()
{
    // TODO: Destroy
    widgetDestroy();
    animDestroy();
    frameDestroy();
}

void HgmGUI::HgmMonitorView::alter_pos(HgmHardwarePosition from, HgmHardwarePosition to)
{
    // TODO: alter position
}

void HgmGUI::HgmMonitorView::update_monitor(HardwareRequest* hrr)
{
    // // TODO: 
    // HDJsonDoc doc(8192);
    // deserializeJson(doc, hdt);
    // Serial.println(doc["Header"].as<String>());

    // hrr->hd->cpuData->Set(doc);
    // hrr->hd->gpuData->Set(doc);
    // hrr->hd->memData->Set(doc);
    // hrr->hd->netData->Set(doc);
    // hrr->hd->diskData->Set(doc);

    if (hrr->isRequest(HGM_CPU))
        cpu_update(hrr);
    if (hrr->isRequest(HGM_GPU))
        gpu_update(hrr);
    if (hrr->isRequest(HGM_MEMORY))
        mem_update(hrr);
    if (hrr->isRequest(HGM_NETWORK))
        net_update(hrr);
    if (hrr->isRequest(HGM_HARD_DISK))
        disk_update(hrr);
}
