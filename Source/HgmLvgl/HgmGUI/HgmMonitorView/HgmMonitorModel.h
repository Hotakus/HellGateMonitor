/******************************************************************
 * @file HgmMonitorModel.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/11/7 20:41
 * @copyright Copyright (c) 2021/11/7
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMMONITORMODEL_H
#define HELLGATEMONITOR_HGMMONITORMODEL_H

#include "../../../HgmApp/HardwareInfoRecv/HardwareRequest.h"

using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

namespace HgmGUI {
	class HgmMonitorModel {
	private:

	public:

		typedef struct _monitor_data_t {

		} monitor_data_t;

		monitor_data_t dat;

        HardwareRequest* hrr;

		HgmMonitorModel();
		~HgmMonitorModel();

		void begin();
		void end();
		monitor_data_t* getData();
	};
}

#endif //HELLGATEMONITOR_HGMMONITORMODEL_H
