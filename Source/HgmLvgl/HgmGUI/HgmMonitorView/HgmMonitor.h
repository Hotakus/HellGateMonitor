/******************************************************************
 * @file HgmMonitor.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/11/7 20:41
 * @copyright Copyright (c) 2021/11/7
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMMONITOR_H
#define HELLGATEMONITOR_HGMMONITOR_H

#include "HgmMonitorModel.h"
#include "HgmMonitorView.h"
#include "../../../Utils/MsgCenter/MsgCenter.h"

#include "../HgmFramework.h"

#include <Arduino.h>

using namespace msgmanager;

namespace HgmGUI {
	class HgmMonitor {
	private:
		String _name = "HgmMonitor";

		static void monitor_ui_cb(msg_t* msg);
		static void monitor_update_cb(msg_t* msg);
		static void monitor_pos_cb(msg_t* msg);
	public:

		/**
		 * @brief View and model
		 */
		struct _def_vm {
			HgmMonitorModel model;
			HgmMonitorView view;
		} def_vm;

		subscriber_t gui_subs;
		subscriber_t update_subs;
		msg_t gui_msg;
		msg_t update_msg;

		HgmMonitor();
		~HgmMonitor();

		void begin();
		void end();
		HgmMonitorModel::monitor_data_t * getData();
		String& name() {
			return this->_name;
		}
	};
}

#endif //HELLGATEMONITOR_HGMMONITOR_H
