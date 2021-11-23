/******************************************************************
 * @file HgmTw.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/30 2:03
 * @copyright Copyright (c) 2021/10/30
*******************************************************************/
#include "HgmTw.h"
#include "../HgmFramework.h"

#define HGM_DEBUG 1
#include "../../../HgmLogUtil.h"

using namespace HgmGUI;

static HgmTw* instance = nullptr;

HgmGUI::HgmTw::HgmTw()
{
    instance = this;

    gui_msg.id(_name);
    gui_subs.name(_name);
    gui_subs.subscribe_msg(_name, HgmTw::tw_ui_cb);

    HgmFramework::getInstance()->hgmFwCenter.addMsg(&gui_msg);
    HgmFramework::getInstance()->hgmFwCenter.subscribe(&gui_subs);
}

HgmGUI::HgmTw::~HgmTw()
{
    HgmFramework::getInstance()->hgmFwCenter.unsubscribe(&gui_subs);
    HgmFramework::getInstance()->hgmFwCenter.removeMsg(gui_msg.id());

    instance = nullptr;
}

void HgmGUI::HgmTw::begin()
{
    def_vm.model.begin();

    // 消息和订阅设置
    update_msg.id(_name + String("Update"));
    update_msg.pData(&def_vm.model.dat);
    update_subs.name(_name + String("Update"));
    update_subs.subscribe_msg(update_subs.name(), HgmTw::tw_update_cb);

    // 注册消息和订阅者
    HgmFramework::getInstance()->hgmFwCenter.addMsg(&update_msg);
    HgmFramework::getInstance()->hgmFwCenter.subscribe(&update_subs);

    def_vm.view.begin();
} 

void HgmGUI::HgmTw::end()
{
    HgmFramework::getInstance()->hgmFwCenter.unsubscribe(&update_subs);
    HgmFramework::getInstance()->hgmFwCenter.removeMsg(update_msg.id());

    def_vm.view.stop();
    def_vm.model.end();
}

HgmTwModel::tw_data_t* HgmGUI::HgmTw::getData()
{
    return def_vm.model.getData();
}

void HgmTw::tw_ui_cb(msg_t* msg)
{
    HgmFramework::gui_data_t* gd = ((HgmFramework::gui_data_t*)msg->pData());
    HgmFramework::CTL_t ctl = gd->ctl;

    switch (ctl)
    {
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

void HgmTw::tw_update_cb(msg_t* msg)
{
    HgmTwModel::tw_data_t* tw_data = ((HgmTwModel::tw_data_t*)msg->pData());
    if (!tw_data) {
        hgm_log_e(TAG, "data is null");
        return;
    }
    
    switch (tw_data->tdt)
    {
    case HgmTwModel::BILI: {
        HgmTwView::update_bili(tw_data);
        break;
    }
    case HgmTwModel::TIME: {
        HgmTwView::update_time(tw_data);
        break;
    }
    case HgmTwModel::WEATHER: {
        HgmTwView::update_weather(tw_data);
        break;
    }
    default:
        break;
    }
}
