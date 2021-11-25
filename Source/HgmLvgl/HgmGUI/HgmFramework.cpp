/******************************************************************
 * @file hgm_top_framework.c
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 18:36
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/
#include "../../LvglSrc/lvgl/lvgl.h"
#include "../../HgmApp/HotakusMemUtil.h"

#include "HgmFramework.h"
#include "HgmTwView/HgmTw.h"
#include "HgmMonitorView/HgmMonitor.h"

#define TAG "HgmFramework"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

#include <Arduino.h>

using namespace HgmGUI;

static HgmTw* hgmTw = nullptr;
static HgmMonitor* hgmMonitor = nullptr;

static HgmFramework* instance = nullptr;

HgmFramework::HgmFramework()
{
    instance = this;

    hgmFwCenter.begin();

    /* Create All UI */
    hgmMonitor = new HgmMonitor();
    hgmTw = new HgmTw();
}

HgmFramework::~HgmFramework()
{
    /* Remove All UI */
    delete hgmTw;
    delete hgmMonitor;

    hgmFwCenter.end();
    
    instance = NULL;
}

/**
 * @brief initialize the hgm framework
 */
void HgmGUI::HgmFramework::begin()
{
    changeGUI("HgmTw");
}

/**
 * @brief Change GUI by name.
 * @param name : Name of GUI
 * @return Boolean
 */
bool HgmGUI::HgmFramework::changeGUI(String name)
{

    hgm_log_d(TAG, "Change to %s", name.c_str());

    msg_t* msg = nullptr;
    bool ret = false;

	/* Kill the previous GUI  */
    if (!curr.isEmpty()) {
        msg = hgmFwCenter.findMsg(curr);
        if (!msg) return false;

        _gd.ctl = END;
        msg->pData(&_gd);
        ret = hgmFwCenter.notify(curr, curr);
        if (!ret) return ret;
        prev = curr;
    }

	/* Create the designated GUI  */
    msg = hgmFwCenter.findMsg(name);
    if (!msg) return false;
    _gd.ctl = BEGIN;
    msg->pData(&_gd);
    ret = hgmFwCenter.notify(name, name);
    if (ret)
        curr = name;
    return ret;
}

bool HgmGUI::HgmFramework::changePrev()
{
    return false;
}

bool HgmGUI::HgmFramework::changeNext()
{
    return false;
}

HgmFramework* HgmGUI::HgmFramework::getInstance()
{
    return instance;
}
