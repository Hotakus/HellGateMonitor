/******************************************************************
 * @file HgmMonitorView.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/11/7 20:37
 * @copyright Copyright (c) 2021/11/7
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMMONITORVIEW_H
#define HELLGATEMONITOR_HGMMONITORVIEW_H

#include "../../../LvglSrc/lvgl/lvgl.h"
#include "../../../HgmApp/HardwareInfoRecv/HardwareRequest.h"

using namespace HgmApplication;

namespace HgmGUI {
	class HgmMonitorView {
	private:
		void frameCreate();
		void widgetCreate();
		void animCreate();

		void animDestroy();
		void widgetDestroy();
		void frameDestroy();

        lv_obj_t* frame(HgmHardwarePosition pos);
        void cpu_widget_create(HgmHardwarePosition pos);
        void gpu_widget_create(HgmHardwarePosition pos);
        void mem_widget_create(HgmHardwarePosition pos);
        void network_widget_create(HgmHardwarePosition pos);
        void status_bar_create();

        void cpu_update(HardwareRequest* hrr);
        void gpu_update(HardwareRequest* hrr);
        void mem_update(HardwareRequest* hrr);
        void net_update(HardwareRequest* hrr);
        void disk_update(HardwareRequest* hrr);

	public:
        struct _widget
        {
            struct _status_bar {
                lv_obj_t* bg;
                struct _bat_icon {
                    lv_obj_t* icon;
                    uint8_t value;  // %
                } battery;

                struct _signal_icon {
                    lv_obj_t* icon;
                    uint8_t value;
                } signal;

                lv_obj_t* time_label;
                lv_obj_t* more_btn;
                lv_obj_t* next_btn;

            } status_bar;

            struct _frame {
                struct {
                    lv_obj_t* lt;
                    lv_obj_t* lb;
                    lv_obj_t* rt;
                    lv_obj_t* rb;
                } inner;

                lv_obj_t* lt;
                lv_obj_t* lb;
                lv_obj_t* rt;
                lv_obj_t* rb;
            } frame;

            struct _anim {
                lv_anim_timeline_t* at;
                lv_anim_t* flt;
                lv_anim_t* flb;
                lv_anim_t* frt;
                lv_anim_t* frb;
                lv_anim_t* sb;
            } anim;

            struct {
                struct {
                    lv_obj_t* name;
                    lv_obj_t* temp;
                    lv_obj_t* usage;
                    lv_obj_t* power;
                } label;

                struct {
                    lv_obj_t* usage;
                    lv_obj_t* temp;
                } bar;
            } cpu, gpu;

            struct _mem {
                lv_obj_t* icon;
                struct {
                    lv_obj_t* name;
                    lv_obj_t* percent;
                    lv_obj_t* used;
                    lv_obj_t* free;
                } label;

                struct {
                    lv_obj_t* usage;
                } bar;
            } mem;

            struct {
                struct {
                    lv_obj_t* name;
                    lv_obj_t* percent;
                    lv_obj_t* upload;
                    lv_obj_t* download;
                } label;

                struct {
                    lv_obj_t* usage;
                } bar;
            } network;
        } widget;

        HgmMonitorView();
		~HgmMonitorView();

		void begin();
		void end();

		void update_monitor(HardwareRequest* hrr);
        void alter_pos(HgmHardwarePosition from, HgmHardwarePosition to);
	};
}

#endif //HELLGATEMONITOR_HGMMONITORVIEW_H
