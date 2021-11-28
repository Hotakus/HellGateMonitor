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

	HgmFramework::getInstance()->viewsCenter.addMsg(&gui_msg);
	HgmFramework::getInstance()->viewsCenter.subscribe(&gui_subs);
}

HgmGUI::HgmMonitor::~HgmMonitor()
{
	HgmFramework::getInstance()->viewsCenter.unsubscribe(&gui_subs);
	HgmFramework::getInstance()->viewsCenter.removeMsg(gui_msg.id());

	instance = nullptr;
}

void HgmGUI::HgmMonitor::begin()
{
    Serial.println("------------------------------------------------- 01");
	def_vm.model.begin();
    Serial.println("------------------------------------------------- 02");

	// 订阅数据更新消息
	update_msg.id(_name + String("Update"));
	update_msg.pData(def_vm.model.hrr);
	update_subs.name(_name + String("Update"));
	update_subs.subscribe_msg(_name + String("Update"), HgmMonitor::monitor_update_cb);

    Serial.println("------------------------------------------------- 03");

	// 注册消息和订阅者
	HgmFramework::getInstance()->dataCenter.addMsg(&update_msg);
	HgmFramework::getInstance()->dataCenter.subscribe(&update_subs);

    Serial.println("------------------------------------------------- 04");

    hgmWiFi.hgmTcp->begin();
    hgmWiFi.OpenTCP();

    Serial.println("------------------------------------------------- 05");

	def_vm.view.begin();
    def_vm.model.hrr->initTask();

    Serial.println("------------------------------------------------- 06");
}

void HgmGUI::HgmMonitor::end()
{
    Serial.println("------------------------------------------------- 11");
    def_vm.model.hrr->deInitTask();
    Serial.println("------------------------------------------------- 12");
    def_vm.view.end();
    Serial.println("------------------------------------------------- 13");
    def_vm.model.end();
    Serial.println("------------------------------------------------- 14");

    hgmWiFi.OpenTCP(false);
    hgmWiFi.hgmTcp->stop();
    Serial.println("------------------------------------------------- 15");

	HgmFramework::getInstance()->dataCenter.unsubscribe(&update_subs);
	HgmFramework::getInstance()->dataCenter.removeMsg(update_msg.id());
    Serial.println("------------------------------------------------- 16");
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
