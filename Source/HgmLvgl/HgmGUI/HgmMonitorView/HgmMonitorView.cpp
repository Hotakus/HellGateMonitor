/******************************************************************
 * @file HgmMonitorView.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/11/7 20:37
 * @copyright Copyright (c) 2021/11/7
*******************************************************************/
#include "../../../HgmApp/HardwareInfoRecv/HardwareRequest.h"
#include "HgmMonitorView.h"

using namespace HgmGUI;
using namespace HgmApplication;

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

LV_FONT_DECLARE(k12x8_6px);
LV_FONT_DECLARE(k12x8_7px);
LV_FONT_DECLARE(k12x8_8px);
LV_FONT_DECLARE(k12x8_10px);
LV_FONT_DECLARE(k12x8_14px_time);
LV_FONT_DECLARE(k12x8_16px_time);
LV_FONT_DECLARE(k12x8_24px_time);

HgmGUI::HgmMonitorView::HgmMonitorView()
{
}

HgmGUI::HgmMonitorView::~HgmMonitorView()
{
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
    lv_label_set_text_fmt(widget.cpu.label.name, "Intel Core i7-8700");
    lv_obj_set_style_anim_speed(widget.cpu.label.name, 20, 0);

    widget.cpu.label.power = lv_label_create(f);
    lv_obj_set_style_text_font(widget.cpu.label.power, &k12x8_7px, 0);
    lv_obj_align_to(widget.cpu.label.power, widget.cpu.label.name, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.cpu.label.power, true);
    lv_label_set_text_fmt(widget.cpu.label.power, "#59493f 0233W#", 0);

    widget.cpu.label.temp = lv_label_create(f);
    lv_obj_set_style_text_font(widget.cpu.label.temp, &k12x8_7px, 0);
    lv_obj_align_to(widget.cpu.label.temp, widget.cpu.label.power, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.cpu.label.temp, true);
    lv_label_set_text_fmt(widget.cpu.label.temp, "#59493f 100℃#", 0);

    widget.cpu.label.usage = lv_label_create(f);
    lv_obj_set_style_text_font(widget.cpu.label.usage, &k12x8_7px, 0);
    lv_obj_align_to(widget.cpu.label.usage, widget.cpu.label.temp, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.cpu.label.usage, true);
    lv_label_set_text_fmt(widget.cpu.label.usage, "#59493f 100%%#", 0);

    widget.cpu.bar.temp = lv_bar_create(f);
    lv_obj_set_size(widget.cpu.bar.temp, 40, 8);
    lv_bar_set_value(widget.cpu.bar.temp, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.cpu.bar.temp, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.cpu.bar.temp, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.cpu.bar.temp, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.cpu.bar.temp, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(widget.cpu.bar.temp, widget.cpu.label.temp, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    widget.cpu.bar.usage = lv_bar_create(f);
    lv_obj_set_size(widget.cpu.bar.usage, 40, 8);
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
    lv_label_set_text_fmt(widget.gpu.label.name, "Inti7-8700");
    lv_obj_set_style_anim_speed(widget.gpu.label.name, 20, 0);

    widget.gpu.label.power = lv_label_create(f);
    lv_obj_set_style_text_font(widget.gpu.label.power, &k12x8_7px, 0);
    lv_obj_align_to(widget.gpu.label.power, widget.gpu.label.name, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.gpu.label.power, true);
    lv_label_set_text_fmt(widget.gpu.label.power, "#59493f 0233W#", 0);

    widget.gpu.label.temp = lv_label_create(f);
    lv_obj_set_style_text_font(widget.gpu.label.temp, &k12x8_7px, 0);
    lv_obj_align_to(widget.gpu.label.temp, widget.gpu.label.power, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.gpu.label.temp, true);
    lv_label_set_text_fmt(widget.gpu.label.temp, "#59493f 100℃#", 0);

    widget.gpu.label.usage = lv_label_create(f);
    lv_obj_set_style_text_font(widget.gpu.label.usage, &k12x8_7px, 0);
    lv_obj_align_to(widget.gpu.label.usage, widget.gpu.label.temp, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_label_set_recolor(widget.gpu.label.usage, true);
    lv_label_set_text_fmt(widget.gpu.label.usage, "#59493f 100%%#", 0);

    widget.gpu.bar.temp = lv_bar_create(f);
    lv_obj_set_size(widget.gpu.bar.temp, 40, 8);
    lv_bar_set_value(widget.gpu.bar.temp, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.gpu.bar.temp, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.gpu.bar.temp, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.gpu.bar.temp, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.gpu.bar.temp, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(widget.gpu.bar.temp, widget.gpu.label.temp, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    widget.gpu.bar.usage = lv_bar_create(f);
    lv_obj_set_size(widget.gpu.bar.usage, 40, 8);
    lv_bar_set_value(widget.gpu.bar.usage, 70, LV_ANIM_ON);
    lv_obj_set_style_radius(widget.gpu.bar.usage, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(widget.gpu.bar.usage, 2, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(widget.gpu.bar.usage, lv_color_make(0, 0, 0), LV_PART_MAIN);
    lv_obj_set_style_bg_color(widget.gpu.bar.usage, lv_color_make(0x6a, 0x83, 0x33), LV_PART_INDICATOR);
    lv_obj_align_to(widget.gpu.bar.usage, widget.gpu.label.usage, LV_ALIGN_OUT_RIGHT_MID, 11, 0);
}

void HgmMonitorView::mem_widget_create(HgmHardwarePosition pos)
{

}

void HgmMonitorView::network_widget_create(HgmHardwarePosition pos)
{

}

void HgmGUI::HgmMonitorView::begin()
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

    // TODO: Check battery
    widget.status_bar.battery.icon = lv_img_create(widget.status_bar.bg);
    lv_obj_align(widget.status_bar.battery.icon, LV_ALIGN_TOP_LEFT, 1, 5);
    lv_img_set_src(widget.status_bar.battery.icon, &bat_null);

    widget.status_bar.signal.icon = lv_img_create(widget.status_bar.bg);
    lv_obj_align(widget.status_bar.signal.icon, LV_ALIGN_TOP_MID, 0, 25);
    lv_img_set_src(widget.status_bar.signal.icon, &signal_0);

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

    /* widgets */
    // TODO: Check monitor position by configuration.

    cpu_widget_create(HGM_LEFT_TOP);
    gpu_widget_create(HGM_LEFT_BOTTOM);
}

void HgmGUI::HgmMonitorView::end()
{
}

void HgmGUI::HgmMonitorView::update_monitor(HardwareRequest::_hardData* hd)
{

}
