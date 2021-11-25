/******************************************************************
 * @file HgmMonitor.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/11/7 20:47
 * @copyright Copyright (c) 2021/11/7
*******************************************************************/
#include "HgmMonitor.h"
#include "HgmMonitorModel.h"
#include "../../../HgmApp/HardwareInfoRecv/HardwareRequest.h"
#include "../../../HgmApp/HgmWiFi/HgmWiFi.h"

#define TAG "HgmMonitor"
#define HGM_DEBUG 1
#include "../../../HgmLogUtil.h"

using namespace HgmGUI;
using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

extern HgmWiFi hgmWiFi;

static HgmMonitor* instance = nullptr;

HgmGUI::HgmMonitor::HgmMonitor()
{
	instance = this;

	gui_msg.id(_name);
	gui_subs.name(_name);
	gui_subs.subscribe_msg(_name, HgmMonitor::monitor_ui_cb);

	HgmFramework::getInstance()->hgmFwCenter.addMsg(&gui_msg);
	HgmFramework::getInstance()->hgmFwCenter.subscribe(&gui_subs);
}

HgmGUI::HgmMonitor::~HgmMonitor()
{
	HgmFramework::getInstance()->hgmFwCenter.unsubscribe(&gui_subs);
	HgmFramework::getInstance()->hgmFwCenter.removeMsg(gui_msg.id());

	instance = nullptr;
}

void HgmGUI::HgmMonitor::begin()
{
	def_vm.model.begin();

	// 订阅数据更新消息
	update_msg.id(_name + String("Update"));
	update_msg.pData(def_vm.model.hrr);
	update_subs.name(_name + String("Update"));
	update_subs.subscribe_msg(_name + String("Update"), HgmMonitor::monitor_update_cb);

	// 注册消息和订阅者
	HgmFramework::getInstance()->hgmFwCenter.addMsg(&update_msg);
	HgmFramework::getInstance()->hgmFwCenter.subscribe(&update_subs);

    hgmWiFi.hgmTcp->begin();
    hgmWiFi.OpenTCP();

	def_vm.view.begin();
    def_vm.model.hrr->initTask();
}

void HgmGUI::HgmMonitor::end()
{
	HgmFramework::getInstance()->hgmFwCenter.unsubscribe(&update_subs);
	HgmFramework::getInstance()->hgmFwCenter.removeMsg(update_msg.id());

	def_vm.view.end();
	def_vm.model.end();

    hgmWiFi.OpenTCP(false);
    hgmWiFi.hgmTcp->stop();
}

HgmMonitorModel::monitor_data_t * HgmGUI::HgmMonitor::getData()
{
	return def_vm.model.getData();
}

void HgmMonitor::monitor_ui_cb(msg_t* msg)
{
	HgmFramework::gui_data_t* gd = ((HgmFramework::gui_data_t*)msg->pData());
	HgmFramework::CTL_t ctl = gd->ctl;

	switch (ctl) {
		case HgmFramework::BEGIN: {
			instance->begin();
			break;
		}
		case HgmFramework::END: {
			instance->end();
			break;
		}
		default:
			break;
	}
}

void HgmMonitor::monitor_update_cb(msg_t *msg)
{
    HardwareRequest* hrr = (HardwareRequest*)msg->pData();
    instance->def_vm.view.update_monitor(hrr);
}
