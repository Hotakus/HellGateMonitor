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

	public:
		struct _widget {

		} widget;

        HgmMonitorView();
		~HgmMonitorView();

		void begin();
		void end();

		static void update_monitor(HardwareRequest::_hardData* hd);
	};
}

#endif //HELLGATEMONITOR_HGMMONITORVIEW_H
