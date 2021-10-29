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

using namespace HgmGUI;

static HgmTw* instance = nullptr;

HgmGUI::HgmTw::HgmTw()
{
    instance = this;

    // 消息和订阅设置
    msg.set(_name, &_gd);
    subscriber.set(_name);
    subscriber.subscribe_msg(_name, HgmTw::hgm_ui_cb);

    // 注册消息和订阅者
    HgmFramework::getInstance()->hgmFwCenter.addMsg(&msg);
    HgmFramework::getInstance()->hgmFwCenter.subscribe(&subscriber);
}

HgmGUI::HgmTw::~HgmTw()
{
    instance = nullptr;

    HgmFramework::getInstance()->hgmFwCenter.unsubscribe(&subscriber);
    HgmFramework::getInstance()->hgmFwCenter.removeMsg(msg.id);
}

void HgmGUI::HgmTw::begin()
{
    def_vm.view.begin();
    def_vm.model.begin();
} 

void HgmGUI::HgmTw::end()
{
    def_vm.view.stop();
    def_vm.model.end();
}

void HgmGUI::HgmTw::setData(HgmTwModel::tw_data_t* _dat)
{
    def_vm.model.setData(_dat);
}

HgmTwModel::tw_data_t* HgmGUI::HgmTw::getData()
{
    return def_vm.model.getData();
}

void HgmTw::hgm_ui_cb(msg_t* msg)
{
    HgmFramework::gui_data_t* gd = ((HgmFramework::gui_data_t*)msg->pData);
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
    case HgmFramework::SET_DATA: {
        instance->setData((HgmTwModel::tw_data_t*)gd->pData);
    }
    default:
        break;
    }
}
