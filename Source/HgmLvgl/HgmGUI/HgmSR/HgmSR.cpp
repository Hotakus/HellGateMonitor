/******************************************************************
 * @file HgmSR.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/12/1 10:57
 * @copyright Copyright (c) 2021/12/1
*******************************************************************/
#include "HgmSR.h"
#include "HgmSRModel.h"
#include "../../../HgmApp/HardwareInfoRecv/HardwareRequest.h"
#include "../../../HgmApp/HgmWiFi/HgmWiFi.h"
#include "../../../HgmApp/ScreenRecv/ScreenRecv.h"

#define TAG "HgmSR"
#define HGM_DEBUG 1
#include "../../../HgmLogUtil.h"

using namespace HgmGUI;
using namespace HgmApplication;
using namespace HgmApplication::HgmJsonParseUtil;

extern HgmWiFi hgmWiFi;
extern ScreenRecv screenRecv;

static HgmSR* instance = nullptr;

HgmGUI::HgmSR::HgmSR()
{
    instance = this;

    gui_msg.id(_name);
    gui_subs.name(_name);
    gui_subs.subscribe_msg(_name, HgmSR::sr_ui_cb);

    HgmFramework::getInstance()->viewsCenter.addMsg(&gui_msg);
    HgmFramework::getInstance()->viewsCenter.subscribe(&gui_subs);
}

HgmGUI::HgmSR::~HgmSR()
{
    HgmFramework::getInstance()->viewsCenter.unsubscribe(&gui_subs);
    HgmFramework::getInstance()->viewsCenter.removeMsg(gui_msg.id());

    instance = nullptr;
}

void HgmGUI::HgmSR::begin()
{
    def_vm.model.begin();

    // 订阅数据更新消息
    status_msg.id("connStatus");
    update_msg.id(_name + String("Update"));
    //update_msg.pData(def_vm.model.hrr);

    update_subs.name(_name + String("Update"));
    update_subs.subscribe_msg(update_msg.id(), HgmSR::sr_screen_cb);
    update_subs.subscribe_msg(status_msg.id(), HgmSR::sr_status_cb);

    // 注册消息和订阅者
    HgmFramework::getInstance()->dataCenter.addMsg(&update_msg);
    HgmFramework::getInstance()->dataCenter.addMsg(&status_msg);
    HgmFramework::getInstance()->dataCenter.subscribe(&update_subs);

    def_vm.view.begin();
    screenRecv.begin(SR_OPEN_SINGLE_BUFF);
    screenRecv.initTask();
}

void HgmGUI::HgmSR::end()
{
    screenRecv.deInitTask();
    screenRecv.end();
    def_vm.view.end();
    def_vm.model.end();

    HgmFramework::getInstance()->dataCenter.unsubscribe(&update_subs);
    HgmFramework::getInstance()->dataCenter.removeMsg(update_msg.id());
    HgmFramework::getInstance()->dataCenter.removeMsg(status_msg.id());
}


void HgmGUI::HgmSR::sr_ui_cb(msg_t* msg)
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

void HgmGUI::HgmSR::sr_status_cb(msg_t* msg)
{
    bool* ds = (bool*)msg->pData();
    instance->def_vm.view.update_status(*ds);
}

void HgmGUI::HgmSR::sr_screen_cb(msg_t* msg)
{
    sr_t* sr = (sr_t*)msg->pData();
    instance->def_vm.view.update_screen(sr);
}

